/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:08:21 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/21 00:17:33 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "map.h"
# include "ft_args.h"
# include "ft_mlx/window.h"
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>

typedef int			t_ret;
# define RET_OK 0
# define RET_ERROR_PARSE -1
# define RET_ERROR_INIT -2
# define RET_ERROR_ARGS -3
# define RET_ERROR_USAGE -4
# define RET_ERROR_500 500

typedef enum		e_mapmode
{
					SINGLE,
					FOLDER,
					NONE
}					t_mapmode;
# define DIRMODE_FLAG "-d"

typedef struct		s_fdf
{
	t_map			map;
	t_params		*params;
	t_mapmode		mapmode;
	DIR				*dir;
	int				fd;
	void			*mlx_ptr;
	t_window		*windows;
	size_t			window_count;
}					t_fdf;

t_ret				parse(t_fdf *fdf);

void				assert(t_ret ret, const char *msg);

#endif
