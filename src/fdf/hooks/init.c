/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:51:22 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/03 16:51:48 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_hooks(t_canvas *canvas, void *s)
{
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_W, fdf_press_w, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_A, fdf_press_a, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_S, fdf_press_s, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_D, fdf_press_d, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_LEFT, fdf_press_arrow_left, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_UP, fdf_press_arrow_up, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_RIGHT, fdf_press_arrow_right, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_ARROW_DOWN, fdf_press_arrow_down, s);
	canvas->keyboard_hooks->add(canvas->keyboard_hooks, KEY_T, fdf_press_t, s);
	// canvas->mouse_hooks->add(canvas->mouse_hooks, 0, canvas->zone, fdf_click, s);
	// canvas->motion_hooks->add(canvas->motion_hooks, canvas->zone, fdf_motion, s);
}
