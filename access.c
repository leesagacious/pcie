/*
 * read a byte from the configuration space of the PCIe device.
 */
int pci_read_config_byte(const struct pci_dev *dev, int where, u8 *val)
{
	if (pci_dev_is_disconnected(dev)) {
		*val = ~0;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	return pci_bus_read_config_byte(dev->bus, dev->devfn, where, val);
}
