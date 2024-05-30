# RPi Zero Cross Compilation

This repository contains a working example of cross compilation on a x86_64 host system to the Raspberry Pi Zero (armv6).

## Quickstart

First, clone the repository and initialize all submodules. We are using [Sentry Native](https://github.com/getsentry/sentry-native) as an example.

```bash
git clone https://github.com/TumbleOwlee/rpizero-cross-compile.git
git submodule update --init --recursive
```

Next, we have to setup the sysroot and get the cross compiler. Keep in mind that you can **not** use the cross compilers from the official repositories, since they will most likely have dropped support of `armv6` and will be compiled with `--with-arch=armv7-a+fp`. That makes them useless for the older Raspberry Pi Zero. This repository contains a script that will retrieve the compiler from [tttapa/docker-arm-cross-toolchain](https://github.com/tttapa/docker-arm-cross-toolchain/) and will set up the sysroot using a raspbian mirror. Check the script for more details.

Now let's set up the sysroot and get the compilers. Everything will be contained in the `./env` subdirectory.

```bash
./init
```

That's all. Finally you just have to add the following lines to your `CMakeLists.txt`.

```cmake
set(CMAKE_SYSROOT "${CMAKE_CURRENT_SOURCE_DIR}/env/chroot/armv6")
set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/env/compiler/armv6/x-tools/armv6-rpi-linux-gnueabihf/armv6-rpi-linux-gnueabihf.toolchain.cmake")
```
