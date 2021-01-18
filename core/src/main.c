/*
** Crimata Technologies - 2020
**
** Client Main
**
**
** This is the top-level file for the client program. It is the home
** of main (), which spawns all the nessesary threads and ensures
** the program shutsdown correctly.  
**
** The functions are as follows:
**
**   **********************FUNCTIONS SEMANTICS************************
**
**   1. main () : spawns three additional threads for audio, networking
**      and the "main loop" in addition to initiating the GTK gui.
**
**   @ - 
**   @@ - 
 */

#include <main.h>

GtkBuilder *builder;
GObject *homeWindow;
GObject *homeBox;
GObject *crimataAiBox;

pthread_t drawing_thread;
pthread_mutex_t mutex;

enum anim_e 
{ 
    BOUNCE_ANIM, 
    STANDBY_ANIM 
};

static char* user_id;

void * anim_handler ()
{
    // start_up_anim ();

    // while (!exit)
    // {
    //     switch (current_anim)
    //     {
    //         case BOUNCE_ANIM:
    //             bounce_anim ();
    //             break;

    //         case STANDBY_ANIM:
    //             standby_anim ();
    //             break;
    //     }
    // }
    return 0;
}

void * server_connect (void *ptr)
{
    puts("Connecting to the server!");

    if (connect_socket ( "127.0.0.1", 1040 ) < 0) {
        puts("error connecting to socket");
        exit(1);
    }

    /* Send the user_id to the backend. */
    user_id = (char *) malloc(2);
    strcpy(user_id, "1");
    send_package(user_id, strlen(user_id), 2);

    return 0;
}

void * main_loop (void *ptr)
{
    sleep(1);

    bool exit = false;

    // recv_package() will write to this variable.
    char *package_response = malloc(sizeof(int));

    while (!exit) {

        int mes_len;
        int mes_type = recv_package(&package_response, &mes_len);

        switch (mes_type) {

            case 0:
                printf("audio message length: %d\n", mes_len);
                feed_output_buffer(package_response, mes_len);
                break;

            case 1:
                if (strcmp(package_response, "EXIT") == 0) {
                    exit = true;
                } else {
                    //! write to render_text memory address.
                    render_text = (char *) malloc(sizeof package_response);
                    strcpy(render_text, (const char *) package_response);
                    puts((const char *) package_response);
                }
                break;

            case -1:
                puts("error parsing package");
                break;
        }
    }

    free(package_response);

    return 0;
}

int main (int argc, char *argv[])
{
    pthread_t _admin, _main, _audio;

    //! Launch non-UI threads before initializing the UI.
    //! Le9t's simply try connecting to the server.
    //! Now, let's kickstarting the main loop.
    pthread_create(&_admin, NULL, (void *) server_connect, NULL);
    pthread_create(&_main, NULL, (void *) main_loop, NULL);
    pthread_create(&_audio, NULL, (void *) init_audio, NULL);


 //    gtk_init (&argc, &argv);

 //    GError *error = NULL;
 //    builder = gtk_builder_new ();
 //    gtk_builder_add_from_file (builder, "../gui/src/window.ui", &error);

 //    /* Set up hooks for relevant UI elements. */
 //    homeWindow = gtk_builder_get_object (builder, "homeWindow");
 //    homeBox = gtk_builder_get_object (builder, "homeBox");
 //    crimataAiBox = gtk_builder_get_object (builder, "crimataAiBox");

 //    /* Allocate area of window to have drawing functionality and set dims. */
 //    create_cairo_surface(crimataAiBox);

 //    /* CrimataAi animations */
	// pthread_mutex_init (&mutex, NULL);
 //    pthread_create (&drawing_thread, NULL, anim_handler, NULL);

 //    /* Create a timer to invalidate (refresh) crimataAiBox at 60Hz
 //    ** Needs to only be called when crimataAiBox is showing.
 //    */
 //    g_timeout_add (1000 / 60, invalidate_cb, (void *) crimataAiBox);

 //    /* Assign UI opertaions using GTK singals */
 //    g_signal_connect (homeWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
 //    g_signal_connect (crimataAiBox, "draw", G_CALLBACK (drawing_area_draw_cb), NULL);
 //    g_signal_connect (crimataAiBox, "configure-event", G_CALLBACK (resize_cairo_surface_cb), NULL);

 //    gtk_main();

    while (1) {
        sleep(1);
    }


    close_audio();
    close_socket();

    pthread_join(_audio, NULL);
    pthread_join(_admin, NULL);
    // pthread_join(_main, NULL);

    return 0;
}