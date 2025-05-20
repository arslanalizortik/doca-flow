#include <doca_log.h>
#include <doca_dpa.h>
#include <doca_dpa_dev.h>

#include <iostream>
#include <cstring>

int main()
{
    doca_log_init("doca_http_parser");
    doca_log_set_level(DOCA_LOG_LEVEL_INFO);

    doca_dpa_t *dpa = nullptr;
    if (doca_dpa_create(nullptr, &dpa) != DOCA_SUCCESS) {
        std::cerr << "Failed to create DPA instance\n";
        return 1;
    }

    if (doca_dpa_load(dpa, "libhttp_parser_dpa.a") != DOCA_SUCCESS) {
        std::cerr << "Failed to load DPA program\n";
        return 1;
    }

    const char *http_req = "GET /index.html HTTP/1.1\r\nHost: example.com\r\nUser-Agent: curl/7.68.0\r\n\r\n";
    size_t data_len = strlen(http_req);

    void *dpa_buf = nullptr;
    if (doca_dpa_malloc(dpa, data_len, &dpa_buf) != DOCA_SUCCESS) {
        std::cerr << "Failed to allocate DPA memory\n";
        return 1;
    }

    memcpy(dpa_buf, http_req, data_len);

    if (doca_dpa_launch(dpa, "parse_http_header", dpa_buf) != DOCA_SUCCESS) {
        std::cerr << "Failed to launch DPA function\n";
        return 1;
    }

    doca_dpa_free(dpa_buf);
    doca_dpa_destroy(dpa);
    doca_log_destroy();

    return 0;
}
