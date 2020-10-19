
inherit kernel
require recipes-kernel/linux/linux-yocto.inc

KBRANCH = "linux-5.4.y"
SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git;protocol=git;nocheckout=1;branch=${KBRANCH} \
           file://defconfig \
		   file://0001-Revert-net-stmmac-platform-Fix-MDIO-init-for-platfor.patch \
		   file://patch-5.4.10-rt5.patch \
           "

LIC_FILES_CHKSUM  = "file://COPYING;md5=bbea815ee2795b2f4230826c0c6b8814"


LINUX_VERSION ?= "5.4.10"
LINUX_VERSION_EXTENSION_append = "-ngt"

# Modify SRCREV to a different commit hash in a copy of this recipe to
# build a different release of the Linux kernel.
# tag: v5.4.10 7622136b11e0c6738be243b229da6ee9395b10a9

SRCREV = "7622136b11e0c6738be243b229da6ee9395b10a9"

#PV_ngt-board = "${LINUX_VERSION}+git${SRCREV}"
#PV_atlas-board = "${LINUX_VERSION}+git${SRCREV}"
PV = "5.4.10"

COMPATIBLE_MACHINE_atlas-board = "atlas-board"
COMPATIBLE_MACHINE_ngt-board = "ngt-board"
