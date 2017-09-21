#pragma once

#include <cstdint>

struct CubicNoiseConfig;

class CubicNoise
{
public:
	static float sample(const CubicNoiseConfig &config, const float x);
	static float sample(const CubicNoiseConfig &config, const float x, const float y);

	static const int PERIOD_MAX = INT32_MAX;

private:
	static float random(const uint32_t seed, const int32_t x, const int32_t y);
	static int32_t tile(const int32_t coordinate, const int32_t period);
	static float interpolate(const float a, const float b, const float c, const float d, const float x);

	static const unsigned int RAND_A = 134775813;
	static const unsigned int RAND_B = 1103515245;
};

struct CubicNoiseConfig
{
public:
	CubicNoiseConfig(
		const uint32_t seed,
		const int32_t octave,
		const int32_t periodx = CubicNoise::PERIOD_MAX,
		const int32_t periody = CubicNoise::PERIOD_MAX)
		:seed(seed), octave(octave), periodx(periodx), periody(periody) {}

	uint32_t seed;
	int32_t octave;
	int32_t periodx;
	int32_t periody;
};