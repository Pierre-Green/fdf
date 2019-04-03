/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:20:18 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/03 20:40:04 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <sys/param.h>

static t_bool			vec3d_2_vec2d(t_fdf *fdf, t_canvas *canvas, t_vec3_d vec, t_vec3_d *dest)
{
	(void)canvas;
	*dest = vec;
	return (TRUE);
}

static void				compute_pos(t_fdf *fdf, t_point2d at, t_canvas *canvas)
{
	t_vec3_d			from;
	t_vec3_d			to;
	size_t				i;

	i = (at.y * fdf->map->width) + at.x;
	if (!(vec3d_2_vec2d(fdf, canvas, fdf->map->vecs[i], &from)))
		return ;
	if ((at.x + 1 < (int)fdf->map->width) && (vec3d_2_vec2d(fdf, canvas, fdf->map->vecs[i + 1], &to)))
		mlx_canvas_draw_line(canvas, POS(from.x, from.y), POS(to.x, to.y), fdf->state->fdf->theme.line_color);
	if ((at.y + 1 < (int)fdf->map->depth) && (vec3d_2_vec2d(fdf, canvas, fdf->map->vecs[i + fdf->map->width], &to)))
		mlx_canvas_draw_line(canvas, POS(from.x, from.y), POS(to.x, to.y), fdf->state->fdf->theme.line_color);
}

t_image_carry			*fdf_image(t_canvas *canvas, void *s, t_image_carry *carry)
{
	const t_fdf			*fdf = s;
	t_fdf_state			*state;
	t_point2d			pos;

	state = fdf->state->fdf;
	add_hooks(canvas, s);
	pos = POS(-1, -1);
	while (++pos.y < (int)fdf->map->depth)
	{
		pos.x = -1;
		while (++pos.x < (int)fdf->map->width)
			compute_pos((t_fdf *)fdf, pos, canvas);
	}
	return (carry);
}
