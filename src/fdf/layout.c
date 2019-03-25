/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:34:28 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/25 20:03:59 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_container				*fdf_layout(t_fdf *fdf)
{
	t_container			*page;
	// t_container			*header;
	// t_container			*body;
	t_canvas			*canvas;

	page = ft_init_container(POS(0, 0), DIM(fdf->window->width, fdf->window->height), 0xFFFFFF);
	// header = ft_init_container(POS(0, 0), DIM(fdf->window->width, 100), 0xFF0000);
	// body = ft_init_container(POS(0, 100), DIM(fdf->window->width, fdf->window->height - 100), 0xFF00FF);
	canvas = mlx_init_canvas(POS(0, 0), DIM(fdf->window->width, fdf->window->height));
	canvas->background_color = 0xF2F2F2;
	canvas->s = fdf;
	canvas->image = fdf_image;

	page->add_child(page, ft_init_drawable(CANVAS, canvas));
	// page->add_child(page, ft_init_drawable(CONTAINER, header));
	// page->add_child(page, ft_init_drawable(CONTAINER, body));
	// body->add_child(body, ft_init_drawable(CANVAS, canvas));
	return (page);
}
