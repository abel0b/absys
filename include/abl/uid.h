#ifndef ABLUID__H
#define ABLUID__H

#include <stdint.h>

void seed(uint64_t s);

uint64_t genuint64();

void genuid(char uid[8]);

void genuidmaj(char uid[8]);

#endif