#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "frame_buffer.h"

#define BYTES_PER_FRAME (2)
#define INITIAL_FRAME_COUNT (480*100)


#define ALPHA (2)



void init_fb ( frame_buffer *fb ) {
    fb->frames_used = 0;
    fb->frames_free = INITIAL_FRAME_COUNT;
    fb->data = (char *) malloc(BYTES_PER_FRAME*INITIAL_FRAME_COUNT);
    fb->cursor = fb->data;
}


void delete_fb ( frame_buffer *fb ) {
    fb->frames_used = 0;
    fb->frames_free = 0;
    fb->cursor = NULL;
    free(fb->data);
}


void clear_fb ( frame_buffer *fb ) {
    free(fb->data);
    fb->data = (char *) malloc(BYTES_PER_FRAME*INITIAL_FRAME_COUNT);
    fb->cursor = fb->data;
    fb->frames_free = INITIAL_FRAME_COUNT;
    fb->frames_used = 0;
}


void insert_frames_fb ( frame_buffer *fb, char *frame_data, int frames_len ) {

    int frames = frames_len / BYTES_PER_FRAME;

    int cursor_diff = fb->cursor - fb->data;
    int data_len = (fb->frames_free+fb->frames_used)*BYTES_PER_FRAME;

    if (frames > fb->frames_free) {
        fb->data = realloc(fb->data, (data_len+frames_len)*ALPHA);
        fb->cursor = fb->data+cursor_diff;

        if (fb->frames_used*BYTES_PER_FRAME > data_len-cursor_diff) {
            memmove(fb->data+data_len, fb->data, (fb->frames_used*BYTES_PER_FRAME)-(data_len-cursor_diff));
        }
        fb->frames_used += frames;
        fb->frames_free = fb->frames_used;
    }

    data_len = (fb->frames_free+fb->frames_used)*BYTES_PER_FRAME;
    if (fb->frames_used*BYTES_PER_FRAME > data_len-cursor_diff) {
        memcpy(fb->data+((fb->frames_used*BYTES_PER_FRAME)-(data_len-cursor_diff)), frame_data, frames_len);
        fb->frames_free -= frames;
        fb->frames_used += frames;
        return;
    }
    if (frames_len+(fb->frames_used*BYTES_PER_FRAME) > data_len-cursor_diff) {
        int non_overlap = data_len - (cursor_diff+(fb->frames_used*BYTES_PER_FRAME));
        int overlap = frames_len - non_overlap;
        memcpy(fb->cursor+(fb->frames_used*BYTES_PER_FRAME), frame_data, non_overlap);
        memcpy(fb->data, &(frame_data[non_overlap]), overlap);
        fb->frames_free -= frames;
        fb->frames_used += frames;
        return;
    }

    memcpy(fb->cursor+(fb->frames_used*BYTES_PER_FRAME), frame_data, frames_len);
    fb->frames_free -= frames;
    fb->frames_used += frames;
}


void rewrite_frames_fb ( frame_buffer *fb, char *frame_data, int frames_len ) {
    int frames = frames_len / BYTES_PER_FRAME;

    if (frames > (fb->frames_used + fb->frames_free)) {
        fb->data = realloc(fb->data, frames_len*ALPHA);
        fb->frames_free = frames;
        fb->frames_used = frames;
    } else {
        fb->frames_free = fb->frames_free + fb->frames_used - frames;
        fb->frames_used = frames;
    }
    memcpy(fb->data, frame_data, frames_len);
    fb->cursor = fb->data;
}



char* read_frame_at_cursor_fb ( frame_buffer *fb ) {
    char *begin = fb->cursor;
    int frames_free = fb->frames_free;
    int frames_used = fb->frames_used;
    char *data = fb->data;

    if (frames_used == 0) {
        return NULL;
    }

    fb->cursor += BYTES_PER_FRAME;
    if (fb->cursor >= data + ((frames_free+frames_used)*BYTES_PER_FRAME)) {
        fb->cursor = data;
    }

    fb->frames_free += 1;
    fb->frames_used -= 1;

    return begin;
}


