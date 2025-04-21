/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:17:13 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/21 10:17:33 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_file(char *rest, int fd);
char	*ft_get_rest(char *rest);
char	*ft_get_line(char *rest);

char	*get_next_line(int fd)
{
	static char	*rest[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest[fd])
	{
		rest[fd] = malloc(1);
		rest[fd][0] = '\0';
	}
	rest[fd] = ft_read_file(rest[fd], fd);
	if (!rest[fd] || *rest[fd] == '\0')
	{
		free(rest[fd]);
		rest[fd] = NULL;
		return (NULL);
	}
	line = ft_get_line(rest[fd]);
	rest[fd] = ft_get_rest(rest[fd]);
	return (line);
}

char	*ft_read_file(char *rest, int fd)
{
	char	*temp;
	char	*buff;
	int		bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(rest, '\n') && bytes != 0)
	{
		temp = rest;
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			free(rest);
			return (NULL);
		}
		buff[bytes] = '\0';
		rest = ft_strjoin(rest, buff);
		free(temp);
	}
	free(buff);
	return (rest);
}

char	*ft_get_line(char *rest)
{
	char	*temp;
	int		i;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	temp = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (rest[i] && rest[i] != '\n')
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
	return (temp);
}

char	*ft_get_rest(char *rest)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\0')
	{
		free(rest);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlen(rest) - i + 1));
	if (!temp)
	{
		free(rest);
		return (NULL);
	}
	i++;
	while (rest[i])
		temp[j++] = rest[i++];
	temp[j] = '\0';
	free(rest);
	return (temp);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*line;
	int	fd;
	int	fd5;
	(void) argc;

	fd = open(argv[1], O_RDONLY);
	fd5 = open(argv[2], O_RDONLY);
	for(int i = 0; i < 7; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		line = get_next_line(fd5);
		printf("%s", line);
		free(line);	
	}
	close(fd);
	close(fd5);
	return (0);
}
*/
