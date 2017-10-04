CC=gcc
CFLAGS=-lcrypto -g

SRC_DEMO_FILE=cryptoDemo.c
SRC_ENC_FILE=encfile.c

all: encfile demo

encfile: ${SRC_ENC_FILE}
	${CC} ${SRC_ENC_FILE} -o encfile ${CFLAGS}

demo: ${SRC_DEMO}
	${CC} ${SRC_DEMO_FILE} -o cryptoDemo ${CFLAGS}

.PHONY:
clean:
	-rm cryptoDemo
	-rm encfile
