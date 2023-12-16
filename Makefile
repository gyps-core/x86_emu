TARGET = px86
SRCS = $(wildcard *.c)
OBJS = $(SRCS: .c=.o)
#Z_TOOLS = ./tolset_p86/z_tools

CC = gcc
CFLAGS += -m32 -Wall -g

.all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -m32 -o $@ $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)