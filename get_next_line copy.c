/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalkhidi <yalkhidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 13:11:18 by yalkhidi          #+#    #+#             */
/*   Updated: 2025/01/23 17:55:02 by yalkhidi         ###   ########.fr       */
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
	printf(BOLD BLUE "****EXTRACT LINE****\n" RESET);
	char	*line;
	char	*new_buff;
	int		newline_index;

	newline_index = check_end(*buff, endof);
	if ((*buff)[newline_index] == '\n')
	{
		line = ft_substr(*buff, 0, newline_index + 1);
		new_buff = ft_strdup(*buff + newline_index + 1);
		printf("FREE buffer:{%s}\n", *buff);
		free(*buff);
		*buff = new_buff;
		return (line);
	}
	line = ft_strdup(*buff);
	printf("else FREE buffer:{%s}\n", *buff);
	free(*buff);
	*buff = NULL;
	printf("NULL buffer:{%s}\n", *buff);
	return (line);
}

char	*read_to_buff(char *buffer, int fd, int *endof)
{
	printf(BOLD RED"****READ TO BUFF****\n" RESET);
	char	*temp;
	char	read_buff[BUFFER_SIZE + 1];
	ssize_t	length;

	length = read(fd, read_buff, BUFFER_SIZE);
	*endof = length;
	if (length < 0)
		return (NULL);
	read_buff[length] = '\0';
	if (!buffer)
	{
		printf("returning read_buff: %s", read_buff);
		return (ft_strdup(read_buff));
	}
	temp = ft_strjoin(buffer, read_buff);
	// printf("FREE buffer:{%s}\n", buffer);
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	printf(BOLD GREEN "****GET NEXT LINE****\n" RESET);
	static char	*buffer;
	char		*line;
	int			endof;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	// if (!buffer)
	// 	buffer = ft_strdup("");
	endof = 1;
	while (!check_end(buffer, endof) && endof != 0)
	{
		buffer = read_to_buff(buffer, fd, &endof);
		if (!buffer)
			return (NULL);
	}
	// printf("*buffer '%d'\n", *buffer);
	// printf("buffer '%s'\n", buffer);
	if (endof == 0 && (!*buffer))
	{
		printf("FREE buffer:{%s}\n", buffer);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(&buffer, endof);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		printf("Error opening file");
	else
		printf("File opened successfully\n");
	// line = get_next_line(fd);
	// printf("[%s]", line);
	// free(line);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf(CYAN"[%s]" RESET, line);
		free(line);
		line = NULL;
		printf("\n");
	}
	close(fd);
	printf("\nFile closed successfully\n");
	return (0);
}
