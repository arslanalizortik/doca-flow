#include <doca_dpa_dev.h>
#include <doca_dpa_dev_buf.h>
#include <doca_dpa_dev_sync_event.h>
#include <doca_dpa_dev_log.h>
#include <string.h>

#define MAX_HEADER_SIZE 1024

__dpa_global__ void parse_http_headers(void *args)
{
    char *packet_data = (char *)args;
    char header_line[MAX_HEADER_SIZE];
    int i = 0, j = 0;

    // Parse lines until double CRLF (end of HTTP headers)
    while (i < MAX_HEADER_SIZE &&
           !(packet_data[i] == '\r' && packet_data[i+1] == '\n' &&
             packet_data[i+2] == '\r' && packet_data[i+3] == '\n')) {
        if (packet_data[i] == '\r' && packet_data[i+1] == '\n') {
            header_line[j] = '\0';
            doca_dpa_dev_log_info("Header: %s", header_line);
            j = 0;
            i += 2;
            continue;
        }
        header_line[j++] = packet_data[i++];
    }

    doca_dpa_dev_log_info("End of Headers");
}
