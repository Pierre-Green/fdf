/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:23:48 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/20 23:38:21 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dirwin.h"
# include <mlx.h>

t_ret			fdf_selection_window(t_fdf *fdf, t_window *dest)
{
	dest->next = NULL;
	dest->width = DIRWIN_WIDTH;
	dest->height = DIRWIN_HEIGHT;
	dest->ptr = mlx_new_window(fdf->mlx_ptr, dest->width, dest->height, "Choisir sa map...");
	dest->render = fdf_selection_window_render;
	return (RET_OK);
}
