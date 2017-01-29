/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:45:23 by agermain          #+#    #+#             */
/*   Updated: 2017/01/29 18:52:09 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void        error()
{
    ft_putendl("error");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    const t_pieces   *pieces;

    if (argc != 2)
        error();
	pieces = read_file(argv[1]);
    if (check_env(pieces) < 0)
        error();
	return (find_best_placement(pieces));
}
