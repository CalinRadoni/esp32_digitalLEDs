#ifdef __cplusplus
extern "C" {
#endif

#include "dled_strip.h"

#include "esp_log.h"

static const char *LOG_TAG  = "dled_strip";

esp_err_t dled_strip_init(pixel_strip_t *strip)
{
	if (strip == NULL) { return ESP_ERR_INVALID_ARG; }

    strip->type = DLED_NULL;
    strip->pixels = NULL;
    strip->length = 0;
    strip->buffer = NULL;
    strip->buffer_length = 0;
    strip->bytes_per_led = 0;
    strip->max_cc_val = 0;
    strip->T0H = 0; strip->T0L = 0;
    strip->T1H = 0; strip->T1L = 0;
    strip->TRS = 0;

    return ESP_OK;
}

void dled_strip_set_timings(pixel_strip_t *strip)
{
    /* Timings are from datasheets. DLED_WS281x timings should be good.
     * See https://cpldcpu.wordpress.com for interesting investigations about timings. */

    switch (strip->type) {
        case DLED_NULL:
            strip->T0H = 0; strip->T0L = 0; strip->T1H = 0; strip->T1L = 0; strip->TRS = 0;
            break;
        case DLED_WS2812:
            strip->T0H = 350; strip->T0L = 800; strip->T1H = 700; strip->T1L = 600; strip->TRS = 50000;
            break;
        case DLED_WS2812B:
        case DLED_WS2813:
        case DLED_WS2815:
            strip->T0H = 300; strip->T0L = 1090; strip->T1H = 1090; strip->T1L = 320; strip->TRS = 280000;
            break;
        case DLED_WS2812D:
            strip->T0H = 400; strip->T0L = 850; strip->T1H = 800; strip->T1L = 450; strip->TRS = 50000;
            break;
        case DLED_WS281x:
            strip->T0H = 400; strip->T0L = 850; strip->T1H = 850; strip->T1L = 400; strip->TRS = 50000;
            break;
    }
}

esp_err_t dled_strip_create(pixel_strip_t *strip, dstrip_type_t strip_type, uint16_t length, uint8_t max_cc_val_in)
{
    uint16_t req_length;

	if (strip == NULL) {
		ESP_LOGE(LOG_TAG, "Argument is NULL");
		return ESP_ERR_INVALID_ARG;
	}
	if (length == 0) {
		ESP_LOGE(LOG_TAG, "Number of pixels is 0");
		return ESP_ERR_INVALID_SIZE;
	}

    strip->type = strip_type;
    switch(strip->type) {
        case DLED_NULL:
            strip->bytes_per_led = 0;
            break;
        case DLED_WS2812:
        case DLED_WS2812B:
        case DLED_WS2812D:
        case DLED_WS2813:
        case DLED_WS2815:
        case DLED_WS281x:
            strip->bytes_per_led = 3;
            break;
        default:
    		ESP_LOGE(LOG_TAG, "Unknown strip type");
            strip->type = DLED_NULL;
            break;
    }

    if(strip->type == DLED_NULL){
        dled_strip_init(strip);
		return ESP_ERR_INVALID_ARG;
    }

    req_length = length * sizeof(pixel_t);
	strip->pixels = (pixel_t*)malloc(req_length);
	if (strip->pixels == NULL) {
		strip->buffer = NULL;
		ESP_LOGE(LOG_TAG, "Failed to allocate memory for pixels");
		return ESP_ERR_NO_MEM;
	}
    else {
        ESP_LOGI(LOG_TAG, "Allocated %d bytes for pixels", req_length);
    }

    req_length = length * strip->bytes_per_led * sizeof(uint8_t);
	strip->buffer = (uint8_t*)malloc(req_length);
	if (strip->buffer == NULL) {
		free(strip->pixels);
        strip->pixels = NULL;
		ESP_LOGE(LOG_TAG, "Failed to allocate memory for buffer");
		return ESP_ERR_NO_MEM;
	}
    else {
        ESP_LOGI(LOG_TAG, "Allocated %d bytes for output buffer", req_length);
    }

    strip->length = length;
    strip->buffer_length = length * strip->bytes_per_led;

    strip->max_cc_val = max_cc_val_in;

    dled_strip_set_timings(strip);

	for (uint16_t i = 0; i < strip->length; i++)
		dled_pixel_off(&strip->pixels[i]);

    return ESP_OK;
}

esp_err_t dled_strip_destroy(pixel_strip_t *strip)
{
	if (strip == NULL) {
		ESP_LOGE(LOG_TAG, "Argument is NULL");
		return ESP_ERR_INVALID_ARG;
	}

    if (strip->pixels != NULL) { free(strip->pixels); }
    if (strip->buffer != NULL) { free(strip->buffer); }

    dled_strip_init(strip);

    ESP_LOGI(LOG_TAG, "Freed allocated memory");

    return ESP_OK;
}

esp_err_t dled_strip_fill_buffer(pixel_strip_t *strip)
{
	if (strip == NULL) {
		ESP_LOGE(LOG_TAG, "Argument is NULL");
		return ESP_ERR_INVALID_ARG;
	}

    /* To not waste CPU cycles I do not check if:
     *    strip->buffer != NULL
     *    strip->pixels != NULL
     *    the sizes are OK
     * because here these "should" be right. */

    /* WS2812, WS2812B and WS2813 are GRB */
	uint16_t didx = 0;
    for(uint16_t i = 0; i < strip->length; i++){
        strip->buffer[didx++] = strip->pixels[i].g;
        strip->buffer[didx++] = strip->pixels[i].r;
        strip->buffer[didx++] = strip->pixels[i].b;
	}

    return ESP_OK;
}

#ifdef __cplusplus
}
#endif
