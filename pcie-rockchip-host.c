
static int rockchip_pcie_init_irq_domain(struct rockchip *rockchip)
{
	struct device *dev = rockchip->dev;
	/*
	 * get the first child node of the device (typically corresponding
	 * to the interrupt controller node)
	 *
	 * target-> find the interrupt controller node that handles PCIe
	 * INTx interrupt
	 */
	struct device_node *intc = of_get_next_child(dev->of_node, NULL);

	if (!intc) {
		dev_err(dev, "missing child interrupt-controller node\n");
		return -EINVAL;
	}

	/*
	 * create a linear mapped IRQ domain
	 */
	rockchip->irq_domain = irq_domain_add_linear(intc, PCI_NUM_INTX,
				&intx_domain_ops, rockchip);
	

	return 0;
}
