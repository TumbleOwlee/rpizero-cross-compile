# RPi Zero (armv6) Cross Compilation

This repository contains a working example of cross compilation on a x86_64 host system to the Raspberry Pi Zero (armv6).

## Quickstart

First, clone the repository and initialize all submodules. We are using [Sentry Native](https://github.com/getsentry/sentry-native) as an example since it provides everything any other possible dependency might have or use - it's compiled from source but requires some dependencies besides the standard library (`curl` and `zlib`).

```bash
git clone https://github.com/TumbleOwlee/rpizero-cross-compile.git
git submodule update --init --recursive
```

Next, we have to setup the sysroot and get the cross compiler. Keep in mind that you can **not** use the cross compilers from the official repositories, since they will most likely have dropped support of `armv6` and will be compiled with `--with-arch=armv7-a+fp`. That makes them useless for the older Raspberry Pi Zero. This repository contains a script that will retrieve the compiler from [tttapa/docker-arm-cross-toolchain](https://github.com/tttapa/docker-arm-cross-toolchain/) and will set up the sysroot using a raspbian mirror. Check the script for more details.

Now let's set up the sysroot and get the compilers. Everything will be contained in the `./env` subdirectory. Since we have to use `qemu-arm-static` for the sysroot, we also have to register it to `binfmt_misc`. Thus, you have to run the following commands.

```bash
# Register qemu-arm-static
./exec register

# Install the compiler and set up sysroot
./exec install
# Or alternatively, if you would like to customize some options (see --help)
./exec install --env=./path/to/some/dir --version=bookworm --compiler=12
```

Keep in mind, if you specify a custom path using `--env`, you will also have to change the paths in the `CMakeLists.txt`.

That's all. Finally you just have to add the following lines to your `CMakeLists.txt`.

```cmake
set(CMAKE_SYSROOT "${CMAKE_CURRENT_SOURCE_DIR}/env/chroot/armv6")
set(CMAKE_FIND_ROOT_PATH "${CMAKE_SYSROOT}")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/env/compiler/armv6/x-tools/armv6-rpi-linux-gnueabihf/armv6-rpi-linux-gnueabihf.toolchain.cmake")
```

If you would like to unregister the `qemu-arm-static`, just execute `./exec unregister`.

In case you apply this setup to your own project with other or additional dependencies, you will have to install them in your sysroot. You can run `apt-get install` in your sysroot, using the following command.

```bash
sudo chroot ./env/chroot/armv6 /use/bin/apt-get install <packages>
```
