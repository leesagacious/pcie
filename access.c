/*
 * read a byte from the configuration space of the PCIe device.
<<<<<<< HEAD
 *
 * the PCIe specification explicitly states that only the RC has
 * the permission to originate configuration requests. 
 * this means that other devices within the PCIe system are not 
 * allowed to access or configuration the configuration space of 
 * other devices
 *
 * Additionally, the routing method for configuration requests must
 * be based on BDF
=======
>>>>>>> 93b949a9b2d85e8f205d269ea93b9f6250193293
 */
int pci_read_config_byte(const struct pci_dev *dev, int where, u8 *val)
{
	if (pci_dev_is_disconnected(dev)) {
		*val = ~0;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	return pci_bus_read_config_byte(dev->bus, dev->devfn, where, val);
}
