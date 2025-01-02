/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:59:45 by grmullin          #+#    #+#             */
/*   Updated: 2024/12/18 12:22:39 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdlib.h>
#include <stdio.h> // For debugging purposes if needed

static size_t	count_str(char const *s, char const c)
{
	size_t	i;
	size_t	strcount;

	i = 0;
	strcount = 0;
	if (s[0] != '\0' && s[0] != c)
		strcount++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] && s[i + 1] != c)
			strcount++;
		i++;
	}
	return (strcount);
}

static size_t	count_char(char const *s, char const c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char	*newstr(char const *s, char c)
{
	size_t	i;
	size_t	charcount;
	char	*str;

	i = 0;
	charcount = count_char(s, c);
	str = (char *)malloc(sizeof(char) * (charcount + 1));
	if (str == NULL)
		return (NULL);
	while (i < charcount)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	p;
	size_t	strcount;
	char	**ar;

	i = 0;
	p = 0;
	if (s == NULL)
		return (NULL);
	strcount = count_str(s, c);
	ar = (char **)malloc(sizeof(char *) * (strcount + 1));
	if (ar == NULL)
		return (NULL);
	while (i < strcount)
	{
		while (s[p] != '\0' && s[p] == c)
			p++;
		ar[i] = newstr(s + p, c);
		while (s[p] != '\0' && s[p] != c)
			p++;
		i++;
	}
	ar[i] = NULL;
	return (ar);
}

// static char	**free_array(char **ptr, int i)
// {
// 	while (i > 0)
// 	{
// 		i--;
// 		free(ptr[i]);
// 	}
// 	free(ptr);
// 	return (0);
// }

// static int	ft_count_words(const char *s, char c)
// {
// 	int	i;
// 	int	count;
	
	
// 	if (s == NULL) // Check if the input string is NULL
//         return 0; 
// 	i = 0;
// 	count = 0;
// 	while (s[i] && s[i] != '\0')
// 	{
// 		if (s[i] == c)
// 			i++;
// 		else
// 		{
// 			count++;
// 			while (s[i] && s[i] != c)
// 				i++;
// 		}
// 	}
// 	return (count);
// }

// static char	*ft_putword(char *word, const char *s, int i, int word_len)
// {
// 	int	j;

// 	j = 0;
// 	while (word_len > 0)
// 	{
// 		word[j] = s[i - word_len];
// 		j++;
// 		word_len--;
// 	}
// 	word[j] = '\0';
// 	return (word);
// }

// static char	**ft_split_enter(const char *s, char c, char **strings, int count)
// {
// 	int	i;
// 	int	word;
// 	int	word_len;

// 	i = 0;
// 	word = 0;
// 	word_len = 0;
// 	while (word < count)
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		while (s[i] && s[i] != c)
// 		{
// 			i++;
// 			word_len++;
// 		}
// 		strings[word] = (char *)malloc(sizeof(char) * (word_len + 1));
// 		if (strings[word] == NULL)
// 			return (free_array(strings, word));
// 		ft_putword(strings[word], s, i, word_len);
// 		word_len = 0;
// 		word++;
// 	}
// 	strings[word] = 0;
// 	return (strings);
// }

// char **ft_split(const char *s, char c)
// {
//     char **strings;
//     unsigned int count;

//     if (s == NULL) // Check if the input string is NULL
//         return NULL; // Return NULL if it is

//     count = ft_count_words(s, c);
//     strings = (char **)malloc(sizeof(char *) * (count + 1));
//     if (strings == NULL)
//         return NULL;

//     // Proceed with splitting the string...
//     strings = ft_split_enter(s, c, strings, count);
//     return strings;
// }
