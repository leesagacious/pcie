
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


static int do_pci_enable_device(struct pci_dev *dev, int bars)
{
	u16 cmd;
	u8 pin;

	/*
	 * read the device's PCI_INTERRUPT_PIN register (offset 0x3D)
	 *
	 * this register indicates the interrupt pin used by the device
	 * 0x0 : no interrupt pin
	 * 0x1: INTA#
	 * 0x2: INTB#
	 * 0x3: INTC#
	 * 0x4: INTD#
	 *
	 * for PCIe devices, this value represents a virtual pin (emulated 
	 * via message-based interrupts)
	 */
	pci_read_config_byte(dev, PCI_INTERRUPT_PIN, &pin);
	if (pin) {
		pci_read_config_word(dev, PCI_COMMAND, &cmd);
		if (cmd & PCI_COMMAND_INTX_DISABLE)
			pci_write_config_word(dev, PCI_COMMAND,
					cmd & ~PCI_COMMAND_INTX_DISABLE);
	}

	return 0;
}























