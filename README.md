# doca-flow

- DOCA Flow to match and steer HTTP packets (TCP port 80) to the DPA.
- DOCA DPA to parse HTTP headers at the hardware level on the BlueField DPU.

- Matches HTTP traffic using DOCA Flow (based on TCP port 80).
- Offloads payload to a custom DOCA DPA program on the DPU.
- DPA program parses and logs HTTP request headers.

## Project Structure 

```
doca_http_parser/
├── meson.build
├── meson_options.txt
├── dpa/
│   ├── http_parser_dpa.c
│   └── meson.build
└── host/
    ├── main.cpp
    └── meson.build
```
