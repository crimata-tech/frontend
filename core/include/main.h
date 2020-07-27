#ifndef __TEST_MAIN
#define __TEST_MAIN		

#include <gtk/gtk.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <anims.h>
#include <gtk-cairo_api.h>
#include <package_handler.h>
#include <audio_handler.h>

GtkBuilder *builder;
GObject *homeWindow;
GObject *homeBox;
GObject *crimataAiBox;

char *render_text;

enum anim_e;

void * anim_handler ();

int main (int argc, char *argv[]);

#endif