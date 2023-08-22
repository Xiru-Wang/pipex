/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:02:31 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/21 20:14:35 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "pipex.h"
# include <unistd.h>//fork pipe access
# include <fcntl.h>//open  int open(const char *path, int oflag, ...);
# include <stdio.h>//perror
# include <stdlib.h>// malloc
# include <sys/wait.h>// waitpid

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
void	ft_free(char **arr);
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize);
char	**ft_split(char const *s, char c);

#endif
