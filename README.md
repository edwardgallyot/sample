# SAMPLER

A real-time audio sampler for Raspberry Pi Zero with ALSA audio support.

## Building

### Prerequisites
- CMake 3.10+
- ARM cross-compilation toolchain
    - Compiled with [crosstools-ng](https://crosstool-ng.github.io/)
    - Used [this guide](https://www.programmersought.com/article/565710029574/)
- Raspberry Pi Zero with SSH access

### Build for Raspberry Pi Zero
```bash
mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake ..
make
```
## Usage

```bash
# On Raspberry Pi Zero
./SAMPLER
```
