CC = gcc
CFLAGS = -Wall -g
#CFLAGS = -O2 -DNDEBUG
LDLIBS = -lm
OBJS = main.o func_ransac.o optimize_ransac.o

a.out:	$(OBJS)
	$(CC) $(OBJS) $(LDLIBS)

clean:
	rm -f *~ *.o a.out
