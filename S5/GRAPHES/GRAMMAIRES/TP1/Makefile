include Makefile.compilation

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = prog


all : $(AOUT)

prog : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ -lm
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< -lm
clean :
	@rm *.o
cleaner : clean
	@rm $(AOUT)
