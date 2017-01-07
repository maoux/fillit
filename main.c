/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:45:23 by agermain          #+#    #+#             */
/*   Updated: 2017/01/07 18:11:17 by agermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int main()
{
	t_env *pieces;

	pieces = read_file("");
	for(int i = 0; i < pieces->size; i++){
        printf("%s\n", byte_to_binary(pieces->tab[i]));
	}
}
