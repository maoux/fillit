/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 22:42:16 by heynard           #+#    #+#             */
/*   Updated: 2017/01/29 22:01:05 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int			check_tetris(const t_ushort tetris)
{
	int				i;
	static t_ushort	tetriminos[19] = {0xE200, 0x44C0, 0x8E00, 0xC880,
									0xE800, 0xC440, 0x2E00, 0x88C0,
									0xE400, 0x4C40, 0x4E00, 0x8C80,
									0x6C00, 0x8C40, 0xC600, 0x4C80,
									0xF000, 0x8888, 0xCC00};

	i = 0;
	while (i < 19)
	{
		if (tetriminos[i] == tetris)
			return (1);
		i++;
	}
	return (0);
}

int					check_env(t_pieces_cst env)
{
	int				test;
	int				i;

	i = 0;
	while (i < env->size)
	{
		test = 1;
		while ((env->tab[i] < (t_ushort)0x8000) && test)
		{
			if (!(check_tetris(env->tab[i])))
				env->tab[i] = env->tab[i] << 1;
			else
				test = 0;
		}
		if (check_tetris(env->tab[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}
