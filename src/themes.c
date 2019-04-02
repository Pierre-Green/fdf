/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   themes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:46:36 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/02 18:52:40 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "get_next_line.h"

static t_ret	set_name(char **dest, char *name, size_t name_len)
{
	size_t		current;

	if (!(*dest = malloc(sizeof(char) * (8 + name_len))))
		return (RET_ERROR_500);
	current = 0;
	while (current < 6)
	{
		(*dest)[current] = THEMES_DIR[current];
		current++;
	}
	(*dest)[current] = '/';
	current = 0;
	while (current < name_len)
	{
		(*dest)[current + 7] = name[current];
		current++;
	}
	(*dest)[current + 7] = '\0';
	return (RET_OK);
}

static void		parse_cfg(char *key, char *value, t_theme *dest)
{
	if (ft_strcmp(key, "CANVAS_BACKGROUND") == 0)
		dest->canvas_color = ft_int_from_hexstr(value);
	else if (ft_strcmp(key, "UI_BACKGROUND") == 0)
		dest->ui_background = ft_int_from_hexstr(value);
	else if (ft_strcmp(key, "LINE_COLOR") == 0)
		dest->line_color = ft_int_from_hexstr(value);
}

static void		split(char *value, char **key, char **p_value)
{
	size_t		lens[2];

	lens[0] = 0;
	while (*(value + lens[0]) && *(value + lens[0]) != '=')
		(lens[0])++;
	if (*(value + lens[0]) != '=')
		return ;
	lens[1] = 0;
	while (*(value + lens[0] + lens[1]))
		(lens[1])++;
	if (!(*key = malloc(sizeof(char) * lens[0] + 1)))
		return ;
	if (!(*p_value = malloc(sizeof(char) * lens[1] + 1)))
		return ;
	ft_strncpy(*key, value, lens[0]);
	(*key)[lens[0]] = '\0';
	ft_strncpy(*p_value, value + lens[0] + 1, lens[1]);
}

static t_ret	load_theme(char *name, t_fdf *fdf, size_t current)
{
	int			fd;
	char		*line;
	char		*key;
	char		*value;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (RET_ERROR_500);
	while (get_next_line(fd, &line))
	{
		split(line, &key, &value);
		parse_cfg(key, value, &fdf->themes->themes[current]);
		free(line);
	}
	return (RET_OK);
}

t_ret			load_themes(t_fdf *fdf)
{
	DIR			*dir;
	t_dfiles	*files;
	size_t		count;
	size_t		current;
	char		*name;

	if (!(dir = opendir(THEMES_DIR)))
		return (RET_ERROR_500);
	if (!(files = ft_get_dir_files(dir, THEMES_EXT, &count)))
		return (RET_ERROR_500);
	if (!(fdf->themes = malloc(sizeof(t_themes) + sizeof(t_theme) * count)))
		return (RET_ERROR_500);
	current = 0;
	while (files)
	{
		set_name(&name, files->file->d_name, files->file->d_namlen);
		load_theme(name, fdf, current);
		files = files->next;
		current++;
	}
	return (RET_OK);
}
