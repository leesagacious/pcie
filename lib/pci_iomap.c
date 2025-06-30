
void __iomem *pci_iomap_range(struct pci_dev *dev,
			int bar,
			unsigned long offset,
			unsigned long maxlen)
{
	/*
	 * get the physical start address of BAR
	 */
	resource_size_t start = pci_resource_start(dev, bar);
}	
