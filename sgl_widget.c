//#include "sgl_ui.h"

//sgl_widget_handle_t sgl_widget_create(sgl_widget_handle_t parent)
//{
//    sgl_widget_handle_t widget = dsal_malloc(sizeof(sgl_widget_t));
//    if(widget)
//    {
//        memset(widget, 0, sizeof(sgl_widget_t));
//        widget->son = dsal_list_create_list(sizeof(sgl_widget_t));
//        if(widget->son)
//        {
//            widget->parent = parent;
//            dsal_list_add(parent->son, -1, widget);
//        }
//        else
//        {
//            dsal_free(widget);
//            return NULL;
//        }
//    }
//    return widget;
//}

//sgl_widget_handle_t sgl_widget_create_rectangle(sgl_widget_handle_t parent, int w, int h)
//{
//    sgl_widget_handle_t widget = sgl_widget_create(parent);
//    if(widget)
//    {
//        widget->type = SGL_UI_TYPE_RECT;
//        widget->base.w = w;
//        widget->base.h = h;
//    }
//    return widget;
//}

//sgl_widget_handle_t sgl_widget_create_round_rectangle(sgl_widget_handle_t parent, int w, int h, int r)
//{
//    sgl_widget_handle_t widget = sgl_widget_create(parent);
//    if(widget)
//    {
//        widget->type = SGL_UI_TYPE_ROUNDRECT;
//        widget->base.w = w;
//        widget->base.h = h;
//        widget->base.r = r;
//    }
//    return widget;
//}

//sgl_widget_handle_t sgl_widget_create_string(sgl_widget_handle_t parent, char *string, int length)
//{
//    sgl_widget_handle_t widget = sgl_widget_create(parent);
//    if(widget)
//    {
//        widget->type = SGL_UI_TYPE_STRING;
//    }
//    return widget;
//}

//sgl_widget_handle_t sgl_widget_create_mono_bitmap(sgl_widget_handle_t parent, const uint8_t *bitmap, int w, int h)
//{
//    sgl_widget_handle_t widget = sgl_widget_create(parent);
//    if(widget)
//    {
//        widget->type = SGL_UI_TYPE_MONO_BITMAP;
//        widget->base.w = w;
//        widget->base.h = h;
//    }
//    return widget;
//}

//sgl_widget_handle_t sgl_widget_create_circle(sgl_widget_handle_t parent, int r)
//{
//    sgl_widget_handle_t widget = sgl_widget_create(parent);
//    if(widget)
//    {
//        widget->type = SGL_UI_TYPE_CIRCLE;
//        widget->base.r = r;
//    }
//    return widget;
//}

//sgl_widget_handle_t sgl_widget_create_ellipse(sgl_widget_handle_t parent, int rx, int ry)
//{
//    sgl_widget_handle_t widget = sgl_widget_create(parent);
//    if(widget)
//    {
//        widget->type = SGL_UI_TYPE_ELLIPSE;
//        widget->base.w = rx;
//        widget->base.h = ry;
//    }
//    return widget;
//}

//void sgl_widget_create_list(sgl_widget_handle_t parent, char *list, uint32_t size)
//{
//    
//}
