/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:23:48 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/13 20:03:16 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirwin.h"
#include "fdf.h"
#include "ft_str.h"
#include <mlx.h>

static t_dirwin_state		*fdf_selection_window_state(t_fdf *fdf)
{
	t_dirwin_state			*dstate;

	if (!(dstate = (t_dirwin_state *)malloc(sizeof(t_dirwin_state))))
		return (NULL);
	dstate->files = ft_get_dir_files(fdf->dir, "fdf", &dstate->items_count);
	dstate->current_page = 0;
	return (dstate);
}

t_ret						fdf_selection_window(t_fdf *fdf, t_window *dest)
{
	if (!(fdf->state->dirwin = fdf_selection_window_state(fdf)))
		return (RET_ERROR_500);
	dest->body = dirwin_layout(fdf);
	dest->should_render_every_frame = false;
	return (RET_OK);
}
