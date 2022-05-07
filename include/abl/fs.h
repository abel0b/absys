#ifndef ABLFS__H
#define ABLFS__H

#include "abl/str.h"

void ensuredir(char* path);

int isds(char c);

void read_to_str(char* path, struct abl_str* dest);

#endif
