CC = gcc
CFLAGS = 
INCLUDES = -I ../include/
LIBS = -lrs -lgmp -lpbc

SRCS := reed-solomon.c 	file_block.c	file_encode.c 	write_test.c 	\
		log_tests.c 	sha2_tests.c	blstest.c		audit_tests.c	\
		file_elem.c		hmac_test.c		
OBJS := $(SRCS:.c=.o)

.PHONY: clean

VPATH = ../lib

all: $(OBJS) $(SRCS) makefile

reed-solomon.o: 	reed-solomon.c logging.c
file_block.o: 		handlefile.c file_block.c logging.c
file_encode.o: 		handlefile.c file_encode.c logging.c
write_test.o: 		handlefile.c write_test.c logging.c
log_tests.o: 		logging.c log_tests.c
sha2_tests.o: 		sha256.c print-utils.c sha2_tests.c
blstest.o: 			bls.c blstest.c logging.c
audit_tests.o:		audit_tests.c handlefile.c audit.c logging.c print-utils.c bls.c
file_elem.o:		file_elem.c bls.c logging.c handlefile.c
hmac_test.o:		hmac_test.c hmac-sha256.c sha256.c print-utils.c

$(OBJS) :
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ ../LICENSE

clean: 
	rm -f *.o