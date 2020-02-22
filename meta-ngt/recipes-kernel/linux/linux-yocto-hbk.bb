require recipes-kernel/linux/linux-yocto.inc

KBRANCH_ngt ?= "v5.4/standard/base"
KBRANCH_atlas ?= "v5.4/standard/base"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH};"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
PV = "5.4.15"
PR = "r0"

SRCREV_machine_ngt ?= "1fc888264c16696efac2751cfb470c8bd773d9e8"
SRCREV_machine_atlas ?= "1fc888264c16696efac2751cfb470c8bd773d9e8"

KMACHINE_ngt ?= "socfpga"
KMACHINE_atlas ?= "socfpga"

COMPATIBLE_MACHINE_ngt = "socfpga"
COMPATIBLE_MACHINE_atlas = "socfpga"

LINUX_VERSION_ngt = "${PV}"
LINUX_VERSION_atlas = "${PV}"

SRC_URI += "file://defconfig"
