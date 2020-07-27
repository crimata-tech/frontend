#ifndef AUDIOHANDLER
#define AUDIOHANDLER


void init_audio ();

void feed_output_buffer ( char *data, int len );

int send_audio_package ();

void close_audio ();


#endif
