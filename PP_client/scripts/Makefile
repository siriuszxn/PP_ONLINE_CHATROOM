CC := gcc
CFLAGS := -Wall -O3
Libs = -lpthread -lsqlite3
Target := client
Source := $(wildcard src/*.c)
Objs := $(patsubst %.c,%.o,$(Source))
Modules += client_main client_thread dis_menu input_check pack_msg rand_ppid
AllObjs := $(addsuffix /src/*.o,$(Modules))

