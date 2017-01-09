/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:56:05 by heynard           #+#    #+#             */
/*   Updated: 2017/01/09 23:12:02 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static short int	check_buffer(char *buffer)
{
	short int		piece;
	int				i;

	piece = 0x0000;
	i = 0;
	if (ft_strlen(buffer) == 16)
	{
		while (buffer[i] != '\0')
		{
			if (buffer[i] == '#')
				piece = piece | (0x8000 >> i);
			if (buffer[i] != '.' && buffer[i] != '#')
				error();
			i++;
		}
	}
	return (piece);
}

static void			set_tab(int fd, short int *tab, int *s)
{
	char			*line;
	char			*buffer;
	short int		tmp;
	int				gnl;

	buffer = NULL;
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		buffer = ft_strjoin(buffer, line);
		if ((tmp = check_buffer(buffer)) != 0)
		{
			buffer = NULL;
			tab[*s] = tmp;
			*s += 1;
		}
	}
	free(line);
	free(buffer);
	if (gnl < 0)
		error();
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
	if ((tab = (short int *)malloc(sizeof(short int) * 26)) == NULL)
		error();
	size = 0;
	set_tab(fd, tab, &size);
	env->tab = tab;
	env->size = (unsigned char)size;
	if (close(fd) < 0)
		error();
	return (env);
}
