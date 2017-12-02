#ifndef _LPLD_COMPUTER_H_
#define _LPLD_COMPUTER_H_

#include "common.h"

extern void lpld_sendimg(void *imgaddr, uint32_t imgsize);
extern void lpld_sendccd(void *ccdaddr, uint32_t ccdsize);
extern void lpld_sendware(void *wareaddr, uint32_t waresize);

#endif