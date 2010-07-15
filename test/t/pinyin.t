# vi:filetype=perl

use lib 'lib';
use Test::Nginx::Socket;

#repeat_each(3);

plan tests => repeat_each() * 2 * blocks();

no_long_string();

run_tests();

__DATA__

=== TEST 1: set pinyin
--- config
    location /foo {
        set $foo "aba";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
aba

=== TEST 2: set pinyin
--- config
    location /foo {
        set $foo "中国";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
中国

=== TEST 3: set pinyin
--- config
    location /foo {
        set $foo "你hao";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
nihao

=== TEST 4: set pinyin
--- config
    location /foo {
        set $foo "wo你ta";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
wonita

=== TEST 5: set pinyin
--- config
    location /foo {
        set $foo "wo ta";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
wo ta

=== TEST 6: set pinyin
--- config
    location /foo {
        set $foo "wo　ta";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
wo ta

=== TEST 7: set pinyin
--- config
    location /foo {
        set $foo "西zhimen";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
xizhimen

=== TEST 8: set pinyin TODO
--- config
    location /foo {
        set $foo "renminyin行";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
renminyinxing

=== TEST 9: set pinyin
--- config
    location /foo {
        set $foo "Tian上";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
tianshang

=== TEST 10: set pinyin
--- config
    location /foo {
        set $foo "TIANShang";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
tianshang

=== TEST 11: set pinyin
--- config
    location /foo {
        set $foo "TＩANShang";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
tianshang

=== TEST 12: set pinyin
--- config
    location /foo {
        set $foo "西ｚｈｉMen";
        set_pinyin_to_normal $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
xizhimen
