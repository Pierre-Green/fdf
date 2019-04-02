/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:34:28 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/02 19:57:27 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_str.h"

static t_container		*header(t_fdf *fdf, t_theme theme)
{
	t_container			*header;
	t_text				*title;

	header = ft_init_container(POS(0, 0), DIM(fdf->window->width, 100), theme.ui_background);
	title = ft_init_text(POS(fdf->window->width / 2, 50), ft_strjoin("FDF - ", fdf->map->name), theme.text_color);
	title->align = CENTER;
	header->add_child(header, ft_init_drawable(TEXT, title));
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
	footer->add_child(footer, ft_init_drawable(TEXT,
				ft_init_text(POS(10, 20), "MOVE: W/A/S/D", theme.text_color)));
	footer->add_child(footer, ft_init_drawable(TEXT,
				ft_init_text(POS(10, 60), "RANDOM THEME: T", theme.text_color)));
	footer->add_child(footer, ft_init_drawable(TEXT,
				ft_init_text(POS(200, 20), "Rotate camera: arrows", theme.text_color)));
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
