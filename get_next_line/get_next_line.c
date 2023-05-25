/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:38:07 by ralopez-          #+#    #+#             */
/*   Updated: 2022/09/24 12:38:10 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*exchange(char *text, char *cad)
{
	char	*text_aux;

	text_aux = ft_strjoin_gnl(text, cad);
	free(text);
	return (text_aux);
}

static char	*leer(int fd, char *text)
{
	int		bytes_read;
	char	*cad;

	if (text == NULL)
		text = ft_calloc_gnl(1, 1);
	cad = (char *)ft_calloc_gnl(BUFFER_SIZE +1, sizeof(char));
	if (!cad)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, cad, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(cad);
			return (NULL);
		}
		cad[bytes_read] = 0;
		text = exchange(text, cad);
		if (ft_strchr_gnl(text, '\n'))
			break ;
	}
	free(cad);
	return (text);
}

char	*obtain_line(char *text)
{
	char	*res;
	int		i;

	i = 0;
	if (!text[i])
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	res = NULL;
	res = (char *)ft_calloc_gnl(i + 2, sizeof(char));
	i = 0;
	while (text[i] && text[i] != '\n')
	{
		res[i] = text[i];
		i++;
	}
	if (text[i] && text[i] == '\n')
		res[i] = '\n';
	return (res);
}

char	*clean_text(char *text)
{
	char	*aux;
	int		i;
	int		a;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free(text);
		return (NULL);
	}
	aux = NULL;
	if (text[i] == '\n')
		i++;
	aux = (char *)ft_calloc_gnl((ft_strlen_gnl(text) - i) + 1, sizeof(char));
	if (!aux)
		return (NULL);
	a = 0;
	while (text[i])
		aux[a++] = text[i++];
	free(text);
	return (aux);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	line = NULL;
	if (read(fd, 0, 0) < 0)
	{
		if (text != NULL)
		{
			free(text);
			text = NULL;
		}
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	text = leer(fd, text);
	if (!text)
		return (NULL);
	line = obtain_line(text);
	text = clean_text(text);
	return (line);
}
