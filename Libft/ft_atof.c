#include "libft.h"

double atof_aux(const char *str)
{
    int i;
    double f;

    i = 10;
    f = 0;
    if (*str && *str == '.')
    {
        str++;
        i = 10;
        while ((*str >= 48) && (*str <= 57) && *str)
	    {
		    f += ((double)(*str - 48) / i);
            i *= 10;
		    str++;
	    }
    }
    return (f);
}

double	ft_atof(const char *str)
{
	double	f;
	char	sign;

	f = 0;
	sign = 1;
	while (((*str > 8) && (*str < 14)) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ((*str >= 48) && (*str <= 57) && *str)
	{
		f = (f * 10) + (*str - 48);
		str++;
	}
    f = f + atof_aux(&(*str));
	return (f * sign);
}