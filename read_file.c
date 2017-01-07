/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:56:05 by heynard           #+#    #+#             */
/*   Updated: 2017/01/07 20:02:36 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static short int	set_piece(char *line)
{
	short int		piece;
	int				i;

	i = 0;
	piece = 0x0000;
	while (line[i] != '\0')
	{
		if (line[i] != '.' && line[i] != '#')
			error();
		if (line[i] == '#')
			piece = piece | (1 << i);
		i++;
	}
//	if (check_piece(piece) < 0)
//		error();
	return (piece);
}
static short int	*set_tab(int fd, short int *tab, int *s)
{
	char			**line;
	char			*buf;
	int				nbc;
	int				test;

	test = 0;
	buf = NULL;
	while ((nbc = get_next_line(fd, line)) > 0 || test == 1)
	{
		if (nbc == 0)
			test = 0;
		if (ft_strequ(*line, "\n"))
		{
			tab[*s++] = set_piece(buf);
			free(buf);
			buf = NULL;
		}
		else
		{
			*line[nbc] = '\0';
			if (buf == NULL)
				buf = ft_strdup(*line);
			else
				buf = ft_strjoin(buf, *line);
		}
	}
	tab[*s++] = set_piece(buf);
	return (tab);
}

t_env				*read_file(const char *file_name)
{
	t_env			*env;
	short int		*tab;
	int				fd;
	int				size;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		error();
	if ((env = malloc(sizeof(t_env))) == NULL)
		error();
	size = 0;
	if ((tab = (short int *)malloc(26 * sizeof(short int))) == NULL)
		error();
	tab = set_tab(fd, tab, &size);
	env->tab = tab;
	env->size = (unsigned char)size;
	if (close(fd) < 0)
		error();
	return (env);
}
