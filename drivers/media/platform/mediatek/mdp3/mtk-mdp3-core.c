// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2022 MediaTek Inc.
 * Author: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#include <linux/clk.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/remoteproc.h>
#include <linux/remoteproc/mtk_scp.h>
#include <media/videobuf2-dma-contig.h>

#include "mtk-mdp3-core.h"
#include "mtk-mdp3-m2m.h"
#include "mtk-mdp3-capture.h"

#include "mt8183/mdp3-plat-mt8183.h"
#include "mt8195/mdp3-plat-mt8195.h"
#include "mt8188/mdp3-plat-mt8188.h"

static const struct mtk_mdp_driver_data mt8183_mdp_driver_data = {
	.mdp_plat_id = MT8183,
	.mdp_probe_infra = mt8183_mdp_probe_infra,
	.mdp_sub_comp_dt_ids = mt8183_sub_comp_dt_ids,
	.mdp_cfg = &mt8183_plat_cfg,
	.mdp_mutex_table_idx = mt8183_mutex_idx,
	.comp_data = mt8183_mdp_comp_data,
	.comp_data_len = ARRAY_SIZE(mt8183_mdp_comp_data),
	.pipe_info = mt8183_pipe_info,
	.pipe_info_len = ARRAY_SIZE(mt8183_pipe_info),
	.format = mt8183_formats,
	.format_len = ARRAY_SIZE(mt8183_formats),
	.def_limit = &mt8183_mdp_def_limit,
	.pp_used = MDP_PP_USED_1,
};

static const struct mtk_mdp_driver_data mt8195_mdp_driver_data = {
	.mdp_plat_id = MT8195,
	.mdp_probe_infra = mt8195_mdp_probe_infra,
	.mdp_sub_comp_dt_ids = mt8195_sub_comp_dt_ids,
	.mdp_cfg = &mt8195_plat_cfg,
	.mdp_mutex_table_idx = mt8195_mutex_idx,
	.comp_data = mt8195_mdp_comp_data,
	.comp_data_len = ARRAY_SIZE(mt8195_mdp_comp_data),
	.pipe_info = mt8195_pipe_info,
	.pipe_info_len = ARRAY_SIZE(mt8195_pipe_info),
	.format = mt8195_formats,
	.format_len = ARRAY_SIZE(mt8195_formats),
	.def_limit = &mt8195_mdp_def_limit,
	.pp_criteria = &mt8195_mdp_pp_criteria,
	.pp_used = MDP_PP_USED_4,
};

static const struct mtk_mdp_driver_data mt8188_mdp_driver_data = {
	.mdp_plat_id = MT8188,
	.mdp_probe_infra = mt8188_mdp_probe_infra,
	.mdp_sub_comp_dt_ids = mt8188_sub_comp_dt_ids,
	.mdp_cfg = &mt8188_plat_cfg,
	.mdp_mutex_table_idx = mt8188_mutex_idx,
	.comp_data = mt8188_mdp_comp_data,
	.comp_data_len = ARRAY_SIZE(mt8188_mdp_comp_data),
	.pipe_info = mt8188_pipe_info,
	.pipe_info_len = ARRAY_SIZE(mt8188_pipe_info),
	.format = mt8188_formats,
	.format_len = ARRAY_SIZE(mt8188_formats),
	.def_limit = &mt8188_mdp_def_limit,
	.pp_criteria = &mt8188_mdp_pp_criteria,
	.pp_used = MDP_PP_USED_2,
};

static const struct of_device_id mdp_of_ids[] = {
	{ .compatible = "mediatek,mt8183-mdp3-rdma",
	  .data = &mt8183_mdp_driver_data,
	},
	{ .compatible = "mediatek,mt8195-mdp3-rdma",
	  .data = &mt8195_mdp_driver_data,
	},
	{ .compatible = "mediatek,mt8188-mdp3-rdma",
	  .data = &mt8188_mdp_driver_data,
	},
	{},
};
MODULE_DEVICE_TABLE(of, mdp_of_ids);

static struct platform_device *__get_pdev_by_id(struct platform_device *pdev,
						struct platform_device *from,
						enum mdp_infra_id id)
{
	struct device_node *node, *f = NULL;
	struct platform_device *mdp_pdev = NULL;
	const struct mtk_mdp_driver_data *mdp_data;
	const char *compat;

	if (!pdev)
		return ERR_PTR(-ENODEV);

	if (id < MDP_INFRA_MMSYS || id >= MDP_INFRA_MAX) {
		dev_err(&pdev->dev, "Illegal infra id %d\n", id);
		return ERR_PTR(-ENODEV);
	}

	mdp_data = of_device_get_match_data(&pdev->dev);
	if (!mdp_data) {
		dev_err(&pdev->dev, "have no driver data to find node\n");
		return ERR_PTR(-ENODEV);
	}

	compat = mdp_data->mdp_probe_infra[id].compatible;
	if (strlen(compat) == 0)
		return NULL;

	if (from)
		f = from->dev.of_node;
	node = of_find_compatible_node(f, NULL, compat);
	if (WARN_ON(!node)) {
		dev_err(&pdev->dev, "find node from id %d failed\n", id);
		return ERR_PTR(-ENODEV);
	}

	mdp_pdev = of_find_device_by_node(node);
	of_node_put(node);
	if (WARN_ON(!mdp_pdev)) {
		dev_err(&pdev->dev, "find pdev from id %d failed\n", id);
		return ERR_PTR(-ENODEV);
	}

	return mdp_pdev;
}

struct platform_device *mdp_get_plat_device(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *mdp_node;
	struct platform_device *mdp_pdev;

	mdp_node = of_parse_phandle(dev->of_node, MDP_PHANDLE_NAME, 0);
	if (!mdp_node) {
		dev_err(dev, "can't get node %s\n", MDP_PHANDLE_NAME);
		return NULL;
	}

	mdp_pdev = of_find_device_by_node(mdp_node);
	of_node_put(mdp_node);

	return mdp_pdev;
}
EXPORT_SYMBOL_GPL(mdp_get_plat_device);

int mdp_vpu_get_locked(struct mdp_dev *mdp)
{
	int ret = 0;

	if (mdp->vpu_count++ == 0) {
		ret = rproc_boot(mdp->rproc_handle);
		if (ret) {
			dev_err(&mdp->pdev->dev,
				"vpu_load_firmware failed %d\n", ret);
			goto err_load_vpu;
		}
		ret = mdp_vpu_register(mdp);
		if (ret) {
			dev_err(&mdp->pdev->dev,
				"mdp_vpu register failed %d\n", ret);
			goto err_reg_vpu;
		}
		ret = mdp_vpu_dev_init(&mdp->vpu, mdp->scp, &mdp->vpu_lock);
		if (ret) {
			dev_err(&mdp->pdev->dev,
				"mdp_vpu device init failed %d\n", ret);
			goto err_init_vpu;
		}
	}
	return 0;

err_init_vpu:
	mdp_vpu_unregister(mdp);
err_reg_vpu:
err_load_vpu:
	mdp->vpu_count--;
	return ret;
}

void mdp_vpu_put_locked(struct mdp_dev *mdp)
{
	if (--mdp->vpu_count == 0) {
		mdp_vpu_dev_deinit(&mdp->vpu);
		mdp_vpu_unregister(mdp);
	}
}

void mdp_video_device_release(struct video_device *vdev)
{
	struct mdp_dev *mdp = (struct mdp_dev *)video_get_drvdata(vdev);
	int i;

	for (i = 0; i < mdp->mdp_data->pp_used; i++)
		if (mdp->cmdq_clt[i])
			cmdq_mbox_destroy(mdp->cmdq_clt[i]);

	scp_put(mdp->scp);

	destroy_workqueue(mdp->job_wq);
	destroy_workqueue(mdp->clock_wq);

	pm_runtime_disable(&mdp->pdev->dev);

	vb2_dma_contig_clear_max_seg_size(&mdp->pdev->dev);

	mdp_comp_destroy(mdp);
	for (i = 0; i < MDP_PIPE_MAX; i++) {
		if (mdp->mdp_mutex[i])
			mtk_mutex_put(mdp->mdp_mutex[i]);
		if (mdp->mdp_mutex2[i])
			mtk_mutex_put(mdp->mdp_mutex2[i]);
	}

	mdp_vpu_shared_mem_free(&mdp->vpu);
	v4l2_m2m_release(mdp->m2m_dev);
	kfree(mdp);
}

static int mdp_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mdp_dev *mdp;
	struct platform_device *mm_pdev, *mm2_pdev;
	int ret, i, mutex_id;

	mdp = kzalloc(sizeof(*mdp), GFP_KERNEL);
	if (!mdp) {
		ret = -ENOMEM;
		goto err_return;
	}

	mdp->pdev = pdev;
	mdp->mdp_data = of_device_get_match_data(&pdev->dev);

	if (strcmp(dev->of_node->name, MDP_NODE_NAME)) {
		platform_set_drvdata(pdev, mdp);
		goto success_return;
	}

	mm_pdev = __get_pdev_by_id(pdev, NULL, MDP_INFRA_MMSYS);
	if (IS_ERR_OR_NULL(mm_pdev)) {
		ret = -ENODEV;
		goto err_destroy_device;
	}
	mdp->mdp_mmsys = &mm_pdev->dev;

	/* Not all chips have MMSYS2, config may be null */
	mm2_pdev = __get_pdev_by_id(pdev, mm_pdev, MDP_INFRA_MMSYS2);
	if (IS_ERR(mm2_pdev)) {
		ret = PTR_ERR(mm2_pdev);
		goto err_destroy_device;
	}
	mdp->mdp_mmsys2 = &mm2_pdev->dev;

	mm_pdev = __get_pdev_by_id(pdev, NULL, MDP_INFRA_MUTEX);
	if (IS_ERR_OR_NULL(mm_pdev)) {
		ret = -ENODEV;
		goto err_destroy_device;
	}
	mm2_pdev = __get_pdev_by_id(pdev, mm_pdev, MDP_INFRA_MUTEX2);
	/* MUTEX2 must works with MMSYS2 */
	if ((IS_ERR(mm2_pdev)) ||
	    (mm2_pdev && IS_ERR_OR_NULL(mdp->mdp_mmsys2))) {
		ret = -ENODEV;
		goto err_destroy_device;
	}
	for (i = 0; i < mdp->mdp_data->pipe_info_len; i++) {
		struct platform_device *p;
		struct mtk_mutex **m;
		u32 id;

		mutex_id = mdp->mdp_data->pipe_info[i].mutex_id;
		id = mdp->mdp_data->pipe_info[i].mmsys_id;
		p = (id && mm2_pdev) ? mm2_pdev : mm_pdev;
		m = (id && mm2_pdev) ?
			mdp->mdp_mutex2 : mdp->mdp_mutex;
		if (m[mutex_id])
			continue;
		m[mutex_id] = mtk_mutex_get(&p->dev);
		if (!m[mutex_id]) {
			ret = -ENODEV;
			goto err_free_mutex;
		}
	}

	ret = mdp_comp_config(mdp);
	if (ret) {
		dev_err(dev, "Failed to config mdp components\n");
		goto err_free_mutex;
	}

	mdp->job_wq = alloc_workqueue(MDP_MODULE_NAME, WQ_FREEZABLE, 0);
	if (!mdp->job_wq) {
		dev_err(dev, "Unable to create job workqueue\n");
		ret = -ENOMEM;
		goto err_deinit_comp;
	}

	mdp->clock_wq = alloc_workqueue(MDP_MODULE_NAME "-clock", WQ_FREEZABLE,
					0);
	if (!mdp->clock_wq) {
		dev_err(dev, "Unable to create clock workqueue\n");
		ret = -ENOMEM;
		goto err_destroy_job_wq;
	}

	mm_pdev = __get_pdev_by_id(pdev, NULL, MDP_INFRA_SCP);
	if (IS_ERR_OR_NULL(mm_pdev)) {
		dev_err(&pdev->dev, "Could not get scp device\n");
		ret = -ENODEV;
		goto err_destroy_clock_wq;
	}
	mdp->scp = platform_get_drvdata(mm_pdev);
	mdp->rproc_handle = scp_get_rproc(mdp->scp);
	dev_dbg(&pdev->dev, "MDP rproc_handle: %pK", mdp->rproc_handle);

	mutex_init(&mdp->vpu_lock);
	mutex_init(&mdp->m2m_lock);
	mutex_init(&mdp->cap_lock);

	for (i = 0; i < mdp->mdp_data->pp_used; i++) {
		mdp->cmdq_clt[i] = cmdq_mbox_create(dev, i);
		if (IS_ERR(mdp->cmdq_clt[i])) {
			ret = PTR_ERR(mdp->cmdq_clt[i]);
			goto err_mbox_destroy;
		}
	}

	init_waitqueue_head(&mdp->callback_wq);
	ida_init(&mdp->mdp_ida);
	platform_set_drvdata(pdev, mdp);

	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	ret = v4l2_device_register(dev, &mdp->v4l2_dev);
	if (ret) {
		dev_err(dev, "Failed to register v4l2 device\n");
		ret = -EINVAL;
		goto err_mbox_destroy;
	}

	ret = mdp_m2m_device_register(mdp);
	if (ret) {
		v4l2_err(&mdp->v4l2_dev, "Failed to register m2m device\n");
		goto err_unregister_device;
	}

	if (mdp->comp[MDP_COMP_SPLIT])
		mdp_cap_init(mdp);

success_return:
	dev_dbg(dev, "mdp-%d registered successfully\n", pdev->id);
	return 0;

err_unregister_device:
	v4l2_device_unregister(&mdp->v4l2_dev);
err_mbox_destroy:
	while (--i >= 0)
		cmdq_mbox_destroy(mdp->cmdq_clt[i]);
	scp_put(mdp->scp);
err_destroy_clock_wq:
	destroy_workqueue(mdp->clock_wq);
err_destroy_job_wq:
	destroy_workqueue(mdp->job_wq);
err_deinit_comp:
	mdp_comp_destroy(mdp);
err_free_mutex:
	for (i = 0; i < mdp->mdp_data->pipe_info_len; i++) {
		if (mdp->mdp_mutex[i])
			mtk_mutex_put(mdp->mdp_mutex[i]);
		if (mdp->mdp_mutex2[i])
			mtk_mutex_put(mdp->mdp_mutex2[i]);
	}
err_destroy_device:
	kfree(mdp);
err_return:
	dev_dbg(dev, "Errno %d\n", ret);
	return ret;
}

static int mdp_remove(struct platform_device *pdev)
{
	struct mdp_dev *mdp = platform_get_drvdata(pdev);

	if (mdp->comp[MDP_COMP_SPLIT])
		mdp_cap_deinit();

	v4l2_device_unregister(&mdp->v4l2_dev);

	dev_dbg(&pdev->dev, "%s driver unloaded\n", pdev->name);

	return 0;
}

static int __maybe_unused mdp_suspend(struct device *dev)
{
	struct mdp_dev *mdp = dev_get_drvdata(dev);
	int ret, i;

	atomic_set(&mdp->suspended, 1);

	for (i = 0; i < MDP_CMDQ_USER_MAX; i++) {
		if (atomic_read(&mdp->job_count[i])) {
			ret = wait_event_timeout(mdp->callback_wq,
						 !atomic_read(&mdp->job_count[i]),
						 2 * HZ);
			if (ret == 0) {
				dev_err(dev,
					"flushed cmdq task incomplete, user=%d, count=%d\n",
					i, atomic_read(&mdp->job_count[i]));
				return -EBUSY;
			}
		}
	}

	return 0;
}

static int __maybe_unused mdp_resume(struct device *dev)
{
	struct mdp_dev *mdp = dev_get_drvdata(dev);

	atomic_set(&mdp->suspended, 0);

	return 0;
}

static const struct dev_pm_ops mdp_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(mdp_suspend, mdp_resume)
};

static struct platform_driver mdp_driver = {
	.probe		= mdp_probe,
	.remove		= mdp_remove,
	.driver = {
		.name	= MDP_MODULE_NAME,
		.pm	= &mdp_pm_ops,
		.of_match_table = of_match_ptr(mdp_of_ids),
	},
};

module_platform_driver(mdp_driver);

MODULE_AUTHOR("Ping-Hsun Wu <ping-hsun.wu@mediatek.com>");
MODULE_DESCRIPTION("MediaTek image processor 3 driver");
MODULE_LICENSE("GPL");
