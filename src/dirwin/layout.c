/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:37:36 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/21 15:41:17 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirwin.h"
#include "fdf.h"
#include <mlx.h>
#include "ft_math/dim.h"
#include "ft_math/point.h"
#include "ft_mlx/drawables.h"
#include "ft_printf.h"
#include "ft_str.h"

static void		onclick(int mouse, int target, void *state)
{
	t_fdf		*fdf;
	size_t		selector;
	t_dfiles	*node;

	(void)mouse;
	fdf = state;
	selector = 0;
	node = fdf->state->dirwin->files;
	while (selector < (size_t)target)
	{
		node = node->next;
		selector++;
	}
	fdf->map->name = node->file->d_name;
	parse(fdf);
}

static t_pagination			*getpagination(t_fdf *fdf)
{
	t_pagination			*pagination;
	t_dfiles				*node;
	t_button				*button;
	size_t					current;

	pagination = mlx_init_pagination(ft_zone2d_from_pdim(POS(0, 0), DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT - 100)), DIM(192, 108), (t_margin){10, 10, 10, 10});
	current = 0;
	node = fdf->state->dirwin->files;
	while (current < fdf->state->dirwin->items_count && node)
	{
		button = mlx_init_button(POS(0, 0), DIM(192, 108), 0x724F5B, node->file->d_name);
		button->uuid = current;
		button->onclick = onclick;
		pagination->add_child(pagination, ft_init_drawable(BUTTON, button));
		node = node->next;
		current++;
	}
	return (pagination);
}

t_container					*dirwin_layout(t_fdf *fdf)
{
	t_container				*page;
	t_container				*header;
	t_container				*body;
	t_text					*title;

	page = ft_init_container(POS(0, 0), DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT), 0x4D2028);

	header = ft_init_container(POS(0, 0), DIM(DIRWIN_WIDTH, 100), 0x724F5B);
	title = ft_init_text(POS(DIRWIN_WIDTH / 2, 50), "Choisissez votre carte !", 0xFFFFFF);
	title->align = CENTER;
	header->add_child(header, ft_init_drawable(TEXT, title));

	body = ft_init_container(POS(0, 100), DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT - 100), 0x4D2028);
	body->add_child(body, ft_init_drawable(PAGINATION, getpagination(fdf)));

	page->add_child(page, ft_init_drawable(CONTAINER, body));
	page->add_child(page, ft_init_drawable(CONTAINER, header));
	return (page);
}
