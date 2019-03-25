/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:18 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/25 20:07:03 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/param.h>

static t_ret			vec2pos(t_vec3_d vec, t_fdf_state *state, t_dim2d dims, t_point2d *out)
{
	vec = ft_vec3_d_matmut(vec, state->camera->view_mat, TRUE);
	vec = ft_vec3_d_matmut(vec, state->proj, TRUE);
	out->x = MIN(dims.width - 1, vec.x * 150);
	out->y = MIN(dims.height - 1, vec.y * 150);
	return (RET_OK);
}

static void				draw_vec(t_canvas *canvas, t_map *map, t_fdf_state *state, t_point2d pos)
{
	t_point2d			from;
	t_point2d			to;

	if (RET_ERROR_500 == (vec2pos(map->vecs[pos.x + (pos.y * map->width)], state, canvas->zone.dim, &from)))
		return ;
	if (pos.x < (int)map->width - 1)
	{
		vec2pos(map->vecs[pos.x + 1 + (pos.y * map->width)], state, canvas->zone.dim, &to);
		mlx_canvas_draw_line(canvas, from, to, 0x0000FF);
	}
	if (pos.y < (int)map->depth - 1)
	{
		vec2pos(map->vecs[pos.x + ((pos.y + 1) * map->width)], state, canvas->zone.dim, &to);
		mlx_canvas_draw_line(canvas, from, to, 0xFF0000);
	}
}

static void				draw_vecs(t_canvas *canvas, t_fdf *fdf, t_fdf_state *state)
{
	size_t				x;
	size_t				y;
	const t_map			*map = fdf->map;

	y = 0;
	while (y < map->depth)
	{
		x = 0;
		while (x < map->width)
		{
			draw_vec(canvas, (t_map *)map, state, POS(x, y));
			x++;
		}
		y++;
	}
}

static void				add_hooks(t_canvas *canvas, void *s)
{
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_W, fdf_press_w, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_A, fdf_press_a, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_S, fdf_press_s, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_D, fdf_press_d, s);
}

t_image_carry			*fdf_image(t_canvas *canvas, void *s, t_image_carry *carry)
{
	const t_fdf			*fdf = s;
	t_fdf_state			*state;

	state = fdf->state->fdf;
	state->camera->update(state->camera);
	add_hooks(canvas, s);
	state->proj = ft_perspective_matrix44_d(ft_degrees_to_radian(90), 0.1, 100);
	draw_vecs(canvas, (t_fdf *)fdf, state);
	return (carry);
}
