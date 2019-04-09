/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:54:14 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/09 18:45:28 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "fdf.h"

static void					on_theme_click(int mouse, int uuid, void *s)
{
	if (mouse == 1)
	{
		if (uuid == 0)
			fdf_prev_theme(s);
		else if (uuid == 1)
			fdf_next_theme(s);
	}
}

t_container					*fdf_config_theme(t_fdf *fdf, t_config_state *state)
{
	t_container				*container;
	t_button				*prev;
	t_button				*next;
	const t_theme			theme = fdf->state->fdf->theme;

	prev = mlx_init_button(POS(0, 20), DIM((state->win->width - 30) / 2, 30),
			theme.ui_background, "PREV");
	prev->set_s(prev, fdf)->set_onclick(prev, on_theme_click)->set_uuid(prev, 0);
	next = mlx_init_button(POS((state->win->width - 30) / 2, 20),
			DIM((state->win->width - 30) / 2, 30), theme.ui_background, "NEXT");
	next->set_s(next, fdf)->set_onclick(next, on_theme_click)->set_uuid(prev, 1);
	container = ft_init_container(POS(10, 10), DIM(state->win->width - 20, 50), theme.canvas_color);
	container->add_child(container, ft_init_drawable(TEXT, ft_init_text(POS(0, 0),
					"Select theme", theme.ui_background)));
	container->add_child(container, ft_init_drawable(BUTTON, prev));
	container->add_child(container, ft_init_drawable(BUTTON, next));
	return (container);
}

t_container					*fdf_config_layout(t_fdf *fdf)
{
	t_container				*page;
	const t_config_state	*state = fdf->state->config;
	const t_theme			theme = fdf->state->fdf->theme;

	page = ft_init_container(POS(0, 0),
			DIM(state->win->width, state->win->height), theme.canvas_color);
	page->add_child(page, ft_init_drawable(CONTAINER, fdf_config_theme(fdf, (t_config_state *)state)));
	return (page);
}
