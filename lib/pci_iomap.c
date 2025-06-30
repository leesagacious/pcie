
void __iomem *pci_iomap_range(struct pci_dev *dev,
			int bar,
			unsigned long offset,
			unsigned long maxlen)
{
	/*
	 * get the physical start address of BAR
	 */
	resource_size_t start = pci_resource_start(dev, bar);
	/*
	 * get the total len of BAR
	 */
	resource_size_t len = pci_resource_len(dev, bar);
	/*
	 * get the resource type of BAR
	 */
	resource_size_t flags = pci_resource_flags(dev, bar);

	/*
	 * the physical address stored in the BAR is mapping to
	 * kernel virtual address
	 */	
	if (flags & IORESOURCE_MEM)
		return ioremap(start, len);

	return NULL;
}	
