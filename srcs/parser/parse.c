#include "minishell.h"
#include "libft.h"

// DEBUG
void	print_table(t_list *table)
{
	t_command	*command;
	char		*mode;

	printf("\n_____COMMAND TABLE_____\n\n");
	while (table != NULL)
	{
		command = (t_command *)table->content;
		printf("Element.\nVars = ");
		while (*(command->vars))
		{
			printf("[%s] ", *(command->vars));
			command->vars++;
		}
		printf("\nFiles in = ");
		while (command->files_in)
		{
			printf("[%s] ", (char *)command->files_in->content);
			command->files_in = command->files_in->next;
		}
		printf("\nFiles out = ");
		while (command->files_out)
		{
			mode = ((int)command->out_modes->content == APPEND) ?
				"Append" : "Trunc";
			printf("[%s][%s] ", (char *)command->files_out->content, mode);
			command->files_out = command->files_out->next;
			command->out_modes = command->out_modes->next;
		}
		printf("\n");
		table = table->next;
	}
	printf("\n_____COMMAND TABLE_____\n");
}

/*
**	The main parse function, will loop over the list and delegate work to
**	other functions.
*/

void		parse(t_list *tokens)
{
	char			*token;
	t_parser		parser;
	t_list			*comm_table;

	comm_table = NULL;
	parser.start = tokens;
	parser.prev_sep = NO_SEPARATOR;
	while (tokens != NULL)
	{
		token = (char *)tokens->content;
		parser.sep = is_separator(token);
		if (parser.sep)
		{
			create_command(&comm_table, &parser);
			parser.prev_sep = parser.sep;
			parser.start = tokens->next;
		}
		tokens = tokens->next;
	}
	if (parser.start != NULL)
		create_command(&comm_table, &parser);
	//
	print_table(comm_table);
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
	prev = NO_REDIRECT;
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
	printf("Length? [%i]\n", length);
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

	(void)command;
	vars_parsed = 0;
	while (parser->start && !is_separator((char *)parser->start->content))
	{
		redirect = is_redirect((char*)parser->start->content);
		if (redirect != NO_REDIRECT)
		{
			handle_redirect(command, parser, redirect);
		}
		else
		{
			*(command->vars + vars_parsed) = parser->start->content;
			vars_parsed++;
		}
		parser->start = parser->start->next;
	}
}

/*
**	This function will handle a redirect, and put the right information in the
**	struct.
*/

void		handle_redirect(t_command *command, t_parser *parser,
				t_redirect redirect)
{
	char		*file;
	t_filemode	mode;

	(void)command;
	file = (char *)parser->start->next->content;
	if (redirect == REDIRECT_IN)
	{
		ft_lstadd_back(&(command->files_in), ft_lstnew(file));
	}
	else
	{
		mode = (redirect == REDIRECT_OUT_TRUNC) ? TRUNC : APPEND;
		ft_lstadd_back(&(command->files_out), ft_lstnew(file));
		ft_lstadd_back(&(command->out_modes), ft_lstnew((void *)mode));
	}
	parser->start = parser->start->next;
}
