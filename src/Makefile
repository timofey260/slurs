
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

# WINDOWS SLURS BUILD FLAGS
# WINRAYLIBDIR ?= ../raylib-5.5_win64_mingw-w64/
# WINFLAGS ?= -I $(WINRAYLIBDIR)include -L $(WINRAYLIBDIR)lib -lraylib -lgdi32 -lwinmm -lopengl32 -luser32 -lkernel32 -lmsvcrt -lshell32

all: $(RAYLIBDIR)libraylib.a debug

git: $(RAYLIBDIR) $(RRESDIR)

$(RAYLIBDIR):
	git clone https://github.com/raysan5/raylib ../raylib

$(RAYLIBDIR)libraylib.a rl: $(RAYLIBDIR)
	make -C $(RAYLIBDIR) $(RAYLIBBUILDFLAGS)

test: release
	gcc $(DEBUG_FLAGS) main.c -L $(OUTDIR) -lslurs $(FLAGS) -o $(HOMEDIR)app.test

release $(OUTDIR)libslurs.a: release-objects link

release-objects: $(RAYLIBDIR)libraylib.a
	gcc $(RELEASE_FLAGS) $(FILES) -c $(FLAGS)

debug: debug-objects link

debug-objects: $(RAYLIBDIR)libraylib.a
	gcc $(DEBUG_FLAGS) $(FILES) -c $(FLAGS)

link: $(OUTDIR)libslurs.a
	mkdir -p $(OBJDIR)
	mkdir -p $(OUTDIR)
	mv -f $(SRCDIR)*.o $(OBJDIR)
	rm -f $(OBJDIR)main.o
	ar rcs $(OUTDIR)libslurs.a $(OBJDIR)*.o

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
