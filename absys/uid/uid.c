#include "absys/uid.h"
#include "absys/time.h"
#include "absys/log.h"
#include <stdio.h>
#include <stdlib.h>

static uint64_t state = 1;

ABSYS_API void absys_uid_seed(uint64_t s) {
    state = s;
}
 
ABSYS_INTERNAL uint64_t genuint64() {
    uint64_t x = state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return state = x;
}

static void genuid_aux(char uid[8], char alphabet[16]) {
    uint64_t num = absys_time_get_us();
    unsigned char* buf = (unsigned char*)&num;
    for(int i = 0; i < 8; ++i) {
        uid[i] = alphabet[(int)buf[7 - i] / 16];
    }
}

ABSYS_API void absys_uid_gen(char uid[8], enum absys_uid_kind kind) {
    switch(kind) {
	case ABSYS_UID_LALPHANUM:
            genuid_aux(uid, "0123456789abcdef");
	    break;
	case ABSYS_UID_UALPHANUM:
    	    genuid_aux(uid, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	    break;
	default:
	    absys_elog("invalid kind %d for abl uid", kind);
	    exit(1);
	    break;
    }
}
