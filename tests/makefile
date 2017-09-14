CC = gcc
CFLAGS = 
INCLUDES = -I ../include/
LIBS = -lrs -lgmp -lpbc

SRCS := reed-solomon.c file_block.c file_encode.c write_test.c \
		log_tests.c sha2_tests.c
OBJS := $(SRCS:.c=.o)

.PHONY: all

all: $(OBJS) $(SRCS) makefile

reed-solomon.o: reed-solomon.c ../lib/logging.c
	@echo -e "Running Reed Solomon Tests:\n"
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ 
	@echo "Reed Solomon Tests Passed"
	@echo ""

file_block.o: ../lib/handlefile.o file_block.c ../lib/logging.c
	@echo -e "Running Handle File Tests:\n"
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ ../LICENSE
	@echo "File Handling Tests Passed"
	@echo ""

file_encode.o: ../lib/handlefile.o file_encode.c ../lib/logging.c
	@echo -e "Running Encode File Tests:\n"
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ ../LICENSE
	@echo ""

write_test.o: ../lib/handlefile.o write_test.c ../lib/logging.c
	@echo -e "Running File Write Tests:\n"
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@ ../LICENSE
	@echo ""

blstest.o: ../lib/bls.o blstest.c ../lib/logging.c
	@echo -e "Running BLS Tests:\n"
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@
	@echo ""

log_tests.o: ../lib/logging.o log_tests.c
	@echo -e "Running Logger Tests:\n"
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@
	@echo ""

sha2_tests.o: ../lib/sha2.o sha2_tests.c
	@echo -e "Running SHA256 Hashing Tests:\n"
	@$(CC) $(FLAGS) $(INCLUDES) $^ -o $@ $(LIBS)
	@./$@
	@echo ""

clean: 
	rm -f *.o