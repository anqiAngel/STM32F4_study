/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h" /* FatFs lower layer API */
// #include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
// #include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
// #include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */
#include "bsp_spi.h"
/* Definitions of physical drive number for each drive */
// #define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
// #define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
// #define USB		2	/* Example: Map USB MSD to physical drive 2 */

#define SD_CARD 0
#define SPI_FLASH 1
#define FLASH_SECTOR_SIZE 4096

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(
	BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = 0;
	switch (pdrv)
	{
	case SD_CARD:

		// translate the reslut code here

		return stat;

	case SPI_FLASH:
		if (SPI_FLASH_Read_ID() == 0x17)
		{
			/* code */
			stat &= ~STA_NOINIT;
		}
		else
		{
			/* code */
			stat |= STA_NOINIT;
		}
		// translate the reslut code here
		return stat;
	}
	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize(
	BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv)
	{
	case SD_CARD:
		// translate the reslut code here
		return stat;

	case SPI_FLASH:
		SPI_FLASH_Init();
		stat = disk_status(SPI_FLASH);
		// translate the reslut code here
		return stat;
	}
	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(
	BYTE pdrv,	  /* Physical drive nmuber to identify the drive */
	BYTE *buff,	  /* Data buffer to store read data */
	DWORD sector, /* Sector address in LBA */
	UINT count	  /* Number of sectors to read */
)
{
	DRESULT res;

	switch (pdrv)
	{
	case SD_CARD:
		// translate the arguments here

		// translate the reslut code here

		return res;

	case SPI_FLASH:
		// translate the arguments
		// 使用后10MB
		sector += 1536;
		SPI_FLASH_Read_Data(sector * FLASH_SECTOR_SIZE, buff, count * FLASH_SECTOR_SIZE);
		// translate the reslut code here
		res = RES_OK;
		return res;
	}

	return RES_PARERR;
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write(
	BYTE pdrv,		  /* Physical drive nmuber to identify the drive */
	const BYTE *buff, /* Data to be written */
	DWORD sector,	  /* Sector address in LBA */
	UINT count		  /* Number of sectors to write */
)
{
	DRESULT res;
	switch (pdrv)
	{
	case SD_CARD:
		// translate the arguments here

		// translate the reslut code here

		return res;

	case SPI_FLASH:
		// translate the arguments here
		// 使用后10MB
		sector += 1536;
		for (int i = 0; i < count; i++)
		{
			/* code */
			SPI_FLASH_Erase_Sector(sector * FLASH_SECTOR_SIZE);
			SPI_FLASH_Page_Program(sector * FLASH_SECTOR_SIZE, (uint8_t *)buff, FLASH_SECTOR_SIZE);
			sector++;
			buff += FLASH_SECTOR_SIZE;
		}
		// translate the reslut code here
		res = RES_OK;
		return res;
	}

	return RES_PARERR;
}
#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl(
	BYTE pdrv, /* Physical drive nmuber (0..) */
	BYTE cmd,  /* Control code */
	void *buff /* Buffer to send/receive control data */
)
{
	DRESULT res;
	switch (pdrv)
	{
	case SD_CARD:

		// Process of the command for the SD_CARD drive
		return res;

	case SPI_FLASH:
		// Process of the command for the SPI_FLASH
		switch (cmd)
		{
		case GET_SECTOR_COUNT:
			/* code */
			*(DWORD *)buff = (16 * 1024 * 1024 / FLASH_SECTOR_SIZE) - 1536;
			return RES_OK;
		case GET_SECTOR_SIZE:
			/* code */
			*(WORD *)buff = FLASH_SECTOR_SIZE;
			return RES_OK;
		case GET_BLOCK_SIZE:
			/* code */
			*(DWORD *)buff = 1;
			return RES_OK;
		case CTRL_SYNC:
			/* code */
			*(DWORD *)buff = 1;
			return RES_OK;
		default:
			return RES_PARERR;
		}
	}
	return RES_PARERR;
}
#endif

DWORD get_fattime(void)
{
	return 0;
}
