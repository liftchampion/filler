/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapka                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggerardy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:25:22 by ggerardy          #+#    #+#             */
/*   Updated: 2018/11/29 16:09:36 by ggerardy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# define INIT_VECT_SIZE 16

# include <string.h>
# include "libft.h"

typedef struct	s_buf
{
	char	*buffer;
	ssize_t	pos;
	ssize_t	len;
	ssize_t	capac;
}				t_buf;

typedef enum {
	ERROR = -1,
	NO_LINE = 0,
	ENDL_GOT = 1,
	ENDL_NOT_FOUND = 2,
}	t_result;

t_result		ft_get_line_from_buffer(t_buf *buf, t_string **str, int fd,
					int buff_size);
t_result		ft_append_line(t_buf *buf, int fd, t_string *str,
					int buff_size);
void			ft_free_buf(void *buf);
t_result		ft_gnl_init_works(int fd, t_map **fd_bf, t_buf ***curr_buf,
					int buff_size);

#endif
