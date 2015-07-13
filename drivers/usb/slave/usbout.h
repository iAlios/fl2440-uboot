/****************************************************************
 NAME: usbout.h
 DESC: 
 HISTORY:
 Mar.25.2002:purnnamu: reuse the source of S3C2400X u24xmon 
 ****************************************************************/
 
#ifndef __USBOUT_H__
#define __USBOUT_H__

void ep3_handler(void);
void ep3_handler_optimized(void);

void isr_dma2(void);
void clear_ep3_out_pkt_ready(void);

#endif /*__USBOUT_H__*/
