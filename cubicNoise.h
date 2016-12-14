#pragma once

#include <stdint.h>

#define CUBIC_NOISE_PERIOD_INFINITELY UINT32_MAX

typedef struct {
	uint32_t seed;
	uint32_t octave;
	uint32_t width, height;
	uint32_t periodx, periody;
	int32_t offsetx, offsety;
} cubicNoiseConfig;

cubicNoiseConfig cubicNoiseConfig1D(
	const uint32_t seed,
	const uint32_t octave,
	const uint32_t length,
	const uint32_t period,
	const int32_t offset);

cubicNoiseConfig cubicNoiseConfig2D(
	const uint32_t seed,
	const uint32_t octave,
	const uint32_t width,
	const uint32_t height,
	const uint32_t periodx,
	const uint32_t periody,
	const int32_t offsetx,
	const int32_t offsety);

float cubicNoiseSample1D(
	const cubicNoiseConfig config,
	const float x);

float cubicNoiseSample2D(
	const cubicNoiseConfig config,
	const float x,
	const float y);