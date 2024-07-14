/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:35:32 by nboer             #+#    #+#             */
/*   Updated: 2024/07/14 14:25:15 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_one_line(t_list *lst)
{
	char	*line;
	int		len;

	if (!lst)
		return (NULL);
	len = get_len(lst);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	copy_line(lst, line);
	return (line);
}

void	add_newnode_to_back(t_list **lst, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = traverse_lst(*lst);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->buf = buffer;
	new_node->next = NULL;
	if (!last_node)
		*lst = new_node;
	else
		last_node->next = new_node;
}

void	format_lst(char *buf, t_list **lst, t_list *new_node) //
{
	t_list	*templst;

	if (!(*lst))
		return ;
	while (*lst)
	{
		templst = (*lst)->next;
		free((*lst)->buf);
		free(*lst);
		*lst = templst;
	}
	*lst = NULL;
	if (new_node != NULL && new_node->buf[0])
		*lst = new_node;
	else
	{
		free(buf);
		free(new_node);
	}
}

void	make_lst(t_list **lst, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!(check_line(*lst)))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			if (bytes_read < 0)
				format_lst(NULL, lst, NULL);
			return ;
		}
		buffer[bytes_read] = '\0'; 
		add_newnode_to_back(lst, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
	{
		format_lst(NULL, &lst, NULL);
		return (NULL);
	}
	make_lst(&lst, fd);
	if (!lst)
		return (NULL);
	next_line = get_one_line(lst);
	get_remainder(&lst);
	return (next_line);
}
