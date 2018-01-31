#ifndef MAIN_DLED_STRIP_H_
#define MAIN_DLED_STRIP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "dled_pixel.h"

#include "esp_err.h"

/**
 * @brief The type of digital LEDs.
 *
 */
typedef enum {
    DLED_NULL,    /*!< This is used as NOT set value */
    DLED_WS2812,
    DLED_WS2812B,
    DLED_WS2812D,
    DLED_WS2813,
    DLED_WS2815,
    DLED_WS281x    /*!< This value should work for all WS281* and clones */
} dstrip_type_t;

/**
 * @brief Structure to be used as a LED strip
 *
 */
typedef struct {
	pixel_t* pixels;        /*!< these are the pixels, one for each LED */
	uint16_t length;        /*!< the number of pixels */

	uint8_t* buffer;        /*!< buffer to hold data to be sent to LEDs */
	uint16_t buffer_length; /*!< length, in bytes, of buffer */

	uint8_t max_cc_val;     /*!< maximum value allowed for a color component */

	dstrip_type_t type;          /*!< type of digital LEDs */
	uint8_t bytes_per_led;       /*!< number of bytes per LED */
    uint16_t T0H, T0L, T1H, T1L; /*!< timings of the communication protocol */
    uint32_t TRS;                /*!< reset timing of the communication protocol */
} pixel_strip_t;

/**
 * @brief Initialize a pixel_strip_t structure.
 *
 * @param[in,out] strip The structure to be initialized.
 *
 * @return
 *    - ESP_OK success
 *    - ESP_ERR_INVALID_ARG if the `strip` argument is NULL
 */
esp_err_t dled_strip_init(pixel_strip_t *strip);

/**
 * @brief Creates the buffers and set the members of a pixel_strip_t structure.
 *
 * Creates `pixels` and `buffers` of a pixel_strip_t structure.
 * Based of supplied parameters it sets all of the structure's members.
 *
 * @param[in,out] strip      The structure to work with.
 * @param[in]     strip_type The type of digital LEDs.
 * @param[in]     length     The number of digital LEDs.
 * @param[in]     max_cc_val The maximum value allowed for a color component.
 *
 * @return
 *    - ESP_OK success
 *    - ESP_ERR_INVALID_ARG if the `strip` argument is NULL __OR__ `strip_type` is unknown or DSTRIP_NULL
 *    - ESP_ERR_INVALID_SIZE if length is zero
 *    - ESP_ERR_NO_MEM if failed to allocate memory for `pixels` or `buffer`
 */
esp_err_t dled_strip_create(pixel_strip_t *strip, dstrip_type_t strip_type, uint16_t length, uint8_t max_cc_val);

/**
 * @brief Destroy the buffers of a pixel_strip_t structure.
 *
 * Destroys `pixels` and `buffers` of a pixel_strip_t structure.
 * Calls `dled_strip_init` to initialize the structure.
 *
 * @param[in,out] strip      The structure to work with.
 *
 * @return
 *    - ESP_OK success
 *    - ESP_ERR_INVALID_ARG if the `strip` argument is NULL
 */
esp_err_t dled_strip_destroy(pixel_strip_t *strip);

/**
 * @brief Fill structure's `buffer` from structure's `pixels`
 *
 * Fill structure's `buffer` from structure's `pixels` based of the type of LEDs.
 *
 * @param[in,out] strip      The structure to work with.
 *
 * @return
 *    - ESP_OK success
 *    - ESP_ERR_INVALID_ARG if the `strip` argument is NULL
 */
esp_err_t dled_strip_fill_buffer(pixel_strip_t *strip);

#ifdef __cplusplus
}
#endif

#endif
