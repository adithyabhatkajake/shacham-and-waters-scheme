CC = gcc
CFLAGS = 
INCLUDES = -I ../include/
LIBS = -lrs -lgmp -lpbc

SRCS := reed-solomon.c file_block.c file_encode.c write_test.c
OBJS := $(SRCS:.c=.o)

.PHONY: all

all: $(OBJS) $(SRCS) makefile

reed-solomon.o: reed-solomon.c ../lib/logging.c
	@echo "==========================="
	@echo "Running Reed Solomon Tests:"
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $^ -o $@
	./$@ 
	@echo "Reed Solomon Tests Passed"
	@echo "==========================="

file_block.o: ../lib/handlefile.o file_block.c ../lib/logging.c
	@echo "==========================="
	@echo "Running Handle File Tests:"
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) $^ -o $@
	./$@ ../LICENSE
	@echo "File Handling Tests Passed"
	@echo "==========================="

file_encode.o: ../lib/handlefile.o file_encode.c ../lib/logging.c
	@echo "==========================="
	@echo "Running Encode File Tests:"
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) $^ -o $@ $(LIBS)
	./$@ ../LICENSE
	@echo "==========================="

write_test.o: ../lib/handlefile.o write_test.c ../lib/logging.c
	@echo "==========================="
	@echo "Running File Write Tests:"
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) $^ -o $@ $(LIBS)
	./$@ ../LICENSE
	@echo "==========================="

blstest.o: ../lib/bls.o blstest.c ../lib/logging.c
	@echo "==========================="
	@echo "Running BLS Tests:"
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) $^ -o $@ $(LIBS)
	./$@
	@echo "==========================="

clean: 
	rm -f *.o