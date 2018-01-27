PROG = zebra

PMK = version.h
PCLEAN = version_clean

CFLAGS  += -DMAKELIB -g -Wall

include $(MKDIR)/mklib


VERSION  = 1
REVISE   = 0
BUILD    = $(shell git log | grep -cE 'Author:.*<.*@.*>')
BUILDSHA = $(shell git rev-parse --short HEAD)
PROMGRAM = $(shell cat $(SRCDIR)/PROGRAM)
PLATFORM_VERSION = "$(VERSION)$(if $(REVISE),.$(REVISE)$(if $(BUILD),.$(BUILD)$(if $(BUILDSHA),.$(BUILDSHA))))"
TIME     = $(shell date)

version.h:
	@echo "$(PROMGRAM):: Compile time: ${TIME}"
	@echo "$(PROMGRAM):: Current platform version: ${PLATFORM_VERSION}"
	@echo "#ifndef __VERSION_H__" > ./version.h
	@echo "#define __VERSION_H__" >> ./version.h
	@echo "#define QUAGGA_PROGNAME \"$(PROMGRAM)\" " >> ./version.h
	@echo "#define QUAGGA_COMPILE_TIME \"$(TIME)\"" >> ./version.h
	@echo "#define QUAGGA_VERSION \"$(PLATFORM_VERSION)\"" >> ./version.h
	@echo "#endif /* end of __VERSION_H__ */" >> ./version.h

version_clean:
	@rm -rf version.h
