/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:56:34 by tzara             #+#    #+#             */
/*   Updated: 2025/05/20 12:28:02 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static long long	process_numbers(long long num, long long i, int sign,
						const char *s);
static int			is_digit(int c);
static int			is_whitespace(int c);
static int			is_sign(int c);

long long	ft_atoll(const char *s)
{
	long long	i;
	long long	num;
	int			sign;

	if (s == NULL)
		return (0);
	if (s[0] == '\0')
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (is_whitespace(s[i]))
		i++;
	if (!is_sign(s[i]) && !is_digit(s[i]))
		return (0);
	if (is_sign(s[i]) && !is_digit(s[i + 1]))
		return (0);
	return (process_numbers(num, i, sign, s));
}

static int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	is_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || (c == 32));
}

static int	is_sign(int c)
{
	return (c == '-' || c == '+');
}

static long long	process_numbers(long long num, long long i, int sign,
		const char *s)
{
	if (is_sign(s[i]))
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	if (ft_strlen(s + i) > 19)
		return (ft_printf("Error: Argument value is too long\n"));
	while (s[i] != '\0' && is_digit(s[i]))
	{
		num *= 10;
		num += (s[i] - '0') % 10;
		i++;
	}
	return (num * sign);
}
