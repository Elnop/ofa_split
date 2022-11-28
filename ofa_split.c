#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

bool	ischarset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}

char **mk_tab(char *str, char *charset)
{
	size_t	len;
	size_t	wc;
	size_t	csc;

	len = 0;
	csc = 0;
	wc = 0;
	while (str[len])
	{
		while (ischarset(str[len++], charset))
			csc++;
		if (!*str)
			break ;
		wc++;
		while (str[len] && !ischarset(str[len], charset))
			len++;
	}
	return(malloc((wc + 1) * sizeof(char *) + (len - csc + wc) * sizeof(char)));
}

size_t	wordlen(char *str, char *charset)
{
	size_t	i;

	i = 0;
	while (str[i] && !ischarset(str[i], charset))
		i++;
	return (i);
}

char	**ofa_split(char *str, char *charset)
{
	char	**tab;
	size_t	i;
	size_t	tab_index;

	tab = mk_tab(str, charset);
	if (!tab)
		return (NULL);
	tab_index = 0;
	while (*str)
	{
		while (ischarset(*str, charset))
			str++;
		if (!*str)
			break ;
		tab[tab_index] = malloc((wordlen(str, charset) + 1) * sizeof(char));
		i = 0;
		while (*str && !ischarset(*str, charset))
			tab[tab_index][i++] = *str++;
		tab[tab_index++][i] = 0;
	}
	tab[tab_index] = NULL;
	return (tab);
}

/*
#include <stdio.h>

int main()
{
	printf("- %s\n", ofa_split("Hello world", " ")[0]);
	printf("- %s\n", ofa_split("Hello world", " ")[1]);
	printf("- %s\n", ofa_split("Hello world", " ")[2]);
}
*/