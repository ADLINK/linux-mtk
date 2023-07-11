#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/kobject.h>

#define SKU_REG 0x10005220

#define SKU_BIT0 0
#define SKU_BIT1 1
#define SKU_BIT2 2
#define SKU_BIT3 3
#define SKU_BIT4 4

#define PCB_REG         0x10005230
#define PCB_BIT0 20
#define PCB_BIT1 21

#define PCB_PUPD_REG    0x11F40030
#define PCB_PUPD_BIT0   9
#define PCB_PUPD_BIT1   8

struct sku_info {
    uint32_t sku_id;
    char* sku_str;
};

struct sku_info skus[] = {
    {0, "LEC-MTK-I1200-2G-64G-CT(000E)"},
    {1, "LEC-MTK-I1200-4G-64G-CT(100E)"},
    {2, "LEC-MTK-I1200-8G-64G-CT(200E)"},
    {3, "LEC-MTK-I1200-2G-64G-BW-CT(300E)"},
    {4, "LEC-MTK-I1200-4G-64G-BW-CT(400E)"},
    {5, "LEC-MTK-I1200-8G-64G-BW-CT(500E)"},
    {6, "LEC-MTK-I1200-4G-64G-BW-ER(600E)"},
    {7, "LEC-MTK-I1200-8G-64G-BW-ER(TBD)"}
};

static struct kobject *kobj_ref;

static ssize_t pcb_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    void __iomem *pcb_reg;
    void __iomem *pcb_pupd_reg;
    uint32_t pcb_id_0, pcb_id_1;
    uint32_t pcb_id;
    uint32_t reg_value;

    pcb_reg = ioremap(PCB_REG, sizeof(uint32_t));
    pcb_pupd_reg = ioremap(PCB_PUPD_REG, sizeof(uint32_t));

    reg_value = ioread32(pcb_pupd_reg);

    reg_value &= ~(1 << PCB_PUPD_BIT0);
    reg_value &= ~(1 << PCB_PUPD_BIT1);

    iowrite32(reg_value, pcb_pupd_reg);

    pcb_id_0 = (ioread32(pcb_reg) >> PCB_BIT0) & 0x1;
    pcb_id_1 = (ioread32(pcb_reg) >> PCB_BIT1) & 0x1;

    pcb_id = (pcb_id_1 << 1) | pcb_id_0;

    iounmap(pcb_reg);
    iounmap(pcb_pupd_reg);

    switch (pcb_id) {
    case 0:
        return sprintf(buf, "PCB A1\n");
    case 1:
        return sprintf(buf, "PCB A2\n");
    case 2:
        return sprintf(buf, "PCB A3\n");
    case 3:
        return sprintf(buf, "PCB A4\n");
    default:
        return sprintf(buf, "Unknown PCB\n");
    }
}

static ssize_t sku_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    void __iomem *sku_reg;
    uint32_t sku_id_0, sku_id_1, sku_id_2, sku_id_3, sku_id_4;
    uint32_t sku_id;
    int i;

    sku_reg = ioremap(SKU_REG, sizeof(uint32_t));

    sku_id_0 = (ioread32(sku_reg) >> SKU_BIT0) & 0x1;
    sku_id_1 = (ioread32(sku_reg) >> SKU_BIT1) & 0x1;
    sku_id_2 = (ioread32(sku_reg) >> SKU_BIT2) & 0x1;
    sku_id_3 = (ioread32(sku_reg) >> SKU_BIT3) & 0x1;
    sku_id_4 = (ioread32(sku_reg) >> SKU_BIT4) & 0x1;

    sku_id = (sku_id_4 << 4) | (sku_id_3 << 3) | (sku_id_2 << 2) | (sku_id_1 << 1) | sku_id_0;

    for (i = 0; i < sizeof(skus)/sizeof(struct sku_info); i++) {
        if (skus[i].sku_id == sku_id) {
            iounmap(sku_reg);
            return sprintf(buf, "%s\n", skus[i].sku_str);
        }
    }

    iounmap(sku_reg);
    return sprintf(buf, "Unknown SKU\n");
}

struct kobj_attribute pcb_attr = __ATTR_RO(pcb);
struct kobj_attribute sku_attr = __ATTR_RO(sku);

static int __init sysinfo_init(void)
{
    kobj_ref = kobject_create_and_add("sysinfo", kernel_kobj);
    if (sysfs_create_file(kobj_ref, &pcb_attr.attr))
    {
        printk(KERN_INFO "Cannot create pcb sysfs file.\n");
    }
    if (sysfs_create_file(kobj_ref, &sku_attr.attr))
    {
        printk(KERN_INFO "Cannot create sku sysfs file.\n");
    }
    return 0;
}

static void __exit sysinfo_exit(void)
{
    kobject_put(kobj_ref);
}

module_init(sysinfo_init);
module_exit(sysinfo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tim Liang");
MODULE_DESCRIPTION("A simple Linux driver for the SKU and PCB info.");
MODULE_VERSION("1.0");

