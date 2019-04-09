/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:22:29 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/09 15:49:11 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_mlx/window.h"
#include <stdio.h>

static t_fdf_state		*fdf_state(t_fdf *fdf)
{
	t_fdf_state			*state;

	(void)fdf;
	if (!(state = (t_fdf_state *)malloc(sizeof(t_fdf_state))))
		return (NULL);
	state->camera = mlx_init_camera(ft_init3_vec3_d(-0.5, 0.5, -1.8));
	state->camera->rotation = (t_vec3_d){ 45, 20, 0 };
	state->camera->update(state->camera);
	state->camera->rotat_velocity *= 8;
	state->last = POS(-42, -42);
	state->motion_focus = FALSE;
	state->theme = fdf->themes->themes[0];
	state->selected_theme = 0;
	return (state);
}

static void				fdf_normalize_map(t_fdf *fdf)
{
	t_point2d			pos;
	int					at;

	pos.y = 0;
	while (pos.y < (int)fdf->map->depth)
	{
		pos.x = 0;
		while (pos.x < (int)fdf->map->width)
		{
			at = (pos.y * fdf->map->width) + pos.x;
			fdf->map->vecs[at] = ft_vec3_d_div(fdf->map->vecs[at],
					ft_init3_vec3_d(fdf->map->width - 1, fdf->map->height, fdf->map->depth - 1));
			pos.x++;
		}
		pos.y++;
	}
}

t_ret					fdf_window_init(t_fdf *fdf, t_window *dest)
{
	if (!(fdf->state->fdf = fdf_state(fdf)))
		return (RET_ERROR_500);
	if (fdf_init_config(fdf) == RET_ERROR_500)
		return (RET_ERROR_500);
	fdf_normalize_map(fdf);
	dest->body = fdf_layout(fdf);
	dest->should_render_every_frame = FALSE;
	return (RET_OK);
}
