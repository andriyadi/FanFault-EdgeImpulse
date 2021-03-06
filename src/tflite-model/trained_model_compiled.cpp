/* Generated by Edge Impulse
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
// Generated on: 07.02.2021 06:55:45

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/kernels/micro_ops.h"

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#endif

namespace {

constexpr int kTensorArenaSize = 144;

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  TfLiteType type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
  TfLiteQuantization quantization;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

TfLiteContext ctx{};
TfLiteTensor tflTensors[11];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[4];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,33 } };
const TfArray<1, float> quant0_scale = { 1, { 0.012449424713850021, } };
const TfArray<1, int> quant0_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant0 = { (TfLiteFloatArray*)&quant0_scale, (TfLiteIntArray*)&quant0_zero, 0 };
const ALIGN(8) int32_t tensor_data1[32] = { -279, 4649, 912, -69, 3740, -49, -391, 1382, -13, -86, -58, -211, -70, 620, -57, 298, 1287, -204, 2246, -31, -32, -34, -50, -24, 384, -3, 3787, 1646, -23, 2285, -173, -59, };
const TfArray<1, int> tensor_dimension1 = { 1, { 32 } };
const TfArray<1, float> quant1_scale = { 1, { 0.00011629507935140282, } };
const TfArray<1, int> quant1_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant1 = { (TfLiteFloatArray*)&quant1_scale, (TfLiteIntArray*)&quant1_zero, 0 };
const ALIGN(8) int32_t tensor_data2[16] = { 1073, 5153, 3479, -2723, 7497, 6975, -1982, 217, -299, -990, -2545, 404, -222, 387, -2220, -517, };
const TfArray<1, int> tensor_dimension2 = { 1, { 16 } };
const TfArray<1, float> quant2_scale = { 1, { 7.635631482116878e-05, } };
const TfArray<1, int> quant2_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant2 = { (TfLiteFloatArray*)&quant2_scale, (TfLiteIntArray*)&quant2_zero, 0 };
const ALIGN(8) int32_t tensor_data3[3] = { -915, 264, 1017, };
const TfArray<1, int> tensor_dimension3 = { 1, { 3 } };
const TfArray<1, float> quant3_scale = { 1, { 0.00031668838346377015, } };
const TfArray<1, int> quant3_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant3 = { (TfLiteFloatArray*)&quant3_scale, (TfLiteIntArray*)&quant3_zero, 0 };
const ALIGN(8) int8_t tensor_data4[32*33] = { 
  20, 24, 39, 4, -4, -26, 30, 1, 3, 10, 97, 24, 21, 4, 0, -12, -4, 13, 32, -6, 16, 82, 37, 2, -6, 28, 13, -9, 14, 25, 58, 52, 35, 
  -61, 14, -6, 31, 0, -26, 24, -20, -2, -47, -90, -57, 26, -32, -1, 12, 26, -13, 19, -16, -38, -50, -46, 43, -5, -10, 3, 17, 31, 21, -94, -18, -63, 
  -75, -12, 4, 28, 19, -20, -12, -24, -20, -66, -87, -80, -3, 29, 29, -6, 1, 5, 6, -18, -73, -28, -80, 19, 1, 36, -17, -17, 31, 6, 8, -40, -28, 
  23, 34, 6, 13, 14, 5, 26, -17, 17, 20, 54, 60, 3, 4, 5, 2, -9, 10, -29, -20, 16, 74, 70, 29, 41, 10, -11, -21, -18, -32, 85, 63, 67, 
  -51, 27, -45, -3, 3, 6, 10, 30, 11, -20, -90, -8, -14, -46, 23, -10, 12, 7, -11, 30, -19, -42, -43, 20, -42, 5, 23, 21, 10, 19, -69, -36, -90, 
  104, -1, 28, 36, 22, -1, 3, -10, 2, 73, 84, 61, -6, 2, 19, -16, -4, -20, 2, -13, 38, 95, 115, 17, 35, 6, 27, 18, -30, -18, 101, 46, 116, 
  -28, -10, -27, 8, 17, -15, -8, 27, -10, 0, -9, -10, -5, -7, -19, 8, -27, 18, -19, 2, -22, 2, 8, -8, -28, 20, -37, 28, 3, 20, 13, -2, -18, 
  -74, 12, 10, 20, -10, 26, 29, 26, -4, 4, -33, -90, 42, 5, 16, 3, 30, 26, 6, -65, -73, -30, -88, 6, 16, 11, -6, -29, -20, -30, -42, -79, -53, 
  88, -34, -33, 22, -9, 13, 29, -16, 37, 44, 79, 89, -10, -17, -16, -15, -29, 10, 0, 52, 42, 65, 55, 10, -40, 19, 23, 24, -2, 16, 38, 71, 44, 
  79, 4, 37, 17, 12, 16, 17, 28, 13, 56, 98, 83, 39, -14, 24, 30, 8, 6, 11, 34, 27, 46, 99, 11, -8, -14, 15, -9, 20, 20, 77, 83, 61, 
  62, -5, 11, 18, 8, 4, -11, -6, 6, 54, 86, 88, -2, 20, 4, -4, 3, -4, -9, 28, -2, 56, 53, 23, 28, -6, 4, -29, -1, -24, 83, 84, 83, 
  58, -24, 13, 28, -1, 25, 0, 15, -11, 71, 57, 33, 22, -24, 26, 21, 2, 12, 22, -70, -29, 20, 23, -5, 22, -13, -8, -4, 24, -4, 53, 51, 61, 
  98, -5, 33, 23, -14, -5, 11, -26, 24, 108, 122, 72, 21, 20, -15, -20, 28, 4, 0, -6, 26, 73, 97, 11, 24, 6, -9, -24, 2, 15, 99, 85, 118, 
  -53, 1, -4, 9, 36, 10, -16, 14, 10, -11, -41, -30, 47, 6, -3, -20, 5, 31, 18, 13, 1, -36, -76, 32, 9, 2, 38, 25, -25, -1, 15, -20, 32, 
  69, -1, 50, 3, 6, 3, -27, -22, 61, 47, 86, 77, 17, 26, 13, 26, -16, -9, -27, 47, 61, 76, 110, 8, 4, 9, -20, -13, 21, -8, 127, 84, 60, 
  -19, -26, 10, 27, 0, -4, 20, 25, -17, -18, -3, -5, -8, -16, -4, -16, 22, 30, 20, 31, -50, -12, -11, 23, -6, 19, 13, 12, -4, -24, -43, 39, -10, 
  -57, 18, -7, -13, -15, -4, -32, -22, 37, -37, -50, 25, 16, -20, 4, 16, -28, -12, -14, 25, 17, -26, -54, -20, -36, 4, -27, -26, -14, 24, -37, -81, -72, 
  -15, 1, 6, -8, 11, -18, 1, -7, -13, 6, 2, 25, -3, -12, -10, 28, -11, -17, -14, 31, 5, -4, -11, -19, -17, -25, 17, -26, 3, 19, 4, -7, -28, 
  -112, -33, -2, -11, -7, -9, 2, -24, -58, -96, -122, -77, 14, 5, -26, -22, -23, -5, 2, -24, -27, -54, -81, 20, -18, -13, 24, -8, 0, 28, -93, -48, -90, 
  74, 1, 3, 32, -27, 28, -7, 5, 30, 57, 89, 96, -32, -13, -4, 25, -7, 24, 3, 70, 86, 92, 88, 18, 13, -24, -31, -24, 19, 25, 70, 57, 54, 
  71, 9, 19, 6, 1, 5, -2, -2, 8, 65, 97, 44, 17, -14, -10, -13, -24, 29, 30, 48, 76, 57, 110, -12, 24, 38, 12, -30, 10, 16, 107, 72, 94, 
  96, 0, 12, -11, -11, 21, 31, 30, 35, 74, 83, 79, 1, 5, 31, -13, 18, 18, 17, 45, 46, 109, 84, 1, 38, 8, 24, -9, 29, -3, 89, 59, 79, 
  28, 35, -2, 19, 5, 3, -27, -32, 15, 13, 51, 30, 17, -15, -24, 32, -24, 8, -2, 3, 27, 83, 76, -1, 12, 4, 31, -5, 25, 19, 49, 22, 85, 
  -9, -10, -26, -1, 22, 28, -19, -23, -9, 14, -7, 20, -10, 18, 7, 30, 19, 12, -32, 13, -26, 21, -32, -15, -14, -6, 25, -21, 5, 0, 20, -4, -15, 
  -5, 21, 7, -29, -16, 10, 1, 2, 7, -55, -70, -35, -13, 18, -8, -17, -7, 25, -20, -12, 21, -38, -33, 14, 19, -27, -19, -9, -7, -14, -42, 12, -43, 
  -11, -24, -23, 19, -8, -27, 3, -15, -15, 11, 17, -5, 28, -18, -10, 18, -23, 28, 26, 37, 43, -21, 7, 21, -19, 11, -23, 9, 8, -2, 12, -9, -12, 
  60, 36, 41, -28, 23, 17, -27, 6, 36, 0, 4, 21, -11, -9, 15, 5, 24, 11, -21, 39, 32, 25, 24, 0, -3, 8, 16, 11, 22, -31, 7, 19, -19, 
  70, 31, -8, -28, -18, -25, -8, 4, 16, -22, -37, 59, 6, 14, -29, -30, -1, -20, 0, 24, 34, 23, 64, -50, -5, -25, 33, -27, 24, 30, -11, 41, 37, 
  92, 12, 11, -27, -21, -25, -16, -23, 14, 74, 64, 51, -51, -32, 25, 29, 13, 25, 2, 44, 73, 45, 60, -41, -6, -26, 17, -3, 27, 23, 98, 93, 53, 
  37, -23, -14, -2, 15, -6, -15, 15, 40, -25, 22, 58, -36, -15, -26, -24, 15, 28, 15, 62, 23, 36, 57, 29, -17, -20, -4, -19, -30, 28, -2, 46, -13, 
  19, 17, 33, 18, -14, 22, -8, -26, 48, 66, 87, -5, 24, 50, 40, 19, -17, -13, 14, 14, 8, 68, 58, 9, 40, 12, 7, -12, 24, 15, 45, 40, 81, 
  93, 15, 5, 11, -21, 30, -28, -13, 7, 65, 98, 76, 22, -13, -18, -15, -11, 3, -28, -9, 12, 97, 70, 16, 10, 0, 26, -13, 14, 23, 93, 39, 79, 
};
const TfArray<2, int> tensor_dimension4 = { 2, { 32,33 } };
const TfArray<1, float> quant4_scale = { 1, { 0.0093414019793272018, } };
const TfArray<1, int> quant4_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant4 = { (TfLiteFloatArray*)&quant4_scale, (TfLiteIntArray*)&quant4_zero, 0 };
const ALIGN(8) int8_t tensor_data5[16*32] = { 
  -24, -4, -76, 37, 2, 4, 25, -53, 77, 25, -37, -39, 32, -79, 50, -9, 33, -19, -14, 60, 27, 72, 29, 3, 37, -13, -2, 56, 35, 19, -33, 51, 
  -28, 69, 41, -30, 36, -38, 23, 48, -25, -40, -33, -25, -59, 20, -41, 13, 34, 29, 95, 18, -4, -27, -29, 6, 36, -29, 16, 33, 9, 47, -3, -5, 
  -32, 44, -27, -24, 24, 12, -26, -25, 33, -17, -22, 8, -11, -23, -44, 27, 5, -27, 39, -35, -7, 0, 11, 3, 25, 24, 43, 46, 18, 52, -10, -31, 
  -14, 0, 0, 10, -23, 55, -4, 25, -1, 14, 25, 57, 62, 36, 61, -6, -10, -33, -39, 21, 11, 48, 33, -15, -1, -29, -14, 32, 33, -21, 10, 50, 
  15, 90, 108, -40, 105, -101, -14, 102, -85, -78, -38, -46, -104, 57, -76, 46, 116, -29, 120, -39, -96, -54, -68, 30, 34, 24, 46, 32, -112, 47, -36, -106, 
  22, 44, 53, -17, 84, -40, 4, 103, -96, -89, -127, 9, -70, 99, -111, -15, 45, -1, 103, -71, -54, -83, -54, 21, -17, 22, 57, -1, -114, 2, -16, -32, 
  37, 3, 8, 38, -1, 44, -15, 16, 39, 23, 33, -9, 51, 39, 34, -35, -27, 28, -55, 10, 49, 19, 4, -10, 7, 6, 3, -17, -18, 15, 19, 0, 
  -5, -10, -28, 40, -1, 103, 32, -48, 86, 40, 58, 33, 114, -22, 105, -30, -40, -29, -73, 75, 96, 87, 26, 25, 26, 14, 18, 68, 108, 71, 23, 58, 
  -26, -21, 27, -12, -17, -9, 1, 28, -5, -14, -37, 31, 23, 9, 17, 20, 0, -27, 17, -34, -7, -24, 29, 13, -14, -32, -23, -20, 19, -31, 4, 16, 
  2, -30, -56, 29, 26, 99, -32, -56, 69, 90, 112, -13, 93, -23, 112, -17, -37, 2, -26, 76, 83, 71, 45, 8, -21, 28, 40, 73, 106, 37, 10, 36, 
  8, -5, 19, 7, -15, 0, -10, 0, 49, 35, 24, 56, 76, 22, 71, -33, -12, -3, -66, -13, 11, 20, 38, -13, 16, 32, 19, 24, -19, -20, -7, 30, 
  13, -14, -35, 32, -4, 17, 27, -17, 41, 54, 58, -2, 53, -4, 66, 38, 13, 12, -72, 69, 75, 37, 39, 9, -9, 13, 7, 46, 61, 62, 15, 32, 
  28, 4, -95, 7, 24, 70, 9, -72, 40, 35, 48, -15, 72, -74, 72, 25, 15, 16, -68, 28, 28, 70, 13, 23, -18, 30, 21, 43, 63, 56, -10, 43, 
  2, 11, -64, 35, -26, 21, -2, -44, 38, 17, 44, 10, 94, 0, 30, -26, -17, -30, -71, 61, 44, 79, 34, -14, 23, -2, 41, 26, 53, 35, 43, 42, 
  14, 0, 19, 25, -42, 63, -13, -42, 31, 42, -10, 29, 75, 7, 36, -18, -27, 28, -33, -3, 24, 49, 12, -4, -28, 1, 32, -12, 19, -17, 35, 23, 
  23, 9, -11, 17, -22, -37, -29, -10, -12, 3, -12, -32, 8, 19, 22, 0, 21, -24, 11, -31, -16, 8, -27, 10, -3, 4, 4, -35, -20, -17, 2, -16, 
};
const TfArray<2, int> tensor_dimension5 = { 2, { 16,32 } };
const TfArray<1, float> quant5_scale = { 1, { 0.0099105006083846092, } };
const TfArray<1, int> quant5_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant5 = { (TfLiteFloatArray*)&quant5_scale, (TfLiteIntArray*)&quant5_zero, 0 };
const ALIGN(8) int8_t tensor_data6[3*16] = { 
  -4, -106, -88, 73, -68, -84, 43, 46, -40, 19, 16, 53, 35, 72, 97, -19, 
  55, 9, 73, -68, 4, -47, -23, 37, 37, 10, -78, 15, 72, 21, -79, 11, 
  -127, 52, 34, 21, 115, 90, -32, -91, 9, -103, -1, -112, -118, -116, -32, -36, 
};
const TfArray<2, int> tensor_dimension6 = { 2, { 3,16 } };
const TfArray<1, float> quant6_scale = { 1, { 0.0097929676994681358, } };
const TfArray<1, int> quant6_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant6 = { (TfLiteFloatArray*)&quant6_scale, (TfLiteIntArray*)&quant6_zero, 0 };
const TfArray<2, int> tensor_dimension7 = { 2, { 1,32 } };
const TfArray<1, float> quant7_scale = { 1, { 0.0077045867219567299, } };
const TfArray<1, int> quant7_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant7 = { (TfLiteFloatArray*)&quant7_scale, (TfLiteIntArray*)&quant7_zero, 0 };
const TfArray<2, int> tensor_dimension8 = { 2, { 1,16 } };
const TfArray<1, float> quant8_scale = { 1, { 0.032338347285985947, } };
const TfArray<1, int> quant8_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant8 = { (TfLiteFloatArray*)&quant8_scale, (TfLiteIntArray*)&quant8_zero, 0 };
const TfArray<2, int> tensor_dimension9 = { 2, { 1,3 } };
const TfArray<1, float> quant9_scale = { 1, { 0.23075641691684723, } };
const TfArray<1, int> quant9_zero = { 1, { 34 } };
const TfLiteAffineQuantization quant9 = { (TfLiteFloatArray*)&quant9_scale, (TfLiteIntArray*)&quant9_zero, 0 };
const TfArray<2, int> tensor_dimension10 = { 2, { 1,3 } };
const TfArray<1, float> quant10_scale = { 1, { 0.00390625, } };
const TfArray<1, int> quant10_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant10 = { (TfLiteFloatArray*)&quant10_scale, (TfLiteIntArray*)&quant10_zero, 0 };
const TfLiteFullyConnectedParams opdata0 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs0 = { 3, { 0,4,1 } };
const TfArray<1, int> outputs0 = { 1, { 7 } };
const TfLiteFullyConnectedParams opdata1 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs1 = { 3, { 7,5,2 } };
const TfArray<1, int> outputs1 = { 1, { 8 } };
const TfLiteFullyConnectedParams opdata2 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs2 = { 3, { 8,6,3 } };
const TfArray<1, int> outputs2 = { 1, { 9 } };
const TfLiteSoftmaxParams opdata3 = { 1 };
const TfArray<1, int> inputs3 = { 1, { 9 } };
const TfArray<1, int> outputs3 = { 1, { 10 } };
const TensorInfo_t tensorData[] = {
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension0, 33, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant0))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data1, (TfLiteIntArray*)&tensor_dimension1, 128, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant1))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 64, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant2))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 12, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant3))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data4, (TfLiteIntArray*)&tensor_dimension4, 1056, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant4))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 512, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant5))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 48, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant6))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 48, (TfLiteIntArray*)&tensor_dimension7, 32, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant7))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension8, 16, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant8))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 16, (TfLiteIntArray*)&tensor_dimension9, 3, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant9))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension10, 3, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant10))}, },
};const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs3, (TfLiteIntArray*)&outputs3, const_cast<void*>(static_cast<const void*>(&opdata3)), OP_SOFTMAX, },
};
static std::vector<void*> overflow_buffers;
static TfLiteStatus AllocatePersistentBuffer(struct TfLiteContext* ctx,
                                                 size_t bytes, void** ptr) {
  if (current_location - bytes < tensor_boundary) {
    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    *ptr = malloc(bytes);
    if (*ptr == NULL) {
      printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return kTfLiteError;
    }
    overflow_buffers.push_back(*ptr);
    return kTfLiteOk;
  }

  current_location -= bytes;

  *ptr = current_location;
  return kTfLiteOk;
}
typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;
static std::vector<scratch_buffer_t> scratch_buffers;

static TfLiteStatus RequestScratchBufferInArena(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  scratch_buffer_t b;
  b.bytes = bytes;

  TfLiteStatus s = AllocatePersistentBuffer(ctx, b.bytes, &b.ptr);
  if (s != kTfLiteOk) {
    return s;
  }

  scratch_buffers.push_back(b);

  *buffer_idx = scratch_buffers.size() - 1;

  return kTfLiteOk;
}

static void* GetScratchBuffer(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > static_cast<int>(scratch_buffers.size()) - 1) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}
} // namespace

  TfLiteStatus trained_model_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;
  ctx.AllocatePersistentBuffer = &AllocatePersistentBuffer;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArena;
  ctx.GetScratchBuffer = &GetScratchBuffer;
  ctx.tensors = tflTensors;
  ctx.tensors_size = 11;
  for(size_t i = 0; i < 11; ++i) {
    tflTensors[i].type = tensorData[i].type;
    tflTensors[i].is_variable = 0;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    tflTensors[i].allocation_type = tensorData[i].allocation_type;
#else
    tflTensors[i].allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
    tflTensors[i].bytes = tensorData[i].bytes;
    tflTensors[i].dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    if(tflTensors[i].allocation_type == kTfLiteArenaRw){
      uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

     tflTensors[i].data.data =  start;
    }
    else{
       tflTensors[i].data.data = tensorData[i].data;
    }
#else
    tflTensors[i].data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
    tflTensors[i].quantization = tensorData[i].quantization;
    if (tflTensors[i].quantization.type == kTfLiteAffineQuantization) {
      TfLiteAffineQuantization const* quant = ((TfLiteAffineQuantization const*)(tensorData[i].quantization.params));
      tflTensors[i].params.scale = quant->scale->data[0];
      tflTensors[i].params.zero_point = quant->zero_point->data[0];
    }
    if (tflTensors[i].allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tflTensors[i].data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }
  if (tensor_boundary > current_location /* end of arena size */) {
    printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }
  registrations[OP_FULLY_CONNECTED] = *tflite::ops::micro::Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = *tflite::ops::micro::Register_SOFTMAX();

  for(size_t i = 0; i < 4; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
    tflNodes[i].custom_initial_data = nullptr;
    tflNodes[i].custom_initial_data_size = 0;
    if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for(size_t i = 0; i < 4; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  0, 
};
TfLiteTensor* trained_model_input(int index) {
  return &ctx.tensors[inTensorIndices[index]];
}

static const int outTensorIndices[] = {
  10, 
};
TfLiteTensor* trained_model_output(int index) {
  return &ctx.tensors[outTensorIndices[index]];
}

TfLiteStatus trained_model_invoke() {
  for(size_t i = 0; i < 4; ++i) {
    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);
    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus trained_model_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif
  scratch_buffers.clear();
  for (size_t ix = 0; ix < overflow_buffers.size(); ix++) {
    free(overflow_buffers[ix]);
  }
  overflow_buffers.clear();
  return kTfLiteOk;
}
