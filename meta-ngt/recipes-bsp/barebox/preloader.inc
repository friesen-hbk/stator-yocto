SUMMARY = "Barebox - a bootloader that inherits the best of U-Boot and the Linux kernel"
HOMEPAGE = "http://www.barebox.org/"
SECTION = "bootloaders"
PROVIDES = "virtual/preloader"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=f5125d13e000b9ca1f0d3364286c4192"

PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit kernel-arch deploy
inherit cml1

DEPENDS = "libusb1-native lzop-native bison-native flex-native"

SRC_URI += "file://${BPN}.config.${PV}"

EXTRA_OEMAKE = "CROSS_COMPILE=${TARGET_PREFIX}"

S = "${WORKDIR}/barebox-${PV}"
B = "${WORKDIR}/barebox-${PV}"


do_configure() {

    # bbwarn "Bootloader Config : ${WORKDIR}/${PN}.config.${PV}"
    # bbwarn "B: ${B}"
    # bbwarn "S: ${S}"


    if [ -e ${WORKDIR}/${PN}.config.${PV} ]; then
	cp ${WORKDIR}/${PN}.config.${PV} ${S}/.config
    else
	bbwarn "No defconfig given in preloader"
    fi

    cml1_do_configure
}

do_compile () {
#	# If there is an 'env' directory, append its content
#	# to the compiled environment
#	if [ -d ${WORKDIR}/env/ ]; then \
#		mkdir -p ${S}/.yocto-defaultenv
#		cp -r ${WORKDIR}/env/* ${S}/.yocto-defaultenv/; \
#		grep -q .yocto-defaultenv ${B}/.config || \
#	        sed -i -e "s,^\(CONFIG_DEFAULT_ENVIRONMENT_PATH=.*\)\"$,\1 .yocto-defaultenv\"," \
#		                ${B}/.config; \
#
#	fi
#
	# Barebox uses pkg-config only for building native tools
# 	export PKG_CONFIG_LIBDIR="${STAGING_DIR_NATIVE}${libdir}/pkgconfig:${STAGING_DIR_NATIVE}/usr/share/pkgconfig"
# 	export PKG_CONFIG_SYSROOT_DIR=
# 	export PKG_CONFIG_PATH="${STAGING_DIR_NATIVE}"
#
	export TARGETCFLAGS="${TARGET_LDFLAGS}${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}"
	unset LDFLAGS
	unset CFLAGS
	unset CPPFLAGS
	unset CXXFLAGS
	unset MACHINE

	oe_runmake
}

# Suffix that allows to create different barebox images in one BSP
BAREBOX_IMAGE_SUFFIX = ""

do_deploy[cleandirs] = "${DEPLOYDIR}"
do_deploy[vardepsexclude] = "DATETIME"
do_deploy () {

	install -d ${DEPLOYDIR}
	if [ -e ${B}/barebox.bin ]; then
		install -m 644 -T ${B}/barebox.bin ${DEPLOYDIR}/barebox-xload-image
	fi
}

addtask deploy before do_build after do_compile
