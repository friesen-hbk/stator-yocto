DESCRIPTION = "A base for NGT images"
LICENSE = "MIT"

IMAGE_FEATURES += "\
    package-management \
    ssh-server-openssh \
    tools-profile \
"

inherit core-image

CORE_IMAGE_EXTRA_INSTALL += "\
   hbm
"
