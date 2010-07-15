#define DDEBUG 1
#include "ddebug.h"
#include <ndk.h>
#include <cconv.h>

#include <ctype.h>
#include "gperf_pinyin_lookup.h"
#include "ngx_http_set_pinyin.h"

#define pinyin_tolower(c)      (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)

ngx_int_t
ngx_http_set_pinyin_to_normal(ngx_http_request_t *r,
        ngx_str_t *res, ngx_http_variable_value_t *v)
{
    size_t                   len;
    u_char                  *p;

    if (v->not_found || v->len == 0) {
        res->data = (u_char *) "";
        res->len = sizeof("") - 1;
        return NGX_OK;
    }

    len = 2 * v->len; //max_len pinyin max is 6

    p = ngx_palloc(r->pool, len);
    if (p == NULL) {
        return NGX_ERROR;
    }
    dd("src: %s, %d\n", v->data, (int)v->len);
    res->data = p;
    p = (u_char *) ngx_http_set_pinyin_escape_to_normal(p, &len, v->data, v->len);
    res->len = len;
    dd("res: %s, %d\n", res->data, (int)res->len);

    if (p != res->data + res->len) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                "set_pinyin_to_normal: buffer error");
        return NGX_ERROR;
    }

    return NGX_OK;
}

uintptr_t
ngx_http_set_pinyin_escape_to_normal(u_char *dst, size_t *dst_len, u_char *src, size_t size)
{
    dd("enter escapse_to_normal");
    int all_chinese = 1;
    int all_pinyin = 1;
    const struct gperf_pinyin_pair * pair = NULL;
    size_t i;
    size_t dst_size = 0;
    u_char *tmp;
    u_char c;

    for (i = 0; i < size; i++) {
        c = *(src+i);
        if (isspace(c)) {
        } else if (isascii(c)) {
            all_chinese = 0;
        } else {
            all_pinyin = 0;
        }
    }

    dd("all_pinyin %d or all_chinese %d", all_pinyin, all_chinese);
    if (all_pinyin) {
        for (i = 0 ; i < size; i++) {
            dst[i] = pinyin_tolower(*(src+i));
        }

        *dst_len = size;
        return (uintptr_t)(dst + size);
    }

    if (all_chinese) {
        ngx_memcpy(dst, src, size);
        *dst_len = size;
        return (uintptr_t)(dst + size);
    }

    for (i = 0; i < size; i++) {
        tmp = src +i;
        c = *tmp;
        if ((c >= 'A' && c <= 'Z')) {
            dst[dst_size++] = pinyin_tolower(c);
        } else if (i + 3 <= size  &&
                (pair = gperf_pinyin_lookup((const char*)tmp, 3)) != NULL) {
            ngx_memcpy(dst + dst_size, pair->pinyin, pair->pinyin_size);
            i = i + 2;
            dst_size += pair->pinyin_size;
        } else {
            dst[dst_size++] = c;
        }
    }

    *dst_len = dst_size;
    return (uintptr_t)(dst + dst_size);
}
