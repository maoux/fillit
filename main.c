/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:45:23 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 22:04:18 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	error(void)
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

int		main(int argc, char **argv)
{
	const t_pieces	*pieces;

	if (argc != 2)
	{
		ft_putstr("Error: missing pieces file\nUsage: ");
		ft_putstr(argv[0]);
		ft_putendl(" \033[4mfilename\033[0m");
		exit(EXIT_FAILURE);
	}
	pieces = read_file(argv[1], 0);
	if (check_env(pieces) < 0)
		error();
	return (find_best_placement(pieces));
}
