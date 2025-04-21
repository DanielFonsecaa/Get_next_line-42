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

char	*ft_read_file(int fd, char *rest)
{
	char	*buff;
	char	*temp;
	int		bytes_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(rest, '\n') && bytes_read > 0)
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

char	*ft_get_line(char *rest)
{
	char	*temp;
	int		i;

	i = 0;
	if (!rest)
		return (NULL);
	while (rest[i] != '\n' && rest[i])
		i++;
	temp = malloc(sizeof(char) * (i + 2));
	i = 0;
	while (rest[i] != '\n' && rest[i])
	{
		temp[i] = rest[i];
		i++;
	}
	if (rest[i] && rest[i] == '\n')
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
	while (rest[i] && (rest[i] != '\n'))
		++i;
	if (!rest[i])
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
	++i;
	j = 0;
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
		if (!rest)
			return (NULL);
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
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char *line;
	(void)argc;
	int fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); // Print the line read from the file
        free(line); // Free the memory allocated for the line
    }

    close(fd); // Close the file descriptor
    return (0);
}
//int	main()
//{
//	int i = 0;
//
//	while (i < 4)
//	{
//		printf("%s\n", get_next_line(0));
//		i++;
//	}
//    return (0);
//}
//*/
