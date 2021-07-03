# FanFault-EdgeImpulse
Fan operation monitoring, powered by TinyML and [Edge Impulse](https://edgeimpulse.com). A simple project to classify fan operation, whether it is currently off, working normally, or any issue.

It is developed for Arduino Nano 33 BLE Sense devboard. For other boards, refer to Edge Impulse [docs](https://docs.edgeimpulse.com/docs/fully-supported-development-boards). 
To make my life easier, I use PlatformIO as tooling, and CLion as IDE, but you can use VSCode with PlatformIO extension.

## Video
I made a demo video to show how it works

[![Demo Video](http://i3.ytimg.com/vi/GB6ArqH_eLo/maxresdefault.jpg)](https://youtu.be/GB6ArqH_eLo)

Also, I used this project as demo when delivering a webinar in Hannover Messe 2021, about "Unlocking the Potential of IoT with on-device AI", as shown in this video:

[![Unlocking the Potential of IoT with on-device AI](http://i3.ytimg.com/vi/EySmxypcWY0/hqdefault.jpg)](https://www.youtube.com/watch?v=EySmxypcWY0)

## Edge Impulse
Public project: https://studio.edgeimpulse.com/public/17594/latest

This is demo state project, dataset is not much. But you get the idea.

To get started with Arduino Nano 33 BLE Sense and Edge Impulse, [read this](https://docs.edgeimpulse.com/docs/arduino-nano-33-ble-sense).

## Screen Capture
Inference result on console:
![capture](https://raw.githubusercontent.com/andriyadi/FanFault-EdgeImpulse/main/assets/terminal_cap.png)
I'm using ANSI color code to get the text colored and bolded. To get the same effect, make sure your terminal supports it.

## How to replicate
You need to have PlatformIO installed. 
Project should be buildable just by typing: `pio run` on terminal. 
To build and view the result, run `./flashmon.sh`
