/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:34:22 by achansel          #+#    #+#             */
/*   Updated: 2022/09/06 14:35:16 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

bool	is_hex_conversion(char c)
{
	return (c == 'x' || c == 'X');
}

bool	is_unsigned_conversion(char c)
{
	return (is_hex_conversion(c) || c == 'u');
}

bool	is_numerical_conversion(char c)
{
	return (is_unsigned_conversion(c) || c == 'd' || c == 'i');
}

bool	is_conversion_letter(const char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| is_numerical_conversion(c) || c == '%');
}
