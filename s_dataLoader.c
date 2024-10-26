#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <kos/fs.h>
//#include <kos/iso9660.h>
#include <kos.h>

#include "s_dataLoader.h"

void DATA_Init()
{
	fs_iso9660_init();
	//fs_romdisk_init();
	//fs_romdisk_mount("/data", NULL, 0);
}

uint8_t* DATA_GetFileData(const char* filename)
{
	file_t file = fs_open(filename, O_RDONLY);
	uint32_t size = fs_total(file);
	uint8_t* buffer = (uint8_t*)malloc(size);
	
	if (!buffer) return NULL;
	
	int32_t res = fs_read(file, buffer, size);
	fs_close(file);
	
	if (res != size)
	{
		free(buffer);
		return NULL;
	}
	
	return buffer;
}

void DATA_Close()
{
	fs_iso9660_shutdown();
}
