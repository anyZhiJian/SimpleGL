#include "sgl.h"
#include <stdio.h>
#include <stdarg.h>

void sgl_show_string(sgl_t *sgl, int x, int y, const char *str, int length, sgl_align_t align, sgl_dir_t dir, uint32_t color)
{
    int i;
    int fontwidth = sgl->font_info.width;
    int fontheight = sgl->font_info.height;
    switch(dir)
    {
        case sgl_dir_up:
            sgl_align(&x, &y, fontwidth * length, fontheight, align);
            for(i = 0; i < length; ++i)
                sgl_show_mono_bitmap(sgl, x + i * fontwidth, y, fontwidth, fontheight, &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize], dir, color);
            break;
        case sgl_dir_right:
            sgl_align(&x, &y, fontheight, fontwidth * length, align);
            for(i = 0; i < length; ++i)
                sgl_show_mono_bitmap(sgl, x, y + i * fontwidth, fontwidth, fontheight, &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize], dir, color);
            break;
        case sgl_dir_left:
            sgl_align(&x, &y, fontheight, fontwidth * length, align);
            y += (length - 1) * fontwidth;
            for(i = 0; i < length; ++i)
                sgl_show_mono_bitmap(sgl, x, y - i * fontwidth, fontwidth, fontheight, &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize], dir, color);
            break;
        case sgl_dir_down:
            sgl_align(&x, &y, fontwidth * length, fontheight, align);
            x += (length - 1) * fontwidth;
            for(i = 0; i < length; ++i)
                sgl_show_mono_bitmap(sgl, x - i * fontwidth, y, fontwidth, fontheight, &sgl->font_info.font[(str[i] - ' ') * sgl->font_info.fontsize], dir, color);
            break;
    }
}

int sgl_show_format_string(sgl_t *sgl, int x, int y, sgl_align_t align, sgl_dir_t dir, uint32_t color, const char *format, ...)
{
    char buffer[sgl_FORMAT_STRING_BUFFERSIZE];
    va_list args;
    va_start(args, format);
    int length = vsnprintf(buffer, sgl_FORMAT_STRING_BUFFERSIZE, format, args);
    va_end(args);
    sgl_show_string(sgl, x, y, buffer, length, align, dir, color);
    return length;
}
