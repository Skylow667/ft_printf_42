/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlocusso <nlocusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:30:38 by nlocusso          #+#    #+#             */
/*   Updated: 2022/10/01 22:22:34 by nlocusso         ###   ########.fr       */
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

int		nb_fmt(char const *fmt)
{
	int	i;
	int cnt;

	cnt = 0;
	i = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%' && fmt[i + 1] != '%')
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
	/*else if (fmt[1] == 'p')
		;
	else if (fmt[1] == 'd')
		ft_putnbr(va_arg(args, char *)); # modifier la fonction pour le point
	else if (fmt[1] == 'i')
		ft_putnbr(va_arg(args, char *));
	else if (fmt[1] == 'u')
		ft_putnbr(args); # modifier pour les unsign
	else if (fmt[1] == 'x')
		ft_putnbr_base(va_arg(args, char *)); # Full majuscules
	else if (fmt[1] == 'X')
		ft_putnbr_base(va_arg(args, char *)); # Full minuscules
	*/
	else
		write(1, "Erreur", 6);
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
		if (fmt[i] == '%' && fmt[i + 1] != '\0')
		{
			tab[cnt] = malloc(2 * sizeof(char *));
			tab[cnt][0] = fmt[i];
			tab[cnt][1] = fmt[i + 1];
		   	cnt++;
		}
		i++;
	}
	return (tab);
}

int ft_printf(const char *fmt, ...)
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
		if (tab_fmt[i] == "%%")
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
	ft_printf("%s\n%s", "chat", "chien");
	printf("\n");
	printf("%s%s", "chat", "chien");
	return 0;
}
