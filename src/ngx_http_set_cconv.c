#define DDEBUG 1
#include "ddebug.h"
#include <ndk.h>
#include <cconv.h>

#include "ngx_http_set_cconv.h"

ngx_int_t
ngx_http_set_cconv_to_cn_str(ngx_http_request_t *r,
        ngx_str_t *res, ngx_http_variable_value_t *v)
{
    size_t                   len;
    u_char                  *p;
    size_t                   escape = 0;

    if (v->not_found || v->len == 0) {
        res->data = (u_char *) "";
        res->len = sizeof("") - 1;
        return NGX_OK;
    }

    escape = ngx_http_set_cconv_escape_to_cn_str(NULL, v->data, v->len);
    len = v->len + escape;

    p = ngx_palloc(r->pool, len);
    if (p == NULL) {
        return NGX_ERROR;
    }

    res->data = p;
    res->len = len;

    p = (u_char *) ngx_http_set_cconv_escape_to_cn_str(p, v->data, v->len);

    if (p != res->data + res->len) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                "set_cconv_str: buffer error");
        return NGX_ERROR;
    }

    return NGX_OK;
}

uintptr_t
ngx_http_set_cconv_escape_to_cn_str(u_char *dst, u_char *src, size_t size)
{
    static cconv_t to_cconv = NULL;
    int ret = 0;
    size_t inlen = size;
    size_t outlen = size;

    if (dst == NULL) {
        return (uintptr_t) 0;
    }

    if (to_cconv == NULL) {
        to_cconv = cconv_open(CCONV_CODE_UHS, CCONV_CODE_UTF);
    }

    if (to_cconv == NULL || to_cconv == (cconv_t)(-1)) {
       return (uintptr_t) (-1);
    }

#ifdef FreeBSD
    ret = cconv(to_cconv, (const char**)&src, &inlen, (char**)&dst, &outlen);
#else
    ret = cconv(to_cconv, (char**)&src, &inlen, (char**)&dst, &outlen);
#endif

   if ((int)ret < 0) {
       return (uintptr_t) (-1);
   }

   return (uintptr_t)dst;
}

ngx_int_t
ngx_http_set_cconv_to_tw_str(ngx_http_request_t *r,
        ngx_str_t *res, ngx_http_variable_value_t *v)
{
    size_t                   len;
    u_char                  *p;
    size_t                   escape = 0;

    if (v->not_found || v->len == 0) {
        res->data = (u_char *) "";
        res->len = sizeof("") - 1;
        return NGX_OK;
    }

    escape = ngx_http_set_cconv_escape_to_tw_str(NULL, v->data, v->len);
    len = v->len + escape;

    p = ngx_palloc(r->pool, len);
    if (p == NULL) {
        return NGX_ERROR;
    }

    res->data = p;
    res->len = len;

    p = (u_char *) ngx_http_set_cconv_escape_to_tw_str(p, v->data, v->len);

    if (p != res->data + res->len) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                "set_cconv_str: buffer error");
        return NGX_ERROR;
    }

    return NGX_OK;
}

uintptr_t
ngx_http_set_cconv_escape_to_tw_str(u_char *dst, u_char *src, size_t size)
{
    static cconv_t to_cconv = NULL;
    int ret = 0;
    size_t inlen = size;
    size_t outlen = size;

    if (dst == NULL) {
        return (uintptr_t) 0;
    }

    if (to_cconv == NULL) {
        to_cconv = cconv_open(CCONV_CODE_UHT, CCONV_CODE_UTF);
    }

    if (to_cconv == NULL || to_cconv == (cconv_t)(-1)) {
       return (uintptr_t) (-1);
    }

#ifdef FreeBSD
    ret = cconv(to_cconv, (const char**)&src, &inlen, (char**)&dst, &outlen);
#else
    ret = cconv(to_cconv, (char**)&src, &inlen, (char**)&dst, &outlen);
#endif

   if ((int)ret < 0) {
       return (uintptr_t) (-1);
   }

   return (uintptr_t)dst;
}

