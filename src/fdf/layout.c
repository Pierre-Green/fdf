/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:34:28 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/02 18:49:32 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_container		*header(t_fdf *fdf, t_theme theme)
{
	t_container			*header;

	header = ft_init_container(POS(0, 0), DIM(fdf->window->width, 100), theme.ui_background);
	return (header);
}

static t_container		*body(t_fdf *fdf, t_theme theme)
{
	t_container			*body;
	t_canvas			*canvas;

	body = ft_init_container(POS(0, 100), DIM(fdf->window->width, fdf->window->height - 200), 0x000000);
	canvas = mlx_init_canvas(POS(0, 0), DIM(fdf->window->width, fdf->window->height - 200));
	canvas->s = fdf;
	canvas->background_color = theme.canvas_color;
	canvas->image = fdf_image;
	body->add_child(body, ft_init_drawable(CANVAS, canvas));
	return (body);
}

static t_container		*footer(t_fdf *fdf, t_theme theme)
{
	t_container			*footer;

	footer = ft_init_container(POS(0, fdf->window->height - 100), DIM(fdf->window->width, 100), theme.ui_background);
	return (footer);
}

t_container				*fdf_layout(t_fdf *fdf)
{
	t_container			*page;
	const t_theme		theme = fdf->state->fdf->theme;

	page = ft_init_container(POS(0, 0), DIM(fdf->window->width, fdf->window->height), 0xFFFFFF);
	page->add_child(page, ft_init_drawable(CONTAINER, header(fdf, theme)));
	page->add_child(page, ft_init_drawable(CONTAINER, body(fdf, theme)));
	page->add_child(page, ft_init_drawable(CONTAINER, footer(fdf, theme)));
	return (page);
}
