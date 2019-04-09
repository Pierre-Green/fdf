/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:28:57 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/09 18:50:05 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "fdf.h"

void		fdf_next_theme(t_fdf *fdf)
{
	size_t	new;

	new = fdf->state->fdf->selected_theme + 1;
	if (new >= fdf->themes->len)
		new = 0;
	fdf->state->fdf->theme = fdf->themes->themes[new];
	fdf->window->render(fdf->window);
}

void		fdf_prev_theme(t_fdf *fdf)
{
	int		new;

	new = fdf->state->fdf->selected_theme - 1;
	if (new < 0)
		new = fdf->themes->len - 1;
	fdf->state->fdf->theme = fdf->themes->themes[new];
	fdf->window->render(fdf->window);
}
