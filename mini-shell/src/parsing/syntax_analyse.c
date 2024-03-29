/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauger <lauger@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:31:25 by lauger            #+#    #+#             */
/*   Updated: 2024/03/29 11:29:29 by lauger           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*typedef struct s_here_doc
{
	int fd;
	char *filename;
	char *line;
	char *tmp;
	char *delimiter;
} t_here_doc;

static int is_delimiter(char *line, char *tmp, char *delimiter)
{
	if (!line || !tmp | !delimiter)
		return (0);
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && ft_strlen(tmp) == ft_strlen(delimiter) + 1)
		return (1);
	return (0);
}

static void handle_null(t_here_doc *here_doc)
{
	if ((here_doc->line && (here_doc->line)[0] == '\0') || (here_doc->line && (here_doc->line)[ft_strlen(here_doc->line) - 1] == '\n'))
	{
		write(1, " > ", 3);
		free(here_doc->tmp);
		here_doc->tmp = NULL;
	}
	else
		free(here_doc->tmp);
}

static void handle_while(t_here_doc *here_doc)
{
	static char *buff;

	while (true)
	{
		handle_null(here_doc);
		//here_doc->tmp = get_next_line(0, &buff);
		here_doc->tmp = readline(NULL);
		if (here_doc->tmp)
		{
			if (is_delimiter(here_doc->line, here_doc->tmp, here_doc->delimiter) == 0)
				here_doc->line = ft_strjoin(here_doc->line, here_doc->tmp);
			else if (is_delimiter(here_doc->line, here_doc->tmp, here_doc->delimiter) == 1)
			{
				free(buff);
				buff = NULL;
				break;
			}
		}
		else if ((here_doc->line)[0] == '\0' || (here_doc->line)[ft_strlen(here_doc->line) - 1] == '\n')
		{
			free(buff);
			buff = NULL;
			ft_printf("\nbash: warning: here-document at line 1 delimited"
				"by end-of-file (wanted `%s')\n", here_doc->delimiter);
			break;
		}
	}
}

void init_here_doc(t_here_doc *here_doc)
{
	here_doc->fd = 0;
	here_doc->filename = NULL;
	here_doc->line = NULL;
	here_doc->tmp = NULL;
	here_doc->delimiter = NULL;
}

static void handle_here_doc(char *delimiter)
{
	char *tmp;
	t_here_doc *here_doc;

	here_doc = malloc(sizeof(t_here_doc));
	if (here_doc == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		// freeeeeeeeeeeeee
		exit(EXIT_FAILURE);
	}
	init_here_doc(here_doc);
	here_doc->filename = "/tmp/proute";
	here_doc->fd = open(here_doc->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
	here_doc->line = ft_calloc(1, 1);
	here_doc->delimiter = delimiter;
	tmp = ft_calloc(1, 1);

	handle_while(here_doc);

	write(here_doc->fd, here_doc->line, ft_strlen(here_doc->line));
	free(here_doc->line);
	free(here_doc->tmp);
}*/

void handle_here_doc(char *delimiter)
{
	char *line;
	char *here_doc_content = NULL;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			ft_printf("\nbash: warning: here-document at line 1 delimited"
					  "by end-of-file (wanted `%s')\n",
					  delimiter);
			break;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		if (here_doc_content == NULL)
			here_doc_content = strdup(line);
		else
		{
			char *temp = malloc(strlen(here_doc_content) + strlen(line) + 2);
			sprintf(temp, "%s\n%s", here_doc_content, line);
			free(here_doc_content);
			here_doc_content = temp;
		}
		free(line);
	}

	printf("\nContenu du here_doc :\n%s\n", here_doc_content);

	// Libérer la mémoire allouée pour le contenu du here_doc
	free(here_doc_content);
}

void syntax_analyse(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			current = current->next;
			handle_here_doc(current->value);
		}
		current = current->next;
	}
}