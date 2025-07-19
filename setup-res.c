
/*
 * if the mask = 0xff, then all resources are enabled
 *
 * Enable specified resources (I/O and memory regions) for a PCIe device
 * @dev: Target PCIe device
 * @mask: Resource enable bitmask (each bit corresponds to a resource index in 
 * 				   PCI_NUM_RESOURCES)
 *
 * Functionality:
 * 	1. iterates through the device's resource list and checks if the resources
 * 	   specified by the mask can be enabled
 *	2. validates resource validity (allocated,declared, not a ROM or ROM is already
 *					enabled)
 *	3. set the I/O or memory enable bit in the PCI command register
 *	4. update the PCI configuration space (when the command register changes)
 */
int pci_enable_resources(struct pci_dev *dev, int mask)
{
	u16 cmd, old_cmd;
	int i;
	struct resource *r;

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
		
		/*
		 * get a resource from the resource array.
		 */
		r = &dev->resource[i];

		/*
		 * if the current resource is not memory resource
		 * or I/O resource, skip it directly
		 */
		if (!(r->flags & (IORESOURCE_IO | IORESOURCE_MEM)))
			continue;
		
		/*
		 * if this resource is a ROM resource, and the ROM resource
		 * is not yet enabled, then processed to the next resource
		 */
		if ((i == PCI_ROM_RESOURCE) &&
			(!(r->flags & IORESOURCE_ROM_ENABLE)))
			continue;
		
		/*
		 * check whether the resources have been successfully allocated 
		 * to valid addresses.
		 * 
		 * IORESOURCE_UNSET: indicates that the PCI BAR has not yet been
		 * properly assigned a physical address
		 *
		 * if the resource is in the "unset" state, enabling the device may
		 * lead to accessing an invalid address,triggering a hardware error
		 */
		if (r->flags & IORESOURCE_UNSET) {
			pci_err(dev, "can not enable device: BAR %d %pR not assigned\n",
				i, r);
			return -EINVAL;
		}
		
		/*
		 * verify whether the resource has been registered into the system 
		 * resource tree
		 *   r->parent: points to the parent resource, indicating that this
		 *   BAR has been declared and added to the global resource tree 
		 *   via function such as request_resource()
		 */
		if (!r->parent) {
			pci_err(dev, "can not enable device: BAR %d %pR not claimed\n",
				i, r);
			return -EINVAL;
		}

		/*
		 * set the command register according to the resource type
		 */
		if (r->flags & IORESOURCE_IO)
			cmd |= PCI_COMMAND_IO;		// enable I/O space access
		if (r->flags & IORESOURCE_MEM)
			cmd |= PCI_COMMAND_MEMORY;	// enable memory space access
	}
}
