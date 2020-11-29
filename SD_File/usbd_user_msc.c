/*----------------------------------------------------------------------------
 *      RL-ARM - USB
 *----------------------------------------------------------------------------
 *      Name:    usbd_user_msc.c
 *      Purpose: Mass Storage Device Class User module
 *      Rev.:    V4.70
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/
 
#include <RTL.h>
#include <rl_usb.h>
#include <File_Config.h>
#include <string.h>
#include "MCI_LPC23xx.h"
#include "LPC23xx.H"
#include "LCD.h"
 
extern FAT_VI *mc0;
extern Media_INFO info;
int i,k,count=0;
void usbd_msc_init () {
  USBD_MSC_BlockSize  = 512;
  USBD_MSC_BlockGroup = mc0->CaSize + 2;/* Cache buffer from File_Config.c    */
  USBD_MSC_BlockCount = info.block_cnt * (info.read_blen / 512);
  USBD_MSC_MemorySize = USBD_MSC_BlockCount * info.read_blen;
  USBD_MSC_BlockBuf   = (U8 *)mc0->CaBuf;
  USBD_MSC_MediaReady = __TRUE;
}
 
void usbd_msc_read_sect (U32 block, U8 *buf, U32 num_of_blocks) {
  if (USBD_MSC_MediaReady) {
    ioc_read_sect(block, buf, num_of_blocks, mc0);
  }
}
 
void usbd_msc_write_sect (U32 block, U8 *buf, U32 num_of_blocks) {
  if (USBD_MSC_MediaReady) {
		LED_Off(0xFF);
		count++;
    ioc_write_sect(block, buf, num_of_blocks, mc0);
		cmd_dir(NULL);
		if((USBD_MSC_MediaReady)&&(!((MCI_RX_ACTIVE)&(MCI_STATUS)))){
		/*for(k=0;k<10;k++){
		LED_Off(0xFF);
		for (i=0; i < 1000; i ++);
		LED_On(0xFF);
		for (i=0; i < 1000; i ++);*/
			set_cursor(0,0);
			lcd_print("Tx Done");
			for(k=0;k<10;k++){
		LED_Off(0xFF);
		for (i=0; i < 1000; i ++);
		LED_On(0xFF);
		for (i=0; i < 1000; i ++);
		}
	}
		
		}
	}
 