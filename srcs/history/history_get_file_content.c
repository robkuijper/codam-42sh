/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history_get_file_content.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: omulder <omulder@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/30 13:49:22 by mavan-he       #+#    #+#                */
/*   Updated: 2019/08/06 11:09:15 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"
#include <fcntl.h>
#include "libft.h"
#include <unistd.h>

/*
** Get the content out of the history file
*/

static int		get_line_in_history(int fd, t_vshdata *vshdata, int i)
{
	int		ret;
	char	*line;

	line = NULL;
	ret = ft_get_next_line_delim(fd, &line, HIST_SEPARATE);
	if (ret == -1)
		return (err_ret(E_HIST_READ_STR));
	vshdata->history[i] = (t_history*)ft_memalloc(sizeof(t_history));
	if (vshdata->history[i] == NULL)
		return (err_ret(E_ALLOC_STR));
	vshdata->history[i]->number = i + 1;
	vshdata->history[i]->str = line;
	return (ret);
}

static int		allocate_leftover_history(t_vshdata *vshdata, int i)
{
	while (i < HISTORY_MAX)
	{
		vshdata->history[i] = (t_history*)ft_memalloc(sizeof(t_history));
		if (vshdata->history[i] == NULL)
			return (err_ret(E_ALLOC_STR));
		vshdata->history[i]->number = -1;
		i++;
	}
	return (FUNCT_SUCCESS);
}

int				history_get_file_content(t_vshdata *vshdata)
{
	int		fd;
	int		ret;
	int		i;

	vshdata->history = (t_history **)ft_memalloc(
		sizeof(t_history *) * HISTORY_MAX);
	if (vshdata->history == NULL || vshdata->history_file == NULL)
		return (err_ret(E_ALLOC_STR));
	fd = open(vshdata->history_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (err_ret(E_HIST_OPEN_STR));
	ret = 1;
	i = 0;
	while (ret > 0 && i < HISTORY_MAX)
	{
		ret = get_line_in_history(fd, vshdata, i);
		if (ret == FUNCT_ERROR)
			return (FUNCT_ERROR);
		i++;
	}
	close(fd);
	ret = allocate_leftover_history(vshdata, i);
	if (ret == FUNCT_ERROR)
		return (FUNCT_ERROR);
	return (FUNCT_SUCCESS);
}
