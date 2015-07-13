/****************************************************************
 NAME: usbmain.h
 DESC: 
 HISTORY:
 Mar.25.2002:purnnamu: reuse the source of S3C2400X u24xmon 
 ****************************************************************/
 
#ifndef __USBMAIN_H__
#define __USBMAIN_H__

void usbd_main(void);
void isr_usbd(void);

void dbg_printf(char *fmt,...);


#endif /*__USBMAIN_H__*/
