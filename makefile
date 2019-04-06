TARGET = simple-lisp
CC = gcc

SRC = lisp.c prompt.c sl_decimal.c sl_list.c sl_object.c 
OBJ = $(patsubst %.c,%.o, $(SRC))

CFLAGS = -O0 -g -Wall
INC = -I. 
LIBS = -ledit

# deps
DEPS := $(patsubst %.c,%.d, $(C_SOURCES))
sinclude $(DEPS)	

.PHONY:all clean
all:$(TARGET)
$(TARGET):$(DEPS) $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)  $(LIBS)

$(OBJ): %.o: %.c
	$(CC) -o $@  -c $< $(INC) $(CFLAGS)

$(DEPS):%.d:%.c
	$(CC) -MM $< $(INC) > $@ 

#######################################
# clean up
#######################################

clean:
	-rm  $(DEPS) $(OBJ) $(TARGET) 
