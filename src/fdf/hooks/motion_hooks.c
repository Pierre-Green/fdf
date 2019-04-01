/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:57:22 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/27 19:09:06 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_motion(int x, int y, void *s)
{
	const t_fdf		*fdf = s;
	t_fdf_state		*state;

	state = fdf->state->fdf;
	if (!state->motion_focus)
		return ;
	if (state->last.x == -42 && state->last.y == -42)
		state->last = POS(x, y);
	mlx_camera_mouse(state->camera, x - state->last.x, y - state->last.y);
	state->last = POS(x, y);
}
