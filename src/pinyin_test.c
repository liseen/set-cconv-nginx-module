#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pinyin_lookup.h"

char * escape_str(char *dst, char *src, size_t len)
{
    int all_chinese = 1;
    int all_pinyin = 1;
    const struct pinyin_map * pmap = NULL;
    size_t i;
    size_t dst_size = 0;

    if (len <=  3) {
        strncpy(dst, src, len);
        return dst + len;
    }

    for (i = 0; i <= len; i++) {
        char c = *(src+i);
        if (isspace(c)) {
        } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            all_chinese = 0;
        } else {
            all_pinyin = 0;
        }
    }

    if (all_pinyin || all_chinese) {
        strncpy(dst, src, len);
        return dst + len;
    }

    for (i = 0; i <= len; i++) {
        pmap = set_pinyin_lookup(src + i, 3);
        if (pmap != NULL) {
            strncpy(dst + dst_size, pmap->pinyin, pmap->pinyin_size);
            i = i + 2;
            dst_size += pmap->pinyin_size;
        } else {
            dst[dst_size++] = *(src + i);
        }
    }
}

int main()
{
    char *str = "你好aad";
    char buf[100];
    int len;
    memset(buf, 0, 100);
    len = strlen(str);
    escape_str(buf, str, len);
    printf("%s\n", buf);
    return 0;
}


