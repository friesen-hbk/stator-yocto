# Overview

This is the main repository for the HBK NGT BSP.

The BSP provides a toolchain, emulator images, and firmware for NExT cards and frames.

# Getting Started

The BSP is based on Yocto 3.1.2 (Dunfell).

Ubuntu 20.04 is recommended for developer machines. Note Ubuntu 18.04 is no longer supported. For those preferring a
Windows environment, Windows Subsystem for Linux v2 should work too.

The following packages are required:

``` shell
$ sudo apt install gawk wget git-core diffstat unzip texinfo gcc-multilib \
      build-essential chrpath socat cpio python python3 python3-pip \
      python3-pexpect xz-utils debianutils iputils-ping python3-git \
      python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3 xterm \
      libncurses-dev libtinfo5
```

To set up the BSP:

``` shell
$ git clone git@gitlab.hbm.com:next/stator-yocto.git --recurse-submodules -j$(nproc)
$ cd stator-yocto
$ ./bootstrap-yocto
$ MACHINE=ngt-board source setup-environment build-ngt
$ bitbake ubifs-image
$ bitbake hbg-image

```

## devtool issue

There is an issue running devtool on certain recipes, for instance:

``` shell
$ devtool modify linux-ngt

(...skip stack trace...)

Exception: ModuleNotFoundError: No module named '_sysconfigdata'
```

A possible workaround, should you run into this problem on your machine:

``` shell
cd /usr/lib/python3.8
sudo ln -s _sysconfigdata__x86_64-linux-gnu.py _sysconfigdata.py
```
