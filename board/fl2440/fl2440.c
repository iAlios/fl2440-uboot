/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
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

#include <common.h>
#include <netdev.h>
#include <asm/arch/s3c24x0_cpu.h>
#include <video_fb.h>
DECLARE_GLOBAL_DATA_PTR;

#define FCLK_SPEED 1

#if FCLK_SPEED==0		/* Fout = 203MHz, Fin = 12MHz for Audio */
#define M_MDIV	0xC3
#define M_PDIV	0x4
#define M_SDIV	0x1
#elif FCLK_SPEED==1		

#if defined(CONFIG_S3C2410)     /* Fout = 202.8MHz */
#define M_MDIV	0xA1
#define M_PDIV	0x3
#define M_SDIV	0x1
#endif

#if defined(CONFIG_S3C2440)     /* Fout = 405MHZ */
#define M_MDIV 0x7f
#define M_PDIV 0x2
#define M_SDIV 0x1
#endif
#endif

#define USB_CLOCK 1

#if USB_CLOCK==0
#define U_M_MDIV	0xA1
#define U_M_PDIV	0x3
#define U_M_SDIV	0x1
#elif USB_CLOCK==1

#if defined(CONFIG_S3C2410)
#define U_M_MDIV	0x48
#define U_M_PDIV	0x3
#define U_M_SDIV	0x2
#endif

#if defined(CONFIG_S3C2440)/*见S3C2440数据手册P227*/
#define U_M_MDIV	0x38
#define U_M_PDIV	0x2
#define U_M_SDIV	0x2
#endif
#endif

static inline void delay(unsigned long loops) {
	__asm__ volatile ("1:\n"
			"subs %0, %1, #1\n"
			"bne 1b":"=r" (loops):"0" (loops));
}

/*
 * Miscellaneous platform dependent initialisations
 */

int board_init(void) {
	struct s3c24x0_clock_power * const clk_power =
			s3c24x0_get_base_clock_power();
	struct s3c24x0_gpio * const gpio = s3c24x0_get_base_gpio();

	/* to reduce PLL lock time, adjust the LOCKTIME register */
	clk_power->LOCKTIME = 0xFFFFFF;

	/* configure MPLL */
	clk_power->MPLLCON = ((M_MDIV << 12) + (M_PDIV << 4) + M_SDIV);

	/* some delay between MPLL and UPLL */
	delay(4000);
	delay(4000); //add for sometime the usb -62 error

	/* configure UPLL */
	clk_power->UPLLCON = ((U_M_MDIV << 12) + (U_M_PDIV << 4) + U_M_SDIV);

	/* some delay between MPLL and UPLL */
	delay(8000);

	/* set up the I/O ports */
	gpio->GPACON = 0x007FFFFF;

#if defined(CONFIG_S3C2440)
	gpio->GPBCON = 0x001dd7fc; //初始化相应的GPB 口为输出口,为显示LED作准备,之前忘了改导致灯不亮
	// gpio->GPBCON = 0x00044555;
#else
	gpio->GPBCON = 0x00044555;
#endif

	gpio->GPBUP = 0x000007FF;
	//gpio->GPCCON = 0xAAAAAAAA;
	//gpio->GPCUP = 0x0000FFFF;
	gpio->GPCUP = 0xFFFFFFFF; /*这个up和con放反了还有问题？字符显示出错，真奇怪*/
	gpio->GPCCON = 0xAAAA56A9;

	// gpio->GPCUP = 0xFFFFFFFF;
	gpio->GPDUP = 0xFFFFFFFF;
	gpio->GPDCON = 0xAAAAAAAA;
	//gpio->GPDUP = 0x0000FFFF;

	gpio->GPECON = 0xAAAAAAAA;
	gpio->GPEUP = 0x0000FFFF;
	gpio->GPFCON = 0x000055AA;
	gpio->GPFUP = 0x000000FF;
	gpio->GPGCON = 0xFF95FFBA;
	gpio->GPGUP = 0x0000FFFF;
	gpio->GPHCON = 0x002AFAAA;
	gpio->GPHUP = 0x000007FF;

#if defined(CONFIG_S3C2410)
	/* arch number of SMDK2410-Board */
	gd->bd->bi_arch_number = MACH_TYPE_SMDK2410;
#endif

#if defined(CONFIG_S3C2440)
	/* arch number of fl2440-Board */
	gd->bd->bi_arch_number = MACH_TYPE_S3C2440;
#endif

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x30000100;

	icache_enable();
	dcache_enable();
#if defined(CONFIG_FL2440_LED)
	//gpio->GPBCON = 0x001dd7fc;//初始化相应的GPB 口为输出口,为显示LED作准备,之前忘了改导致灯不亮
	gpio->GPBDAT = ((1<<5) | (1<<6) | (1<<8) | (1<<10));//使LED全部熄灭
	gpio->GPBDAT &= 0xffe;// /*添加关闭蜂鸣器语句*/
	gpio->GPBDAT = ~(3<<5);
#endif
	return 0;
}

int dram_init(void) {
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

	return 0;
}

#if defined(CONFIG_VIDEO_S3C2440)
#define MVAL                   (13)
#define MVAL_USED              (0)
#define INVVDEN                (1)
#define BSWP                   (0)
//#define HWSWP                  (1)//为一时会造成字符显示的错误，显示很模糊
#define HWSWP                  (1)
//TFT 240320
#define LCD_XSIZE_TFT_240320   (320)
#define LCD_YSIZE_TFT_240320   (240)
//TFT 240320
#define HOZVAL_TFT_240320      (LCD_XSIZE_TFT_240320-1)
#define LINEVAL_TFT_240320     (LCD_YSIZE_TFT_240320-1)
//Timing parameter for WXCAT35-TG#001
#if 1
#define VBPD_240320            (3)
#define VFPD_240320            (5)
#define VSPW_240320            (15)
#define HBPD_240320            (58)
#define HFPD_240320            (15)
#define HSPW_240320_WXCAT35    (8)//adjust the horizontal displacement of the screen
#endif
#if 0
#define VBPD_240320            (14)
#define VFPD_240320            (11)
#define VSPW_240320            (2)
#define HBPD_240320            (37)
#define HFPD_240320            (19)
#define HSPW_240320_WXCAT35    (29)
#endif
#define CLKVAL_TFT_240320      (7)
//FCLK = 405MHZ, HCLK = 101.25MHZ, VCLK=4602272HZ
void board_video_init(GraphicDevice *pGD)
{
	struct s3c24x0_lcd * const lcd = s3c24x0_get_base_lcd();
	/*Configuration for fl2440*/
	// lcd->LCDCON1 = 0x00000778;
	lcd->LCDCON1 = (CLKVAL_TFT_240320 <<8)|(MVAL_USED <<7)|(3<<5)|(12<<1)|0;
	lcd->LCDCON2 = (VBPD_240320<<24)|(LINEVAL_TFT_240320<<14)|(VFPD_240320<<6)|(VSPW_240320);
	lcd->LCDCON3 = (HBPD_240320<<19)|(HOZVAL_TFT_240320<<8)|(HFPD_240320);
	lcd->LCDCON4 = (MVAL<<8)|(HSPW_240320_WXCAT35);
	// lcd->LCDCON5 = 0x00000f09;
	lcd->LCDCON5 = (1<<11)|(1<<9)|(1<<8)|(1<<3)|(BSWP<<1)|(HWSWP);
	// lcd->LCDCON5 = (1<<11)|(0<<9)|(0<<8)|(0<<6)|(1<<3)|(BSWP<<1)|(HWSWP);
	lcd->LPCSEL = 0x00000000;
}
#endif /*CONFIG_VIDEO_S3C2440*/

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_CS8900
	rc = cs8900_initialize(0, CONFIG_CS8900_BASE);
#endif

#ifdef CONFIG_DRIVER_DM9000
	rc = dm9000_initialize(bis);
#endif
	return rc;
}
#endif
