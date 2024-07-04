idf_component_register(
	SRC_DIRS "."
	INCLUDE_DIRS "include"
	REQUIRES nvs_flash mdns esp32-dns-server
	EMBED_FILES assets/style.css assets/jquery.gz assets/code.js assets/index.html
)