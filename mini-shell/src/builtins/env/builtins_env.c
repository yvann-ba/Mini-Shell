#include "../../minishell.h"

static	int	remove_env_var(char *var, char ***env)
{
	int		i;
	size_t	var_len;

	i = 0;
	var_len = ft_strlen(var);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, var_len) \
		== 0 && (*env)[i][var_len] == '=')
		{
			free((*env)[i]);
			while ((*env)[i + 1])
			{
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_unset(t_token *tokens, char ***env, int *exit_status)
{
	t_token	*current;
	int		found;

	found = 0;
	current = tokens->next;
	while (current)
	{
		found |= remove_env_var(current->value, env);
		current = current->next;
	}
	if (found)
		*exit_status = 0;
}

void	ft_env(t_token *arg_lst, char **env, int *exit_status)
{
	int		i;
	char	*equal_sign_ptr;

	i = 0;
	if (arg_lst->next && arg_lst->next->value)
	{
		ft_printf("env: too many arguments\n");
		*exit_status = 127;
		return ;
	}
	while (env[i] != NULL)
	{
		equal_sign_ptr = ft_strchr(env[i], '=');
		if (equal_sign_ptr != NULL && *(equal_sign_ptr + 1) != '\0')
		{
			if (!(*(equal_sign_ptr + 1) == '\'' && *(equal_sign_ptr + 2) \
			== '\'' && *(equal_sign_ptr + 3) == '\0'))
			{
				if (ft_printf("%s\n", env[i]) < 0)
				{
					perror("env command failed");
					*exit_status = 1;
					return ;
				}
			}
		}
		i++;
	}
	*exit_status = 0;
}
