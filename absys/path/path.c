#include "absys/path.h"
#include "absys/fs.h"
#include "absys/utils.h"
#include <stdarg.h>

ABSYS_API void absys_path_push(struct absys_str* path, char* subpath) {
    absys_assert(path->len);
    if (absys_path_isds(path->data[path->len - 1])) {
        absys_str_cat(path, subpath);
    }
    else {
        absys_str_catf(path, "/%s", subpath);
    }
}

ABSYS_API void absys_path_normalize(struct absys_str* path) {
    // TODO: get rid of ../ ./

    int i = 0;
    if (path->len && path->data[0] == '.') {
        i = 1;
        while(absys_path_isds(path->data[i])) {
            i ++;
        }
    }

    int cur = 0;
    while(i < path->len) {
        if(absys_path_isds(path->data[i])) {
            path->data[cur++] = '/';
            while(absys_path_isds(path->data[i])) {
                i++;
            }
        }
        else {
            path->data[cur++] = path->data[i++];
        }
    }

    if (absys_path_isds(path->len && path->data[cur - 1])) {
        -- cur;
    }

    path->data[cur] = '\0';
    path->len = cur;
}

ABSYS_API int absys_path_isds(char c) {
#if WINDOWS
    return (c == '/') || (c == '\\');
#else
    return c == '/';
#endif
}

ABSYS_API char* absys_path_basename(struct absys_str* path) {
    
    int base = 0;
    {
        int i = 0;
        char* pathiter = path->data;
        while(*pathiter != '\0') {
            if (absys_path_isds(*pathiter)){
                base = i+1;
            }
            ++ i;
            ++ pathiter;
        }
    }
    return path->data + base;
}
