#include <stdio.h>
#include <stdlib.h>

#include "pci/pci.h"

int main(int argc, char **argv) {
    struct pci_access *access;
    struct pci_dev *device;

    unsigned int c;

    u16 domain;
    u8 bus, dev, func;

    int i, bar_size;

    if(argc != 5) {
        printf("Wrong number of arguments\n");
        return -1;
    }

    domain = (u16)atoi(argv[1]);
    bus = (u8)atoi(argv[2]);
    dev = (u8)atoi(argv[3]);
    func = (u8)atoi(argv[4]);

    access = pci_alloc();
    pci_init(access);

    pci_scan_bus(access);

    printf("Will get info for device %04x:%02x:%02x.%d\n", domain, bus, dev, func);

    for (device = access->devices; device; device=device->next) {
        if (device->domain == domain && device->bus == bus && device->dev == dev && device->func == func) {
            pci_fill_info(device, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
            c = pci_read_byte(device, PCI_INTERRUPT_PIN);
            printf("%04x:%02x:%02x.%d vendor=%04x device=%04x class=%04x irq=%d (pin %d) base0=%lx\n",
                device->domain, device->bus, device->dev, device->func, device->vendor_id, device->device_id,
                device->device_class, device->irq, c, (long) device->base_addr[0]);
            for (i = 0; i < 6; i++) {
                printf("Region %d has size %d\n", i, (unsigned int)device->size[i]);
            }
        }
    }

    pci_scan_bus(access);

    printf("\n");
    printf("Will get info for device %04x:%02x:%02x.%d\n", domain, bus, dev, func);

    device = pci_get_dev(access, domain, bus, dev, func);

    if(device) {
        /*pci_fill_info(device, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);
        c = pci_read_byte(device, PCI_INTERRUPT_PIN);
        printf("%04x:%02x:%02x.%d vendor=%04x device=%04x class=%04x irq=%d (pin %d) base0=%lx\n",
            device->domain, device->bus, device->dev, device->func, device->vendor_id, device->device_id,
            device->device_class, device->irq, c, (long) device->base_addr[0]);*/
        for(i = 0; i < 6; i++) {
            printf("Region %d has size %d\n", i, (unsigned int)device->size[i]);
        }
    }

    pci_cleanup(access);

    return 0;
}
