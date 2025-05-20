#include <doca_dpa.h>
#include <doca_dpa_dev.h>
#include <doca_log.h>
#include <cstring>
#include <iostream>

int main()
{
    doca_log_init("doca_http_parser");
    doca_log_set_level(DOCA_LOG_LEVEL_INFO);

    doca_dpa_t *dpa = nullptr;
    if (doca_dpa_create(nullptr, &dpa) != DOCA_SUCCESS) {
        std::cerr << "DPA init failed\n";
        return 1;
    }

    if (doca_dpa_load(dpa, "libhttp_parser_dpa.a") != DOCA_SUCCESS) {
        std::cerr << "Failed to load DPA code\n";
        return 1;
    }

    const char *http_req =
        "GET /index.html HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "User-Agent: test-agent\r\n"
        "Accept: */*\r\n\r\n";

    void *dpa_buf = nullptr;
    size_t len = strlen(http_req);
    if (doca_dpa_malloc(dpa, len, &dpa_buf) != DOCA_SUCCESS) {
        std::cerr << "DPA malloc failed\n";
        return 1;
    }

    memcpy(dpa_buf, http_req, len);

    if (doca_dpa_launch(dpa, "parse_http_header", dpa_buf) != DOCA_SUCCESS) {
        std::cerr << "Failed to launch\n";
        return 1;
    }

    doca_dpa_free(dpa_buf);
    doca_dpa_destroy(dpa);
    doca_log_destroy();

    return 0;
}
