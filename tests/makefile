CC = gcc
CFLAGS = 
INCLUDES = -I ../include/
LIBS = -lrs

SRCS := reed-solomon.c file_block.c
OBJS := $(SRCS:.c=.o)

.PHONY: all

all: $(OBJS) $(SRCS) makefile

reed-solomon.o: reed-solomon.c
	@echo "==========================="
	@echo "Running Reed Solomon Tests:"
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $< -o $@
	./$@ 
	@echo "Reed Solomon Tests Passed"
	@echo "==========================="

file_block.o: ../lib/handlefile.o file_block.c
	@echo "==========================="
	@echo "Running Handle File Tests:"
	$(CC) $(FLAGS) $(INCLUDES) $(LIBS) file_block.c ../lib/handlefile.o -o $@
	./$@ ../LICENSE
	@echo "File Handling Tests Passed"
	@echo "==========================="
clean: 
	rm -f *.o