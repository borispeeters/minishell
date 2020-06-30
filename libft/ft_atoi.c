/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:24:22 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/02/03 09:26:14 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r')
		str++;
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result >= 922337203685477580)
		{
			if ((sign == -1 && *str >= '9') || (sign == 1 && *str >= '8'))
				return ((sign == -1) ? 0 : -1);
			result = (result * 10) + (*str - 48);
			return ((int)result * sign);
		}
		result *= 10;
		result += (*str - 48);
		str++;
	}
	return ((int)result * sign);
}
