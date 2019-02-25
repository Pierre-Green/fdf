/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:45:06 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/22 16:17:08 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "dirwin.h"
#include "ft_printf.h"
#include "ft_str.h"

void				assert(t_ret ret, const char *msg)
{
	if (ret != RET_OK)
	{
		if (ret == RET_ERROR_USAGE)
			ft_printf("%s\n", msg);
		else
			ft_printf("FDF error(%d): %s\n", ret, msg);
		exit(ret);
	}
}

static t_ret	initial_state(t_fdf **fdf)
{
	if (!(*fdf = (t_fdf *)malloc(sizeof(t_fdf))))
		return (RET_ERROR_INIT);
	(*fdf)->mlx_ptr = mlx_init();
	(*fdf)->params = NULL;
	(*fdf)->mapmode = UNDEFINED;
	(*fdf)->windows = NULL;
	(*fdf)->window_count = 0;
	if (!((*fdf)->state = (t_state *)malloc(sizeof(t_state))))
		return (RET_ERROR_INIT);
	(*fdf)->state->dirwin = NULL;
	return (RET_OK);
}

static t_ret	parse_params(t_fdf *fdf, int ac, char **av, char **msg)
{
	DIR			*dir;
	int			fd;

	fdf->params = get_params(ac, av);
	if (fdf->params->length == 2 && ft_strcmp(fdf->params->at(fdf->params, 0)->value, DIRMODE_FLAG) == 0)
	{
		if ((dir = opendir(fdf->params->at(fdf->params, 1)->value)) == NULL)
		{
			*msg = ft_strdup("Please use an existing directory...");
			return (RET_ERROR_ARGS);
		}
		fdf->mapmode = FOLDER;
		fdf->dir = dir;
	}
	else if (fdf->params->length == 1)
	{
		if ((fd = open((char *)fdf->params->at(fdf->params, 0), O_RDONLY)) < 0)
		{
			*msg = ft_strdup("Please use an existing file...");
			return (RET_ERROR_ARGS);
		}
		fdf->mapmode = SINGLE;
		fdf->fd = fd;
	}
	else
	{
		*msg = ft_strdup("usage: ./fdf [-d dir] filename");
		return (RET_ERROR_USAGE);
	}
	return (RET_OK);
}

static t_ret		render(t_fdf *fdf)
{
	size_t			curr;
	t_window		*win;
	t_hook_carry	**carries;

	curr = 0;
	win = fdf->windows;
	if (!(carries = (t_hook_carry **)malloc(sizeof(*carries) * fdf->window_count)))
		return (RET_ERROR_500);
	while (curr < fdf->window_count)
	{
		if (!(*carries = (t_hook_carry *)malloc(sizeof(carries))))
			return (RET_ERROR_500);
		(*(carries + curr))->window = win;
		(*(carries + curr))->state = fdf;
		if (win->should_render_every_frame)
			mlx_expose_hook(fdf->mlx_ptr, win->render, fdf);
		mlx_key_hook(win->ptr, keyboard_hooks_dispatcher, *carries);
		mlx_hook(win->ptr, 2, 1l<<0, lkeyboard_hooks_dispatcher, *carries);
		mlx_mouse_hook(win->ptr, mouse_hooks_dispatcher, *carries);
		win = win->next;
		curr++;
	}
	// SALE
	fdf->windows->render(fdf);
	mlx_loop(fdf->mlx_ptr);
	return (RET_OK);
}

int				main(int ac, char **av)
{
	t_fdf		*fdf;
	char		*msg;

	assert(initial_state(&fdf), "Initialization error !");
	assert(parse_params(fdf, ac, av, &msg), msg);
	if (!(fdf->windows = ft_init_window()))
		assert(RET_ERROR_500, "Window initialization error");
	fdf->window_count++;
	if (fdf->mapmode == SINGLE)
	{
		// Parse
	}
	else if (fdf->mapmode == FOLDER)
		assert(fdf_selection_window(fdf, fdf->windows), "Error creating selection window");
	else
		assert(RET_ERROR_500, "WTF");
	assert(render(fdf), "Render router error");
	return (0);
}

