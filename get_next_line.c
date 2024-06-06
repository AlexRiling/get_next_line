
#define BUFFER_SIZE 10

char *get_next_line(int fd)
{
	static char *remainder;
	char buffer[BUFFER_SIZE + 1];
	int bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
	}
}
