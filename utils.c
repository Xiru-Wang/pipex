/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:03:06 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/21 19:51:23 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s) + 1;
	ret = (char *)malloc(len * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s, len);
	return (ret);
}

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
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (*s2 == 0)
		return ((char *)s1);
	while (*s2 && *s1 && len > 0)
	{
		while (s1[i + k] == s2[k] && len--)
			k++;
		if (s2[k] == '\0')
			return ((char *)&s1[i]);
		i++;
		len--;
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
