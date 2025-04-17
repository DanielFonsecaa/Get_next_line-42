/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:06:55 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/17 17:50:41 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char	*ft_read_file(int fd, char *rest)
{
	char	*buff;
	char	*temp;
	int		bytes_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(rest, '\n') && bytes_read != 0)
	{
		temp = rest;
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(rest);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		rest = ft_strjoin(rest, buff);
		free(temp);
	}
	free(buff);
	return (rest);
}

static char	*ft_get_line(char *rest)
{
	char	*temp;
	int		i;

	i = 0;
	while (rest[i] != '\n' && rest[i])
		i++;
	temp = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (rest[i] != '\n' && rest[i])
	{
		temp[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
	{
		temp[i] = rest[i];
		i++;
	}
	temp[i] = '\0';
	write(1, temp, ft_strlen(temp));
	return (temp);
}

static char	*ft_get_rest(char *rest)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!rest)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\0')
	{
		free(rest);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlen(rest) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	while (rest[i])
		temp[j++] = rest[i++];
	temp[j] = '\0';
	free(rest);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
	{
		rest = malloc(1);
		rest[0] = '\0';
	}
	rest = ft_read_file(fd, rest);
	if (!rest || *rest == '\0')
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	line = ft_get_line(rest);
	rest = ft_get_rest(rest);
	return (line);
}

/* int	main(int argc, char **argv)
{
	char *temp;
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	for (int i = 0; i < 5; i++)
	{
		temp = get_next_line(fd);
		free(temp);
	}
	temp = get_next_line(fd);
	free(temp);
	close(fd);
}

 */
