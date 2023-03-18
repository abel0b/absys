#ifndef ABSYSPATH__H
#define ABSYSPATH__H

#include "absys/str.h"

ABSYS_API void absys_path_push(struct absys_str* path, char* subpath);

ABSYS_API void absys_path_pushf(struct absys_str* path, char* fmt, ...);

ABSYS_API void absys_path_normalize(struct absys_str* path);

ABSYS_API char* absys_path_basename(struct absys_str* path);

ABSYS_API int absys_path_isds(char c);

#endif
