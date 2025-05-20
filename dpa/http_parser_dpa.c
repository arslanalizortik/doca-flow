#include <doca_dpa_dev.h>
#include <doca_dpa_dev_log.h>
#include <string.h>

__dpa_global__ void parse_http_header(void *args)
{
    char *data = (char *)args;
    int i = 0;
    char line[256];
    int line_i = 0;

    while (i < 2048) {
        if (data[i] == '\r' && data[i+1] == '\n') {
            line[line_i] = '\0';
            doca_dpa_dev_log_info("Header Line: %s", line);
            line_i = 0;
            i += 2;

            if (data[i] == '\r' && data[i+1] == '\n') {
                doca_dpa_dev_log_info("End of Header");
                break;
            }

            continue;
        }

        if (line_i < sizeof(line) - 1)
            line[line_i++] = data[i];
        i++;
    }
}
