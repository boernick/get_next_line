/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:35:39 by nboer             #+#    #+#             */
/*   Updated: 2024/07/01 18:33:41 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static size_t	get_length_dest(char *dest, size_t size)
{
	size_t	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	if (i < size)
		return (i);
	else
		return (size);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	l_dest;
	size_t	l_src;
	size_t	j;

	j = 0;
	l_dest = get_length_dest(dest, size);
	l_src = ft_strlen(src);
	if (size > l_dest)
	{
		while (src[j] != '\0' && ((l_dest + j) < (size - 1)))
		{
			dest[l_dest + j] = src[j];
			j++;
		}
		dest[l_dest + j] = '\0';
	}
	return (l_dest + l_src);
}

char	*ft_strdup(const char *str)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(str);
	p = (char *) malloc((len + 1) * sizeof(char));
	if (p != NULL)
	{
		while (i < len)
		{
			p[i] = str[i];
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != (char)c)
	{
		if (!*str++)
			return (0);
	}
	return ((char *)str);
}
