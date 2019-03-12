/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:34:28 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/12 18:25:59 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_container	*getlayout(t_fdf *fdf)
{
	t_container		*body;
	t_container		*header;
	t_canvas		*canvas;

	body = ft_init_container(POS(0, 0), DIM(fdf->window->width, fdf->window->height), 0xFFFFFF);
	header = ft_init_container(POS(0, 0), DIM(fdf->window->width, 100), 0xFF0000);
	canvas = mlx_init_canvas(POS(0, 100), DIM(fdf->window->width, fdf->window->height - 100), (void *)0, fdf->mlx_ptr, fdf);

	body->add_child(body, ft_init_drawable(CONTAINER, header));
	body->add_child(body, ft_init_drawable(CANVAS, canvas));
	return (body);
}

int					fdf_window_render(t_window *win, void *s)
{
	
	t_fdf					*fdf;
	t_fdf_state			*fdf_state;

	fdf = (t_fdf *)s;
	mlx_clear_window(win->mlx, win->ptr);
	fdf_state = fdf->state->fdf;
	if (fdf_state->body == NULL)
		fdf_state->body = getlayout(fdf);
	fdf_state->imgcarry = fdf_state->body->render(fdf_state->body, win->mlx, win, fdf_state->imgcarry);
	return (0);
}
