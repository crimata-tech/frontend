#ifndef FRAMEBUFFER
#define FRAMEBUFFER


typedef struct {
    int frames_free, frames_used;
    char *data, *cursor;
} frame_buffer;


void init_fb ( frame_buffer *fb );

void delete_fb ( frame_buffer *fb );

void clear_fb ( frame_buffer *fb );

void insert_frames_fb ( frame_buffer *fb, char *frame_data, int frames_len );

void rewrite_frames_fb ( frame_buffer *fb, char *frame_data, int frames_len );

char* read_frame_at_cursor_fb ( frame_buffer *fb );


#endif
