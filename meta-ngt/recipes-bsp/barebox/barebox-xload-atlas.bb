require barebox-xload.inc

SRC_URI[md5sum] = "a755165468163793d260e329ea585fc2"
SRC_URI[sha256sum] = "31823ba18b5630b902b14a55e4d45ea8a632967a3cc997f79970935372fa6a9f"

SRC_URI += "file://barebox-xload.config.${PV}"
SRC_URI += "file://0001-atlas_fix_dts_name.patch"
LIC_FILES_CHKSUM = "file://COPYING;md5=057bf9e50e1ca857d0eb97bfe4ba8e5d"

PV="2017.08.0"

COMPATIBLE_MACHINE_atlas-board = "atlas-board"

