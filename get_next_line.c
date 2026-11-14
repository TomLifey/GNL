/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabutair <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 14:10:30 by mabutair          #+#    #+#             */
/*   Updated: 2026/10/31 14:13:30 by mabutair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_check(char *saved, char *buf)
{
	free(saved);
	free(buf);
	return (NULL);
}

static char	*ft_reading(int fd, char *saved)
{
	ssize_t	byte_c;
	char	*buf;
	char	*temp;

	byte_c = 1;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (ft_check(saved, NULL));
	while (!ft_strchr(saved, '\n') && byte_c > 0)
	{
		byte_c = read(fd, buf, BUFFER_SIZE);
		if (byte_c == -1)
			return (ft_check(saved, buf));
		buf[byte_c] = '\0';
		if (byte_c > 0)
		{
			temp = ft_strjoin(saved, buf);
			if (!temp)
				return (ft_check(saved, buf));
			free(saved);
			saved = temp;
		}
	}
	free(buf);
	return (saved);
}

static char	*ft_get_line(char *saved)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_get_leftovers(char *saved)
{
	char	*leftovers;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
		return (ft_check(saved, NULL));
	i++;
	len = 0;
	while (saved[i + len])
		len++;
	leftovers = ft_calloc(len + 1, sizeof(char));
	if (!leftovers)
		return (ft_check(saved, NULL));
	j = 0;
	while (saved[i])
		leftovers[j++] = saved[i++];
	free(saved);
	return (leftovers);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		saved = ft_check(saved, NULL);
		return (NULL);
	}
	if (!saved)
	{
		saved = ft_calloc(1, sizeof(char));
		if (!saved)
			return (NULL);
	}
	saved = ft_reading(fd, saved);
	if (!saved)
		return (NULL);
	line = ft_get_line(saved);
	if (!line)
	{
		saved = ft_check(saved, NULL);
		return (NULL);
	}
	saved = ft_get_leftovers(saved);
	return (line);
}
