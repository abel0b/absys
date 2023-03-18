#ifndef ABSYSUID__H
#define ABSYSUID__H

#include <stdint.h>
#include "absys/defs.h"

enum absys_uid_kind {
    ABSYS_UID_LALPHANUM = 0,
    ABSYS_UID_UALPHANUM = 1,
};

ABSYS_API void absys_uid_seed(uint64_t s);

ABSYS_API void absys_uid_gen(char uid[8], enum absys_uid_kind kind);

#endif
