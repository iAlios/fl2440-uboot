/********************************************************/
/*														*/
/* 						Samsung S3C24x0					*/
/*														*/
/********************************************************/
#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

/* the gpio config */
#define GPIO_IN    				(0x0)
#define GPIO_OUT    			(0x1)
#define GPIO_EINT	    		(0x2)
#define GPIO_OTHER    			(0x3)

/* PENDING BIT */
#define BIT_EINT0		(0x1)
#define BIT_EINT1		(0x1<<1)
#define BIT_EINT2		(0x1<<2)
#define BIT_EINT3		(0x1<<3)
#define BIT_EINT4_7		(0x1<<4)
#define BIT_EINT8_23		(0x1<<5)
#define BIT_BAT_FLT		(0x1<<7)
#define BIT_TICK		(0x1<<8)
#define BIT_WDT			(0x1<<9)
#define BIT_TIMER0		(0x1<<10)
#define BIT_TIMER1		(0x1<<11)
#define BIT_TIMER2		(0x1<<12)
#define BIT_TIMER3		(0x1<<13)
#define BIT_TIMER4		(0x1<<14)
#define BIT_UART2		(0x1<<15)
#define BIT_LCD			(0x1<<16)
#define BIT_DMA0		(0x1<<17)
#define BIT_DMA1		(0x1<<18)
#define BIT_DMA2		(0x1<<19)
#define BIT_DMA3		(0x1<<20)
#define BIT_SDI			(0x1<<21)
#define BIT_SPI0		(0x1<<22)
#define BIT_UART1		(0x1<<23)
#define BIT_USBD		(0x1<<25)
#define BIT_USBH		(0x1<<26)
#define BIT_IIC			(0x1<<27)
#define BIT_UART0		(0x1<<28)
#define BIT_SPI1		(0x1<<29)
#define BIT_RTC			(0x1<<30)
#define BIT_ADC			(0x1<<31)
#define BIT_ALLMSK		(0xFFFFFFFF)

/* IRQ list */
#define IRQ_EINT0		(0)
#define IRQ_EINT1		(1)
#define IRQ_EINT2		(2)
#define IRQ_EINT3		(3)
#define IRQ_EINT4_7		(4)
#define IRQ_EINT8_23		(5)
#define IRQ_BAT_FLT		(7)
#define IRQ_TICK		(8)
#define IRQ_WDT			(9)
#define IRQ_TIMER0		(10)
#define IRQ_TIMER1		(11)
#define IRQ_TIMER2		(12)
#define IRQ_TIMER3		(13)
#define IRQ_TIMER4		(14)
#define IRQ_UART2		(15)
#define IRQ_LCD			(16)
#define IRQ_DMA0		(17)
#define IRQ_DMA1		(18)
#define IRQ_DMA2		(19)
#define IRQ_DMA3		(20)
#define IRQ_SDI			(21)
#define IRQ_SPI0		(22)
#define IRQ_UART1		(23)
#define IRQ_USBD		(25)
#define IRQ_USBH		(26)
#define IRQ_IIC			(27)
#define IRQ_UART0		(28)
#define IRQ_SPI1		(29)
#define IRQ_RTC			(30)
#define IRQ_ADC			(31)

#define N_IRQS         (32)

/* the condition of triggering the irq */
#define IRQ_LOW_TRG    				(0x0)
#define IRQ_HIGH_TRG    			(0x1)
#define IRQ_DOWN_EDGE_TRG    		(0x2)
#define IRQ_UP_EDGE_TRG    			(0x4)
#define IRQ_BOTH_EDGE_TRG    		(0x8)

/* MISCCR */
#define S3C24X0_MISCCR_USBDEV	    (0<<3)
#define S3C24X0_MISCCR_USBHOST	    (1<<3)

#define S3C24X0_MISCCR_CLK0_MPLL    (0<<4)
#define S3C24X0_MISCCR_CLK0_UPLL    (1<<4)
#define S3C24X0_MISCCR_CLK0_FCLK    (2<<4)
#define S3C24X0_MISCCR_CLK0_HCLK    (3<<4)
#define S3C24X0_MISCCR_CLK0_PCLK    (4<<4)
#define S3C24X0_MISCCR_CLK0_DCLK0   (5<<4)
#define S3C24X0_MISCCR_CLK0_MASK    (7<<4)

#define S3C24X0_MISCCR_CLK1_MPLL    (0<<8)
#define S3C24X0_MISCCR_CLK1_UPLL    (1<<8)
#define S3C24X0_MISCCR_CLK1_FCLK    (2<<8)
#define S3C24X0_MISCCR_CLK1_HCLK    (3<<8)
#define S3C24X0_MISCCR_CLK1_PCLK    (4<<8)
#define S3C24X0_MISCCR_CLK1_DCLK1   (5<<8)
#define S3C24X0_MISCCR_CLK1_MASK    (7<<8)

#define S3C24X0_MISCCR_USBSUSPND0   (1<<12)
#define S3C24X0_MISCCR_USBSUSPND1   (1<<13)

#define S3C24X0_MISCCR_nRSTCON	    (1<<16)

#define S3C24X0_MISCCR_nEN_SCLK0    (1<<17)
#define S3C24X0_MISCCR_nEN_SCLK1    (1<<18)
#define S3C24X0_MISCCR_nEN_SCLKE    (1<<19)
#define S3C24X0_MISCCR_SDSLEEP	    (7<<17)

#define S3C24X0_CLKSLOW_UCLK_OFF	(1<<7)
#define S3C24X0_CLKSLOW_MPLL_OFF	(1<<5)
#define S3C24X0_CLKSLOW_SLOW		(1<<4)
#define S3C24X0_CLKSLOW_SLOWVAL(x)	(x)
#define S3C24X0_CLKSLOW_GET_SLOWVAL(x)	((x) & 7)

struct _irq_handler {
	void                *m_data;
	void (*m_func)( void *data);
};

#endif /* __ASM_ARCH_HARDWARE_H */
