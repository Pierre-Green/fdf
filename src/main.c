/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:45:06 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/22 18:47:10 by pguthaus         ###   ########.fr       */
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

static t_ret		initial_state(t_fdf **fdf)
{
	if (!(*fdf = (t_fdf *)malloc(sizeof(t_fdf))))
		return (RET_ERROR_INIT);
	(*fdf)->mlx_ptr = mlx_init();
	(*fdf)->params = NULL;
	(*fdf)->mapmode = UNDEFINED;
	(*fdf)->dirwin = NULL;
	(*fdf)->window = NULL;
	(*fdf)->window_count = 0;
	if (!((*fdf)->state = (t_state *)malloc(sizeof(t_state))))
		return (RET_ERROR_INIT);
	if (!((*fdf)->map = (t_map *)malloc(sizeof(t_map)
					+ (sizeof(t_vec3_d) * FDF_MAP_INITIAL_CAPACITY))))
		return (RET_ERROR_INIT);
	(*fdf)->map->width = 0;
	(*fdf)->map->depth = 0;
	(*fdf)->map->capacity = FDF_MAP_INITIAL_CAPACITY;
	(*fdf)->map->len = 0;
	(*fdf)->map->name = NULL;
	(*fdf)->state->dirwin = NULL;
	(*fdf)->state->fdf = NULL;
	return (RET_OK);
}

static t_ret		parse_params(t_fdf *fdf, int ac, char **av, char **msg)
{
	DIR				*dir;
	int				fd;

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
		if ((fd = open((char *)fdf->params->at(fdf->params, 0)->value, O_RDONLY)) < 0)
		{
			*msg = ft_strdup("Please use an existing file...");
			return (RET_ERROR_ARGS);
		}
		fdf->map->name = fdf->params->at(fdf->params, 0)->value;
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
	if (fdf->mapmode == FOLDER)
		if ((fdf->dirwin->render(fdf->dirwin)) == 1)
			ft_printf("Window has no body...");
	if (fdf->window)
		fdf->window->render(fdf->window);
	mlx_loop(fdf->mlx_ptr);
	return (RET_OK);
}

int					main(int ac, char **av)
{
	t_fdf			*fdf;
	char			*msg;

	assert(initial_state(&fdf), "Initialization error !");
	assert(parse_params(fdf, ac, av, &msg), msg);
	fdf->window_count++;
	if (fdf->mapmode == SINGLE)
	{
		assert(parse(fdf), "Parsing error...");
	}
	else if (fdf->mapmode == FOLDER)
	{
		if (!(fdf->dirwin = ft_init_window(fdf->mlx_ptr, DIM(DIRWIN_WIDTH, DIRWIN_HEIGHT), "Choose your map", fdf)))
			assert(RET_ERROR_500, "Window initialization error");
		assert(fdf_selection_window(fdf, fdf->dirwin), "Error creating selection window");
	}
	else
		assert(RET_ERROR_500, "WTF");
	assert(render(fdf), "Render router error");
	return (0);
}

