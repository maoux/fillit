/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:42:06 by heynard           #+#    #+#             */
/*   Updated: 2017/01/12 18:06:36 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		error()
{
	ft_putendl("error");
	exit(EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	t_env	*env;

	if (argc != 2)
		error();
	env = read_file(argv[1]);
	if (check_env(env) < 0)
		error();
	//test
	print_pieces(env);
	//
	return (1);
}
