#include "font.h"
#include "font_Consolas.h"
#include "font_Song_Typeface.h"
// #include "font_xxx.h"(自定义字体添加字段)

font_info_t font_get_font_info(font_t font)
{
    font_info_t info;
    switch(font)
    {
        case font_Song_Typeface_6x12:   info.width = 6,     info.height = 12,   info.font = (uint8_t*)Song_Typeface_6x12;   break;
        case font_Song_Typeface_8x16:   info.width = 8,     info.height = 16,   info.font = (uint8_t*)Song_Typeface_8x16;   break;
        case font_Song_Typeface_10x20:  info.width = 10,    info.height = 20,   info.font = (uint8_t*)Song_Typeface_10x20;  break;
        case font_Song_Typeface_12x24:  info.width = 12,    info.height = 24,   info.font = (uint8_t*)Song_Typeface_12x24;  break;
        case font_Song_Typeface_14x28:  info.width = 14,    info.height = 28,   info.font = (uint8_t*)Song_Typeface_14x28;  break;
        case font_Song_Typeface_16x32:  info.width = 16,    info.height = 32,   info.font = (uint8_t*)Song_Typeface_16x32;  break;
//        case font_Consolas_6x12:        info.width = 6,     info.height = 12,   info.font = (uint8_t*)Consolas_6x12;        break;
//        case font_Consolas_8x16:        info.width = 8,     info.height = 16,   info.font = (uint8_t*)Consolas_8x16;        break;
//        case font_Consolas_10x20:       info.width = 10,    info.height = 20,   info.font = (uint8_t*)Consolas_10x20;       break;
//        case font_Consolas_12x24:       info.width = 12,    info.height = 24,   info.font = (uint8_t*)Consolas_12x24;       break;
//        case font_Consolas_14x28:       info.width = 14,    info.height = 28,   info.font = (uint8_t*)Consolas_14x28;       break;
//        case font_Consolas_16x32:       info.width = 16,    info.height = 32,   info.font = (uint8_t*)Consolas_16x32;       break;
        // case font_xxx:font_info.width = xx,font_info.height = xx,font_info.font = (uint8_t*)xxx;break;(自定义字体添加字段)
    }
    info.fontsize = info.width * ((info.height + 8 - 1) / 8); // 适用于非负数的向上取整除法(a + b - 1) / b
    return info;
}
