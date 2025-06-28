
int rockchip_pcie_parse_dt(struct rockchip_pcie *rockchip)
{
	/*
	 * obtain the physical base address of the PCIe controller's APB 
	 * registers and map it to a virtual address accessible by the 
	 * kernel
	 */	
	rockchip->apb_base = 
		devm_platform_ioremap_resource_byname(pdev, "apb-base");
	if (IS_ERR(rockchip->apb_base))
		return PTR_ERR(rockchip->apb_base);
}
