/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mavan-he <mavan-he@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/05/21 19:54:55 by mavan-he       #+#    #+#                */
/*   Updated: 2019/11/06 13:41:04 by rkuijper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "vsh.h"

/*
**	parser_io_redirect gets an IO_NUM or redir token
**	after IO_NUM there has to be a redir token
**	after the redir token there has to be a WORD or ASSIGN
**	the redir token will be the head token
**	the optional IO_NUM and WORD or ASSIGN will be on the right
**	left will be empty
*/

bool	parser_io_redirect(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast *redir;

	redir = NULL;
	if (TK_TYPE == IO_NUMBER && parser_add_astnode(token_lst, ast) == false)
		return (false);
	if (tools_is_redirect_tk(TK_TYPE) == false ||
		parser_add_astnode(token_lst, ast) == false)
		return (parser_return_del(ast));
	if ((TK_TYPE != WORD && TK_TYPE != ASSIGN) ||
		parser_add_astnode(token_lst, &redir) == false)
		return (parser_return_del(ast));
	if ((*ast)->left == NULL)
		(*ast)->left = redir;
	else
		(*ast)->left->left = redir;
	(*ast)->right = (*ast)->left;
	(*ast)->left = NULL;
	return (true);
}

t_ast	*parser_new_node(t_tokenlst *token)
{
	t_ast *node;

	node = (t_ast*)ft_memalloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->type = token->type;
	node->flags = token->flags;
	if (token->value != NULL)
	{
		node->value = ft_strdup(token->value);
		if (node->value == NULL)
			return (NULL);
	}
	else
		node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*
**	parser_add_right executes a parser function with an empty ast
**	It adds this new ast to the right side of the current ast
*/

bool	parser_add_right(t_tokenlst **token_lst, t_ast **ast,
		bool (*parse_priority_x)(t_tokenlst **, t_ast **))
{
	t_ast *right;

	right = NULL;
	if (parse_priority_x(token_lst, &right) != true)
		return (parser_return_del(ast));
	(*ast)->right = right;
	return (true);
}

/*
**	parser_add_astnode creates a new ast node with current token
**	it adds the existing ast to the left of the new node
*/

bool	parser_add_astnode(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast *new_node;

	new_node = parser_new_node(*token_lst);
	if (new_node == NULL)
	{
		(*token_lst)->flags |= T_MALLOC_ERROR;
		return (false);
	}
	new_node->left = *ast;
	new_node->right = NULL;
	*ast = new_node;
	*token_lst = (*token_lst)->next;
	return (true);
}
