/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:36:25 by heynard           #+#    #+#             */
/*   Updated: 2016/11/18 19:12:08 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char		*ft_strchr(const char *s, int c)
{
	if (*s == (char)c)
		return ((char *)s);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s += 1;
		if (*s == (char)c)
			return ((char *)s);
	}
	return (NULL);
}
