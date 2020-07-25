/* SPDX-License-Identifier: ((GPL-2.0 WITH Linux-syscall-note) OR BSD-2-Clause) */
/*
 * Copyright 2018-2020 Broadcom.
 */

#ifndef __UAPI_LINUX_MISC_BCM_VK_H
#define __UAPI_LINUX_MISC_BCM_VK_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define BCM_VK_MAX_FILENAME 64

struct vk_image {
	__u32 type; /* Type of image */
#define VK_IMAGE_TYPE_BOOT1 1 /* 1st stage (load to SRAM) */
#define VK_IMAGE_TYPE_BOOT2 2 /* 2nd stage (load to DDR) */
	char filename[BCM_VK_MAX_FILENAME]; /* Filename of image */
};

struct vk_reset {
	__u32 arg1;
	__u32 arg2;
};

#define VK_MAGIC		0x5e

/* Load image to Valkyrie */
#define VK_IOCTL_LOAD_IMAGE	_IOW(VK_MAGIC, 0x2, struct vk_image)

/* Send Reset to Valkyrie */
#define VK_IOCTL_RESET		_IOW(VK_MAGIC, 0x4, struct vk_reset)

/*
 * message block - basic unit in the message where a message's size is always
 *		   N x sizeof(basic_block)
 */
struct vk_msg_blk {
	__u8 function_id;
#define VK_FID_TRANS_BUF	5
#define VK_FID_SHUTDOWN		8
	__u8 size;
	__u16 trans_id; /* transport id, queue & msg_id */
	__u32 context_id;
	__u32 args[2];
#define VK_CMD_PLANES_MASK	0x000f /* number of planes to up/download */
#define VK_CMD_UPLOAD		0x0400 /* memory transfer to vk */
#define VK_CMD_DOWNLOAD		0x0500 /* memory transfer from vk */
#define VK_CMD_MASK		0x0f00 /* command mask */
};

#define VK_BAR_FWSTS			0x41c
#define VK_BAR_COP_FWSTS		0x428
/* VK_FWSTS definitions */
#define VK_FWSTS_RELOCATION_ENTRY	BIT(0)
#define VK_FWSTS_RELOCATION_EXIT	BIT(1)
#define VK_FWSTS_INIT_START		BIT(2)
#define VK_FWSTS_ARCH_INIT_DONE		BIT(3)
#define VK_FWSTS_PRE_KNL1_INIT_DONE	BIT(4)
#define VK_FWSTS_PRE_KNL2_INIT_DONE	BIT(5)
#define VK_FWSTS_POST_KNL_INIT_DONE	BIT(6)
#define VK_FWSTS_INIT_DONE		BIT(7)
#define VK_FWSTS_APP_INIT_START		BIT(8)
#define VK_FWSTS_APP_INIT_DONE		BIT(9)
#define VK_FWSTS_MASK			0xffffffff
#define VK_FWSTS_READY			(VK_FWSTS_INIT_START | \
					 VK_FWSTS_ARCH_INIT_DONE | \
					 VK_FWSTS_PRE_KNL1_INIT_DONE | \
					 VK_FWSTS_PRE_KNL2_INIT_DONE | \
					 VK_FWSTS_POST_KNL_INIT_DONE | \
					 VK_FWSTS_INIT_DONE | \
					 VK_FWSTS_APP_INIT_START | \
					 VK_FWSTS_APP_INIT_DONE)
/* Deinit */
#define VK_FWSTS_APP_DEINIT_START	BIT(23)
#define VK_FWSTS_APP_DEINIT_DONE	BIT(24)
#define VK_FWSTS_DRV_DEINIT_START	BIT(25)
#define VK_FWSTS_DRV_DEINIT_DONE	BIT(26)
#define VK_FWSTS_RESET_DONE		BIT(27)
#define VK_FWSTS_DEINIT_TRIGGERED	(VK_FWSTS_APP_DEINIT_START | \
					 VK_FWSTS_APP_DEINIT_DONE  | \
					 VK_FWSTS_DRV_DEINIT_START | \
					 VK_FWSTS_DRV_DEINIT_DONE)
/* Last nibble for reboot reason */
#define VK_FWSTS_RESET_REASON_SHIFT	28
#define VK_FWSTS_RESET_REASON_MASK	(0xf << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_SYS_PWRUP	(0x0 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_MBOX_DB		(0x1 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_M7_WDOG		(0x2 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_TEMP		(0x3 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_PCI_FLR		(0x4 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_PCI_HOT		(0x5 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_PCI_WARM		(0x6 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_PCI_COLD		(0x7 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_L1		(0x8 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_L0		(0x9 << VK_FWSTS_RESET_REASON_SHIFT)
#define VK_FWSTS_RESET_UNKNOWN		(0xf << VK_FWSTS_RESET_REASON_SHIFT)

#endif /* __UAPI_LINUX_MISC_BCM_VK_H */
