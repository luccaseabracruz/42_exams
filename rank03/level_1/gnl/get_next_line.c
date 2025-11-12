#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static size_t	ft_line_len(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	return (len);
}


static char	*ft_line_buffer_join(char *line, char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	line_len;
	size_t	buffer_len;
	char	*res;

	line_len = ft_line_len(line);
	buffer_len = ft_line_len(buffer);
	res = malloc((line_len + buffer_len) * sizeof(char) + 1);
	if (!res)
	{
		if (line)
			free(line);
		return (NULL);
	}
	i = -1;
	while (++i < line_len)
		res[i] = line[i];
	if (line)
		free(line);
	j = -1;
	while (++j < buffer_len)
		res[i + j] = buffer[j];
	res[i + j] = '\0';
	return (res);
}

char	*ft_strchr(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

static void	ft_clean_buffer(char *buffer)
{
	char	*tmp;

	if (!buffer)
		return ;
	tmp = buffer;
	while (*tmp && *tmp != '\n')
		tmp++;
	if (*tmp == '\n')
		tmp++;
	while (*tmp)
	{
		*buffer = *tmp;
		buffer++;
		tmp++;
	}
	while (*buffer)
	{
		*buffer = '\0';
		buffer++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			bytes_read;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 )
		return (NULL);
	line = ft_line_buffer_join(NULL, buffer);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0 || buffer[0] == '\0')
		{
			free(line);
			ft_clean_buffer(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		line = ft_line_buffer_join(line, buffer);
	}
	ft_clean_buffer(buffer);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	char	*file;
// 	int		fd;

// 	file = "../filter/subject.txt";
// 	fd = open(file, O_RDONLY);
// 	if (fd < STDERR_FILENO)
// 	{
// 		perror("open");
// 		return (EXIT_FAILURE);
// 	}
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (EXIT_SUCCESS);
// }