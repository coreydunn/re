CC=      cc
CFLAGS=  -Wfatal-errors
LDFLAGS= -s
OBJS=    main.o vec.o buf.o blist.o term.o
RM=      rm -f

all: re
re: $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
%.o: %.c
	$(CC) -c $^ $(CFLAGS)
create_test: create_test.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)
libcurs.a: term.o
	ar r $@ $^
clean:
	$(RM) $(OBJS) re create_test
