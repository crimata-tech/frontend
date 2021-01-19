#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include <portaudio.h>
#include <fvad.h>
#include "frame_buffer.h"
#include "package_handler.h"
#include "anims.h"

#include "audio_handler.h"


#define SAMPLE_RATE  (16000)
#define BUFFER_mSECS    (30)
#define FRAMES_PER_BUFFER (160 * (BUFFER_mSECS/10))

#define NUM_CHANNELS    (1)


/* Select sample format. */
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"



static frame_buffer input_buffer;
static frame_buffer output_buffer;

/*  tri-state semaphore-esque variable:
 *  0 - output_buffer is available
 *  1 - output_buffer is being inserted into
 *  2 - output_buffer is being read from  */
static int write_to_o_buf = 0;

static bool streams_open;

static bool voice_activate = false;
static int vad_streak = 0;

static Fvad *vad;

int send_audio_package ();
int send_close_package ();

static int min_int (int a, int b) {
    return (a < b) ? a : b;
}




static int o_callback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *fb )
{
    (void) fb;
    unsigned int i;
    char *o_buf = (char *) outputBuffer;

    (void) inputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;

    if (write_to_o_buf == 0) {
        write_to_o_buf = 2;
        if (output_buffer.frames_used > 0) {
            int frames_to_read = min_int(framesPerBuffer, output_buffer.frames_used);
            for (int i = 0; i < frames_to_read; i++) {
                *((SAMPLE *)o_buf) = *((SAMPLE *) read_frame_at_cursor_fb(&output_buffer));
                o_buf += sizeof(SAMPLE);
            }
        } else {
            *((SAMPLE *)o_buf) = 0;
        }
        write_to_o_buf = 0;
    }

    return paContinue;
}


/* This routine will be called by the PortAudio engine when audio is needed.
** It may be called at interrupt level on some machines so don't do anything
** that could mess up the system like calling malloc() or free().
*/
static int i_callback( const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void *fb )
{
    (void) fb;
    int i;
    char *i_buf = (char *) inputBuffer;

    (void) outputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;


    i = fvad_process(vad, (int16_t *) i_buf, framesPerBuffer);

    if ( (i == 1) || voice_activate) {
        if (!voice_activate) {
            // set_anim(THINKING_ANIM);
            puts("Recording...");
        }
        if (i == 1) {
            voice_activate = true;
            vad_streak = 60;
        }
        insert_frames_fb(&input_buffer, i_buf, framesPerBuffer*sizeof(SAMPLE));
    }

    if (!voice_activate) {
        rewrite_frames_fb(&input_buffer, i_buf, framesPerBuffer*sizeof(SAMPLE));
    }

    if (vad_streak >= 1) {
        vad_streak -= 1;

        if (input_buffer.frames_used == (3*FRAMES_PER_BUFFER)) {
            send_audio_package();
        }

        /*  This means we had voice audio, but we no longer do so send what we got  */
        if (vad_streak == 0) {
            voice_activate = false;
            // set_anim(PULSE_ANIM);
            if (input_buffer.frames_used > 0) {
                send_audio_package();
            }
            send_close_package();
        }
    }

    return paContinue;
}


static void handle_input_stream () {
    PaStreamParameters  inputParameters;
    PaStream*           istream;
    PaError             err = paNoError;

    init_fb(&input_buffer);


    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */

    if (inputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default input device.\n");
        // goto done;
    }
    inputParameters.channelCount = 1;                    /* mono input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultHighInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;


    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &istream,
              &inputParameters,
              NULL,                  /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              i_callback,
              &input_buffer );
    if( err != paNoError ) {
        puts("Error when opening Port Audio input stream.");
    }

    err = Pa_StartStream( istream );
    // if( err != paNoError ) goto done;

    while( (( err = Pa_IsStreamActive( istream ) ) == 1) && streams_open)
    {
        Pa_Sleep(1000);
    }

    delete_fb(&input_buffer);

    // if( err < 0 ) goto done;

    err = Pa_CloseStream( istream );
    // if( err != paNoError ) goto done;

// done:
//     Pa_Terminate();
//     if( err != paNoError )
//     {
//         fprintf( stderr, "An error occured while using the portaudio stream\n" );
//         fprintf( stderr, "Error number: %d\n", err );
//         fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
//         err = 1;          /* Always return 0 or 1, but no other return codes. */
//     }
//     printf("input audio stream error code (0 is SUCCESS): %d\n\n", err);
}


static void handle_output_stream () {
    PaStreamParameters  outputParameters;
    PaStream*           ostream;
    PaError             err = paNoError;

    init_fb(&output_buffer);


    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto done;
    }

    outputParameters.channelCount = 1;                     /* mono output */
    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;


    err = Pa_OpenStream(
              &ostream,
              NULL,
              &outputParameters,                  /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,
              o_callback,
              &output_buffer );
    if( err != paNoError ) {
        puts("Error when opening Port Audio output stream.");
        goto done;
    }

    err = Pa_StartStream( ostream );
    if( err != paNoError ) goto done;

    while(((err = Pa_IsStreamActive( ostream ) ) == 1) && streams_open)
    {
        Pa_Sleep(1000);
    }

    delete_fb(&output_buffer);

    if( err < 0 ) goto done;

    err = Pa_CloseStream( ostream );
    if( err != paNoError ) goto done;

done:
    Pa_Terminate();
    if( err != paNoError )
    {
        fprintf( stderr, "An error occured while using the portaudio stream\n" );
        fprintf( stderr, "Error number: %d\n", err );
        fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
        err = 1;          /* Always return 0 or 1, but no other return codes. */
    }
    printf("output audio stream error code (0 is SUCCESS): %d\n\n", err);
}


void init_audio () {
    puts("Initializing audio stream");

    pthread_t in_th, out_th;
    int err = paNoError;

    err = Pa_Initialize();
    if( err != paNoError ) {
        fprintf(stderr, "error initializing port audio: %s\n", Pa_GetErrorText(err));
        exit(1);
    }

    streams_open = true;

    vad = fvad_new();
    if (!vad) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    if (fvad_set_sample_rate(vad, SAMPLE_RATE) < 0) {
        fprintf(stderr, "invalid mode\n");
        exit(1);
    }

    if (fvad_set_mode(vad, 1) < 0) {
        fprintf(stderr, "invalid mode\n");
        exit(1);
    }

    puts("Creating input and output streams.");
    sleep(1);
    pthread_create(&in_th, NULL, (void *) handle_input_stream, NULL);
    // pthread_create(&out_th, NULL, (void *) handle_output_stream, NULL);

    pthread_join(in_th, NULL);
    // pthread_join(out_th, NULL);

    fvad_free(vad);
}




void feed_output_buffer (char * data, int len) {

    while (write_to_o_buf == 2) {
        struct timespec t;
        t.tv_sec = 0;
        t.tv_nsec = 5000;
        nanosleep(&t, &t);
    }
    write_to_o_buf = 1;
    insert_frames_fb(&output_buffer, data, len);

    write_to_o_buf = 0;
}



int send_audio_package () {
    int err = 0;
    if ((err = send_package(input_buffer.data, input_buffer.frames_used*sizeof(SAMPLE), 0))) {
        printf("error sending audio package");
    }
    clear_fb(&input_buffer);
    return err;
}


int send_close_package () {
    int err = 0;
    if ((err = send_package("END", strlen("END"), 1))) {
        fprintf(stderr, "error sending closing package");
    }
    return err;
}



void close_audio () {
    streams_open = false;
}

