/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_libft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:13:26 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/19 12:29:34 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOT_LIBFT_H
# define NOT_LIBFT_H

# include <stddef.h>

// ----------------------------------------Prototypes
size_t	ft_strlen(const char *s);
char	*ft_itoa(int n);
int		ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(int count, size_t size);

#endif