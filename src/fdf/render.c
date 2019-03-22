/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:18 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/22 20:29:58 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void					draw_vecs(t_canvas *canvas, t_fdf *fdf, t_matrix44_d trans)
{
	size_t				x;
	size_t				y;
	t_vec3_d			transformed;
	const t_map			*map = fdf->map;

	y = 0;
	while (y < map->depth)
	{
		x = 0;
		while (x < map->width)
		{
			transformed = ft_vec3_d_matmut(map->vecs[x + (y * map->width)], trans, TRUE);
			mlx_canvas_draw_line(canvas, POS(transformed.x, transformed.y), POS(300, 300), 0x000000);
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
	t_matrix44_d		mat_trans;

	state = fdf->state->fdf;
	add_hooks(canvas, s);
	mat_trans = ft_multiply_matrix44_d(state->camera->view_mat,
			ft_perspective_matrix44_d(90, 16 / 9, 1, 11));
	draw_vecs(canvas, (t_fdf *)fdf, mat_trans);
	return (carry);
}
