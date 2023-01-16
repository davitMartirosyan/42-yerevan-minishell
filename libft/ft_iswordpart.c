/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_iswordpart.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dmartiro		 <dmartiro		@student.42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/10/23 07:03:19 by root			  #+#	#+#			 */
/*   Updated: 2022/11/30 13:24:33 by dmartiro					 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int ft_iswordpart(int ch)
{
	if (!ft_isspace(ch) && !ft_isspecial(ch))
		return (1);
	else
		return (0);
}