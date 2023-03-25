MAKE_DIR=.

SRC_DIR=$(MAKE_DIR)/src/

OUTPUT_DIR=$(MAKE_DIR)/bin/

FFMPEG_INCLUDE=$(MAKE_DIR)/include

FFMPEG_LIB=$(MAKE_DIR)/lib

CFLAGS = -g -Wall -I $(FFMPEG_INCLUDE) -L $(FFMPEG_LIB) -lavformat -lavfilter -lavcodec -lavutil -lpthread -luuid

CC=gcc

SRC=$(wildcard $(SRC_DIR)*.c)
BIN=$(OUTPUT_DIR)$(SRC:$(SRC_DIR)%.c=%)

all: ${BIN}

${BIN}:$(SRC)
	${CC} $^ ${CFLAGS} -o $@

clean:
	rm -rf ${BIN}

.PHONY: all clean
