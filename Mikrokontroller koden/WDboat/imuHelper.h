#pragma once
#include "Arduino.h"

#define GYRO_SCALE (4 / 16.4 * PI / 180.0 / 1000000.0)   //MPU6050 16.4 LSB/(deg/s) and we ignore the last 2 bits
#define ACC_LPF_FACTOR 4 // that means a LPF of 16
#define ACC_1G 512
#define GYR_CMPF_FACTOR 600
#define GYR_CMPFM_FACTOR 250
#define INV_GYR_CMPF_FACTOR   (1.0f / (GYR_CMPF_FACTOR  + 1.0f))
#define INV_GYR_CMPFM_FACTOR  (1.0f / (GYR_CMPFM_FACTOR + 1.0f))

typedef struct fp_vector
{
	float X, Y, Z;
} t_fp_vector_def;

typedef union
{
	float A[3];
	t_fp_vector_def V;
} t_fp_vector;

typedef struct int32_t_vector
{
	int32_t X, Y, Z;
} t_int32_t_vector_def;

typedef union
{
	int32_t A[3];
	t_int32_t_vector_def V;
} t_int32_t_vector;

int16_t _atan2(int32_t y, int32_t x);
float InvSqrt(float x);
void rotateV(struct fp_vector *v, float* delta);

