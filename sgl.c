#include "sgl.h"
#include <string.h>
#include <stdlib.h>

void sgl_init(sgl_t* sgl, void* buffer, uint32_t buffer_size, uint32_t page_num, uint32_t hor_res, uint32_t ver_res)
{
    sgl->buffer = buffer;
    sgl->buffer_size = buffer_size;
    sgl->hor_res = hor_res;
    sgl->ver_res = ver_res;
    sgl->max_x = hor_res - 1;
    sgl->max_y = ver_res - 1;
    if(page_num < 2)
        page_num = 1;
    sgl->page_num = page_num;
    sgl->page_width = sgl->ver_res / page_num;
    sgl->page_start = 0;
    sgl->page.left = 0;
    sgl->page.right = hor_res - 1;
    sgl->page.top = 0;
    sgl->page.bottom = sgl->page_width - 1;
    sgl->visible = sgl->page;
    sgl->offset_x = 0;
    sgl->offset_y = 0;
    sgl->font_info = font_get_font_info(font_Song_Typeface_8x16);
    sgl->rotate = SGL_ROTATE_0;
    sgl->frame_start_cb = NULL;
    sgl->frame_end_cb = NULL;
    sgl->draw_piexl = sgl_draw_piexl_mono;
}

void sgl_paint_start(sgl_t* sgl)
{
    if(sgl->page_start == 0 && sgl->frame_start_cb)
        sgl->frame_start_cb();
    if(sgl->page_num > 1)
    {
        sgl->page.left = 0;
        sgl->page.top = sgl->page_start;
        sgl->page.right = sgl->hor_res - 1;
        sgl->page.bottom = sgl->page_start + sgl->page_width - 1;
        if(sgl->rotate)
        {
            sgl_original2rotated(&sgl->page.left, &sgl->page.top, sgl->max_x, sgl->max_y, sgl->rotate);
            sgl_original2rotated(&sgl->page.right, &sgl->page.bottom, sgl->max_x, sgl->max_y, sgl->rotate);
            if(sgl->page.left > sgl->page.right)
                sgl_swap_int(&sgl->page.left, &sgl->page.right);
            if(sgl->page.top > sgl->page.bottom)
                sgl_swap_int(&sgl->page.top, &sgl->page.bottom);
        }
        sgl->visible = sgl->page;
    }
}

void sgl_paint_end(sgl_t* sgl)
{
    sgl->page_start += sgl->page_width;
    if(sgl->page_start >= sgl->ver_res)
    {
        sgl->page_start = 0;
        if(sgl->frame_end_cb != NULL)
            sgl->frame_end_cb();
    }
}

void sgl_clear(sgl_t* sgl, uint8_t data)
{
    memset(sgl->buffer, data, sgl->buffer_size);
}

void sgl_display(sgl_t* sgl)
{
    sgl_paint_start(sgl);
    if(sgl->draw)
        sgl->draw(sgl);
    if(sgl->flush)
        sgl->flush(sgl->buffer, sgl->buffer_size);
    sgl_paint_end(sgl);
}

void sgl_set_buffer(sgl_t* sgl, void* buffer)
{
    sgl->buffer = buffer;
}

void sgl_set_draw(sgl_t* sgl, void (* draw)(struct sgl_t*))
{
    sgl->draw = draw;
}

void sgl_set_flush(sgl_t* sgl, void (* flush)(void*, uint32_t))
{
    sgl->flush = flush;
}

void sgl_set_draw_piexl(sgl_t* sgl, void (* draw_piexl)(sgl_t*, int, int, uint32_t))
{
    sgl->draw_piexl = draw_piexl;
}

void sgl_set_frame_start_cb(sgl_t* sgl, void (* frame_start_cb)(void))
{
    sgl->frame_start_cb = frame_start_cb;
}

void sgl_set_frame_end_cb(sgl_t* sgl, void (* frame_end_cb)(void))
{
    sgl->frame_end_cb = frame_end_cb;
}

void sgl_set_font(sgl_t* sgl, font_t font)
{
    sgl->font_info = font_get_font_info(font);
}

void sgl_set_screen_rotation(sgl_t* sgl, sgl_rotate_t rotate)
{
    sgl->rotate = rotate;
    if(sgl->page_num < 2)
    {
        if(rotate == SGL_ROTATE_0 || rotate == SGL_ROTATE_180)
        {
            sgl->page.right = sgl->max_x;
            sgl->page.bottom = sgl->max_y;
        }
        else
        {
            sgl->page.right = sgl->max_y;
            sgl->page.bottom = sgl->max_x;
        }
        sgl_reset_visible_rect(sgl);
    }
}

void sgl_set_visible_rect(sgl_t* sgl, int left, int top, int right, int bottom)
{
    if(left < sgl->page.left)
        left = sgl->page.left;
    if(top < sgl->page.top)
        top = sgl->page.top;
    if(right > sgl->page.right)
        right = sgl->page.right;
    if(bottom > sgl->page.bottom)
        bottom = sgl->page.bottom;
    sgl->visible.left = left;
    sgl->visible.top = top;
    sgl->visible.right = right;
    sgl->visible.bottom = bottom;
}

void sgl_reset_visible_rect(sgl_t* sgl)
{
    sgl->visible = sgl->page;
}

void sgl_draw_piexl_mono(sgl_t* sgl, int x, int y, uint32_t color)
{
    switch(color)
    {
        case color_mono_light:      ((uint8_t*)sgl->buffer)[(y / 8) * sgl->hor_res + x] |= (1<<(y % 8));     break;
        case color_mono_dark:       ((uint8_t*)sgl->buffer)[(y / 8) * sgl->hor_res + x] &= ~(1<<(y % 8));    break;
        case color_mono_inverse:    ((uint8_t*)sgl->buffer)[(y / 8) * sgl->hor_res + x] ^= (1<<(y % 8));     break;
    }
}

void sgl_draw_piexl_rgb565(sgl_t* sgl, int x, int y, uint32_t color)
{
    ((uint16_t*)sgl->buffer)[(x + sgl->hor_res * y)] = (color << 8) | (color >> 8);
}
