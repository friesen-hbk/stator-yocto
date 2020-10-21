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

PACKAGES += "${PN}-bareboxenv ${PN}-bareboxcrc32 ${PN}-kernel-install \
         ${PN}-bareboximd"

SRC_URI = "http://barebox.org/download/barebox-${PV}.tar.bz2 \
           file://0001-ARM-add-fncpy.h-from-linux-v4.6.patch \
           file://0002-firmware-socfpga-set-APPLYCFG-after-loading-bitstrea.patch \
           file://0003-reset-add-of_reset_control_get-to-header.patch \
           file://0004-drivers-add-fpga-bridge-framework.patch \
           file://0005-drivers-fpga-add-socfpga-bridges.patch \
           file://0006-fpga-add-fpga-region-support.patch \
           file://0007-drivers-firmware-socfpga-remove-bridges-shutdown.patch \
           file://0008-firmware-socfpga-change-function-prefixes.patch \
           file://0009-firmware-import-Arria10-fpgamgr-from-linux.patch \
           file://0010-firmware-add-support-for-compressed-images.patch \
           file://0011-ARM-SoCFPGA-Add-new-board-from-HBM.patch \
           file://0012-ARM-configs-add-socfpga-qspi-xload-defconfig.patch \
           file://0013-state-comment-out-condition-which-prevents-the-value.patch \
           file://0014-hbm_soc-remove-offsets-from-device-tree-barebox-stat.patch \
           file://0015-ngtboard-added-config-files.patch \
           "

S = "${WORKDIR}/barebox-${PV}"

COMPATIBLE_MACHINE = "ngt-board"

EXTRA_OEMAKE = "CROSS_COMPILE=${TARGET_PREFIX}"

do_configure() {
	if [ -e ${WORKDIR}/defconfig ]; then
		cp ${WORKDIR}/defconfig ${S}/.config
	else
		bbwarn "No defconfig given"
	fi

	cml1_do_configure
}

do_compile () {
	# If there is an 'env' directory, append its content
	# to the compiled environment
	if [ -d ${WORKDIR}/env/ ]; then \
		mkdir -p ${S}/.yocto-defaultenv
		cp -r ${WORKDIR}/env/* ${S}/.yocto-defaultenv/; \
		grep -q .yocto-defaultenv ${B}/.config || \
	        sed -i -e "s,^\(CONFIG_DEFAULT_ENVIRONMENT_PATH=.*\)\"$,\1 .yocto-defaultenv\"," \
		                ${B}/.config; \

	fi

	# Barebox uses pkg-config only for building native tools
	export PKG_CONFIG_LIBDIR="${STAGING_DIR_NATIVE}${libdir}/pkgconfig:${STAGING_DIR_NATIVE}/usr/share/pkgconfig"
	export PKG_CONFIG_SYSROOT_DIR=
	export PKG_CONFIG_PATH="${STAGING_DIR_NATIVE}"

	export TARGETCFLAGS="${TARGET_LDFLAGS}${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"
	unset LDFLAGS
	unset CFLAGS
	unset CPPFLAGS
	unset CXXFLAGS
	unset MACHINE

	oe_runmake
}

do_install() {
	if grep "CONFIG_BAREBOXENV_TARGET=y" ${B}/.config; then
		install -d ${D}${bindir}
		install -m 0755 ${B}/scripts/bareboxenv-target ${D}${bindir}/bareboxenv
	fi
	if grep "CONFIG_BAREBOXCRC32_TARGET=y" ${B}/.config; then
		install -d ${D}${bindir}
		install -m 0755 ${B}/scripts/bareboxcrc32-target ${D}${bindir}/bareboxcrc32
	fi
	if grep "CONFIG_KERNEL_INSTALL_TARGET=y" ${B}/.config; then
		install -d ${D}${bindir}
		install -m 0755 ${B}/scripts/kernel-install-target ${D}${bindir}/kernel-install
	fi
	if grep "CONFIG_IMD_TARGET=y" ${B}/.config; then
		install -d ${D}${bindir}
		install -m 0755 ${B}/scripts/bareboximd-target ${D}${bindir}/bareboximd
	fi
}

# Suffix that allows to create different barebox images in one BSP
BAREBOX_IMAGE_SUFFIX = ""

do_deploy[cleandirs] = "${DEPLOYDIR}"
do_deploy[vardepsexclude] = "DATETIME"
do_deploy () {
	install -d ${DEPLOYDIR}
	if [ -e ${B}/barebox-flash-image ]; then
		install -m 644 -t ${DEPLOYDIR}/ ${B}/barebox-flash-image
	fi
	if [ -e ${B}/barebox.efi ]; then
		install -m 644 -t ${DEPLOYDIR}/ ${B}/barebox.efi
	fi
	for IMAGE in ${B}/images/*.img; do
		if [ -e ${IMAGE} ]; then
			BAREBOX_IMG_BASENAME=$(basename ${IMAGE} .img)${BAREBOX_IMAGE_SUFFIX}
			install -m 644 -T ${IMAGE} ${DEPLOYDIR}/${BAREBOX_IMG_BASENAME}-${DATETIME}.img
			ln -sf ${BAREBOX_IMG_BASENAME}-${DATETIME}.img ${DEPLOYDIR}/${BAREBOX_IMG_BASENAME}.img
		fi
	done
}

FILES_${PN} = ""
FILES_${PN}-bareboxenv = "${bindir}/bareboxenv"
FILES_${PN}-bareboxcrc32 = "${bindir}/bareboxcrc32"
FILES_${PN}-kernel-install = "${bindir}/kernel-install"
FILES_${PN}-bareboximd = "${bindir}/bareboximd"

addtask deploy before do_build after do_compile
