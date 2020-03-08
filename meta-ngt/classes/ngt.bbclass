DESCRIPTION = "A base for HBK images"
LICENSE = "MIT"

IMAGE_FEATURES += "\
    package-management \
    ssh-server-openssh \
    tools-profile \
"

inherit core-image

CORE_IMAGE_EXTRA_INSTALL += "\
"

## SDK
TOOLCHAIN_TARGET_TASK += ""
TOOLCHAIN_TARGET_TASK += "libstdc++-staticdev"