#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 64

typedef struct Indices
{
    size_t *inds;
    size_t length;
} Indices;

typedef struct SplitStruct
{
    char **strs;
    size_t length;
} SplitStruct;

void get_text(char *str)
{
    int ch, i;
    i = 0;

    while ((ch = getchar()) != '\n' && i < BUFFER_SIZE)
    {
        str[i++] = ch;  
    }
    str[i] = '\0';
}

Indices *ind_of(char *str, char ch)
{
    size_t len = 0;
    size_t count = 0;
    size_t i = 0;
    Indices *res = malloc(sizeof(Indices));

    while(str[len])
    {
        if (str[len++] == ch)
        {
            count++;
        } 
    }

    res->inds = malloc(sizeof(size_t) * count);
    res->length = count;
    len = 0;

    while(str[len])
    {
        if (str[len] == ch)
        {
            res->inds[i++] = len;
        }
        len++;
    }
    return res;
}

SplitStruct *split(char *str, char ch)
{
    int x = 0, j = 0, k = 0;
    Indices *i = ind_of(str, ch);
    SplitStruct *s = malloc(sizeof(SplitStruct));
    s->strs = malloc(sizeof(char *) * i->length + 1);
    s->length = i->length + 1;
    for (int k = 0; x < i->length; x++)
    {
        s->strs[x] = malloc(sizeof(char) * i->inds[x] - (x > 0 ? i->inds[x - 1] : 0) + 1);
        
        while (j < i->inds[x])
        {
           s->strs[x][k++] = str[j++];    
        }   
        s->strs[x][k] = '\0';
        k = 0;
        j += 2; // gets rid of the space after comma, might get rid of this/handle better
        
    }

    int remaining_len = j;
    while(str[remaining_len++]);
    s->strs[x] = malloc(sizeof(char) * remaining_len);
    while(str[j])
    {
        s->strs[x][k++] = str[j++]; 
    }
    s->strs[x][k] = '\0';
    
    return s;
}

int main()
{
    char str[BUFFER_SIZE]; 
    get_text(str);
    SplitStruct *s = split(str, ',');
    for (int i = 0; i < s->length; i++)
    {
        printf("\n%s", s->strs[i]);
    } 
    return 0;
}

