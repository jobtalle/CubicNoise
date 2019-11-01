const BufferedCubicNoise = function(width, height) {
    this.width = width;
    this.values = new Array((width + 2) * (height + 2));

    for (let i = 0; i < this.values.length; ++i)
        this.values[i] = Math.random();
};

BufferedCubicNoise.prototype.interpolate = function(a, b, c, d, x) {
    const p = (d - c) - (a - b);

    return x * (x * (x * p + ((a - b) - p)) + (c - a)) + b;
};

BufferedCubicNoise.prototype.sample = function(x, y) {
    const xi = Math.floor(x);
    const yi = Math.floor(y);

    return this.interpolate(
        this.interpolate(
            this.values[yi * this.width + xi],
            this.values[yi * this.width + xi + 1],
            this.values[yi * this.width + xi + 2],
            this.values[yi * this.width + xi + 3],
            x - xi),
        this.interpolate(
            this.values[(yi + 1) * this.width + xi],
            this.values[(yi + 1) * this.width + xi + 1],
            this.values[(yi + 1) * this.width + xi + 2],
            this.values[(yi + 1) * this.width + xi + 3],
            x - xi),
        this.interpolate(
            this.values[(yi + 2) * this.width + xi],
            this.values[(yi + 2) * this.width + xi + 1],
            this.values[(yi + 2) * this.width + xi + 2],
            this.values[(yi + 2) * this.width + xi + 3],
            x - xi),
        this.interpolate(
            this.values[(yi + 3) * this.width + xi],
            this.values[(yi + 3) * this.width + xi + 1],
            this.values[(yi + 3) * this.width + xi + 2],
            this.values[(yi + 3) * this.width + xi + 3],
            x - xi),
        y - yi) * 0.5 + 0.25;
};