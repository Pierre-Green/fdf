/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:18 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/01 19:28:36 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/param.h>

static t_ret			vec2pos(t_vec3_d vec, t_fdf_state *state, t_dim2d dims, t_point2d *out)
{
	vec = ft_vec3_d_matmut(vec, state->camera->view_mat);
	vec = ft_vec3_d_matmut(vec, state->proj);
	out->x = (vec.x + (dims.width / 2));
	out->y = (vec.y + (dims.height / 2));
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
		mlx_canvas_draw_line(canvas, from, to, state->theme.line_color);
	}
	if (pos.y < (int)map->depth - 1)
	{
		vec2pos(map->vecs[pos.x + ((pos.y + 1) * map->width)], state, canvas->zone.dim, &to);
		mlx_canvas_draw_line(canvas, from, to, state->theme.line_color);
	}
}

static void				draw_vecs(t_canvas *canvas, t_fdf *fdf, t_fdf_state *state)
{
	size_t				x;
	size_t				y;
	const t_map			*map = fdf->map;

	y = 0;
	printf("cam yaw: %f pitch: %f\n", state->camera->yaw, state->camera->pitch);
	ft_vec3_d_debug(state->camera->position, "Camera position");
	ft_vec3_d_debug(state->camera->vec_front, "Vec front");
	ft_vec3_d_debug(state->camera->vec_right, "Vec right");
	ft_mat44d_debug(state->proj, "Projection mat");
	ft_mat44d_debug(state->camera->view_mat, "Camera mat");
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
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_LEFT, fdf_press_arrow_left, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_UP, fdf_press_arrow_up, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_RIGHT, fdf_press_arrow_right, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_DOWN, fdf_press_arrow_down, s);
	// canvas->mouse_hooks->add(canvas->mouse_hooks, 0, canvas->zone, fdf_click, s);
	// canvas->motion_hooks->add(canvas->motion_hooks, canvas->zone, fdf_motion, s);
}

t_image_carry			*fdf_image(t_canvas *canvas, void *s, t_image_carry *carry)
{
	const t_fdf			*fdf = s;
	t_fdf_state			*state;

	state = fdf->state->fdf;
	state->camera->update(state->camera);
	add_hooks(canvas, s);
	canvas->background_color = state->theme.background_color;
	state->proj = ft_perspective_matrix44_d(ft_degrees_to_radian(90), 0.1, 100);
	draw_vecs(canvas, (t_fdf *)fdf, state);
	return (carry);
}
