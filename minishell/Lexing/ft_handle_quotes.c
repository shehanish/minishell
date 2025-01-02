/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkaruna <shkaruna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:50:33 by shkaruna          #+#    #+#             */
/*   Updated: 2025/01/02 14:49:44 by shkaruna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include "../minishell.h"

int	valid_quotes(const char *s)
{
	int	in_single_quotes;
	int	in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	while (*s)
	{
		if (*s == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*s == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*s == '\\' && (*(s + 1) == '\'' || *(s + 1) == '"'))
			s++;
		s++;
	}
	if (in_single_quotes || in_double_quotes)
		return (0);
	return (1);
}

static void	parse_single_quotes(const char *s, char *new_value, int *i, int *j)
{
	(*i)++;
	while (s[*i] && s[*i] != '\'')
	{
		new_value[(*j)++] = s[(*i)++];
	}
	if (s[*i] == '\'')
	{
		(*i)++;
	}
}

static char	*extract_var_name(const char *s, int *i)
{
	char	*var_name;
	int		k;
	int		start;

	start = *i;
	while (s[*i] && (isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	var_name = malloc(*i - start + 1);
	if (!var_name)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	k = 0;
	while (start < *i)
		var_name[k++] = s[start++];
	var_name[k] = '\0';
	return (var_name);
}
static void	handle_var_expansion(const char *s, char *new_value, int *i, int *j,
		t_env *env_list)
{
	char	*var_name;
	char	*value;

	(*i)++;
	var_name = extract_var_name(s, i);
	value = get_env_var(env_list, var_name);
	if (value)
	{
		while (*value)
			new_value[(*j)++] = *value++;
	}
	else
	{
		new_value[(*j)++] = '$';
		while (s[*i] && (isalnum(s[*i]) || s[*i] == '_'))
			new_value[(*j)++] = s[(*i)++];
	}
}

static void	parse_double_quotes(const char *s, char *new_value, int *i, int *j,
		t_env *env_list)
{
	(*i)++;
	while (s[*i] && s[*i] != '"')
	{
		if (s[*i] == '\\' && (s[*i + 1] == '"' || s[*i + 1] == '\\'))
			(*i)++;
		else if (s[*i] == '$')
			handle_var_expansion(s, new_value, i, j, env_list);
		else
			new_value[(*j)++] = s[(*i)++];
	}
	if (s[*i] == '"')
		(*i)++;
}

int	parse_quotes_in_tokens(t_token *token_list, t_env *env_list)
{
	t_token	*current;
	char	*s;
	int		i;
	int		j;
	char	*new_value;

	new_value = NULL;
	i = 0;
	j = 0;
	current = token_list;
	t_token *temp = token_list;
	while (temp)
	{
		temp = temp->next;
	}

	while (current)
	{
		if (!current->value)
		{
			fprintf(stderr, "Token value is NULL at parse_quotes_in_tokens\n");
			current = current->next;
			continue ;
		}
		
		if (current->type == WORD)
		{
			s = current->value;
			if (!valid_quotes(s))
			{
				return (0);
			}
			new_value = malloc(strlen(s) + 1);
			if (!new_value)
			{
				fprintf(stderr, "Memory allocation error\n");
				exit(EXIT_FAILURE);
			}
			i = 0;
			j = 0;
			
			while (s[i])
			{
				if (s[i] == '\'')
					parse_single_quotes(s, new_value, &i, &j);
				else if (s[i] == '"')
					parse_double_quotes(s, new_value, &i, &j, env_list);
				else
					new_value[j++] = s[i++];
			}
			new_value[j] = '\0';
			current->value = new_value;
		}
		current = current->next;
	}
	return (1);
}
