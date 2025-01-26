/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:11:18 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/01/26 18:59:24 by yalkhidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*extract_line(char **buff, int endof)
{
	char	*line;
	char	*new_buff;
	int		newline_index;

	if (!buff || !*buff)
		return (NULL);
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

char	*get_next_line(int fd)
{
	static char	*buffer[10240];
	char		*line;
	int			endof;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	endof = 1;
	while (!check_end(buffer[fd], endof) && endof > 0)
	{
		buffer[fd] = read_to_buff(buffer[fd], fd, &endof);
		if (!buffer[fd])
			return (NULL);
	}
	if (endof == 0 && (!buffer[fd] || !*buffer[fd]))
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	line = extract_line(&buffer[fd], endof);
	return (line);
}
