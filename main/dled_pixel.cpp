#ifdef __cplusplus
extern "C" {
#endif

#include "dled_pixel.h"

void dled_pixel_set(pixel_t* pixel, uint8_t r, uint8_t g, uint8_t b)
{
	if (pixel == NULL) return;
	pixel->r = r, pixel->g = g, pixel->b = b;
}

void dled_pixel_off(pixel_t* pixel)
{
	if (pixel == NULL) return;
	pixel->r = 0, pixel->g = 0, pixel->b = 0;
}

/*
 * Maximum number of colors is: 6 * strand->brightLimit;
 * r max. g /   b 0
 * r \    g max
 * r 0    g max b /
 * r 0    g \   b max
 * r /    g 0   b max
 * r max  g 0   b \
 */
pixel_t dled_pixel_get_color_by_index(uint8_t max_cc_val, uint16_t index)
{
    pixel_t pixel;
    uint8_t seq;
    uint8_t idx;
    uint8_t maxVal;

    if (max_cc_val == 0) {
        dled_pixel_off(&pixel);
        return pixel;
    }
    maxVal = max_cc_val;

    seq = (index / maxVal) % 6;
    idx =  index % maxVal;

    switch (seq) {
    case 0: dled_pixel_set(&pixel, maxVal,       idx,          0           ); break;
    case 1: dled_pixel_set(&pixel, maxVal - idx, maxVal,       0           ); break;
    case 2: dled_pixel_set(&pixel, 0,            maxVal,       idx         ); break;
    case 3: dled_pixel_set(&pixel, 0,            maxVal - idx, maxVal      ); break;
    case 4: dled_pixel_set(&pixel, idx,          0,            maxVal      ); break;
    case 5: dled_pixel_set(&pixel, maxVal,       0,            maxVal - idx); break;
    }

    return pixel;
}

void dled_pixel_rainbow_step(pixel_t *pixels, uint16_t length, uint8_t max_cc_val, uint16_t step)
{
    if (pixels == NULL) return;
    if (length == 0)    return;

    for (uint16_t idx = 0; idx < length; idx++) {
        pixels[idx] = dled_pixel_get_color_by_index(max_cc_val, idx + step);
    }
}

void dled_pixel_move_pixel(pixel_t *pixels, uint16_t length, uint8_t max_cc_val, uint16_t step)
{
    pixel_t pixel;
    uint8_t seq;
    uint16_t idx;
    uint8_t maxVal;

    if (pixels == NULL) return;
    if (length == 0)    return;

    maxVal = max_cc_val;

    seq = (step / length) % 6;
    idx =  step % length;

    switch (seq) {
    case 0: dled_pixel_set(&pixel, maxVal, 0, 0); break;
    case 1: dled_pixel_set(&pixel, 0, maxVal, 0); idx = length - idx - 1; break;
    case 2: dled_pixel_set(&pixel, 0, 0, maxVal); break;
    case 3: dled_pixel_set(&pixel, maxVal / 2, maxVal / 2, 0); idx = length - idx - 1; break;
    case 4: dled_pixel_set(&pixel, 0, maxVal / 2, maxVal / 2); break;
    case 5: dled_pixel_set(&pixel, maxVal / 2, 0, maxVal / 2); idx = length - idx - 1; break;
    }

    for (uint16_t i = 0; i < length; i++) {
        if (i == idx) {
            pixels[i] = pixel;
        }
        else {
            pixels[i].r /= 2;
            pixels[i].g /= 2;
            pixels[i].b /= 2;
        }
    }
}

#ifdef __cplusplus
}
#endif
