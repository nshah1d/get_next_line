/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nshahid <nshahid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:07:29 by nshahid           #+#    #+#             */
/*   Updated: 2023/09/08 07:41:56 by nshahid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_end_of_line(char *str, size_t i)
{
	char	*ptr;

	ptr = str + i;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
		ptr++;
	return (ptr - str);
}

char	*ft_move_pointer(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*str == '\0')
	{
		free(str);
		return (NULL);
	}
	i = ft_end_of_line(str, i);
	new_str = (char *)malloc((ft_strlen(str) - i) + 1);
	if (!new_str)
	{
		free(new_str);
		return (NULL);
	}
	while (*(str + i))
		*(new_str + j++) = *(str + i++);
	*(new_str + j) = '\0';
	free(str);
	return (new_str);
}

char	*ft_read_line(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	i = ft_end_of_line(str, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_free(char *buff1, char *buff2)
{
	free(buff1);
	free(buff2);
	buff2 = NULL;
	return (buff2);
}

char	*get_next_line(int fd)
{
	char		*read_content;
	int			read_bytes;
	static char	*read_buffer[MAX_FD];

	read_bytes = 1;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	read_content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_content)
		return (NULL);
	while (!ft_strchr(read_buffer[fd], '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, read_content, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			read_buffer[fd] = ft_free(read_content, read_buffer[fd]);
			return (NULL);
		}
		read_content[read_bytes] = '\0';
		read_buffer[fd] = ft_strjoin(read_buffer[fd], read_content);
	}
	free(read_content);
	read_content = ft_read_line(read_buffer[fd]);
	read_buffer[fd] = ft_move_pointer(read_buffer[fd]);
	return (read_content);
}
