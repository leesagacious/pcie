
/*
 * initialize a device for use with memory space
 *
 * initialize device before it's used by a driver. 
 * ask low-level code to enable memory resource.
 * wake up the device if it was suspended.
 * beware, this function can fail
 *
 * low-level call chain:
 *
 * 1. pci_enable_device_mem
 * 	2. pci_enable_device_flags
 * 		3. do_pci_enable_device
 * 			4. pcibios_enable_device
 * 				5. pci_enable_resource
 * 					->
 * 					6. setup PCI_COMMAND_MEMORY
 * if (bars & IORESOURCE_MEM) {
 * 	cmd |= PCI_COMMAND_MEMORY;
 * 	pci_write_config_word(dev, PCI_COMMAND, cmd);
 * }
 *
 * write the memory bit(bit 1) to the COMMAND register in the 
 * pci configuration space to enable memory space access
 *
 */
int pci_enable_device_mem(struct pci_dev *dev)
{
	/*
	 * IORESOURCE_MEM: only enable memory space resource.
	 */
	return pci_enable_device_flags(dev, IORESOURCE_MEM);
}
