#include "minishell.h"
#include "libft.h"

/*
**	The main parse function, will loop over the list and delegate work to
**	other functions.
*/

t_list			*parse(t_list **tokens)
{
	char			*token;
	t_parser		parser;
	t_list			*comm_table;
	t_list			*tmp;

	comm_table = NULL;
	parser.start = *tokens;
	parser.prev_sep = NO_SEPARATOR;
	while (*tokens != NULL)
	{
		token = (char *)(*tokens)->content;
		parser.sep = is_separator(token);
		if (parser.sep)
		{
			create_command(&comm_table, &parser);
			tmp = parser.start;
			parser.prev_sep = parser.sep;
			parser.start = (*tokens)->next;
			free(tmp->content);
			free(tmp);
		}
		if (parser.sep == SEMICOLON)
		{
			*tokens = (*tokens)->next;
			return (comm_table);
		}
		*tokens = (*tokens)->next;
	}
	if (parser.start != NULL)
		create_command(&comm_table, &parser);
	return (comm_table);
}

/*
**	This function will check if the format of the command is valid, that mostly
**	means no double redirects. Will return 0 if invalid, otherwise the length
**	of the var list.
*/

int			validate_command(t_parser *parser)
{
	t_redirect	prev;
	t_redirect	curr;
	int			count;
	t_list		*node;

	count = 0;
	curr = NO_REDIRECT;
	node = parser->start;
	while (node != NULL && !is_separator((char *)node->content))
	{
		count++;
		prev = curr;
		curr = is_redirect((char *)node->content);
		if (curr != NO_REDIRECT)
			count -= 2;
		if (prev != NO_REDIRECT && curr != NO_REDIRECT)
			return (0);
		node = node->next;
	}
	if (curr != NO_REDIRECT)
		return (0);
	return (count);
}

/*
**	This function will take a few links of the token list and create a new
**	entry in the command table for it.
*/

void		create_command(t_list **table, t_parser *parser)
{
	t_list			*new;
	int				length;

	length = validate_command(parser);
	new = prepare_command(length);
	if (new == NULL)
	{
		printf("Iets ging fout lmaoooo\n");
		return ;
	}
	parse_command((t_command*)new->content, parser);
	ft_lstadd_back(table, new);
}

/*
**	This will loop over the tokens and assign the correct values to fields in
**	the command struct.
*/

void		parse_command(t_command *command, t_parser *parser)
{
	int			vars_parsed;
	t_redirect	redirect;
	t_list		*tmp;

	vars_parsed = 0;
	while (parser->start && !is_separator((char *)parser->start->content))
	{
		redirect = is_redirect((char*)parser->start->content);
		if (redirect != NO_REDIRECT)
			handle_redirect(command, parser, redirect);
		else
		{
			*(command->vars + vars_parsed) = parser->start->content;
			vars_parsed++;
		}
		tmp = parser->start;
		parser->start = parser->start->next;
		free(tmp);
	}
	if (parser->sep == PIPE)
		command->pipe ^= PIPE_OUT;
	if (parser->prev_sep == PIPE)
		command->pipe ^= PIPE_IN;
}

/*
**	This function will handle a redirect, and put the right information in the
**	struct.
*/

void		handle_redirect(t_command *command, t_parser *parser,
				t_redirect redirect)
{
	char		*file;
	t_filemode	*mode;
	t_list		*tmp;

	file = (char *)parser->start->next->content;
	if (redirect == REDIRECT_IN)
	{
		ft_lstadd_back(&(command->files_in), ft_lstnew(file));
	}
	else
	{
		mode = malloc(sizeof(t_filemode));
		*mode = (redirect == REDIRECT_OUT_TRUNC) ? TRUNC : APPEND;
		ft_lstadd_back(&(command->files_out), ft_lstnew(file));
		ft_lstadd_back(&(command->out_modes), ft_lstnew(mode));
	}
	tmp = parser->start;
	parser->start = parser->start->next;
	free(tmp->content);
	free(tmp);
}
