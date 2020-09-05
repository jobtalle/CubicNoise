function randomize(seed, x, y) {
	const RND_A = 134775813;
	const RND_B = 1103515245;

	return (((((x ^ y) * RND_A) ^ (seed + x)) * (((RND_B * x) << 16) ^ (RND_B * y) - RND_A)) >>> 0) / 4294967295;
}

function tile(coordinate, period) {
	if (coordinate < 0) while (coordinate < 0)
		coordinate += period;
	else
		return coordinate % period;
}

function interpolate(a, b, c, d, x) {
	const p = (d - c) - (a - b);

	return x * (x * (x * p + ((a - b) - p)) + (c - a)) + b;
}

/**
 * Config a cubic noise.
 * @param {Number} seed A seed in the range [0, 1].
 * @param {Number} [periodX] The number of units after which the x coordinate repeats.
 * @param {Number} [periodY] The number of units after which the y coordinate repeats.
 * @returns {Object} A configuration object used by noise functions.
 */
function cubicNoiseConfig(seed, periodX = Number.MAX_SAFE_INTEGER, periodY = Number.MAX_SAFE_INTEGER) {
	return {
		seed: Math.floor(seed * Number.MAX_SAFE_INTEGER),
		periodX: periodX,
		periodY: periodY
	}
}

/**
 * Sample 1D cubic noise.
 * @param {Object} config A valid noise configuration.
 * @param {Number} x The X position to sample at.
 * @returns {Number} A noise value in the range [0, 1].
 */
function cubicNoiseSample1(config, x) {
	const xi = Math.floor(x);
	const lerp = x - xi;

	return interpolate(
		randomize(config.seed, tile(xi - 1, config.periodX), 0),
		randomize(config.seed, tile(xi, config.periodX), 0),
		randomize(config.seed, tile(xi + 1, config.periodX), 0),
		randomize(config.seed, tile(xi + 2, config.periodX), 0),
		lerp) * 0.666666 + 0.166666;
}

/**
 * Sample 2D cubic noise.
 * @param {Object} config A valid noise configuration.
 * @param {Number} x The X position to sample at.
 * @param {Number} y The Y position to sample at.
 * @returns {Number} A noise value in the range [0, 1].
 */
function cubicNoiseSample2(config, x, y) {
	const xi = Math.floor(x);
	const lerpX = x - xi;
	const yi = Math.floor(y);
	const lerpY = y - yi;
	const x0 = tile(xi - 1, config.periodX);
	const x1 = tile(xi, config.periodX);
	const x2 = tile(xi + 1, config.periodX);
	const x3 = tile(xi + 2, config.periodX);

	const xSamples = new Array(4);

	for(let i = 0; i < 4; ++i) {
		const y = tile(yi - 1 + i, config.periodY);

		xSamples[i] = interpolate(
			randomize(config.seed, x0, y),
			randomize(config.seed, x1, y),
			randomize(config.seed, x2, y),
			randomize(config.seed, x3, y),
			lerpX);
	}

	return interpolate(xSamples[0], xSamples[1], xSamples[2], xSamples[3], lerpY) * 0.5 + 0.25;
}
