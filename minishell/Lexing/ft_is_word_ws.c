/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_word_ws.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:35:12 by grmullin          #+#    #+#             */
/*   Updated: 2025/01/02 12:49:02 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_is_whitespace(t_token **head, t_token **tmp, char *line, int *i)
{
    (void)head;
    (void)tmp;
    if (line[*i] == ' ')
    {
        while (line[*i] && line[*i] == ' ')
            *i += 1;
    }
}

void ft_is_word(t_token **head, t_token **tmp, char *line, int *i)
{
    char *value;
    int len;

    if (is_char(line, i))
    {
        value = ft_strdup(""); // Allocate memory for an empty string
        while (line[*i] && line[*i] != '|' && line[*i] != '>' && line[*i] != '<')
        {
            char *substr = ft_substr(line, *i, 1); // Allocate memory for the character at position *i
            char *new_value = ft_strjoin(value, substr); // Allocate new string
            free(value); // Free the old value after it has been joined
            free(substr); // Free the temporary substring
            value = new_value; // Set value to the new concatenated string
            (*i)++;
        }
        len = ft_strlen(value);
        if (value[len - 1] == ' ') // Trim trailing space if necessary
            value[len - 1] = '\0';
        create_token(head, tmp, value, WORD); // Pass value to create_token
        // Do not free value here, as create_token likely takes ownership
    }
}

// void    ft_is_word(t_token **head, t_token **tmp, char *line, int *i)
// {
//     char    *value;
//     int     len;
    
//     if (is_char(line, i))
//     {
//         value = ft_strdup("");
//         while (line[*i] && line[*i] != '|' && line[*i] != '>' && line[*i] != '<')
//         {
//             value = ft_strjoin(value, ft_substr(line, *i, 1));
//             *i += 1;
//         }
        
//         len = ft_strlen(value);
//         if (value[len - 1] == ' ')
//             value[len - 1] = '\0';
//         create_token(head, tmp, value, WORD);
//     }
// }

int is_char(char *line, int *i)
{
    if (line[*i] != '|' && line[*i] != '>' 
        && line[*i] != '<')
        return (1);
    return (0);
}