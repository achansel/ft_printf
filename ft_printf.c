/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:35:45 by achansel          #+#    #+#             */
/*   Updated: 2022/09/06 14:42:08 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_int.h"

static char	*conversion_serialize(const char sp, t_conv_mods *mods, va_list *ap)
{
	if (sp == 'c')
		return (serialize_char(va_arg(*ap, int), mods));
	else if (sp == 's')
		return (serialize_string(va_arg(*ap, char *), mods));
	else if (sp == 'd' || sp == 'i')
		return (serialize_int(va_arg(*ap, int), mods));
	else if (sp == 'u')
		return (serialize_uint(va_arg(*ap, unsigned int), mods));
	else if (sp == 'x' || sp == 'X')
		return (serialize_hex(va_arg(*ap, uint32_t), mods, false, sp == 'X'));
	else if (sp == 'p')
		return (serialize_hex(va_arg(*ap, uint64_t), mods, true, false));
	else if (sp == '%')
		return (ft_strdup("%"));
	else
		return (ft_strdup("INVALIDCONV"));
}

static int	write_before_conversion(const char s, t_cv *m, const bool n,
		char c)
{
	if (mod_should_force_sign(m, n, s))
		return (write(1, "+", 1));
	else if (mod_should_leave_space(m, n, s))
		return (write(1, " ", 1));
	else if (mod_should_alternative_form(m, s, c - 48) && s == 'X')
		return (write(1, "0X", 2));
	else if (mod_should_alternative_form(m, s, c - 48) && s == 'x')
		return (write(1, "0x", 2));
	return (0);
}

static int	conversion_handler(const char spec, t_conv_mods *m, va_list *ap)
{
	const char	*o;
	int			print_len;
	bool		st;
	int			slen;

	o = conversion_serialize(spec, m, ap);
	st = 0;
	slen = ft_strlen(o);
	if (spec == 'c')
		slen = 1;
	print_len = slen + (int)(mod_should_leave_space(m, o[0] == '-', spec)
			|| mod_should_force_sign(m, o[0] == '-', spec))
		+ (int)(mod_should_alternative_form(m, spec, o[0] - '0') * 2);
	if (mod_should_right_adjust(m, spec, print_len))
		st |= (write_n(1, ' ', m->width - print_len) < 0);
	st |= (write_before_conversion(spec, m, o[0] == '-', o[0]) < 0);
	st |= (write(1, o, slen) < 0);
	if (mod_should_left_adjust(m, spec, print_len))
		st |= (write_n(1, ' ', m->width - print_len) < 0);
	free((void *) o);
	if (st != 0)
		return (-1);
	if (print_len < m->width)
		return (print_len + (m->width - print_len));
	return (print_len);
}

static int	fetch_and_print_conversion(const char **fmt, va_list *ap)
{
	const char	*conv;
	char		c_spec;
	t_conv_mods	c_mods;
	int			c_display_len;

	conv = *fmt;
	c_spec = get_conversion_specifier(conv + 1);
	c_mods = get_conversion_modifiers(conv + 1);
	c_display_len = conversion_handler(c_spec, &c_mods, ap);
	(*fmt)++;
	while (**fmt != c_spec)
		(*fmt)++;
	(*fmt)++;
	return (c_display_len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		count;
	int		len_written;

	count = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
			len_written = fetch_and_print_conversion(&fmt, &ap);
		else
			len_written = write(1, fmt++, 1);
		if (len_written == -1)
		{
			count = -1;
			break ;
		}
		count += len_written;
	}	
	va_end(ap);
	return (count);
}
