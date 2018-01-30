PROG    = luna

ECFLAGS = -g -O0  -I. #-Werror

ELDFLAGS = -L$(SRCDIR)/libs/http_parser/http_parser \
           -L$(SRCDIR)/libs/pcre-m \
           -L$(SRCDIR)/libs/zebra \
	   -L$(SRCDIR)/libs/cmdline \
	   -L$(SRCDIR)/libs/boots \
	   -L$(SRCDIR)/libs/pub \
	   -L$(SRCDIR)/itf \
	   -L$(SRCDIR)/pid \
	   -L$(SRCDIR)/fct \
	   -L$(SRCDIR)/acl 

LDLIBS   = -litf -lpid -lfct -lacl \
	   -llunapub -lcmdline -lboots\
	   -lzebra -lhttp_parser -lpcre \
	   -lcrypt -lreadline -lrt -lpcap -lz
	   
include $(MKDIR)/mkapp

