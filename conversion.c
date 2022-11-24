/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:33:51 by achansel          #+#    #+#             */
/*   Updated: 2022/09/06 14:34:02 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

static int	printf_atoi(const char **str)
{
	int	no;
	int	sign;

	sign = 1;
	no = 0;
	if (**str == '.')
		(*str)++;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
	{
		no = no * 10 + **str - '0';
		(*str)++;
	}
	return (no * sign);
}

static t_conv_mods	conv_mods_init(void)
{
	t_conv_mods	ret;

	ret.force_sign = false;
	ret.alternative = false;
	ret.zero_padded = false;
	ret.left_adjusted = false;
	ret.space_before_positive = false;
	ret.precision = -1;
	ret.width = -1;
	return (ret);
}

t_conv_mods	get_conversion_modifiers(const char *str)
{
	t_conv_mods	c;

	c = conv_mods_init();
	while (*str && !is_conversion_letter(*str))
	{
		if (*str == '#')
			c.alternative = ++str != 0;
		else if (*str == '+')
			c.force_sign = ++str != 0;
		else if (*str == '0')
			c.zero_padded = ++str != 0;
		else if (*str == '-')
			c.left_adjusted = ++str != 0;
		else if (*str == ' ')
			c.space_before_positive = ++str != 0;
		else if (*str == '.')
			c.precision = printf_atoi(&str);
		else if (*str >= '1' && *str <= '9')
			c.width = printf_atoi(&str);
	}
	if (c.space_before_positive && c.force_sign)
		c.space_before_positive = false;
	if (c.zero_padded && (c.left_adjusted || c.precision != -1))
		c.zero_padded = false;
	return (c);
}

char	get_conversion_specifier(const char *str)
{
	while (*str && !is_conversion_letter(*str))
		str++;
	return (*str);
}
