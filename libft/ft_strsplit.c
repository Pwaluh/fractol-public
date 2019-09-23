/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judrion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:11:58 by judrion           #+#    #+#             */
/*   Updated: 2019/09/23 23:17:53 by judrion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int			is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\0' || c == '\r')
		return (1);
	return (0);
}

static char			*copy(char *str, int i)
{
	char	*output;
	int		j;

	j = 0;
	output = (char*)malloc(sizeof(char) * (i + 1));
	if (output == NULL)
		return (output);
	while (j < i)
	{
		output[j] = str[j];
		j = j + 1;
	}
	return (output);
}

static int			count_word(char *str)
{
	int		j;

	j = 0;
	while (*str)
	{
		if (is_whitespace(*str) == 1 && is_whitespace(*(str - 1)) == 0)
			j = j + 1;
		str++;
	}
	if (is_whitespace(*str) == 1 && is_whitespace(*(str - 1)) == 0)
		j = j + 1;
	return (j);
}

static void			populate_tab(char **tab, char *str)
{
	int		i;
	int		j;

	while (*str)
	{
		if (is_whitespace(*str) == 0)
			i = i + 1;
		if (is_whitespace(*str) == 1 && is_whitespace(*(str - 1)) == 0)
		{
			tab[j] = copy(str - i, i);
			j = j + 1;
			i = 0;
		}
		str++;
	}
	if (is_whitespace(*str) == 1 && is_whitespace(*(str - 1)) == 0)
		tab[j] = copy(str - i, i);
}

char				**ft_split(char *str)
{
	char	**tab;
	char	*tmp;
	int		nb_mot;

	if (*str == '\0')
	{
		tab = (char**)malloc(sizeof(char*) * 1);
		*tab = NULL;
		return (tab);
	}
	tmp = str;
	nb_mot = count_word(str);
	tab = (char**)malloc(sizeof(char*) * (nb_mot + 1));
	if (tab == NULL)
		return (tab);
	str = tmp;
	populate_tab(tab, str);
	tab[nb_mot] = NULL;
	return (tab);
}
