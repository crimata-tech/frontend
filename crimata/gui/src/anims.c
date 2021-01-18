#include <math.h>

#include "anims.h"
#include "eases.h"

static const int frames_per_sec = 60;

void * init_context ()
{
    pthread_mutex_lock (&mutex);
    cairo_t *cr = cairo_create (surface);
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_rectangle (cr, 0, 0, surface_width, surface_height);
    cairo_fill (cr);
    cairo_translate (cr, surface_width/2, surface_height/2);
    return cr;
}

void * destroy_context (cairo_t *cr)
{
    cairo_destroy (cr);
    pthread_mutex_unlock (&mutex);
    usleep (1E6 / frames_per_sec);
    return 0;
}

/* Animate a logo through multiple calls and adjusting x y cords.
** X's and Y's @ 0 means logo is at default position:
**
**                        *
**                       * *
*/
void logo (cairo_t *cr, float x1, // circle top
                        float y1, 
                        float x2, // circle bottom left
                        float y2, 
                        float x3, // circle bottom right
                        float y3
                        )
{
    // circle top
    cairo_arc (cr, x1+0, y1-10, 7.25, 0, 6.28);
    cairo_fill (cr);

    // circle bottom left
    cairo_arc (cr, x2-9.34, y2+6, 7.25, 0, 6.28);
    cairo_fill (cr);

    // circle bottom right
    cairo_arc (cr, x3+9.34, y3+6, 7.25, 0, 6.28);
    cairo_fill (cr);
}

#include "start_up_anim.c"
#include "recording_anim.c"
#include "standby_anim.c"
#include "bounce_anim.c"

void * print_anim ()
{
    while (1)
    {
        cairo_t *cr = init_context ();

        //! Render text based on global text variable.
        cairo_set_source_rgba (cr, 0.2, 0.2, 0.2, 1);
        cairo_text_extents_t te;
        cairo_select_font_face (cr, "Montserrat", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 20);
        cairo_text_extents (cr, render_text, &te);
        cairo_move_to (cr, te.width/-2, te.height/2);
        cairo_show_text (cr, render_text);

        destroy_context (cr);
    }
}





