// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 MediaTek Inc.
 */

#include <linux/init.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/kthread.h>
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/debugfs.h>
#include <linux/i2c.h>
#include <linux/kernel.h>
#include <linux/of_platform.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/of_graph.h>

#include "mtk_hdmirx.h"
#include "vga_table.h"

#define _VGA_TABLE_C_
#define VGAMODE_OFFSET 0
#define VGACAPTURE_OFFSET                                                      \
	(VGAMODE_OFFSET +                                                      \
		(u16)MAX_TIMING_FORMAT * sizeof(struct VGAMODE))

#define ADCPLL_WORKAROUND 1
#define OVERSAMPLE_THRESHOLD 500 /* 250//350 //25MHz */

const struct VGAMODE VGATIMING_TABLE[] = {
	/*
	 * HF    VF      P-CLK   HTOTAL  VTOTAL  H-W     H-Act
	 *H-BP    V(BP+w) V-Act
	 */
	{0, 0, 0, 0, 0, 0, 720, 0, 0, 480, 0x00, MODE_NOSUPPORT},
	{157, 60, 540, 3432, 525, 283, 2880, 229, 16, 480, 0x41,
		MODE_525I_OVERSAMPLE},
	{157, 50, 540, 3456, 625, 259, 2880, 277, 20, 576, 0x41,
		MODE_625I_OVERSAMPLE},
	{315, 60, 540, 1716, 525, 120, 1440, 120, 35, 480, 0x03,
		MODE_480P_OVERSAMPLE},
	{313, 50, 540, 1728, 625, 124, 1440, 138, 43, 576, 0x01,
		MODE_576P_OVERSAMPLE},
	{375, 50, 742, 1980, 750, 32, 1280, 260, 24, 720, 0x00, MODE_720p_50},
	{450, 60, 742, 1650, 750, 31, 1280, 260, 24, 720, 0x00, MODE_720p_60},
	{270, 48, 742, 2750, 1125, 44, 1920, 193, 19, 1080, 0x40,
		MODE_1080i_48},
	{281, 50, 742, 2640, 1125, 35, 1920, 192, 19, 1080, 0x40,
		MODE_1080i_50},
	{338, 60, 742, 2200, 1125, 36, 1920, 192, 19, 1080, 0x40, MODE_1080i},
	{270, 24, 742, 2750, 1125, 33, 1920, 194, 40, 1080, 0x00,
		MODE_1080p_24},
	{281, 25, 742, 2640, 1125, 33, 1920, 194, 40, 1080, 0x00,
		MODE_1080p_25},
	{337, 30, 742, 2200, 1125, 33, 1920, 194, 40, 1080, 0x00,
		MODE_1080p_30},
	{562, 50, 1485, 2640, 1125, 30, 1920, 192, 40, 1080, 0x00,
		MODE_1080p_50},
	{675, 60, 1485, 2200, 1125, 30, 1920, 192, 40, 1080, 0x00,
		MODE_1080p_60},
	{157, 60, 270, 1716, 525, 134, 1440, 114, 17, 480, 0x41, MODE_525I},
	{157, 50, 270, 1728, 625, 124, 1440, 138, 21, 576, 0x41, MODE_625I},
	{315, 60, 270, 858, 525, 60, 720, 61, 36, 480, 0x00, MODE_480P},
	{313, 50, 270, 864, 625, 74, 720, 69, 42, 576, 0x00, MODE_576P},
	{180, 24, 743, 4125, 750, 40, 1280, 262, 24, 720, 0x00, MODE_NOSUPPORT},
	{188, 25, 743, 3960, 750, 40, 1280, 262, 24, 720, 0x00, MODE_720p_25},
	{225, 30, 743, 3300, 750, 40, 1280, 262, 24, 720, 0x00, MODE_720p_30},
	{157, 60, 269, 1716, 262, 60, 1440, 61, 36, 240, 0x600, MODE_240P},
	{0, 0, 742, 2200, 563, 35, 1920, 201, 19, 540, 0x00, MODE_540P},
	{156, 50, 270, 1728, 313, 63, 1440, 213, 22, 288, 0x600, MODE_288P},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_480P_24},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_480P_30},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_576P_25},
	{315, 60, 252, 800, 525, 96, 640, 48, 35, 480, 0x600,
		MODE_HDMI_640_480P},
	{180, 24, 594, 3300, 750, 40, 1280, 262, 23, 720, 0x600, MODE_720p_24},
	{750, 50, 1485, 1980, 1500, 40, 1280, 220, 30, 1470, 0x700,
		MODE_3D_720p_50_FP},
	{900, 60, 1485, 1650, 1500, 40, 1280, 220, 30, 1470, 0x700,
		MODE_3D_720p_60_FP},
	{540, 24, 1485, 2750, 2250, 44, 1920, 148, 45, 2205, 0x700,
		MODE_3D_1080p_24_FP},
	{675, 30, 1485, 2200, 2250, 44, 1920, 148, 22, 2228, 0x700,
		MODE_3D_1080I_60_FP},
	{629, 60, 540, 858, 1050, 40, 720, 220, 45, 1005, 0x700,
		MODE_3D_480p_60_FP},
	{625, 50, 540, 864, 1250, 40, 720, 220, 49, 1201, 0x700,
		MODE_3D_576p_50_FP},
	{359, 24, 1186, 3300, 1500, 40, 1280, 220, 30, 1470, 0x700,
		MODE_3D_720p_24_FP},
	{449, 30, 1486, 3300, 1500, 40, 1280, 220, 30, 1470, 0x700,
		MODE_3D_720p_30_FP},
	{673, 30, 1482, 2200, 2250, 44, 1920, 148, 45, 2205, 0x700,
		MODE_3D_1080p_30_FP},
	{314, 30, 539, 1716, 1050, 283, 1440, 229, 22, 1028, 0x700,
		MODE_3D_480I_60_FP},
	{312, 25, 539, 1728, 1250, 277, 1440, 277, 24, 1226, 0x700,
		MODE_3D_576I_60_FP},
	{563, 25, 1485, 2640, 2250, 44, 1920, 148, 22, 2228, 0x700,
		MODE_3D_1080I_50_FP},
	{1125, 50, 2970, 2640, 2250, 44, 1920, 148, 45, 2205, 0x700,
		MODE_3D_1080p_50_FP},
	{1350, 60, 2970, 2200, 2250, 44, 1920, 148, 45, 2205, 0x700,
		MODE_3D_1080p_60_FP},
	{450, 60, 742, 1650, 750, 40, 1280, 220, 15, 735, 0x700,
		MODE_3D_1650_750_60_FP},
	{450, 30, 742, 1650, 1500, 40, 1280, 220, 15, 1485, 0x700,
		MODE_3D_1650_1500_30_FP},
	{628, 60, 504, 800, 1050, 96, 640, 48, 45, 1005, 0x700,
		MODE_3D_640_480p_60_FP},
	{314, 60, 540, 1716, 524, 62, 1440, 195, 22, 502, 0x700,
		MODE_3D_1440_240p_60_FP},
	{312, 50, 540, 1728, 624, 63, 1440, 213, 22, 600, 0x700,
		MODE_3D_1440_288p_50_FP},
	{625, 50, 1080, 1728, 1250, 128, 1440, 136, 49, 1201, 0x700,
		MODE_3D_1440_576p_50_FP},
	{375, 25, 1483, 3960, 1500, 40, 1280, 593, 30, 1470, 0x700,
		MODE_3D_720p_25_FP},
	{563, 25, 1482, 2640, 2250, 44, 1920, 148, 45, 2205, 0x700,
		MODE_3D_1080p_25_FP},
	{625, 25, 1440, 2304, 2500, 168, 1920, 184, 84, 2415, 0x700,
		MODE_3D_1080I_1250TOTAL_50_FP},
	{270, 24, 1485, 5500, 1125, 66, 3840, 388, 39, 1080, 0x700,
		MODE_3D_1080p_24_SBS_FULL},
	{280, 25, 1485, 5280, 1125, 66, 3840, 388, 39, 1080, 0x700,
		MODE_3D_1080p_25_SBS_FULL},
	{337, 30, 1485, 4400, 1125, 66, 3840, 388, 39, 1080, 0x700,
		MODE_3D_1080p_30_SBS_FULL},
	{281, 50, 1486, 5280, 1125, 70, 3840, 388, 18, 1080, 0x740,
		MODE_3D_1080I_50_SBS_FULL},
	{337, 60, 1486, 4400, 1125, 72, 3840, 388, 18, 1080, 0x740,
		MODE_3D_1080I_60_SBS_FULL},
	{180, 24, 1186, 6600, 750, 80, 2560, 524, 23, 720, 0x700,
		MODE_3D_720p_24_SBS_FULL},
	{225, 30, 1486, 6600, 750, 80, 2560, 522, 23, 720, 0x700,
		MODE_3D_720p_30_SBS_FULL},
	{375, 50, 1486, 3960, 750, 64, 2560, 524, 23, 720, 0x700,
		MODE_3D_720p_50_SBS_FULL},
	{450, 60, 1485, 3300, 750, 62, 2560, 524, 23, 720, 0x700,
		MODE_3D_720p_60_SBS_FULL},
	{315, 60, 540, 1716, 525, 120, 1440, 122, 36, 480, 0x700,
		MODE_3D_480p_60_SBS_FULL},
	{312, 50, 540, 1728, 625, 148, 1440, 138, 42, 576, 0x700,
		MODE_3D_576p_50_SBS_FULL},
	{157, 60, 540, 3432, 525, 268, 2880, 228, 16, 480, 0x740,
		MODE_3D_480I_60_SBS_FULL},
	{157, 50, 540, 3456, 625, 248, 2880, 276, 20, 576, 0x740,
		MODE_3D_576I_50_SBS_FULL},
	{314, 60, 503, 1600, 525, 192, 1280, 96, 35, 480, 0x700,
		MODE_3D_640_480p_60_SBS_FULL},
	{628, 60, 504, 800, 1050, 96, 640, 48, 70, 960, 0x700,
		MODE_3D_640_480p_60_LA},
	{314, 60, 539, 1716, 524, 124, 1440, 120, 36, 480, 0x700,
		MODE_3D_240p_60_LA},
	{313, 50, 540, 1728, 625, 124, 1440, 138, 42, 576, 0x700,
		MODE_3D_288p_50_LA},
	{630, 60, 540, 858, 1050, 62, 720, 60, 72, 960, 0x700,
		MODE_3D_480p_60_LA},
	{625, 50, 540, 864, 1250, 64, 720, 68, 90, 1152, 0x700,
		MODE_3D_576p_50_LA},
	{360, 24, 1189, 3300, 1500, 40, 1280, 10, 52, 1440, 0x700,
		MODE_3D_720p_24_LA},
	{900, 60, 1485, 1650, 1500, 40, 1280, 10, 52, 1440, 0x700,
		MODE_3D_720p_60_LA},
	{750, 50, 1485, 1980, 1500, 40, 1280, 220, 52, 1440, 0x700,
		MODE_3D_720p_50_LA},
	{540, 24, 1485, 2750, 2250, 44, 1920, 148, 84, 2160, 0x700,
		MODE_3D_1080p_24_LA},
	{561, 25, 1485, 2640, 2250, 44, 1920, 148, 84, 2160, 0x700,
		MODE_3D_1080p_25_LA},
	{673, 30, 1485, 2200, 2250, 44, 1920, 148, 84, 2160, 0x700,
		MODE_3D_1080p_30_LA},
	{315, 60, 540, 1716, 525, 62, 1440, 195, 23, 503, 0x700,
		MODE_3D_480I_60_FA},
	{315, 50, 540, 1728, 625, 62, 1440, 138, 25, 601, 0x700,
		MODE_3D_576I_50_FA},
	{673, 60, 1485, 2200, 1125, 44, 1920, 148, 20, 1080, 0x700,
		MODE_3D_1080I_60_FA},
	{563, 50, 1485, 2640, 1125, 44, 1920, 148, 19, 1080, 0x700,
		MODE_3D_1080I_50_FA},
	{675, 60, 1485, 2200, 1125, 44, 1920, 148, 23, 1103, 0x700,
		MODE_3D_MASTER_1080I_60_FA},
	{563, 50, 1485, 2640, 1125, 44, 1920, 148, 23, 1103, 0x700,
		MODE_3D_MASTER_1080I_50_FA},
	{157, 60, 270, 1716, 525, 134, 1440, 114, 18, 480, 0x740,
		MODE_3D_480I_60_SBS_HALF},
	{157, 50, 270, 1728, 625, 124, 1440, 138, 20, 576, 0x740,
		MODE_3D_576I_50_SBS_HALF},
	{338, 60, 742, 2200, 1125, 36, 1920, 194, 18, 1080, 0x740,
		MODE_3D_1080I_60_SBS_HALF},
	{281, 50, 742, 2640, 1125, 35, 1920, 194, 18, 1080, 0x740,
		MODE_3D_1080I_50_SBS_HALF},
	{312, 50, 720, 2304, 1250, 35, 1920, 194, 18, 1080, 0x740,
		MODE_1080i_50_VID39},
	{337, 30, 889, 2640, 1125, 33, 1920, 194, 39, 1080, 0x700,
		MODE_1080P_30_2640H},
	{157, 60, 540, 3432, 262, 248, 2880, 128, 18, 240, 0x700,
		MODE_240P_60_3432H},
	{312, 25, 1080, 3456, 1250, 252, 2880, 276, 22, 1226, 0x700,
		MODE_576i_50_3456H_FP},
	{312, 50, 540, 1728, 625, 128, 1440, 136, 44, 576, 0x700,
		MODE_576P_50_1728H_FP},
	{315, 60, 1082, 3432, 525, 248, 2880, 240, 36, 480, 0x700,
		MODE_480P_60_3432H},
	{312, 50, 1080, 3456, 625, 248, 2880, 128, 44, 576, 0x700,
		MODE_2576P_60_3456H},
	{630, 60, 1080, 1716, 1050, 120, 1440, 122, 45, 1005, 0x700,
		MODE_3D_1440_480p_60_FP},
	{314, 60, 540, 1716, 526, 62, 1440, 195, 23, 503, 0x700,
		MODE_3D_240p_263LINES},
	{540, 24, 2970, 5500, 2250, 88, 3840, 296, 82, 2160, 0x00,
		MODE_3840_2160P_24},
	{563, 25, 2972, 5280, 2250, 88, 3840, 296, 82, 2160, 0x00,
		MODE_3840_2160P_25},
	{675, 30, 2972, 4400, 2250, 88, 3840, 296, 82, 2160, 0x00,
		MODE_3840_2160P_30},
	{540, 24, 2970, 5500, 2250, 88, 4096, 296, 82, 2160, 0x00,
		MODE_4096_2160P_24},
	{563, 25, 2972, 5280, 2250, 88, 4096, 296, 82, 2160, 0x00,
		MODE_4096_2160P_25},
	{675, 30, 2972, 4400, 2250, 88, 4096, 296, 82, 2160, 0x00,
		MODE_4096_2160P_30},
	{2700, 60, 2970, 2200, 2250, 44, 1920, 148, 82, 2160, 0x00,
		MODE_3840_2160P_60_420},
	{2250, 50, 2970, 2640, 2250, 44, 1920, 148, 82, 2160, 0x00,
		MODE_3840_2160P_50_420},
	{2700, 60, 2970, 2200, 2250, 44, 2048, 64, 82, 2160, 0x00,
		MODE_4096_2160P_60_420},
	{2250, 50, 2970, 2640, 2250, 44, 2048, 64, 82, 2160, 0x00,
		MODE_4096_2160P_50_420},
	{1125, 50, 5940, 5280, 2250, 88, 4096, 128, 82, 2160, 0x00,
		MODE_4096_2160P_50},
	{1350, 60, 5940, 4400, 2250, 88, 4096, 128, 82, 2160, 0x00,
		MODE_4096_2160P_60},
	{1125, 50, 5940, 5280, 2250, 88, 3840, 296, 82, 2160, 0x00,
		MODE_3840_2160P_50},
	{1350, 60, 5940, 4400, 2250, 88, 3840, 296, 82, 2160, 0x00,
		MODE_3840_2160P_60},
	{1350, 60, 2972, 2200, 2250, 44, 1920, 148, 82, 2160, 0x00,
		MODE_NOSUPPORT},
	{1120, 50, 2970, 2640, 2250, 44, 1920, 148, 82, 2160, 0x00,
		MODE_NOSUPPORT},
	{315, 50, 252, 800, 629, 96, 640, 48, 87, 480, 0x00, MODE_NOSUPPORT},
	{314, 70, 283, 900, 449, 108, 720, 54, 36, 400, 0x88, MODE_NOSUPPORT},
	{313, 70, 250, 800, 449, 96, 640, 48, 61, 350, 0x90, MODE_NOSUPPORT},
	{314, 70, 283, 900, 449, 108, 720, 54, 62, 350, 0x90, MODE_NOSUPPORT},
	{379, 85, 315, 832, 445, 64, 640, 96, 63, 350, 0x90, MODE_NOSUPPORT},
	{379, 85, 315, 832, 445, 64, 640, 96, 44, 400, 0x88, MODE_NOSUPPORT},
	{379, 85, 355, 936, 446, 72, 720, 108, 45, 400, 0x88, MODE_NOSUPPORT},
	{315, 60, 252, 800, 525, 96, 640, 48, 35, 480, 0x02, MODE_NOSUPPORT},
	{297, 60, 238, 800, 500, 64, 640, 80, 17, 480, 0x00, MODE_NOSUPPORT},
	{294, 60, 235, 800, 494, 32, 640, 80, 11, 480, 0x00, MODE_NOSUPPORT},
	{350, 67, 302, 864, 525, 64, 640, 96, 42, 480, 0x00, MODE_NOSUPPORT},
	{379, 72, 315, 832, 520, 40, 640, 128, 31, 480, 0x00, MODE_NOSUPPORT},
	{375, 75, 315, 840, 500, 64, 640, 120, 19, 480, 0x00, MODE_NOSUPPORT},
	{433, 85, 360, 832, 509, 56, 640, 80, 28, 480, 0x00, MODE_NOSUPPORT},
	{352, 56, 360, 1024, 625, 72, 800, 128, 24, 600, 0x98, MODE_NOSUPPORT},
	{352, 56, 360, 1024, 625, 184, 800, 32, 24, 600, 0x80, MODE_NOSUPPORT},
	{379, 60, 400, 1056, 628, 128, 800, 88, 27, 600, 0x18, MODE_NOSUPPORT},
	{374, 60, 383, 1024, 624, 80, 800, 112, 21, 600, 0x00, MODE_NOSUPPORT},
	{370, 60, 355, 960, 618, 32, 800, 80, 15, 600, 0x00, MODE_NOSUPPORT},
	{480, 72, 500, 1040, 666, 120, 800, 64, 29, 600, 0x18, MODE_NOSUPPORT},
	{469, 75, 495, 1056, 625, 80, 800, 160, 24, 600, 0x18, MODE_NOSUPPORT},
	{537, 85, 563, 1048, 631, 64, 800, 152, 30, 600, 0x18, MODE_NOSUPPORT},
	{497, 75, 572, 1152, 667, 64, 832, 224, 42, 624, 0x00, MODE_NOSUPPORT},
	{298, 60, 315, 1056, 500, 80, 848, 104, 17, 480, 0x00, MODE_NOSUPPORT},
	{310, 60, 338, 1088, 517, 112, 848, 112, 31, 480, 0x18, MODE_NOSUPPORT},
	{295, 60, 298, 1008, 494, 32, 848, 80, 11, 480, 0x00, MODE_NOSUPPORT},
	{302, 60, 336, 1112, 504, 104, 856, 104, 23, 480, 0x00, MODE_NOSUPPORT},
	{484, 60, 650, 1344, 806, 136, 1024, 160, 35, 768, 0x00,
		MODE_NOSUPPORT},
	{0, 0, 650, 1352, 804, 96, 1024, 202, 33, 768, 0x00, MODE_NOSUPPORT},
	{0, 0, 816, 1688, 806, 130, 1280, 174, 25, 768, 0x00, MODE_NOSUPPORT},
	{0, 0, 801, 1664, 798, 136, 1280, 200, 26, 768, 0x00, MODE_NOSUPPORT},
	{478, 60, 635, 1328, 798, 104, 1024, 152, 27, 768, 0x24,
		MODE_NOSUPPORT},
	{478, 60, 795, 1664, 798, 128, 1280, 192, 27, 768, 0x24,
		MODE_NOSUPPORT},
	{477, 60, 848, 1776, 798, 136, 1360, 208, 27, 768, 0x24,
		MODE_NOSUPPORT},
	{438, 70, 456, 1040, 625, 120, 800, 76, 24, 600, 0x18, MODE_NOSUPPORT},
	{473, 60, 560, 1184, 790, 32, 1024, 80, 19, 768, 0x24, MODE_NOSUPPORT},
	{474, 60, 683, 1440, 790, 32, 1280, 80, 19, 768, 0x24, MODE_NOSUPPORT},
	{474, 60, 720, 1520, 790, 32, 1360, 80, 19, 768, 0x24, MODE_NOSUPPORT},
	{565, 70, 750, 1328, 806, 136, 1024, 144, 35, 768, 0x00,
		MODE_NOSUPPORT},
	{600, 75, 788, 1312, 800, 96, 1024, 176, 31, 768, 0x18, MODE_NOSUPPORT},
	{603, 75, 820, 1360, 805, 104, 1024, 168, 34, 768, 0x2C,
		MODE_NOSUPPORT},
	{603, 75, 1023, 1696, 805, 128, 1280, 208, 34, 768, 0x2C,
		MODE_NOSUPPORT},
	{687, 85, 945, 1376, 809, 104, 1024, 176, 38, 768, 0x2C,
		MODE_NOSUPPORT},
	{686, 85, 1175, 1712, 809, 136, 1280, 216, 38, 768, 0x2C,
		MODE_NOSUPPORT},
	{611, 76, 831, 1360, 803, 112, 1024, 168, 34, 768, 0x00,
		MODE_NOSUPPORT},
	{537, 60, 817, 1520, 897, 120, 1152, 184, 30, 864, 0x00,
		MODE_NOSUPPORT},
	{638, 70, 945, 1480, 912, 96, 1152, 200, 47, 864, 0x00, MODE_NOSUPPORT},
	{675, 75, 1080, 1600, 900, 128, 1152, 256, 35, 864, 0x18,
		MODE_NOSUPPORT},
	{686, 75, 1000, 1456, 915, 128, 1152, 144, 42, 870, 0x00,
		MODE_NOSUPPORT},
	{771, 85, 1215, 1576, 907, 128, 1152, 232, 42, 864, 0x00,
		MODE_NOSUPPORT},
	{617, 65, 929, 1504, 937, 128, 1152, 195, 35, 900, 0x00,
		MODE_NOSUPPORT},
	{717, 76, 1055, 1472, 943, 96, 1152, 208, 41, 900, 0x00,
		MODE_NOSUPPORT},
	{450, 60, 742, 1650, 750, 40, 1280, 220, 25, 720, 0x00, MODE_NOSUPPORT},
	{560, 70, 950, 1696, 800, 128, 1280, 208, 31, 768, 0x00,
		MODE_NOSUPPORT},
	{603, 75, 1023, 1696, 805, 128, 1280, 208, 34, 768, 0x00,
		MODE_NOSUPPORT},
	{600, 60, 1080, 1800, 1000, 112, 1280, 312, 39, 960, 0x02,
		MODE_NOSUPPORT},
	{752, 75, 1300, 1728, 1005, 136, 1280, 224, 42, 960, 0x08,
		MODE_NOSUPPORT},
	{859, 85, 1485, 1728, 1011, 160, 1280, 224, 50, 960, 0x18,
		MODE_NOSUPPORT},
	{639, 60, 1080, 1688, 1066, 112, 1280, 248, 41, 1024, 0x18,
		MODE_NOSUPPORT},
	{800, 75, 1350, 1688, 1066, 144, 1280, 248, 41, 1024, 0x18,
		MODE_NOSUPPORT},
	{911, 85, 1575, 1728, 1072, 160, 1280, 224, 47, 1024, 0x18,
		MODE_NOSUPPORT},
	{647, 60, 1010, 1560, 1080, 32, 1400, 80, 27, 1050, 0x34,
		MODE_NOSUPPORT},
	{647, 60, 1190, 1840, 1080, 32, 1680, 80, 27, 1050, 0x34,
		MODE_NOSUPPORT},
	{653, 60, 1218, 1864, 1089, 144, 1400, 232, 36, 1050, 0x2C,
		MODE_NOSUPPORT},
	{653, 60, 1463, 2240, 1089, 176, 1680, 280, 36, 1050, 0x2C,
		MODE_NOSUPPORT},
	{823, 75, 1560, 1896, 1099, 144, 1400, 248, 46, 1050, 0x08,
		MODE_NOSUPPORT},
	{555, 60, 888, 1600, 926, 32, 1440, 80, 23, 900, 0x10, MODE_NOSUPPORT},
	{559, 60, 1065, 1904, 934, 152, 1440, 232, 31, 900, 0x08,
		MODE_NOSUPPORT},
	{706, 75, 1368, 1936, 942, 152, 1440, 248, 39, 900, 0x08,
		MODE_NOSUPPORT},
	{750, 60, 1620, 2160, 1250, 192, 1600, 304, 49, 1200, 0x00,
		MODE_NOSUPPORT},
	{666, 60, 1385, 2080, 1111, 32, 1920, 80, 28, 1080, 0x10,
		MODE_NOSUPPORT},
	{740, 60, 1540, 2080, 1235, 32, 1920, 80, 32, 1200, 0x10,
		MODE_NOSUPPORT},
	{717, 67, 1170, 1632, 1067, 112, 1280, 224, 41, 1024, 0x10,
		MODE_NOSUPPORT},
	{670, 60, 1728, 2576, 1118, 208, 1920, 328, 37, 1080, 0x00,
		MODE_NOSUPPORT},
	{675, 60, 1485, 2200, 1125, 44, 1920, 148, 41, 1080, 0x00,
		MODE_NOSUPPORT},
	{592, 60, 853, 1440, 988, 112, 1280, 80, 25, 960, 0x00, MODE_NOSUPPORT},
	{497, 60, 835, 1680, 831, 128, 1280, 200, 28, 800, 0x00,
		MODE_NOSUPPORT},
	{477, 60, 855, 1792, 798, 143, 1366, 213, 27, 768, 0x98,
		MODE_NOSUPPORT},
	{637, 60, 1090, 1712, 1063, 136, 1280, 216, 36, 1024, 0x08,
		MODE_NOSUPPORT},
	{349, 70, 285, 816, 500, 40, 640, 110, 19, 480, 0x00, MODE_NOSUPPORT},
	{477, 60, 855, 1792, 795, 112, 1360, 256, 24, 768, 0x98,
		MODE_NOSUPPORT},
	{477, 60, 859, 1800, 795, 144, 1360, 208, 26, 768, 0x80,
		MODE_NOSUPPORT},
	{559, 60, 1190, 2128, 932, 168, 1600, 256, 31, 900, 0x08,
		MODE_NOSUPPORT},
	{448, 60, 745, 1664, 748, 128, 1280, 192, 25, 720, 0x08,
		MODE_NOSUPPORT},
	{575, 72, 975, 1696, 801, 128, 1280, 208, 32, 768, 0x00,
		MODE_NOSUPPORT},
	{480, 60, 720, 1500, 800, 56, 1366, 64, 31, 768, 0x00, MODE_NOSUPPORT},
	{600, 60, 1080, 1800, 1000, 80, 1600, 96, 99, 900, 0x02,
		MODE_NOSUPPORT},
	{574, 50, 1496, 2608, 1147, 88, 1920, 72, 63, 1080, 0x00,
		MODE_NOSUPPORT},
	{562, 50, 1485, 2640, 1125, 44, 1920, 148, 41, 1080, 0x00,
		MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, MODE_NOSUPPORT},
	/*
	 * HF    VF      P-CLK   HTOTAL  VTOTAL  H(Bp+W) H-Act
	 * H-BP    V(BP+w) V-Act
	 */
};

const u8 bHdtvTimings = HDTV_TIMING_NUM;
const u8 bUserVgaTimings = USERMODE_TIMING;
const u8 bAllTimings =
	(sizeof(VGATIMING_TABLE) / sizeof(struct VGAMODE));
const u8 bVgaTimings =
	(ALL_TIMING_NUM - HDTV_TIMING_NUM - USERMODE_TIMING);
const u8 bUserVgaTimingBegin = (ALL_TIMING_NUM - USERMODE_TIMING);

u16
Get_VGAMODE_IHF(u8 mode)
{
	return VGATIMING_TABLE[mode].IHF;
}

u8
Get_VGAMODE_IVF(u8 mode)
{
	return VGATIMING_TABLE[mode].IVF;
}

u16
Get_VGAMODE_ICLK(u8 mode)
{
	if (mode > MODE_WAIT)
		return 0;

	if (fgIsVgaTiming(mode) &&
		(VGATIMING_TABLE[mode].ICLK < OVERSAMPLE_THRESHOLD))
		return VGATIMING_TABLE[mode].ICLK * 2;
	else
		return VGATIMING_TABLE[mode].ICLK;
}

u16
Get_VGAMODE_IHTOTAL(u8 mode)
{
	u16 u4Htotal = 0;

	if (mode > MODE_WAIT)
		return 0;

	if (fgIsVgaTiming(mode) &&
		(VGATIMING_TABLE[mode].ICLK < OVERSAMPLE_THRESHOLD))
		return VGATIMING_TABLE[mode].IHTOTAL * 2;

	u4Htotal = VGATIMING_TABLE[mode].IHTOTAL;
	return VGATIMING_TABLE[mode].IHTOTAL;
}

u16
Get_VGAMODE_IVTOTAL(u8 mode)
{
	return VGATIMING_TABLE[mode].IVTOTAL;
}

u16
Get_VGAMODE_IPH_STA(u8 mode)
{
	if (mode > MODE_WAIT)
		return 0;

	if (fgIsVgaTiming(mode) &&
		(VGATIMING_TABLE[mode].ICLK < OVERSAMPLE_THRESHOLD))
		return (VGATIMING_TABLE[mode].IPH_BP +
			       VGATIMING_TABLE[mode].IPH_SYNCW) *
		       2;
	else
		return VGATIMING_TABLE[mode].IPH_BP +
		       VGATIMING_TABLE[mode].IPH_SYNCW;
}

u16
Get_VGAMODE_IPH_WID(u8 mode)
{
	if (mode > MODE_WAIT)
		return 0;

	if (fgIsVgaTiming(mode) &&
		(VGATIMING_TABLE[mode].ICLK < OVERSAMPLE_THRESHOLD))
		return VGATIMING_TABLE[mode].IPH_WID * 2;
	else
		return VGATIMING_TABLE[mode].IPH_WID;
}

u16
Get_VGAMODE_IPH_SYNCW(u8 mode)
{
	if (mode > MODE_WAIT)
		return 0;

	if (fgIsVgaTiming(mode) &&
		(VGATIMING_TABLE[mode].ICLK < OVERSAMPLE_THRESHOLD))
		return VGATIMING_TABLE[mode].IPH_SYNCW * 2;
	else
		return VGATIMING_TABLE[mode].IPH_SYNCW;
}

u16
Get_VGAMODE_IPH_BP(u8 mode)
{
	if (mode > MODE_WAIT)
		return 0;

	if (fgIsVgaTiming(mode) &&
		(VGATIMING_TABLE[mode].ICLK < OVERSAMPLE_THRESHOLD))
		return VGATIMING_TABLE[mode].IPH_BP * 2;
	else
		return VGATIMING_TABLE[mode].IPH_BP;
}

u8
Get_VGAMODE_IPV_STA(u8 mode)
{
	return VGATIMING_TABLE[mode].IPV_STA;
}

u16
Get_VGAMODE_IPV_LEN(u8 mode)
{
	return VGATIMING_TABLE[mode].IPV_LEN;
}

u16
Get_VGAMODE_COMBINE(u8 mode)
{
	return VGATIMING_TABLE[mode].COMBINE;
}

u16
Get_VGAMODE_ID(u8 mode)
{
	return VGATIMING_TABLE[mode].timing_id;
}

u8
Get_VGAMODE_OverSample(u8 mode)
{
	if (mode > MODE_WAIT)
		return 0;

	if (fgIsVgaTiming(mode) &&
		(VGATIMING_TABLE[mode].ICLK < OVERSAMPLE_THRESHOLD))
		return 1;
	else
		return VGATIMING_TABLE[mode].COMBINE & 0x01;
}
