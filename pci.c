
/*
 * initialize a device for use with memory space
 *
 * initialize device before it's used by a driver. 
 * ask low-level code to enable memory resource.
 * wake up the device if it was suspended.
 * beware, this function can fail
 */
int pci_enable_device_mem(struct pci_dev *dev)
{
	return pci_enable_device_flags(dev, IORESOURCE_MEM);
}
