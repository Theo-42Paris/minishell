/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzara <tzara@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:58:00 by kjolly            #+#    #+#             */
/*   Updated: 2025/05/20 12:30:48 by tzara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_calloc(1, sizeof(char)));
	if (len > s_len - start)
		len = s_len - start;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*dst;
// 	unsigned int	i;
// 	unsigned int	temp;

// 	i = 0;
// 	if (start > ft_strlen(s))
// 		return (ft_calloc(1, sizeof(char)));
// 	temp = ft_strlen(s + start);
// 	if (temp > len)
// 		temp = len;
// 	dst = malloc(sizeof(char) * temp + 1);
// 	if (dst == NULL)
// 		return (NULL);
// 	while (i < len && s[i + start])
// 	{
// 		dst[i] = s[i + start];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }
// ? la fonction extrait une nouvelle chaine a partir d'une autre
// ? len = taille max de la nouvelle chaine
// ? start = index de debut de la nouvelle chaine
// ! start parcour la source string "n"
// ! i parcour la destination sans depassrr la taille max autoriser par len
/*int	main(void)
{
	const char	s[] = "hola";
	unsigned int start = 0;
	unsigned int len = 18446744073709551615;

	printf("%s\n", ft_substr(s,  start, len));
}*/
