/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_commandline_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsitter <fsitter@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 15:44:02 by fsitter           #+#    #+#             */
/*   Updated: 2026/08/26 12:09:53 by fsitter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_parsing.h"

static bool	f_test_ending(const char *s);

bool	f_test_input(int ac, const char *s)
{
	if (ac != 2)
		return (ft_putstr_fd("Error\nWrong number of arguments.\n", 2), false);
	if (f_test_ending(s) == false)
		return (ft_putstr_fd("Error\nWrong fileextension or hidden file.\n", 2),
			false);
	return (true);
}

static bool	f_test_ending(const char *s)
{
	size_t	i;

	i = ft_strlen(s);
	if (i < 5)
		return (false);
	if (s[i - 4] != '.')
		return (false);
	if (s[i - 3] != 'c')
		return (false);
	if (s[i - 2] != 'u')
		return (false);
	if (s[i - 1] != 'b')
		return (false);
	return (true);
}
