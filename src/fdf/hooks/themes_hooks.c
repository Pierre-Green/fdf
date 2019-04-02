/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:07:26 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/02 19:54:00 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void				fdf_press_t(void *s)
{
	const t_fdf		*fdf = s;
	size_t			random = rand() % fdf->themes->len;

	if (random == fdf->state->fdf->selected_theme && fdf->themes->len > 1)
		fdf_press_t(s);
	fdf->state->fdf->theme = fdf->themes->themes[random];
	fdf->state->fdf->selected_theme = random;
	fdf->window->body = fdf_layout((t_fdf *)fdf);
}
