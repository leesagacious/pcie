
int rockchip_pcie_get_phys(struct rockchip_pcie *rockchip)
{
	struct phy *phy;

	phy = devm_phy_get(dev, "pcie-phy");
	if (!IS_ERR(phy)) {
		rockchip->legacy_phy = true;
		rockchip->phys[0] = phy;
		dev_warn(dev, "legacy phy model is deprecated!\n");
		return 0;
	}

	return 0;
}

int rockchip_pcie_parse_dt(struct rockchip_pcie *rockchip)
{
	int err;

	regs = platform_get_resource_byname(pdev,
				IORESOURCE_MEM,
				"axi-base");
	rockchip->reg_base = devm_pci_remap_cfg_resource(dev, regs);
	if (IS_ERR(rockchip->reg_base))
		return PTR_ERR(rockchip->reg_base);

	/*
	 * obtain the physical base address of the PCIe controller's APB 
	 * registers and map it to a virtual address accessible by the 
	 * kernel
	 */	
	rockchip->apb_base = 
		devm_platform_ioremap_resource_byname(pdev, "apb-base");
	if (IS_ERR(rockchip->apb_base))
		return PTR_ERR(rockchip->apb_base);
	
	/*
	 * Acquire physical layer resources for the PCIe controller
	 */
	err = rockchip_pcie_get_phys(rockchip);
	if (err)
		return err;
}
