/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_handle_escaped_newlines.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/31 14:18:35 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/30 13:56:47 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static bool	remove_last_escaped_newline(char *line)
{
	int i;

	i = ft_strlen(line);
	if (i == 0)
		return (false);
	i--;
	if (line[i] == '\n' && tools_is_char_escaped(line, i) == true)
	{
		line[i] = '\0';
		line[i - 1] = '\0';
		return (true);
	}
	return (false);
}

int			shell_handle_escaped_newlines(t_vshdata *data)
{
	int		ret;
	char	*line_tmp;

	ret = remove_last_escaped_newline(data->line->line);
	if (ret == false)
		return (FUNCT_FAILURE);
	while (true)
	{
		ft_putchar('\n');
		line_tmp = data->line->line;
		shell_display_prompt(data, LINECONT_PROMPT);
		ret = input_read(data);
		if (ret == NEW_PROMPT)
			return (ft_free_return(line_tmp, NEW_PROMPT));
		data->line->line = ft_strjoinfree_all(line_tmp, data->line->line);
		if (data->line->line == NULL)
			return (err_ret(E_ALLOC_STR));
		if (remove_last_escaped_newline(data->line->line) == false)
			break ;
	}
	return (ret);
}
