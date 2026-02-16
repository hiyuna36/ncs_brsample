# Bluetooth - Device Infomation Service

## Build Configuration

| 項目                                           | 値                               |
| ---------------------------------------------- | -------------------------------- |
| SDK                                            | nRF Connect SDK v3.2.0           |
| Toolchain                                      | nRF Connect SDK Toolchain v3.2.0 |
| Board target                                   | nrf54l15dk/nrf54l15/cpuapp       |
| Base configuration files (Kconfig fragmenets)  | prj.conf                         |
| Extra Kconfig fragments                        |                                  |
| Base Devicetree overlays                       |                                  |
| Extra Devicetree overlays                      |                                  |
| Snippets                                       |                                  |
| Optimization level (size, speed, or debugging) | Optimize for debugging(-Og)      |
| Include debug thread infomation                | Checked                          |
| Extra CMake arguments                          |                                  |
| Build directory name                           | build                            |
| System build (sysbuild)                        | Build system default             |

## Thread

| Name       | Priority | 主な関数                           |
| ---------- | -------- | ---------------------------------- |
| MPSL Works | -10      |                                    |
| BT RX WQ   | -8       | connected                          |
| sysworkq   | -1       | disconnected recycled_cb adv_start |
| main       | 0        | main                               |
| BT LW WQ   | 10       |                                    |
| idle       | 15       |                                    |

