/****************************************************************
 NAME: usbmain.c
 DESC: endpoint interrupt handler
 USB init jobs
 HISTORY:
 Mar.25.2002:purnnamu: ported for S3C2410X.
 Mar.27.2002:purnnamu: DMA is enabled.
 ****************************************************************/
#include <common.h>
#include <asm/arch/s3c24x0_cpu.h>
#include <asm/io.h>

#include "2440usb.h"
#include "usbmain.h"
#include "usblib.h"
#include "usbsetup.h"
#include "usbout.h"
#include "usbin.h"

#define BIT_USBD		(0x1<<25)
extern void
clear_pending(int bit);

void usbd_main(void) {
	init_descriptor_table();
	config_usbd();
	prepare_ep1_fifo();
}

void isr_usbd(void) {
	struct s3c24x0_usb_device * const usbdevregs =
			s3c24x0_get_base_usb_device();
	U8 usbdIntpnd, ep_intpnd;
	U8 saveIndexReg = readb(&usbdevregs->INDEX_REG);
	usbdIntpnd = readb(&usbdevregs->USB_INT_REG);
	ep_intpnd = readb(&usbdevregs->EP_INT_REG);

	if (usbdIntpnd & SUSPEND_INT) {
		writeb(SUSPEND_INT, &usbdevregs->USB_INT_REG);
	}
	if (usbdIntpnd & RESUME_INT) {
		writeb(RESUME_INT, &usbdevregs->USB_INT_REG);
	}
	if (usbdIntpnd & RESET_INT) {
		reconfig_usbd();
		writeb(RESET_INT, &usbdevregs->USB_INT_REG); //RESET_INT should be cleared after ResetUsbd().
		prepare_ep1_fifo();
	}

	if (ep_intpnd & EP0_INT) {
		writeb(EP0_INT, &usbdevregs->EP_INT_REG);
		ep0_handler();
	}
	if (ep_intpnd & EP1_INT) {
		writeb(EP1_INT, &usbdevregs->EP_INT_REG);
		ep1_handler();
	}

	if (ep_intpnd & EP2_INT) {
		writeb(EP2_INT, &usbdevregs->EP_INT_REG);
		//ep2_handler();
	}

	if (ep_intpnd & EP3_INT) {
		writeb(EP3_INT, &usbdevregs->EP_INT_REG);
		ep3_handler();
	}

	if (ep_intpnd & EP4_INT) {
		writeb(EP4_INT, &usbdevregs->EP_INT_REG);
		//ep4_handler();
	}

	clear_pending((int) BIT_USBD);
	writeb(saveIndexReg, &usbdevregs->INDEX_REG);
}

/******************* Consol printf for debug *********************/

#define DBGSTR_LENGTH (0x1000)
U8 dbg_str_fifo[DBGSTR_LENGTH];
volatile U32 dbg_str_rd_pt = 0;
volatile U32 dbg_str_wr_pt = 0;

void _wr_dbg_str_fifo(U8 c) {
	dbg_str_fifo[dbg_str_wr_pt++] = c;
	if (dbg_str_wr_pt == DBGSTR_LENGTH)
		dbg_str_wr_pt = 0;

}

#if 0
void dbg_printf(char *fmt,...)
{
	int i,slen;
	va_list ap;
	char string[256];

	va_start(ap,fmt);
	vsprintf(string,fmt,ap);

	slen=strlen(string);

	for(i=0;i<slen;i++) {
		_wr_dbg_str_fifo(string[i]);
	}

	va_end(ap);
	puts(string);
}
#else
void dbg_printf(char *fmt, ...) {
}
#endif

