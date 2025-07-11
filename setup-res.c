

int pci_enable_resources(struct pci_dev *dev, int mask)
{
	u16 cmd, old_cmd;
	
	/*
	 * read the command register from the PCIe configuration
	 * space
	 */
	pci_read_config_word(dev, PCI_COMMAND, &cmd);
	old_cmd = cmd;

}
