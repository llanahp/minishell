/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:43:41 by ralopez-          #+#    #+#             */
/*   Updated: 2022/09/24 12:43:42 by ralopez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_calloc_gnl(size_t count, size_t size);
void	ft_bzero_gnl(void *s, size_t n);
size_t	ft_strlen_gnl(const char *c);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_strchr_gnl(const char *s, int c);
#endif
