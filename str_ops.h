#ifndef STR_OPS_H
#define STR_OPS_H
#include <stdlib.h>
int _strcmp(char *s1, char *s2);
int num_of_substr(char *str, char *delimiter);
char **str_split(char *str, char *delimiter);
char **str_split2(char *str, char delimiter);
int _atoi(char *num);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str, int fd);
int _putchar(char c, int fd);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
char *_strstr(const char *haystack, const char *needle);
int _strlen(char *s);
#endif