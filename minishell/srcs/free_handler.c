/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efaustin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:29 by efaustin          #+#    #+#             */
/*   Updated: 2025/01/23 12:03:46 by efaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_free_all(t_shell *shell, int flag, int ret_stat)
{
	if (shell->envp != NULL)
		ft_free_args(shell->envp);
	if (shell->envp_list != NULL)
		ft_free_envp_list(shell->envp_list);
	if (shell->line != NULL)
		free(shell->line);
	if (shell->cmd != NULL)
		free_cmd(&shell->cmd);
	if (shell->cmdstmp != NULL && flag == true)
		ft_free_args(shell->cmdstmp);
	close(shell->pipe_fd[0]);
	close(shell->pipe_fd[1]);
	if (ret_stat == true)
		return (shell->status);
	return (1);
}

void	ft_free_envp_list(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		if (env->key != NULL)
			free(env->key);
		if (env->value != NULL)
			free(env->value);
		if (env != NULL)
			free(env);
		env = NULL;
		env = tmp;
	}
	env = NULL;
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
		free(args[i++]);
	if (args != NULL)
		free(args);
	args = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd != NULL)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->args != NULL)
			ft_free_args((*cmd)->args);
		if ((*cmd)->fd.filename_in != NULL)
			free((*cmd)->fd.filename_in);
		if ((*cmd)->fd.filename_out != NULL)
			free((*cmd)->fd.filename_out);
		if ((*cmd)->fd.fd_out != STDOUT_FILENO && (*cmd)->fd.fd_out > 0)
			close((*cmd)->fd.fd_out);
		if ((*cmd)->fd.fd_in != STDIN_FILENO && (*cmd)->fd.fd_in > 0)
			close((*cmd)->fd.fd_in);
		if ((*cmd)->cmd != NULL)
			free((*cmd)->cmd);
		if (*cmd != NULL)
			free(*cmd);
		*cmd = tmp;
	}
	*cmd = NULL;
}
