#include "hangman.h"

void fill(t_key *key)
{
	key->g[0] = 27;
	key->g[1] = 91;
	key->g[2] = 68;
	key->g[3] = 0;
	key->d[0] = 27;
	key->d[1] = 91;
	key->d[2] = 67;
	key->d[3] = 0;
	key->h[0] = 27;
	key->h[1] = 91;
	key->h[2] = 65;
	key->h[3] = 0;
	key->b[0] = 27;
	key->b[1] = 91;
	key->b[2] = 66;
	key->b[3] = 0;
}

int count_space(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			++j;
		++i;
	}
	return (j);
}

void print_base(char *to_find, char *guess)
{
	int i;
	int len;

	i = 0;
	len = strlen(to_find);
	while (i < len)
	{
		if (to_find[i] == ' ')
			write(1, " ", 1);
		else if (guess[i] != '\0')
			write(1, &guess[i], 1);
		else
			write(1, "_", 1);
		++i;
	}
	write(1, "\n", 1);
}

void set_intera(struct termios *s_set)
{
	tcgetattr(0, s_set);
	s_set->c_lflag &= ~(ICANON | ECHO | ISIG);
	tcsetattr(0, 0, s_set);	
}

int read_char(char *c, t_key keys, int ok_read)
{
	char q;

	if (ok_read == 0)
		write(1, "your guess: ", 12);
	else
		write(1, "error, you can't do that, press enter to validate, your guess: ", 63);
	read(0, c, 1);
	if (*c == 3)
		exit(0);
	if ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z'))
	{
		write(1, c, 1);
		read(0, &q, 1);
		if (q == 3)
			exit(0);
		if (q == '\n')
			return (0);
		else;
		{
			write(1, &keys.g, 3);
			write(1, " ", 1);
			write(1, &keys.g, 3);
			return (1);
		}
	}
	return (1);
}

int str_fill(char *to_find, char *guess, char c)
{
	int len;
	int i;
	int found;

	len = strlen(to_find);
	i = 0;
	found = 1;
	while (i < len)
	{
		if (to_find[i] == c)
		{
			guess[i] = c;
			found = 0;
		}
		++i;
	}
	return (found);
}

void pendax(int number)
{
	char *tmp;

	if (number == 0)
		write(1, "\n\n\n\n\n\n\n\n\n\n\n\n", 12);
	if (number == 1)
		write(1, "\n\n\n\n\n\n\n\n\n\n\n============\n", 24);
	if (number == 2)
		write(1, "\n   ||\n   ||\n   ||\n   ||\n   ||\n   ||\n   ||\n   ||\n   ||\n   ||\n============\n", 74);
	if (number == 3)
		write(1, "\n   ||  /\n   || /\n   ||/\n   ||\n   ||\n   ||\n   ||\n   ||\n  /||\n //||\n============\n", 80);
	if (number == 4)
		write(1, "   ,==========Y===\n   ||  /\n   || /\n   ||/\n   ||\n   ||\n   ||\n   ||\n   ||\n  /||\n //||\n============\n", 98);
	if (number == 5)
		write(1, "   ,==========Y===\n   ||  /      |\n   || /       |\n   ||/\n   ||\n   ||\n   ||\n   ||\n   ||\n  /||\n //||\n============\n", 113);
	if (number == 6)
		write(1, "   ,==========Y===\n   ||  /      |\n   || /       |\n   ||/        O\n   ||\n   ||\n   ||\n   ||\n   ||\n  /||\n //||\n============\n", 122);
	if (number == 7)
		write(1, "   ,==========Y===\n   ||  /      |\n   || /       |\n   ||/        O\n   ||        /|\\\n   ||        /|\n   ||\n   ||\n   ||\n  /||\n //||\n============\n", 143);
}

char *read_word(void)
{
	int fd;
	char *line;

	fd = open("pass.txt", O_RDONLY);
	get_next_line(fd, &line);
	return (line);
}

int main(void)
{
	t_key keys;
	fill(&keys);
	printf("\033[H\033[J\n");
	char *to_find = read_word();
	char *guess = calloc(sizeof(char), strlen(to_find) + 1);
	char c;
	int fail;
	int ok_read = 0;
	struct termios s_set;

	fail = 0;
	set_intera(&s_set);
	str_fill(to_find, guess, ' ');
	while (1)
	{
		pendax(fail);
		if (fail >= 7)
		{
			write(1, "\nle mot etait: ", 15);
			write(1, to_find, strlen(to_find));
			write(1, "\nyou loose\n", 11);
			free(guess);
			free(to_find);
			return (1);
		}
		write(1, keys.b, 3);
		print_base(to_find, guess);
		write(1, keys.b, 3);
		
		while (read_char(&c, keys, ok_read) != 0)
		{
			printf("\033[H\033[J\n");
			pendax(fail);
			write(1, keys.b, 3);
			print_base(to_find, guess);
			write(1, keys.b, 3);
			ok_read = 1;
		}
		ok_read = 0;
		fail = fail + str_fill(to_find, guess, c);
		if (strcmp(guess, to_find) == 0)
		{
			printf("\033[H\033[J\n");
			pendax(fail);
			write(1, keys.b, 3);
			print_base(to_find, guess);
			write(1, "\nle mot etait: ", 15);
			write(1, to_find, strlen(to_find));
			free(guess);
			free(to_find);
			write(1, "\nwell played\n", 13);
			return (0);
		}
		printf("\033[H\033[J\n");
	}
	return (0);
}