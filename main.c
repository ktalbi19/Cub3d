#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define BUFFER_SIZE 64

typedef struct s_struct
{
    char    **map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int     F;
	int     C;
}	t_struct;

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	long int	res;
	long int	sign;

	res = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - 48);
		if (res * sign > INT_MAX)
			return (-1);
		if (res * sign < INT_MIN)
			return (0);
		str++;
	}
	return (res * sign);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n > 0 && str1[i] && str2[i] && str1[i] == str2[i])
	{
		i++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (str1[i] - str2[i]);
}

int	ft_linelen(char *line)
{
	int	i;

	if (!line)
		return (-1);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_getline(int len, char *read)
{
	char	*line;
	int		i;

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = read[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*ft_clearline(int len, char *read)
{
	char	*output;
	int		i;

	if (read == NULL || (ft_strlen(read) - len + 1) == 0)
		return (NULL);
	output = malloc(ft_strlen(read) - len + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (read[len + i])
	{
		output[i] = read[len + i];
		i++;
	}
	output[i] = '\0';
	free (read);
	return (output);
}

int	ft_newread(int fd, char **oldread)
{
	int		count;
	char	newread[BUFFER_SIZE + 1];
	char	*output;
	int		i;
	int		new_i;

	count = read(fd, newread, BUFFER_SIZE);
	newread[count] = '\0';
	output = malloc(ft_strlen(*oldread) + count + 1);
	if (!output)
		return (-1);
	i = 0;
	while (oldread[0][i])
	{
		output[i] = oldread[0][i];
		i++;
	}
	new_i = 0;
	while (newread[new_i])
		output[i++] = newread[new_i++];
	output[i] = '\0';
	free(*oldread);
	*oldread = output;
	return (count);
}

int	validparams(int fd, char **line, char **readbuff)
{
	if (*readbuff == NULL)
	{
		*readbuff = malloc(sizeof(char));
		if (!*readbuff)
			return (-1);
		**readbuff = '\0';
	}
	if (fd < 0 || !line
		|| BUFFER_SIZE <= 0 || fd > 4096)
	{
		free (*readbuff);
		*readbuff = NULL;
		return (-1);
	}
	return (1);
}

int	end_of_read(int rdcount, char **readbuff, char **line)
{
	int	len;

	if (rdcount == 0 && ft_strlen(*readbuff) <= 0)
	{
		free(*readbuff);
		*readbuff = NULL;
		*line = malloc(sizeof(char));
		if (!*line)
			return (-1);
		**line = '\0';
	}
	else if (rdcount == 0)
	{
		len = ft_strlen(*readbuff);
		*line = ft_getline(len, *readbuff);
		free(*readbuff);
		*readbuff = NULL;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*readbuff;
	int			linelen;
	int			readcount;

	if (validparams(fd, line, &readbuff) < 0)
		return (-1);
	linelen = ft_linelen(readbuff);
	while (linelen < 0)
	{
		readcount = ft_newread(fd, &readbuff);
		if (!readbuff || readcount < 0)
			return (-1);
		else if (readcount == 0)
			return (end_of_read(readcount, &readbuff, line));
		linelen = ft_linelen(readbuff);
	}
	*line = ft_getline(linelen, readbuff);
	readbuff = ft_clearline(linelen + 1, readbuff);
	return (1);
}

void	*null_error(char *message)
{
	printf(" Error\n %s\n", message);
	return (0);
}

static int	file_linecount(char *file)
{
	int		linecount;
	int		fd;
	int		readcount;
	char	c;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (-1);
	linecount = 1;
	while (1)
	{
		readcount = read(fd, &c, 1);
		if (readcount == 0)
			break ;
		if (readcount < 0)
			return (-1);
		if (c == '\n')
			linecount++;
	}
	close(fd);
	return (linecount);
}

static char	**alloc_columns(char *file)
{
	char	**map;
	int		line_count;

	line_count = file_linecount(file);
	if (line_count <= 0)
		return (null_error("open or reading error, the file may not exist"));
	map = malloc(sizeof(char *) * line_count + 1);
	if (map == NULL)
		return (null_error("malloc error on alloc_map()"));
	return (map);
}

void	printf_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			write(1, &map[i][j], 1);
	}
	return ;
}

void    get_color2(char nbr[], char nbg[], char nbb[], t_struct *p, char c)
{
    int r;
    int g;
    int b;
    int output;

    r = ft_atoi(nbr);
    g = ft_atoi(nbg);
    b = ft_atoi(nbb);
    output = 256 * 256 * r + 256 * g + b;
    if (c == 'F')
        p->F = output;
    else
        p->C = output;

}

void    get_color(char *line, t_struct *p, char c)
{
    int     i = 0;
    int     j = 0;
    char    nbr[3];
    char    nbg[3];
    char    nbb[3];

    while (!ft_isdigit(line[i]))
        i++;
    while (ft_isdigit(line[i])){
        nbr[j++] = line[i++];
    }
    nbr[j] = '\0';
    j = 0;
    while (!ft_isdigit(line[i]))
        i++;
    while (ft_isdigit(line[i]))
        nbg[j++] = line[i++];
    nbg[j++] = '\0';
    j = 0;
    while (!ft_isdigit(line[i]))
        i++;
    while (ft_isdigit(line[i]))
        nbb[j++] = line[i++];
    nbb[j] = '\0';
    get_color2(nbr, nbg, nbb, p, c);
}

char	*get_path(char *line)
{
	char	*ret;
	int	j = 0;
	int	i = 0;
	int	z = 0;

	while (line[i] != '.')
		i++;
	z = i;
	while (line[i] !='\n')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	while (line[z] != '\n')
	{
		ret[j] = line[z];
		z++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

void	str_comp(char *line, t_struct *p)
{
	if (strcmp("NO", line) == 0)
		p->NO = get_path(line);
	if (strcmp("SO", line) == 0)
		p->SO = get_path(line);
	if (strcmp("WE", line) == 0)
		p->WE = get_path(line);
	if (strcmp("EA", line) == 0)
		p->EA = get_path(line);
	if (strcmp("F", line) == 0)
		get_color(line, p, 'F');
	if (strcmp("C", line) == 0)
		get_color(line, p, 'C');
	return ;
}

int ft_countlines(char **map, int pos_map)
{
    int i;

    i = 0;
    while (map[pos_map++])
        i++;
    return (i);
}

int ft_countchar(char **map, int pos_map)
{
    int i;

    i = 0;
	printf("%s\n", map[pos_map]);
	printf("BLUBLUBLU2\n");
    while (map[pos_map][i])
        i++;
	printf("BLUBLUBLU3\n");
    return (i);
}

char    **get_map(char **map, int pos_map, t_struct *p)
{
    char    **new;
    int     x = 0;
    int     y = 0;
    int     nb_lines;

    pos_map++;
    nb_lines = ft_countlines(map, pos_map);
    new = malloc(sizeof(char *) * nb_lines + 1);
    if (!new)
        return (NULL);
    new[nb_lines] = NULL;
    printf("%s", new[y]);
    while (map[pos_map])
    {
        x = -1;
		printf("%s\n", map[pos_map]);
        new[y] = malloc(sizeof(char) * ft_countchar(map, pos_map) + 1);
		printf("BLUBLUBLU\n");
        if (!new[y])
            return (NULL);
        while (map[pos_map][++x]){
            new[y][x] = map[pos_map][x];}
        //new[y][x] = '\0';
        pos_map++;
        y++;
    }
    return (new);
}

void	check_init_params(char **map, t_struct *p)
{
	int	i, j, z;

	z = 0;
	i = -1;

    printf("_0_0_0_0_0_0_0_0\n");
    printf_map(map);
    printf("_0_0_0_0_0_0_0_0\n");
	while (map[++i])
	{
		if (p->NO == NULL || p->SO == NULL || p->WE == NULL || p->EA == NULL || p->C == 0 || p->F == 0)
			str_comp(map[i], p);
        if (p->NO && p->SO && p->WE && p->EA && p->C && p->F)
            break ;
    }
    printf("*^^^^^^^^^^^^\n");
    printf_map(map);
    printf("^^^^^^^^^^^^*\n");
    p->map = get_map(map, i, p);
    printf("\n********************\n");
    printf_map(p->map);
}

void	init(t_struct *p)
{
	p->NO = NULL;
	p->SO = NULL;
	p->WE = NULL;
	p->EA = NULL;
	p->C = 0;
	p->F = 0;
}

int	main(int ac, char **av)
{
	int		i, fd;
	char	**map;
	t_struct	p;

	map = alloc_columns(av[1]);
	if (map == NULL)
		return (0);
	fd = open(av[1], O_RDONLY);
	i = 0;
	while (get_next_line(fd, &map[i++]))
		;
	map[i] = NULL;
	close(fd);
	printf_map(map);
	init(&p);
	check_init_params(map, &p);
	return (0);
}
