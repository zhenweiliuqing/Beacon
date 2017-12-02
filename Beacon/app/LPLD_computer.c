#include "common.h"
#include "LPLD_computer.h"

void lpld_sendimg(void *imgaddr, uint32_t imgsize)
{
#define CMD_IMG     1
    uint8_t cmdf[2] = {CMD_IMG, ~CMD_IMG};    //山外上位机 使用的命令
    uint8_t cmdr[2] = {~CMD_IMG, CMD_IMG};    //山外上位机 使用的命令

    LPLD_UART_PutCharArr(UART5, cmdf, sizeof(cmdf));    //先发送命令

    LPLD_UART_PutCharArr(UART5, (uint8_t *)imgaddr, imgsize); //再发送图像

    LPLD_UART_PutCharArr(UART5, cmdr, sizeof(cmdr));    //先发送命令
}


/*!
 *  @brief      山外多功能调试助手上位机，线性CCD显示函数
 *  @param      ccdaddr    CCD图像起始地址
 *  @param      ccdsize    CCD图像占用空间的大小
 *  @since      v5.0
*  Sample usage:
             具体用法参考这帖子:
            【山外线性CCD】上位机显示例程和超广角采集效果 - 智能车资料区
             http://vcan123.com/forum.php?mod=viewthread&tid=6340&ctid=27
 */
void lpld_sendccd(void *ccdaddr, uint32_t ccdsize)
{
#define CMD_CCD     2
    uint8_t cmdf[2] = {CMD_CCD, ~CMD_CCD};    //开头命令
    uint8_t cmdr[2] = {~CMD_CCD, CMD_CCD};    //结尾命令

    LPLD_UART_PutCharArr(UART5, cmdf, sizeof(cmdf));    //先发送命令

    LPLD_UART_PutCharArr(UART5, (uint8_t *)ccdaddr, ccdsize); //再发送图像

    LPLD_UART_PutCharArr(UART5, cmdr, sizeof(cmdr));    //再发送命令
}
