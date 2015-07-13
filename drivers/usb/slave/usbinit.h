/****************************************************************
 NAME: u2440mon.h
 DESC: 
 HISTORY:
 Mar.29.2002:purnnamu: created first
 ****************************************************************/
 
#ifndef __U241MON_H__
#define __U241MON_H__

extern volatile unsigned char *down_ptr;
extern volatile U32 total_dma_count;
extern volatile U32 download_file_size;
extern volatile U32 downloadAddress;
extern volatile U16 checkSum;

extern int download_run;
extern U32 temp_download_address;

#endif /*__U241MON_H__*/
