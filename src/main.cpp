/* Includes ---------------------------------------------------------------- */
#include <Arduino.h>
#include "fan-fault_inference.h"
#include <Arduino_LSM9DS1.h>

/* Color */
#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
//#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
//#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
//#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR(COLOR)  "\u001b[" COLOR "m"
#define LOG_BOLD(COLOR)   "\u001b[" COLOR ";1m"
#define LOG_RESET_COLOR   "\u001b[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_BOLD_I  LOG_BOLD(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V


/* Constant defines -------------------------------------------------------- */
#define CONVERT_G_TO_MS2    9.80665f

/* Private variables ------------------------------------------------------- */
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal
static uint32_t run_inference_every_ms = 200;
static rtos::Thread inference_thread(osPriorityLow);
static float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = {0};
static float inference_buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE];

/* Forward declaration */
void run_inference_background();

/**
* @brief      Arduino setup function
*/
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Edge Impulse Inferencing Demo");

    if (!IMU.begin()) {
        ei_printf("Failed to initialize IMU!\r\n");
    } else {
        ei_printf("%sIMU initialized%s\r\n", LOG_COLOR_E, LOG_RESET_COLOR);
    }

    // LED init
    pinMode(LEDR, OUTPUT);
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    if (EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != 3) {
        ei_printf("ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME should be equal to 3 (the 3 sensor axes)\n");
        return;
    }

    inference_thread.start(mbed::callback(&run_inference_background));
}

/**
* @brief      Printf function uses vsnprintf and output using Arduino Serial
*
* @param[in]  format     Variable argument list
*/
void ei_printf(const char *format, ...) {
    static char print_buf[1024] = {0};

    va_list args;
    va_start(args, format);
    int r = vsnprintf(print_buf, sizeof(print_buf), format, args);
    va_end(args);

    if (r > 0) {
        Serial.write(print_buf);
    }
}

/**
* @brief      Blink led based on classification label
*
* @param[in]  label      classification label
*/
void led_blinker(const char *label) {
    // Reset LED
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    if (strcmp(label, "off") == 0) {
        digitalWrite(LEDG, LOW);
    } else if (strcmp(label, "normal") == 0) {
        digitalWrite(LEDB, LOW);
    } else if (strcmp(label, "issue") == 0) {
        static uint32_t lastRedLedBlink = 0;
        static bool lastRedOn = true;
        if (millis() - lastRedLedBlink > 300) {
            lastRedOn = !lastRedOn;
            digitalWrite(LEDR, lastRedOn);
            lastRedLedBlink = millis();
        }
    }
}

/**
 * @brief      Run inferencing in the background.
 */
void run_inference_background() {
    // wait until we have a full buffer
    delay((EI_CLASSIFIER_INTERVAL_MS * EI_CLASSIFIER_RAW_SAMPLE_COUNT) + 100);

    // This is a structure that smoothens the output result
    // With the default settings 70% of readings should be the same before classifying.
    ei_classifier_smooth_t smooth;
    //ei_classifier_smooth_init(&smooth, 10 /* no. of readings */, 7 /* min. readings the same */, 0.8 /* min. confidence */, 0.3 /* max anomaly */);
    ei_classifier_smooth_init(&smooth,
                              8 /* no. of readings */,
                              4 /* min. readings the same */,
                              0.6 /* min. confidence */,
                              0.3 /* max anomaly */);

    while (1) {
        // copy the buffer
        memcpy(inference_buffer, buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE * sizeof(float));

        // Turn the raw buffer in a signal which we can the classify
        signal_t signal;
        int err = numpy::signal_from_buffer(inference_buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
        if (err != 0) {
            ei_printf("Failed to create signal from buffer (%d)\n", err);
            return;
        }

        // Run the classifier
        ei_impulse_result_t result = {0};

        err = run_classifier(&signal, &result, debug_nn);
        if (err != EI_IMPULSE_OK) {
            ei_printf("ERR: Failed to run classifier (%d)\n", err);
            return;
        }

        // print the predictions
        /*
        ei_printf("Predictions ");
        ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
           result.timing.dsp, result.timing.classification, result.timing.anomaly);
        ei_printf(": ");

        // ei_classifier_smooth_update yields the predicted label
        const char *prediction = ei_classifier_smooth_update(&smooth, &result);
        ei_printf("%s ", prediction);
        // print the cumulative results
        ei_printf(" [ ");
        for (size_t ix = 0; ix < smooth.count_size; ix++) {
           ei_printf("%u", smooth.count[ix]);
           if (ix != smooth.count_size + 1) {
               ei_printf(", ");
           }
           else {
             ei_printf(" ");
           }
        }
        ei_printf("]\n");
        */

        const char *prediction = ei_classifier_smooth_update(&smooth, &result);
        if (strcmp(prediction, "uncertain") == 0) {
            ei_printf("Prediction: %s%10s%s  ->  ", LOG_COLOR_E, prediction, LOG_RESET_COLOR);
        }
        else {
            ei_printf("Prediction: %s%10s%s  ->  ", LOG_COLOR_BOLD_I, prediction, LOG_RESET_COLOR);
        }

        // Light up LED
        led_blinker(prediction);

        for (size_t ix = 0; ix < smooth.count_size; ix++) {

            bool uncertain_anom = false;

            if (ix < EI_CLASSIFIER_LABEL_COUNT) {
                ei_printf("%s: ", ei_classifier_inferencing_categories[ix]);
            }
            else {
                ei_printf("%s%s: ", (ix == EI_CLASSIFIER_LABEL_COUNT? "  |  ":""), (ix == EI_CLASSIFIER_LABEL_COUNT + 1)? "uncertain": "anomaly");
                uncertain_anom = true;
            }

            size_t barNum = smooth.count[ix];

            for (size_t j = 0; j < barNum; j++) {
                if (uncertain_anom) {
                    ei_printf("%s%s%s", LOG_COLOR_E, "█", LOG_RESET_COLOR);
                }
                else {
                    ei_printf("%s%s%s", LOG_COLOR_I, "█", LOG_RESET_COLOR);
                }
            }
            for (size_t j = (barNum); j < smooth.last_readings_size; j++) {
                ei_printf(" ");
            }

            if (ix != smooth.count_size + 1) {
                ei_printf("  ");
            }
        }
        ei_printf("\n");

        delay(run_inference_every_ms);
    }

    ei_classifier_smooth_free(&smooth);
}

/**
* @brief      Get data and run inferencing
*
* @param[in]  debug  Get debug info if true
*/
void loop() {
    while (1) {
        // Determine the next tick (and then sleep later)
        uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 1000);

        // roll the buffer -3 points so we can overwrite the last one
        numpy::roll(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, -3);

        // read to the end of the buffer
        IMU.readAcceleration(
                buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 3],
                buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 2],
                buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 1]
        );

        buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 3] *= CONVERT_G_TO_MS2;
        buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 2] *= CONVERT_G_TO_MS2;
        buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE - 1] *= CONVERT_G_TO_MS2;

        // and wait for next tick
        uint64_t time_to_wait = next_tick - micros();
        delay((int) floor((float) time_to_wait / 1000.0f));
        delayMicroseconds(time_to_wait % 1000);
    }
}

#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_ACCELEROMETER
#error "Invalid model for current sensor"
#endif