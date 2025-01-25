/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:11:18 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/01/25 16:49:22 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_end(char *str, int endof)
{
	int	i;

	if (!str || endof == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*extract_line(char **buff, int endof)
{
	char	*line;
	char	*new_buff;
	int		newline_index;

	newline_index = check_end(*buff, endof);
	if ((*buff)[newline_index] == '\n')
	{
		line = ft_substr(*buff, 0, newline_index + 1);
		if (!line)
			return (free(*buff), *buff = NULL, NULL);
		new_buff = ft_strdup(*buff + newline_index + 1);
		if (!new_buff)
			return (free(line), free(*buff), *buff = NULL, NULL);
		free(*buff);
		*buff = new_buff;
	}
	else
	{
		line = ft_strdup(*buff);
		free(*buff);
		*buff = NULL;
	}
	return (line);
}

char	*read_to_buff(char *buffer, int fd, int *endof)
{
	char	*temp;
	char	read_buff[BUFFER_SIZE + 1];
	ssize_t	length;

	length = read(fd, read_buff, BUFFER_SIZE);
	*endof = length;
	if (length < 0)
	{
		free(buffer);
		return (NULL);
	}
	read_buff[length] = '\0';
	if (!buffer)
		return (ft_strdup(read_buff));
	temp = ft_strjoin(buffer, read_buff);
	free(buffer);
	return (temp);
}

void cleanup_buffers(char *buffer[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (buffer[i])
        {
            free(buffer[i]);
            buffer[i] = NULL;
        }
    }
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	int			endof;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	endof = 1;
	while (!check_end(buffer[fd], endof) && endof != 0)
	{
		buffer[fd] = read_to_buff(buffer[fd], fd, &endof);
		if (!buffer[fd])
			return (NULL);
	}
	if (endof == 0 && (!*buffer[fd]))
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = extract_line(&buffer[fd], endof);
	// free(buffer);
	cleanup_buffers(buffer, 1024);
	return (line);
}

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line1;
	char	*line2;
	char	*line3;

	fd1 = open("text.txt", O_RDONLY);
	if (fd1 < 0)
		printf("Error opening file fd1\n");
	else
		printf("File fd1 opened successfully\n");
	fd2 = open("exam.txt", O_RDONLY);
	if (fd2 < 0)
		printf("Error opening file fd2\n");
	else
		printf("File fd2 opened successfully\n");
	fd3 = open("lorem.txt", O_RDONLY);
	if (fd3 < 0)
		printf("Error opening file fd3\n");
	else
		printf("File fd3 opened successfully\n");
	// line1 = get_next_line(fd1);
	// printf("[%s]", line1);
	// free(line1);
	
	// line2 = get_next_line(fd2);
	// printf("[%s]", line2);
	// free(line2);
	
	line3 = get_next_line(fd3);
	printf("[%s]", line3);
	free(line3);
	
	// line1 = get_next_line(fd1);
	// printf("[%s]", line1);
	// free(line1);
	
	// line2 = get_next_line(fd2);
	// printf("[%s]", line2);
	// free(line2);
	
	// line3 = get_next_line(fd3);
	// printf("[%s]", line3);
	// free(line3);

	close(fd1);
	close(fd2);
	close(fd3);
	printf("\nFile closed successfully\n");
	return (0);
}