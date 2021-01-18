#include <gtk-cairo_api.h>

cairo_surface_t *surface;
int surface_width;
int surface_height;

// // simply call gtk_widget_queue_draw on crimataAiBox
gboolean invalidate_cb (gpointer uiBox)
{
  gtk_widget_queue_draw (GTK_WIDGET (uiBox));
  return TRUE;
}

// refresh the drawing surface
void drawing_area_draw_cb (GtkWidget *widget, cairo_t *context)
{
  // copy the contents of the surface to the current context
  pthread_mutex_lock (&mutex);

  if (surface != (cairo_surface_t *)NULL)
  {
    cairo_set_source_rgb (context, 1, 1, 1);
    cairo_set_source_surface (context, surface, 0, 0);
    cairo_paint (context);
  }

  pthread_mutex_unlock (&mutex);
}

void create_cairo_surface (GObject* uiBox)
{
  GtkAllocation allocation;
  gtk_widget_get_allocation ((GtkWidget*) uiBox, &allocation);

  // create the surface -> what we are going to be painting on
  surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, allocation.width, 
    allocation.height);

  surface_width = allocation.width;
  surface_height = allocation.height;
}

/* Create drawing surface on crimataAiBox during Gtk config event. */
void resize_cairo_surface_cb (GtkWidget *widget, GdkEvent *event)
{
  if (event->type == GDK_CONFIGURE)
  {
    pthread_mutex_lock (&mutex);

    GtkAllocation allocation;
    gtk_widget_get_allocation (widget, &allocation);
    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, allocation.width, 
      allocation.height);

    surface_width = allocation.width;
    surface_height = allocation.height;

    pthread_mutex_unlock (&mutex);
  }
}