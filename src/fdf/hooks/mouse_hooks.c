/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:09:24 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/27 19:11:35 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				fdf_click(t_mouse_btn btn, int id, void *s)
{
	const t_fdf		*fdf = s;
	t_fdf_state		*state;
	
	(void)id;
	state = fdf->state->fdf;
	if (btn == 1)
		state->motion_focus = TRUE;
	if (btn == 2)
		state->motion_focus = FALSE;
}
