
static void pci_msi_setup_pci_dev(struct pci_dev *dev)
{
	/*
	 * find the position of the device's MSI capability register
	 * if the device supports MSI,
	 * disable MSI interrupts(set msi control register enable bit to 0)
	 */
	dev->msi_cap = pci_find_capability(dev, PCI_CAP_ID_MSI);
	if (dev->msi_cap)
		pci_msi_set_enable(dev, 0);

	/*
	 * find the position of the device's msi-x capability register
	 * if the device supports msi-x
	 * disable msi-x interrupts: clear enable bit
	 * while preserving other bits.
	 */
	dev->msix_cap = pci_find_capability(dev, PCI_CAP_ID_MSIX);
	if (dev->msix_cap)
		pci_msix_clear_and_set_ctrl(dev, PCI_MSIX_FLAGS_ENABLE, 0);
}

static void pci_init_capabilities(struct pci_dev *dev)
{
	/*
	 * MSI/MSI-X initialization: set up the interrupt capability structure
	 * and temporarily disable interrupts.
	 */
	pci_msi_setup_pci_dev(dev);

}
