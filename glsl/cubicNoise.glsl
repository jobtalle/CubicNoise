float random(vec3 x) {
    return fract(sin(x.x + x.y * 57.0 + x.z * 113.0) * 43758.5453);
}

float interpolate(float a, float b, float c, float d, float x) {
    float p = (d - c) - (a - b);
    
    return x * (x * (x * p + ((a - b) - p)) + (c - a)) + b;
}

float sampleX(vec3 at) {
    float floored = floor(at.x);
    
    return interpolate(
        random(vec3(floored - 1.0, at.yz)),
        random(vec3(floored, at.yz)),
        random(vec3(floored + 1.0, at.yz)),
        random(vec3(floored + 2.0, at.yz)),
    	fract(at.x)) * 0.5 + 0.25;
}

float sampleY(vec3 at) {
    float floored = floor(at.y);
    
    return interpolate(
        sampleX(vec3(at.x, floored - 1.0, at.z)),
        sampleX(vec3(at.x, floored, at.z)),
        sampleX(vec3(at.x, floored + 1.0, at.z)),
        sampleX(vec3(at.x, floored + 2.0, at.z)),
        fract(at.y));
}

float cubicNoise(vec3 at) {
    float floored = floor(at.z);
    
    return interpolate(
        sampleY(vec3(at.xy, floored - 1.0)),
        sampleY(vec3(at.xy, floored)),
        sampleY(vec3(at.xy, floored + 1.0)),
        sampleY(vec3(at.xy, floored + 2.0)),
        fract(at.z));
}