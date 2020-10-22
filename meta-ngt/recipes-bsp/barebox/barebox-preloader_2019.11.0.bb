require barebox-common.inc
require preloader.inc

SRC_URI[md5sum] = "45bf108b22de94a73dfe5c024c873486"
SRC_URI[sha256sum] = "607165b96d98fcc114fbd07e4001e7b527739a543e7adbe019854fbd8c78777f"

SRC_URI += "file://0001-ARM-add-fncpy.h-from-linux-v4.6.patch"
SRC_URI += "file://0002-firmware-socfpga-set-APPLYCFG-after-loading-bitstrea.patch"
SRC_URI += "file://0003-reset-add-of_reset_control_get-to-header.patch"
SRC_URI += "file://0004-drivers-add-fpga-bridge-framework.patch"
SRC_URI += "file://0005-drivers-fpga-add-socfpga-bridges.patch"
SRC_URI += "file://0006-fpga-add-fpga-region-support.patch"
SRC_URI += "file://0007-drivers-firmware-socfpga-remove-bridges-shutdown.patch"
SRC_URI += "file://0008-firmware-socfpga-change-function-prefixes.patch"
SRC_URI += "file://0009-firmware-import-Arria10-fpgamgr-from-linux.patch"
SRC_URI += "file://0010-firmware-add-support-for-compressed-images.patch"
SRC_URI += "file://0011-ARM-SoCFPGA-Add-new-board-from-HBM.patch"
SRC_URI += "file://0012-ARM-configs-add-socfpga-qspi-xload-defconfig.patch"
SRC_URI += "file://0013-state-comment-out-condition-which-prevents-the-value.patch"
SRC_URI += "file://0014-hbm_soc-remove-offsets-from-device-tree-barebox-stat.patch"
SRC_URI += "file://remove-redundant-yyloc-global.patch"
