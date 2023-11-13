/* SPDX-License-Identifier: GPL-2.0 */
/*
 * mt8195-afe-common.h  --  Mediatek 8195 audio driver definitions
 *
 * Copyright (c) 2021 MediaTek Inc.
 * Author: Bicycle Tsai <bicycle.tsai@mediatek.com>
 *         Trevor Wu <trevor.wu@mediatek.com>
 */

#ifndef _MT_8195_AFE_COMMON_H_
#define _MT_8195_AFE_COMMON_H_

#include <sound/soc.h>
#include <linux/list.h>
#include <linux/regmap.h>
#include "../common/mtk-base-afe.h"

enum {
	MT8195_DAI_START,
	MT8195_AFE_MEMIF_START = MT8195_DAI_START,
	MT8195_AFE_MEMIF_DL2 = MT8195_AFE_MEMIF_START,
	MT8195_AFE_MEMIF_DL3,
	MT8195_AFE_MEMIF_DL6,
	MT8195_AFE_MEMIF_DL7,
	MT8195_AFE_MEMIF_DL8,
	MT8195_AFE_MEMIF_DL10,
	MT8195_AFE_MEMIF_DL11,
	MT8195_AFE_MEMIF_UL_START,
	MT8195_AFE_MEMIF_UL1 = MT8195_AFE_MEMIF_UL_START,
	MT8195_AFE_MEMIF_UL2,
	MT8195_AFE_MEMIF_UL3,
	MT8195_AFE_MEMIF_UL4,
	MT8195_AFE_MEMIF_UL5,
	MT8195_AFE_MEMIF_UL6,
	MT8195_AFE_MEMIF_UL8,
	MT8195_AFE_MEMIF_UL9,
	MT8195_AFE_MEMIF_UL10,
	MT8195_AFE_MEMIF_END,
	MT8195_AFE_MEMIF_NUM = (MT8195_AFE_MEMIF_END - MT8195_AFE_MEMIF_START),
	MT8195_AFE_IO_START = MT8195_AFE_MEMIF_END,
	MT8195_AFE_IO_DL_SRC = MT8195_AFE_IO_START,
	MT8195_AFE_IO_DMIC_IN,
	MT8195_AFE_IO_DPTX,
	MT8195_AFE_IO_ETDM_START,
	MT8195_AFE_IO_ETDM1_IN = MT8195_AFE_IO_ETDM_START,
	MT8195_AFE_IO_ETDM2_IN,
	MT8195_AFE_IO_ETDM1_OUT,
	MT8195_AFE_IO_ETDM2_OUT,
	MT8195_AFE_IO_ETDM3_OUT,
	MT8195_AFE_IO_ETDM_END,
	MT8195_AFE_IO_ETDM_NUM =
		(MT8195_AFE_IO_ETDM_END - MT8195_AFE_IO_ETDM_START),
	MT8195_AFE_IO_MULTI_IN_START = MT8195_AFE_IO_ETDM_END,
	MT8195_AFE_IO_MULTI_IN1 = MT8195_AFE_IO_MULTI_IN_START,
	MT8195_AFE_IO_MULTI_IN2,
	MT8195_AFE_IO_MULTI_IN_END,
	MT8195_AFE_IO_MULTI_IN_NUM =
		(MT8195_AFE_IO_MULTI_IN_END - MT8195_AFE_IO_MULTI_IN_START),
	MT8195_AFE_IO_PCM = MT8195_AFE_IO_MULTI_IN_END,
	MT8195_AFE_IO_UL_SRC1,
	MT8195_AFE_IO_UL_SRC2,
	MT8195_AFE_IO_END,
	MT8195_AFE_IO_NUM = (MT8195_AFE_IO_END - MT8195_AFE_IO_START),
	MT8195_DAI_END = MT8195_AFE_IO_END,
	MT8195_DAI_NUM = (MT8195_DAI_END - MT8195_DAI_START),
};

enum {
	MT8195_TOP_CG_A1SYS_TIMING,
	MT8195_TOP_CG_A2SYS_TIMING,
	MT8195_TOP_CG_26M_TIMING,
	MT8195_TOP_CG_NUM,
};

enum {
	MT8195_AFE_IRQ_1,
	MT8195_AFE_IRQ_2,
	MT8195_AFE_IRQ_3,
	MT8195_AFE_IRQ_8,
	MT8195_AFE_IRQ_9,
	MT8195_AFE_IRQ_10,
	MT8195_AFE_IRQ_13,
	MT8195_AFE_IRQ_14,
	MT8195_AFE_IRQ_15,
	MT8195_AFE_IRQ_16,
	MT8195_AFE_IRQ_17,
	MT8195_AFE_IRQ_18,
	MT8195_AFE_IRQ_19,
	MT8195_AFE_IRQ_20,
	MT8195_AFE_IRQ_21,
	MT8195_AFE_IRQ_22,
	MT8195_AFE_IRQ_23,
	MT8195_AFE_IRQ_24,
	MT8195_AFE_IRQ_25,
	MT8195_AFE_IRQ_26,
	MT8195_AFE_IRQ_27,
	MT8195_AFE_IRQ_28,
	MT8195_AFE_IRQ_NUM,
};

enum {
	MT8195_ETDM_OUT1_1X_EN = 9,
	MT8195_ETDM_OUT2_1X_EN = 10,
	MT8195_ETDM_OUT3_1X_EN = 11,
	MT8195_ETDM_IN1_1X_EN = 12,
	MT8195_ETDM_IN2_1X_EN = 13,
	MT8195_ETDM_IN1_NX_EN = 25,
	MT8195_ETDM_IN2_NX_EN = 26,
};

enum {
	MT8195_MTKAIF_MISO_0,
	MT8195_MTKAIF_MISO_1,
	MT8195_MTKAIF_MISO_2,
	MT8195_MTKAIF_MISO_NUM,
};

struct mtk_dai_memif_irq_priv {
	unsigned int asys_timing_sel;
};

struct mtkaif_param {
	bool mtkaif_calibration_ok;
	int mtkaif_chosen_phase[MT8195_MTKAIF_MISO_NUM];
	int mtkaif_phase_cycle[MT8195_MTKAIF_MISO_NUM];
	int mtkaif_dmic_on;
	int mtkaif_adda6_only;
};

struct clk;

struct mt8195_afe_private {
	struct clk **clk;
	struct clk_lookup **lookup;
	struct regmap *topckgen;
	int pm_runtime_bypass_reg_ctl;
#ifdef CONFIG_DEBUG_FS
	struct dentry **debugfs_dentry;
#endif
	int afe_on_ref_cnt;
	int top_cg_ref_cnt[MT8195_TOP_CG_NUM];
	spinlock_t afe_ctrl_lock;	/* Lock for afe control */
	struct mtk_dai_memif_irq_priv irq_priv[MT8195_AFE_IRQ_NUM];
	struct mtkaif_param mtkaif_params;

	/* dai */
	void *dai_priv[MT8195_DAI_NUM];
};

int mt8195_afe_fs_timing(unsigned int rate);
/* dai register */
int mt8195_dai_adda_register(struct mtk_base_afe *afe);
int mt8195_dai_dmic_register(struct mtk_base_afe *afe);
int mt8195_dai_etdm_register(struct mtk_base_afe *afe);
int mt8195_dai_pcm_register(struct mtk_base_afe *afe);
int mt8195_dai_multi_in_register(struct mtk_base_afe *afe);

#define MT8195_SOC_ENUM_EXT(xname, xenum, xhandler_get, xhandler_put, id) \
{ \
	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_enum_double, \
	.get = xhandler_get, .put = xhandler_put, \
	.device = id, \
	.private_value = (unsigned long)&xenum, \
}

#endif
