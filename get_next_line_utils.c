/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:35:39 by nboer             #+#    #+#             */
/*   Updated: 2024/07/13 21:01:12 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*traverse_lst(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	get_len(t_list *lst)
{
	int		i;
	int		len;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->buf[i] != '\0')
		{
			if (lst->buf[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

int	check_line(t_list *lst)
{
	int		i;

	if (!lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->buf[i] && i < BUFFER_SIZE)
		{
			if (lst->buf[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

void	copy_line(t_list *lst, char *line)
{
	int	i;
	int	j;

	if (!lst)
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->buf[i] != '\0')
		{
			if (lst->buf[i] == '\n')
			{
				line[j] = '\n';
				j++;
				line[j] = '\0';
				return ;
			}
			line[j] = lst->buf[i];
			i++;
			j++;
		}
		lst = lst->next;
	}
	line[j] = '\0';
}

void	get_remainder(t_list **lst)
{
	char	*buf;
	int		i;
	int		j;
	t_list	*last_node;
	t_list	*new_node;

	buf = malloc(BUFFER_SIZE + 1);
	new_node = malloc(sizeof(t_list));
	if (!buf || !new_node)
		return ;
	last_node = traverse_lst(*lst);
	i = 0;
	j = 0;
	while (last_node->buf[i] && last_node->buf[i] != '\n')
		++i;
	while (last_node->buf[i] && last_node->buf[++i])
		buf[j++] = last_node->buf[i];
	buf[j] = '\0';
	new_node->buf = buf;
	new_node->next = NULL;
	format_lst(buf, lst, new_node);
}
