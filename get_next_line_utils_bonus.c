/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-fons <dda-fons@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:18:16 by dda-fons          #+#    #+#             */
/*   Updated: 2025/04/21 10:19:17 by dda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	char	*ret;

	while (*s)
	{
		if (*s == (char)c)
		{
			ret = (char *)s;
			return (ret);
		}
		s++;
	}
	if (!(char)c)
	{
		ret = (char *)&s[ft_strlen(s)];
		return (ret);
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	if (s1)
	{
		while (*s1)
			ret[i++] = *s1++;
	}
	while (*s2)
		ret[i++] = *s2++;
	ret[i] = '\0';
	return (ret);
}
