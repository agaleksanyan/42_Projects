#include "libft.h"

static int	count_word(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**free_words(char **words, int j)
{
	while (j > 0)
	{
		j--;
		free(words[j]);
	}
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int	i;
	int	j;
	int	start;
	int	end;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	words = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			end = i;
			words[j] = ft_substr(s, start, end - start);
			if (!words[j])
				return free_words(words, j);
			j++;
		}
	}
	words[j] = NULL;
	return (words);
}
