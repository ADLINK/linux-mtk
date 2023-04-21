// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 MediaTek Inc.
 * Author: Pedro Tsai <pedro.tsai@mediatek.com>
 *
 * Based on panel-sharp-nt35532 driver.
 */

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#include <drm/drm_crtc.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_panel.h>

#include <video/mipi_display.h>

struct lcm_init_struct {
	u8 cmd;
	u8 count;
	u8 params[64];
};

static struct lcm_init_struct init_setting[] = {
	{0x00, 1, {0x00} },
	{0xFF, 4, {0x19, 0x01, 0x01, 0x00} },
	{0x00, 1, {0x80} },
	{0xFF, 2, {0x19, 0x01} },
	{0x00, 1, {0x00} },
	{0x1C, 1, {0x33} },
	{0x00, 1, {0xA0} },
	{0xC1, 1, {0xE8} },
	{0x00, 1, {0xA7} },
	{0xC1, 1, {0x00} },
	{0x00, 1, {0x90} },
	{0xC0, 6, {0x00, 0x2F, 0x00, 0x00, 0x00, 0x01} },
	{0x00, 1, {0xC0} },
	{0xC0, 6, {0x00, 0x2F, 0x00, 0x00, 0x00, 0x01} },
	{0x00, 1, {0x9A} },
	{0xC0, 1, {0x1E} },
	{0x00, 1, {0xAC} },
	{0xC0, 1, {0x06} },
	{0x00, 1, {0xDC} },
	{0xC0, 1, {0x06} },
	{0x00, 1, {0x81} },
	{0xA5, 1, {0x06} },
	{0x00, 1, {0x82} },
	{0xC4, 1, {0xF0} },
	{0x00, 1, {0x92} },
	{0xE9, 1, {0x00} },
	{0x00, 1, {0x90} },
	{0xF3, 1, {0x01} },
	{0x00, 1, {0x82} },
	{0xA5, 1, {0x1F} },
	{0x00, 1, {0x93} },
	{0xC5, 1, {0x19} },
	{0x00, 1, {0x95} },
	{0xC5, 1, {0x28} },
	{0x00, 1, {0x97} },
	{0xC5, 1, {0x18} },
	{0x00, 1, {0x99} },
	{0xC5, 1, {0x23} },
	{0x00, 1, {0x9B} },
	{0xC5, 2, {0x44, 0x40} },
	{0x00, 1, {0x00} },
	{0xD9, 2, {0x00, 0xBA} },
	{0x00, 1, {0x00} },
	{0xD8, 2, {0x1B, 0x1B} },
	{0x00, 1, {0xB3} },
	{0xC0, 1, {0xCC} },
	{0x00, 1, {0xBC} },
	{0xC0, 1, {0x00} },
	{0x00, 1, {0x84} },
	{0xC4, 1, {0x22} },
	{0x00, 1, {0x94} },
	{0xC1, 1, {0x84} },
	{0x00, 1, {0x98} },
	{0xC1, 1, {0x74} },
	{0x00, 1, {0x80} },
	{0xC4, 1, {0x38} },
	{0x00, 1, {0xCD} },
	{0xF5, 1, {0x19} },
	{0x00, 1, {0xDB} },
	{0xF5, 1, {0x19} },
	{0x00, 1, {0xF5} },
	{0xC1, 1, {0x40} },
	{0x00, 1, {0xB9} },
	{0xC0, 1, {0x11} },
	{0x00, 1, {0x8D} },
	{0xF5, 1, {0x20} },
	{0x00, 1, {0x80} },
	{0xC0, 14, {0x00, 0x86, 0x00, 0x0A, 0x0A, 0x00, 0x86, 0x0A, 0x0A, 0x00,
		    0x86, 0x00, 0x0A, 0x0A} },
	{0x00, 1, {0xF0} },
	{0xC3, 6, {0x00, 0x00, 0x00, 0x00, 0x00, 0x80} },
	{0x00, 1, {0xA0} },
	{0xC0, 7, {0x00, 0x00, 0x03, 0x00, 0x00, 0x1E, 0x06} },
	{0x00, 1, {0xD0} },
	{0xC0, 7, {0x00, 0x00, 0x03, 0x00, 0x00, 0x1E, 0x06} },
	{0x00, 1, {0x90} },
	{0xC2, 4, {0x84, 0x01, 0x3B, 0x40} },
	{0x00, 1, {0xB0} },
	{0xC2, 8, {0x02, 0x01, 0x45, 0x43, 0x02, 0x01, 0x45, 0x43} },
	{0x00, 1, {0x80} },
	{0xC3, 12, {0x84, 0x08, 0x03, 0x00, 0x02, 0x89, 0x82, 0x08, 0x03, 0x00,
		    0x02, 0x89} },
	{0x00, 1, {0x90} },
	{0xC3, 12, {0x83, 0x08, 0x03, 0x00, 0x02, 0x89, 0x81, 0x08, 0x03, 0x00,
		    0x02, 0x89} },
	{0x00, 1, {0x80} },
	{0xCC, 15, {0x09, 0x0D, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
		    0x0E, 0x28, 0x28, 0x28, 0x28} },
	{0x00, 1, {0x90} },
	{0xCC, 15, {0x0D, 0x09, 0x14, 0x13, 0x12, 0x11, 0x15, 0x16, 0x17, 0x18,
		    0x0E, 0x28, 0x28, 0x28, 0x28} },
	{0x00, 1, {0xA0} },
	{0xCC, 15, {0x1D, 0x1E, 0x1F, 0x19, 0x1A, 0x1B, 0x1C, 0x20, 0x21, 0x22,
		    0x23, 0x24, 0x25, 0x26, 0x27} },
	{0x00, 1, {0xB0} },
	{0xCC, 8, {0x01, 0x02, 0x03, 0x05, 0x06, 0x07, 0x04, 0x08} },
	{0x00, 1, {0xC0} },
	{0xCC, 12, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x77} },
	{0x00, 1, {0xD0} },
	{0xCC, 12, {0xFF, 0x0F, 0x30, 0xC0, 0x0F, 0x30, 0x00, 0x00, 0x33, 0x03,
		    0x00, 0x77} },
	{0x00, 1, {0xDE} },
	{0xCC, 1, {0x00} },
	{0x00, 1, {0x80} },
	{0xCB, 15, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x30, 0x00, 0x00, 0x00, 0x00} },
	{0x00, 1, {0x90} },
	{0xCB, 15, {0x30, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00, 0x00} },
	{0x00, 1, {0xA0} },
	{0xCB, 15, {0x15, 0x15, 0x05, 0xF5, 0x05, 0xF5, 0x00, 0x00, 0x00, 0x00,
		    0x15, 0x00, 0x00, 0x00, 0x00} },
	{0x00, 1, {0xB0} },
	{0xCB, 15, {0x00, 0x01, 0xFD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		    0x00, 0x00, 0x00, 0x00, 0x00} },
	{0x00, 1, {0xC0} },
	{0xCB, 8, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77} },
	{0x00, 1, {0xD0} },
	{0xCB, 8, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77} },
	{0x00, 1, {0xE0} },
	{0xCB, 8, {0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x77, 0x77} },
	{0x00, 1, {0xF0} },
	{0xCB, 8, {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x77, 0x77} },
	{0x00, 1, {0x80} },
	{0xCD, 15, {0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x01, 0x12,
		    0x11, 0x03, 0x04, 0x0B, 0x17} },
	{0x00, 1, {0x90} },
	{0xCD, 11, {0x3D, 0x02, 0x3D, 0x25, 0x25, 0x25, 0x1F, 0x20, 0x21, 0x25,
		    0x25} },
	{0x00, 1, {0xA0} },
	{0xCD, 15, {0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x01, 0x12,
		    0x11, 0x05, 0x06, 0x0B, 0x17} },
	{0x00, 1, {0xB0} },
	{0xCD, 11, {0x17, 0x02, 0x3D, 0x25, 0x25, 0x25, 0x1F, 0x20, 0x21, 0x25,
		    0x25} },
	{0x00, 1, {0x00} },
	{0xE1, 24, {0x56, 0x56, 0x59, 0x60, 0x64, 0x67, 0x6d, 0x79, 0x7e, 0x8c,
		    0x93, 0x99, 0x62, 0x5e, 0x5e, 0x4f, 0x3e, 0x2f, 0x24, 0x1d,
		    0x16, 0x0c, 0x08, 0x04} },
	{0x00, 1, {0x00} },
	{0xE2, 24, {0x56, 0x56, 0x59, 0x60, 0x64, 0x67, 0x6d, 0x79, 0x7e, 0x8c,
		    0x93, 0x99, 0x62, 0x5e, 0x5a, 0x4b, 0x3e, 0x2f, 0x24, 0x1d,
		    0x16, 0x0c, 0x08, 0x04} },
	{0x00, 1, {0x00} },
	{0xE3, 24, {0x53, 0x56, 0x58, 0x5c, 0x61, 0x65, 0x6c, 0x77, 0x7c, 0x8b,
		    0x93, 0x99, 0x62, 0x5e, 0x5d, 0x4f, 0x3e, 0x2e, 0x24, 0x1d,
		    0x16, 0x0c, 0x07, 0x04} },
	{0x00, 1, {0x00} },
	{0xE4, 24, {0x53, 0x56, 0x58, 0x5c, 0x61, 0x65, 0x6c, 0x77, 0x7c, 0x8b,
		    0x93, 0x99, 0x62, 0x5e, 0x59, 0x4b, 0x3e, 0x2e, 0x24, 0x1d,
		    0x16, 0x0c, 0x07, 0x04} },
	{0x00, 1, {0x00} },
	{0xE5, 24, {0x20, 0x22, 0x29, 0x35, 0x3f, 0x45, 0x51, 0x63, 0x6e, 0x81,
		    0x8c, 0x95, 0x64, 0x5f, 0x5e, 0x4e, 0x3e, 0x2e, 0x24, 0x1d,
		    0x16, 0x0c, 0x07, 0x04} },
	{0x00, 1, {0x00} },
	{0xE6, 24, {0x20, 0x22, 0x29, 0x35, 0x3f, 0x45, 0x51, 0x63, 0x6e, 0x81,
		    0x8c, 0x95, 0x64, 0x5f, 0x5a, 0x4a, 0x3e, 0x2e, 0x24, 0x1d,
		    0x16, 0x0c, 0x07, 0x04} },
	{0x00, 1, {0xD4} },
	{0xC3, 4, {0x01, 0x01, 0x01, 0x01} },
	{0x00, 1, {0xF7} },
	{0xC3, 4, {0x03, 0x1B, 0x00, 0x00} },
	{0x00, 1, {0xF2} },
	{0xC1, 3, {0x80, 0x0F, 0x0F} },
	{0x00, 1, {0xC2} },
	{0xC5, 1, {0x12} },
	{0x00, 1, {0xA8} },
	{0xC4, 1, {0x11} },
	{0x00, 1, {0x00} },
	{0xFF, 3, {0xFF, 0xFF, 0xFF} },
};

static ssize_t tpv_r_write_buffer(struct mipi_dsi_device *dsi, u8 cmd,
			       const void *data, size_t len)
{
	ssize_t err;
	size_t size;
	u8 *tx;

	if (len > 0) {
		size = len + 1;

		tx = kmalloc(size, GFP_KERNEL);
		if (!tx)
			return -ENOMEM;

		tx[0] = cmd;
		memcpy(&tx[1], data, len);
	} else {
		tx = &cmd;
		size = 1;
	}

	if (cmd < 0xB0)
		err = mipi_dsi_dcs_write_buffer(dsi, tx, size);
	else
		err = mipi_dsi_generic_write(dsi, tx, size);

	if (len > 0)
		kfree(tx);

	return err;
}

static ssize_t tpv_r_push_table(struct mipi_dsi_device *dsi,
				const struct lcm_init_struct *table,
				size_t len)
{
	ssize_t err;
	size_t i;

	for (i = 0; i < len; i++) {
		err = tpv_r_write_buffer(dsi, table[i].cmd, table[i].params,
					 table[i].count);
		if (err < 0)
			return err;
	}

	return err;
}

struct tpv_otm_panel {
	struct drm_panel base;
	struct mipi_dsi_device *dsi;

	struct gpio_desc *reset_gpio;
	struct gpio_desc *pwr_gpio;
	struct gpio_desc *pwr2_gpio;

	struct backlight_device *backlight;

	bool prepared;
	bool enabled;

	const struct drm_display_mode *mode;
};

static inline struct tpv_otm_panel *to_tpv_otm_panel(struct drm_panel *panel)
{
	return container_of(panel, struct tpv_otm_panel, base);
}

static int tpv_otm_panel_on(struct tpv_otm_panel *tpv_otm)
{
	struct mipi_dsi_device *dsi = tpv_otm->dsi;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	ret = tpv_r_push_table(dsi, init_setting, ARRAY_SIZE(init_setting));
	if (ret < 0)
		return ret;

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0)
		return ret;

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0)
		return ret;

	return 0;
}

static int tpv_otm_panel_off(struct tpv_otm_panel *tpv_otm)
{
	struct mipi_dsi_device *dsi = tpv_otm->dsi;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0)
		return ret;

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0)
		return ret;

	return 0;
}


static int tpv_otm_panel_disable(struct drm_panel *panel)
{
	struct tpv_otm_panel *tpv_otm = to_tpv_otm_panel(panel);

	if (!tpv_otm->enabled)
		return 0;

	backlight_disable(tpv_otm->backlight);

	tpv_otm->enabled = false;

	return 0;
}

static int tpv_otm_panel_unprepare(struct drm_panel *panel)
{
	struct tpv_otm_panel *tpv_otm = to_tpv_otm_panel(panel);
	int ret;

	if (!tpv_otm->prepared)
		return 0;

	ret = tpv_otm_panel_off(tpv_otm);
	if (ret < 0) {
		dev_err(panel->dev, "failed to set panel off: %d\n", ret);
		return ret;
	}

	gpiod_set_value(tpv_otm->pwr2_gpio, 0);
	gpiod_set_value(tpv_otm->pwr_gpio, 0);
	gpiod_set_value(tpv_otm->reset_gpio, 0);

	tpv_otm->prepared = false;

	return 0;
}

static int tpv_otm_panel_prepare(struct drm_panel *panel)
{
	struct tpv_otm_panel *tpv_otm = to_tpv_otm_panel(panel);
	int ret;

	if (tpv_otm->prepared)
		return 0;

	gpiod_set_value(tpv_otm->pwr_gpio, 1);
	msleep(20);
	gpiod_set_value(tpv_otm->pwr2_gpio, 1);
	msleep(20);

	gpiod_set_value(tpv_otm->reset_gpio, 0);
	msleep(5);
	gpiod_set_value(tpv_otm->reset_gpio, 1);
	msleep(20);

	ret = tpv_otm_panel_on(tpv_otm);
	if (ret < 0) {
		dev_err(panel->dev, "failed to set panel on: %d\n", ret);
		goto poweroff;
	}
	tpv_otm->prepared = true;

	return 0;

poweroff:
	gpiod_set_value(tpv_otm->pwr2_gpio, 0);
	gpiod_set_value(tpv_otm->pwr_gpio, 0);
	gpiod_set_value(tpv_otm->reset_gpio, 0);

	return ret;
}

static int tpv_otm_panel_enable(struct drm_panel *panel)
{
	struct tpv_otm_panel *tpv_otm = to_tpv_otm_panel(panel);

	if (tpv_otm->enabled)
		return 0;

	backlight_enable(tpv_otm->backlight);

	tpv_otm->enabled = true;

	return 0;
}

static const struct drm_display_mode default_mode = {
	.clock = 134500,  /*  clock: (htotal * vtotal * 60) /1000 */
	.hdisplay = 1080,
	.hsync_start = 1080 + 40,
	.hsync_end = 1080 + 40 + 10,
	.htotal = 1080 + 40 + 10 + 20,
	.vdisplay = 1920,
	.vsync_start = 1920 + 20,
	.vsync_end = 1920 + 20 + 2,
	.vtotal = 1920 + 20 + 2 + 8,
};

static int tpv_otm_panel_get_modes(struct drm_panel *panel,
				   struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &default_mode);
	if (!mode) {
		dev_err(panel->dev, "failed to add mode %ux%ux@%u\n",
				default_mode.hdisplay, default_mode.vdisplay,
				drm_mode_vrefresh(&default_mode));
		return -ENOMEM;
	}

	drm_mode_set_name(mode);

	drm_mode_probed_add(connector, mode);


	connector->display_info.width_mm = 80;
	connector->display_info.height_mm = 136;

	return 1;
}

static const struct drm_panel_funcs tpv_otm_panel_funcs = {
	.disable = tpv_otm_panel_disable,
	.unprepare = tpv_otm_panel_unprepare,
	.prepare = tpv_otm_panel_prepare,
	.enable = tpv_otm_panel_enable,
	.get_modes = tpv_otm_panel_get_modes,
};

static int tpv_otm_panel_add(struct tpv_otm_panel *tpv_otm)
{
	struct device *dev = &tpv_otm->dsi->dev;

	tpv_otm->mode = &default_mode;
	tpv_otm->reset_gpio = devm_gpiod_get(dev, "reset",
					      GPIOD_OUT_LOW);
	if (IS_ERR(tpv_otm->reset_gpio)) {
		dev_err(dev, "cannot get reset-gpios %ld\n",
			PTR_ERR(tpv_otm->reset_gpio));
		return PTR_ERR(tpv_otm->reset_gpio);
	}

	tpv_otm->pwr_gpio = devm_gpiod_get(dev, "pwr",
					    GPIOD_OUT_LOW);
	if (IS_ERR(tpv_otm->pwr_gpio)) {
		dev_err(dev, "cannot get pwr-gpios %ld\n",
			PTR_ERR(tpv_otm->pwr_gpio));
		return PTR_ERR(tpv_otm->pwr_gpio);
	}

	tpv_otm->pwr2_gpio = devm_gpiod_get(dev, "pwr2",
					     GPIOD_OUT_LOW);
	if (IS_ERR(tpv_otm->pwr_gpio)) {
		dev_err(dev, "cannot get pwr2-gpios %ld\n",
			PTR_ERR(tpv_otm->pwr2_gpio));
		return PTR_ERR(tpv_otm->pwr2_gpio);
	}

	tpv_otm->backlight = devm_of_find_backlight(dev);
	if (IS_ERR(tpv_otm->backlight)) {
		dev_err(dev, "failed to get backlight\n");
		return PTR_ERR(tpv_otm->backlight);
	}

	drm_panel_init(&tpv_otm->base, &tpv_otm->dsi->dev, &tpv_otm_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	drm_panel_add(&tpv_otm->base);

	return 0;
}

static void tpv_otm_panel_del(struct tpv_otm_panel *tpv_otm)
{
	if (tpv_otm->base.dev)
		drm_panel_remove(&tpv_otm->base);
}


static int tpv_otm_panel_probe(struct mipi_dsi_device *dsi)
{
	struct tpv_otm_panel *tpv_otm;
	int ret;

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
			MIPI_DSI_MODE_VIDEO_HSE |
			MIPI_DSI_CLOCK_NON_CONTINUOUS |
			MIPI_DSI_MODE_NO_EOT_PACKET;

	tpv_otm = devm_kzalloc(&dsi->dev, sizeof(*tpv_otm), GFP_KERNEL);
	if (!tpv_otm)
		return -ENOMEM;

	mipi_dsi_set_drvdata(dsi, tpv_otm);
	tpv_otm->dsi = dsi;

	ret = tpv_otm_panel_add(tpv_otm);
	if (ret < 0)
		return ret;

	return mipi_dsi_attach(dsi);
}

static int tpv_otm_panel_remove(struct mipi_dsi_device *dsi)
{
	struct tpv_otm_panel *tpv_otm = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = tpv_otm_panel_disable(&tpv_otm->base);
	if (ret < 0)
		dev_err(&dsi->dev, "failed to disable panel: %d\n", ret);

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "failed to detach from DSI host: %d\n", ret);

	tpv_otm_panel_del(tpv_otm);

	return 0;
}

static void tpv_otm_panel_shutdown(struct mipi_dsi_device *dsi)
{
	struct tpv_otm_panel *tpv_otm = mipi_dsi_get_drvdata(dsi);

	tpv_otm_panel_disable(&tpv_otm->base);
}

static const struct of_device_id tpv_otm_of_match[] = {
	{ .compatible = "tpv,otm1901a", },
	{ }
};
MODULE_DEVICE_TABLE(of, tpv_otm_of_match);

static struct mipi_dsi_driver tpv_otm_panel_driver = {
	.driver = {
		.name = "panel-tpv-otm1901a",
		.of_match_table = tpv_otm_of_match,
	},
	.probe = tpv_otm_panel_probe,
	.remove = tpv_otm_panel_remove,
	.shutdown = tpv_otm_panel_shutdown,
};
module_mipi_dsi_driver(tpv_otm_panel_driver);

MODULE_AUTHOR("Pedro Tsai <pedro.tsai@mediatek.com>");
MODULE_LICENSE("GPL v2");
