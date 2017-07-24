using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public sealed class CubicNoise
{
	private static readonly int RND_A = 134775813;
	private static readonly int RND_B = 1103515245;

	private int seed;
	private int octave;
	private int periodx = int.MaxValue;
	private int periody = int.MaxValue;

	public CubicNoise(int seed, int octave, int periodx, int periody)
	{
		this.seed = seed;
		this.octave = octave;
		this.periodx = periodx;
		this.periody = periody;
	}

	public CubicNoise(int seed, int octave)
	{
		this.seed = seed;
		this.octave = octave;
	}

	public float sample(float x)
	{
		int xi = (int)Mathf.Floor(x / octave);
		float lerp = x / octave - xi;

		return interpolate(
				randomize(seed, tile(xi - 1, periodx), 0),
				randomize(seed, tile(xi, periodx), 0),
				randomize(seed, tile(xi + 1, periodx), 0),
				randomize(seed, tile(xi + 2, periodx), 0),
				lerp) * 0.5f + 0.25f;
	}

	public float sample(float x, float y)
	{
		int xi = (int)Mathf.Floor(x / octave);
		float lerpx = x / octave - xi;
		int yi = (int)Mathf.Floor(y / octave);
		float lerpy = y / octave - yi;

		float[] xSamples = new float[4];

		for (int i = 0; i < 4; ++i)
			xSamples[i] = interpolate(
					randomize(seed, tile(xi - 1, periodx), tile(yi - 1 + i, periody)),
					randomize(seed, tile(xi, periodx), tile(yi - 1 + i, periody)),
					randomize(seed, tile(xi + 1, periodx), tile(yi - 1 + i, periody)),
					randomize(seed, tile(xi + 2, periodx), tile(yi - 1 + i, periody)),
					lerpx);

		return interpolate(xSamples[0], xSamples[1], xSamples[2], xSamples[3], lerpy) * 0.5f + 0.25f;
	}

	private static float randomize(int seed, int x, int y)
	{
		return (float)((((x ^ y) * RND_A) ^ (seed + x)) * (((RND_B * x) << 16) ^ (RND_B * y) - RND_A)) / int.MaxValue;
	}

	private static int tile(int coordinate, int period)
	{
		return coordinate % period;
	}

	private static float interpolate(float a, float b, float c, float d, float x)
	{
		float p = (d - c) - (a - b);

		return x * x * x * p + x * x * ((a - b) - p) + x * (c - a) + b;
	}
}
