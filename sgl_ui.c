//#include "sgl_ui.h"

//void sgl_ui_init(sgl_ui_t *ui, sgl_t *sgl)
//{
//    ui->sgl = sgl;
//}

//void sgl_ui_handler(sgl_ui_t *ui)
//{
//    sgl_display(ui->sgl);
//}

//void sgl_ui_event_porc(sgl_ui_t *ui)
//{
//    
//}

//void sgl_ui_animation_proc(sgl_ui_t *ui)
//{
//    
//}

//void sgl_ui_paint_porc(sgl_ui_t *ui, sgl_widget_t *widget, int x, int y)
//{
//    if(!(widget->flag & SGL_UI_FLAG_VISIBLE)) return;
//    int real_x = x + widget->base.x;
//    int real_y = y + widget->base.y;
//    sgl_ui_base_t* base = &widget->base;
//    dsal_list_node_handle_t temp = widget->son->head;
//    while(temp)
//    {
//        sgl_ui_paint_porc(ui, temp->data, real_x, real_y);
//        temp = temp->next;
//    }
//    switch(widget->type)
//    {
//        case SGL_UI_TYPE_RECT:sgl_draw_rectangle(ui->sgl, real_x, real_y, base->w, base->h, 1, base->color);break;
//        case SGL_UI_TYPE_ROUNDRECT:sgl_draw_round_rectangle(ui->sgl, real_x, real_y, base->w, base->h, base->r, 1, base->color);break;
////        case SGL_UI_TYPE_STRING:sgl_show_string(ui->sgl, real_x, real_y, base->w, base->h, base->r, 1, base->color);break;
////        case SGL_UI_TYPE_MONO_BITMAP:sgl_show_mono_bitmap(ui->sgl, real_x, real_y, base->w, base->h, 1, base->color);break;
//        case SGL_UI_TYPE_CIRCLE:sgl_draw_circle(ui->sgl, real_x, real_y, base->r, 1, base->color);break;
//        case SGL_UI_TYPE_ELLIPSE:sgl_draw_ellipse(ui->sgl, real_x, real_y, base->w, base->h, 1, base->color);break;
//        default:break;
//    }
//}

//void sgl_ui_proc(sgl_ui_t *ui)
//{
////    sgl_ui_event_porc(ui);
////    sgl_ui_animation_proc(ui);
//    sgl_ui_paint_porc(ui, &ui->act_screen, 0, 0);
//}
