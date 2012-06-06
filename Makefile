CC=gcc
CFLAGS=-std=gnu99 -O2 -Wall -Wextra

all: fds fds-duptrick-fcntl fds-fcntl fds-thousandfiles fds-thousandfiles-duptrick-fcntl fds-thousandfiles-fcntl

fds: openfiles.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ openfiles.c

fds-duptrick-fcntl: openfiles.c
	$(CC) -DDUPTRICK -DFCNTL $(CFLAGS) $(LDFLAGS) -o $@ openfiles.c

fds-fcntl: openfiles.c
	$(CC) -DFCNTL $(CFLAGS) $(LDFLAGS) -o $@ openfiles.c

fds-thousandfiles: openfiles.c
	$(CC) -DTHOUSANDFILES $(CFLAGS) $(LDFLAGS) -o $@ openfiles.c

fds-thousandfiles-duptrick-fcntl: openfiles.c
	$(CC) -DTHOUSANDFILES -DDUPTRICK -DFCNTL $(CFLAGS) $(LDFLAGS) -o $@ openfiles.c

fds-thousandfiles-fcntl: openfiles.c
	$(CC) -DTHOUSANDFILES -DFCNTL $(CFLAGS) $(LDFLAGS) -o $@ openfiles.c

clean: openfiles.c
	$(rm) fds fds-duptrick-fcntl fds-fcntl fds-thousandfiles fds-thousandfiles-duptrick-fcntl fds-thousandfiles-fcntl tmp
