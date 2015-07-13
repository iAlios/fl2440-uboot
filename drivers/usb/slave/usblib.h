/****************************************************************
 NAME: usblib.h
 DESC: 
 HISTORY:
 Mar.25.2002:purnnamu: ported for S3C2410X.
 ****************************************************************/
#ifndef __USBLIB_H__
#define __USBLIB_H__

#include "2440usb.h"
#include "def.h"

#define PWR_REG_DEFAULT_VALUE (DISABLE_SUSPEND)

void config_usbd(void);
void reconfig_usbd(void);

void rd_pkt_ep0(U8 *buf,int num);
void wr_pkt_ep0(U8 *buf,int num);
void wr_pkt_ep1(U8 *buf,int num);
void wr_pkt_ep2(U8 *buf,int num);
void rd_pkt_ep3(U8 *buf,int num);
void rd_pkt_ep4(U8 *buf,int num);

void config_ep3_int_mode(void);
void config_ep3_dma_mode(U32 bufAddr,U32 count);

#endif /*__USBLIB_H__*/

