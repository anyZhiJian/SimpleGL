#include "sgl_line.h"
#include "sgl_function.h"
#include "sgl_point.h"

static void sgl_draw_original_hline(sgl_t *sgl, int x, int y, int len,
                                    uint32_t color) {
    int i;
    int x1 = x + len;
    if (len > 0)
        for (i = x; i < x1; ++i)
            sgl->draw_piexl(sgl, i, y, color);
    else if (len < 0)
        for (i = x; i > x1; --i)
            sgl->draw_piexl(sgl, i, y, color);
}

static void sgl_draw_original_vline(sgl_t *sgl, int x, int y, int len,
                                    uint32_t color) {
    int i;
    int y1 = y + len;
    if (len > 0)
        for (i = y; i < y1; ++i)
            sgl->draw_piexl(sgl, x, i, color);
    else if (len < 0)
        for (i = y; i > y1; --i)
            sgl->draw_piexl(sgl, x, i, color);
}

static int sgl_clip_hline(int *x, int *y, int *len, sgl_rect_t visible) {
    int x_end;
    if (*y < visible.top || *y > visible.bottom)
        return -1;
    if (*len > 0) {
        if (*x > visible.right)
            return -1;
        x_end = *x + *len - 1;
        if (x_end < visible.left)
            return -1;
        if (*x < visible.left)
            *x = visible.left;
        if (x_end > visible.right)
            x_end = visible.right;
        *len = x_end - *x + 1;
    } else if (*len < 0) {
        if (*x < visible.left)
            return -1;
        x_end = *x + *len + 1;
        if (x_end > visible.right)
            return -1;
        if (x_end < visible.left)
            x_end = visible.left;
        if (*x > visible.right)
            *x = visible.right;
        *len = x_end - *x - 1;
    }
    return 0;
}

static int sgl_clip_vline(int *x, int *y, int *len, sgl_rect_t visible) {
    int y_end;
    if (*x < visible.left || *x > visible.right)
        return -1;
    if (*len > 0) {
        if (*y > visible.bottom)
            return -1;
        y_end = *y + *len - 1;
        if (y_end < visible.top)
            return -1;
        if (*y < visible.top)
            *y = visible.top;
        if (y_end > visible.bottom)
            y_end = visible.bottom;
        *len = y_end - *y + 1;
    } else if (*len < 0) {
        if (*y < visible.top)
            return -1;
        y_end = *y + *len + 1;
        if (y_end > visible.bottom)
            return -1;
        if (y_end < visible.top)
            y_end = visible.top;
        if (*y > visible.bottom)
            *y = visible.bottom;
        *len = y_end - *y - 1;
    }
    return 0;
}

void sgl_draw_hline(sgl_t *sgl, int x, int y, int len, uint32_t color) {
    if (len == 0)
        return;
    if (sgl_clip_hline(&x, &y, &len, sgl->visible))
        return;
    if (sgl->rotate)
        sgl_rotated2original(&x, &y, sgl->max_x, sgl->max_y, sgl->rotate);
    if (sgl->page_num > 1)
        y -= sgl->page_start;
    switch (sgl->rotate) {
    case SGL_ROTATE_0:
        sgl_draw_original_hline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_90:
        sgl_draw_original_vline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_180:
        sgl_draw_original_hline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        sgl_draw_original_vline(sgl, x, y, -len, color);
        break;
    }
}

void sgl_draw_vline(sgl_t *sgl, int x, int y, int len, uint32_t color) {
    if (len == 0)
        return;
    if (sgl_clip_vline(&x, &y, &len, sgl->visible))
        return;
    if (sgl->rotate)
        sgl_rotated2original(&x, &y, sgl->max_x, sgl->max_y, sgl->rotate);
    if (sgl->page_num > 1)
        y -= sgl->page_start;
    switch (sgl->rotate) {
    case SGL_ROTATE_0:
        sgl_draw_original_vline(sgl, x, y, len, color);
        break;
    case SGL_ROTATE_90:
        sgl_draw_original_hline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_180:
        sgl_draw_original_vline(sgl, x, y, -len, color);
        break;
    case SGL_ROTATE_270:
        sgl_draw_original_hline(sgl, x, y, len, color);
        break;
    }
}

void sgl_draw_line(sgl_t *sgl, int x0, int y0, int x1, int y1, uint32_t color) {
    int i;
    int distance;
    int err_x = 0, err_y = 0;
    int inc_x = 1, inc_y = 1;
    int x = x0, y = y0;
    int dx = x1 - x0;
    int dy = y1 - y0;
    if (dx == 0) {
        sgl_draw_original_vline(sgl, x0, y0, dy, color);
        return;
    }
    if (dy == 0) {
        sgl_draw_original_hline(sgl, x0, y0, dx, color);
        return;
    }
    if (dx < 0) {
        dx = -dx;
        inc_x = -1;
    }
    if (dy < 0) {
        dy = -dy;
        inc_y = -1;
    }
    distance = dx > dy ? dx : dy;
    for (i = 0; i <= distance; ++i) {
        err_x += dx;
        err_y += dy;
        if (err_x > distance) {
            err_x -= distance;
            x += inc_x;
        }
        if (err_y > distance) {
            err_y -= distance;
            y += inc_y;
        }
        sgl_draw_point(sgl, x, y, color);
    }
}