#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (0);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	result = (char *)malloc(l1 + l2 + 1);
	if (result != NULL)
	{
		ft_memcpy(result, s1, l1);
		ft_memcpy(result + l1, s2, l2 + 1);
	}
	return (result);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*lol1;
	unsigned char	*lol2;
	int				i;

	i = 0;
	if (dst == 0 && src == 0)
		return (0);
	lol1 = (unsigned char *)src;
	lol2 = (unsigned char *)dst;
	while (n > 0)
	{
		lol2[i] = lol1[i];
		n--;
		i++;
	}
	return (dst);
}	

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
