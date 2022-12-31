/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 19:05:51 by dmartiro          #+#    #+#             */
/*   Updated: 2022/04/03 20:34:30 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*linking;

	if (!*lst || !lst || !del)
		return ;
	while (*lst && lst)
	{
		linking = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = linking;
	}
}
