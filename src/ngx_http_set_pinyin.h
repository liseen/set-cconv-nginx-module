#ifndef NGX_SET_PINYIN
#define NGX_SET_PINYIN

#include <ngx_core.h>
#include <ngx_config.h>
#include <ngx_http.h>

ngx_int_t ngx_http_set_pinyin_to_normal(ngx_http_request_t *r, ngx_str_t *res, ngx_http_variable_value_t *v);

uintptr_t ngx_http_set_pinyin_escape_to_normal(u_char *dst, size_t *len, u_char *src, size_t size);

#endif /* NGX_SET_PINYIN */
