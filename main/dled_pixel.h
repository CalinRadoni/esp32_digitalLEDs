#ifndef MAIN_DLED_PIXEL_H_
#define MAIN_DLED_PIXEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Structure to be used as a pixel.
 *
 */
typedef struct {
	uint8_t r; /*!< Red color component */
    uint8_t g; /*!< Green color component */
    uint8_t b; /*!< Blue color component */
} pixel_t;

/**
 * @brief Set the pixel_t from RGB.
 * @param[in,out] pixel   Pointer to the pixel_t object to be changed.
 * @param[in]     r, g, b The RGB color components.
 */
void dled_pixel_set(pixel_t* pixel, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Set the pixel_t to off (all zero).
 * @param[in,out] pixel Pointer to the pixel_t object to be changed.
 */
void dled_pixel_off(pixel_t* pixel);

/**
 * @brief Get a color from a simple rainbow palette.
 *
 * Returns a pixel with color identified by the index parameter.
 * The color palette is a simple rainbow made from r-g, g-b and b-r combinations
 * with a number of (6 * max_cc_val) colors.
 *
 * @param[in] max_cc_val The maximum value allowed for a color component.
 *                       The size of the color palette depends of this parameter.
 * @param[in] index      Index of the requested color from palette. The value used
 *                       is index modulo size of the color palette.
 * @return The pixel.
 */
pixel_t dled_pixel_get_color_by_index(uint8_t max_cc_val, uint16_t index);

/**
 * @brief Set a rainbow style sequence
 *
 * Creates a rainbow slice. Internally this function calls dled_pixel_get_color_by_index.
 *
 * @param[in,out] pixels     The pixels to be set.
 * @param[in]     length     Number of pixels.
 * @param[in]     max_cc_val The maximum value allowed for a color component.
 *                           The size of the color palette depends of this parameter.
 * @param[in]     step       Index of rainbow seqence.
 *
 * @code{c}
 * pixel_t *pixels;
 * ... // create the pixels
 * uint16_t step = 0;
 * while (true) {
 *     dled_pixel_rainbow_step(pixels, number_of_pixels, max_cc_val, step++);
 *     ... // send the pixels to LEDs
 *     delay_ms(50); // wait a little between sequences
 * }
 * @endcode
 */
void dled_pixel_rainbow_step(pixel_t *pixels, uint16_t length, uint8_t max_cc_val, uint16_t step);

/**
 * @brief Moves a pixel back and forth
 *
 * Moves a pixel back and forth changing its color through red, green and blue.
 * There are (6 * length) steps.
 *
 * @param[in,out] pixels     The pixels to be set.
 * @param[in]     length     Number of pixels.
 * @param[in]     max_cc_val The maximum value allowed for a color component.
 * @param[in]     step       The step of the moving sequence.
 *
 * @code{c}
 * pixel_t *pixels;
 * ... // create the pixels
 * uint16_t step = 0;
 * while (true) {
 *     dled_pixel_move_pixel(pixels, number_of_pixels, max_cc_val, step++);
 *     ... // send the pixels to LEDs
 *     delay_ms(50); // wait a little between sequences
 * }
 * @endcode
 */
void dled_pixel_move_pixel(pixel_t *pixels, uint16_t length, uint8_t max_cc_val, uint16_t step);

#ifdef __cplusplus
}
#endif

#endif
