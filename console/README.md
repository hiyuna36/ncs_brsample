# Console出力

## Build Configuration

### uart

| 項目                                           | 値                               |
| ---------------------------------------------- | -------------------------------- |
| SDK                                            | nRF Connect SDK v3.2.0           |
| Toolchain                                      | nRF Connect SDK Toolchain v3.2.0 |
| Board target                                   | nrf54l15dk/nrf54l15/cpuapp       |
| Base configuration files (Kconfig fragmenets)  | prj.conf                         |
| Extra Kconfig fragments                        | console_uart.conf                |
| Base Devicetree overlays                       |                                  |
| Extra Devicetree overlays                      |                                  |
| Snippets                                       |                                  |
| Optimization level (size, speed, or debugging) | Optimize for debugging(-Og)      |
| Extra CMake arguments                          |                                  |
| Build directory name                           | build\uart                       |
| System build (sysbuild)                        | Build system default             |

### rtt

| 項目                                           | 値                               |
| ---------------------------------------------- | -------------------------------- |
| SDK                                            | nRF Connect SDK v3.2.0           |
| Toolchain                                      | nRF Connect SDK Toolchain v3.2.0 |
| Board target                                   | nrf54l15dk/nrf54l15/cpuapp       |
| Base configuration files (Kconfig fragmenets)  | prj.conf                         |
| Extra Kconfig fragments                        | console_rtt.conf                 |
| Base Devicetree overlays                       |                                  |
| Extra Devicetree overlays                      |                                  |
| Snippets                                       |                                  |
| Optimization level (size, speed, or debugging) | Optimize for debugging(-Og)      |
| Extra CMake arguments                          |                                  |
| Build directory name                           | build\uart                       |
| System build (sysbuild)                        | Build system default             |

### console無効

| 項目                                           | 値                               |
| ---------------------------------------------- | -------------------------------- |
| SDK                                            | nRF Connect SDK v3.2.0           |
| Toolchain                                      | nRF Connect SDK Toolchain v3.2.0 |
| Board target                                   | nrf54l15dk/nrf54l15/cpuapp       |
| Base configuration files (Kconfig fragmenets)  | prj.conf                         |
| Extra Kconfig fragments                        | console_disable.conf             |
| Base Devicetree overlays                       |                                  |
| Extra Devicetree overlays                      |                                  |
| Snippets                                       |                                  |
| Optimization level (size, speed, or debugging) | Optimize for debugging(-Og)      |
| Extra CMake arguments                          |                                  |
| Build directory name                           | build\nocon                      |
| System build (sysbuild)                        | Build system default             |
