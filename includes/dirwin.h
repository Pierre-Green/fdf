/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirwin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 23:22:05 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/13 19:14:40 by pguthaus         ###   ########.fr       */
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
	size_t				items_count;
	size_t				current_page;
	t_dfiles			*files;
}						t_dirwin_state;

#endif
