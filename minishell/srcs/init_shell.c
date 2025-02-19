/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/23 12:03:46 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	ft_crtl_c(130);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_generate_newlevel(t_shell *shell)
{
	char	*level;
	char	*newlevel;
	char	*levelstr;

	level = ft_getenv("SHLVL", &shell->envp_list);
	if (level == NULL)
		ft_export_new_key("SHLVL=1", shell);
	if (level == NULL)
		return ;
	levelstr = ft_itoa(ft_atoi(level) + 1);
	if (levelstr == NULL)
		ft_export_on_same_key("SHLVL=1", shell);
	if (levelstr == NULL)
		return ;
	newlevel = ft_strdup("SHLVL=000000000000");
	if (newlevel == NULL)
		return ;
	ft_strlcpy(newlevel + 6, levelstr, ft_strlen(levelstr) + 1);
	ft_export_on_same_key(newlevel, shell);
	ft_update_envp_matrix(shell);
	free(levelstr);
	free(newlevel);
}

void	ft_init_shell(t_shell *shell, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	shell->envp_list = ft_get_envp_list(envp);
	shell->envp = ft_matdup(envp);
	envp = shell->envp;
	shell->line = NULL;
	shell->cmd = NULL;
	shell->cmdstmp = NULL;
	shell->status = 0;
	shell->heredoc_exitstatus = 0;
	shell->pipe_fd[0] = 0;
	shell->pipe_fd[1] = 1;
	ft_generate_newlevel(shell);
}

t_env	*ft_get_envp_list(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == NULL)
			return (NULL);
		tmp->key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		tmp->equal = 1;
		tmp->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		tmp->next = env;
		env = tmp;
		i++;
	}
	return (env);
}
