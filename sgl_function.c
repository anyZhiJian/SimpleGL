#include "sgl.h"

inline void sgl_swap_int(int *var0, int *var1)
{
    int temp = *var0;
    *var0 = *var1;
    *var1 = temp;
}

inline int sgl_min(int var0, int var1)
{
    if(var0 > var1)
        return var1;
    else
        return var0;
}

inline int sgl_max(int var0, int var1)
{
    if(var0 > var1)
        return var0;
    else
        return var1;
}

inline int sgl_check_rect(int left, int top, int right, int bottom, sgl_rect_t visible)
{
    if(left > visible.right || right < visible.left || top > visible.bottom || bottom < visible.top)
        return -1;
    return 0;
}

inline int sgl_clip_hline(int *x, int *y, int *len, sgl_rect_t visible)
{
    int x_end;
    if(*y < visible.top || *y > visible.bottom)
        return -1;
    if(*len > 0)
    {
        if(*x > visible.right)
            return -1;
        x_end = *x + *len - 1;
        if(x_end < visible.left)
            return -1;
        if(*x < visible.left)
            *x = visible.left;
        if(x_end > visible.right)
            x_end = visible.right;
        *len = x_end - *x + 1;
    }
    else if(*len < 0)
    {
        if(*x < visible.left)
            return -1;
        x_end = *x + *len + 1;
        if(x_end > visible.right)
            return -1;
        if(x_end < visible.left)
            x_end = visible.left;
        if(*x > visible.right)
            *x = visible.right;
        *len = x_end - *x - 1;
    }
    return 0;
}

inline int sgl_clip_vline(int *x, int *y, int *len, sgl_rect_t visible)
{
    int y_end;
    if(*x < visible.left || *x > visible.right)
        return -1;
    if(*len > 0)
    {
        if(*y > visible.bottom)
            return -1;
        y_end = *y + *len - 1;
        if(y_end < visible.top)
            return -1;
        if(*y < visible.top)
            *y = visible.top;
        if(y_end > visible.bottom)
            y_end = visible.bottom;
        *len = y_end - *y + 1;
    }
    else if(*len < 0)
    {
        if(*y < visible.top)
            return -1;
        y_end = *y + *len + 1;
        if(y_end > visible.bottom)
            return -1;
        if(y_end < visible.top)
            y_end = visible.top;
        if(*y > visible.bottom)
            *y = visible.bottom;
        *len = y_end - *y - 1;
    }
    return 0;
}

inline void sgl_rotated2original(int *x, int *y, int max_x, int max_y, sgl_rotate_t rotate)
{
    int temp = *x;
    if(rotate == sgl_rotate_90)
    {
        *x = max_x - *y;
        *y = temp;
    }
    else if(rotate == sgl_rotate_270)
    {
        *x = *y;
        *y = max_y - temp;
    }
    else if(rotate == sgl_rotate_180)
    {
        *x = max_x - *x;
        *y = max_y - *y;
    }
}

inline void sgl_original2rotated(int *x, int *y, int max_x, int max_y, sgl_rotate_t rotate)
{
    int temp = *x;
    if(rotate == sgl_rotate_90)
    {
        *x = *y;
        *y = max_x - temp;
    }
    else if(rotate == sgl_rotate_270)
    {
        *x = max_y - *y;
        *y = temp;
    }
    else if(rotate == sgl_rotate_180)
    {
        *x = max_x - *x;
        *y = max_y - *y;
    }
}

inline void sgl_align(int *x, int *y, int w, int h, sgl_align_t align)
{
    switch(align)
    {
        case sgl_align_up_left:        break;
        case sgl_align_up_right:       *x -= w - 1;break;
        case sgl_align_down_left:      *y -= h - 1;break;
        case sgl_align_down_right:     *x -= w - 1;*y -= h - 1;break;
        case sgl_align_center:         *x -= w / 2;*y -= h / 2;break;
        case sgl_align_up_center:      *x -= w / 2;break;
        case sgl_align_down_center:    *x -= w / 2;*y -= h - 1;break;
        case sgl_align_left_center:    *y -= h / 2;break;
        case sgl_align_right_center:   *x -= w - 1;*y -= h / 2;break;
    }
}
