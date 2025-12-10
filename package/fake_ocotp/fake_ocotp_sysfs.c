#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fake OCOTP");
MODULE_DESCRIPTION("Fake i.MX6 OCOTP sysfs for QEMU testing");

static unsigned int cfg0 = 0x12345678;  // default test value
static unsigned int cfg1 = 0x87654321;

static struct kobject *fsl_kobj;

// Show/Store functions for sysfs
static ssize_t cfg0_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "0x%08x\n", cfg0);
}

static ssize_t cfg0_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (sscanf(buf, "%x", &cfg0) == 1)
        return count;
    return -EINVAL;
}

static ssize_t cfg1_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "0x%08x\n", cfg1);
}

static ssize_t cfg1_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (sscanf(buf, "%x", &cfg1) == 1)
        return count;
    return -EINVAL;
}

// Sysfs attributes
static struct kobj_attribute cfg0_attr = __ATTR(HW_OCOTP_CFG0, 0664, cfg0_show, cfg0_store);
static struct kobj_attribute cfg1_attr = __ATTR(HW_OCOTP_CFG1, 0664, cfg1_show, cfg1_store);

static struct attribute *attrs[] = {
    &cfg0_attr.attr,
    &cfg1_attr.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .attrs = attrs,
};

static int __init fake_ocotp_init(void)
{
    int ret;

    // Create top-level /sys/fsl_otp
    fsl_kobj = kobject_create_and_add("fsl_otp", NULL);
    if (!fsl_kobj)
        return -ENOMEM;

    ret = sysfs_create_group(fsl_kobj, &attr_group);
    if (ret)
        kobject_put(fsl_kobj);

    pr_info("fake_ocotp: initialized\n");
    return ret;
}

static void __exit fake_ocotp_exit(void)
{
    kobject_put(fsl_kobj);
    pr_info("fake_ocotp: exited\n");
}

module_init(fake_ocotp_init);
module_exit(fake_ocotp_exit);

