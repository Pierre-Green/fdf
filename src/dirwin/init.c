/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:23:48 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/11 19:00:50 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dirwin.h"
# include "fdf.h"
# include "ft_str.h"
# include <mlx.h>

static void					fdf_selection_window_state(t_fdf *fdf)
{
	t_dirwin_state			*dstate;

	dstate = fdf->state->dirwin;
	dstate->files = ft_get_dir_files(fdf->dir, "fdf", &dstate->items_count);
	dstate->current_page = 0;
	dstate->carry = NULL;
	dstate->container = NULL;
}

t_ret						fdf_selection_window(t_fdf *fdf, t_window *dest)
{
	dest->should_render_every_frame = false;
	dest->render = fdf_selection_window_render;
	if (!(fdf->state->dirwin = (t_dirwin_state *)malloc(sizeof(t_dirwin_state))))
		return (RET_ERROR_500);
	fdf_selection_window_state(fdf);
	return (RET_OK);
}
