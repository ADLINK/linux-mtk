/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Copyright (c) 2021 BayLibre
 */
#ifndef _MTK_DP_REG_H_
#define _MTK_DP_REG_H_

#define MTK_DP_SIP_CONTROL_AARCH32 0x82000523
#define MTK_DP_SIP_ATF_VIDEO_UNMUTE 0x20
#define MTK_DP_SIP_ATF_EDP_VIDEO_UNMUTE 0x21

#define DP_PHY_GLB_BIAS_GEN_00 0x0000
#define RG_XTP_GLB_BIAS_INTR_CTRL (0x1f << 16)

#define DP_PHY_GLB_DPAUX_TX 0x0008
#define RG_CKM_PT0_CKTX_IMPSEL (0xf << 20)

#define DP_PHY_LANE_TX_0 0x104
#define RG_XTP_LN0_TX_IMPSEL_PMOS (0xf << 12)
#define RG_XTP_LN0_TX_IMPSEL_NMOS (0xf << 16)

#define DP_PHY_LANE_TX_1 0x204
#define RG_XTP_LN1_TX_IMPSEL_PMOS (0xf << 12)
#define RG_XTP_LN1_TX_IMPSEL_NMOS (0xf << 16)

#define DP_PHY_LANE_TX_2 0x304
#define RG_XTP_LN2_TX_IMPSEL_PMOS (0xf << 12)
#define RG_XTP_LN2_TX_IMPSEL_NMOS (0xf << 16)

#define DP_PHY_LANE_TX_3 0x404
#define RG_XTP_LN3_TX_IMPSEL_PMOS (0xf << 12)
#define RG_XTP_LN3_TX_IMPSEL_NMOS (0xf << 16)

#define TOP_OFFSET 0x2000
#define ENC0_OFFSET 0x3000
#define ENC1_OFFSET 0x3200
#define TRANS_OFFSET 0x3400
#define AUX_OFFSET 0x3600
#define SEC_OFFSET 0x4000

#define MTK_DP_HPD_DISCONNECT BIT(1)
#define MTK_DP_HPD_CONNECT BIT(2)
#define MTK_DP_HPD_INTERRUPT BIT(3)

#define MTK_DP_0034 0x034
#define DA_XTP_GLB_CKDET_EN_FORCE_VAL BIT(15)
#define DA_XTP_GLB_CKDET_EN_FORCE_EN BIT(14)
#define DA_CKM_INTCKTX_EN_FORCE_VAL BIT(13)
#define DA_CKM_INTCKTX_EN_FORCE_EN BIT(12)
#define DA_CKM_CKTX0_EN_FORCE_VAL BIT(11)
#define DA_CKM_CKTX0_EN_FORCE_EN BIT(10)
#define DA_CKM_XTAL_CK_FORCE_VAL BIT(9)
#define DA_CKM_XTAL_CK_FORCE_EN BIT(8)
#define DA_CKM_BIAS_LPF_EN_FORCE_VAL BIT(7)
#define DA_CKM_BIAS_LPF_EN_FORCE_EN BIT(6)
#define DA_CKM_BIAS_EN_FORCE_VAL BIT(5)
#define DA_CKM_BIAS_EN_FORCE_EN BIT(4)
#define DA_XTP_GLB_AVD10_ON_FORCE_VAL BIT(3)
#define DA_XTP_GLB_AVD10_ON_FORCE BIT(2)
#define DA_XTP_GLB_LDO_EN_FORCE_VAL BIT(1)
#define DA_XTP_GLB_LDO_EN_FORCE_EN BIT(0)

#define MTK_DP_1040 0x1040
#define RG_DPAUX_RX_VALID_DEGLITCH_EN BIT(2)
#define RG_XTP_GLB_CKDET_EN BIT(1)
#define RG_DPAUX_RX_EN BIT(0)

#define MTK_DP_ENC0_P0_3000 (ENC0_OFFSET + 0x000)
#define LANE_NUM_DP_ENC0_P0_MASK 0x3
#define VIDEO_MUTE_SW_DP_ENC0_P0_MASK 0x4
#define VIDEO_MUTE_SW_DP_ENC0_P0_SHIFT 2
#define VIDEO_MUTE_SEL_DP_ENC0_P0_MASK 0x8
#define VIDEO_MUTE_SEL_DP_ENC0_P0_SHIFT 3
#define ENHANCED_FRAME_EN_DP_ENC0_P0_MASK 0x10
#define ENHANCED_FRAME_EN_DP_ENC0_P0_SHIFT 4

#define MTK_DP_ENC0_P0_3004 (ENC0_OFFSET + 0x004)
#define VIDEO_M_CODE_SEL_DP_ENC0_P0_MASK 0x100
#define VIDEO_M_CODE_SEL_DP_ENC0_P0_SHIFT 8
#define DP_TX_ENCODER_4P_RESET_SW_DP_ENC0_P0_MASK 0x200
#define DP_TX_ENCODER_4P_RESET_SW_DP_ENC0_P0_SHIFT 9

#define MTK_DP_ENC0_P0_3008 (ENC0_OFFSET + 0x008)
#define VIDEO_M_CODE_SW_0_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_300C (ENC0_OFFSET + 0x00C)
#define VIDEO_M_CODE_SW_1_DP_ENC0_P0_MASK 0xff

#define MTK_DP_ENC0_P0_3010 (ENC0_OFFSET + 0x010)
#define HTOTAL_SW_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3014 (ENC0_OFFSET + 0x014)
#define VTOTAL_SW_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3018 (ENC0_OFFSET + 0x018)
#define HSTART_SW_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_301C (ENC0_OFFSET + 0x01C)
#define VSTART_SW_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3020 (ENC0_OFFSET + 0x020)
#define HWIDTH_SW_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3024 (ENC0_OFFSET + 0x024)
#define VHEIGHT_SW_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3028 (ENC0_OFFSET + 0x028)
#define HSW_SW_DP_ENC0_P0_MASK 0x7fff
#define HSW_SW_DP_ENC0_P0_SHIFT 0
#define HSP_SW_DP_ENC0_P0_MASK 0x8000

#define MTK_DP_ENC0_P0_302C (ENC0_OFFSET + 0x02C)
#define VSW_SW_DP_ENC0_P0_MASK 0x7fff
#define VSW_SW_DP_ENC0_P0_SHIFT 0
#define VSP_SW_DP_ENC0_P0_MASK 0x8000

#define MTK_DP_ENC0_P0_3030 (ENC0_OFFSET + 0x030)
#define HTOTAL_SEL_DP_ENC0_P0_SHIFT 0
#define VTOTAL_SEL_DP_ENC0_P0_SHIFT 1
#define HSTART_SEL_DP_ENC0_P0_SHIFT 2
#define VSTART_SEL_DP_ENC0_P0_SHIFT 3
#define HWIDTH_SEL_DP_ENC0_P0_SHIFT 4
#define VHEIGHT_SEL_DP_ENC0_P0_SHIFT 5
#define HSP_SEL_DP_ENC0_P0_SHIFT 6
#define HSW_SEL_DP_ENC0_P0_SHIFT 7
#define VSP_SEL_DP_ENC0_P0_SHIFT 8
#define VSW_SEL_DP_ENC0_P0_SHIFT 9
#define VBID_AUDIO_MUTE_FLAG_SW_DP_ENC0_P0_MASK 0x800
#define VBID_AUDIO_MUTE_SW_DP_ENC0_P0_SHIFT 11
#define VBID_AUDIO_MUTE_FLAG_SEL_DP_ENC0_P0_MASK 0x1000
#define VBID_AUDIO_MUTE_SEL_DP_ENC0_P0_SHIFT 12

#define MTK_DP_ENC0_P0_3034 (ENC0_OFFSET + 0x034)

#define MTK_DP_ENC0_P0_3038 (ENC0_OFFSET + 0x038)
#define VIDEO_SOURCE_SEL_DP_ENC0_P0_MASK 0x800
#define VIDEO_SOURCE_SEL_DP_ENC0_P0_SHIFT 11

#define MTK_DP_ENC0_P0_303C (ENC0_OFFSET + 0x03C)
#define SRAM_START_READ_THRD_DP_ENC0_P0_MASK 0x3f
#define SRAM_START_READ_THRD_DP_ENC0_P0_SHIFT 0
#define VIDEO_COLOR_DEPTH_DP_ENC0_P0_MASK 0x700
#define VIDEO_COLOR_DEPTH_DP_ENC0_P0_SHIFT 8
#define VIDEO_COLOR_DEPTH_DP_ENC0_P0_16BIT                                     \
	(0 << VIDEO_COLOR_DEPTH_DP_ENC0_P0_SHIFT)
#define VIDEO_COLOR_DEPTH_DP_ENC0_P0_12BIT                                     \
	(1 << VIDEO_COLOR_DEPTH_DP_ENC0_P0_SHIFT)
#define VIDEO_COLOR_DEPTH_DP_ENC0_P0_10BIT                                     \
	(2 << VIDEO_COLOR_DEPTH_DP_ENC0_P0_SHIFT)
#define VIDEO_COLOR_DEPTH_DP_ENC0_P0_8BIT                                      \
	(3 << VIDEO_COLOR_DEPTH_DP_ENC0_P0_SHIFT)
#define VIDEO_COLOR_DEPTH_DP_ENC0_P0_6BIT                                      \
	(4 << VIDEO_COLOR_DEPTH_DP_ENC0_P0_SHIFT)
#define PIXEL_ENCODE_FORMAT_DP_ENC0_P0_MASK 0x7000
#define PIXEL_ENCODE_FORMAT_DP_ENC0_P0_SHIFT 12
#define PIXEL_ENCODE_FORMAT_DP_ENC0_P0_RGB                                     \
	(0 << PIXEL_ENCODE_FORMAT_DP_ENC0_P0_SHIFT)
#define PIXEL_ENCODE_FORMAT_DP_ENC0_P0_YCBCR422                                \
	(1 << PIXEL_ENCODE_FORMAT_DP_ENC0_P0_SHIFT)
#define PIXEL_ENCODE_FORMAT_DP_ENC0_P0_YCBCR420                                \
	(2 << PIXEL_ENCODE_FORMAT_DP_ENC0_P0_SHIFT)
#define VIDEO_MN_GEN_EN_DP_ENC0_P0_MASK 0x8000
#define VIDEO_MN_GEN_EN_DP_ENC0_P0_SHIFT 15

#define MTK_DP_ENC0_P0_3040 (ENC0_OFFSET + 0x040)
#define SDP_DOWN_CNT_INIT_DP_ENC0_P0_MASK 0xfff
#define SDP_DOWN_CNT_INIT_DP_ENC0_P0_SHIFT 0

#define MTK_DP_ENC0_P0_3044 (ENC0_OFFSET + 0x044)
#define VIDEO_N_CODE_0_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3048 (ENC0_OFFSET + 0x048)
#define VIDEO_N_CODE_1_DP_ENC0_P0_MASK 0xff

#define MTK_DP_ENC0_P0_304C (ENC0_OFFSET + 0x04C)
#define VBID_VIDEO_MUTE_DP_ENC0_P0_MASK 0x4
#define SDP_VSYNC_RISING_MASK_DP_ENC0_P0_MASK 0x100

#define MTK_DP_ENC0_P0_3050 (ENC0_OFFSET + 0x050)
#define VIDEO_N_CODE_MN_GEN_0_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3054 (ENC0_OFFSET + 0x054)
#define VIDEO_N_CODE_MN_GEN_1_DP_ENC0_P0_MASK 0xff

#define MTK_DP_ENC0_P0_3064 (ENC0_OFFSET + 0x064)
#define HDE_NUM_LAST_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3088 (ENC0_OFFSET + 0x088)
#define AU_EN_DP_ENC0_P0_MASK 0x40
#define AU_EN_DP_ENC0_P0_SHIFT 6
#define AUDIO_8CH_EN_DP_ENC0_P0_MASK 0x80
#define AUDIO_8CH_SEL_DP_ENC0_P0_MASK 0x100
#define AUDIO_2CH_EN_DP_ENC0_P0_MASK 0x4000
#define AUDIO_2CH_SEL_DP_ENC0_P0_MASK 0x8000

#define MTK_DP_ENC0_P0_308C (ENC0_OFFSET + 0x08C)
#define CH_STATUS_0_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3090 (ENC0_OFFSET + 0x090)
#define CH_STATUS_1_DP_ENC0_P0_MASK 0xffff

#define MTK_DP_ENC0_P0_3094 (ENC0_OFFSET + 0x094)
#define CH_STATUS_2_DP_ENC0_P0_MASK 0xff

#define MTK_DP_ENC0_P0_30A0 (ENC0_OFFSET + 0x0A0)

#define MTK_DP_ENC0_P0_30A4 (ENC0_OFFSET + 0x0A4)
#define AU_TS_CFG_DP_ENC0_P0_MASK 0xff

#define MTK_DP_ENC0_P0_30A8 (ENC0_OFFSET + 0x0A8)

#define MTK_DP_ENC0_P0_30AC (ENC0_OFFSET + 0x0AC)

#define MTK_DP_ENC0_P0_30B0 (ENC0_OFFSET + 0x0B0)

#define MTK_DP_ENC0_P0_30B4 (ENC0_OFFSET + 0x0B4)
#define ISRC_CFG_DP_ENC0_P0_MASK 0xff00
#define ISRC_CFG_DP_ENC0_P0_SHIFT 8

#define MTK_DP_ENC0_P0_30B8 (ENC0_OFFSET + 0x0B8)

#define MTK_DP_ENC0_P0_30BC (ENC0_OFFSET + 0x0BC)
#define ISRC_CONT_DP_ENC0_P0_MASK 0x1
#define ISRC_CONT_DP_ENC0_P0_SHIFT 0
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_MASK 0x700
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_SHIFT 8
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_MUL_2                             \
	(1 << AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_SHIFT)
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_MUL_4                             \
	(2 << AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_SHIFT)
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_MUL_8                             \
	(3 << AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_SHIFT)
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_DIV_2                             \
	(5 << AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_SHIFT)
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_DIV_4                             \
	(6 << AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_SHIFT)
#define AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_DIV_8                             \
	(7 << AUDIO_M_CODE_MULT_DIV_SEL_DP_ENC0_P0_SHIFT)

#define MTK_DP_ENC0_P0_30D8 (ENC0_OFFSET + 0x0D8)

#define MTK_DP_ENC0_P0_312C (ENC0_OFFSET + 0x12C)
#define ASP_HB2_DP_ENC0_P0_MASK 0xff
#define ASP_HB3_DP_ENC0_P0_MASK 0xff00
#define ASP_HB3_DP_ENC0_P0_SHIFT 8

#define MTK_DP_ENC0_P0_3130 (ENC0_OFFSET + 0x130)

#define MTK_DP_ENC0_P0_3138 (ENC0_OFFSET + 0x138)

#define MTK_DP_ENC0_P0_3154 (ENC0_OFFSET + 0x154)
#define PGEN_HTOTAL_DP_ENC0_P0_MASK 0x3fff

#define MTK_DP_ENC0_P0_3158 (ENC0_OFFSET + 0x158)
#define PGEN_HSYNC_RISING_DP_ENC0_P0_MASK 0x3fff

#define MTK_DP_ENC0_P0_315C (ENC0_OFFSET + 0x15C)
#define PGEN_HSYNC_PULSE_WIDTH_DP_ENC0_P0_MASK 0x3fff

#define MTK_DP_ENC0_P0_3160 (ENC0_OFFSET + 0x160)
#define PGEN_HFDE_START_DP_ENC0_P0_MASK 0x3fff

#define MTK_DP_ENC0_P0_3164 (ENC0_OFFSET + 0x164)
#define PGEN_HFDE_ACTIVE_WIDTH_DP_ENC0_P0_MASK 0x3fff

#define MTK_DP_ENC0_P0_3168 (ENC0_OFFSET + 0x168)
#define PGEN_VTOTAL_DP_ENC0_P0_MASK 0x1fff

#define MTK_DP_ENC0_P0_316C (ENC0_OFFSET + 0x16C)
#define PGEN_VSYNC_RISING_DP_ENC0_P0_MASK 0x1fff

#define MTK_DP_ENC0_P0_3170 (ENC0_OFFSET + 0x170)
#define PGEN_VSYNC_PULSE_WIDTH_DP_ENC0_P0_MASK 0x1fff

#define MTK_DP_ENC0_P0_3174 (ENC0_OFFSET + 0x174)
#define PGEN_VFDE_START_DP_ENC0_P0_MASK 0x1fff

#define MTK_DP_ENC0_P0_3178 (ENC0_OFFSET + 0x178)
#define PGEN_VFDE_ACTIVE_WIDTH_DP_ENC0_P0_MASK 0x1fff

#define MTK_DP_ENC0_P0_31B0 (ENC0_OFFSET + 0x1B0)
#define PGEN_PATTERN_SEL_SHIFT 4
#define PGEN_PATTERN_SEL_MASK 0x0070

#define MTK_DP_ENC0_P0_31C8 (ENC0_OFFSET + 0x1C8)
#define VSC_EXT_VESA_HB0_DP_ENC0_P0_MASK 0xff
#define VSC_EXT_VESA_HB1_DP_ENC0_P0_MASK 0xff00
#define VSC_EXT_VESA_HB1_DP_ENC0_P0_SHIFT 8

#define MTK_DP_ENC0_P0_31CC (ENC0_OFFSET + 0x1CC)
#define VSC_EXT_VESA_HB2_DP_ENC0_P0_MASK 0xff
#define VSC_EXT_VESA_HB2_DP_ENC0_P0_SHIFT 0
#define VSC_EXT_VESA_HB3_DP_ENC0_P0_MASK 0xff00

#define MTK_DP_ENC0_P0_31D0 (ENC0_OFFSET + 0x1D0)
#define VSC_EXT_CEA_HB0_DP_ENC0_P0_MASK 0xff
#define VSC_EXT_CEA_HB1_DP_ENC0_P0_MASK 0xff00
#define VSC_EXT_CEA_HB1_DP_ENC0_P0_SHIFT 8

#define MTK_DP_ENC0_P0_31D4 (ENC0_OFFSET + 0x1D4)
#define VSC_EXT_CEA_HB2_DP_ENC0_P0_MASK 0xff
#define VSC_EXT_CEA_HB2_DP_ENC0_P0_SHIFT 0
#define VSC_EXT_CEA_HB3_DP_ENC0_P0_MASK 0xff00

#define MTK_DP_ENC0_P0_31D8 (ENC0_OFFSET + 0x1D8)
#define VSC_EXT_VESA_NUM_DP_ENC0_P0_MASK 0x3f
#define VSC_EXT_VESA_NUM_DP_ENC0_P0_SHIFT 0
#define VSC_EXT_CEA_NUM_DP_ENC0_P0_MASK 0x3f00
#define VSC_EXT_CEA_NUM_DP_ENC0_P0_SHIFT 8

#define MTK_DP_ENC0_P0_31DC (ENC0_OFFSET + 0x1DC)
#define HDR0_CFG_DP_ENC0_P0_MASK 0xff
#define HDR0_CFG_DP_ENC0_P0_SHIFT 0

#define MTK_DP_ENC0_P0_31E8 (ENC0_OFFSET + 0x1E8)

#define MTK_DP_ENC0_P0_31EC (ENC0_OFFSET + 0x1EC)
#define AUDIO_CH_SRC_SEL_DP_ENC0_P0_MASK 0x10
#define AUDIO_CH_SRC_SEL_DP_ENC0_P0_SHIFT 4
#define ISRC1_HB3_DP_ENC0_P0_MASK 0xff00
#define ISRC1_HB3_DP_ENC0_P0_SHIFT 8

#define MTK_DP_ENC1_P0_3200 (ENC1_OFFSET + 0x000)

#define MTK_DP_ENC1_P0_3280 (ENC1_OFFSET + 0x080)
#define SDP_PACKET_TYPE_DP_ENC1_P0_MASK 0x1f
#define SDP_PACKET_W_DP_ENC1_P0 0x20
#define SDP_PACKET_W_DP_ENC1_P0_MASK 0x20
#define SDP_PACKET_W_DP_ENC1_P0_SHIFT 5

#define MTK_DP_ENC1_P0_328C (ENC1_OFFSET + 0x08C)

#define MTK_DP_ENC1_P0_3290 (ENC1_OFFSET + 0x090)

#define MTK_DP_ENC1_P0_32A0 (ENC1_OFFSET + 0x0A0)

#define MTK_DP_ENC1_P0_32A4 (ENC1_OFFSET + 0x0A4)

#define MTK_DP_ENC1_P0_3300 (ENC1_OFFSET + 0x100)
#define VIDEO_AFIFO_RDY_SEL_DP_ENC1_P0_MASK 0x300
#define VIDEO_AFIFO_RDY_SEL_DP_ENC1_P0_SHIFT 8

#define MTK_DP_ENC1_P0_3304 (ENC1_OFFSET + 0x104)
#define AU_PRTY_REGEN_DP_ENC1_P0_MASK 0x100
#define AU_CH_STS_REGEN_DP_ENC1_P0_MASK 0x200
#define AUDIO_SAMPLE_PRSENT_REGEN_DP_ENC1_P0_MASK 0x1000

#define MTK_DP_ENC1_P0_3324 (ENC1_OFFSET + 0x124)
#define AUDIO_SOURCE_MUX_DP_ENC1_P0_MASK 0x300
#define AUDIO_SOURCE_MUX_DP_ENC1_P0_SHIFT 8
#define AUDIO_SOURCE_MUX_DP_ENC1_P0_DPRX                                       \
	(0 << AUDIO_SOURCE_MUX_DP_ENC1_P0_SHIFT)

#define MTK_DP_ENC1_P0_3364 (ENC1_OFFSET + 0x164)
#define SDP_DOWN_CNT_INIT_IN_HBLANK_DP_ENC1_P0_MASK 0xfff
#define SDP_DOWN_CNT_INIT_IN_HBLANK_DP_ENC1_P0_SHIFT 0
#define FIFO_READ_START_POINT_DP_ENC1_P0_MASK 0xf000
#define FIFO_READ_START_POINT_DP_ENC1_P0_SHIFT 12

#define MTK_DP_ENC1_P0_3368 (ENC1_OFFSET + 0x168)
#define VIDEO_SRAM_FIFO_CNT_RESET_SEL_DP_ENC1_P0_SHIFT 0
#define VIDEO_STABLE_CNT_THRD_DP_ENC1_P0_SHIFT 4
#define SDP_DP13_EN_DP_ENC1_P0_SHIFT 8
#define BS2BS_MODE_DP_ENC1_P0_MASK 0x3000
#define BS2BS_MODE_DP_ENC1_P0_SHIFT 12

#define MTK_DP_ENC1_P0_33F4 (ENC1_OFFSET + 0x1F4)

#define MTK_DP_TRANS_P0_3400 (TRANS_OFFSET + 0x000)
#define PATTERN1_EN_DP_TRANS_P0_MASK 0x1000
#define PATTERN1_EN_DP_TRANS_P0_SHIFT 12
#define PATTERN2_EN_DP_TRANS_P0_MASK 0x2000
#define PATTERN3_EN_DP_TRANS_P0_MASK 0x4000
#define PATTERN4_EN_DP_TRANS_P0_MASK 0x8000

#define MTK_DP_TRANS_P0_3404 (TRANS_OFFSET + 0x004)
#define DP_SCR_EN_DP_TRANS_P0_MASK 0x1

#define MTK_DP_TRANS_P0_340C (TRANS_OFFSET + 0x00C)
#define DP_TX_TRANSMITTER_4P_RESET_SW_DP_TRANS_P0_MASK 0x2000
#define DP_TX_TRANSMITTER_4P_RESET_SW_DP_TRANS_P0_SHIFT 13

#define MTK_DP_TRANS_P0_3410 (TRANS_OFFSET + 0x010)
#define HPD_DEB_THD_DP_TRANS_P0_MASK 0xf
#define HPD_DEB_THD_DP_TRANS_P0_SHIFT 0
#define HPD_INT_THD_DP_TRANS_P0_MASK 0xf0
#define HPD_INT_THD_DP_TRANS_P0_SHIFT 4
#define HPD_INT_THD_DP_TRANS_P0_LOWER_500US (2 << HPD_INT_THD_DP_TRANS_P0_SHIFT)
#define HPD_INT_THD_DP_TRANS_P0_UPPER_1100US                                   \
	(2 << (HPD_INT_THD_DP_TRANS_P0_SHIFT + 2))
#define HPD_DISC_THD_DP_TRANS_P0_MASK 0xf00
#define HPD_DISC_THD_DP_TRANS_P0_SHIFT 8
#define HPD_CONN_THD_DP_TRANS_P0_MASK 0xf000
#define HPD_CONN_THD_DP_TRANS_P0_SHIFT 12

#define MTK_DP_TRANS_P0_3414 (TRANS_OFFSET + 0x014)
#define HPD_DB_DP_TRANS_P0_MASK 0x4

#define MTK_DP_TRANS_P0_3418 (TRANS_OFFSET + 0x018)
#define IRQ_CLR_DP_TRANS_P0_MASK 0xf
#define IRQ_MASK_DP_TRANS_P0_MASK 0xf0
#define IRQ_MASK_DP_TRANS_P0_SHIFT 4
#define IRQ_MASK_DP_TRANS_P0_DISC_IRQ (BIT(1) << IRQ_MASK_DP_TRANS_P0_SHIFT)
#define IRQ_MASK_DP_TRANS_P0_CONN_IRQ (BIT(2) << IRQ_MASK_DP_TRANS_P0_SHIFT)
#define IRQ_MASK_DP_TRANS_P0_INT_IRQ (BIT(3) << IRQ_MASK_DP_TRANS_P0_SHIFT)
#define IRQ_STATUS_DP_TRANS_P0_MASK 0xf000
#define IRQ_STATUS_DP_TRANS_P0_SHIFT 12

#define MTK_DP_TRANS_P0_342C (TRANS_OFFSET + 0x02C)
#define XTAL_FREQ_DP_TRANS_P0_DEFAULT 0x69
#define XTAL_FREQ_DP_TRANS_P0_MASK 0xff

#define MTK_DP_TRANS_P0_3430 (TRANS_OFFSET + 0x030)
#define HPD_INT_THD_ECO_DP_TRANS_P0_MASK 0x3
#define HPD_INT_THD_ECO_DP_TRANS_P0_HIGH_BOUND_EXT BIT(1)

#define MTK_DP_TRANS_P0_34A4 (TRANS_OFFSET + 0x0A4)
#define LANE_NUM_DP_TRANS_P0_MASK 0xc
#define LANE_NUM_DP_TRANS_P0_SHIFT 2

#define MTK_DP_TRANS_P0_3540 (TRANS_OFFSET + 0x140)
#define FEC_EN_DP_TRANS_P0_MASK 0x1
#define FEC_EN_DP_TRANS_P0_SHIFT 0
#define FEC_CLOCK_EN_MODE_DP_TRANS_P0_MASK 0x8
#define FEC_CLOCK_EN_MODE_DP_TRANS_P0_SHIFT 3

#define MTK_DP_TRANS_P0_3580 (TRANS_OFFSET + 0x180)
#define POST_MISC_DATA_LANE0_OV_DP_TRANS_P0_MASK 0x100
#define POST_MISC_DATA_LANE1_OV_DP_TRANS_P0_MASK 0x200
#define POST_MISC_DATA_LANE2_OV_DP_TRANS_P0_MASK 0x400
#define POST_MISC_DATA_LANE3_OV_DP_TRANS_P0_MASK 0x800

#define MTK_DP_TRANS_P0_35C4 (TRANS_OFFSET + 0x1C4)
#define SW_IRQ_MASK_DP_TRANS_P0_MASK 0xffff

#define MTK_DP_TRANS_P0_35C8 (TRANS_OFFSET + 0x1C8)
#define SW_IRQ_CLR_DP_TRANS_P0_MASK 0xffff

#define SW_IRQ_STATUS_DP_TRANS_P0_MASK 0xffff
#define SW_IRQ_STATUS_DP_TRANS_P0_SHIFT 0

#define MTK_DP_TRANS_P0_35D0 (TRANS_OFFSET + 0x1D0)
#define SW_IRQ_FINAL_STATUS_DP_TRANS_P0_MASK 0xffff

#define MTK_DP_TRANS_P0_35F0 (TRANS_OFFSET + 0x1F0)

#define MTK_DP_AUX_P0_360C (AUX_OFFSET + 0x00C)
#define AUX_TIMEOUT_THR_AUX_TX_P0_MASK 0x1fff

#define MTK_DP_AUX_P0_3614 (AUX_OFFSET + 0x014)
#define AUX_RX_UI_CNT_THR_AUX_TX_P0_MASK 0x7f
#define AUX_RX_UI_CNT_THR_AUX_TX_P0_SHIFT 0

#define MTK_DP_AUX_P0_3618 (AUX_OFFSET + 0x018)
#define AUX_RX_FIFO_FULL_AUX_TX_P0_MASK 0x200
#define AUX_RX_FIFO_WRITE_POINTER_AUX_TX_P0_MASK 0xf

#define MTK_DP_AUX_P0_3620 (AUX_OFFSET + 0x020)
#define AUX_RD_MODE_AUX_TX_P0_MASK 0x200
#define AUX_RX_FIFO_READ_PULSE_TX_P0_MASK 0x100
#define AUX_RX_FIFO_R_PULSE_TX_P0_SHIFT 8
#define AUX_RX_FIFO_READ_DATA_AUX_TX_P0_MASK 0xff
#define AUX_RX_FIFO_READ_DATA_AUX_TX_P0_SHIFT 0

#define MTK_DP_AUX_P0_3624 (AUX_OFFSET + 0x024)
#define AUX_RX_REPLY_COMMAND_AUX_TX_P0_MASK 0xf

#define MTK_DP_AUX_P0_3628 (AUX_OFFSET + 0x028)
#define AUX_RX_PHY_STATE_AUX_TX_P0_MASK 0x3ff
#define AUX_RX_PHY_STATE_AUX_TX_P0_SHIFT 0
#define AUX_RX_PHY_STATE_AUX_TX_P0_RX_IDLE                                     \
	(BIT(0) << AUX_RX_PHY_STATE_AUX_TX_P0_SHIFT)

#define MTK_DP_AUX_P0_362C (AUX_OFFSET + 0x02C)
#define AUX_NO_LENGTH_AUX_TX_P0_MASK 0x1
#define AUX_NO_LENGTH_AUX_TX_P0_SHIFT 0
#define AUX_TX_AUXTX_OV_EN_AUX_TX_P0_MASK 0x2
#define AUX_RESERVED_RW_0_AUX_TX_P0_MASK 0xfffc

#define MTK_DP_AUX_P0_3630 (AUX_OFFSET + 0x030)
#define AUX_TX_REQUEST_READY_AUX_TX_P0_MASK 0x8
#define AUX_TX_REQUEST_READY_AUX_TX_P0_SHIFT 3

#define MTK_DP_AUX_P0_3634 (AUX_OFFSET + 0x034)
#define AUX_TX_OVER_SAMPLE_RATE_AUX_TX_P0_MASK 0xff00
#define AUX_TX_OVER_SAMPLE_RATE_AUX_TX_P0_SHIFT 8

#define MTK_DP_AUX_P0_3640 (AUX_OFFSET + 0x040)
#define AUX_RX_RECV_COMPLETE_IRQ_TX_P0_MASK 0x40
#define AUX_RX_AUX_RECV_COMPLETE_IRQ_AUX_TX_P0_SHIFT 6
#define AUX_RX_EDID_RECV_COMPLETE_IRQ_AUX_TX_P0_SHIFT 5
#define AUX_RX_MCCS_RECV_COMPLETE_IRQ_AUX_TX_P0_SHIFT 4
#define AUX_RX_CMD_RECV_IRQ_AUX_TX_P0_SHIFT 3
#define AUX_RX_ADDR_RECV_IRQ_AUX_TX_P0_SHIFT 2
#define AUX_RX_DATA_RECV_IRQ_AUX_TX_P0_SHIFT 1
#define AUX_400US_TIMEOUT_IRQ_AUX_TX_P0_MASK 0x1
#define AUX_400US_TIMEOUT_IRQ_AUX_TX_P0_SHIFT 0

#define MTK_DP_AUX_P0_3644 (AUX_OFFSET + 0x044)
#define MCU_REQUEST_COMMAND_AUX_TX_P0_MASK 0xf

#define MTK_DP_AUX_P0_3648 (AUX_OFFSET + 0x048)
#define MCU_REQUEST_ADDRESS_LSB_AUX_TX_P0_MASK 0xffff

#define MTK_DP_AUX_P0_364C (AUX_OFFSET + 0x04C)
#define MCU_REQUEST_ADDRESS_MSB_AUX_TX_P0_MASK 0xf

#define MTK_DP_AUX_P0_3650 (AUX_OFFSET + 0x050)
#define MCU_REQ_DATA_NUM_AUX_TX_P0_MASK 0xf000
#define MCU_REQ_DATA_NUM_AUX_TX_P0_SHIFT 12
#define PHY_FIFO_RST_AUX_TX_P0_MASK 0x200
#define MCU_ACK_TRAN_COMPLETE_AUX_TX_P0_MASK 0x100
#define MCU_ACK_TRAN_COMPLETE_AUX_TX_P0_SHIFT 8

#define MTK_DP_AUX_P0_3658 (AUX_OFFSET + 0x058)
#define AUX_TX_OV_EN_AUX_TX_P0_MASK 0x1

#define MTK_DP_AUX_P0_3690 (AUX_OFFSET + 0x090)
#define RX_REPLY_COMPLETE_MODE_AUX_TX_P0_MASK 0x100
#define RX_REPLY_COMPLETE_MODE_AUX_TX_P0_SHIFT 8

#define MTK_DP_AUX_P0_3704 (AUX_OFFSET + 0x104)
#define AUX_TX_FIFO_WRITE_DATA_NEW_MODE_TOGGLE_AUX_TX_P0_MASK 0x2
#define AUX_TX_FIFO_NEW_MODE_EN_AUX_TX_P0_MASK 0x4
#define AUX_TX_FIFO_NEW_MODE_EN_AUX_TX_P0_SHIFT 2

#define MTK_DP_AUX_P0_3708 (AUX_OFFSET + 0x108)

#define MTK_DP_AUX_P0_37C8 (AUX_OFFSET + 0x1C8)
#define MTK_ATOP_EN_AUX_TX_P0_MASK 0x1
#define MTK_ATOP_EN_AUX_TX_P0_SHIFT 0

#define MTK_DP_TOP_PWR_STATE (TOP_OFFSET + 0x00)
#define DP_PWR_STATE_MASK 0x3
#define DP_PWR_STATE_BANDGAP 1
#define DP_PWR_STATE_BANDGAP_TPLL 2
#define DP_PWR_STATE_BANDGAP_TPLL_LANE 3

#define MTK_DP_TOP_SWING_EMP (TOP_OFFSET + 0x04)
#define DP_TX0_VOLT_SWING_MASK 0x3
#define DP_TX0_VOLT_SWING_SHIFT 0
#define DP_TX0_PRE_EMPH_MASK 0xc
#define DP_TX0_PRE_EMPH_SHIFT 2
#define DP_TX1_VOLT_SWING_MASK 0x300
#define DP_TX1_VOLT_SWING_SHIFT 8
#define DP_TX1_PRE_EMPH_MASK 0xc00
#define DP_TX2_VOLT_SWING_MASK 0x30000
#define DP_TX2_PRE_EMPH_MASK 0xc0000
#define DP_TX3_VOLT_SWING_MASK 0x3000000
#define DP_TX3_PRE_EMPH_MASK 0xc000000

#define MTK_DP_TOP_RESET_AND_PROBE (TOP_OFFSET + 0x20)
#define SW_RST_B_SHIFT 0
#define SW_RST_B_PHYD (BIT(4) << SW_RST_B_SHIFT)

#define MTK_DP_TOP_IRQ_STATUS (TOP_OFFSET + 0x28)
#define RGS_IRQ_STATUS_SHIFT 0
#define RGS_IRQ_STATUS_TRANSMITTER (BIT(1) << RGS_IRQ_STATUS_SHIFT)

#define MTK_DP_TOP_IRQ_MASK (TOP_OFFSET + 0x2C)
#define IRQ_MASK_AUX_TOP_IRQ BIT(2)

#define MTK_DP_TOP_MEM_PD (TOP_OFFSET + 0x38)
#define MEM_ISO_EN_SHIFT 0
#define FUSE_SEL_SHIFT 2

#endif /*_MTK_DP_REG_H_*/
