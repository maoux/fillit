/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 15:54:05 by agermain          #+#    #+#             */
/*   Updated: 2017/01/07 17:50:47 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static void		create_fd_buffer(int fd, t_gnl *gnl, void **swap, int *counters)
{
	gnl->size++;
	swap[0] = gnl->buffers;
	swap[1] = gnl->fds;
	gnl->fds = (void*)ft_memalloc((gnl->size) * sizeof(int));
	gnl->buffers = (void*)ft_memalloc((gnl->size) * sizeof(char*));
	counters[1] = 0;
	while (counters[1] < counters[0])
	{
		gnl->buffers[counters[1]] = ((char**)swap[0])[counters[1]];
		gnl->fds[counters[1]] = ((int*)swap[1])[counters[1]];
		counters[1]++;
	}
	if (swap[1] != NULL)
	{
		ft_memdel((void**)&swap[1]);
		ft_memdel((void**)&swap[0]);
	}
	gnl->fds[gnl->size - 1] = fd;
	gnl->buffers[gnl->size - 1] = ft_strnew(0);
}

static char		**retrieve_buffer(int fd, t_gnl *gnl)
{
	void	*swap[2];
	int		counters[2];

	counters[0] = 0;
	while (counters[0] < gnl->size && gnl->fds[counters[0]] != fd)
		counters[0]++;
	if (counters[0] == gnl->size)
		create_fd_buffer(fd, gnl, swap, counters);
	return (&(gnl->buffers[counters[0]]));
}

static int		buffer_append(int fd, char **buffer)
{
	char	*new_buffer;
	char	read_buffer[BUFF_SIZE + 1];
	int		bytes_read;

	bytes_read = read(fd, read_buffer, BUFF_SIZE);
	if (bytes_read == -1)
		return (-1);
	read_buffer[bytes_read] = '\0';
	new_buffer = ft_strnew(ft_strlen(*buffer) + bytes_read);
	ft_strcat(new_buffer, *buffer);
	ft_strncat(new_buffer, read_buffer, bytes_read);
	free(*buffer);
	*buffer = new_buffer;
	return (bytes_read);
}

static int		read_buffer_fd(int fd, char **existing_buff, char **line)
{
	char	*last_occurence;
	char	*swap;
	int		line_length;

	while ((last_occurence = ft_strchr(*existing_buff, '\n')) == NULL &&
		(last_occurence = ft_strchr(*existing_buff, '\r')) == NULL &&
		(line_length = buffer_append(fd, existing_buff)) > 0)
		;
	if (line_length == -1)
		return (-1);
	if (last_occurence == NULL)
	{
		*line = ft_strdup(*existing_buff);
		return (ft_strlen(*line) > 0 ? 2 : 0);
	}
	line_length = (int)last_occurence - (int)(*existing_buff);
	*line = ft_strnew(line_length);
	*line = ft_strncpy(*line, *existing_buff, line_length);
	swap = *existing_buff;
	*existing_buff = ft_strnew((ft_strlen(swap) - ft_strlen(*line)) - 1);
	ft_strcpy(*existing_buff, &(swap[ft_strlen(*line) + 1]));
	free(swap);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	fd_buffers = {.size = 0, .buffers = NULL, .fds = NULL};
	char			**buffer;
	int				read_result;
	int				i;

	if (fd < 0)
		return (-1);
	buffer = retrieve_buffer(fd, &fd_buffers);
	if (*buffer == NULL)
		return (0);
	read_result = read_buffer_fd(fd, buffer, line);
	if (read_result == 2)
	{
		i = 0;
		while (fd_buffers.fds[i] != fd)
			i++;
		free(fd_buffers.buffers[i]);
		fd_buffers.buffers[i] = NULL;
		return (1);
	}
	return (read_result);
}
