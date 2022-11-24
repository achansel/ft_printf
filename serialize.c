/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:36:06 by achansel          #+#    #+#             */
/*   Updated: 2022/09/06 14:36:56 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

char	*serialize_char(const char c, t_conv_mods *m)
{
	char	*ret;

	(void) m;
	ret = malloc(2);
	ret[0] = c;
	ret[1] = 0;
	return (ret);
}

char	*serialize_string(const char *s, t_conv_mods *m)
{
	if (!s)
	{
		if (m->precision >= 0)
			return (ft_strndup("(null)", m->precision));
		else
			return (ft_strdup("(null)"));
	}
	if (m->precision < 0)
		return (ft_strdup(s));
	else
		return (ft_strndup(s, m->precision));
}

char	*serialize_int(const int i, t_conv_mods *m)
{
	if (i == 0 && m->precision == 0)
		return (ft_strdup(""));
	if (m->precision >= 0)
		return (printf_ntoa_base((uint64_t)(i), i < 0, "0123456789",
			m->precision));
	else if (m->width >= 0 && m->zero_padded)
		return (printf_ntoa_base((uint64_t)(i), i < 0, "0123456789",
			m->width
			- (i < 0 || mod_should_leave_space(m, i < 0, 'i')
				|| mod_should_force_sign(m, i < 0, 'i'))));
	else
		return (printf_ntoa_base((uint64_t)(i), i < 0, "0123456789", 0));
}

char	*serialize_uint(const unsigned int u, t_conv_mods *m)
{
	if (u == 0 && m->precision == 0)
		return (ft_strdup(""));
	if (m->precision >= 0)
		return (printf_ntoa_base((uint64_t)(u), false, "0123456789",
			m->precision));
	else if (m->width >= 0 && m->zero_padded)
		return (printf_ntoa_base((uint64_t)(u), false, "0123456789",
			m->width));
	else
		return (printf_ntoa_base((uint64_t)(u), false, "0123456789",
			0));
}

char	*serialize_hex(const uint64_t u, t_conv_mods *m, bool force_a, bool up)
{
	char		*ret;
	const char	*base;
	char		*tmp;

	if (u == 0 && m->precision == 0)
		return (ft_strdup(""));
	base = "0123456789ABCDEF";
	if (!up)
		base = "0123456789abcdef";
	if (m->precision >= 0)
		ret = printf_ntoa_base((uint64_t)(u), false, base, m->precision);
	else if (m->width >= 0 && m->zero_padded)
		ret = printf_ntoa_base((uint64_t)(u), false, base,
				m->width
				- (mod_should_alternative_form(m, 'x', u)
					|| force_a));
	else
		ret = printf_ntoa_base((uint64_t)(u), false, base, 0);
	if (force_a)
	{
		tmp = ret;
		ret = ft_strjoin("0x", tmp);
		free(tmp);
	}
	return (ret);
}
