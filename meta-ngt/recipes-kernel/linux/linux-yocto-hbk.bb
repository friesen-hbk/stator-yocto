require recipes-kernel/linux/linux-yocto.inc

KBRANCH_armada80xx ?= "v5.4/standard/base"
KBRANCH_armada37xx ?= "v5.4/standard/base"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = "git://git.yoctoproject.org/linux-yocto.git;name=machine;branch=${KBRANCH};"

LIC_FILES_CHKSUM = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"
PV = "5.4.15"
PR = "r0"

SRCREV_machine_armada80xx ?= "1fc888264c16696efac2751cfb470c8bd773d9e8"
SRCREV_machine_armada37xx ?= "1fc888264c16696efac2751cfb470c8bd773d9e8"

KMACHINE_armada80xx ?= "armada80xx"
KMACHINE_armada37xx ?= "armada37xx"

COMPATIBLE_MACHINE_armada80xx = "armada80xx"
COMPATIBLE_MACHINE_armada37xx = "armada37xx"

LINUX_VERSION_armada80xx = "${PV}"
LINUX_VERSION_armada37xx = "${PV}"

SRC_URI += "file://defconfig"