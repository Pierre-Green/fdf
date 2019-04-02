/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:22:48 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/02 18:16:12 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include "ft_utils.h"

static t_map		*add_vec(t_fdf *fdf, t_vec3_d vec)
{
	t_map			*map;
	size_t			curr;

	if (fdf->map->len < fdf->map->capacity)
	{
		map = fdf->map;
		map->vecs[map->len] = vec;
		map->len++;
	}
	else
	{
		if (!(map = malloc(sizeof(t_map) + (sizeof(t_vec3_d)
							* fdf->map->capacity << 1))))
			return (NULL);
		map->len = fdf->map->len;
		map->capacity = fdf->map->capacity << 1;
		map->name = fdf->map->name;
		map->width = fdf->map->width;
		map->depth = fdf->map->depth;
		curr = 0;
		while (curr < map->len)
		{
			map->vecs[curr] = fdf->map->vecs[curr];
			curr++;
		}
		ft_memdel((void **)&fdf->map);
		fdf->map = map;
		add_vec(fdf, vec);
	}
	return (map);
}

static t_ret		parse_line(t_fdf *fdf, char *line)
{
	t_map			*map;
	size_t			x;
	int				y;

	x = 0;
	map = fdf->map;
	while (*line)
	{
		if (*line != '-' && !ft_isdigit(*line))
			return (RET_ERROR_PARSE);
		y = ft_atoi_consume(&line);
		fdf->map = add_vec(fdf, (t_vec3_d){x, y * 0.1, map->depth});
		while (*line && *line == ' ')
			line++;
		x++;
	}
	if (x < map->width || map->width == 0)
		map->width = x;
	return (RET_OK);
}

static t_ret		parser_compute(t_fdf *fdf)
{
	int				gnl_res;
	char			*buff;

	while ((gnl_res = get_next_line(fdf->fd, &buff)) > 0)
	{
		parse_line(fdf, buff);
		free(buff);
		fdf->map->depth++;
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
