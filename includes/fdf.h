/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:08:21 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/25 19:37:30 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "map.h"
# include "ft_args.h"
# include "ft_mlx/window.h"
# include "ft_math/matrix.h"
# include "ft_mlx/camera.h"
# include "ft_mlx/camera.h"
# include "dirwin.h"
# include <sys/types.h>
# include <dirent.h>
# include <unistd.h>
# include "ft_printf.h"
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
					UNDEFINED,
}					t_mapmode;
# define DIRMODE_FLAG "-d"

typedef struct		s_fdf_state
{
	t_camera		*camera;
	t_matrix44_d	proj;
}					t_fdf_state;

typedef struct		s_state
{
	t_dirwin_state	*dirwin;
	t_fdf_state		*fdf;
}					t_state;

typedef struct		s_fdf
{
	t_map			*map;
	t_params		*params;
	t_mapmode		mapmode;
	DIR				*dir;
	int				fd;
	void			*mlx_ptr;
	t_window		*window;
	t_window		*dirwin;
	t_state			*state;
	size_t			window_count;
}					t_fdf;

t_ret				parse(t_fdf *fdf);

void				assert(t_ret ret, const char *msg);

t_ret				fdf_selection_window(t_fdf *fdf, t_window *dest);

int					fdf_selection_window_render(t_window *win, void *s);

char				**fdf_selection_get_files(t_fdf *fdf);

t_ret				fdf_window_init(t_fdf *fdf, t_window *dest);

int					fdf_window_render(t_window *win, void *s);

t_container			*fdf_layout(t_fdf *fdf);

t_container			*dirwin_layout(t_fdf *fdf);

t_image_carry		*fdf_image(t_canvas *canvas, void *s, t_image_carry *carry);

void				fdf_press_w(void *s);

void				fdf_press_a(void *s);

void				fdf_press_s(void *s);

void				fdf_press_d(void *s);

#endif
