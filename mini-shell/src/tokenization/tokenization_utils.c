#include "../minishell.h"

void	add_word_token(const char **input, t_token **head,
			char **env, t_minishell *shell)
{
	char		*substituted_value;
	char		*token_temp;
	(void)env;
	shell->is_single_quote = 0;
	shell->is_double_quote = 0;
	substituted_value = NULL;
	token_temp = ft_strdup("");
	if (!token_temp)
		return ;
	if (**input && !ft_isspace(**input) && !is_special_char(**input))
		handle_quotes(input, head, shell, &token_temp);
	if (token_temp && *token_temp)
	{
		substituted_value = substitute_env_vars(token_temp, env, shell);
		add_token(head, init_token(TOKEN_WORD, substituted_value, shell));
		free(substituted_value);
	}
	free(token_temp);
}

int	is_special_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	identify_double_char_tokens(const char **input, t_token **head, t_minishell *shell)
{
	if (**input == '>' && *(*input + 1) == '>')
	{
		add_token(head, init_token(TOKEN_DOUBLE_REDIRECT_OUT, ">>", shell));
		*input += 2;
		return ;
	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		add_token(head, init_token(TOKEN_HEREDOC, "<<", shell));
		*input += 2;
		return ;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	current = *tokens;
	while (current != NULL)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = next;
	}
	*tokens = NULL;
}

// void	free_tokens(t_token **tokens)
// {
// 	t_token *next;

// 	if (tokens == NULL || *tokens == NULL)
// 		return;
// 	while (*tokens != NULL)
// 	{
// 		next = (*tokens)->next;
// 		if ((*tokens)->value != NULL)
// 		{
// 			free((*tokens)->value);
// 			(*tokens)->value = NULL;
// 		}
// 		free(*tokens);
// 		*tokens = next;
// 	}
// }