inherit externalsrc

LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"
EXTERNALSRC = "${BSPDIR}/sources/webxi/"

PV="${HBK_FIRMWARE_TAG}"
PR="${HBK_FIRMWARE_COUNT}"

DEPENDS = "boost"

inherit cmake

# Specify any options you want to pass to cmake using EXTRA_OECMAKE:
EXTRA_OECMAKE = ""
