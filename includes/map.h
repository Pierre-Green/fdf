/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:09:06 by pguthaus          #+#    #+#             */
/*   Updated: 2019/04/08 19:41:57 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdlib.h>
# include "ft_math/vec.h"
# define FDF_MAP_INITIAL_CAPACITY 32

typedef struct		s_map
{
	size_t			width;
	size_t			depth;
	size_t			height;
	size_t			len;
	size_t			capacity;
	char			*name;
	t_vec3_d		vecs[];
}					t_map;

#endif
