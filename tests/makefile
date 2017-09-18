CC = gcc
CFLAGS = 
INCLUDES = -I ../include/
LIBS = -lrs -lgmp -lpbc

SRCS := reed-solomon.c file_block.c file_encode.c write_test.c \
		log_tests.c sha2_tests.c blstest.c
OBJS := $(SRCS:.c=.o)

.PHONY: all

VPATH = ../lib

all: $(OBJS) $(SRCS) makefile

reed-solomon.o: reed-solomon.c logging.c
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ 

file_block.o: handlefile.c file_block.c logging.c
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ ../LICENSE

file_encode.o: handlefile.c file_encode.c logging.c
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ ../LICENSE

write_test.o: handlefile.c write_test.c logging.c
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ ../LICENSE

blstest.o: bls.c blstest.c logging.c
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@

log_tests.o: logging.c log_tests.c
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@

sha2_tests.o: sha256.c print-utils.c sha2_tests.c
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@

clean: 
	rm -f *.o