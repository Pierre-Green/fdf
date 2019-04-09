/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 15:44:38 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/09 16:02:30 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "fdf.h"

t_ret				fdf_init_config(t_fdf *fdf)
{
	t_window		*window;
	t_config_state	*state;

	if (!(window = ft_init_window(fdf->mlx_ptr, DIM(300, 500),
					"FDF - CONFIG", fdf)))
		return (RET_ERROR_500);
	window->should_render_every_frame = FALSE;
	if (!(state = malloc(sizeof(t_config_state))))
		return (RET_ERROR_500);
	state->win = window;
	fdf->state->config = state;
	window->body = fdf_config_layout(fdf);
	window->render(window);
	return (RET_OK);
}
