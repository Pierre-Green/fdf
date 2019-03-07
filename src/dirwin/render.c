/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:37:36 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/07 03:17:49 by pierre           ###   ########.fr       */
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
	t_container				*body;
	t_container				*header;
	t_text					*title;

	(void)fdf;
	body = ft_init_container(POS(0, 0), DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT), 0x4D2028);
	header = ft_init_container(POS(0, 0), DIM(DIRWIN_WIDTH, 100), 0x724F5B);
	title = ft_init_text(POS(DIRWIN_WIDTH / 2, 50), "Choisissez votre carte !", 0xFFFFFF);
	header->add_child(header, ft_init_drawable(TEXT, title));
	body->add_child(body, ft_init_drawable(CONTAINER, header));
	return (body);
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
