/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:35:32 by nboer             #+#    #+#             */
/*   Updated: 2024/06/16 14:35:37 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_line(t_list *list)
{
	char*	is_new;

	is_new = ft_strchr(list->buf, '\n');
	if (is_new == NULL)
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
	if (!(lst))
	{
		*lst = new_node;
		return ;
	}	
	// You need templst (a temporary pointer) to traverse the list so that you do not lose the reference to the head of the list (*lst). 
	// If you were to use *lst directly to traverse the list, you would end up modifying the original pointer, 
	// which would make it impossible to access the head of the list afterwards. 
	// Using a temporary pointer allows you to traverse the list without altering the original head pointer
	templst = *lst;
	while (templst->next != NULL)
		templst = templst->next;
	templst->next = new_node;
	// You don't need to free templst because it points to nodes already managed by the list. 
	// The function templst = templst->next simply moves the pointer to the next node without allocating new memory.
}
// To change the HEAD POINTER you have to use a DOUBLE POINTER: This approach follows the simple C rule: if you want to 
// modify the local variable of one function inside another function, 
// pass a pointer to that variable.
void	make_lst(t_list **lst, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!(check_line(*lst)))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, &buffer, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
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

char	*get_line(t_list *lst)
{
	char	*line;
	int		len;
	len = get_len(lst);
	line = malloc(len + 1);
	while (lst->next != NULL)
	{
		ft_strlcat(line, lst->buf, len);
		printf("%s\n", line);
		lst = lst-> next;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_list	**lst;
	char			*next_line;
	
	*next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	make_lst(lst, fd); //make a linked list
	if (lst == NULL)
		return (NULL);
	next_line = get_line(*lst);
	return (next_line);
}
