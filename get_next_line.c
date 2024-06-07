/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariling <ariling@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 05:14:05 by ariling           #+#    #+#             */
/*   Updated: 2024/06/07 16:21:25 by ariling          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

// Find the position of the next line break in the string
static size_t	locate_next_line(char *buffer, size_t start)
{
	char	*cursor;

	cursor = buffer + start;
	while (*cursor && *cursor != '\n')
		cursor++;
	if (*cursor == '\n')
		cursor++;
	return (cursor - buffer);
}

// Create a new substring starting after the first newline character
static char	*extract_remainder(char *buffer)
{
	char	*new_buffer;
	size_t	start;
	size_t	index;

	start = 0;
	index = 0;
	if (!*buffer)
		return (free(buffer), NULL);
	start = locate_next_line(buffer, start);
	new_buffer = (char *)malloc((ft_strlen(buffer) - start) + 1);
	if (!new_buffer)
		return (free(new_buffer), NULL);
	while (*(buffer + start))
		*(new_buffer + index++) = *(buffer + start++);
	*(new_buffer + index) = '\0';
	if (!*new_buffer)
		return (free(buffer), free(new_buffer), NULL);
	free(buffer);
	return (new_buffer);
}

// Read a single line from the buffer
static char	*extract_line(char *buffer)
{
	char	*line;
	size_t	index;

	index = 0;
	if (!buffer || *buffer == '\0')
		return (NULL);
	index = locate_next_line(buffer, index);
	line = (char *)malloc(sizeof(char) * index + 1);
	if (!line)
		return (NULL);
	index = 0;
	while (*(buffer + index) && *(buffer + index) != '\n')
	{
		*(line + index) = *(buffer + index);
		index++;
	}
	if (*(buffer + index) == '\n')
	{
		*(line + index) = *(buffer + index);
		index++;
	}
	*(line + index) = '\0';
	return (line);
}

// Free two buffers and set the second to NULL
static char	*cleanup_buffers(char *buffer1, char *buffer2)
{
	free(buffer1);
	free(buffer2);
	buffer2 = NULL;
	return (buffer2);
}

// Main function to get the next line from the file descriptor `fd`
char	*get_next_line(int fd)
{
	char		*read_buf;
	int			bytes_read;
	static char	*static_buf;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	read_buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	while (!(ft_strchr(static_buf, '\n')) && bytes_read != 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			static_buf = cleanup_buffers(read_buf, static_buf);
			return (NULL);
		}
		*(read_buf + bytes_read) = '\0';
		static_buf = ft_strjoin(static_buf, read_buf);
	}
	free(read_buf);
	read_buf = extract_line(static_buf);
	static_buf = extract_remainder(static_buf);
	return (read_buf);
}
