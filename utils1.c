/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:00:20 by xiwang            #+#    #+#             */
/*   Updated: 2023/08/28 19:00:30 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_err(char *str)
{
	perror(str);
	exit(2);
}

char	**call_awk(char *av)
{
	char		**cmd;
	size_t		i;
	size_t		k;

	cmd = (char **)malloc(3 * sizeof(char *));
	cmd[0] = ft_strdup("awk");
	if (av[4] == av[ft_strlen(av) - 1])
	{
		if (av[4] == '\'' && av[5] == '\"')
		{
			ft_free(cmd);
			return (NULL);
		}
		i = 5;
		k = 0;
		cmd[1] = (char *)malloc(sizeof(char) * (ft_strlen(av) - 4));
		while (av[i] && i < (ft_strlen(av) - 1))
			cmd[1][k++] = av[i++];
		cmd[1][k] = 0;
		cmd[2] = NULL;
		return (cmd);
	}
	handle_err("awk: syntax error");
	return (NULL);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

// < input grep Hello | awk "'{count++} END {print count}'" > output
//Bash standard stream:
// awk: syntax error at source line 1
//  context is
// 	 >>> ' <<<
// awk: bailing out at source line 1
//< input grep Hello | awk '"{count++} END {print count}"' > output
//print 1st cmd
