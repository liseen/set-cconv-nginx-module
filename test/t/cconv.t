# vi:filetype=perl

use lib 'lib';
use Test::Nginx::Socket;

#repeat_each(3);

plan tests => repeat_each() * 2 * blocks();

no_long_string();

run_tests();

#no_diff();

__DATA__

=== TEST 1: set cconv
--- config
    location /foo {
        set $foo "中國";
        set_cconv_to_simp $foo $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
中国

=== TEST 2: set cconv
--- config
    location /foo {
        set $foo "中國";
        set_cconv_to_simp $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
中国

=== TEST 3: set cconv empty value
--- config
    location /foo {
        set $foo "";
        set_cconv_to_simp $foo;
        echo -n $foo;
    }
--- request
GET /foo
--- response_body

=== TEST 4: set cconv null value
--- config
    location /foo {
        set_cconv_to_simp $foo;
        echo -n $foo;
    }
--- request
GET /foo
--- response_body

=== TEST 5: set cconv to simp 乾
--- config
    location /foo {
        set $foo "乾";
        set_cconv_to_simp $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
乾


=== TEST 6: set cconv to traditional
--- config
    location /foo {
        set $foo "中国";
        set_cconv_to_trad $foo;
        echo $foo;
    }
--- request
GET /foo
--- response_body
中國









