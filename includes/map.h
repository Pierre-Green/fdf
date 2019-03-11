/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:09:06 by pguthaus          #+#    #+#             */
/*   Updated: 2019/03/11 17:17:07 by pguthaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include <stdlib.h>
# include "ft_math/vec.h"
# include "ft_lst.h"

typedef struct		s_map
{
	t_list			*vecs;
	size_t			width;
	size_t			depth;
	char			*name;
}					t_map;

#endif
