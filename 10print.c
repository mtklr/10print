#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {
	int maxy, maxx;
	int r;
	int delay;
	int size;
	int c;

	delay = 500;

	/* unbuffered output */
	setvbuf(stdout, (char *)NULL, _IONBF, 0);

#ifdef PERLINE
	getsize(&maxx, &maxy);
	char line[maxx];

	size='m';
	delay = 0;

	while (1) {
		for (int i=0; i<maxx; i++) {
			r = arc4random_uniform(2);

			if (r == 0) {
				line[i] = '/';
			} else {
				line[i] = '\\';
			}

		}

		line[maxx] = '\0';

		switch (size) {
			case 'l':
				printf("\e#3%s\n", line);
				printf("\e#4%s\n", line);
				break;

			case 'm':
				printf("\e#6%s\n", line);
				break;
			default:
				printf("%s\n", line);
				break;
		}

		/* print per line */
		/* is cursor at colume 1? then flush */
		fflush(stdout);

		usleep(delay);
	}
#else
	while (1) {
		r = arc4random_uniform(2);

		if (r == 0) {
			c='/';
		} else {
			c='\\';
		}

		/* printf("\e#6%c", c); */
		putchar(c);
		usleep(delay);
	}
#endif

	return 0;
}
