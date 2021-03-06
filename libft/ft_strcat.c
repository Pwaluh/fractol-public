/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 19:04:10 by judrion           #+#    #+#             */
/*   Updated: 2018/11/28 11:55:37 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, char *s2)
{
	char	*end_s1;

	end_s1 = ft_strchr(s1, '\0');
	ft_memcpy(end_s1, s2, ft_strlen(s2) + 1);
	return (s1);
}
