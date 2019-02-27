/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:37:36 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/25 18:40:51 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirwin.h"
#include "fdf.h"
#include <mlx.h>
#include "ft_math/dim.h"
#include "ft_math/point.h"
#include "ft_mlx/drawables.h"
#include "ft_printf.h"

static t_container			*getlayout(t_fdf *fdf)
{
	t_container				*container;
	t_drawable				*child;
	t_container				*container2;

	(void)fdf;
	container = ft_init_container((struct s_point2d){ 0, 0 }, (struct s_dim2d){ DIRWIN_WIDTH, DIRWIN_HEIGHT});
	container->background_color = 0xFFFFFF;

	if(!(child = malloc(sizeof(t_drawable))))
		return (NULL);
	container2 = ft_init_container((struct s_point2d){ 170, 80 }, (struct s_dim2d){ 370, 123 });
	container2->background_color = 0x00FF00;
	child->drawable = container2;
	child->type = CONTAINER;
	container->add_child(container, child);
	return (container);
}

int							fdf_selection_window_render(void *s)
{
	t_fdf					*fdf;
	t_dirwin_state			*dw_state;
	char					*value_ptr;
	int						img_cfg[3];
	t_image_carry			*carry;

	fdf = (t_fdf *)s;
	// mlx_clear_window(fdf->mlx_ptr, fdf->windows->ptr);
	dw_state = fdf->state->dirwin;
	if (dw_state->img_ptr == NULL)
		dw_state->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->windows->width, fdf->windows->height);
	value_ptr = mlx_get_data_addr(dw_state->img_ptr, &img_cfg[0], &img_cfg[1], &img_cfg[2]);
	if (dw_state->container == NULL)
		dw_state->container = getlayout(fdf);
	carry = ft_image_carry_from(&value_ptr, img_cfg[0], img_cfg[1], img_cfg[2]);
	dw_state->container->image(dw_state->container, (t_point2d){0,0}, carry);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->windows->ptr, dw_state->img_ptr, 0, 0);
	return (0);
}
