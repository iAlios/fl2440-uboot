/****************************************************************
 NAME: usbout.c
 DESC: USB bulk-OUT operation related functions
 HISTORY:
 Mar.25.2002:purnnamu: ported for S3C2410X.
 Mar.27.2002:purnnamu: DMA is enabled.
 ****************************************************************/
#include <common.h>
#include <asm/arch/s3c24x0_cpu.h>
#include <asm/io.h>

#include "def.h"

#include "2440usb.h"
#include "usbmain.h"
#include "usb.h"
#include "usblib.h"
#include "usbsetup.h"
#include "usbout.h"

#include "usbinit.h"

#define BIT_USBD		(0x1<<25)
#define BIT_DMA2		(0x1<<19)

extern volatile U32 dw_usb_buf_read_ptr;
extern volatile U32 dw_usb_buf_write_ptr;
extern volatile U32 dw_will_dma_cnt;
extern volatile U32 b_dma_pending;
extern volatile U32 dw_usb_buf_base;
extern volatile U32 dw_usb_buf_size;
extern void
clear_pending(int bit);
//static void PrintEpoPkt(U8 *pt,int cnt);
static void
rdpkt_ep3_check_sum(U8 *buf, int num);

// ===================================================================
// All following commands will operate in case 
// - out_csr3 is valid.
// ===================================================================

#define CLR_EP3_OUT_PKT_READY() writeb(((out_csr3 & (~ EPO_WR_BITS)) & (~EPO_OUT_PKT_READY)) , &usb_dev_regs->OUT_CSR1_REG)
//#define SET_EP3_SEND_STALL()	usbdevregs->OUT_CSR1_REG= ((out_csr3 & (~EPO_WR_BITS)) | EPO_SEND_STALL) 
#define CLR_EP3_SENT_STALL()	writeb(((out_csr3 & (~EPO_WR_BITS)) &(~EPO_SENT_STALL)), &usb_dev_regs->OUT_CSR1_REG)
//#define FLUSH_EP3_FIFO() 	usbdevregs->OUT_CSR1_REG= ((out_csr3 & (~EPO_WR_BITS)) |EPO_FIFO_FLUSH) 

// ***************************
// *** VERY IMPORTANT NOTE ***
// ***************************
// Prepare for the packit size constraint!!!

// EP3 = OUT end point. 

U8 ep3_buf[EP3_PKT_SIZE];

void ep3_handler(void) {
	struct s3c24x0_interrupt * int_regs = s3c24x0_get_base_interrupt();
	struct s3c24x0_usb_device * const usb_dev_regs =
			s3c24x0_get_base_usb_device();
	U8 out_csr3;
	int fifoCnt;
	writeb(3, &usb_dev_regs->INDEX_REG);
	out_csr3 = readb(&usb_dev_regs->OUT_CSR1_REG);

//    DbgPrintf("<3:%x]",out_csr3);

	if (out_csr3 & EPO_OUT_PKT_READY) {
//	fifoCnt=usbdevregs->OUT_FIFO_CNT1_REG; 
		fifoCnt = readb(&usb_dev_regs->OUT_FIFO_CNT1_REG);
#if 0
		rd_pkt_ep3(ep3_buf,fifoCnt);
		PrintEpoPkt(ep3_buf,fifoCnt);
#else

		if (download_file_size == 0) {
			rd_pkt_ep3((U8 *) down_ptr, 8);

			if (download_run == 0) {
				downloadAddress = temp_download_address;
			} else {
				downloadAddress = *((U8 *) (down_ptr + 0))
						+ (*((U8 *) (down_ptr + 1)) << 8)
						+ (*((U8 *) (down_ptr + 2)) << 16)
						+ (*((U8 *) (down_ptr + 3)) << 24);

				dw_usb_buf_read_ptr = downloadAddress;
				dw_usb_buf_write_ptr = downloadAddress;
			}
			download_file_size = *((U8 *) (down_ptr + 4))
					+ (*((U8 *) (down_ptr + 5)) << 8)
					+ (*((U8 *) (down_ptr + 6)) << 16)
					+ (*((U8 *) (down_ptr + 7)) << 24);
			checkSum = 0;
			down_ptr = (U8 *) downloadAddress;

			rdpkt_ep3_check_sum((U8 *) down_ptr, fifoCnt - 8); //The first 8-bytes are deleted.
			down_ptr += fifoCnt - 8;

#if USBDMA
			//CLR_EP3_OUT_PKT_READY() is not executed.
			//So, USBD may generate NAK until DMA2 is configured for USB_EP3;
			writel((readl(&int_regs->INTMSK) | BIT_USBD), &int_regs->INTMSK);
			return;
#endif
		} else {
#if USBDMA
			printf("<ERROR>");
#endif
			rdpkt_ep3_check_sum((U8 *) down_ptr, fifoCnt);
			down_ptr += fifoCnt;  //fifoCnt=64
		}
#endif
		CLR_EP3_OUT_PKT_READY();
#if 0
		if(((rOUT_CSR1_REG&0x1)==1) && ((rEP_INT_REG & 0x8)==0))
		{
			fifoCnt=rOUT_FIFO_CNT1_REG;
			rdpkt_ep3_check_sum((U8 *)down_ptr,fifoCnt);
			down_ptr+=fifoCnt;  //fifoCnt=64
			CLR_EP3_OUT_PKT_READY();
		}
#endif
		return;
	}

	//I think that EPO_SENT_STALL will not be set to 1.
	if (out_csr3 & EPO_SENT_STALL) {
		dbg_printf("[STALL]");
		CLR_EP3_SENT_STALL();
		return;
	}
}

#if 0
void print_epo_pkt(U8 *pt,int cnt)
{
	int i;
	dbg_printf("[BOUT:%d:",cnt);
	for(i=0;i<cnt;i++)
	dbg_printf("%x,",pt[i]);
	dbg_printf("]");
}
#endif

void rdpkt_ep3_check_sum(U8 *buf, int num) {
	int i;
	struct s3c24x0_usb_device * const usb_dev_regs =
			s3c24x0_get_base_usb_device();

	for (i = 0; i < num; i++) {
		buf[i] = readb(&usb_dev_regs->fifo[3].EP_FIFO_REG);
		checkSum += buf[i];
	}
}

void isr_dma2(void) {
	struct s3c24x0_interrupt * int_regs = s3c24x0_get_base_interrupt();
	struct s3c24x0_usb_device * const usb_dev_regs =
			s3c24x0_get_base_usb_device();
	U8 out_csr3;
	U32 dw_empty_cnt;
	U8 save_index_reg = readb(&usb_dev_regs->INDEX_REG);
	writeb(3, &usb_dev_regs->INDEX_REG);
	out_csr3 = readb(&usb_dev_regs->OUT_CSR1_REG);

	clear_pending((int) BIT_DMA2);

	if (!total_dma_count)
		total_dma_count = dw_will_dma_cnt + EP3_PKT_SIZE;
	else
		total_dma_count += dw_will_dma_cnt;

	dw_usb_buf_write_ptr = ((dw_usb_buf_write_ptr + dw_will_dma_cnt
			- dw_usb_buf_base) % dw_usb_buf_size) + dw_usb_buf_base;

	if (total_dma_count >= download_file_size) {
		total_dma_count = download_file_size;

		config_ep3_int_mode();

		if (out_csr3 & EPO_OUT_PKT_READY) {
			CLR_EP3_OUT_PKT_READY();
		}
		writel(((readl(&int_regs->INTMSK) | BIT_DMA2) & ~(BIT_USBD)),
				&int_regs->INTMSK);
	} else {
		if ((total_dma_count + 0x80000) < download_file_size) {
			dw_will_dma_cnt = 0x80000;
		} else {
			dw_will_dma_cnt = download_file_size - total_dma_count;
		}

		dw_empty_cnt = (dw_usb_buf_read_ptr - dw_usb_buf_write_ptr - 1
				+ dw_usb_buf_size) % dw_usb_buf_size;
		if (dw_empty_cnt >= dw_will_dma_cnt) {
			config_ep3_dma_mode(dw_usb_buf_write_ptr, dw_will_dma_cnt);
		} else {
			b_dma_pending = 1;
		}
	}
	writeb(save_index_reg, &usb_dev_regs->INDEX_REG);
}

void clear_ep3_out_pkt_ready(void) {
	struct s3c24x0_usb_device * const usb_dev_regs =
			s3c24x0_get_base_usb_device();
	U8 out_csr3;
	writeb(3, &usb_dev_regs->INDEX_REG);
	out_csr3 = readb(&usb_dev_regs->OUT_CSR1_REG);
	CLR_EP3_OUT_PKT_READY();
}
