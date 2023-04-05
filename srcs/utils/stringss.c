#include "cub3d.h"

char	*ft_strchr( const char *s, int c )
{
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

int	is_space( char c )
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*ft_strcpy( char *dst, const char *src )
{
	char	*p;
	
	p = dst;
	while (*src && *src != '\n')
		*p++ = *src++;
	*p = '\0';
	return (dst);
}
