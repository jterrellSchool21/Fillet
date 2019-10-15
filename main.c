/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:34:16 by jterrell          #+#    #+#             */
/*   Updated: 2019/10/10 13:34:17 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void    put_to_this_map(t_map *map, int i, int j, t_tetra *tetra, char L)
{
    int     k;
    int     t;

    k = 0;
    while (k < tetra->h)
    {
        t = 0;
        while (t < tetra->w)
        {
            if (tetra->tetra[k][t] == '#')
                map->map[i + k][j + t] = L;
            t++;
        }
        k++;
    }
    //print_map(map);
    //printf("               \n\n");
}

int     check_map(t_map *map, t_tetra *tetra, int i, int j)
{
    int     k;
    int     t;

    k = 0;
    while (k < tetra->h)
    {
        t = 0;
        while (t < tetra->w)
        {
            if (tetra->tetra[k][t] == '#' && map->map[i + k][j + t] != '.')
                return (0);
            t++;
        }
        k++;
    }
    put_to_this_map(map, i, j, tetra, tetra->letter);
    return (1);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_list	*list;

	if (argc != 2)
	{
		ft_putstr("usage: fillit fili_name\n");
		return (1);
	}
	else
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
		{
			ft_putstr("error\n");
			return (1);
		}
		if (!(list = read_map(fd)))
		{
			ft_putstr("error\n");
			return (1);
		}
		close(fd);
	}



	/*t_tetra *ptr;
	int     i;

	while (list)
    {
	    i = 0;
        ptr = (t_tetra*)list->content;
	    while (i < ptr->h)
        {
	        printf("%s\n", ptr->tetra[i]);
	        i++;
        }
	    printf("\n");
	    list = list->next;
	    printf("w = %d h = %d L = %c\n\n", ptr->w, ptr->h, ptr->letter);
    }*/
	print_map(try(list));
    listdel(list);
	return (0);
}

void    listdel(t_list *list)
{
    t_list  *list_next;
    t_tetra *tetra;
    int     i;


    i = 0;
    while (list)
    {
        tetra = (t_tetra*)list->content;
        list_next = list->next;
        while (i < tetra->h)
        {
            free(tetra->tetra[i]);
            i++;
        }
        free(tetra);
        free(list);
        list = list_next;
    }
}

void    print_map(t_map *map)
{
    int     i;
    int     j;

    i = 0;
    while (i < map->size)
    {
        j = 0;
        while (j < map->size)
        {
            ft_putchar(map->map[i][j]);
            j++;
        }
        ft_putchar('\n');
        i++;
    }
    free_map(map , map->size);
}
