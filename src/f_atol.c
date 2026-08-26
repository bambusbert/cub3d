/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_atol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 12:09:25 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/26 12:09:26 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/f_parsing.h"

int			check_digit(long long *num, int neg, long long limit, char c);
bool		is_overflow(char *arg);

uint32_t	f_catch_num(char *s)
{
	int	ret;
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]) && s[i] != ' ' && s[i] != '\t')
			return (ft_putstr_fd("Error\nNot a Number.\n", 2), 600);
		i++;
	}
	if (is_overflow(s) == false)
		return (ft_putstr_fd("Error\nNumber out of range.\n", 2), 600);
	ret = f_atoll(s);
	return (ret);
}

int	check_digit(long long *num, int neg, long long limit, char c)
{
	if (!neg && *num > (limit - (c - '0')) / 10)
		return (1);
	if (neg && *num < (limit + (c - '0')) / 10)
		return (1);
	if (!neg)
		*num = *num * 10 + (c - '0');
	else
		*num = *num * 10 - (c - '0');
	return (0);
}

bool	is_overflow(char *arg)
{
	long long	num;
	long long	limit;
	int			neg;
	int			i;

	i = 0;
	neg = 0;
	num = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		neg = (arg[i++] == '-');
	if (neg)
		return (ft_putstr_fd("Error\nNegative Number.\n", 2), false);
	else
		limit = LIMIT_UP;
	while (ft_isdigit(arg[i]))
	{
		if (check_digit(&num, neg, limit, arg[i]))
			return (ft_putstr_fd("Error\nNumber too big.\n", 2), false);
		i++;
	}
	return (true);
}

long long	f_atoll(char *arg)
{
	long long	num;
	int			neg;
	int			i;

	i = 0;
	neg = 0;
	num = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		neg = (arg[i++] == '-');
	while (ft_isdigit(arg[i]))
	{
		if (neg)
			num = num * 10 - (arg[i] - '0');
		else
			num = num * 10 + (arg[i] - '0');
		i++;
	}
	return (num);
}
