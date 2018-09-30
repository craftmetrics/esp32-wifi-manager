#include "esp_wifi.h"
#include "esp_wifi_types.h"

esp_err_t wifi_manager_clear_sta_config();
esp_err_t wifi_manager_save_sta_config(wifi_config_t* config);
bool wifi_manager_load_sta_config(wifi_config_t* config);
