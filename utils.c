/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:26:29 by achansel          #+#    #+#             */
/*   Updated: 2022/09/06 14:33:36 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"
#include <stdio.h>

#define MAX_NUMBER_STRING_LEN (100)

int	ft_strlen(const char *str)
{
	const char	*new;

	new = str;
	while (*new)
		new++;
	return (new - str);
}

static char	*ft_strrev(char *str)
{
	char	tmp;
	char	*end;
	char	*begin;

	begin = str;
	end = str + ft_strlen(str) - 1;
	while (begin < end)
	{
		tmp = *begin;
		*begin++ = *end;
		*end-- = tmp;
	}
	return (str);
}

char	*printf_ntoa_base(uint64_t n, bool neg, const char *base, int digit_w)
{
	char	*ret;
	int		i;

	if (digit_w + 1 > MAX_NUMBER_STRING_LEN)
		ret = malloc(digit_w + 1);
	else
		ret = malloc(MAX_NUMBER_STRING_LEN);
	i = 0;
	if (!ret)
		return (NULL);
	if (neg)
		n = -(int64_t)(n);
	if (!n)
		ret[i++] = base[0];
	while (n != 0)
	{
		ret[i++] = base[n % ft_strlen(base)];
		n /= ft_strlen(base);
	}
	while (i < digit_w)
		ret[i++] = base[0];
	if (neg)
		ret[i++] = '-';
	ret[i] = '\0';
	return (ft_strrev(ret));
}

char	*ft_strdup(const char *str)
{
	char	*new;
	int		i;

	i = -1;
	new = malloc(ft_strlen(str) + 1);
	while (str[++i])
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

char	*ft_strndup(const char *str, int n)
{
	char	*new;
	int		i;

	i = -1;
	if (ft_strlen(str) > n)
		new = malloc(n + 1);
	else
		new = malloc(ft_strlen(str) + 1);
	while (str[++i] && i < n)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}
