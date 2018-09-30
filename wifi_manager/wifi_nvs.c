#include <string.h>
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "wifi_nvs.h"

static const char wifi_manager_nvs_namespace[] = "espwifimgr";
static const char TAG[] = "WIFIMGRSET";

esp_err_t wifi_manager_clear_sta_config() {
	nvs_handle handle;
	esp_err_t esp_err;
	ESP_LOGD(TAG, "wifi_manager: clearing sta_config");

	esp_err = nvs_open(wifi_manager_nvs_namespace, NVS_READWRITE, &handle);
	if (esp_err != ESP_OK) return esp_err;

	esp_err = nvs_erase_all(handle);
	if (esp_err != ESP_OK) return esp_err;

	esp_err = nvs_commit(handle);
	if (esp_err != ESP_OK) return esp_err;

	nvs_close(handle);

	return ESP_OK;
}

esp_err_t wifi_manager_save_sta_config(wifi_config_t* config) {

	nvs_handle handle;
	esp_err_t esp_err;

	ESP_LOGD(TAG, "wifi_manager: About to save config to flash");

	if(config){

		esp_err = nvs_open(wifi_manager_nvs_namespace, NVS_READWRITE, &handle);
		if (esp_err != ESP_OK) return esp_err;

		esp_err = nvs_set_blob(handle, "ssid", config->sta.ssid, 32);
		if (esp_err != ESP_OK) return esp_err;

		esp_err = nvs_set_blob(handle, "password", config->sta.password, 64);
		if (esp_err != ESP_OK) return esp_err;

		esp_err = nvs_commit(handle);
		if (esp_err != ESP_OK) return esp_err;

		nvs_close(handle);

		ESP_LOGD(TAG, "ssid:%s password:%s", config->sta.ssid, config->sta.password);


	}

	return ESP_OK;
}

bool wifi_manager_load_sta_config(wifi_config_t* config) {
	nvs_handle handle;
	esp_err_t esp_err;

	if (nvs_open(wifi_manager_nvs_namespace, NVS_READONLY, &handle) != ESP_OK){
        return false;
    }

    /* allocate buffer */
    size_t sz;
    uint8_t *buff = malloc(sizeof(uint8_t) * 128);
    memset(buff, 0x00, sizeof(sz));

    /* ssid */
    sz = sizeof(config->sta.ssid);
    esp_err = nvs_get_blob(handle, "ssid", buff, &sz);
    if(esp_err != ESP_OK){
        free(buff);
        return false;
    }
    memcpy(config->sta.ssid, buff, sz);

    /* password */
    sz = sizeof(config->sta.password);
    esp_err = nvs_get_blob(handle, "password", buff, &sz);
    if(esp_err != ESP_OK){
        free(buff);
        return false;
    }
    memcpy(config->sta.password, buff, sz);

    free(buff);
    nvs_close(handle);

    return true;
}
