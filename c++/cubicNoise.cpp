#include <cmath>

#include "cubicNoise.hpp"

float CubicNoise::sample(const CubicNoiseConfig &config, const float x)
{
	const int32_t xi = (int32_t)floorf(x / config.octave);
	const float lerp = x / config.octave - xi;

	return interpolate(
		random(config.seed, tile(xi - 1, config.periodx), 0),
		random(config.seed, tile(xi, config.periodx), 0),
		random(config.seed, tile(xi + 1, config.periodx), 0),
		random(config.seed, tile(xi + 2, config.periodx), 0),
		lerp) * 0.5f + 0.25f;
}

float CubicNoise::sample(const CubicNoiseConfig &config, const float x, const float y)
{
	const int32_t xi = (int32_t)floorf(x / config.octave);
	const float lerpx = x / config.octave - xi;
	const int32_t yi = (int32_t)floorf(y / config.octave);
	const float lerpy = y / config.octave - yi;

	float xSamples[4];

	for(int i = 0; i < 4; ++i)
		xSamples[i] = interpolate(
			random(config.seed,
				tile(xi - 1, config.periodx),
				tile(yi - 1 + i, config.periody)),
			random(config.seed,
				tile(xi, config.periodx),
				tile(yi - 1 + i, config.periody)),
			random(config.seed,
				tile(xi + 1, config.periodx),
				tile(yi - 1 + i, config.periody)),
			random(config.seed,
				tile(xi + 2, config.periodx),
				tile(yi - 1 + i, config.periody)),
			lerpx);

	return interpolate(
		xSamples[0], xSamples[1], xSamples[2], xSamples[3], lerpy) * 0.5f + 0.25f;
}

float CubicNoise::random(const uint32_t seed, const int32_t x, const int32_t y)
{
	return (float)
		((((x ^ y) * CubicNoise::RAND_A) ^ (seed + x)) *
		(((CubicNoise::RAND_B * x) << 16) ^ (CubicNoise::RAND_B * y) - CubicNoise::RAND_A)) /
		UINT32_MAX;
}

int32_t CubicNoise::tile(const int32_t coordinate, const int32_t period)
{
	return coordinate % period;
}

float CubicNoise::interpolate(const float a, const float b, const float c, const float d, const float x)
{
	const float p = (d - c) - (a - b);

	return x * (x * (x * p + ((a - b) - p)) + (c - a)) + b;
}