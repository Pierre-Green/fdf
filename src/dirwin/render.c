/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:37:36 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/21 01:39:39 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirwin.h"
#include <mlx.h>

int					fdf_selection_window_render(void *s)
{
	const t_fdf		*fdf = (t_fdf *)s;

	mlx_clear_window(fdf->mlx_ptr, fdf->windows);
	return (0);
}
