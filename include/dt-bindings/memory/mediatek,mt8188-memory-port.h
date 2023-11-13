/* SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause) */
/*
 * Copyright (c) 2022 MediaTek Inc.
 * Author: Chengci Xu <chengci.xu@mediatek.com>
 */
#ifndef _DT_BINDINGS_MEMORY_MEDIATEK_MT8188_LARB_PORT_H_
#define _DT_BINDINGS_MEMORY_MEDIATEK_MT8188_LARB_PORT_H_

#include <dt-bindings/memory/mtk-memory-port.h>

/*
 * MM IOMMU supports 16GB dma address. We separate it to four ranges:
 * 0 ~ 4G; 4G ~ 8G; 8G ~ 12G; 12G ~ 16G, we could adjust these masters
 * locate in anyone region. BUT:
 * a) Make sure all the ports inside a larb are in one range.
 * b) The iova of any master can NOT cross the 4G/8G/12G boundary.
 *
 * This is the suggested mapping in this SoC:
 *
 * modules    dma-address-region	larbs-ports
 * disp         0 ~ 4G                  larb0/1/2/3
 * vcodec      4G ~ 8G                  larb19/21/23
 * cam/mdp     8G ~ 12G                 the other larbs.
 * N/A         12G ~ 16G
 * CCU0   0x24000_0000 ~ 0x243ff_ffff   larb27: port 0/1
 * CCU1   0x24400_0000 ~ 0x247ff_ffff   larb27: port 2/3
 *
 * This SoC have two MM IOMMU HWs, this is the connected information:
 * iommu-vdo: larb0/2/5/9/10/11A/11C/13/16B/17B/19/21
 * iommu-vpp: larb1/3/4/6/7/11B/12/14/15/16A/17A/23/27
 */

/* MM IOMMU larbs */
#define SMI_L0_ID		0
#define SMI_L1_ID		1
#define SMI_L2_ID		2
#define SMI_L3_ID		3
#define SMI_L4_ID		4
#define SMI_L5_ID		5
#define SMI_L6_ID		6
#define SMI_L7_ID		7
#define SMI_L9_ID		8
#define SMI_L10_ID		9
#define SMI_L11A_ID		10
#define SMI_L11B_ID		11
#define SMI_L11C_ID		12
#define SMI_L12_ID		13
#define SMI_L13_ID		14
#define SMI_L14_ID		15
#define SMI_L15_ID		16
#define SMI_L16A_ID		17
#define SMI_L16B_ID		18
#define SMI_L17A_ID		19
#define SMI_L17B_ID		20
#define SMI_L19_ID		21
#define SMI_L21_ID		22
#define SMI_L23_ID		23
#define SMI_L27_ID		24
#define SMI_L28_ID		25

/* Fake LARB ID for APU & GPU */
#define APU_L0_ID		26
#define APU_L1_ID		27

/* MM IOMMU ports */
/* LARB 0 -- VDO-0 */
#define M4U_PORT_L0_DISP_RDMA1			MTK_M4U_ID(SMI_L0_ID, 0)
#define M4U_PORT_L0_DISP_WDMA0			MTK_M4U_ID(SMI_L0_ID, 1)
#define M4U_PORT_L0_DISP_OVL0_RDMA0		MTK_M4U_ID(SMI_L0_ID, 2)
#define M4U_PORT_L0_DISP_OVL0_RDMA1		MTK_M4U_ID(SMI_L0_ID, 3)
#define M4U_PORT_L0_DISP_OVL0_HDR		MTK_M4U_ID(SMI_L0_ID, 4)
#define M4U_PORT_L0_DISP_POSTMASK0		MTK_M4U_ID(SMI_L0_ID, 5)
#define M4U_PORT_L0_DISP_FAKE_ENG0		MTK_M4U_ID(SMI_L0_ID, 6)

/* LARB 1 -- VD0-0 */
#define M4U_PORT_L1_DISP_RDMA0			MTK_M4U_ID(SMI_L1_ID, 0)
#define M4U_PORT_L1_DISP_WDMA1			MTK_M4U_ID(SMI_L1_ID, 1)
#define M4U_PORT_L1_DISP_OVL1_RDMA0		MTK_M4U_ID(SMI_L1_ID, 2)
#define M4U_PORT_L1_DISP_OVL1_RDMA1		MTK_M4U_ID(SMI_L1_ID, 3)
#define M4U_PORT_L1_DISP_OVL1_HDR		MTK_M4U_ID(SMI_L1_ID, 4)
#define M4U_PORT_L1_DISP_WROT0			MTK_M4U_ID(SMI_L1_ID, 5)
#define M4U_PORT_L1_DISP_FAKE_ENG1		MTK_M4U_ID(SMI_L1_ID, 6)

/* LARB 2 -- VDO-1 */
#define M4U_PORT_L2_MDP_RDMA0			MTK_M4U_ID(SMI_L2_ID, 0)
#define M4U_PORT_L2_MDP_RDMA2			MTK_M4U_ID(SMI_L2_ID, 1)
#define M4U_PORT_L2_MDP_RDMA4			MTK_M4U_ID(SMI_L2_ID, 2)
#define M4U_PORT_L2_MDP_RDMA6			MTK_M4U_ID(SMI_L2_ID, 3)
#define M4U_PORT_L2_DISP_FAKE1			MTK_M4U_ID(SMI_L2_ID, 4)

/* LARB 3 -- VDO-1 */
#define M4U_PORT_L3_MDP_RDMA1			MTK_M4U_ID(SMI_L3_ID, 0)
#define M4U_PORT_L3_MDP_RDMA3			MTK_M4U_ID(SMI_L3_ID, 1)
#define M4U_PORT_L3_MDP_RDMA5			MTK_M4U_ID(SMI_L3_ID, 2)
#define M4U_PORT_L3_MDP_RDMA7			MTK_M4U_ID(SMI_L3_ID, 3)
#define M4U_PORT_L3_HDR_DS_SMI			MTK_M4U_ID(SMI_L3_ID, 4)
#define M4U_PORT_L3_HDR_ADL_SMI			MTK_M4U_ID(SMI_L3_ID, 5)
#define M4U_PORT_L3_DISP_FAKE1			MTK_M4U_ID(SMI_L3_ID, 6)

/* LARB 4 -- VPP-0 */
#define M4U_PORT_L4_MDP_RDMA			MTK_M4U_ID(SMI_L4_ID, 0)
#define M4U_PORT_L4_MDP_FG			MTK_M4U_ID(SMI_L4_ID, 1)
#define M4U_PORT_L4_MDP_OVL			MTK_M4U_ID(SMI_L4_ID, 2)
#define M4U_PORT_L4_MDP_WROT			MTK_M4U_ID(SMI_L4_ID, 3)
#define M4U_PORT_L4_FAKE_ENG			MTK_M4U_ID(SMI_L4_ID, 4)
#define M4U_PORT_L4_DISP_RDMA			MTK_M4U_ID(SMI_L4_ID, 5)
#define M4U_PORT_L4_DISP_WDMA			MTK_M4U_ID(SMI_L4_ID, 6)

/* LARB 5 -- VPP-1 */
#define M4U_PORT_L5_SVPP1_MDP_RDMA		MTK_M4U_ID(SMI_L5_ID, 0)
#define M4U_PORT_L5_SVPP1_MDP_FG		MTK_M4U_ID(SMI_L5_ID, 1)
#define M4U_PORT_L5_SVPP1_MDP_OVL		MTK_M4U_ID(SMI_L5_ID, 2)
#define M4U_PORT_L5_SVPP1_MDP_WROT		MTK_M4U_ID(SMI_L5_ID, 3)
#define M4U_PORT_L5_SVPP2_MDP_RDMA		MTK_M4U_ID(SMI_L5_ID, 4)
#define M4U_PORT_L5_SVPP2_MDP_FG		MTK_M4U_ID(SMI_L5_ID, 5)
#define M4U_PORT_L5_SVPP2_MDP_WROT		MTK_M4U_ID(SMI_L5_ID, 6)
#define M4U_PORT_L5_LARB5_FAKE_ENG		MTK_M4U_ID(SMI_L5_ID, 7)

/* LARB 6 -- VPP-1 */
#define M4U_PORT_L6_SVPP3_MDP_RDMA		MTK_M4U_ID(SMI_L6_ID, 0)
#define M4U_PORT_L6_SVPP3_MDP_FG		MTK_M4U_ID(SMI_L6_ID, 1)
#define M4U_PORT_L6_SVPP3_MDP_WROT		MTK_M4U_ID(SMI_L6_ID, 2)
#define M4U_PORT_L6_LARB6_FAKE_ENG		MTK_M4U_ID(SMI_L6_ID, 3)

/* LARB 7 -- WPE */
#define M4U_PORT_L7_WPE_RDMA_0			MTK_M4U_ID(SMI_L7_ID, 0)
#define M4U_PORT_L7_WPE_RDMA_1			MTK_M4U_ID(SMI_L7_ID, 1)
#define M4U_PORT_L7_WPE_WDMA_0			MTK_M4U_ID(SMI_L7_ID, 2)

/* LARB 9 -- IMG-M */
#define M4U_PORT_L9_IMGI_T1_A			MTK_M4U_ID(SMI_L9_ID, 0)
#define M4U_PORT_L9_UFDI_T1_A			MTK_M4U_ID(SMI_L9_ID, 1)
#define M4U_PORT_L9_IMGBI_T1_A			MTK_M4U_ID(SMI_L9_ID, 2)
#define M4U_PORT_L9_IMGCI_T1_A			MTK_M4U_ID(SMI_L9_ID, 3)
#define M4U_PORT_L9_SMTI_T1_A			MTK_M4U_ID(SMI_L9_ID, 4)
#define M4U_PORT_L9_SMTI_T4_A			MTK_M4U_ID(SMI_L9_ID, 5)
#define M4U_PORT_L9_TNCSTI_T1_A			MTK_M4U_ID(SMI_L9_ID, 6)
#define M4U_PORT_L9_TNCSTI_T4_A			MTK_M4U_ID(SMI_L9_ID, 7)
#define M4U_PORT_L9_YUVO_T1_A			MTK_M4U_ID(SMI_L9_ID, 8)
#define M4U_PORT_L9_YUVBO_T1_A			MTK_M4U_ID(SMI_L9_ID, 9)
#define M4U_PORT_L9_YUVCO_T1_A			MTK_M4U_ID(SMI_L9_ID, 10)
#define M4U_PORT_L9_TIMGO_T1_A			MTK_M4U_ID(SMI_L9_ID, 11)
#define M4U_PORT_L9_YUVO_T2_A			MTK_M4U_ID(SMI_L9_ID, 12)
#define M4U_PORT_L9_YUVO_T5_A			MTK_M4U_ID(SMI_L9_ID, 13)
#define M4U_PORT_L9_IMGI_T1_B			MTK_M4U_ID(SMI_L9_ID, 14)
#define M4U_PORT_L9_IMGBI_T1_B			MTK_M4U_ID(SMI_L9_ID, 15)
#define M4U_PORT_L9_IMGCI_T1_B			MTK_M4U_ID(SMI_L9_ID, 16)
#define M4U_PORT_L9_SMTI_T4_B			MTK_M4U_ID(SMI_L9_ID, 17)
#define M4U_PORT_L9_TNCSO_T1_A			MTK_M4U_ID(SMI_L9_ID, 18)
#define M4U_PORT_L9_SMTO_T1_A			MTK_M4U_ID(SMI_L9_ID, 19)
#define M4U_PORT_L9_SMTO_T4_A			MTK_M4U_ID(SMI_L9_ID, 20)
#define M4U_PORT_L9_TNCSTO_T1_A			MTK_M4U_ID(SMI_L9_ID, 21)
#define M4U_PORT_L9_YUVO_T2_B			MTK_M4U_ID(SMI_L9_ID, 22)
#define M4U_PORT_L9_YUVO_T5_B			MTK_M4U_ID(SMI_L9_ID, 23)
#define M4U_PORT_L9_SMTO_T4_B			MTK_M4U_ID(SMI_L9_ID, 24)

/* LARB 10 -- IMG-D */
#define M4U_PORT_L10_IMGI_D1			MTK_M4U_ID(SMI_L10_ID, 0)
#define M4U_PORT_L10_IMGBI_D1			MTK_M4U_ID(SMI_L10_ID, 1)
#define M4U_PORT_L10_IMGCI_D1			MTK_M4U_ID(SMI_L10_ID, 2)
#define M4U_PORT_L10_IMGDI_D1			MTK_M4U_ID(SMI_L10_ID, 3)
#define M4U_PORT_L10_DEPI_D1			MTK_M4U_ID(SMI_L10_ID, 4)
#define M4U_PORT_L10_DMGI_D1			MTK_M4U_ID(SMI_L10_ID, 5)
#define M4U_PORT_L10_SMTI_D1			MTK_M4U_ID(SMI_L10_ID, 6)
#define M4U_PORT_L10_RECI_D1			MTK_M4U_ID(SMI_L10_ID, 7)
#define M4U_PORT_L10_RECI_D1_N			MTK_M4U_ID(SMI_L10_ID, 8)
#define M4U_PORT_L10_TNRWI_D1			MTK_M4U_ID(SMI_L10_ID, 9)
#define M4U_PORT_L10_TNRCI_D1			MTK_M4U_ID(SMI_L10_ID, 10)
#define M4U_PORT_L10_TNRCI_D1_N			MTK_M4U_ID(SMI_L10_ID, 11)
#define M4U_PORT_L10_IMG4O_D1			MTK_M4U_ID(SMI_L10_ID, 12)
#define M4U_PORT_L10_IMG4BO_D1			MTK_M4U_ID(SMI_L10_ID, 13)
#define M4U_PORT_L10_SMTI_D8			MTK_M4U_ID(SMI_L10_ID, 14)
#define M4U_PORT_L10_SMTO_D1			MTK_M4U_ID(SMI_L10_ID, 15)
#define M4U_PORT_L10_TNRMO_D1			MTK_M4U_ID(SMI_L10_ID, 16)
#define M4U_PORT_L10_TNRMO_D1_N			MTK_M4U_ID(SMI_L10_ID, 17)
#define M4U_PORT_L10_SMTO_D8			MTK_M4U_ID(SMI_L10_ID, 18)
#define M4U_PORT_L10_DBGO_D1			MTK_M4U_ID(SMI_L10_ID, 19)

/* LARB 11A -- IMG-D */
#define M4U_PORT_L11A_WPE_RDMA_0		MTK_M4U_ID(SMI_L11A_ID, 0)
#define M4U_PORT_L11A_WPE_RDMA_1		MTK_M4U_ID(SMI_L11A_ID, 1)
#define M4U_PORT_L11A_WPE_RDMA_4P_0		MTK_M4U_ID(SMI_L11A_ID, 2)
#define M4U_PORT_L11A_WPE_RDMA_4P_1		MTK_M4U_ID(SMI_L11A_ID, 3)
#define M4U_PORT_L11A_WPE_CQ0			MTK_M4U_ID(SMI_L11A_ID, 4)
#define M4U_PORT_L11A_WPE_CQ1			MTK_M4U_ID(SMI_L11A_ID, 5)
#define M4U_PORT_L11A_PIMGI_P1			MTK_M4U_ID(SMI_L11A_ID, 6)
#define M4U_PORT_L11A_PIMGBI_P1			MTK_M4U_ID(SMI_L11A_ID, 7)
#define M4U_PORT_L11A_PIMGCI_P1			MTK_M4U_ID(SMI_L11A_ID, 8)
#define M4U_PORT_L11A_IMGI_T1_C			MTK_M4U_ID(SMI_L11A_ID, 9)
#define M4U_PORT_L11A_IMGBI_T1_C		MTK_M4U_ID(SMI_L11A_ID, 10)
#define M4U_PORT_L11A_IMGCI_T1_C		MTK_M4U_ID(SMI_L11A_ID, 11)
#define M4U_PORT_L11A_SMTI_T1_C			MTK_M4U_ID(SMI_L11A_ID, 12)
#define M4U_PORT_L11A_SMTI_T4_C			MTK_M4U_ID(SMI_L11A_ID, 13)
#define M4U_PORT_L11A_SMTI_T6_C			MTK_M4U_ID(SMI_L11A_ID, 14)
#define M4U_PORT_L11A_YUVO_T1_C			MTK_M4U_ID(SMI_L11A_ID, 15)
#define M4U_PORT_L11A_YUVBO_T1_C		MTK_M4U_ID(SMI_L11A_ID, 16)
#define M4U_PORT_L11A_YUVCO_T1_C		MTK_M4U_ID(SMI_L11A_ID, 17)
#define M4U_PORT_L11A_WPE_WDMA_0		MTK_M4U_ID(SMI_L11A_ID, 18)
#define M4U_PORT_L11A_WPE_WDMA_4P_0		MTK_M4U_ID(SMI_L11A_ID, 19)
#define M4U_PORT_L11A_WROT_P1			MTK_M4U_ID(SMI_L11A_ID, 20)
#define M4U_PORT_L11A_TCCSO_P1			MTK_M4U_ID(SMI_L11A_ID, 21)
#define M4U_PORT_L11A_TCCSI_P1			MTK_M4U_ID(SMI_L11A_ID, 22)
#define M4U_PORT_L11A_TIMGO_T1_C		MTK_M4U_ID(SMI_L11A_ID, 23)
#define M4U_PORT_L11A_YUVO_T2_C			MTK_M4U_ID(SMI_L11A_ID, 24)
#define M4U_PORT_L11A_YUVO_T5_C			MTK_M4U_ID(SMI_L11A_ID, 25)
#define M4U_PORT_L11A_SMTO_T1_C			MTK_M4U_ID(SMI_L11A_ID, 26)
#define M4U_PORT_L11A_SMTO_T4_C			MTK_M4U_ID(SMI_L11A_ID, 27)
#define M4U_PORT_L11A_SMTO_T6_C			MTK_M4U_ID(SMI_L11A_ID, 28)
#define M4U_PORT_L11A_DBGO_T1_C			MTK_M4U_ID(SMI_L11A_ID, 29)

/* LARB 11B -- IMG-D */
#define M4U_PORT_L11B_WPE_RDMA_0		MTK_M4U_ID(SMI_L11B_ID, 0)
#define M4U_PORT_L11B_WPE_RDMA_1		MTK_M4U_ID(SMI_L11B_ID, 1)
#define M4U_PORT_L11B_WPE_RDMA_4P_0		MTK_M4U_ID(SMI_L11B_ID, 2)
#define M4U_PORT_L11B_WPE_RDMA_4P_1		MTK_M4U_ID(SMI_L11B_ID, 3)
#define M4U_PORT_L11B_WPE_CQ0			MTK_M4U_ID(SMI_L11B_ID, 4)
#define M4U_PORT_L11B_WPE_CQ1			MTK_M4U_ID(SMI_L11B_ID, 5)
#define M4U_PORT_L11B_PIMGI_P1			MTK_M4U_ID(SMI_L11B_ID, 6)
#define M4U_PORT_L11B_PIMGBI_P1			MTK_M4U_ID(SMI_L11B_ID, 7)
#define M4U_PORT_L11B_PIMGCI_P1			MTK_M4U_ID(SMI_L11B_ID, 8)
#define M4U_PORT_L11B_IMGI_T1_C			MTK_M4U_ID(SMI_L11B_ID, 9)
#define M4U_PORT_L11B_IMGBI_T1_C		MTK_M4U_ID(SMI_L11B_ID, 10)
#define M4U_PORT_L11B_IMGCI_T1_C		MTK_M4U_ID(SMI_L11B_ID, 11)
#define M4U_PORT_L11B_SMTI_T1_C			MTK_M4U_ID(SMI_L11B_ID, 12)
#define M4U_PORT_L11B_SMTI_T4_C			MTK_M4U_ID(SMI_L11B_ID, 13)
#define M4U_PORT_L11B_SMTI_T6_C			MTK_M4U_ID(SMI_L11B_ID, 14)
#define M4U_PORT_L11B_YUVO_T1_C			MTK_M4U_ID(SMI_L11B_ID, 15)
#define M4U_PORT_L11B_YUVBO_T1_C		MTK_M4U_ID(SMI_L11B_ID, 16)
#define M4U_PORT_L11B_YUVCO_T1_C		MTK_M4U_ID(SMI_L11B_ID, 17)
#define M4U_PORT_L11B_WPE_WDMA_0		MTK_M4U_ID(SMI_L11B_ID, 18)
#define M4U_PORT_L11B_WPE_WDMA_4P_0		MTK_M4U_ID(SMI_L11B_ID, 19)
#define M4U_PORT_L11B_WROT_P1			MTK_M4U_ID(SMI_L11B_ID, 20)
#define M4U_PORT_L11B_TCCSO_P1			MTK_M4U_ID(SMI_L11B_ID, 21)
#define M4U_PORT_L11B_TCCSI_P1			MTK_M4U_ID(SMI_L11B_ID, 22)
#define M4U_PORT_L11B_TIMGO_T1_C		MTK_M4U_ID(SMI_L11B_ID, 23)
#define M4U_PORT_L11B_YUVO_T2_C			MTK_M4U_ID(SMI_L11B_ID, 24)
#define M4U_PORT_L11B_YUVO_T5_C			MTK_M4U_ID(SMI_L11B_ID, 25)
#define M4U_PORT_L11B_SMTO_T1_C			MTK_M4U_ID(SMI_L11B_ID, 26)
#define M4U_PORT_L11B_SMTO_T4_C			MTK_M4U_ID(SMI_L11B_ID, 27)
#define M4U_PORT_L11B_SMTO_T6_C			MTK_M4U_ID(SMI_L11B_ID, 28)
#define M4U_PORT_L11B_DBGO_T1_C			MTK_M4U_ID(SMI_L11B_ID, 29)

/* LARB 11C -- IMG-D */
#define M4U_PORT_L11C_WPE_RDMA_0		MTK_M4U_ID(SMI_L11C_ID, 0)
#define M4U_PORT_L11C_WPE_RDMA_1		MTK_M4U_ID(SMI_L11C_ID, 1)
#define M4U_PORT_L11C_WPE_RDMA_4P_0		MTK_M4U_ID(SMI_L11C_ID, 2)
#define M4U_PORT_L11C_WPE_RDMA_4P_1		MTK_M4U_ID(SMI_L11C_ID, 3)
#define M4U_PORT_L11C_WPE_CQ0			MTK_M4U_ID(SMI_L11C_ID, 4)
#define M4U_PORT_L11C_WPE_CQ1			MTK_M4U_ID(SMI_L11C_ID, 5)
#define M4U_PORT_L11C_PIMGI_P1			MTK_M4U_ID(SMI_L11C_ID, 6)
#define M4U_PORT_L11C_PIMGBI_P1			MTK_M4U_ID(SMI_L11C_ID, 7)
#define M4U_PORT_L11C_PIMGCI_P1			MTK_M4U_ID(SMI_L11C_ID, 8)
#define M4U_PORT_L11C_IMGI_T1_C			MTK_M4U_ID(SMI_L11C_ID, 9)
#define M4U_PORT_L11C_IMGBI_T1_C		MTK_M4U_ID(SMI_L11C_ID, 10)
#define M4U_PORT_L11C_IMGCI_T1_C		MTK_M4U_ID(SMI_L11C_ID, 11)
#define M4U_PORT_L11C_SMTI_T1_C			MTK_M4U_ID(SMI_L11C_ID, 12)
#define M4U_PORT_L11C_SMTI_T4_C			MTK_M4U_ID(SMI_L11C_ID, 13)
#define M4U_PORT_L11C_SMTI_T6_C			MTK_M4U_ID(SMI_L11C_ID, 14)
#define M4U_PORT_L11C_YUVO_T1_C			MTK_M4U_ID(SMI_L11C_ID, 15)
#define M4U_PORT_L11C_YUVBO_T1_C		MTK_M4U_ID(SMI_L11C_ID, 16)
#define M4U_PORT_L11C_YUVCO_T1_C		MTK_M4U_ID(SMI_L11C_ID, 17)
#define M4U_PORT_L11C_WPE_WDMA_0		MTK_M4U_ID(SMI_L11C_ID, 18)
#define M4U_PORT_L11C_WPE_WDMA_4P_0		MTK_M4U_ID(SMI_L11C_ID, 19)
#define M4U_PORT_L11C_WROT_P1			MTK_M4U_ID(SMI_L11C_ID, 20)
#define M4U_PORT_L11C_TCCSO_P1			MTK_M4U_ID(SMI_L11C_ID, 21)
#define M4U_PORT_L11C_TCCSI_P1			MTK_M4U_ID(SMI_L11C_ID, 22)
#define M4U_PORT_L11C_TIMGO_T1_C		MTK_M4U_ID(SMI_L11C_ID, 23)
#define M4U_PORT_L11C_YUVO_T2_C			MTK_M4U_ID(SMI_L11C_ID, 24)
#define M4U_PORT_L11C_YUVO_T5_C			MTK_M4U_ID(SMI_L11C_ID, 25)
#define M4U_PORT_L11C_SMTO_T1_C			MTK_M4U_ID(SMI_L11C_ID, 26)
#define M4U_PORT_L11C_SMTO_T4_C			MTK_M4U_ID(SMI_L11C_ID, 27)
#define M4U_PORT_L11C_SMTO_T6_C			MTK_M4U_ID(SMI_L11C_ID, 28)
#define M4U_PORT_L11C_DBGO_T1_C			MTK_M4U_ID(SMI_L11C_ID, 29)

/* LARB 12 -- IPE */
#define M4U_PORT_L12_FDVT_RDA_0			MTK_M4U_ID(SMI_L12_ID, 0)
#define M4U_PORT_L12_FDVT_RDB_0			MTK_M4U_ID(SMI_L12_ID, 1)
#define M4U_PORT_L12_FDVT_WRA_0			MTK_M4U_ID(SMI_L12_ID, 2)
#define M4U_PORT_L12_FDVT_WRB_0			MTK_M4U_ID(SMI_L12_ID, 3)
#define M4U_PORT_L12_ME_RDMA			MTK_M4U_ID(SMI_L12_ID, 4)
#define M4U_PORT_L12_ME_WDMA			MTK_M4U_ID(SMI_L12_ID, 5)
#define M4U_PORT_L12_DVS_RDMA			MTK_M4U_ID(SMI_L12_ID, 6)
#define M4U_PORT_L12_DVS_WDMA			MTK_M4U_ID(SMI_L12_ID, 7)
#define M4U_PORT_L12_DVP_RDMA			MTK_M4U_ID(SMI_L12_ID, 8)
#define M4U_PORT_L12_DVP_WDMA			MTK_M4U_ID(SMI_L12_ID, 9)
#define M4U_PORT_L12_FDVT_2ND_RDA_0		MTK_M4U_ID(SMI_L12_ID, 10)
#define M4U_PORT_L12_FDVT_2ND_RDB_0		MTK_M4U_ID(SMI_L12_ID, 11)
#define M4U_PORT_L12_FDVT_2ND_WRA_0		MTK_M4U_ID(SMI_L12_ID, 12)
#define M4U_PORT_L12_FDVT_2ND_WRB_0		MTK_M4U_ID(SMI_L12_ID, 13)
#define M4U_PORT_L12_DHZEI_E1			MTK_M4U_ID(SMI_L12_ID, 14)
#define M4U_PORT_L12_DHZEO_E1			MTK_M4U_ID(SMI_L12_ID, 15)

/* LARB 13 -- CAM-1 */
#define M4U_PORT_L13_CAMSV_CQI_E1		MTK_M4U_ID(SMI_L13_ID, 0)
#define M4U_PORT_L13_CAMSV_CQI_E2		MTK_M4U_ID(SMI_L13_ID, 1)
#define M4U_PORT_L13_GCAMSV_A_IMGO_1		MTK_M4U_ID(SMI_L13_ID, 2)
#define M4U_PORT_L13_GCAMSV_C_IMGO_1		MTK_M4U_ID(SMI_L13_ID, 3)
#define M4U_PORT_L13_GCAMSV_A_IMGO_2		MTK_M4U_ID(SMI_L13_ID, 4)
#define M4U_PORT_L13_GCAMSV_C_IMGO_2		MTK_M4U_ID(SMI_L13_ID, 5)
#define M4U_PORT_L13_PDAI_A_0			MTK_M4U_ID(SMI_L13_ID, 6)
#define M4U_PORT_L13_PDAI_A_1			MTK_M4U_ID(SMI_L13_ID, 7)
#define M4U_PORT_L13_CAMSV_CQI_B_E1		MTK_M4U_ID(SMI_L13_ID, 8)
#define M4U_PORT_L13_CAMSV_CQI_B_E2		MTK_M4U_ID(SMI_L13_ID, 9)
#define M4U_PORT_L13_CAMSV_CQI_C_E1		MTK_M4U_ID(SMI_L13_ID, 10)
#define M4U_PORT_L13_CAMSV_CQI_C_E2		MTK_M4U_ID(SMI_L13_ID, 11)
#define M4U_PORT_L13_GCAMSV_E_IMGO_1		MTK_M4U_ID(SMI_L13_ID, 12)
#define M4U_PORT_L13_GCAMSV_E_IMGO_2		MTK_M4U_ID(SMI_L13_ID, 13)
#define M4U_PORT_L13_GCAMSV_A_UFEO_1		MTK_M4U_ID(SMI_L13_ID, 14)
#define M4U_PORT_L13_GCAMSV_C_UFEO_1		MTK_M4U_ID(SMI_L13_ID, 15)
#define M4U_PORT_L13_GCAMSV_A_UFEO_2		MTK_M4U_ID(SMI_L13_ID, 16)
#define M4U_PORT_L13_GCAMSV_C_UFEO_2		MTK_M4U_ID(SMI_L13_ID, 17)
#define M4U_PORT_L13_GCAMSV_E_UFEO_1		MTK_M4U_ID(SMI_L13_ID, 18)
#define M4U_PORT_L13_GCAMSV_E_UFEO_2		MTK_M4U_ID(SMI_L13_ID, 19)
#define M4U_PORT_L13_GCAMSV_G_IMGO_1		MTK_M4U_ID(SMI_L13_ID, 20)
#define M4U_PORT_L13_GCAMSV_G_IMGO_2		MTK_M4U_ID(SMI_L13_ID, 21)
#define M4U_PORT_L13_PDAO_A			MTK_M4U_ID(SMI_L13_ID, 22)
#define M4U_PORT_L13_PDAO_C			MTK_M4U_ID(SMI_L13_ID, 23)

/* LARB 14 -- CAM-1 */
#define M4U_PORT_L14_GCAMSV_B_IMGO_1		MTK_M4U_ID(SMI_L14_ID, 0)
#define M4U_PORT_L14_GCAMSV_B_IMGO_2		MTK_M4U_ID(SMI_L14_ID, 1)
#define M4U_PORT_L14_SCAMSV_A_IMGO_1		MTK_M4U_ID(SMI_L14_ID, 2)
#define M4U_PORT_L14_SCAMSV_A_IMGO_2		MTK_M4U_ID(SMI_L14_ID, 3)
#define M4U_PORT_L14_SCAMSV_B_IMGO_1		MTK_M4U_ID(SMI_L14_ID, 4)
#define M4U_PORT_L14_SCAMSV_B_IMGO_2		MTK_M4U_ID(SMI_L14_ID, 5)
#define M4U_PORT_L14_PDAI_B_0			MTK_M4U_ID(SMI_L14_ID, 6)
#define M4U_PORT_L14_PDAI_B_1			MTK_M4U_ID(SMI_L14_ID, 7)
#define M4U_PORT_L14_GCAMSV_D_IMGO_1		MTK_M4U_ID(SMI_L14_ID, 8)
#define M4U_PORT_L14_GCAMSV_D_IMGO_2		MTK_M4U_ID(SMI_L14_ID, 9)
#define M4U_PORT_L14_GCAMSV_F_IMGO_1		MTK_M4U_ID(SMI_L14_ID, 10)
#define M4U_PORT_L14_GCAMSV_F_IMGO_2		MTK_M4U_ID(SMI_L14_ID, 11)
#define M4U_PORT_L14_GCAMSV_H_IMGO_1		MTK_M4U_ID(SMI_L14_ID, 12)
#define M4U_PORT_L14_GCAMSV_H_IMGO_2		MTK_M4U_ID(SMI_L14_ID, 13)
#define M4U_PORT_L14_GCAMSV_B_UFEO_1		MTK_M4U_ID(SMI_L14_ID, 14)
#define M4U_PORT_L14_GCAMSV_B_UFEO_2		MTK_M4U_ID(SMI_L14_ID, 15)
#define M4U_PORT_L14_GCAMSV_D_UFEO_1		MTK_M4U_ID(SMI_L14_ID, 16)
#define M4U_PORT_L14_GCAMSV_D_UFEO_2		MTK_M4U_ID(SMI_L14_ID, 17)
#define M4U_PORT_L14_PDAO_B			MTK_M4U_ID(SMI_L14_ID, 18)
#define M4U_PORT_L14_IPUI			MTK_M4U_ID(SMI_L14_ID, 19)
#define M4U_PORT_L14_IPUO			MTK_M4U_ID(SMI_L14_ID, 20)
#define M4U_PORT_L14_IPU3O			MTK_M4U_ID(SMI_L14_ID, 21)
#define M4U_PORT_L14_FAKE			MTK_M4U_ID(SMI_L14_ID, 22)

/* LARB 15 -- IMG-D */
#define M4U_PORT_L15_VIPI_D1			MTK_M4U_ID(SMI_L15_ID, 0)
#define M4U_PORT_L15_VIPBI_D1			MTK_M4U_ID(SMI_L15_ID, 1)
#define M4U_PORT_L15_SMTI_D6			MTK_M4U_ID(SMI_L15_ID, 2)
#define M4U_PORT_L15_TNCSTI_D1			MTK_M4U_ID(SMI_L15_ID, 3)
#define M4U_PORT_L15_TNCSTI_D4			MTK_M4U_ID(SMI_L15_ID, 4)
#define M4U_PORT_L15_SMTI_D4			MTK_M4U_ID(SMI_L15_ID, 5)
#define M4U_PORT_L15_IMG3O_D1			MTK_M4U_ID(SMI_L15_ID, 6)
#define M4U_PORT_L15_IMG3BO_D1			MTK_M4U_ID(SMI_L15_ID, 7)
#define M4U_PORT_L15_IMG3CO_D1			MTK_M4U_ID(SMI_L15_ID, 8)
#define M4U_PORT_L15_IMG2O_D1			MTK_M4U_ID(SMI_L15_ID, 9)
#define M4U_PORT_L15_SMTI_D9			MTK_M4U_ID(SMI_L15_ID, 10)
#define M4U_PORT_L15_SMTO_D4			MTK_M4U_ID(SMI_L15_ID, 11)
#define M4U_PORT_L15_FEO_D1			MTK_M4U_ID(SMI_L15_ID, 12)
#define M4U_PORT_L15_TNCSO_D1			MTK_M4U_ID(SMI_L15_ID, 13)
#define M4U_PORT_L15_TNCSTO_D1			MTK_M4U_ID(SMI_L15_ID, 14)
#define M4U_PORT_L15_SMTO_D6			MTK_M4U_ID(SMI_L15_ID, 15)
#define M4U_PORT_L15_SMTO_D9			MTK_M4U_ID(SMI_L15_ID, 16)
#define M4U_PORT_L15_TNCO_D1			MTK_M4U_ID(SMI_L15_ID, 17)
#define M4U_PORT_L15_TNCO_D1_N			MTK_M4U_ID(SMI_L15_ID, 18)

/* LARB 16A -- CAM */
#define M4U_PORT_L16A_IMGO_R1			MTK_M4U_ID(SMI_L16A_ID, 0)
#define M4U_PORT_L16A_CQI_R1			MTK_M4U_ID(SMI_L16A_ID, 1)
#define M4U_PORT_L16A_CQI_R2			MTK_M4U_ID(SMI_L16A_ID, 2)
#define M4U_PORT_L16A_BPCI_R1			MTK_M4U_ID(SMI_L16A_ID, 3)
#define M4U_PORT_L16A_LSCI_R1			MTK_M4U_ID(SMI_L16A_ID, 4)
#define M4U_PORT_L16A_RAWI_R2			MTK_M4U_ID(SMI_L16A_ID, 5)
#define M4U_PORT_L16A_RAWI_R3			MTK_M4U_ID(SMI_L16A_ID, 6)
#define M4U_PORT_L16A_UFDI_R2			MTK_M4U_ID(SMI_L16A_ID, 7)
#define M4U_PORT_L16A_UFDI_R3			MTK_M4U_ID(SMI_L16A_ID, 8)
#define M4U_PORT_L16A_RAWI_R4			MTK_M4U_ID(SMI_L16A_ID, 9)
#define M4U_PORT_L16A_RAWI_R5			MTK_M4U_ID(SMI_L16A_ID, 10)
#define M4U_PORT_L16A_AAI_R1			MTK_M4U_ID(SMI_L16A_ID, 11)
#define M4U_PORT_L16A_UFDI_R5			MTK_M4U_ID(SMI_L16A_ID, 12)
#define M4U_PORT_L16A_FHO_R1			MTK_M4U_ID(SMI_L16A_ID, 13)
#define M4U_PORT_L16A_AAO_R1			MTK_M4U_ID(SMI_L16A_ID, 14)
#define M4U_PORT_L16A_TSFSO_R1			MTK_M4U_ID(SMI_L16A_ID, 15)
#define M4U_PORT_L16A_FLKO_R1			MTK_M4U_ID(SMI_L16A_ID, 16)

/* LARB 16B -- CAM */
#define M4U_PORT_L16B_IMGO_R1			MTK_M4U_ID(SMI_L16B_ID, 0)
#define M4U_PORT_L16B_CQI_R1			MTK_M4U_ID(SMI_L16B_ID, 1)
#define M4U_PORT_L16B_CQI_R2			MTK_M4U_ID(SMI_L16B_ID, 2)
#define M4U_PORT_L16B_BPCI_R1			MTK_M4U_ID(SMI_L16B_ID, 3)
#define M4U_PORT_L16B_LSCI_R1			MTK_M4U_ID(SMI_L16B_ID, 4)
#define M4U_PORT_L16B_RAWI_R2			MTK_M4U_ID(SMI_L16B_ID, 5)
#define M4U_PORT_L16B_RAWI_R3			MTK_M4U_ID(SMI_L16B_ID, 6)
#define M4U_PORT_L16B_UFDI_R2			MTK_M4U_ID(SMI_L16B_ID, 7)
#define M4U_PORT_L16B_UFDI_R3			MTK_M4U_ID(SMI_L16B_ID, 8)
#define M4U_PORT_L16B_RAWI_R4			MTK_M4U_ID(SMI_L16B_ID, 9)
#define M4U_PORT_L16B_RAWI_R5			MTK_M4U_ID(SMI_L16B_ID, 10)
#define M4U_PORT_L16B_AAI_R1			MTK_M4U_ID(SMI_L16B_ID, 11)
#define M4U_PORT_L16B_UFDI_R5			MTK_M4U_ID(SMI_L16B_ID, 12)
#define M4U_PORT_L16B_FHO_R1			MTK_M4U_ID(SMI_L16B_ID, 13)
#define M4U_PORT_L16B_AAO_R1			MTK_M4U_ID(SMI_L16B_ID, 14)
#define M4U_PORT_L16B_TSFSO_R1			MTK_M4U_ID(SMI_L16B_ID, 15)
#define M4U_PORT_L16B_FLKO_R1			MTK_M4U_ID(SMI_L16B_ID, 16)

/* LARB 17A -- CAM */
#define M4U_PORT_L17A_YUVO_R1			MTK_M4U_ID(SMI_L17A_ID, 0)
#define M4U_PORT_L17A_YUVO_R3			MTK_M4U_ID(SMI_L17A_ID, 1)
#define M4U_PORT_L17A_YUVCO_R1			MTK_M4U_ID(SMI_L17A_ID, 2)
#define M4U_PORT_L17A_YUVO_R2			MTK_M4U_ID(SMI_L17A_ID, 3)
#define M4U_PORT_L17A_RZH1N2TO_R1		MTK_M4U_ID(SMI_L17A_ID, 4)
#define M4U_PORT_L17A_DRZS4NO_R1		MTK_M4U_ID(SMI_L17A_ID, 5)
#define M4U_PORT_L17A_TNCSO_R1			MTK_M4U_ID(SMI_L17A_ID, 6)

/* LARB 17B -- CAM */
#define M4U_PORT_L17B_YUVO_R1			MTK_M4U_ID(SMI_L17B_ID, 0)
#define M4U_PORT_L17B_YUVO_R3			MTK_M4U_ID(SMI_L17B_ID, 1)
#define M4U_PORT_L17B_YUVCO_R1			MTK_M4U_ID(SMI_L17B_ID, 2)
#define M4U_PORT_L17B_YUVO_R2			MTK_M4U_ID(SMI_L17B_ID, 3)
#define M4U_PORT_L17B_RZH1N2TO_R1		MTK_M4U_ID(SMI_L17B_ID, 4)
#define M4U_PORT_L17B_DRZS4NO_R1		MTK_M4U_ID(SMI_L17B_ID, 5)
#define M4U_PORT_L17B_TNCSO_R1			MTK_M4U_ID(SMI_L17B_ID, 6)

/* LARB 19 -- VENC */
#define M4U_PORT_L19_VENC_RCPU			MTK_M4U_ID(SMI_L19_ID, 0)
#define M4U_PORT_L19_VENC_REC			MTK_M4U_ID(SMI_L19_ID, 1)
#define M4U_PORT_L19_VENC_BSDMA			MTK_M4U_ID(SMI_L19_ID, 2)
#define M4U_PORT_L19_VENC_SV_COMV		MTK_M4U_ID(SMI_L19_ID, 3)
#define M4U_PORT_L19_VENC_RD_COMV		MTK_M4U_ID(SMI_L19_ID, 4)
#define M4U_PORT_L19_VENC_NBM_RDMA		MTK_M4U_ID(SMI_L19_ID, 5)
#define M4U_PORT_L19_VENC_NBM_RDMA_LITE		MTK_M4U_ID(SMI_L19_ID, 6)
#define M4U_PORT_L19_JPGENC_Y_RDMA		MTK_M4U_ID(SMI_L19_ID, 7)
#define M4U_PORT_L19_JPGENC_C_RDMA		MTK_M4U_ID(SMI_L19_ID, 8)
#define M4U_PORT_L19_JPGENC_Q_TABLE		MTK_M4U_ID(SMI_L19_ID, 9)
#define M4U_PORT_L19_VENC_SUB_W_LUMA		MTK_M4U_ID(SMI_L19_ID, 10)
#define M4U_PORT_L19_VENC_FCS_NBM_RDMA		MTK_M4U_ID(SMI_L19_ID, 11)
#define M4U_PORT_L19_JPGENC_BSDMA		MTK_M4U_ID(SMI_L19_ID, 12)
#define M4U_PORT_L19_JPGDEC_WDMA_0		MTK_M4U_ID(SMI_L19_ID, 13)
#define M4U_PORT_L19_JPGDEC_BSDMA_0		MTK_M4U_ID(SMI_L19_ID, 14)
#define M4U_PORT_L19_VENC_NBM_WDMA		MTK_M4U_ID(SMI_L19_ID, 15)
#define M4U_PORT_L19_VENC_NBM_WDMA_LITE		MTK_M4U_ID(SMI_L19_ID, 16)
#define M4U_PORT_L19_VENC_FCS_NBM_WDMA		MTK_M4U_ID(SMI_L19_ID, 17)
#define M4U_PORT_L19_JPGDEC_WDMA_1		MTK_M4U_ID(SMI_L19_ID, 18)
#define M4U_PORT_L19_JPGDEC_BSDMA_1		MTK_M4U_ID(SMI_L19_ID, 19)
#define M4U_PORT_L19_JPGDEC_HUFF_OFFSET_1	MTK_M4U_ID(SMI_L19_ID, 20)
#define M4U_PORT_L19_JPGDEC_HUFF_OFFSET_0	MTK_M4U_ID(SMI_L19_ID, 21)
#define M4U_PORT_L19_VENC_CUR_LUMA		MTK_M4U_ID(SMI_L19_ID, 22)
#define M4U_PORT_L19_VENC_CUR_CHROMA		MTK_M4U_ID(SMI_L19_ID, 23)
#define M4U_PORT_L19_VENC_REF_LUMA		MTK_M4U_ID(SMI_L19_ID, 24)
#define M4U_PORT_L19_VENC_REF_CHROMA		MTK_M4U_ID(SMI_L19_ID, 25)
#define M4U_PORT_L19_VENC_SUB_R_LUMA		MTK_M4U_ID(SMI_L19_ID, 26)

/* LARB 21 -- VDEC-CORE0 */
#define M4U_PORT_L21_HW_VDEC_MC_EXT		MTK_M4U_ID(SMI_L21_ID, 0)
#define M4U_PORT_L21_HW_VDEC_UFO_EXT		MTK_M4U_ID(SMI_L21_ID, 1)
#define M4U_PORT_L21_HW_VDEC_PP_EXT		MTK_M4U_ID(SMI_L21_ID, 2)
#define M4U_PORT_L21_HW_VDEC_PRED_RD_EXT	MTK_M4U_ID(SMI_L21_ID, 3)
#define M4U_PORT_L21_HW_VDEC_PRED_WR_EXT	MTK_M4U_ID(SMI_L21_ID, 4)
#define M4U_PORT_L21_HW_VDEC_PPWRAP_EXT		MTK_M4U_ID(SMI_L21_ID, 5)
#define M4U_PORT_L21_HW_VDEC_TILE_EXT		MTK_M4U_ID(SMI_L21_ID, 6)
#define M4U_PORT_L21_HW_VDEC_VLD_EXT		MTK_M4U_ID(SMI_L21_ID, 7)
#define M4U_PORT_L21_HW_VDEC_VLD2_EXT		MTK_M4U_ID(SMI_L21_ID, 8)
#define M4U_PORT_L21_HW_VDEC_AVC_MV_EXT		MTK_M4U_ID(SMI_L21_ID, 9)
#define M4U_PORT_L21_HW_VDEC_UFO_EXT_C		MTK_M4U_ID(SMI_L21_ID, 10)

/* LARB 23 -- VDEC-SOC */
#define M4U_PORT_L23_HW_VDEC_LAT0_VLD_EXT	MTK_M4U_ID(SMI_L23_ID, 0)
#define M4U_PORT_L23_HW_VDEC_LAT0_VLD2_EXT	MTK_M4U_ID(SMI_L23_ID, 1)
#define M4U_PORT_L23_HW_VDEC_LAT0_AVC_MV_EXT	MTK_M4U_ID(SMI_L23_ID, 2)
#define M4U_PORT_L23_HW_VDEC_LAT0_PRED_RD_EXT	MTK_M4U_ID(SMI_L23_ID, 3)
#define M4U_PORT_L23_HW_VDEC_LAT0_TILE_EXT	MTK_M4U_ID(SMI_L23_ID, 4)
#define M4U_PORT_L23_HW_VDEC_LAT0_WDMA_EXT	MTK_M4U_ID(SMI_L23_ID, 5)
#define M4U_PORT_L23_HW_VDEC_UFO_ENC_EXT	MTK_M4U_ID(SMI_L23_ID, 6)
#define M4U_PORT_L23_HW_VDEC_UFO_ENC_EXT_C	MTK_M4U_ID(SMI_L23_ID, 7)
#define M4U_PORT_L23_HW_VDEC_MC_EXT_C		MTK_M4U_ID(SMI_L23_ID, 8)

/* LARB 27 -- CCU */
#define M4U_PORT_L27_CCUI			MTK_M4U_ID(SMI_L27_ID, 0)
#define M4U_PORT_L27_CCUO			MTK_M4U_ID(SMI_L27_ID, 1)
#define M4U_PORT_L27_CCUI2			MTK_M4U_ID(SMI_L27_ID, 2)
#define M4U_PORT_L27_CCUO2			MTK_M4U_ID(SMI_L27_ID, 3)

/* LARB 28 -- AXI-CCU */
#define M4U_PORT_L28_CCU_AXI_0			MTK_M4U_ID(SMI_L28_ID, 0)

/* APU 0 */
#define M4U_PORT_L0_APU_CODE			MTK_M4U_ID(APU_L0_ID, 0)
#define M4U_PORT_L0_APU_DATA			MTK_M4U_ID(APU_L0_ID, 1)
#define M4U_PORT_L0_APU_SECURE			MTK_M4U_ID(APU_L0_ID, 2)
#define M4U_PORT_L0_APU_VLM			MTK_M4U_ID(APU_L0_ID, 3)
/* APU 1 */
#define M4U_PORT_L1_APU_CODE			MTK_M4U_ID(APU_L1_ID, 0)
#define M4U_PORT_L1_APU_DATA			MTK_M4U_ID(APU_L1_ID, 1)
#define M4U_PORT_L1_APU_SECURE			MTK_M4U_ID(APU_L1_ID, 2)
#define M4U_PORT_L1_APU_VLM			MTK_M4U_ID(APU_L1_ID, 3)

/* infra/peri */
#define IFR_IOMMU_PORT_PCIE_0			MTK_IFAIOMMU_PERI_ID(0)

#endif
