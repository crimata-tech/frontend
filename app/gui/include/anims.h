#ifndef ANIMS
#define ANIMS

#include <gtk/gtk.h>
#include <pthread.h>
#include <stdbool.h> 

extern cairo_surface_t *surface;
extern int surface_width;
extern int surface_height;

extern char *render_text;

extern pthread_mutex_t mutex;

void * test_anim ();

void * print_anim ();

void * start_up_anim ();

void * recording_anim ();

void * standby_anim ();

void * bounce_anim ();

#endif