CC := gcc
CFLAGS := -Wall -O3
Libs = -lpthread -lsqlite3
Target := server
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += rand_ppid server_main server_thread pp_sqlite3
AllObjs := $(addsuffix /src/*.o,$(Modules))

