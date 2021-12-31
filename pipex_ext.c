/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-mars <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 15:49:21 by sel-mars          #+#    #+#             */
/*   Updated: 2021/12/28 18:12:34 by sel-mars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(int ret, int comp)
{
	if (comp == -1 && ret == -1)
	{
		perror(0);
		exit(0);
	}
	else if (comp == 5 && ret != 5)
	{
		perror(0);
		exit(0);
	}
	else
		return ;
}

char	**ft_cmd_split(char *cmd)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd, ' ');
	return (cmd_split);
}
