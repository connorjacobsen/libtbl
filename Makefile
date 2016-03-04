CC = cc
CFLAGS = -Wall
OBJS = .o

llist_test: llist.o test/llist_test.o
		$(CC) $(CFLAGS) -o $@ llist.o test/llist_test.o
		./llist_test

tbl_test: tbl.o test/tbl_test.o llist.o
		$(CC) $(CFLAGS) -o $@ tbl.o test/tbl_test.o llist.o
		./tbl_test

.PHONY: clean
clean:
		rm -rf *.o test/*.o
		rm -rf llist_test tbl_test

