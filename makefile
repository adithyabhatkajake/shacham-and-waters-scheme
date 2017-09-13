CC = gcc
CFLAGS = -g
INCLUDES = -I include/
LIBS = -lrs -lgmp -pbc

LIB_DIR   := lib
LIB_SRCS  := handlefile.c bls.c
LIB_OBJS  := $(addprefix $(LIB_DIR)/, $(LIB_SRCS:.c=.o))

.PHONY: all
all: libs

tests: $(LIB_OBJS)
	make -C tests/

libs: $(LIB_OBJS)

$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

print-%:
	@echo '$*=$($*)'

clean: 
	$(RM) $(LIB_DIR)/*.o
	make -C tests/ clean
