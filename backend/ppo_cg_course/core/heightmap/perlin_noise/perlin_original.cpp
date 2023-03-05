#include "perlin_original.h"

PerlinNoise::PerlinNoise(unsigned int seed){
    reseed(seed);
}

PerlinNoise::~PerlinNoise(){
}

/*!
 * \brief reseed -- set permutation table
 * \param seed -- value defining permutation table
 */
void PerlinNoise::reseed(unsigned int seed){
    _seed = seed;

    for (int i = 0; i < 256; i++){
        _p[i] = i;
    }

    std::shuffle(std::begin(_p), std::begin(_p) + 256, std::default_random_engine(_seed));

    for (unsigned int i = 0; i < 256; i++){
        _p[256 + i] = _p[i];
    }
}

/*!
 * \brief PerlinNoise::fade -- fade function (f(t) = 6t^5 - 15t^4 + 10t^3)
 * \param t -- value of argumnet
 * \return value of function
 */
double PerlinNoise::fade(double t){
    return t * t * t * (t * (t * 6 - 15) + 10);
}

/*!
 * \brief PerlinNoise::lerp -- linear interpolation
 */
double PerlinNoise::lerp(double t, double a, double b){
    return a + t * (b - a);
}

double PerlinNoise::map(double value, double old_min, double old_max, double new_min, double new_max)
{
    double proportion = (value - old_min) / (old_max - old_min);
    return lerp(proportion, new_min, new_max);
}

double PerlinNoise::gradient(int hash, double x, double y, double z)
{
    int h = hash & 0b1111; //hash % 16
    double u = h < 0b1000 ? x : y;
    double v = h < 0b0100 ? y : h == 0b1100 || h == 0b1110 ? x : z;

    return ((h & 0b0001) == 0 ? u : -u) + ((h & 0b0010) == 0 ? v : -v);
}

/*!
 * \brief PerlinNoise::noise2D -- generate a noise with one frequency
 * \param x -- position X of pixel in the screen
 * \param y -- position X of pixel in the screen
 * \return generated value of height for pixel
 */
double PerlinNoise::noise2D(double x, double y)
{
    int xi = (int)(std::floor(x)) & 255;
    int yi = (int)(std::floor(y)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);

    double sx = fade(x);
    double sy = fade(y);

    unsigned char aa, ab, ba, bb;
    aa = _p[_p[xi] + yi];
    ab = _p[_p[xi] + yi + 1];
    ba = _p[_p[xi + 1] + yi];
    bb = _p[_p[xi + 1] + yi + 1];

    double average = lerp(sy, lerp(sx,
                                                     gradient(aa, x, y, 0),
                                                     gradient(ba, x - 1, y, 0)),
                                              lerp(sx,
                                                     gradient(ab, x, y - 1, 0),
                                                     gradient(bb, x - 1, y - 1, 0)));

    return map(average, -1, 1, 0, 1);
}

/*!
 * \brief PerlinNoise::accumulatedNoise2D -- generate a complex noise in one pixel
 * \param x -- position X of pixel in the screen
 * \param y -- position X of pixel in the screen
 * \param meta_data -- structure with perlin noise parameters
 * \return generated value of height of pixel in combined noise
 */
double PerlinNoise::accumulatedNoise2D(double x, double y, meta_data_t &meta_data)
{
     double lacunarity = meta_data.lacunarity;
     double gain = meta_data.gain;
     int octaves = meta_data.octaves;

     double amplitude = 1;
     double frequency = 1;
     double result = 0.0;
     double maxVal = 0.0;

     for (; octaves > 0; octaves--)
     {
         result += noise2D(x * frequency, y * frequency) * amplitude;
         maxVal += amplitude;

         amplitude *= gain;
         frequency *= lacunarity;
     }

     double e = result / maxVal;
     return e;
}
