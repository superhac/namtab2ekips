################################################################################
# fake_ocotp Buildroot package
################################################################################

FAKE_OCOTP_VERSION = 1.0
FAKE_OCOTP_SITE = package/fake_ocotp
FAKE_OCOTP_SITE_METHOD = local
FAKE_OCOTP_LICENSE = GPL-2.0+
FAKE_OCOTP_LICENSE_FILES = fake_ocotp_sysfs.c

# Build using the module's Makefile
define FAKE_OCOTP_BUILD_CMDS
    $(MAKE) -C $(LINUX_DIR) M=$(@D) ARCH=$(BR2_ARCH) CROSS_COMPILE=$(TARGET_CROSS)
endef

# Install .ko into target /lib/modules
define FAKE_OCOTP_INSTALL_TARGET_CMDS
    mkdir -p $(TARGET_DIR)/lib/modules
    cp $(@D)/fake_ocotp_sysfs.ko $(TARGET_DIR)/lib/modules/
    mkdir -p $(TARGET_DIR)/etc/init.d
    cp $(@D)/fake_ocotp.init $(TARGET_DIR)/etc/init.d/S99fake_ocotp
endef

$(eval $(generic-package))
