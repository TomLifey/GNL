/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabutair <mabutair@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 13:49:26 by mabutair          #+#    #+#             */
/*   Updated: 2026/11/12 10:42:25 by mabutair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (ft_check(saved, NULL));
	byte_c = 1;
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
	while (saved[i] && saved[i] != '\n')
		i++;
	if (i == 0 && !saved[i])
		return (NULL);
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

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
		return (ft_check(saved, NULL));
	leftovers = ft_calloc(ft_strlen(saved) - i, sizeof(char));
	if (!leftovers)
		return (ft_check(saved, NULL));
	i++;
	j = 0;
	while (saved[i])
		leftovers[j++] = saved[i++];
	free(saved);
	return (leftovers);
}

char	*get_next_line(int fd)
{
	static char	*saved[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved[fd])
		saved[fd] = ft_calloc(1, sizeof(char));
	if (!saved[fd])
		return (NULL);
	saved[fd] = ft_reading(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = ft_get_line(saved[fd]);
	if (!line)
	{
		saved[fd] = ft_check(saved[fd], NULL);
		return (NULL);
	}
	saved[fd] = ft_get_leftovers(saved[fd]);
	return (line);
}
