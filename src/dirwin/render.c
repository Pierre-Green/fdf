/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:37:36 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/08 02:20:55 by pierre           ###   ########.fr       */
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

static void	onclick()
{
	ft_printf("Clicked \n");
}

static t_pagination			*getpagination(t_fdf *fdf)
{
	t_pagination			*pagination;
	char					c;
	char					*str;

	(void)fdf;
	pagination = mlx_init_pagination(ft_zone2d_from_pdim(POS(0, 0), DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT - 100)), DIM(192, 108), (t_margin){10, 20, 10, 20});
	c = 'A' - 1;
	str = ft_strnew(1);
	while (c <= 'Z')
	{
		str[0] = c;
		pagination->add_child(pagination, ft_init_drawable(BUTTON, mlx_init_button(POS(0, 0), DIM(192, 108), 0x724F5B, str, onclick)));
		c++;
	}
	return (pagination);
}

static t_container			*getlayout(t_fdf *fdf)
{
	t_container				*page;
	t_container				*header;
	t_container				*body;
	t_text					*title;

	(void)fdf;
	page = ft_init_container(POS(0, 0), DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT), 0x4D2028);

	header = ft_init_container(POS(0, 0), DIM(DIRWIN_WIDTH, 100), 0x724F5B);
	title = ft_init_text(POS(DIRWIN_WIDTH / 2, 50), "Choisissez votre carte !", 0xFFFFFF);
	header->add_child(header, ft_init_drawable(TEXT, title));

	body = ft_init_container(POS(0, 100), DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT - 100), 0x4D2028);
	body->add_child(body, ft_init_drawable(PAGINATION, getpagination(fdf)));

	page->add_child(page, ft_init_drawable(CONTAINER, body));
	page->add_child(page, ft_init_drawable(CONTAINER, header));
	return (page);
}

int							fdf_selection_window_render(void *s)
{
	t_fdf					*fdf;
	t_dirwin_state			*dw_state;

	fdf = (t_fdf *)s;
	// mlx_clear_window(fdf->mlx_ptr, fdf->windows->ptr);
	dw_state = fdf->state->dirwin;
	if (dw_state->container == NULL)
		dw_state->container = getlayout(fdf);
	dw_state->carry = dw_state->container->render(dw_state->container, fdf->mlx_ptr, fdf->windows, dw_state->carry);
	return (0);
}
