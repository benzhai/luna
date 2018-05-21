PROG    = test

ECFLAGS = -g -O0  -I. -I$(SRCDIR)/libs/pcre-m/pcre -I$(SRCDIR)/libs/boots -I$(SRCDIR)/acl -I$(SRCDIR)/fct

ELDFLAGS = -L$(SRCDIR)/libs/http_parser/http_parser \
           -L$(SRCDIR)/libs/pcre-m \
           -L$(SRCDIR)/libs/zebra \
	   -L$(SRCDIR)/libs/cmdline \
	   -L$(SRCDIR)/libs/boots \
	   -L$(SRCDIR)/libs/pub \
	   -L$(SRCDIR)/itf \
	   -L$(SRCDIR)/pid \
	   -L$(SRCDIR)/fct \
	   -L$(SRCDIR)/acl \
	   -L$(SRCDIR)/dpf 

LDLIBS   = -lfct -lacl -litf -ldpf -lpid \
	   -llunapub -lcmdline -lboots\
	   -lzebra -lhttp_parser -lpcre \
	   -lcrypt -lreadline -lrt -lpcap -lz -lcunit
	   
include $(MKDIR)/mkapp
