/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:02:31 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/25 19:55:02 by xiruwang         ###   ########.fr       */
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

void	handle_err(char *str);
char	**call_awk(char *av);
void	close_pipe(int *fd);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free(char **arr);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	**ft_split(char const *s, char c);

#endif
