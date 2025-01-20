/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:11:18 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/01/20 19:22:09 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_end(char *str)
{
	int	i;

	if (!str)
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

char	*read_to_buff(char *buffer, int fd)
{
	char	*temp;
	char	read_buff[BUFFER_SIZE + 1];
	ssize_t	length;

	length = read(fd, read_buff, BUFFER_SIZE);
	if (length <= 0)
		return (buffer);
	read_buff[length] = '\0';
	if (!buffer)
		return (ft_strdup(read_buff));
	temp = ft_strjoin(buffer, read_buff);
	free(buffer);
	return (temp);
}

char	*extract_line(char **buff)
{
	char	*line;
	char	*new_buff;
	int		newline_index;

	newline_index = check_end(*buff);
	if (newline_index > 0)
	{
		line = ft_substr(*buff, 0, newline_index + 1);
		new_buff = ft_strdup(*buff + newline_index + 1);
		printf("new_buff %s\n", new_buff);
		free(*buff);
		*buff = new_buff;
		return (line);
	}
	line = ft_strdup(*buff);
	free(*buff);
	*buff = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	while (!check_end(buffer))
	{
		buffer = read_to_buff(buffer, fd);
		if (!buffer)
			return (NULL);
	}
	line = extract_line(&buffer);
	free(buffer);
	buffer = NULL;
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;
	// int		len;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("error opening file\n");
		return (1);
	}
	else
		printf("file opened successfully\n");
	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	// while (1)
	// {
	// 	line = get_next_line(fd);
	// 	if (line == NULL)
	// 		break ;
	// 	printf("%s", line);
	// 	free(line);
	// 	line = NULL;
	// }
	close(fd);
}

