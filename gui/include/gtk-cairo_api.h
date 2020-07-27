#ifndef GTK_CAIRO_API
#define GTK_CAIRO_API

/*
** Crimata Technologies - 2020
**
** Client Gtk-Cairo API
**
**
** An API that serves as a boilerplate for rendering graphics in the
** center of a given GObject or GTKWidget.
**
** The semantics are as follows:

**   **********************VARIABLES SEMANTICS************************

**   1. @cairo_surface_t *surface : tells functions to look for the
**   definition of surface in your code.
**
**   2. pthread_mutex_t mutex : Gives Mutual (MUT) Exclustion (EX)
**   functionality to functions so that they don't access surface
**   and context variables at the same time.

**   **********************FUNCTIONS SEMANTICS************************

**
**   3. @@invalidate_cb () : Calls gtk_widget_queue_draw() on a given
**   widget so that GTK knows to refresh it.
**
**   4. create_cairo_surface () : Allocate a region of the window to
**   create (technically update) the surface while also updating its 
**   surface_width and surface_height variables.
**
**   5. drawing_area_draw_cb () : Set this function up in a callback
**   so that it can refresh and paint over the cairo source every 
**   "frame" to obtain the animation effect.
**
**   6. resize_cairo_surface_cb () : Effectivly the same as create_-
**   cairo_surface but is called everytime the window gets resized.
**
**   @ - https://cairographics.org/manual/cairo-cairo-surface-t.html
**   @@ - _cb in name means should be used as a GTK callback.
 */

#include <gtk/gtk.h>

extern cairo_surface_t *surface;
extern int surface_width;
extern int surface_height;

extern pthread_mutex_t mutex;

gboolean invalidate_cb (gpointer widget);

void create_cairo_surface (GObject* uiBox);

void drawing_area_draw_cb (GtkWidget *widget, cairo_t *context);

void resize_cairo_surface_cb (GtkWidget *widget, GdkEvent *event);

#endif