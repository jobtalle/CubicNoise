#pragma once

#include <stdint.h>

#define CUBIC_NOISE_PERIOD_INFINITELY INT32_MAX

typedef struct {
	uint32_t seed;
	int32_t octave;
	int32_t periodx, periody;
} cubicNoiseConfig;

cubicNoiseConfig cubicNoiseConfig1D(
	const uint32_t seed,
	const int32_t octave,
	const int32_t period);

cubicNoiseConfig cubicNoiseConfig2D(
	const uint32_t seed,
	const int32_t octave,
	const int32_t periodx,
	const int32_t periody);

float cubicNoiseSample1D(
	const cubicNoiseConfig config,
	const float x);

float cubicNoiseSample2D(
	const cubicNoiseConfig config,
	const float x,
	const float y);