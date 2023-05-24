// SPDX-License-Identifier: GPL-2.0
//
// mt8195-mt6359-demo.c  --
//	MT8195-MT6359-DEMO ALSA SoC machine driver
//
// Copyright (c) 2022 baylibre
// Author: Nicolas Belin <nbelin@baylibre.com>
//

#include <linux/input.h>
#include <linux/module.h>
#include <linux/pm_runtime.h>
#include <sound/jack.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include "../../codecs/mt6359.h"
#include "../common/mtk-afe-platform-driver.h"
#include "../common/mtk-soundcard-driver.h"
#include "mt8195-afe-clk.h"
#include "mt8195-afe-common.h"

#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of.h>


#ifdef CONFIG_ARCH_ADLINKTECH 
#define WM8960_CODEC_DAI		"wm8960-hifi"
#define WM8960_DEV0_NAME		"wm8960.3-001a"
#define TLV320AIC3X_CODEC_DAI	"tlv320aic3x-hifi"
#define TLV320AIC3X_DEV0_NAME	"tlv320aic3x.3-0018"
#endif

static const struct snd_soc_dapm_widget
	mt8195_mt6359_demo_widgets[] = {
#ifdef CONFIG_ARCH_ADLINKTECH
	SND_SOC_DAPM_HP("Headphone", NULL),
	SND_SOC_DAPM_MIC("AMIC", NULL),
#else
	SND_SOC_DAPM_HP("Headphone Jack", NULL),
	SND_SOC_DAPM_MIC("Headset Mic", NULL),
#endif
};

static const struct snd_soc_dapm_route mt8195_mt6359_demo_routes[] = {
	{ "Headphone Jack", NULL, "AIF1 Playback" },
	{ "AIF1 Capture", NULL, "Headset Mic" },
};

#ifdef CONFIG_ARCH_ADLINKTECH
static const struct snd_soc_dapm_route tlv320aic3x_routes[] = {
	{ "Headphone", NULL, "HPLOUT" },
	{ "Headphone", NULL, "HPROUT" },
	{ "MIC3L", NULL, "AMIC" },
	{ "MIC3R", NULL, "AMIC" },
};

static const struct snd_soc_dapm_route wm8960_routes[] = {
	{ "Headphone", NULL, "HP_L" },
	{ "Headphone", NULL, "HP_R" },
	{ "LINPUT1", NULL, "AMIC" },
	{ "RINPUT1", NULL, "AMIC" },
};

static const struct snd_kcontrol_new mt8195_mt6359_demo_controls[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("AMIC"),
};

static struct snd_soc_dai_link_component tlv320aic3x_codecs = {
	.name = TLV320AIC3X_DEV0_NAME,
	.dai_name = TLV320AIC3X_CODEC_DAI,
};
static struct snd_soc_dai_link_component wm8960_codecs = {
	.name = WM8960_DEV0_NAME,
	.dai_name = WM8960_CODEC_DAI,
};

enum {
    CODEC_TLV320,
    CODEC_WM8960,
};

struct codec_config {
    struct snd_soc_dai_link_component *codecs;
    const struct snd_soc_dapm_route *routes;
    int num_routes;
};

static struct codec_config codecs_config[] = {
    [CODEC_TLV320] = {
        .codecs = &tlv320aic3x_codecs,
        .routes = tlv320aic3x_routes,
        .num_routes = ARRAY_SIZE(tlv320aic3x_routes),
    },
    [CODEC_WM8960] = {
        .codecs = &wm8960_codecs,
        .routes = wm8960_routes,
        .num_routes = ARRAY_SIZE(wm8960_routes),
    },
    //... add other codecs here
};
#endif

static int mt8195_etdm_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_card *card = rtd->card;
	struct snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	unsigned int rate = params_rate(params);
#ifdef CONFIG_ARCH_ADLINKTECH
	struct snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	unsigned int mclk_fs_ratio = 256;
#else
	unsigned int mclk_fs_ratio = 128;
#endif
	unsigned int mclk_fs = rate * mclk_fs_ratio;
	int ret;

	ret = snd_soc_dai_set_sysclk(cpu_dai, 0, mclk_fs, SND_SOC_CLOCK_OUT);
	if (ret) {
		dev_err(card->dev, "failed to set sysclk\n");
		return ret;
	}
#ifdef CONFIG_ARCH_ADLINKTECH
	ret = snd_soc_dai_set_sysclk(codec_dai, 0, mclk_fs, SND_SOC_CLOCK_IN);
	if (ret) {
		dev_err(card->dev, "failed to set codec sysclk\n");
		return ret;
	}
#endif

	return 0;
}

static const struct snd_soc_ops mt8195_etdm_ops = {
	.hw_params = mt8195_etdm_hw_params,
};

#define CKSYS_AUD_TOP_CFG 0x032c
#define CKSYS_AUD_TOP_MON 0x0330

static int mt8195_mt6359_mtkaif_calibration(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *cmpnt_afe =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	struct snd_soc_component *cmpnt_codec =
		asoc_rtd_to_codec(rtd, 0)->component;
	struct mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt_afe);
	struct mt8195_afe_private *afe_priv = afe->platform_priv;
	struct mtkaif_param *param = &afe_priv->mtkaif_params;
	int phase;
	unsigned int monitor = 0;
	int mtkaif_calibration_num_phase;
	int test_done_1, test_done_2, test_done_3;
	int cycle_1, cycle_2, cycle_3;
	int prev_cycle_1, prev_cycle_2, prev_cycle_3;
	int chosen_phase_1, chosen_phase_2, chosen_phase_3;
	int counter;
	bool mtkaif_calibration_ok;
	int mtkaif_chosen_phase[MT8195_MTKAIF_MISO_NUM];
	int mtkaif_phase_cycle[MT8195_MTKAIF_MISO_NUM];
	int i;

	dev_info(afe->dev, "%s(), start\n", __func__);

	param->mtkaif_calibration_ok = false;
	for (i = 0; i < MT8195_MTKAIF_MISO_NUM; i++) {
		param->mtkaif_chosen_phase[i] = -1;
		param->mtkaif_phase_cycle[i] = 0;
		mtkaif_chosen_phase[i] = -1;
		mtkaif_phase_cycle[i] = 0;
	}

	if (IS_ERR(afe_priv->topckgen)) {
		dev_info(afe->dev, "%s() Cannot find topckgen controller\n",
			 __func__);
		return 0;
	}

	pm_runtime_get_sync(afe->dev);
	mt6359_mtkaif_calibration_enable(cmpnt_codec);

	/* set test type to synchronizer pulse */
	regmap_update_bits(afe_priv->topckgen,
			   CKSYS_AUD_TOP_CFG, 0xffff, 0x4);
	mtkaif_calibration_num_phase = 42;	/* mt6359: 0 ~ 42 */
	mtkaif_calibration_ok = true;

	for (phase = 0;
	     phase <= mtkaif_calibration_num_phase && mtkaif_calibration_ok;
	     phase++) {
		mt6359_set_mtkaif_calibration_phase(cmpnt_codec,
						    phase, phase, phase);

		regmap_update_bits(afe_priv->topckgen,
				   CKSYS_AUD_TOP_CFG, 0x1, 0x1);

		test_done_1 = 0;
		test_done_2 = 0;
		test_done_3 = 0;
		cycle_1 = -1;
		cycle_2 = -1;
		cycle_3 = -1;
		counter = 0;
		while (!(test_done_1 & test_done_2 & test_done_3)) {
			regmap_read(afe_priv->topckgen,
				    CKSYS_AUD_TOP_MON, &monitor);
			test_done_1 = (monitor >> 28) & 0x1;
			test_done_2 = (monitor >> 29) & 0x1;
			test_done_3 = (monitor >> 30) & 0x1;
			if (test_done_1 == 1)
				cycle_1 = monitor & 0xf;

			if (test_done_2 == 1)
				cycle_2 = (monitor >> 4) & 0xf;

			if (test_done_3 == 1)
				cycle_3 = (monitor >> 8) & 0xf;

			/* handle if never test done */
			if (++counter > 10000) {
				dev_info(afe->dev, "%s(), test fail, cycle_1 %d, cycle_2 %d, cycle_3 %d, monitor 0x%x\n",
					 __func__,
					 cycle_1, cycle_2, cycle_3, monitor);
				mtkaif_calibration_ok = false;
				break;
			}
		}

		if (phase == 0) {
			prev_cycle_1 = cycle_1;
			prev_cycle_2 = cycle_2;
			prev_cycle_3 = cycle_3;
		}

		if (cycle_1 != prev_cycle_1 &&
		    mtkaif_chosen_phase[MT8195_MTKAIF_MISO_0] < 0) {
			mtkaif_chosen_phase[MT8195_MTKAIF_MISO_0] = phase - 1;
			mtkaif_phase_cycle[MT8195_MTKAIF_MISO_0] = prev_cycle_1;
		}

		if (cycle_2 != prev_cycle_2 &&
		    mtkaif_chosen_phase[MT8195_MTKAIF_MISO_1] < 0) {
			mtkaif_chosen_phase[MT8195_MTKAIF_MISO_1] = phase - 1;
			mtkaif_phase_cycle[MT8195_MTKAIF_MISO_1] = prev_cycle_2;
		}

		if (cycle_3 != prev_cycle_3 &&
		    mtkaif_chosen_phase[MT8195_MTKAIF_MISO_2] < 0) {
			mtkaif_chosen_phase[MT8195_MTKAIF_MISO_2] = phase - 1;
			mtkaif_phase_cycle[MT8195_MTKAIF_MISO_2] = prev_cycle_3;
		}

		regmap_update_bits(afe_priv->topckgen,
				   CKSYS_AUD_TOP_CFG, 0x1, 0x0);

		if (mtkaif_chosen_phase[MT8195_MTKAIF_MISO_0] >= 0 &&
		    mtkaif_chosen_phase[MT8195_MTKAIF_MISO_1] >= 0 &&
		    mtkaif_chosen_phase[MT8195_MTKAIF_MISO_2] >= 0)
			break;
	}

	if (mtkaif_chosen_phase[MT8195_MTKAIF_MISO_0] < 0) {
		mtkaif_calibration_ok = false;
		chosen_phase_1 = 0;
	} else {
		chosen_phase_1 = mtkaif_chosen_phase[MT8195_MTKAIF_MISO_0];
	}

	if (mtkaif_chosen_phase[MT8195_MTKAIF_MISO_1] < 0) {
		mtkaif_calibration_ok = false;
		chosen_phase_2 = 0;
	} else {
		chosen_phase_2 = mtkaif_chosen_phase[MT8195_MTKAIF_MISO_1];
	}

	if (mtkaif_chosen_phase[MT8195_MTKAIF_MISO_2] < 0) {
		mtkaif_calibration_ok = false;
		chosen_phase_3 = 0;
	} else {
		chosen_phase_3 = mtkaif_chosen_phase[MT8195_MTKAIF_MISO_2];
	}

	mt6359_set_mtkaif_calibration_phase(cmpnt_codec,
					    chosen_phase_1,
					    chosen_phase_2,
					    chosen_phase_3);

	mt6359_mtkaif_calibration_disable(cmpnt_codec);
	pm_runtime_put(afe->dev);

	param->mtkaif_calibration_ok = mtkaif_calibration_ok;
	param->mtkaif_chosen_phase[MT8195_MTKAIF_MISO_0] = chosen_phase_1;
	param->mtkaif_chosen_phase[MT8195_MTKAIF_MISO_1] = chosen_phase_2;
	param->mtkaif_chosen_phase[MT8195_MTKAIF_MISO_2] = chosen_phase_3;
	for (i = 0; i < MT8195_MTKAIF_MISO_NUM; i++)
		param->mtkaif_phase_cycle[i] = mtkaif_phase_cycle[i];

	dev_info(afe->dev, "%s(), end, calibration ok %d\n",
		 __func__, param->mtkaif_calibration_ok);

	return 0;
}

static int mt8195_mt6359_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *cmpnt_codec =
		asoc_rtd_to_codec(rtd, 0)->component;

	/* set mtkaif protocol */
	mt6359_set_mtkaif_protocol(cmpnt_codec,
				   MT6359_MTKAIF_PROTOCOL_2_CLK_P2);

	/* mtkaif calibration */
	mt8195_mt6359_mtkaif_calibration(rtd);

	return 0;
}

static int mt8195_etdm_hw_params_fixup(struct snd_soc_pcm_runtime *rtd,
				       struct snd_pcm_hw_params *params)
{
	/* fix BE i2s format to 32bit, clean param mask first */
	snd_mask_reset_range(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT),
			     0, SNDRV_PCM_FORMAT_LAST);
#ifdef CONFIG_ARCH_ADLINKTECH
	params_set_format(params, SNDRV_PCM_FORMAT_S16_LE);
#else
	params_set_format(params, SNDRV_PCM_FORMAT_S24_LE);
#endif
	return 0;
}

static int mt8195_dptx_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	unsigned int rate = params_rate(params);
	unsigned int mclk_fs_ratio = 256;
	unsigned int mclk_fs = rate * mclk_fs_ratio;

	return snd_soc_dai_set_sysclk(cpu_dai, 0, mclk_fs,
				      SND_SOC_CLOCK_OUT);
}

static const struct snd_soc_ops mt8195_dptx_ops = {
	.hw_params = mt8195_dptx_hw_params,
};

static int mt8195_dptx_hw_params_fixup(struct snd_soc_pcm_runtime *rtd,
				       struct snd_pcm_hw_params *params)
{
	/* fix BE i2s format to S24_LE, clean param mask first */
	snd_mask_reset_range(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT),
			     0, (__force unsigned int)SNDRV_PCM_FORMAT_LAST);

	params_set_format(params, SNDRV_PCM_FORMAT_S24_LE);

	return 0;
}

enum {
	DAI_LINK_DL2_FE,
	DAI_LINK_DL3_FE,
	DAI_LINK_DL6_FE,
	DAI_LINK_DL7_FE,
	DAI_LINK_DL8_FE,
	DAI_LINK_DL10_FE,
	DAI_LINK_DL11_FE,
	DAI_LINK_UL1_FE,
	DAI_LINK_UL2_FE,
	DAI_LINK_UL3_FE,
	DAI_LINK_UL4_FE,
	DAI_LINK_UL5_FE,
	DAI_LINK_UL6_FE,
	DAI_LINK_UL8_FE,
	DAI_LINK_UL9_FE,
	DAI_LINK_UL10_FE,
	DAI_LINK_DL_SRC_BE,
	DAI_LINK_DPTX_BE,
	DAI_LINK_ETDM2_IN_BE,
	DAI_LINK_ETDM1_OUT_BE,
	DAI_LINK_ETDM3_OUT_BE,
	DAI_LINK_UL_SRC1_BE,
	DAI_LINK_UL_SRC2_BE,
	DAI_LINK_DMIC_BE,
};

/* FE */
SND_SOC_DAILINK_DEFS(DL2_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DL3_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL3")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DL6_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL6")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DL7_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL7")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DL8_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL8")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DL10_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL10")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DL11_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL11")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL1_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL1")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL2_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL3_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL3")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL4_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL4")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL5_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL5")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL6_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL6")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL8_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL8")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL9_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL9")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL10_FE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL10")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

/* BE */
SND_SOC_DAILINK_DEFS(DL_SRC_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL_SRC")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DPTX_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DPTX")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(ETDM2_IN_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("ETDM2_IN")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
                     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(ETDM1_OUT_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("ETDM1_OUT")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(ETDM3_OUT_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("ETDM3_OUT")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL_SRC1_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL_SRC1")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(UL_SRC2_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL_SRC2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(DMIC_BE,
		     DAILINK_COMP_ARRAY(COMP_CPU("DMIC")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

static struct snd_soc_dai_link mt8195_mt6359_demo_dai_links[] = {
	/* FE */
	[DAI_LINK_DL2_FE] = {
		.name = "DL2_FE",
		.stream_name = "DL2 Playback",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL2_FE),
	},
	[DAI_LINK_DL3_FE] = {
		.name = "DL3_FE",
		.stream_name = "DL3 Playback",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL3_FE),
	},
	[DAI_LINK_DL6_FE] = {
		.name = "DL6_FE",
		.stream_name = "DL6 Playback",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL6_FE),
	},
	[DAI_LINK_DL7_FE] = {
		.name = "DL7_FE",
		.stream_name = "DL7 Playback",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_PRE,
			SND_SOC_DPCM_TRIGGER_PRE,
		},
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL7_FE),
	},
	[DAI_LINK_DL8_FE] = {
		.name = "DL8_FE",
		.stream_name = "DL8 Playback",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL8_FE),
	},
	[DAI_LINK_DL10_FE] = {
		.name = "DL10_FE",
		.stream_name = "DL10 Playback",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL10_FE),
	},
	[DAI_LINK_DL11_FE] = {
		.name = "DL11_FE",
		.stream_name = "DL11 Playback",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL11_FE),
	},
	[DAI_LINK_UL1_FE] = {
		.name = "UL1_FE",
		.stream_name = "UL1 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_PRE,
			SND_SOC_DPCM_TRIGGER_PRE,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL1_FE),
	},
	[DAI_LINK_UL2_FE] = {
		.name = "UL2_FE",
		.stream_name = "UL2 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL2_FE),
	},
	[DAI_LINK_UL3_FE] = {
		.name = "UL3_FE",
		.stream_name = "UL3 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL3_FE),
	},
	[DAI_LINK_UL4_FE] = {
		.name = "UL4_FE",
		.stream_name = "UL4 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL4_FE),
	},
	[DAI_LINK_UL5_FE] = {
		.name = "UL5_FE",
		.stream_name = "UL5 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL5_FE),
	},
	[DAI_LINK_UL6_FE] = {
		.name = "UL6_FE",
		.stream_name = "UL6 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_PRE,
			SND_SOC_DPCM_TRIGGER_PRE,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL6_FE),
	},
	[DAI_LINK_UL8_FE] = {
		.name = "UL8_FE",
		.stream_name = "UL8 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL8_FE),
	},
	[DAI_LINK_UL9_FE] = {
		.name = "UL9_FE",
		.stream_name = "UL9 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL9_FE),
	},
	[DAI_LINK_UL10_FE] = {
		.name = "UL10_FE",
		.stream_name = "UL10 Capture",
		.trigger = {
			SND_SOC_DPCM_TRIGGER_POST,
			SND_SOC_DPCM_TRIGGER_POST,
		},
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL10_FE),
	},
	/* BE */
	[DAI_LINK_DL_SRC_BE] = {
		.name = "DL_SRC_BE",
		.no_pcm = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(DL_SRC_BE),
	},
	[DAI_LINK_DPTX_BE] = {
		.name = "DPTX_BE",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ops = &mt8195_dptx_ops,
		.be_hw_params_fixup = mt8195_dptx_hw_params_fixup,
		SND_SOC_DAILINK_REG(DPTX_BE),
	},
	[DAI_LINK_ETDM2_IN_BE] = {
		.name = "ETDM2_IN_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_capture = 1,
		.ops = &mt8195_etdm_ops,
		.be_hw_params_fixup = mt8195_etdm_hw_params_fixup,
		SND_SOC_DAILINK_REG(ETDM2_IN_BE),
	},
	[DAI_LINK_ETDM1_OUT_BE] = {
		.name = "ETDM1_OUT_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_playback = 1,
		.ops = &mt8195_etdm_ops,
		.be_hw_params_fixup = mt8195_etdm_hw_params_fixup,
		SND_SOC_DAILINK_REG(ETDM1_OUT_BE),
	},
	[DAI_LINK_ETDM3_OUT_BE] = {
		.name = "ETDM3_OUT_BE",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(ETDM3_OUT_BE),
	},
	[DAI_LINK_UL_SRC1_BE] = {
		.name = "UL_SRC1_BE",
		.no_pcm = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL_SRC1_BE),
	},
	[DAI_LINK_UL_SRC2_BE] = {
		.name = "UL_SRC2_BE",
		.no_pcm = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(UL_SRC2_BE),
	},
	[DAI_LINK_DMIC_BE] = {
		.name = "DMIC_BE",
		.no_pcm = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(DMIC_BE),
	},
};

static struct snd_soc_card mt8195_mt6359_demo_soc_card = {
	.name = "mt8195_mt6359_demo",
	.owner = THIS_MODULE,
	.dai_link = mt8195_mt6359_demo_dai_links,
	.num_links = ARRAY_SIZE(mt8195_mt6359_demo_dai_links),
	.dapm_widgets = mt8195_mt6359_demo_widgets,
	.num_dapm_widgets = ARRAY_SIZE(mt8195_mt6359_demo_widgets),
	.dapm_routes = mt8195_mt6359_demo_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8195_mt6359_demo_routes),
};

static int mt8195_mt6359_demo_dev_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &mt8195_mt6359_demo_soc_card;
	struct device_node *platform_node;
	struct snd_soc_dai_link *dai_link;
	int ret, i;
#ifdef CONFIG_ARCH_ADLINKTECH
	struct device_node *np = pdev->dev.of_node;
	struct device_node *tlv320_node, *wm8960_node;
	bool tlv320_available, wm8960_available;
	tlv320_node = of_find_node_by_name(NULL, "tlv320aic310x");
	wm8960_node = of_find_node_by_name(NULL, "wm8960");
	tlv320_available = of_device_is_available(tlv320_node);
	wm8960_available = of_device_is_available(wm8960_node);
#endif
	card->dev = &pdev->dev;
#ifdef CONFIG_ARCH_ADLINKTECH
    struct codec_config *config;

    if (tlv320_available) {
        config = &codecs_config[CODEC_TLV320];
    } else if (wm8960_available) {
        config = &codecs_config[CODEC_WM8960];
    } else {
        // error handling
    }

    mt8195_mt6359_demo_dai_links[DAI_LINK_DL_SRC_BE].codecs = config->codecs;
    mt8195_mt6359_demo_dai_links[DAI_LINK_DL_SRC_BE].num_codecs = 1;
    mt8195_mt6359_demo_dai_links[DAI_LINK_ETDM2_IN_BE].codecs = config->codecs;
    mt8195_mt6359_demo_dai_links[DAI_LINK_ETDM2_IN_BE].num_codecs = 1;

    card->dapm_routes = config->routes;
    card->num_dapm_routes = config->num_routes;
#endif
	
	ret = set_card_codec_info(card);
	if (ret) {
		dev_err_probe(&pdev->dev, ret, "%s set_card_codec_info failed\n",
			     __func__);
		return ret;
	}

	ret = snd_soc_of_parse_card_name(card, "model");
	if (ret) {
		dev_err(&pdev->dev, "%s new card name parsing error %d\n",
			__func__, ret);
		return ret;
	}

	platform_node = of_parse_phandle(pdev->dev.of_node,
					 "mediatek,platform", 0);

	if (!platform_node) {
		dev_dbg(&pdev->dev, "Property 'platform' missing or invalid\n");
		return -EINVAL;
	}

	for_each_card_prelinks(card, i, dai_link) {
		if (!dai_link->platforms->name)
			dai_link->platforms->of_node = platform_node;
	}

	ret = devm_snd_soc_register_card(&pdev->dev, card);
	if (ret)
		dev_err_probe(&pdev->dev, ret, "%s snd_soc_register_card fail\n",
			     __func__);
	return ret;
}

#ifdef CONFIG_OF
static const struct of_device_id mt8195_mt6359_demo_dt_match[] = {
	{.compatible = "mediatek,mt8195_mt6359_demo",},
	{}
};
#endif

static struct platform_driver mt8195_mt6359_demo_driver = {
	.driver = {
		.name = "mt8195_mt6359_demo",
#ifdef CONFIG_OF
		.of_match_table = mt8195_mt6359_demo_dt_match,
#endif
		.pm = &snd_soc_pm_ops,
	},
	.probe = mt8195_mt6359_demo_dev_probe,
};

module_platform_driver(mt8195_mt6359_demo_driver);

/* Module information */
MODULE_DESCRIPTION("MT8195-MT6359-DEMO ALSA SoC machine driver");
MODULE_AUTHOR("Nicolas Belin <nbelin@baylibre.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("mt8195_mt6359_demo soc card");
