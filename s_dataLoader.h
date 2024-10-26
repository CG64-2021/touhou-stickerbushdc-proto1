#ifndef __S_DATALOADER_H__
#define __S_DATALOADER_H__

void DATA_Init();
uint8_t* DATA_GetFileData(const char* filename);
void DATA_Close();

#endif