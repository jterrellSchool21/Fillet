#include "fillit.h"

int     solve(t_list *ist, t_map *map)
{
    int     i;
    int     j;
    t_tetra *now_tetra;

    if (!ist)
        return (0);
    now_tetra = (t_tetra*)ist->content;
    i = 0;
    while (i < map->size - now_tetra->h + 1)
    {
        j = 0;
        while (j < map->size - now_tetra->w + 1)
        {
            if (check_map(map, now_tetra, i, j))
            {
                if (!solve(ist->next, map))
                    return (0);
                else
                    put_to_this_map(map, i, j, now_tetra, '.');
            }
            j++;
        }
        i++;
    }
    return (1);
}

t_map   *new_map(int size)
{
    t_map   *map;
    int     i;
    int     j;

    if(!(map = (t_map*)malloc(sizeof(t_map))))
        return (NULL);
    i = 0;
    map->size = size;
    if(!(map->map = (char**)malloc(sizeof(char*) * size)))
        return (NULL);
    while (i < size)
    {
        j = 0;
        if (!(map->map[i] = (char*)malloc(sizeof(char) * size)))
            return (free_map(map, size));
        while (j < size)
        {
            map->map[i][j] = '.';
            j++;
        }
        i++;
    }
    return (map);
}

int 	ft_list_len(t_list *list)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = list;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int 	ft_square_size(int n)
{
	int		size;

	size = 0;
	while (size * size < n * 4)
		size++;
	return (size);
}

t_map	*try(t_list *ist)
{
	int 	size;
    t_map   *map;

	size = ft_square_size(ft_list_len(ist));
    map = new_map(size);
    while (solve(ist, map))
    {
        free_map(map, size);
        size++;
        map = new_map(size);
    }
    return (map);
}