/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:22:29 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/12 15:06:18 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_mlx/window.h"

static void					fdf_state(t_fdf *fdf)
{
	t_fdf_state				*state;

	state = fdf->state->fdf;
	state->body = NULL;
	state->imgcarry = NULL;
}

t_ret				fdf_window_init(t_fdf *fdf, t_window *dest)
{
	dest->render = fdf_window_render;
	if (!(fdf->state->fdf = (t_fdf_state *)malloc(sizeof(t_fdf_state))))
		return (RET_ERROR_500);
	fdf_state(fdf);
	return (RET_OK);
}
