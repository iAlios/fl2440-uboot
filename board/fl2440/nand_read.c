/* 
 * vivi/s3c2410/nand_read.c: Simple NAND read functions for booting from NAND
 *
 * Copyright (C) 2002 MIZI Research, Inc.
 *
 * Author: Hwang, Chideok <hwang@mizi.com>
 * Date  : $Date: 2002/08/14 10:26:47 $
 *
 * $Revision: 1.6 $
 * $Id: param.c,v 1.9 2002/07/11 06:17:20 nandy Exp 
 *
 * History
 *
 * 2002-05-xx: Hwang, Chideok <hwang@mizi.com>
 *    - µÉ°Å¶ó°í ³­µð¿¡°Ô ÁÜ.
 *
 * 2002-05-xx: Chan Gyun Jeong <cgjeong@mizi.com>
 *    - ³­µðÀÇ ºÎÅ¹À» ¹Þ°í ÁŠŽë·Î µ¿ÀÛÇÏµµ·Ï ŒöÁ€.
 *
 * 2002-08-10: Yong-iL Joh <tolkien@mizi.com>
 *    - SECTOR_SIZE°¡ 512ÀÎ ³ðÀº ŽÙ ÀÐµµ·Ï ŒöÁ€
 *
 */

#include <config.h>

#define __REGb(x)	(*(volatile unsigned char *)(x))
#define __REGi(x)	(*(volatile unsigned int *)(x))
#define NF_BASE		0x4e000000

#ifdef CONFIG_S3C2440
/*S3C2440与S3C2440 nandflash控制寄存器地址不同需要进行修改*/
#define NFCONF		__REGi(NF_BASE + 0x0)
#define NFCONT          __REGi(NF_BASE + 0x4)
#define NFCMD		__REGb(NF_BASE + 0x8)
#define NFADDR		__REGb(NF_BASE + 0xc)
#define NFDATA		__REGb(NF_BASE + 0x10)
#define NFSTAT		__REGb(NF_BASE + 0x20)

#define NAND_CHIP_ENABLE (NFCONT &= ~(1<<1))
#define NAND_CHIP_DISABLE (NFCONT |= (1<<1))
#define NAND_CLEAR_RB (NFSTAT |= (1<<2))
#define NAND_DETECT_RB {while(! (NFSTAT&(1<<2)));}
#define NAND_ECC_CLEAR (NFCONT |= 0x10)
/*see data sheet P193*/

#define BUSY 1
static inline void wait_idle(void) {
	int i;
	while(!(NFSTAT & BUSY))
	for(i=0; i<10; i++);
}

/*根据fl2440的nand flash 作相应修改*/
#define NAND_SECTOR_SIZE	2048
#define NAND_BLOCK_MASK		(NAND_SECTOR_SIZE - 1)

/* low level nand read function */
int
nand_read_ll(unsigned char *buf, unsigned long start_addr, int size)
{
	int i, j;
	int pagenum;

	if ((start_addr & NAND_BLOCK_MASK) || (size & NAND_BLOCK_MASK)) {
		return -1; /* invalid alignment */
	}

	/* chip Enable */
	NAND_CHIP_ENABLE;

	for(i = start_addr; i < (start_addr + size);) {
		/* READ0 */

		NAND_CLEAR_RB;
		for(j = 0; j < 10; j++);

		pagenum = i >> 11;
		/* Write Address
		 该步骤详见nand flash(k9f2g08u0a)手册p17
		 参考fl2440开发板nand_lowlevel.c文件中ReadPage函数
		 */
		NFCMD = 0x0;

		NFADDR = 0;
		NFADDR = 0;
		NFADDR = pagenum & 0xff;
		NFADDR = (pagenum >> 8) & 0xff;
		NFADDR = (pagenum >> 16) & 0xff;
		/* NFADDR = i & 0xff;
		 NFADDR = (i >> 8) & 0xf;
		 NFADDR = (i >> 12) & 0xff;
		 NFADDR = (i >> 20) & 0xff;
		 NFADDR = (i >> 28) & 0x1;*/
		/*如果不理解见数据手册nand flashP9*/

		NFCMD = 0x30;
		wait_idle();

		for(j=0; j < NAND_SECTOR_SIZE; j++) {
			*buf = (NFDATA & 0xff);
			buf++;
		}

		i += NAND_SECTOR_SIZE;

	}

	NAND_CHIP_DISABLE;

	/* chip Disable */

	return 0;
}

#endif

#ifdef CONFIG_S3C2410
#define NFCONF		__REGi(NF_BASE + 0x0)
#define NFCMD		__REGb(NF_BASE + 0x4)
#define NFADDR		__REGb(NF_BASE + 0x8)
#define NFDATA		__REGb(NF_BASE + 0xc)
#define NFSTAT		__REGb(NF_BASE + 0x10)

#define BUSY 1
inline void wait_idle(void) {
	int i;

	while(!(NFSTAT & BUSY))
	for(i=0; i<10; i++);
}

#define NAND_SECTOR_SIZE	512
#define NAND_BLOCK_MASK		(NAND_SECTOR_SIZE - 1)

/* low level nand read function */
int
nand_read_ll(unsigned char *buf, unsigned long start_addr, int size)
{
	int i, j;

	if ((start_addr & NAND_BLOCK_MASK) || (size & NAND_BLOCK_MASK)) {
		return -1; /* invalid alignment */
	}

	/* chip Enable */
	NFCONF &= ~0x800;
	for(i=0; i<10; i++);

	for(i=start_addr; i < (start_addr + size);) {
		/* READ0 */
		NFCMD = 0;

		/* Write Address */
		NFADDR = i & 0xff;
		NFADDR = (i >> 9) & 0xff;
		NFADDR = (i >> 17) & 0xff;
		NFADDR = (i >> 25) & 0xff;

		wait_idle();

		for(j=0; j < NAND_SECTOR_SIZE; j++, i++) {
			*buf = (NFDATA & 0xff);
			buf++;
		}
	}

	/* chip Disable */
	NFCONF |= 0x800; /* chip disable */

	return 0;
}
#endif
