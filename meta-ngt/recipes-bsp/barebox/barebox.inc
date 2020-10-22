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

SRC_URI += "file://env"
SRC_URI += "file://${BPN}.config.${PV}"

#S = "${WORKDIR}/barebox-${PV}"
#B = "${WORKDIR}/${PN}-${PV}"


EXTRA_OEMAKE = "CROSS_COMPILE=${TARGET_PREFIX}"

do_configure() {

    # echo "---->"
    # echo "Bootloader Config : "
    # echo ${PN}.config.${PV}
    # echo "<---"

    if [ -e ${WORKDIR}/${PN}.config.${PV} ]; then
	cp ${WORKDIR}/${PN}.config.${PV} ${S}/.config
    else
	bbwarn "No defconfig given in barebox"
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
	if [ -e ${B}/barebox.bin ]; then
		install -m 644 -T ${B}/barebox.bin ${DEPLOYDIR}/barebox-image
	fi
}

FILES_${PN} = ""
FILES_${PN}-bareboxenv = "${bindir}/bareboxenv"
FILES_${PN}-bareboxcrc32 = "${bindir}/bareboxcrc32"
FILES_${PN}-kernel-install = "${bindir}/kernel-install"
FILES_${PN}-bareboximd = "${bindir}/bareboximd"

addtask deploy before do_build after do_compile