# Modified from peanut-gb SDL example
NAME		:= suiCune

# Default compiler options for GCC and Clang
CC	:= cc
OBJEXT	:= o
RM	:= rm -f
EXEOUT	:= -o
EXTRA_CFLAGS := -std=c99 -Wall -Wextra -Wno-unused-label -Og -g3
EXE	:= $(NAME)
STATIC := yes

TARGET := $(NAME)
SRCS   := tools/emu/peanut_sdl.c tools/emu/minigb_apu/minigb_apu.c \
	$(wildcard home/*.c) \
	$(wildcard audio/*.c) \
	$(wildcard engine/battle_anims/*.c) \
	$(wildcard engine/gfx/*.c) \
	$(wildcard engine/menus/*.c) \
	$(wildcard engine/overworld/*.c)
#	$(wildcard ../*/*/*/*.c)
CFLAGS += $(shell sdl2-config --cflags)

ifeq ($(STATIC),yes)
	CFLAGS += -static
	LDLIBS += $(shell sdl2-config --static-libs)
else
	LDLIBS += $(shell sdl2-config --libs)
endif

LDLIBS += -lm

# File extension ".exe" is automatically appended on MinGW and MSVC builds, even
# if we don't ask for it.
ifeq ($(OS),Windows_NT)
	EXE := $(NAME).exe
endif

CFLAGS += $(EXTRA_CFLAGS)

OBJS := $(SRCS:.c=.$(OBJEXT))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(EXEOUT)$@ $^ $(LDFLAGS) $(LDLIBS) 

%.obj: %.c
	$(CC) $(CFLAGS) $^

%.res: %.rc
	rc /nologo /DCOMPANY="$(COMPANY)" /DDESCRIPTION="$(DESCRIPTION)" \
		/DLICENSE="$(LICENSE)" /DGIT_VER="$(GIT_VER)" \
		/DNAME="$(NAME)" /DICON_FILE="$(ICON_FILE)" $^

clean:
	$(RM) $(SRCS:.c=.$(OBJEXT)) $(TARGET) \
	$(wildcard home/*.o) \
	$(wildcard audio/*.o) \
	$(wildcard engine/battle_anims/*.o) \
	$(wildcard engine/gfx/*.o) \
	$(wildcard engine/menus/*.o) \
	$(wildcard engine/overworld/*.o)
#	$(wildcard ../*/*/*/*.o)
