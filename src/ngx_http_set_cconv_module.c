#define DDEBUG 0
#include "ddebug.h"

#include <ndk.h>
#include "ngx_http_set_cconv.h"


static  ndk_set_var_t  ngx_http_set_cconv_to_cn_str_filter = {
    NDK_SET_VAR_VALUE,
    ngx_http_set_cconv_to_cn_str,
    1,
    NULL
};

static  ndk_set_var_t  ngx_http_set_cconv_to_tw_str_filter = {
    NDK_SET_VAR_VALUE,
    ngx_http_set_cconv_to_tw_str,
    1,
    NULL
};


static ngx_command_t  ngx_http_set_cconv_commands[] = {
    {
        ngx_string ("set_cconv_to_simp"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_SIF_CONF
            |NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF|NGX_CONF_TAKE12,
        ndk_set_var_value,
        0,
        0,
        &ngx_http_set_cconv_to_cn_str_filter
    },
    {
        ngx_string ("set_cconv_to_trad"),
        NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_SIF_CONF
            |NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF|NGX_CONF_TAKE12,
        ndk_set_var_value,
        0,
        0,
        &ngx_http_set_cconv_to_tw_str_filter
    },

    ngx_null_command
};

static ngx_http_module_t  ngx_http_set_cconv_module_ctx = {
    NULL,                                 /* preconfiguration */
    NULL,                                 /* postconfiguration */

    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    NULL,                                  /* create location configuration */
    NULL,                                  /* merge location configuration */
};


ngx_module_t  ngx_http_set_cconv_module = {
    NGX_MODULE_V1,
    &ngx_http_set_cconv_module_ctx,          /* module context */
    ngx_http_set_cconv_commands,             /* module directives */
    NGX_HTTP_MODULE,                        /* module type */
    NULL,                                   /* init master */
    NULL,                                   /* init module */
    NULL,                                   /* init process */
    NULL,                                   /* init thread */
    NULL,                                   /* exit thread */
    NULL,                                   /* exit process */
    NULL,                                   /* exit master */
    NGX_MODULE_V1_PADDING
};
