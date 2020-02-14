DESCRIPTION = "A base for HBK images"
LICENSE = "MIT"

IMAGE_FEATURES += "\
    package-management \
    ssh-server-openssh \
    tools-profile \
"

inherit core-image

CORE_IMAGE_EXTRA_INSTALL += "\
    python \
    file \
    cryptsetup \
    e2fsprogs \
    pciutils \
"
