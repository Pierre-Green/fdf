/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:43:52 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/22 19:48:15 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_press_w(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam =fdf->state->fdf->camera;
	mlx_camera_move(cam, FORWARD);
}

void				fdf_press_a(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam =fdf->state->fdf->camera;
	mlx_camera_move(cam, LEFTWARD);
}

void				fdf_press_s(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam =fdf->state->fdf->camera;
	mlx_camera_move(cam, BACKWARD);

}

void				fdf_press_d(void *s)
{
	const t_fdf		*fdf = s;
	t_camera		*cam;
	
	cam =fdf->state->fdf->camera;
	mlx_camera_move(cam, RIGHTWARD);
}
