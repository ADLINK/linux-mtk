/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __SOC_MEDIATEK_MT8183_MMSYS_H
#define __SOC_MEDIATEK_MT8183_MMSYS_H

#define MT8183_DISP_OVL0_MOUT_EN		0xf00
#define MT8183_DISP_OVL0_2L_MOUT_EN		0xf04
#define MT8183_DISP_OVL1_2L_MOUT_EN		0xf08
#define MT8183_DISP_DITHER0_MOUT_EN		0xf0c
#define MT8183_DISP_PATH0_SEL_IN		0xf24
#define MT8183_DISP_DSI0_SEL_IN			0xf2c
#define MT8183_DISP_DPI0_SEL_IN			0xf30
#define MT8183_DISP_RDMA0_SOUT_SEL_IN		0xf50
#define MT8183_DISP_RDMA1_SOUT_SEL_IN		0xf54
#define MT8183_MDP_ISP_MOUT_EN			0xf80
#define MT8183_MDP_RDMA0_MOUT_EN		0xf84
#define MT8183_MDP_PRZ0_MOUT_EN			0xf8c
#define MT8183_MDP_PRZ1_MOUT_EN			0xf90
#define MT8183_MDP_COLOR_MOUT_EN		0xf94
#define MT8183_MDP_IPU_MOUT_EN			0xf98
#define MT8183_MDP_PATH0_SOUT_SEL		0xfa8
#define MT8183_MDP_PATH1_SOUT_SEL		0xfac
#define MT8183_MDP_PRZ0_SEL_IN			0xfc0
#define MT8183_MDP_PRZ1_SEL_IN			0xfc4
#define MT8183_MDP_TDSHP_SEL_IN			0xfc8
#define MT8183_MDP_WROT0_SEL_IN			0xfd0
#define MT8183_MDP_WDMA_SEL_IN			0xfd4
#define MT8183_MDP_PATH0_SEL_IN			0xfe0
#define MT8183_MDP_PATH1_SEL_IN			0xfe4
#define MT8183_MDP_AAL_MOUT_EN			0xfe8
#define MT8183_MDP_AAL_SEL_IN			0xfec
#define MT8183_MDP_CCORR_SEL_IN			0xff0
#define MT8183_MDP_CCORR_SOUT_SEL		0xff4

#define MT8183_ISP_CTRL_MMSYS_SW0_RST_B		0x140
#define MT8183_ISP_CTRL_MMSYS_SW1_RST_B		0x144
#define MT8183_ISP_CTRL_MDP_ASYNC_CFG_WD	0x934
#define MT8183_ISP_CTRL_MDP_ASYNC_IPU_CFG_WD	0x93C
#define MT8183_ISP_CTRL_ISP_RELAY_CFG_WD	0x994
#define MT8183_ISP_CTRL_IPU_RELAY_CFG_WD	0x9a0

#define MT8183_OVL0_MOUT_EN_OVL0_2L		BIT(4)
#define MT8183_OVL0_2L_MOUT_EN_DISP_PATH0	BIT(0)
#define MT8183_OVL1_2L_MOUT_EN_RDMA1		BIT(4)
#define MT8183_DITHER0_MOUT_IN_DSI0		BIT(0)
#define MT8183_DISP_PATH0_SEL_IN_OVL0_2L	0x1
#define MT8183_DSI0_SEL_IN_RDMA0		0x1
#define MT8183_DSI0_SEL_IN_RDMA1		0x3
#define MT8183_DPI0_SEL_IN_RDMA0		0x1
#define MT8183_DPI0_SEL_IN_RDMA1		0x2
#define MT8183_RDMA0_SOUT_COLOR0		0x1
#define MT8183_RDMA1_SOUT_DSI0			0x1
#define MT8183_MDP_ISP_MOUT_EN_CCORR0		BIT(0)
#define MT8183_MDP_ISP_MOUT_EN_RSZ1		BIT(1)
#define MT8183_MDP_ISP_MOUT_EN_AAL0		BIT(2)
#define MT8183_MDP_IPU_MOUT_EN_CCORR0		BIT(0)
#define MT8183_MDP_IPU_MOUT_EN_RSZ1		BIT(1)
#define MT8183_MDP_IPU_MOUT_EN_AAL0		BIT(2)
#define MT8183_MDP_RDMA0_MOUT_EN_CCORR0		BIT(0)
#define MT8183_MDP_RDMA0_MOUT_EN_RSZ1		BIT(1)
#define MT8183_MDP_RDMA0_MOUT_EN_PATH0_OUT	BIT(2)
#define MT8183_MDP_RDMA0_MOUT_EN_AAL0		BIT(3)
#define MT8183_MDP_AAL_MOUT_EN_CCORR0		BIT(0)
#define MT8183_MDP_AAL_MOUT_EN_RSZ1		BIT(1)
#define MT8183_MDP_AAL_MOUT_EN_RSZ0		BIT(2)
#define MT8183_MDP_PRZ0_MOUT_EN_PATH0_OUT	BIT(0)
#define MT8183_MDP_PRZ0_MOUT_EN_TDSHP0		BIT(1)
#define MT8183_MDP_PRZ1_MOUT_EN_PATH0_OUT	BIT(0)
#define MT8183_MDP_PRZ1_MOUT_EN_TDSHP0		BIT(1)
#define MT8183_MDP_PRZ1_MOUT_EN_PATH1_OUT	BIT(2)
#define MT8183_MDP_PRZ1_MOUT_EN_COLOR0		BIT(4)
#define MT8183_MDP_COLOR_MOUT_EN_PATH0_OUT	BIT(0)
#define MT8183_MDP_COLOR_MOUT_EN_PATH1_OUT	BIT(1)
#define MT8183_MDP_AAL_SEL_IN_CAMIN		0
#define MT8183_MDP_AAL_SEL_IN_RDMA0		1
#define MT8183_MDP_AAL_SEL_IN_CAMIN2		2
#define MT8183_MDP_AAL_SEL_IN_CCORR0		3
#define MT8183_MDP_CCORR_SEL_IN_CAMIN		0
#define MT8183_MDP_CCORR_SEL_IN_RDMA0		1
#define MT8183_MDP_CCORR_SEL_IN_CAMIN2		3
#define MT8183_MDP_CCORR_SEL_IN_AAL0		4
#define MT8183_MDP_PRZ0_SEL_IN_AAL0		0
#define MT8183_MDP_PRZ0_SEL_IN_CCORR0		1
#define MT8183_MDP_PRZ1_SEL_IN_CAMIN		0
#define MT8183_MDP_PRZ1_SEL_IN_RDMA0		1
#define MT8183_MDP_PRZ1_SEL_IN_CAMIN2		4
#define MT8183_MDP_PRZ1_SEL_IN_AAL0		5
#define MT8183_MDP_TDSHP_SEL_IN_RSZ0		0
#define MT8183_MDP_TDSHP_SEL_IN_RSZ1		1
#define MT8183_MDP_PATH0_SEL_IN_RSZ0		0
#define MT8183_MDP_PATH0_SEL_IN_RSZ1		1
#define MT8183_MDP_PATH0_SEL_IN_COLOR0		2
#define MT8183_MDP_PATH0_SEL_IN_RDMA0		3
#define MT8183_MDP_PATH1_SEL_IN_RSZ1		0
#define MT8183_MDP_PATH1_SEL_IN_COLOR0		1
#define MT8183_MDP_WROT0_SEL_IN_PATH0_OUT	0
#define MT8183_MDP_WDMA_SEL_IN_PATH1_OUT	0
#define MT8183_MDP_CCORR_SOUT_SEL_AAL0		0
#define MT8183_MDP_CCORR_SOUT_SEL_RSZ0		1
#define MT8183_MDP_PATH0_SOUT_SEL_WROT0		0
#define MT8183_MDP_PATH1_SOUT_SEL_WDMA		0

#define MT8183_MMSYS_SW0_RST_B			0x140

static const struct mtk_mmsys_routes mmsys_mt8183_routing_table[] = {
	{
		DDP_COMPONENT_OVL0, DDP_COMPONENT_OVL_2L0,
		MT8183_DISP_OVL0_MOUT_EN, MT8183_OVL0_MOUT_EN_OVL0_2L,
		MT8183_OVL0_MOUT_EN_OVL0_2L
	}, {
		DDP_COMPONENT_OVL_2L0, DDP_COMPONENT_RDMA0,
		MT8183_DISP_OVL0_2L_MOUT_EN, MT8183_OVL0_2L_MOUT_EN_DISP_PATH0,
		MT8183_OVL0_2L_MOUT_EN_DISP_PATH0
	}, {
		DDP_COMPONENT_OVL_2L1, DDP_COMPONENT_RDMA1,
		MT8183_DISP_OVL1_2L_MOUT_EN, MT8183_OVL1_2L_MOUT_EN_RDMA1,
		MT8183_OVL1_2L_MOUT_EN_RDMA1
	}, {
		DDP_COMPONENT_DITHER0, DDP_COMPONENT_DSI0,
		MT8183_DISP_DITHER0_MOUT_EN, MT8183_DITHER0_MOUT_IN_DSI0,
		MT8183_DITHER0_MOUT_IN_DSI0
	}, {
		DDP_COMPONENT_OVL_2L0, DDP_COMPONENT_RDMA0,
		MT8183_DISP_PATH0_SEL_IN, MT8183_DISP_PATH0_SEL_IN_OVL0_2L,
		MT8183_DISP_PATH0_SEL_IN_OVL0_2L
	}, {
		DDP_COMPONENT_RDMA1, DDP_COMPONENT_DPI0,
		MT8183_DISP_DPI0_SEL_IN, MT8183_DPI0_SEL_IN_RDMA1,
		MT8183_DPI0_SEL_IN_RDMA1
	}, {
		DDP_COMPONENT_RDMA0, DDP_COMPONENT_COLOR0,
		MT8183_DISP_RDMA0_SOUT_SEL_IN, MT8183_RDMA0_SOUT_COLOR0,
		MT8183_RDMA0_SOUT_COLOR0
	}
};

static const struct mtk_mmsys_routes mmsys_mt8183_mdp_routing_table[] = {
	{
		MDP_COMP_CAMIN, MDP_COMP_CCORR0,
		MT8183_MDP_ISP_MOUT_EN, MT8183_MDP_ISP_MOUT_EN_CCORR0
	}, {
		MDP_COMP_CAMIN, MDP_COMP_RSZ1,
		MT8183_MDP_ISP_MOUT_EN, MT8183_MDP_ISP_MOUT_EN_RSZ1
	}, {
		MDP_COMP_CAMIN, MDP_COMP_AAL0,
		MT8183_MDP_ISP_MOUT_EN, MT8183_MDP_ISP_MOUT_EN_AAL0
	}, {
		MDP_COMP_CAMIN2, MDP_COMP_CCORR0,
		MT8183_MDP_IPU_MOUT_EN, MT8183_MDP_IPU_MOUT_EN_CCORR0
	}, {
		MDP_COMP_CAMIN2, MDP_COMP_RSZ1,
		MT8183_MDP_IPU_MOUT_EN, MT8183_MDP_IPU_MOUT_EN_RSZ1
	}, {
		MDP_COMP_CAMIN2, MDP_COMP_AAL0,
		MT8183_MDP_IPU_MOUT_EN, MT8183_MDP_IPU_MOUT_EN_AAL0
	}, {
		MDP_COMP_RDMA0, MDP_COMP_CCORR0,
		MT8183_MDP_RDMA0_MOUT_EN, MT8183_MDP_RDMA0_MOUT_EN_CCORR0
	}, {
		MDP_COMP_RDMA0, MDP_COMP_RSZ1,
		MT8183_MDP_RDMA0_MOUT_EN, MT8183_MDP_RDMA0_MOUT_EN_RSZ1
	}, {
		MDP_COMP_RDMA0, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_RDMA0_MOUT_EN, MT8183_MDP_RDMA0_MOUT_EN_PATH0_OUT
	}, {
		MDP_COMP_RDMA0, MDP_COMP_AAL0,
		MT8183_MDP_RDMA0_MOUT_EN, MT8183_MDP_RDMA0_MOUT_EN_AAL0
	}, {
		MDP_COMP_AAL0, MDP_COMP_CCORR0,
		MT8183_MDP_AAL_MOUT_EN, MT8183_MDP_AAL_MOUT_EN_CCORR0
	}, {
		MDP_COMP_AAL0, MDP_COMP_RSZ1,
		MT8183_MDP_AAL_MOUT_EN, MT8183_MDP_AAL_MOUT_EN_RSZ1
	}, {
		MDP_COMP_AAL0, MDP_COMP_RSZ0,
		MT8183_MDP_AAL_MOUT_EN, MT8183_MDP_AAL_MOUT_EN_RSZ0
	}, {
		MDP_COMP_RSZ0, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_PRZ0_MOUT_EN, MT8183_MDP_PRZ0_MOUT_EN_PATH0_OUT
	}, {
		MDP_COMP_RSZ0, MDP_COMP_TDSHP0,
		MT8183_MDP_PRZ0_MOUT_EN, MT8183_MDP_PRZ0_MOUT_EN_TDSHP0
	}, {
		MDP_COMP_RSZ1, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_PRZ1_MOUT_EN, MT8183_MDP_PRZ1_MOUT_EN_PATH0_OUT
	}, {
		MDP_COMP_RSZ1, MDP_COMP_TDSHP0,
		MT8183_MDP_PRZ1_MOUT_EN, MT8183_MDP_PRZ1_MOUT_EN_TDSHP0
	}, {
		MDP_COMP_RSZ1, MDP_COMP_PATH1_SOUT,
		MT8183_MDP_PRZ1_MOUT_EN, MT8183_MDP_PRZ1_MOUT_EN_PATH1_OUT
	}, {
		MDP_COMP_RSZ1, MDP_COMP_COLOR0,
		MT8183_MDP_PRZ1_MOUT_EN, MT8183_MDP_PRZ1_MOUT_EN_COLOR0
	}, {
		MDP_COMP_COLOR0, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_COLOR_MOUT_EN, MT8183_MDP_COLOR_MOUT_EN_PATH0_OUT
	}, {
		MDP_COMP_COLOR0, MDP_COMP_PATH1_SOUT,
		MT8183_MDP_COLOR_MOUT_EN, MT8183_MDP_COLOR_MOUT_EN_PATH1_OUT
	}, {
		MDP_COMP_CAMIN, MDP_COMP_AAL0,
		MT8183_MDP_AAL_SEL_IN, MT8183_MDP_AAL_SEL_IN_CAMIN
	}, {
		MDP_COMP_RDMA0, MDP_COMP_AAL0,
		MT8183_MDP_AAL_SEL_IN, MT8183_MDP_AAL_SEL_IN_RDMA0
	}, {
		MDP_COMP_CAMIN2, MDP_COMP_AAL0,
		MT8183_MDP_AAL_SEL_IN, MT8183_MDP_AAL_SEL_IN_CAMIN2
	}, {
		MDP_COMP_CCORR0, MDP_COMP_AAL0,
		MT8183_MDP_AAL_SEL_IN, MT8183_MDP_AAL_SEL_IN_CCORR0
	}, {
		MDP_COMP_CAMIN, MDP_COMP_CCORR0,
		MT8183_MDP_CCORR_SEL_IN, MT8183_MDP_CCORR_SEL_IN_CAMIN
	}, {
		MDP_COMP_RDMA0, MDP_COMP_CCORR0,
		MT8183_MDP_CCORR_SEL_IN, MT8183_MDP_CCORR_SEL_IN_RDMA0
	}, {
		MDP_COMP_CAMIN2, MDP_COMP_CCORR0,
		MT8183_MDP_CCORR_SEL_IN, MT8183_MDP_CCORR_SEL_IN_CAMIN2
	}, {
		MDP_COMP_AAL0, MDP_COMP_CCORR0,
		MT8183_MDP_CCORR_SEL_IN, MT8183_MDP_CCORR_SEL_IN_AAL0
	}, {
		MDP_COMP_AAL0, MDP_COMP_RSZ0,
		MT8183_MDP_PRZ0_SEL_IN, MT8183_MDP_PRZ0_SEL_IN_AAL0
	}, {
		MDP_COMP_CCORR0, MDP_COMP_RSZ0,
		MT8183_MDP_PRZ0_SEL_IN, MT8183_MDP_PRZ0_SEL_IN_CCORR0
	}, {
		MDP_COMP_CAMIN, MDP_COMP_RSZ1,
		MT8183_MDP_PRZ1_SEL_IN, MT8183_MDP_PRZ1_SEL_IN_CAMIN
	}, {
		MDP_COMP_RDMA0, MDP_COMP_RSZ1,
		MT8183_MDP_PRZ1_SEL_IN, MT8183_MDP_PRZ1_SEL_IN_RDMA0
	}, {
		MDP_COMP_CAMIN2, MDP_COMP_RSZ1,
		MT8183_MDP_PRZ1_SEL_IN, MT8183_MDP_PRZ1_SEL_IN_CAMIN2
	}, {
		MDP_COMP_AAL0, MDP_COMP_RSZ1,
		MT8183_MDP_PRZ1_SEL_IN, MT8183_MDP_PRZ1_SEL_IN_AAL0
	}, {
		MDP_COMP_RSZ0, MDP_COMP_TDSHP0,
		MT8183_MDP_TDSHP_SEL_IN, MT8183_MDP_TDSHP_SEL_IN_RSZ0
	}, {
		MDP_COMP_RSZ1, MDP_COMP_TDSHP0,
		MT8183_MDP_TDSHP_SEL_IN, MT8183_MDP_TDSHP_SEL_IN_RSZ1
	}, {
		MDP_COMP_RSZ0, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_PATH0_SEL_IN, MT8183_MDP_PATH0_SEL_IN_RSZ0
	}, {
		MDP_COMP_RSZ1, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_PATH0_SEL_IN, MT8183_MDP_PATH0_SEL_IN_RSZ1
	}, {
		MDP_COMP_COLOR0, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_PATH0_SEL_IN, MT8183_MDP_PATH0_SEL_IN_COLOR0
	}, {
		MDP_COMP_RDMA0, MDP_COMP_PATH0_SOUT,
		MT8183_MDP_PATH0_SEL_IN, MT8183_MDP_PATH0_SEL_IN_RDMA0
	}, {
		MDP_COMP_RSZ1, MDP_COMP_PATH1_SOUT,
		MT8183_MDP_PATH1_SEL_IN, MT8183_MDP_PATH1_SEL_IN_RSZ1
	}, {
		MDP_COMP_COLOR0, MDP_COMP_PATH1_SOUT,
		MT8183_MDP_PATH1_SEL_IN, MT8183_MDP_PATH1_SEL_IN_COLOR0
	}, {
		MDP_COMP_PATH0_SOUT, MDP_COMP_WROT0,
		MT8183_MDP_WROT0_SEL_IN, MT8183_MDP_WROT0_SEL_IN_PATH0_OUT
	}, {
		MDP_COMP_PATH1_SOUT, MDP_COMP_WDMA,
		MT8183_MDP_WDMA_SEL_IN, MT8183_MDP_WDMA_SEL_IN_PATH1_OUT
	}, {
		MDP_COMP_CCORR0, MDP_COMP_AAL0,
		MT8183_MDP_CCORR_SOUT_SEL, MT8183_MDP_CCORR_SOUT_SEL_AAL0
	}, {
		MDP_COMP_CCORR0, MDP_COMP_RSZ0,
		MT8183_MDP_CCORR_SOUT_SEL, MT8183_MDP_CCORR_SOUT_SEL_RSZ0
	}, {
		MDP_COMP_PATH0_SOUT, MDP_COMP_WROT0,
		MT8183_MDP_PATH0_SOUT_SEL, MT8183_MDP_PATH0_SOUT_SEL_WROT0
	}, {
		MDP_COMP_PATH1_SOUT, MDP_COMP_WDMA,
		MT8183_MDP_PATH1_SOUT_SEL, MT8183_MDP_PATH1_SOUT_SEL_WDMA
	}
};

static const unsigned int mmsys_mt8183_mdp_isp_ctrl_table[ISP_CTRL_MAX] = {
	[ISP_CTRL_MMSYS_SW0_RST_B] = MT8183_ISP_CTRL_MMSYS_SW0_RST_B,
	[ISP_CTRL_MMSYS_SW1_RST_B] = MT8183_ISP_CTRL_MMSYS_SW1_RST_B,
	[ISP_CTRL_MDP_ASYNC_CFG_WD] = MT8183_ISP_CTRL_MDP_ASYNC_CFG_WD,
	[ISP_CTRL_MDP_ASYNC_IPU_CFG_WD] = MT8183_ISP_CTRL_MDP_ASYNC_IPU_CFG_WD,
	[ISP_CTRL_ISP_RELAY_CFG_WD] = MT8183_ISP_CTRL_ISP_RELAY_CFG_WD,
	[ISP_CTRL_IPU_RELAY_CFG_WD] = MT8183_ISP_CTRL_IPU_RELAY_CFG_WD,
};

#endif /* __SOC_MEDIATEK_MT8183_MMSYS_H */

