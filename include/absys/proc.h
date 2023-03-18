#ifndef ABSYSPROC__H
#define ABSYSPROC__H

#include <stdio.h>
#include "absys/defs.h"

ABSYS_API int absys_spawn(char* prog, char* argv[], FILE* stdoutlog);

#endif
