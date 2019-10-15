/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jterrell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:34:34 by jterrell          #+#    #+#             */
/*   Updated: 2019/10/10 13:34:35 by jterrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int 	check1(char *tetra)
{
	int 	i;
	int 	count;

	count = 0;
	i = 0;
	while (tetra[i])
	{
		if (tetra[i] == '#')
		{
			if (i + 1 <= 20 && tetra[i + 1] == '#')
				count++;
			if (i - 1 >= 0 && tetra[i - 1] == '#')
				count++;
			if (i + 5 <= 20 && tetra[i + 5] == '#')
				count++;
			if (i >= 5 && tetra[i - 5] == '#')
				count++;
		}
		i++;
	}
	return ((count == 6) || (count == 8));
}

int 	check(char *tetra, int size)
{
	int 	i;
	int 	count;

	count = 0;
	i = 0;
	if (!(size == 21 || size == 20))
		return (0);
	while (i < 20)
	{
		if (i % 5 == 4)
		{
			if (tetra[i] != '\n')
				return (0);
		}
		else
		{
			if (!(tetra[i] == '#' || tetra[i] == '.'))
				return (0);
			if (tetra[i] == '#' && ++count > 4)
				return (0);
		}
		i++;
	}
	if (tetra[20] != '\n' && size == 21)
		return(0);
	return(check1(tetra));
}

void    extreme(char *tetra, t_point *max, t_point *min)
{
    int			i;

    i = 0;
    while (i < 20)
    {
        if (tetra[i] == '#')
        {
            if (i / 5 < min->y)
                min->y = i / 5;
            if (i % 5 < min->x)
                min->x = i % 5;
            if (i / 5 > max->y)
                max->y = i / 5;
            if (i % 5 > max->x)
                max->x = i % 5;
        }
        i++;
    }
    //printf("tetra = \n%s\nmax = %d %d,  min = %d %d\n", tetra, max->x, max->y, min->x, min->y);
}

t_tetra    *do_map(char *buf, char L)
{
    t_point *max;
    t_point *min;
    char    **mass;
    int     i;
    t_tetra *tetroming;

    i = 0;
    min = init_point(3,3);
    max = init_point(0,0);
    extreme(buf, max, min);
    //printf("tetra = \n%s\nmax = %d %d,  min = %d %d\n", buf, max->x, max->y, min->x, min->y);
    if (!(mass = (char**)malloc(sizeof(char*) * (max->y - min->y + 1))))
        return (NULL);
    while (i < max->y - min->y + 1)
    {
        mass[i] = ft_strnew(max->x - min->x + 1);
        ft_strncpy(mass[i], buf + min->x + (min->y + i) * 5, max->x - min->x + 1);
        i++;
    }
    if (!(tetroming = new_tetra( max->x - min->x + 1, max->y - min->y + 1, L, mass)))
        return (NULL);
    ft_memdel((void**)&min);
    ft_memdel((void**)&max);
    return (tetroming);
}

t_list	*read_map(int fd)
{
	char	one_tetra[22];
	int 	i;
    t_tetra	*ptr;
    char    L;
    t_list  *head;

    L = 'A';
	i = 0;
	head = NULL;
	while ((i = read(fd, one_tetra, 21)))
	{
		one_tetra[i] = 0;
		if (!check(one_tetra, i))
			return (0);
		else
        {
		    if (!(ptr = do_map(one_tetra, L++)))
		        return (free_ist(&head));
            ft_lst_pushback(&head, ft_lstnew(ptr, sizeof(t_tetra)));
		}
	}
	if (ft_strlen(one_tetra) != 20)
	    return (NULL);
//printf("\nheight %d, weight %d\n", tetra->h, tetra->w);
	return(head);
}