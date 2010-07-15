#ifndef GPERF_PINYIN_LOOKUP_H
#define GPERF_PINYIN_LOOKUP_H

typedef struct gperf_pinyin_pair{
    char *word;
    size_t word_size;
    char *pinyin;
    size_t pinyin_size;
} gperf_pinyin_pair;

const struct gperf_pinyin_pair *
gperf_pinyin_lookup (register const char *str, register unsigned int len);

#endif
