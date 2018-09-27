#pragma once

#include <stdbool.h>

extern bool media_open(const char *title, int width, int height);
extern bool media_flip_frame_poll_events(void);
extern void media_close(void);