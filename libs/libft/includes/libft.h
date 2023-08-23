/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:08:14 by nsainton          #+#    #+#             */
/*   Updated: 2023/03/31 16:08:14 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "ansicolorcodes.h"
# include "libft_int.h"
//Functions from file : ft_strjoin.c
char		*ft_strjoin(char const *s1, char const *s2);

//Functions from file : strfuncs.c
char		*ft_strcpy(char *dest, const char *src);

char		*ft_strncpy(char *dest, const char *src, size_t n);

size_t		ft_strncat(char *dest, const char *src, size_t n);

size_t		ft_strcat(char *dest, const char *src);

//Functions from file : parsing.c
void		parse_conv(int *width, int *prec, const char **conv, \
char flags[128]);

void		loop(t_pbuffer *buf, const char **conv);

//Functions from file : tstr_print.c
void		tstr_print(t_str *str);

void		tstr_print_fd(t_str *str, int fd);

//Functions from file : get_next_line.c
int			parse_line(t_gline *line, char buf[BUFFER_SIZE + 1], \
const size_t bytes);

int			fill_line(t_gline *line, char buf[BUFFER_SIZE + 1]);

int			ft_check_line(char buf[BUFFER_SIZE + 1], char *line, \
ssize_t n_read);

char		*get_next_line(int fd);

//Functions from file : atoi_until.c
int			atoi_until(t_cchar *s, t_cchar *base, int *err, t_csizet nb);

//Functions from file : ft_bzero.c
void		ft_bzero(void *s, size_t n);

//Functions from file : memfuncs.c
void		*ft_memchr(const void *s, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		*ft_memcpy(void *dest, const void *src, size_t n);

void		*ft_memmove(void *dest, const void *src, size_t n);

void		*ft_memset(void *b, int c, size_t len);

//Functions from file : tstr_init.c
void		tstr_reinit(t_str *str);

int			tstr_init(t_str *str, size_t size);

int			tstr_initstr(t_str *tstr, char *str, size_t buffsize);

int			tstr_cpy(t_str *dst, const t_str *src);

//Functions from file : tstr_add.c
int			tstr_addchar(t_str *str, int c);

int			tstr_addchar_realloc(t_str **str, int c);

size_t		tstrncat(t_str *str, const char *s, size_t bytes);

int			tstrcat_realloc(t_str **str, const char *s);

//Functions from file : minimum.c
t_sint		ft_minint(t_sint a, t_sint b);

t_uint		ft_minuint(t_uint a, t_uint b);

size_t		ft_minst(size_t a, size_t b);

//Functions from file : ft_itoa.c
char		*ft_itoa(int n);

//Functions from file : base.c
int			ft_atoi_base(t_cchar *s, t_cchar *base, t_csizet base_len);

//Functions from file : ft_strrchr.c
char		*ft_strrchr(const char *s, int c);

//Functions from file : printing.c
void		build_res(t_pbuffer *buf, char *res, char flags[128], int len);

void		print_res(t_pbuffer *buf, char *res, int len, t_print *pads);

//Functions from file : print_fd.c
int			ft_putchar_fd(t_cchar c, t_cint fd);

int			ft_putstr_fd(t_cchar *s, t_cint fd);

int			putnstr(t_cchar *s, t_csizet n, t_cint fd);

int			ft_putendl_fd(t_cchar *s, t_cint fd);

int			ft_putnbr_fd(t_cint n, t_cint fd);

//Functions from file : helpers.c
int			max_int(int a, int b);

int			min_int(int a, int b);

t_ull		abs_ll(t_ll a);

t_ull		itou(int n);

t_ull		lltoull(t_ll n);

//Functions from file : ft_split.c
char		**ft_split(char const *s, char c);

//Functions from file : count_equal.c
t_llong		findlongestsubstr(t_cchar *haystack, t_cchar *needle);

//Functions from file : ft_strmapi.c
char		*ft_strmapi(char const *s, int (*f) (unsigned int, int));

//Functions from file : ft_substr.c
char		*ft_substr(char const *s, unsigned int start, size_t len);

//Functions from file : ascii2.c
int			ft_isupper(int c);

int			ft_islower(int c);

int			ft_isalpha(int c);

int			ft_tolower(int c);

int			ft_toupper(int c);

//Functions from file : length.c
size_t		ft_strlen(const char *s);

size_t		ft_strnlen(const char *s, size_t maxlen);

size_t		tablen(const void *tab, size_t elemsize);

//Functions from file : ft_strlcat.c
size_t		ft_strlcat(char *dst, const char *src, size_t size);

//Functions from file : ft_strtrim.c
char		*ft_strtrim(char const *s1, char const *set);

//Functions from file : lst_delelem.c
void		ft_lstdelone(t_list *lst, void (*del) (void *));

void		ft_lstclear(t_list **lst, void (*del) (void *));

void		ft_lstdel_front(t_list **lst, void (*del) (void *));

//Functions from file : decimal.c
void		put_pos(t_ull nb, char **tab, char *base);

void		put_dec(t_pbuffer *buf, va_list *ap, char flags[128]);

void		put_unsigned(t_pbuffer *buf, va_list *ap, char flags[128]);

//Functions from file : init.c
void		init_pbuf_fd(t_pbuffer *buf, int fd);

void		init_pbuf_str(t_pbuffer *buf, t_str *str);

void		set_pad(char flags[128], t_print *pads);

t_pfunc		*get_funcs(void);

//Functions from file : lst_addelem.c
t_list		*ft_lstnew(void *content);

t_list		*ft_lstnew_cpy(t_cvoid *content, size_t size);

void		ft_lstadd_front(t_list **lst, t_list *new);

void		ft_lstadd_back(t_list **lst, t_list *new);

//Functions from file : strings.c
void		put_char(t_pbuffer *buf, va_list *ap, char flags[128]);

void		put_string(t_pbuffer *buf, va_list *ap, char flags[128]);

//Functions from file : flush.c
void		flush(t_pbuffer *buf);

void		flush_fd(t_pbuffer *buf);

void		flush_str(t_pbuffer *buf);

//Functions from file : lst_functions.c
int			ft_lstsize(t_clist *lst);

t_list		*ft_lstlast(t_clist *lst);

void		ft_lstiter(t_list *lst, void (*f) (void *));

t_list		*ft_lstmap(t_list *lst, void *(*f) (void *), \
void (*del) (void *));

//Functions from file : putnbr_tab.c
void		put_uns_tab(t_ull nb, char **tab, char *base, size_t len);

void		put_nb_tab(t_ll nb, char *tab, char *base);

//Functions from file : ft_atoi.c
int			ft_atoi(const char *nptr);

//Functions from file : colors_print.c
int			print_color_string(t_cvoid *s, t_cchar *color, t_cint fd);

int			print_color_number(t_cvoid *nb, t_cchar *color, t_cint fd);

t_colorfunc	chose_function(t_cint type);

int			print_color(t_cvoid *s, t_cint type, t_cchar *color, \
t_cint fd);

int			print_colors(t_cvoid **s, t_cint *type, t_cchar **colors, \
t_cint *infos);

//Functions from file : lst_access.c
void		setnext(t_list *node, t_list *next);

t_list		*getnext(t_clist *node);

void		setcontent(t_list *node, void *content);

void		*getcontent(t_clist *node);

//Functions from file : tstr_alloc.c
t_str		*tstr_realloc(t_str *old_string, size_t new_size);

//Functions from file : ft_strchr.c
char		*ft_strchr(const char *s, int c);

//Functions from file : ft_sprintf.c
int			ft_snprintf(char *str, size_t size, const char *format, ...);

int			ft_sprintf(t_str *str, const char *format, ...);

int			ft_vsnprintf(t_str *str, const char *format, va_list ap);

//Functions from file : ft_strdup.c
char		*ft_strdup(const char *s);

//Functions from file : hexadecimal.c
void		put_hex_min(t_pbuffer *buf, va_list *ap, char flags[128]);

void		put_hex_maj(t_pbuffer *buf, va_list *ap, char flags[128]);

//Functions from file : allocation.c
void		*ft_calloc(size_t nmemb, size_t size);

void		*ft_reallocf(void *memzone, t_csizet old_size, size_t new_size);

void		*ft_realloc(void *memzone, t_csizet old_size, t_csizet new_size);

//Functions from file : percent.c
void		put_percent(t_pbuffer *buf, va_list *ap, char flags[128]);

//Functions from file : ft_strnstr.c
char		*ft_strnstr(const char *s1, const char *s2, size_t n);

//Functions from file : ascii1.c
int			ft_isalnum(int c);

int			ft_isascii(int c);

int			ft_isdigit(int c);

int			ft_isprint(int c);

int			ft_isspace(int c);

//Functions from file : ft_striteri.c
void		ft_striteri(char *s, void (*f) (unsigned int, char *));

//Functions from file : atoi_errors.c
int			atoi_errors_space(t_cchar *s, t_cchar *base, int *err);

int			atoi_errors(t_cchar *s, t_cchar *base, int *err);

//Functions from file : ft_strlcpy.c
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

//Functions from file : ft_strncmp.c
int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_strcmp(t_cchar *s1, t_cchar *s2);

int			cmp_until(t_cchar *s1, t_cchar *s2, t_cchar c);

//Functions from file : tstr_del.c
void		tstr_del(t_str *str);

//Functions from file : ft_printf.c
int			ft_printf(const char *format, ...);

int			ft_dprintf(int fd, const char *format, ...);

int			ft_vdprintf(int fd, const char *format, va_list ap);

//Functions from file : pbuffer.c
void		add_char(t_pbuffer *buf, char c);

void		add_nchar(t_pbuffer *buf, char c, int n);

void		add_str(t_pbuffer *buf, char *str);

void		add_nstr(t_pbuffer *buf, char *str, int n);

void		add_conv(t_cchar **s, t_pbuffer *buf, va_list *cpy, \
char flags[128]);

//Functions from file : address.c
void		put_address(t_pbuffer *buf, va_list *ap, char flags[128]);

//Functions from file : strtoll_errors.c
t_ll		strtoll_errors(t_cchar *s, t_cchar *base, int *err);

#endif