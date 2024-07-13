/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboer <nboer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:36:42 by nboer             #+#    #+#             */
/*   Updated: 2024/07/13 21:27:39 by nboer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;
	int i;
	printf("%s%i\n", "buf size: ", BUFFER_SIZE);

    // Open the file 'text.txt' for reading
    fd = open("text.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("%s\n", "Error opening file");
        return 1;
    }
	i = 0;
	while (i < 7)
	{
		line = get_next_line(fd);
		printf("%s", line);  // Print the line read
		if (line == NULL)
			printf("\n");
		free(line);
		i++;
	}

    // while ((line = get_next_line(fd)) != NULL)
    // {
    //     printf("%s\n", line);  // Print the line read
    //     free(line);            // Free the memory allocated by get_next_line
    // }

    // Close the file descriptor
    close(fd);

	return 0;
}
