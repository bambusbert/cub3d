#include "f_parsing.h"
#include <limits.h>
#include <stdint.h>

int	check_digit(long long *num, int neg, long long limit, char c);
bool	is_overflow(char *arg);

uint32_t f_catch_num(char *s)
{
    int ret;
    int i;

    i = 0;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return (printf("Error\nNot a number.\n"), 600);
        i++;
    }
    if (is_overflow(s) == false)
        return (printf("Error\nNumber out of range.\n"),600);
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
		return (printf("Error\nNegative Number."), false);
	else
		limit = LIMIT_UP;
	while (ft_isdigit(arg[i]))
	{
		if (check_digit(&num, neg, limit, arg[i]))
			return (printf("Error\nNumber too big."), false);
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
		neg = (arg[i++] == '-'); // lassen oder nicht???
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
