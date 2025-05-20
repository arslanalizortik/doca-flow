#include <doca_flow.h>
#include <doca_dpa.h>
#include <doca_dpa_dev.h>
#include <doca_log.h>
#include <iostream>
#include <cstring>

int main() {
    doca_log_init("doca_http_parser");
    doca_log_set_level(DOCA_LOG_LEVEL_INFO);

    // Initialize DOCA Flow
    if (doca_flow_init(nullptr) != DOCA_SUCCESS) {
        std::cerr << "Failed to initialize DOCA Flow\n";
        return -1;
    }

    // Initialize DPA
    doca_dpa_t dpa;
    if (doca_dpa_create(nullptr, &dpa) != DOCA_SUCCESS) {
        std::cerr << "Failed to create DPA instance\n";
        return -1;
    }

    // Load DPA program
    if (doca_dpa_load(dpa, "dpa/libhttp_parser_dpa.a") != DOCA_SUCCESS) {
        std::cerr << "Failed to load DPA program\n";
        return -1;
    }

    std::cout << "DOCA Flow + DPA setup ready. Traffic will be offloaded to DPA for HTTP header parsing.\n";

    // Add DOCA Flow rule here to steer TCP port 80 traffic to DPA
    // (Requires DOCA Flow pipe + action + port setup)

    doca_dpa_destroy(dpa);
    doca_flow_destroy();
    return 0;
}
