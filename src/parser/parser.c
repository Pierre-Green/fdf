/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:22:48 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/10 01:08:49 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"

static t_ret		parser_compute(t_fdf *fdf)
{
	(void)fdf;
	return (RET_OK);
}

t_ret				parse(t_fdf *fdf)
{
	char			filename[255];
	size_t			len;
	size_t			tmp;

	if (fdf->mapmode == SINGLE)
	{
		if ((fdf->fd = open(fdf->map.name, O_RDONLY)) < 0)
			return (RET_ERROR_500);
	}
	else if (fdf->mapmode == FOLDER)
	{
		len = 0;
		while (fdf->params->at(fdf->params, 1)->value[len])
		{
			filename[len] = fdf->params->at(fdf->params, 1)->value[len];
			len++;
		}
		filename[len++] = '/';
		tmp = 0;
		while (fdf->map.name[tmp])
			filename[len++] = fdf->map.name[tmp++];
		filename[len] = '\0';
		if ((fdf->fd = open(filename, O_RDONLY)) < 0)
			return (RET_ERROR_500);
	}
	else
		return (RET_ERROR_500);
	return (parser_compute(fdf));
}
