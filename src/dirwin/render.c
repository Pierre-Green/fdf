/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:37:36 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/22 16:21:01 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirwin.h"
#include "fdf.h"
#include <mlx.h>
#include "ft_math/dim.h"
#include "ft_math/point.h"

static t_container			*getlayout(t_fdf *fdf)
{
	t_container				*container;
	t_container				*con2;
	t_drawable				*drawable;

	container = ft_init_container((struct s_point2d){ 0, 0 }, (struct s_dim2d){ DIRWIN_WIDTH, DIRWIN_HEIGHT});
	con2 = ft_init_container((struct s_point2d){ 10, 100 }, (struct s_dim2d){125, 10});
	con2->background_color = 0xFF0000;
	drawable = malloc(sizeof(t_drawable));
	drawable->drawable = con2;
	drawable->type = CONTAINER;
	container->add_child(container, drawable);
	return (container);
}

int							fdf_selection_window_render(void *s)
{
	t_fdf					*fdf;
	t_dirwin_state			*dw_state;
	char					*value_ptr;
	int						img_cfg[3];

	fdf = (t_fdf *)s;
	// mlx_clear_window(fdf->mlx_ptr, fdf->windows->ptr);
	dw_state = fdf->state->dirwin;
	if (dw_state->img_ptr == NULL)
		dw_state->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->windows->width, fdf->windows->height);
	value_ptr = mlx_get_data_addr(dw_state->img_ptr, &img_cfg[0], &img_cfg[1], &img_cfg[2]);
	if (dw_state->container == NULL)
		dw_state->container = getlayout(fdf);
	dw_state->container->image(dw_state->container, (t_point2d){0,0}, &value_ptr);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->windows->ptr, dw_state->img_ptr, 0, 0);
	return (0);
}
