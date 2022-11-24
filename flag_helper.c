/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:35:23 by achansel          #+#    #+#             */
/*   Updated: 2022/09/06 14:35:23 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

bool	mod_should_force_sign(t_cv *m, bool neg, const char s)
{
	return (m->force_sign && !neg && !is_unsigned_conversion(s));
}

bool	mod_should_leave_space(t_cv *m, bool n, const char s)
{
	return (m->space_before_positive && !n && !is_unsigned_conversion(s));
}

bool	mod_should_alternative_form(t_cv *m, const char s, const uint64_t u)
{
	return (m->alternative && is_hex_conversion(s) && u != 0);
}

bool	mod_should_left_adjust(t_cv *m, const char spec, int print_len)
{
	return (!(m->zero_padded && is_numerical_conversion(spec))
		&& print_len < m->width && m->left_adjusted);
}

bool	mod_should_right_adjust(t_cv *m, const char spec, int print_len)
{
	return (!(m->zero_padded && is_numerical_conversion(spec))
		&& print_len < m->width && !m->left_adjusted);
}
