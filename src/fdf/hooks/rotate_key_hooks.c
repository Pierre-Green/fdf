/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_key_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:09:50 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/02 17:40:05 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_press_arrow_left(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_rotate(cam, YAW_LEFT);
}

void				fdf_press_arrow_up(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_rotate(cam, PITCH_UP);
}

void				fdf_press_arrow_right(void *s)
{

	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_rotate(cam, YAW_RIGHT);
}

void				fdf_press_arrow_down(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_rotate(cam, PITCH_DOWN);
}
