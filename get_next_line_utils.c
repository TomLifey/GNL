/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabutair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 14:10:30 by mabutair          #+#    #+#             */
/*   Updated: 2026/10/31 14:13:30 by mabutair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	if (size == 0 || n == 0)
		return (malloc(0));
	if (n > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(n * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, n * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	index;
	size_t	jndex;

	if (!s1 || !s2)
		return (NULL);
	index = 0;
	jndex = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[index] != '\0')
	{
		ptr[index] = s1[index];
		index++;
	}
	while (s2[jndex] != '\0')
	{
		ptr[index] = s2[jndex];
		index++;
		jndex++;
	}
	ptr[index] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == (char)c)
			return ((char *)&s[index]);
		index++;
	}
	if (s[index] == (char)c)
		return ((char *)&s[index]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
