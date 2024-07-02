/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:43:08 by mualkhid          #+#    #+#             */
/*   Updated: 2024/01/31 13:27:46 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_until_newline(int fd, char *left_str)
{
	char	*buf;
	int		read_bytes;

	buf = malloc(((size_t)BUFFER_SIZE + 2));
	if (!left_str)
	{
		left_str = malloc(1);
		if (!left_str)
			return (NULL);
		*left_str = '\0';
	}
	read_bytes = 1;
	while (!(ft_strchr(left_str, '\n')) && read_bytes > 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buf), free(left_str), NULL);
		buf[read_bytes] = '\0';
		left_str = ft_strjoin(left_str, buf);
	}
	return (free(buf), left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	left_str = ft_read_until_newline(fd, left_str);
	if (!left_str)
		return (NULL);
	i = 0;
	line = ft_getline(left_str);
	left_str = ft_after_newline(left_str);
	return (line);
}
