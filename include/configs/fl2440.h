/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <garyj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK2410 board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARM920T	1	/* This is an ARM920T Core	*/
#define CONFIG_S3C24X0	1	/* in a SAMSUNG S3C24x0-type SoC	*/
#define CONFIG_S3C2440	1	/* specifically a SAMSUNG S3C2410 SoC	*/
#define CONFIG_FL2440	1	/* on a fl2440 Board  */

#define CONFIG_FL2440_LED 1

#define DEBUG            1
/*use to run the uboot in sdram*/
//#define CONFIG_SKIP_LOWLEVEL_INIT   1
//#define CONFIG_SKIP_RELOCATE_UBOOT  1

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ	12000000/* the SMDK2410 has 12MHz input clock */


#define USE_920T_MMU		1
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128*1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

/*
 * Hardware drivers
 */
#if 0
#define CONFIG_NET_MULTI
#define CONFIG_CS8900		/* we have a CS8900 on-board */
#define CONFIG_CS8900_BASE	0x19000300
#define CONFIG_CS8900_BUS16	/* the Linux driver does accesses as shorts */
#endif

#define CONFIG_DRIVER_DM9000             1
#define CONFIG_DM9000_USE_16BIT          1
#define CONFIG_DM9000_BASE               0x20000300
#define DM9000_IO                        CONFIG_DM9000_BASE 
#define DM9000_DATA                      (CONFIG_DM9000_BASE + 4)
#define CONFIG_DM9000_NO_SROM            1 //防止dm9000去从srom中读取物理地址信息
#define CONFIG_NET_MULTI                 1

/*
 * select serial console configuration
 */
#define CONFIG_S3C24X0_SERIAL
#define CONFIG_SERIAL1          1	/* we use SERIAL 1 on SMDK2410 */

/************************************************************
 * RTC
 ************************************************************/
#define	CONFIG_RTC_S3C24X0	1

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_BAUDRATE		115200


/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME


/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_PING
#define CONFIG_CMD_NAND
#define CONFIG_CMD_NET
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_USB
#define CONFIG_CMD_FAT

//#define CONFIG_MTD_DEVICE /*bug when I add the command, I found the bootloader has the problem that the nand command can't run success, I check the code but I can't found where the problem is*/

#if defined(CONFIG_CMD_NAND)

#define CONFIG_NAND_S3C2410
#define CONFIG_SYS_MAX_NAND_DEVICE   1     /* Max number of NAND devices        */
#define NAND_MAX_CHIPS			1
#define CONFIG_SYS_NAND_BASE 0x4E000000
#if 0
#define CONFIG_NAND_S3C2410
#define CONFIG_SYS_NAND_BASE 0x4E000000 
#define CONFIG_SYS_MAX_NAND_DEVICE	1	/* Max number of NAND devices		*/
#define SECTORSIZE 512
#define SECTORSIZE_2K 2048
#define NAND_SECTOR_SIZE SECTORSIZE
#define NAND_SECTOR_SIZE_2K SECTORSIZE_2K
#define NAND_BLOCK_MASK 511
#define NAND_BLOCK_MASK_2K 2047
#define NAND_MAX_CHIPS 1
#define CONFIG_MTD_NAND_VERIFY_WRITE 
#define CONFIG_SYS_64BIT_VSPRINTF       /* needed for nand_util.c */
#endif
#endif


/*#define CONFIG_BOOTARGS	"root=ramfs devfs=mount console=ttySA0,9600" */
#define CONFIG_ETHADDR	08:00:3e:26:0a:5b 
#define CONFIG_NETMASK          255.255.255.0
#define CONFIG_IPADDR		192.168.1.4
#define CONFIG_SERVERIP		192.168.1.1
/*#define CONFIG_BOOTFILE	"elinos-lart" */
/*#define CONFIG_BOOTCOMMAND	"tftp; bootm" */

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200		/* speed to run kgdb serial port */
/* what's this ? it's not used anywhere */
#define CONFIG_KGDB_SER_INDEX	1		/* which serial port to use */
#endif

/*
 * Miscellaneous configurable options
 */
#define	CONFIG_SYS_LONGHELP				/* undef to save memory		*/
#define	CONFIG_SYS_PROMPT		"fl2440 > "	/* Monitor Command Prompt	*/
#define	CONFIG_SYS_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define	CONFIG_SYS_MAXARGS		16		/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x30000000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x33F00000	/* 63 MB in DRAM	*/


#define	CONFIG_SYS_LOAD_ADDR		0x30008000	/* default load address	*/
#define	CONFIG_SYS_HZ			1000

/* valid baudrates */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128*1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #1 */

#define CONFIG_SYS_FLASH_BASE		PHYS_FLASH_1

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */


#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#ifdef CONFIG_FL2440
#define PHYS_FLASH_SIZE		0x00400000 /* 4MB */
#define CONFIG_SYS_MAX_FLASH_SECT	(32)	/* max number of sectors on one chip */
#define CONFIG_ENV_ADDR		(CONFIG_SYS_FLASH_BASE + 0x0F0000) /* addr of environment */
#define CONFIG_SYS_MONITOR_BASE  TEXT_BASE  /*CMI/flash.c need*/
#define FLASH_BASE0_PRELIM      PHYS_FLASH_1      /*CMI/flash.c need*/
#endif

/* timeout values are in ticks */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(5*CONFIG_SYS_HZ) /* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(5*CONFIG_SYS_HZ) /* Timeout for Flash Write */

//#define	CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_SIZE		0x20000	/* Total Size of Environment Sector */
#define	CONFIG_ENV_IS_IN_NAND	1
#define CONFIG_ENV_OFFSET   0x80000

/*JFFS2 support*/
/*#undef CONFIG_JFFS2_CMDLINE*/
#if 1
#define CONFIG_JFFS2_CMDLINE       1    /*when you not use nand legancy*/
#define CONFIG_JFFS2_NAND          1
#define CONFIG_JFFS2_DEV           "nand0"
#define CONFIG_JFFS2_PART_SIZE     0x4c0000
#define CONFIG_JFFS2_PART_OFFSET   0x40000
/*JFFS2 support*/
#endif
/*USB support*/
#define CONFIG_USB_OHCI
#define CONFIG_USB_STORAGE
#define CONFIG_USB_KEYBOARD
#define CONFIG_DOS_PARTITION
#define CFG_DEVICE_DEREGISTER
#define CONFIG_SUPPORT_VFAT
#define LITTLEEDIAN
/*USB support*/

#if 1
/*LCD support*/
#define CONFIG_VIDEO_S3C2440     1
#define CONFIG_VIDEO_LOGO        1
#define CONFIG_VIDEO_BMP_LOGO           1
//#define VIDEO_FB_16BPP_PIXEL_SWAP       1 /*注意在后面版本中它已经改名，如果不添加会使图像显示模糊*/
#define VIDEO_FB_16BPP_WORD_SWAP       1
#define CONFIG_CMD_BMP                  1
//#define CONFIG_LCD               1
#define CONFIG_VIDEO               1
#define CONFIG_CFB_CONSOLE       1
//#define CONFIG_VGA_AS_SINGLE_DEVICE 1          //see Cfb_console.c/drv_video_init
#define CFG_CONSOLE_INFO_QUIET        //support display of console information at boot

#define LCD_VIDEO_ADDR          0x33b00000

/*for PC-keyboard*/
#define VIDEO_KBD_INIT_FCT      0

#define VIDEO_TSTC_FCT          serial_tstc
#define VIDEO_GETC_FCT          serial_getc

#define CONFIG_SERIAL_MULTI     1
/*LCD support*/
#endif

#define CONFIG_CMDLINE_EDITING   1
#define CONFIG_AUTO_COMPLETE     1 //自动补全命令等

/* boot cmdline*/
#define CONFIG_SETUP_MEMORY_TAGS    1      /* 向内核传递内存分布信息 */
#define CONFIG_CMDLINE_TAG          1      /* 向内核传递命令行参数 */

#define CONFIG_BOOTDELAY	5
#ifdef BOOT_NFS
#define CONFIG_BOOTARGS     "console=ttySAC0,115200 noinitrd root=/dev/nfs rw nfsroot=192.168.1.2:/home/ilufei/nfs/rootfs ip=192.168.1.4:192.168.1.2:192.168.1.1:255.255.255.0:tocore:eth0:on"
#define CONFIG_BOOTCOMMAND	"nfs 0x30008000 192.168.1.2:/home/ilufei/nfs/zImage; bootm 0x30008000"
#else
#define CONFIG_BOOTARGS     "console=tty0 console=ttySAC0,115200 noinitrd root=/dev/mtdblock2 rootfstype=yaffs2"
#define CONFIG_BOOTCOMMAND	"nand read 0x30008000 0x600000 0x210000; bootm 0x30008000"
#endif

#if DEBUG
#define DEBUG            1
#define CONFIG_MTD_DEBUG  1
#define CONFIG_MTD_DEBUG_VERBOSE  0
#define DEBUG_CFB_CONSOLE   1
#endif

#define CMD_NAND_YAFFS
#define CMD_NAND_YAFFS_SKIPFB

#endif	/* __CONFIG_H */
