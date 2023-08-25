#include "pipex.h"

void	handle_err(char *str)
{
	perror(str);
	exit(2);
}

char	**call_awk(char *av)
{
	char	**cmd;
	int		i;
	int		k;
	int		len;

	cmd = (char **)malloc(3 * sizeof(char *));
	cmd[0] = ft_strdup("awk");
	len = ft_strlen(av);
	if (av[4] == av[len - 1])
	{
		if (av[4] == '\'' && av[5] == '\"')
		{
			ft_free(cmd);
			return (NULL);//print the 1st cmd
		}
		i = 5;
		k = 0;
		cmd[1] = (char *)malloc(sizeof(char) * (len - 4));
		while (av[i] && i < (len - 1))
		{
			cmd[1][k] = av[i];
			i++;
			k++;
		}
		cmd[1][k] = 0;
		cmd[2] = NULL;
		return (cmd);
	}
	else
	{
		perror("awk: syntax error");
		exit(2);
	}
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
