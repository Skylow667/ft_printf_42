/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <nlocusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:30:38 by nlocusso          #+#    #+#             */
/*   Updated: 2022/10/01 20:08:00 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include "libft.h"

int		nb_fmt(char const *fmt)
{
	int	i;
	int cnt;

	cnt = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] != '%')
			cnt++;
		i++;
	}
	return (cnt);
}
void	fmt_check(const char *fmt, va_list args)
{
	if (*fmt == "%c")
		ft_putchar(args);
	else if (*fmt == "%s")
		ft_putstr(args);
	else if (*fmt == "%p")
		;
	else if (*fmt == "%d")
		ft_putnbr(arsg); # modifier la fonction pour le point
	else if (*fmt == "%i")
		ft_putnbr(args);
	else if (*fmt == "%u")
		ft_putnbr(args); # modifier pour les unsign
	else if (*fmt == "%x")
		ft_putnbr_base(args); # Full majuscules
	else if (*fmt == "%X")
		ft_putnbr_base(args); # Full minuscules
	else if (*fmt == "%%")
		write(1, '%', 1);
}

char	**tab_for_fmt(const char *fmt, int cnt_fmt)
{
	int		i;
	int		y;
	int		cnt;
	char	**tab;

	i = 0;
	y = 0;
	cnt = 0;
	tab = malloc(cnt_fmt * sizeof(char *));
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%' && fmt[i + 1] != '\0')
		{
			tab[cnt] = malloc(2 * sizeof(char *));
			tab[cnt][y] = fmt[i];
			tab[cnt][y + 1] = fmt[i + 1];
		   	cnt++;
		}
		i++;
		y++;
	}
	return (tab);
}

int ft_printf(const char *fmt, ...)
{
	va_list		args;
	const char	*value;
	int			cnt_fmt;
	int			i;
	char		**tab_fmt;
	
	i = 0;
	cnt_fmt = nb_fmt(fmt);
	tab_fmt = tab_for_fmt(fmt, cnt_fmt);
	va_start(args, str);
	while (i != cnt_fmt)
	{
		value = va_arg(args, const char *);
		check(tab_fmt[i], value);
		i++;
	}
	va_end(args);
	return (1);
}	

int main(int argc, char *argv[])
{
	ft_printf("%s", "Salut");
	return 0;
}
