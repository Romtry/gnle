/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rothiery <rothiery@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:05:13 by rothiery          #+#    #+#             */
/*   Updated: 2024/06/11 12:38:41 by rothiery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*saveread(int fd, char *save)
{
	int		i;
	int		brd;
	char	*rd;

	rd = malloc(sizeof(char) * BUFFER_SIZE + 1);
	i = 1;
	brd = 1;
	while (brd > 0 && i == brd)
	{
		i = 0;
		brd = read(fd, rd, BUFFER_SIZE);
		if (brd == -1)
			return (free(rd), free(save), NULL);
		rd[brd] = '\0';
		save = ft_strjoinfr(save, rd);
		if (!save)
			return (free(rd), NULL);
		while (rd[i] != '\0' && rd[i] != '\n')
			i++;
	}
	if (brd == 0 && save[brd] == '\0')
		return (free(save), free(rd), NULL);
	return (free(rd), save);
}

char	*linesep(char *save, int l_line)
{
	char	*line;
	int		i;

	i = 0;
	line = (char *)malloc(sizeof(char) * l_line + 2);
	if (!line)
		return (NULL);
	while (i < l_line)
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*saveend(char *save, int l_line)
{
	char	*temp;
	int		i;

	if (save == NULL)
		return (NULL);
	if (save[l_line] == '\0')
		return (free(save), NULL);
	l_line++;
	temp = (char *)malloc(sizeof(char) * (ft_strlen(save)));
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(save) - l_line)
	{
		temp[i] = save[l_line + i];
		i++;
	}
	temp[i] = '\0';
	return (free(save), temp);
}

char	*get_next_line(int fd)
{
	int			l_line;
	char		*line;
	static char	*save;

	l_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)
		save = ft_strdup("");
	save = saveread(fd, save);
	if (!save)
		return (NULL);
	while (!(save[l_line] == '\n' || save[l_line] == '\0'))
		l_line++;
	if (!save)
		return (NULL);
	line = linesep(save, l_line);
	save = saveend(save, l_line);
	return (line);
}

// #include <stdlib.h>
// #include <libgen.h>
// #include <string.h>
// #include <fcntl.h>
// #include <unistd.h>

// int	main(void)
// {
// 	// First Test
// 	int		fd1 = open("./testers/test1.txt", O_RDONLY);
// 	char	*line1 = get_next_line(fd1);

// 	printf("test.txt file:");
// 	while (line1 != NULL)
// 	{
// 		printf("%s", line1);
// 		free(line1);
// 		line1 = get_next_line(fd1);
// 	}
// 	close(fd1);
// 	return (0);
// }

// int	main(void)
// {
// //	int	i;
// 	int	fd1 = open("test.txt", O_RDONLY);
// 	char	*line1 = get_next_line(fd1);

// //	i = 0;
// 	printf("%s", line1);
// //	free(line1);
// //	line1 = get_next_line();
// //	printf("%s\n", line1);
// 	free(line1);
// }
