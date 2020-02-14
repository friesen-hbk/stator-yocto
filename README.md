# Overview

This is the Yocto manifest and configuration file to create a build environment for the HBK NExT BSP.

## Getting Started

You will need git-lfs to pull code from HBK Gitlab. To install git-lfs:

    $ sudo apt install git-lfs

To set up the Yocto BSP, run:

	$ git archive --remote=ssh://git@gitlab.hbm.com/next/firmware/next-manifest.git HEAD bootstrap-yocto | tar -x

	$ ./bootstrap-yocto

This will download all required files and prepare the Yocto build environment.

## Building Code

To start building, open a new shell and `cd` to the 'next' folder, e.g.:

	$ cd next

Then, configure the environment and start building.

This step depends on the target you are building for, here's a few examples.

To build card firmware for QEMU:

	MACHINE=qemu . base/setup-environment build-card-qemu
	bitbake hbk-card

To build card firmware for the ESPRESSObin eval board:

	$ MACHINE=hbk-card-g1 . base/setup-environment build-card-eval
	$ bitbake hbk-card

To build frame firmware for QEMU:

	MACHINE=qemu . base/setup-environment build-frame-qemu
	bitbake hbk-frame

To build frame firmware for the MACCHIATObin eval board:

	$ MACHINE=hbk-frame-g1 . base/setup-environment build-frame-eval
	$ bitbake hbk-frame

Sourcing the `setup-environment` script sets up the environment for the specified `MACHINE`.

The build/output folder is specified on the command line as a parameter to `setup-environment`. It is possible to use a common `build` folder for all targets, but things might break if different configurations use different `MACHINE_FEATURES` or `DISTRO_FEATURES`.

The build is started by invoking `bitbake` with the name of the recipe that builds the target firmware.

## Modifying Code

Use [devtool](https://www.yoctoproject.org/software-item/devtool/) for anything related to recipes, including adding, modifying and upgrading recipes.

To modify the kernel, add patches to the `internal/meta-hbk` layer (`devtool` is your friend). Use kernel modules for device drivers.

Likewise, to modify the bootloader use patches in `internal/meta-hbk`.

## user.conf

Bitbake will look for a `user.conf` file in the top BSP folder (it's included from `local.conf`).

If you would like to customise the build, simply create this file and adjust things as desired.

For instance, to use 6 CPU cores for building instead if the default 4, `user.conf` might contain:

	BB_NUMBER_THREADS = "6"
	BB_NUMBER_PARSE_THREADS = "6"

A local sstate_cache folder can speed up builds significantly. To set up sstate cache in next/build-sstate-cache, use:

	SSTATE_DIR = "${BSPDIR}/build-sstate-cache"
	SSTATE_MIRRORS_prepend = "file://.* file://${BSPDIR}/build-sstate-cache/PATH "

The `SSTATE_DIR` variable tells Bitbake to store newly generated sstate information in the `build-sstate-cache` folder, while the `SSTATE_MIRRORS`variable instructs Bitbake to look here first for already generated sstate.

## Implementation Notes

We use the latest long-term release [linux-yocto kernel](https://git.yoctoproject.org/cgit/cgit.cgi/linux-yocto/) provided by the Yocto project. Yocto kernels are stable and based on the mainline Linux kernel releases from [www.kernel.org](https://www.kernel.org).
