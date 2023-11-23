#include <stdlib.h>
#include <unistd.h>

size_t strlen(char* str)
{   
    size_t  i;
    
    i = 0;
    while(str[i])
        i++;
}

int new_line(char* str)
{
    while(*str)
    {
        if (*str == '\n')
            return(1);
        str++;
    }
    return(0);
}

char* clean(char* str)
{
    int i;
    
    i = 0;
    while
}

char* get_new_line(char* str)
{
    char* line;
    
    while(str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    line[i] = '\0';
}

char *get_next_line(int fd)
{
    static char* stash;
    char* line;
    char* buffer;
    
    while(buffer != 0 || !new_line(stash))
    {
        read(fd);
        strlcat(stash,buffer,strlen(buffer));
    }
    line = get_new_line(stash);
    stash = clean(stash);
    return(line);
}