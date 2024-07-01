/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:35:32 by nboer             #+#    #+#             */
/*   Updated: 2024/07/01 18:55:15 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_line(t_list *list)
{
	char	*is_new;
	if (list == NULL)
		return (0);
	is_new = ft_strchr(list->buf, '\n');
	if (is_new == 0)
		return (0);
	else 
		return (1);
}

void	add_newnode_to_back(t_list **lst, char *buffer)
{
	t_list	*new_node;
	t_list	*templst;

	new_node = malloc(sizeof(t_list));
	if (!lst || !new_node)
		return ;
	new_node->buf = buffer;
	new_node->next = NULL;
	if (!(*lst))
	{
		*lst = new_node;
		return ;
	}
	templst = *lst;
	while (templst->next != NULL)
		templst = templst->next;
	templst->next = new_node;
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
			return ;
		}
		buffer[BUFFER_SIZE] = '\0';
		add_newnode_to_back(lst, buffer);
	}
	return ;
}

int	get_len(t_list *lst)
{
	int		i;
	int		len;

	len = 0;
	while (lst->next != NULL)
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

char	*get_line(t_list **lst)
{
	char	*line;
	int		len;
	t_list	*next;

	len = get_len(*lst);
	line = malloc(len + 1);
	while ((*lst)->next != NULL)
	{
		ft_strlcat(line, (*lst)->buf, len);
		//printf("%s\n", line);
		next = (*lst)->next;
		free((*lst)->buf);
		free(*lst);
		*lst = next;
	}
	split_line(*lst, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*next_line;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	make_lst(&lst, fd); //make a linked list
	if (lst == NULL)
		return (NULL);
	next_line = get_line(&lst);
	return (next_line);
}
