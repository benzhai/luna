.PHONY:all

all: libpcre.a

libpcre.a:
	cd pcre && ./configure >> /dev/null
	mkdir pcre/.libs
	cd pcre &&  make >> /dev/null

clean:
	cd pcre &&  make clean >> /dev/null
