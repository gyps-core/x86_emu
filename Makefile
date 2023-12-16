TARGET = px86
OBJS = main.o
#Z_TOOLS = ./tolset_p86/z_tools

CC = gcc
CFLAGS += -m32 -Wall

.PHONY: all
all :
	make $(TARGET)

%.o : %.c Makefile
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS) Makefile
	$(CC) -m32 -o $@ $(OBJS)
