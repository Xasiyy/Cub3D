/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abollia <abollia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:00:48 by abollia           #+#    #+#             */
/*   Updated: 2025/08/31 12:22:05 by abollia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

/*---------------------\\\\\___STRING OPERATIONS___/////----------------------*/

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_wcount(const char *str, int sep);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char	**ft_split(const char *s, char c);
int		ft_filecheck(char *file, char *ext);

/*------------------------\\\\\___IDENTIFYERS___/////-------------------------*/

int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_isonlyspace(char *str);

/*----------------------\\\\\___MEMORY OPERATIONS___/////---------------------*/

/*
* FT_SECUFREE
* free *memspace et le fait pointer sur NULL
* Attention! Il faut caster memspace en void ** lors de l'appel,
* memspace est dereference afin de ne pas le modifier en local.
*/
void	ft_secufree(void **memspace);

/*
* FT_SECUMALLOC
* Attention, prototype uniquement
*/
void	*ft_secumalloc(size_t size);

void	*ft_realloc(void *ptr, size_t newsize);
void	ft_ffa(char ***tab);
void	ft_freetab(int **tab, size_t nmemb);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);

/*----------------------\\\\\___FILE DESCRIPTOR___/////-----------------------*/

void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

/*-----------------------\\\\\___TO CONVERTERS___/////------------------------*/

int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *nptr);
long	ft_atol(const char *str);
char	*ft_itoa(int n);

/*---------------------\\\\\___CHAINED LISTS OPS___/////----------------------*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*-------------------------\\\\\___FT_PRINTF___/////--------------------------*/

int		ft_printf(const char *str, ...);
int		ft_printchar(int c);
int		ft_printstr(const char *str);
int		ft_printnbr(int n);
int		ft_printnbru(unsigned int n);
int		ft_printhex(unsigned long long n, const char format);
int		ft_printptr(void *p);

/*-------------------------\\\\\___FT_DPRINTF___/////-------------------------*/

/*
* FT_DPRINTF
* Comme ft_printf, mais avec precision du fd sur lequel ecrire
*/
int		ft_dprintf(int fd, const char *str, ...);

int		ft_dprintchar(int fd, int c);
int		ft_dprintstr(int fd, const char *str);
int		ft_dprintnbr(int fd, int n);
int		ft_dprintnbru(int fd, unsigned int n);
int		ft_dprinthex(int fd, unsigned long long n, const char format);
int		ft_dprintptr(int fd, void *p);

/*-----------------------\\\\\___GET_NEXT_LINE___/////------------------------*/
char	*get_next_line(int fd);

#endif
