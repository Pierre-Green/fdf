/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:09:06 by pguthaus          #+#    #+#             */
/*   Updated: 2019/02/20 21:27:20 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdlib.h>

typedef long long t_height;

typedef struct		s_map
{
	t_height		**values;
	size_t			width;
	size_t			height;
	char			*name;
	t_height		(*at)(size_t, size_t);
}					t_map;

#endif
