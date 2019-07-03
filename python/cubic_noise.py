from math import floor

# Feel free to change these
RND_A = 134775813
RND_B = 1103515245
SEED = 1
# Python3 integers are unlimited size.
# MAX_VAL is set so cubic_noise.py works the same as the other implementations.
MAX_VAL = 2**31 - 1
periodx = MAX_VAL
periody = MAX_VAL
# Don't change MASK. MASK is used for the bitwise operations in randomize()
MASK = 2**32 - 1

def interpolate(a, b, c, d, x):
    p = (d - c) - (a - b)
    return x * (x * (x * p + ((a - b) - p)) + (c - a)) + b

def randomize(x, y, seed=SEED):
    return (((((x ^ y) * RND_A) ^ (seed + x)) *
		(((RND_B * x) << 16) ^ (RND_B * y) - RND_A)) & MASK) / MASK

def tile(coordinate, period=MAX_VAL):
    return coordinate % period

def _sample1d(x, seed=SEED, octave=1):
    xi = floor(x / octave)
    lerp = x / octave - xi
    return interpolate(
                randomize(tile(xi - 1, periodx), 0, seed),
                randomize(tile(xi, periodx), 0, seed),
                randomize(tile(xi + 1, periodx), 0, seed),
                randomize(tile(xi + 2, periodx), 0, seed),
                lerp) * 0.5 + 0.25;

def _sample2d(x, y, seed=SEED, octave=1):
    xi = floor(x / octave)
    lerpx = x / octave - xi
    yi = floor(y / octave)
    lerpy = y / octave - yi
    
    xSamples = [0,0,0,0]
    
    for ii in range(4):
        xSamples[ii] = interpolate(
            randomize(tile(xi - 1, periodx), tile(yi - 1 + ii, periody), seed),
            randomize(tile(xi, periodx), tile(yi - 1 + ii, periody), seed),
            randomize(tile(xi + 1, periodx), tile(yi - 1 + ii, periody), seed),
            randomize(tile(xi + 2, periodx), tile(yi - 1 + ii, periody), seed),
            lerpx)
    
    return interpolate(*xSamples, lerpy) * 0.5 + 0.25;

def sample(x=None, y=None, seed=SEED, octave=1):
    if x is None:
        return _sample1d(y, seed, octave)
    elif y is None:
        return _sample1d(x, seed, octave)
    else:
        return _sample2d(x, y, seed, octave)
