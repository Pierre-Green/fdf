/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirwin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:22:05 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/22 15:55:41 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DIRWIN_H
# define FT_DIRWIN_H
# include <mlx.h>
# include "ft_mlx/window.h"
# include "ft_mlx/drawables.h"
# include "ft_io.h"
# define DIRWIN_WIDTH 700
# define DIRWIN_HEIGHT 500
# define ROW_LENGTH 5
# define COLUMN_LENGTH 5
# define ITEMS_PER_PAGE (ROW_LENGTH * COLUMN_LENGTH)

typedef struct			s_dirwin_state
{
	void				*img_ptr;
	t_container			*container;
	size_t				items_count;
	size_t				current_page;
	t_dfiles			*files;
}						t_dirwin_state;

#endif
