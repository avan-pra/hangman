#ifndef HANGMAN_H
# define HANGMAN_H

#include "gnl/get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <termios.h>

typedef struct	s_key
{
	char g[4];
	char d[4];
	char h[4];
	char b[4];
}				t_key;

#endif