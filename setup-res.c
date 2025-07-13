

int pci_enable_resources(struct pci_dev *dev, int mask)
{
	u16 cmd, old_cmd;
	
	/*
	 * read the command register from the PCIe configuration
	 * space
	 *
	 * command:
	 * 	b0	I/O Space Enable启用设备的 I/O 空间访问
	 * 	b1	Memory Space Enable启用设备的内存空间访问
	 * 	b2	Bus Master Enable允许设备作为总线主控发起 DMA 操作
	 */
	pci_read_config_word(dev, PCI_COMMAND, &cmd);
	old_cmd = cmd;
	
	/*
	 * traverse the resource array of PCIe devices
	 *
	 * enum {
	 *	PCI_BASE_ADDRESS_0 = 0,   // bar0
	 *	PCI_BASE_ADDRESS_1,	  // bar1
	 *	PCI_BASE_ADDRESS_2,       // bar2
	 *	PCI_BASE_ADDRESS_3,	  // bar3
	 *	PCI_BASE_ADDRESS_4,       // bar4
	 *	PCI_BASE_ADDRESS_5,	  // bar5
	 *	PCI_ROM_RESOURCE,	  // ROM
	 *	PCI_NUM_RESOURCES	  // 7 
	 * };
	 */
	for (i = 0; i < PCI_NUM_RESOURCES; i++) {
		/*
		 * each bit in the mask directly corresponds to a 
		 * resource index
		 * bit[0] -> BAR0 (index 0)
		 * bit[1] -> BAR1 (index 1)
		 */
		if (!(mask & (1 << i)))
			continue;	
	}
}
