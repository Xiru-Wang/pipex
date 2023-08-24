/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:03:06 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/24 18:54:52 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_err(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// char	*ft_strdup(const char *s)
// {
// 	char	*ret;
// 	size_t	len;

// 	len = ft_strlen(s) + 1;
// 	ret = (char *)malloc(len * sizeof(char));
// 	if (ret == NULL)
// 		return (NULL);
// 	ft_strlcpy(ret, s, len);
// 	return (ret);
// }

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t			i;
	size_t			k;
	unsigned char	*ret;

	i = 0;
	if (*s2 == 0)
		return ((char *)s1);
	ret = (unsigned char *)s1;
	while (ret[i] && i < len)
	{
		k = 0;
		if (ret[i] == s2[k])
		{
			while (ret[i + k] == s2[k] && i + k < len)
			{
				k++;
				if (s2[k] == 0)
					return (&((char *)s1)[i]);
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}
