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

#define CONFIG_FL2440_LCD	1

#define CONFIG_FL2440_LED 1

/* input clock of PLL */
#define CONFIG_SYS_CLK_FREQ	12000000/* the SMDK2410 has 12MHz input clock */


#define USE_920T_MMU		1
#undef CONFIG_USE_IRQ			/* we don't need IRQ/FIQ stuff */
#define CONFIG_USE_IRQ

//#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SKIP_RELOCATE_UBOOT
#define FL2440_NAND_BOOT

/*
 * Hardware drivers
 */
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
#define CONFIG_SUPPORT_YAFFS
/*YAFFS support*/
#ifdef CONFIG_SUPPORT_YAFFS
#define CONFIG_CMD_NAND_YAFFS				1
#define CONFIG_CMD_NAND_YAFFS_SKIPFB		1
#endif
/*YAFFS support*/
// #define CONFIG_CMD_FASTBOOT

#if defined(CONFIG_FL2440)
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE 
#define CONFIG_MTD_PARTITIONS
#endif

#ifdef BOOT_NFS
#define CONFIG_BOOTARGS     "console=ttySAC0,115200 noinitrd root=/dev/nfs rw nfsroot=192.168.1.2:/home/ilufei/nfs/rootfs ip=192.168.1.4:192.168.1.2:192.168.1.1:255.255.255.0:fl2440:eth0:on"
#define CONFIG_BOOTCOMMAND	"nfs 0x30008000 192.168.1.2:/home/ilufei/nfs/zImage; bootm 0x30008000"
#else
#define CONFIG_BOOTARGS     "console=tty0 console=ttySAC0,115200 noinitrd root=/dev/mtdblock2 rootfstype=yaffs2"
#define CONFIG_BOOTCOMMAND	"echo hello!!!!; run mtddaf"
#endif

#define CONFIG_ETHADDR		08:00:3e:26:0a:5b 
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.1.234
#define CONFIG_SERVERIP		192.168.1.101

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200		/* speed to run kgdb serial port */
/* what's this ? it's not used anywhere */
#define CONFIG_KGDB_SER_INDEX	1		/* which serial port to use */
#endif

#undef MTDIDS_DEFAULT
#undef MTDPARTS_DEFAULT
#define MTDIDS_DEFAULT          "nand0=nandflash"
#define MTDPARTS_DEFAULT        "mtdparts=nandflash:1m(uboot),"					\
                                "5m(kernel),"                                   \
                                "-(rootfs)"                      
                                
	
#define	CONFIG_EXTRA_ENV_SETTINGS					\
		"netdev=eth0\0" 						\
		"usbtty=cdc_acm\0" 						\
		"serial#=fl-201508\0" 						\
		"mtddaf=mtdparts default\0" 						\
		// "bootargs=console=ttyS0,38400 root=/dev/nfs rw nfsroot=192.168.0.20:/export/rootfs ip=192.168.0.207:192.168.0.20:192.168.0.1:255.255.255.0:fl2440:eth0\0" \
		""

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
/**
 * CONFIG_SYS_CONSOLE_IS_IN_ENV is important to serial console!
 * Define this if you want stdin, stdout and/or stderr to be set to usbtty.
 */
#define CONFIG_SYS_CONSOLE_IS_IN_ENV

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


#define CONFIG_NAND_S3C2440

/* NAND configuration */
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x4E000000

#define CONFIG_ENV_IS_IN_NAND
//#define CONFIG_NAND_ENV_DST		0x31000000
#define CONFIG_ENV_OFFSET		0x40000
#define CONFIG_ENV_SIZE		0x10000	/* Total Size of Environment Sector */
//#define CONFIG_S3C2440_NAND_HWECC

//#define CONFIG_SYS_NAND_SKIP_BAD_DOT_I	1  /* ".i" read skips bad blocks	      */

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128 * 1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128	/* size in bytes reserved for initial data */

/* NAND chip page size		*/
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
/* NAND chip block size		*/
#define CONFIG_SYS_NAND_BLOCK_SIZE	(128 * 1024)
/* NAND chip page per block count  */
#define CONFIG_SYS_NAND_PAGE_COUNT	64
/* Location of the bad-block label */
#define CONFIG_SYS_NAND_BAD_BLOCK_POS	0
/* Extra address cycle for > 128MiB */
#define CONFIG_SYS_NAND_5_ADDR_CYCLE

/* Size of the block protected by one OOB (Spare Area in Samsung terminology) */
#define CONFIG_SYS_NAND_ECCSIZE	CONFIG_SYS_NAND_PAGE_SIZE
/* Number of ECC bytes per OOB - S3C6400 calculates 4 bytes ECC in 1-bit mode */
#define CONFIG_SYS_NAND_ECCBYTES	4
/* Number of ECC-blocks per NAND page */
#define CONFIG_SYS_NAND_ECCSTEPS	(CONFIG_SYS_NAND_PAGE_SIZE / CONFIG_SYS_NAND_ECCSIZE)
/* Size of a single OOB region */
#define CONFIG_SYS_NAND_OOBSIZE	64
/* Number of ECC bytes per page */
#define CONFIG_SYS_NAND_ECCTOTAL	(CONFIG_SYS_NAND_ECCBYTES * CONFIG_SYS_NAND_ECCSTEPS)
/* ECC byte positions */
#define CONFIG_SYS_NAND_ECCPOS		{40, 41, 42, 43, 44, 45, 46, 47, \
				 48, 49, 50, 51, 52, 53, 54, 55, \
				 56, 57, 58, 59, 60, 61, 62, 63}
/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1	   /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

/*JFFS2 support*/
#define CONFIG_JFFS2_CMDLINE       1    /*when you not use nand legancy*/
#define CONFIG_JFFS2_NAND          1
#define CONFIG_JFFS2_DEV           "nand0"
#define CONFIG_JFFS2_PART_SIZE     0x0fa00000
#define CONFIG_JFFS2_PART_OFFSET   0x00600000
/*JFFS2 support*/

/*USB Device*/
#define CONFIG_USB_DEVICE
// #define CONFIG_USB_DEVICE_WITH_DMA
#define CONFIG_USB_TTY
/*USB Device*/

/*USB support*/
#define CONFIG_USB_OHCI
#define CONFIG_USB_STORAGE
#define CONFIG_USB_KEYBOARD
#define CONFIG_DOS_PARTITION
#define CFG_DEVICE_DEREGISTER
#define CONFIG_SUPPORT_VFAT
#define LITTLEEDIAN
/*USB support*/

#ifdef CONFIG_FL2440_LCD
/*LCD support*/
#define CONFIG_VIDEO_S3C2440     1
#define CONFIG_VIDEO_LOGO        1
#define CONFIG_VIDEO_BMP_LOGO           1
#define VIDEO_FB_16BPP_WORD_SWAP       1
#define CONFIG_CMD_BMP                  1
//#define CONFIG_SPLASH_SCREEN
//#define CONFIG_LCD               1
#define CONFIG_VIDEO               1
#define CONFIG_CFB_CONSOLE       1
#define CFG_CONSOLE_INFO_QUIET        //support display of console information at boot
#define CONFIG_CMD_RUN

#define LCD_VIDEO_ADDR          0x33b00000

/*for PC-keyboard*/
#define VIDEO_KBD_INIT_FCT      0

#define VIDEO_TSTC_FCT          serial_tstc
#define VIDEO_GETC_FCT          serial_getc

#define CONFIG_SERIAL_MULTI     1
/*LCD support*/
#endif

#define CONFIG_CMDLINE_EDITING   1
#define CONFIG_AUTO_COMPLETE     1 

/* boot cmdline*/
#define CONFIG_SETUP_MEMORY_TAGS    1     
#define CONFIG_CMDLINE_TAG          1      

#define CONFIG_BOOTDELAY	5
#ifdef CONFIG_DEBUG_ENABLE

#ifdef CONFIG_MTD_DEBUG_ENABLE
#define CONFIG_MTD_DEBUG  1
#define CONFIG_MTD_DEBUG_VERBOSE  0
#endif

#ifdef CONFIG_NAND_DEBUG_ENABLE
#define CONFIG_NAND_DEBUG
#define CONFIG_NAND_DEBUG_LEVEL		1
#endif
// #define DEBUG_CFB_CONSOLE   1
#endif

#define CONFIG_SYS_NO_FLASH
#undef CONFIG_CMD_FLASH
#undef CONFIG_CMD_IMLS

#endif	/* __CONFIG_H */
