SUMMARY = "Barebox - a bootloader that inherits the best of U-Boot and the Linux kernel"
HOMEPAGE = "http://www.barebox.org/"
SECTION = "bootloaders"
PROVIDES = "virtual/bootloader"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=f5125d13e000b9ca1f0d3364286c4192"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit kernel-arch deploy
inherit cml1

DEPENDS = "libusb1-native lzop-native bison-native flex-native"


SRC_URI = "http://barebox.org/download/barebox-${PV}.tar.bz2"

COMPATIBLE_MACHINE = "ngt-board"

S = "${WORKDIR}/barebox-${PV}"
B = "${WORKDIR}/${PN}-${PV}"
