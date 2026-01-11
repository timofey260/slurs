
HOMEDIR ?= ../
SRCDIR ?= $(HOMEDIR)src/
OBJDIR ?= $(HOMEDIR)obj/
OUTDIR ?= $(HOMEDIR)out/

# RAYLIB BUILD FLAGS
RAYLIBDIR ?= $(HOMEDIR)raylib/src/
RAYLIBBUILDFLAGS ?= PLATFORM=PLATFORM_DESKTOP

# SLURS BUILD FLAGS
FILES ?= $(SRCDIR)*.c
INCLUDEDIRS ?= -I $(RAYLIBDIR) -I $(SRCDIR)include/
LIBDIRS ?= -L $(RAYLIBDIR)
LIBS ?= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# compiler flags to build anything slurs-related
FLAGS ?= -xc $(INCLUDEDIRS) $(LIBDIRS) $(LIBS)
DEBUG_FLAGS ?= -D DEBUG -ggdb
RELEASE_FLAGS ?= -D RELEASE -O2

# TEXT FORMATTING
COLOR_OUTPUT ?= 1
ifeq ($(COLOR_OUTPUT), 1)
COLOR_CHAR ?= \e[1m
else
COLOR_CHAR ?= 
endif
COLOR_RESET ?= \e[0m
LOG_TEXT = "$(COLOR_CHAR)> %A%$(COLOR_RESET)"

# WINDOWS SLURS BUILD FLAGS
# WINRAYLIBDIR ?= ../raylib-5.5_win64_mingw-w64/
# WINFLAGS ?= -I $(WINRAYLIBDIR)include -L $(WINRAYLIBDIR)lib -lraylib -lgdi32 -lwinmm -lopengl32 -luser32 -lkernel32 -lmsvcrt -lshell32

all: $(RAYLIBDIR)libraylib.a debug

git: $(RAYLIBDIR) $(RRESDIR)

$(RAYLIBDIR):
	git clone https://github.com/raysan5/raylib ../raylib

$(RAYLIBDIR)libraylib.a rl: $(RAYLIBDIR)
	@echo -e ${subst %A%,"Building Raylib",$(LOG_TEXT)}
	make -C $(RAYLIBDIR) $(RAYLIBBUILDFLAGS)

test: debug
	@echo -e ${subst %A%,"Building Test app...",$(LOG_TEXT)}
	gcc $(DEBUG_FLAGS) main.c -L $(OUTDIR) -lslurs $(FLAGS) -o $(HOMEDIR)app.test

release: release-objects link

release-objects $(OUTDIR)libslurs.a:
	@echo -e ${subst %A%,"Building Release library...",$(LOG_TEXT)}
	gcc $(RELEASE_FLAGS) $(FILES) -c $(FLAGS)

debug: debug-objects link

debug-objects:
	@echo -e ${subst %A%,"Building Debug Library...",$(LOG_TEXT)}
	gcc $(DEBUG_FLAGS) $(FILES) -c $(FLAGS)

link: $(OUTDIR)libslurs.a
	@echo -e ${subst %A%,"Linking libslurs.a...",$(LOG_TEXT)}
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OUTDIR)
	@mv -f $(SRCDIR)*.o $(OBJDIR)
	@rm -f $(OBJDIR)main.o
	ar rcs $(OUTDIR)libslurs.a $(OBJDIR)*.o
	@echo -e ${subst %A%,"Library linked and should be in $(OUTDIR)",$(LOG_TEXT)}

header:
	@echo -e ${subst %A%,"Generating Single Header file",$(LOG_TEXT)}
	gcc -E -P -fpreprocessed -undef -nostdinc $(SRCDIR)include/slurs.h -I $(RAYLIBDIR) -o $(OUTDIR)slurs.h

# TODO: add Windows support
# windows-debug:
# 	x86_64-w64-mingw32-gcc -D DEBUG $(FILES) $(RRESFLAGS) $(WINFLAGS) -o ../a.exe
# windows-release:
# 	x86_64-w64-mingw32-gcc -D RELEASE $(FILES) $(RRESFLAGS) $(WINFLAGS) -O2 -o ../a.exe

clean:
ifneq ("$(wildcard $(RAYLIBDIR)Makefile)","")
	make -C $(RAYLIBDIR) clean
endif
	rm -rf $(OUTDIR)
	rm -rf $(OBJDIR)

completeclean: clean
	rm -rf ../raylib/
	rm -f $(HOMEDIR)app.test
