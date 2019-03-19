/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:34:28 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/18 21:53:40 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_image_carry	*fdf_image(t_canvas *canvas, void *s, t_image_carry *carry)
{
	const t_fdf			*fdf = s;
	const t_fdf_state	*state = fdf->state->fdf;
	
	size_t y = 10;
	while (y < 50)
	{
		size_t x = 0;
		while (x < 50)
		{
			ft_put_pixel_to_image(carry, x, y, 0xFF0000);
			x++;
		}
		y++;
	}

	return (carry);
}

t_container				*fdf_layout(t_fdf *fdf)
{
	t_container			*page;
	t_container			*header;
	t_container			*body;
	t_canvas			*canvas;

	page = ft_init_container(POS(0, 0), DIM(fdf->window->width, fdf->window->height), 0xFFFFFF);
	header = ft_init_container(POS(0, 0), DIM(fdf->window->width, 100), 0xFF0000);
	body = ft_init_container(POS(0, 100), DIM(fdf->window->width, fdf->window->height - 100), 0xFF00FF);
	canvas = mlx_init_canvas(POS(0, 0), DIM(fdf->window->width, fdf->window->height - 100));
	canvas->s = fdf;
	canvas->image = fdf_image;

	page->add_child(page, ft_init_drawable(CONTAINER, header));
	page->add_child(page, ft_init_drawable(CONTAINER, body));
	body->add_child(body, ft_init_drawable(CANVAS, canvas));
	return (page);
}
