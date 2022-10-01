#include <gtest/gtest.h>

#include "../core/heightmap/perlin_noise/perlin_original.h"

TEST(tests_get_perlin_heightmap_value, positive)
{
    int seed = 25;
    PerlinNoise perlin_noise(seed);
    double x = 5, y = 7, frequency = 0.5, amplitude = 0.5;
    double noise_value = perlin_noise.noise2D(x * frequency, y * frequency) * amplitude;
    double result = 0.21875;

    EXPECT_DOUBLE_EQ(result, noise_value);
}
