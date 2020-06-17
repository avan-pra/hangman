#include "get_next_line.h"

static void	ft_save(char *s, char *save)
{
	int i;
	int j;
	int k;

	i = 0;
	k = ft_strlen(s);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	s[i] = '\0';
	j = 0;
	i++;
	while (i < k && s[i] != '\0')
	{
		save[j] = s[i];
		i++;
		j++;
	}
	save[j] = '\0';
}

static int	read_line(int fd, char **gnl, char *save, int ret)
{
	char	*tmp;
	char	buf[BUFFER_SIZE + 1];

	while (!(ft_strchr(*gnl, '\n')) && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (-1);
		if (ret > 0)
		{
			buf[ret] = '\0';
			tmp = *gnl;
			*gnl = ft_strjoin(*gnl, buf);
			free(tmp);
		}
	}
	ft_save(*gnl, save);
	if (ret > 0)
		return (1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		*gnl;
	char		*tmp;
	int			ret;
	static char	save[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 0 || !line)
		return (-1);
	if (!(gnl = ft_strnew((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	tmp = gnl;
	if (!(gnl = ft_strjoin(gnl, save)))
		return (-1);
	free(tmp);
	ret = read_line(fd, &gnl, save, 1);
	if (ret < 0)
		return (-1);
	*line = gnl;
	if (ret > 0)
		return (1);
	return (0);
}
