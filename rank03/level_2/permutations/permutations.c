#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static size_t	ft_strlen(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	ft_bubblesort(char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	tmp;

	len = ft_strlen(str);
	i = 0;
	while (i < (len - 1))
	{
		j = 0;
		while (j < (len - 1 - i))
		{
			if (str[j] > str[j + 1])
			{
				tmp = str[j];
				str[j] = str[j + 1];
				str[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
int	ft_haschr(char *str, char c)
{
	while (str && *str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	ft_swap(char *ptr1, char *ptr2)
{
	char	tmp;

	tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void	ft_permutations(int	pos, char *src, char *res, size_t og_len)
{
	int	i;

	if (ft_strlen(res) == og_len)
	{
		write(1, res, og_len);
		write(1, "\n", 1);
		return ;
	}
	if (pos == 0)
		ft_bubblesort(src);
	i = 0;
	while (src[i])
	{
		if (!ft_haschr(res, src[i]))
		{
			res[pos] = src[i];
			ft_permutations(pos + 1, src, res, og_len);
			res[pos] = 0;
		}
		i++;
	}
}


int	main(int argc, char **argv)
{
	char	*res;
	size_t	og_len;
	int		i = 0;

	if (argc < 2)
		return (1);
	og_len = ft_strlen(argv[1]);
	res = malloc(og_len * sizeof(char) + 1);
	if (!res)
		return (1);
	while (i < (int)og_len)
	{
		res[i] = 0;
		i++;
	}
	ft_permutations(0, argv[1], res, og_len);
	free(res);
	return (0);
}
