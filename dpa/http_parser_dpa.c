#include <doca_dpa_dev.h>
#include <doca_dpa_dev_log.h>

__dpa_global__ void parse_http_header(void *arg)
{
    char *pkt_data = (char *)arg;
    int i = 0;
    char line[256];
    int li = 0;

    while (i < 2048) {
        if (pkt_data[i] == '\r' && pkt_data[i+1] == '\n') {
            line[li] = '\0';
            doca_dpa_dev_log_info("Header: %s", line);
            if (line[0] == '\0')
                break;
            li = 0;
            i += 2;
        } else {
            if (li < sizeof(line) - 1)
                line[li++] = pkt_data[i++];
            else
                i++;
        }
    }
}
