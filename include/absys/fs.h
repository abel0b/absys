#ifndef ABSYSFS__H
#define ABSYSFS__H

#include "absys/str.h"
#include "absys/defs.h"

ABSYS_API void absys_fs_mkdirp(char* path);

ABSYS_API void absys_fs_read2str(char* path, struct absys_str* dest);

#endif
