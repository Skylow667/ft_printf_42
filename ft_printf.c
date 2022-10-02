/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <nlocusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:30:38 by nlocusso          #+#    #+#             */
/*   Updated: 2022/10/02 21:28:00 by nlocusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, &str[i], 1);
}

int	nb_fmt(char const *fmt)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%' && fmt[i + 1] == '%')
		{
			i++;
			cnt++;
		}
		else if (fmt[i] == '%' && fmt[i + 1] != '\0')
		{
			cnt++;
			i++;
		}
		else if (fmt[i] >= 9 && fmt[i] <= 13)
			cnt++;
		i++;
	}
	return (cnt);
}

void	fmt_check(const char *fmt, va_list args)
{
	if (fmt[1] == 'c')
		ft_putchar(va_arg(args, int));
	else if (fmt[1] == 's')
		ft_putstr(va_arg(args, char *));
	/*else if (fmt[1] == 'i')
		putnbr(va_arg(args, int));
	else if (fmt[1] == 'p')
		;
	else if (fmt[1] == 'd')
		ft_putnbr_dec(va_arg(args, int)); # modifier la fonction pour le point
	else if (fmt[1] == 'u')
		ft_putnbr_unsign(va_arg(args, int)); # modifier pour les unsign
	else if (fmt[1] == 'x')
		ft_putnbr_base(va_arg(args, int)); # Full majuscules
	else if (fmt[1] == 'X')
		ft_putnbr_base(va_arg(args, int)); # Full minuscules
	*/
	else if (*fmt >= 9 && *fmt <= 13)
		write(1, fmt, 1);
	else
		write(1, "Erreur", 6);
}

int		malloc_fmt(const char *fmt, int i)
{
	int	len_fmt;

	len_fmt = 0;
	if (fmt[i] == '%' && fmt[i + 1] == '%')
		return (2);
	if (fmt[i] >= 9 && fmt[i] <= 13)
		return (1);
	while (fmt[i] != '\0' && fmt[i + 1] != '%')
	{
		len_fmt++;
		if (fmt[i + 1] >= 9 && fmt[i + 1] <= 13)
			return (len_fmt);
		i++;
	}
	return (len_fmt);
}

char	*tab_for_fmt_bis(const char *fmt, int i, char *tab)
{
	int	cnt;
	int	l_malloc;

	l_malloc = (malloc_fmt(fmt, i));
	tab = malloc(l_malloc * sizeof(char *));
	cnt = 0;
	while (cnt != l_malloc)
	{
		tab[cnt] = fmt[i];
		cnt++;
		i++;
	}
	return (tab);
}

char	**tab_for_fmt(const char *fmt, int cnt_fmt)
{
	int		i;
	int		cnt;
	char	**tab;

	i = 0;
	cnt = 0;
	tab = malloc(cnt_fmt * sizeof(char *));
	while (fmt[i] != '\0')
	{
		tab[cnt] = tab_for_fmt_bis(fmt, i, tab[cnt]);
		cnt++;
		i += (malloc_fmt(fmt, i));
	}
	return (tab);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	int			cnt_fmt;
	int			i;
	char		**tab_fmt;
	
	i = 0;
	cnt_fmt = nb_fmt(fmt);
	tab_fmt = tab_for_fmt(fmt, cnt_fmt);
	va_start(args, fmt);
	while (i != cnt_fmt)
	{
		if (tab_fmt[i][1] == '%')
			write(1, "%", 1);
		else
			fmt_check(tab_fmt[i], args);
		i++;
	}
	va_end(args);
	return (1);
}	

int main(int argc, char *argv[])
{
	ft_printf("%%%s\n%s", "chat", "chien");
	printf("\n");
	printf("%%%s\n%s", "chat", "chien");
	return 0;
}
