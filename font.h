/**
  * 字体模块
  *
  * 注意事项：
  * 1 字体取模格式：列行式纵向取模，C51数据格式，低位在前
  * 2 自定义字体步骤：
  *     1 仿照font_xxx头文件补充字库
  *     2 在font.c文件中包含自定义字库头文件
  *     3 在font_t枚举体中添加自定义字体的枚举变量
  *     4 在font_Getfont_info函数中的swtich-case结构中添加自定义字体的相关实现
  *
  */

#ifndef __FONT_H
#define __FONT_H

#include "stm32f10x.h"

typedef enum
{
    font_Song_Typeface_6x12,
    font_Song_Typeface_8x16,
    font_Song_Typeface_10x20,
    font_Song_Typeface_12x24,
    font_Song_Typeface_14x28,
    font_Song_Typeface_16x32,
    font_Consolas_6x12,
    font_Consolas_8x16,
    font_Consolas_10x20,
    font_Consolas_12x24,
    font_Consolas_14x28,
    font_Consolas_16x32,
    // font_xxx,(自定义字体添加字段)
} font_t;

typedef struct
{
    int width;
    int height;
    int fontsize;
    const uint8_t* font;
} font_info_t;

font_info_t font_get_font_info(font_t font);

#endif
