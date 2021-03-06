/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_get_attributes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:08:42 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/27 11:41:44 by omulder       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <termios.h>

/*
**	Insert: check if it is a valid terminal file_d
*/

int		term_get_attributes(int fd, t_vshdataterm *term_p)
{
	int	ret;

	if (term_p == NULL)
		return (FUNCT_FAILURE);
	ret = tcgetattr(fd, term_p->termios_p);
	if (ret == -1)
	{
		ft_eprintf(E_TERM_CNT_GET);
		return (FUNCT_FAILURE);
	}
	ret = tcgetattr(fd, term_p->old_termios_p);
	if (ret == -1)
	{
		ft_eprintf(E_TERM_CNT_GET);
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}
