/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:03:06 by xiruwang          #+#    #+#             */
/*   Updated: 2023/08/25 14:45:13 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}
