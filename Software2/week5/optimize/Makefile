CC = gcc
CFLAGS = -Wall -g
#CFLAGS = -O2 -DNDEBUG
LDLIBS = -lm
OBJS = main.o func2.o optimize.o

a.out:	$(OBJS)
	$(CC) $(OBJS) $(LDLIBS)

clean:
	rm -f *~ *.o a.out
