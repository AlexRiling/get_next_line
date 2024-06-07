#include "get_next_line.h" // your get_next_line header
#include <fcntl.h>         // for open
#include <stdio.h>         // for printf, perror
#include <stdlib.h>        // for exit

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		printf("Usage: %s <file_path>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	if (close(fd) == -1)
	{
		perror("Error closing file");
		return (1);
	}
	return (0);
}
