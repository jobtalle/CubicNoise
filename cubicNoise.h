#pragma once

#include <stdint.h>

#define CUBIC_NOISE_PERIOD_INFINITELY UINT32_MAX

typedef struct {
	uint32_t seed;
	uint32_t octave;
	uint32_t periodx, periody;
} cubicNoiseConfig;

cubicNoiseConfig cubicNoiseConfig1D(
	const uint32_t seed,
	const uint32_t octave,
	const uint32_t period);

cubicNoiseConfig cubicNoiseConfig2D(
	const uint32_t seed,
	const uint32_t octave,
	const uint32_t periodx,
	const uint32_t periody);

float cubicNoiseSample1D(
	const cubicNoiseConfig config,
	const float x);

float cubicNoiseSample2D(
	const cubicNoiseConfig config,
	const float x,
	const float y);