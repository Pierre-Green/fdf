/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:22:48 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/13 21:54:39 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include "ft_utils.h"

static t_ret		parse_line(t_map *map, char *line)
{
	t_vec3_d		*vec;
	size_t			x;
	int				y;

	x = 0;
	while (*line)
	{
		if (*line != '-' && !ft_isdigit(*line))
			return (RET_ERROR_PARSE);
		y = ft_atoi_consume(&line);
		if (*line != ' ')
			return (RET_ERROR_PARSE);
		if (!(vec = malloc(sizeof(t_vec3_d))))
			return (RET_ERROR_500);
		vec->y = y;
		vec->x = x;
		vec->z = map->depth;
		if (!map->vecs)
			map->vecs = ft_lstnew(vec, sizeof(vec));
		else
			ft_lstadd(&map->vecs, ft_lstnew(vec, sizeof(vec)));
		line++;
		x++;
	}
	if (x < map->width || map->width == 0)
		map->width = x;
	return (RET_OK);
}

static t_ret		parser_compute(t_fdf *fdf)
{
	t_map			*map;
	int				gnl_res;
	char			*buff;

	map = fdf->map;
	while ((gnl_res = get_next_line(fdf->fd, &buff)) > 0)
	{
		parse_line((t_map *)map, buff);
		free(buff);
		map->depth++;
	}
	free(buff);
	fdf->window = ft_init_window(fdf->mlx_ptr, DIM(1500, 1000), fdf->map->name, fdf);
	fdf_window_init(fdf, fdf->window);
	fdf->window->render(fdf->window);
	return (RET_OK);
}

t_ret				parse(t_fdf *fdf)
{
	char			filename[255];
	size_t			len;
	size_t			tmp;

	if (fdf->mapmode == FOLDER)
	{
		len = 0;
		while (fdf->params->at(fdf->params, 1)->value[len])
		{
			filename[len] = fdf->params->at(fdf->params, 1)->value[len];
			len++;
		}
		filename[len++] = '/';
		tmp = 0;
		while (fdf->map->name[tmp])
			filename[len++] = fdf->map->name[tmp++];
		filename[len] = '\0';
		if ((fdf->fd = open(filename, O_RDONLY)) < 0)
			return (RET_ERROR_500);
	}
	return (parser_compute(fdf));
}
