TARGET = flibtest
OBJS = flibtest.o flib.o graphics.o framebuffer.o

INCDIR =
CFLAGS = -G0 -Wall -O2
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = 
LDFLAGS =
LIBS= -lpsppower -lpspgu -lpng -lz -lm -lfreetype

EXTRA_TARGETS = EBOOT.PBP kxploit
PSP_EBOOT_TITLE = Font library demo

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
