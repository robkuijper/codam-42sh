/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   term_set_attributes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/18 18:11:05 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/04/18 19:15:18 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

int		term_set_attributes(t_term *term_p)
{
	int	ret;

	term_p->termios_p->c_lflag &= ~ICANON;
	term_p->termios_p->c_lflag &= ~ECHO;
	term_p->termios_p->c_lflag &= ~ISIG;
	term_p->termios_p->c_cc[VMIN] = 1;
	term_p->termios_p->c_cc[VTIME] = 0;
	/* Is TCSANOW flag correct? */
	ret = tcsetattr(STDIN_FILENO, TCSANOW, term_p->termios_p);
	if (ret == FUNCT_ERROR)
	{
		ft_eprintf("Couldn't set terminal attributes.\n");
		return (FUNCT_FAILURE);
	}
	return (FUNCT_SUCCESS);
}