/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 17:39:39 by yislam            #+#    #+#             */
/*   Updated: 2022/08/14 07:04:53 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *remain)
{
	int		i;
	char	*str;

	i = 0;
	if (!remain[i])
		return (NULL);
	while (remain[i] && remain[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (remain[i] && remain[i] != '\n')
	{
		str[i] = remain[i];
		i++;
	}
	if (remain[i] == '\n')
	{
		str[i] = remain[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *remain)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (remain[i] && remain[i] != '\n')
		i++;
	if (!remain[i])
	{
		free(remain);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(remain) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (remain[i])
		str[j++] = remain[i++];
	str[j] = '\0';
	free(remain);
	return (str);
}

char	*ft_read_to_left_str(int fd, char *remain)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(remain, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		remain = ft_strjoin(remain, buff);
	}
	free(buff);
	return (remain);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*remain;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	remain = ft_read_to_left_str(fd, remain);
	if (!remain)
		return (NULL);
	str = ft_get_line(remain);
	remain = ft_new_left_str(remain);
	return (str);
}

/*
#include <stdio.h>

int main()
{
	int a = open("src.txt", O_CREAT, 0777);
	char *p;

	p =get_next_line(a);
	while(p  != NULL)
	{
		printf("%s",p);
		free(p);
		p = get_next_line(a);
	}
	free(p);
	system("Leaks deneme");
}
*/