/* 10c.c */

/* #include <stdio.h> */
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <ncurses.h>
#include <signal.h>
#include <locale.h>
#include <time.h>

#define RED		1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define WHITE		7
#define GREY		8
#define BR_RED		9
#define BR_GREEN	10
#define BR_YELLOW	11
#define BR_BLUE		12
#define BR_MAGENTA	13
#define BR_CYAN		14
#define BR_WHITE	15
#define BRIGHT		8

#define DELAY_MAX 1000
#define DELAY_DEF 50

int bgcolor = -1;
int delay = DELAY_DEF;
int color_flag = 0;
int windy_flag = 0;
int unicode_flag = 0;

/* unicode */
char *stra_box = "\xE2\x95\xB1";	/* &#9585 box drawings diagonal */
char *strb_box = "\xE2\x95\xB2";	/* &#9586 box drawings diagonal */
char *stra_windy = "\xCC\xB8";		/* &#824 combining long solidus overlay */
char *strb_windy = "\xDC\xA2";		/* &#1826 Syriac Letter Nun */

void quit() {
	endwin();
	exit(0);
}

void draw (char *stra, char *strb) {
	for (int y = 0; y < LINES; y++) {
		for (int x = 0; x < COLS; x++) {
			int r = random() % 2;

			if (color_flag == 1) {
				attr_on(COLOR_PAIR(random()%15), NULL);
			}

			if (r == 0) {
				if (unicode_flag == 1) {
					mvaddstr(y, x, stra);
				} else {
					mvaddch(y, x, '/');
				}
			} else {
				if (unicode_flag == 1) {
					mvaddstr(y, x, strb);
				} else {
					mvaddch(y, x, '\\');
				}
			}
		}
	}
}

void init_colors() {
	if (color_flag < 1 || !has_colors() || !can_change_color()) {
		color_flag = 0;
		return;
	}

	if (has_colors()) {
		start_color();
		use_default_colors();

		/* 15 colors */
		init_pair(RED, COLOR_RED, bgcolor);
		init_pair(GREEN, COLOR_GREEN, bgcolor);
		init_pair(YELLOW, COLOR_YELLOW, bgcolor);
		init_pair(BLUE, COLOR_BLUE, bgcolor);
		init_pair(MAGENTA, COLOR_MAGENTA, bgcolor);
		init_pair(CYAN, COLOR_CYAN, bgcolor);
		init_pair(WHITE, COLOR_WHITE, bgcolor);
		init_pair(GREY, bgcolor + BRIGHT, bgcolor);
		init_pair(BR_RED, COLOR_RED + BRIGHT, bgcolor);
		init_pair(BR_GREEN, COLOR_GREEN + BRIGHT, bgcolor);
		init_pair(BR_YELLOW, COLOR_YELLOW + BRIGHT, bgcolor);
		init_pair(BR_BLUE, COLOR_BLUE + BRIGHT, bgcolor);
		init_pair(BR_MAGENTA, COLOR_MAGENTA + BRIGHT, bgcolor);
		init_pair(BR_CYAN, COLOR_CYAN + BRIGHT, bgcolor);
		init_pair(BR_WHITE, COLOR_WHITE + BRIGHT, bgcolor);
	}

	use_default_colors();
	bkgd(' ' | COLOR_PAIR(1));
}

void resize_win(int sig) {
	endwin();
	refresh();
}

int main (int argc, char *argv[]) {
	int opt, busy;
	time_t t;
	char *strap, *strbp;

	strap = stra_box;
	strbp = strb_box;

	signal(SIGWINCH, resize_win);

	/* init rand */
	srandom(time(&t));

	while ((opt = getopt(argc, argv, ":Bbcd:uw")) != -1) {
		switch (opt) {
			case 'B':
				bgcolor = 16;
				break;
			case 'b':
				bgcolor = 0;
				break;
			case 'c':
				color_flag = 1;
				break;
			case 'd':
				delay = atoi(optarg);
				if (delay < 0 || delay > DELAY_MAX || !isdigit(*optarg)) {
				    delay = DELAY_DEF;
				}
				break;
			case 'u':
				unicode_flag = 1;
				break;
			case 'w':
				unicode_flag = 1;
				windy_flag = 1;
				strap = stra_windy;
				strbp = strb_windy;
				break;
			default:
				printf("usage: %s [-Bbcuw] [-d 1..%i] \n", argv[0], DELAY_MAX);
				exit(1);
		}
	}

	setlocale(LC_ALL, "");
	initscr();
	noecho();
	curs_set(0);
	timeout(delay);
	keypad(stdscr, TRUE);
	/* leaveok(stdscr, TRUE); */

	init_colors();

	busy = 1;

	while (busy) {
		switch (getch()) {
			case EOF:
			case KEY_RESIZE:
				break;
			default:
				busy = 0;
				break;
		}

		draw(strap, strbp);
	}

	quit();
	return 0;
}
