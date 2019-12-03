/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbilga <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:29:42 by cbilga            #+#    #+#             */
/*   Updated: 2018/11/15 10:18:02 by cbilga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char*))
{
	if ((s != NULL) && (f != NULL))
	{
		while (*s)
		{
			f(s);
			s++;
		}
	}
}