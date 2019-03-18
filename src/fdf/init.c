/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:22:29 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/18 21:21:43 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_mlx/window.h"

static t_fdf_state		*fdf_state(t_fdf *fdf)
{
	t_fdf_state			*state;

	(void)fdf;
	if (!(state = (t_fdf_state *)malloc(sizeof(t_fdf_state))))
		return (NULL);
	state->camera = mlx_init_camera(ft_init0_vec3_d());
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
