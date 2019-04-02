/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:22:29 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/02 19:19:13 by pguthaus         ###   ########.fr       */
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
	state->camera = mlx_init_camera(ft_init3_vec3_d(1, -5.71, 6.29));
	state->camera->update(state->camera);
	state->camera->rotation_velocity *= 8;
	state->camera->pitch = -78;
	state->camera->yaw = 269;
	state->last = POS(-42, -42);
	state->motion_focus = FALSE;
	state->theme = fdf->themes->themes[0];
	state->selected_theme = 0;
	return (state);
}

t_ret					fdf_window_init(t_fdf *fdf, t_window *dest)
{
	if (!(fdf->state->fdf = fdf_state(fdf)))
		return (RET_ERROR_500);
	dest->body = fdf_layout(fdf);
	dest->should_render_every_frame = FALSE;
	return (RET_OK);
}
