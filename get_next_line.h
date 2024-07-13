/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:55:30 by nboer             #+#    #+#             */
/*   Updated: 2024/07/13 20:31:51 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*buf;
	struct s_list	*next;
}					t_list;

char	*get_next_line(int fd);
char	*get_one_line(t_list *lst);
int		check_line(t_list *list);
int		get_len(t_list *lst);
void	make_lst(t_list **lst, int fd);
void	copy_line(t_list *lst, char *line);
void	add_newnode_to_back(t_list **lst, char *buffer);
void	get_remainder(t_list **lst);
void	format_lst(char *buf, t_list **lst, t_list *new_node);
t_list	*traverse_lst(t_list *lst); 

#endif
