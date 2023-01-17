/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 02:54:04 by dmartiro          #+#    #+#             */
/*   Updated: 2023/01/17 02:54:05 by dmartiro         ###   ########.fr       */
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
