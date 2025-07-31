

static void pci_init_capabilities(struct pci_dev *dev)
{
	/*
	 * MSI/MSI-X initialization: set up the interrupt capability structure
	 * and temporarily disable interrupts.
	 */
	pci_msi_setup_pci_dev(dev);

}
