#ifndef ABLPATH__H
#define ABLPATH__H

#include "abl/str.h"

void abl_path_push(struct abl_str* path, char* subpath);

void abl_path_pushf(struct abl_str* path, char* fmt, ...);

void abl_path_normalize(struct abl_str* path);

char* abl_path_basename(struct abl_str* path);

#endif
