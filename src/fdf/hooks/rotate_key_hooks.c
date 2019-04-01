/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_key_hooks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:09:50 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/27 20:16:40 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_press_arrow_left(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_mouse(cam, -5, 0);
}

void				fdf_press_arrow_up(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_mouse(cam, 0, 5);
}

void				fdf_press_arrow_right(void *s)
{

	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_mouse(cam, 5, 0);
}

void				fdf_press_arrow_down(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam = fdf->state->fdf->camera;
	mlx_camera_mouse(cam, 0, -5);
}
