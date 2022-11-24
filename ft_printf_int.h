/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achansel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 14:35:57 by achansel          #+#    #+#             */
/*   Updated: 2022/09/06 14:47:40 by achansel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_INT_H
# define FT_PRINTF_INT_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include <unistd.h>

/* Structs */
typedef struct s_conversion_modifiers
{
	bool	alternative;
	bool	zero_padded;
	bool	left_adjusted;
	bool	space_before_positive;
	bool	force_sign;
	int		precision;
	int		width;
} t_conv_mods,	t_cv;

/* conversion.c */
t_cv	get_conversion_modifiers(const char *str);
char	get_conversion_specifier(const char *str);

/* utils.c */
int		ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, int n);
char	*printf_ntoa_base(uint64_t n, bool neg, const char *base, int fdw);

/* conversion_helper.c */
bool	is_hex_conversion(const char c);
bool	is_unsigned_conversion(const char c);
bool	is_numerical_conversion(const char c);
bool	is_conversion_letter(const char c);

/* flag_helper.c */
bool	mod_should_force_sign(t_conv_mods *mods, bool neg, const char s);
bool	mod_should_leave_space(t_conv_mods *m, bool n, const char s);
bool	mod_should_alternative_form(t_cv *m, const char s, const uint64_t u);
bool	mod_should_left_adjust(t_cv *m, const char spec, int print_len);
bool	mod_should_right_adjust(t_cv *m, const char spec, int print_len);

/* serialize.c */
char	*serialize_char(const char c, t_conv_mods *m);
char	*serialize_string(const char *s, t_conv_mods *m);
char	*serialize_int(const int i, t_conv_mods *m);
char	*serialize_uint(const unsigned int u, t_conv_mods *m);
char	*serialize_hex(const uint64_t u, t_conv_mods *m, bool force_a, bool up);

/* Helper funcs */
static inline int	write_n(int fd, const char c, int cnt)
{
	int	i;

	i = -1;
	while (++i < cnt)
	{
		if (write(fd, &c, 1) == -1)
			return (-1);
	}
	return (cnt);
}

static inline char	*ft_strjoin(const char *a, const char *b)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(a) + ft_strlen(b) + 1);
	while (*a)
		ret[i++] = *a++;
	while (*b)
		ret[i++] = *b++;
	ret[i] = '\0';
	return (ret);
}

#endif
