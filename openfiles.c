#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

struct linux_dirent {
	long           d_ino;
	off_t          d_off;
	unsigned short d_reclen;
	char           d_name[];
};

void openfiles(int c) {
	int fd = open("tmp", O_CREAT | O_RDWR, 0666);
	int f = 0;
	for (int i = 1; i < c; ++i) {
		f = dup(fd);
	}
	c = f;
}

int main() {
#ifdef THOUSANDFILES
	openfiles(200);
#endif

	int c = 0;
	for (int _ = 0; _ < 10000; ++_) {

#ifdef FCNTL
	int i;

#	ifdef DUPTRICK
	i = dup(0);
	close(i);
#	else // DUPTRICK
	i = 0;
#	endif // DUPTRICK

	struct rlimit rlim;
	getrlimit(RLIMIT_NOFILE, &rlim);
	int limit = (int) rlim.rlim_cur;
	c += i;
	while (i < limit) {
		if (-1 != fcntl(i, F_GETFD)) ++c;
		++i;
	}
#else // FCNTL
	int fd = open("/proc/self/fd", O_DIRECTORY | O_RDONLY);
	void * buf = malloc(1024*1024);
	int nread;
	while ((nread = syscall(SYS_getdents, fd, buf, 1024*1024))) {
		int bpos = 0;
		while (bpos < nread) {
			struct linux_dirent * d = (struct linux_dirent *) (buf + bpos);
			bpos += d->d_reclen;
			++c;
		}
	}
	c -= 3;
	free(buf);
	close(fd);
#endif // FCNTL

	}
	printf("%d\n", c);
	return 0;
}
// vim:set sw=4 ts=4 sts=4:
