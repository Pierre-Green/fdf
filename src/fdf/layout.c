/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:34:28 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/13 21:55:03 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_container			*fdf_layout(t_fdf *fdf)
{
	t_container		*body;
	t_container		*header;
	t_canvas		*canvas;

	body = ft_init_container(POS(0, 0), DIM(fdf->window->width, fdf->window->height), 0xFFFFFF);
	header = ft_init_container(POS(0, 0), DIM(fdf->window->width, 100), 0xFF0000);
	canvas = mlx_init_canvas(POS(0, 100), DIM(fdf->window->width, fdf->window->height - 100), (void *)0, fdf->mlx_ptr);
	canvas->s = fdf;

	body->add_child(body, ft_init_drawable(CONTAINER, header));
	body->add_child(body, ft_init_drawable(CANVAS, canvas));
	return (body);
}
