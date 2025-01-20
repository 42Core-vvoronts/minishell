/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 10:16:52 by ipetrov           #+#    #+#             */
/*   Updated: 2024/12/07 12:44:39 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * Removes and frees the file context associated with the given file descriptor.
 *
 * @param fl Pointer to the head of the linked list of file contexts.
 * @param fd File descriptor to remove from the list.
 * @return Always returns NULL.
 */
char	*pop(t_file **fl, int fd)
{
	t_file	*f;
	t_file	*prv;

	f = *fl;
	prv = f;
	while (f)
	{
		if (f->fd == fd)
			break ;
		prv = f;
		f = f->next;
	}
	if (f == *fl)
	{
		*fl = f->next;
		free(f);
	}
	else
	{
		prv->next = f->next;
		free(f);
	}
	return (NULL);
}

/**
 * Retrieves the file context for the given file descriptor,
 * or creates a new one if it doesn't exist.
 *
 * @param fl Pointer to the head of the linked list of file contexts.
 * @param fd File descriptor to retrieve or create the context for.
 * @return Pointer to the file context.
 */
t_file	*get_context(t_file **fl, int fd)
{
	t_file	*f;
	t_file	*prv;

	f = *fl;
	prv = f;
	while (f)
	{
		if (f->fd == fd)
			return (f);
		prv = f;
		f = f->next;
	}
	f = malloc(sizeof(t_file));
	if (!f)
		return (NULL);
	if (prv)
		prv->next = f;
	f->b = 0;
	f->ttl = 0;
	f->next = NULL;
	if (!*fl)
		*fl = f;
	return (f->fd = fd, f->line = NULL, f->i = 0, f);
}

/**
 * Adds a chunk of data from the buffer to the current line in the file context.
 *
 * @param f Pointer to the file context.
 * @param fl Pointer to the head of the linked list of file contexts.
 * @return Pointer to the updated line, or NULL on failure.
 */
char	*add_chunk(t_file *f, t_file *fl)
{
	ssize_t			len;
	char			*old;
	int				j;

	len = 0;
	while (len < (f->b - f->i) && f->buf[f->i + len++] != '\n')
		;
	old = f->line;
	f->line = (char *)malloc(sizeof(char) * (f->ttl + len + 1));
	if (!f->line)
		return (free(old), pop(&fl, f->fd));
	j = -1;
	while (old && old[++j])
		f->line[j] = old[j];
	while (len--)
		f->line[f->ttl++] = f->buf[f->i++];
	(free(old), f->line[f->ttl] = '\0');
	return ((char *)1);
}

/**
 * Reads the next line from the file associated with the given file descriptor.
 *
 * TODO: ability to change mode return lines
 * with \\n or no or mb other delimiters
 *
 *   0 - if no data to read
 * 	 1 - continue to read
 *  -1 - code for error
 *
 * @param fd File descriptor to read from.
 * @param error Pointer to an integer to store error status.
 * @return Pointer to the next line, or NULL on failure or end of file.
 *
 */
int	get_next_line(int fd, char **line)
{
	static t_file	*fl;
	t_file			*f;

	f = ((t_file *)get_context(&fl, fd));
	if (!f || fd < 0 || BUFFER_SIZE <= 0)
		return (pop(&fl, fd), FAIL);
	while (1)
	{
		if (f->i == f->b)
		{
			f->b = read(fd, f->buf, BUFFER_SIZE);
			f->i = 0;
		}
		if (f->b == 0)
			return (*line = f->line, pop(&fl, fd), STOP);
		else if (f->b < 0)
			return (free(f->line), pop(&fl, fd), ERROR);
		if (!add_chunk(f, fl))
			return (free(f->line), pop(&fl, fd), ERROR);
		if (f->line[f->ttl - 1] == '\n' || f->b < BUFFER_SIZE)
			return (f->ttl = 0, *line = f->line, f->line = NULL, CONTINUE);
	}
}
