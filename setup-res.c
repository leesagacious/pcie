

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

}
