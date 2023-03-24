MAKE_DIR=.

SRC_DIR=$(MAKE_DIR)/src/

OUTPUT_DIR=$(MAKE_DIR)/bin/

FFMPEG_INCLUDE=-I $(MAKE_DIR)/include

FFMPEG_LIB=-L $(MAKE_DIR)/lib -lavformat -lavfilter -lavcodec -lavutil -lpthread

CFLAGS = -g -Wall

CC=gcc

SRC=$(wildcard $(SRC_DIR)*.c)
BIN=$(OUTPUT_DIR)$(SRC:$(SRC_DIR)%.c=%)

all: ${BIN}

${BIN}:$(SRC)
	${CC} ${CFLAGS} $^ ${FFMPEG_INCLUDE} ${FFMPEG_LIB} -o $@

clean:
	rm -rf ${BIN}

.PHONY: all clean
