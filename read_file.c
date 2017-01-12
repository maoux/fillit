/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:56:05 by heynard           #+#    #+#             */
/*   Updated: 2017/01/12 21:35:24 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static unsigned short int	check_buffer(char *buffer)
{
	unsigned short int		piece;
	int						position;
	int						i;

	piece = 0x0000;
	position = 0;
	i = 0;
	if (buffer[0] == '\n' || (buffer[20] != '\n' && buffer[20] != '\0'))
		return (0);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '#')
			piece = piece | (0x8000 >> position);
		if (buffer[i] != '\n' && buffer[i] != '.' && buffer[i] != '#')
			return (0);
		if (buffer[i] != '\n')
			position++;
		i++;
	}
	return (piece);
}

static int					set_tab(int fd, unsigned short int *tab, int *s)
{
	char					*line;
	unsigned short int		tmp;
	int						gnl;

	line = ft_strnew(22);
	while ((gnl = read(fd, line, 21)) > 0)
	{
		line[gnl] = '\0';
		if ((tmp = check_buffer(line)) != 0)
		{
			ft_bzero(line, 22);
			tab[*s] = tmp;
			*s += 1;
		}
		else
			return (-1);
	}
	free(line);
	if (gnl < 0)
		return (-1);
	return (1);
}

t_env						*read_file(const char *file_name)
{
	t_env					*env;
	unsigned short int		*tab;
	int						fd;
	int						size;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		error();
	if ((env = malloc(sizeof(t_env))) == NULL)
		error();
	tab = (unsigned short int *)malloc(sizeof(unsigned short int) * 26);
	if (tab == NULL)
		error();
	size = 0;
	if (set_tab(fd, tab, &size) < 0)
		error();
	env->tab = tab;
	env->size = (unsigned char)size;
	if (close(fd) < 0)
		error();
	return (env);
}
