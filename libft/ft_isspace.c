/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isspace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/13 13:39:22 by omulder        #+#    #+#                */
/*   Updated: 2019/04/30 10:05:52 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
			c == ' ');
}
