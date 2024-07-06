/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:35:32 by nboer             #+#    #+#             */
/*   Updated: 2024/07/06 17:53:34 by nboer            ###   ########.fr       */
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
				printf("%i\n", len);
				return (len);
			}
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

void	copy_line(t_list *lst, char *line)
{
	int	i;
	int	j;
	
	j = 0;
	if(!lst)
		return ;
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
char	*get_line(t_list *lst) //removed a * before every lst in this function
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
	//split_line(*lst, line);
	return (line);
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
		templst = templst->next; //use a templist to traverse the linkedlist.
	templst->next = new_node; // assign the new node to the last pointer - that was pointing to null before.
	//printf("%s\n", new_node->buf);
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
		bytes_read = read(fd, buffer, BUFFER_SIZE); // read FROM the file descriptor, INTO the buffer variable.. a BUFFER_SIZE amount of bytes.
		if (bytes_read <= 0) // if reached the end of document
		{
			free(buffer);
			return ;
		}
		buffer[BUFFER_SIZE] = '\0'; //null terminate the written bytes
		add_newnode_to_back(lst, buffer);
	}
	return ;
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
	next_line = get_line(lst); //CHANGE: FROM &LIST
	return (next_line);
}
