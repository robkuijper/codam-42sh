/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd_changedir.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/08/02 15:03:51 by jbrinksm       #+#    #+#                */
/*   Updated: 2019/08/02 17:47:44 by jbrinksm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

static int	return_and_free(int ret, char **newpath, char **currpath)
{
	ft_strdel(currpath);
	ft_strdel(newpath);
	return (ret);
}

/*
**	Updates OLDPWD and PWD.
*/

static int		cd_post_process_var(char *currpath, char *newpath,
t_envlst *envlst, char cd_flag)
{
	if (newpath == NULL)
		return (cd_alloc_error());
	if (env_add_extern_value(envlst, "OLDPWD", currpath) == FUNCT_ERROR)
		return (cd_alloc_error());

	if (cd_flag == BUILTIN_CD_UP)
	{
		ft_strdel(&newpath);
		newpath = getcwd(NULL, 0);
		if (newpath == NULL)
			return (cd_alloc_error());
	}
	if (env_add_extern_value(envlst, "PWD", newpath) == FUNCT_ERROR)
		return (cd_alloc_error());
	return (FUNCT_SUCCESS);
}

/*
**	This function is the heart of builtin_cd.
**	If BUILTIN_CD_UL is set, then newpath will be set to
**	either `NULL` if the argpath doesn't make sense, or the new path
**	if argpath was parsed succesfully. If newpath wasn't set successfully
**	-- meaning either BUILTIN_CD_UL isn't set OR argpath wasn't valid --
**	chdir will take argpath instead of newpath.
**
**	Afterwards, PWD and OLDPWD are set appropriately.
*/

int			builtin_cd_change_dir(char *argpath, t_envlst *envlst, char cd_flag,
				int print)
{
	char		*pwd;
	char		*currpath;
	char		*newpath;

	newpath = NULL;
	pwd = env_getvalue("PWD", envlst);
	if (cd_flag == BUILTIN_CD_UL && pwd != NULL)
		currpath = ft_strdup(pwd);
	else
		currpath = getcwd(NULL, 0);
	if (currpath == NULL)
		return (cd_change_dir_error(NULL, argpath, NULL, NULL));
	if (cd_flag == BUILTIN_CD_UL)
		newpath = builtin_cd_create_newpath_wrap(currpath, argpath);
	if (newpath == NULL && chdir(argpath) == -1)
		return (cd_change_dir_error(argpath, argpath, &newpath, &currpath));
	else if (newpath != NULL && chdir(newpath) == -1)
		return (cd_change_dir_error(newpath, argpath, &newpath, &currpath));
	if (print == true)
		ft_putendl(argpath);
	if (newpath == NULL)
		newpath = getcwd(NULL, 0);
	if (cd_post_process_var(currpath, newpath, envlst, cd_flag) == FUNCT_ERROR)
		return (return_and_free(FUNCT_ERROR, &newpath, &currpath));
	return (return_and_free(FUNCT_SUCCESS, &newpath, &currpath));
}
