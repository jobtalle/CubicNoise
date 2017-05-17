package noise;

public final class CubicNoise {
    private static final int RND_A = 134775813;
    private static final int RND_B = 1103515245;

    private int seed;
    private int octave;
    private int periodx = Integer.MAX_VALUE;
    private int periody = Integer.MAX_VALUE;

    public CubicNoise(final int seed, final int octave, final int periodx, final int periody)
    {
        this(seed, octave);

        this.periodx = periodx;
        this.periody = periody;
    }

    public CubicNoise(final int seed, final int octave)
    {
        this.seed = seed;
        this.octave = octave;
    }

    public float sample(final float x)
    {
        final int xi = (int) Math.floor(x / octave);
        final float lerp = x / octave - xi;
        
        return interpolate(
                randomize(seed, tile(xi - 1, periodx), 0),
                randomize(seed, tile(xi, periodx), 0),
                randomize(seed, tile(xi + 1, periodx), 0),
                randomize(seed, tile(xi + 2, periodx), 0),
                lerp) * 0.5f + 0.25f;
    }

    public float sample(final float x, final float y)
    {
        final int xi = (int) Math.floor(x / octave);
        final float lerpx = x / octave - xi;
        final int yi = (int) Math.floor(y / octave);
        final float lerpy = y / octave - yi;

        float xSamples[] = new float[4];

        for(int i = 0; i < 4; ++i)
            xSamples[i] = interpolate(
                    randomize(seed, tile(xi - 1, periodx), tile(yi - 1 + i, periody)),
                    randomize(seed, tile(xi, periodx), tile(yi - 1 + i, periody)),
                    randomize(seed, tile(xi + 1, periodx), tile(yi - 1 + i, periody)),
                    randomize(seed, tile(xi + 2, periodx), tile(yi - 1 + i, periody)),
                    lerpx);

        return interpolate(xSamples[0], xSamples[1], xSamples[2], xSamples[3], lerpy) * 0.5f + 0.25f;
    }

    private static float randomize(final int seed, int x, int y)
    {
        return (float) ((((x ^ y) * RND_A) ^ (seed + x)) * (((RND_B * x) << 16) ^ (RND_B * y) - RND_A)) / Integer.MAX_VALUE;
    }

    private static int tile(final int coordinate, final int period)
    {
        return coordinate % period;
    }

    private static float interpolate(final float a, final float b, final float c, final float d, final float x)
    {
        final float p = (d - c) - (a - b);

        return x * x * x * p + x * x * ((a - b) - p) + x * (c - a) + b;
    }
}
