# doca-flow

- DOCA Flow to match and steer HTTP packets (TCP port 80) to the DPA.
- DOCA DPA to parse HTTP headers at the hardware level on the BlueField DPU.

- Matches HTTP traffic using DOCA Flow (based on TCP port 80).
- Offloads payload to a custom DOCA DPA program on the DPU.
- DPA program parses and logs HTTP request headers.

## Project Structure 

```
doca_http_parser/
├── dpa/
│   ├── http_parser_dpa.c
│   └── meson.build
├── host/
│   ├── host_main.cpp
│   └── meson.build
├── meson.build

```

## Build and Run
- Step1: Build DPA Code

```
cd dpa
source /opt/mellanox/doca/setup_env.sh
dpacc --hostcc gcc --mcpu=dpu -o libhttp_parser_dpa.a http_parser_dpa.c
```

- Step2: Build Host With Meson
```
cd ..
meson setup build --prefix=/usr
meson compile -C build

```

- Step3: Run the App
```
cd build
sudo ./doca_http_parser

```