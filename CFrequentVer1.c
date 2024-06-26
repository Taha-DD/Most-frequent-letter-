#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#define H 26

typedef struct {
    char chrctr;
    int frqncy;
} alph;

void stralloc ( char **str ) {
    *str = ( char* ) realloc ( *str, strlen( *str ) + 1 );
    if ( *str == NULL ) {
        printf(" str's memory re-allocation failed");
        raise(SIGABRT);
    }
}

void alfalloc ( alph **i, int n ) {
    *i = ( alph* ) realloc ( *i, n * sizeof( alph ) );
    if ( *i == NULL ) {
        printf(" i's memory re-allocation failed");
        raise(SIGABRT);
    }
}

char *strtolower ( char *str ) {
    char *st = ( char* ) malloc ( strlen( str ) + 1 );
    if ( st == NULL ) {
        printf(" st's memory re-allocation failed");
        raise(SIGABRT);
    }
    strcpy( st, str );
    for ( char *s = st; *s; ++s )
        *s = tolower( *s );
    return st;
}

alph* frqncounter ( char *str ) {
    int r = 1;
    alph *i = ( alph* ) calloc ( H, sizeof( alph ) );
    if ( i == NULL ) {
        printf(" i's contiguous allocation failed");
        raise(SIGABRT);
    }
    
    char *temp = ( char* ) malloc ( H );
    if ( temp == NULL ) {
        printf(" temp's memory re-allocation failed");
        raise(SIGABRT);
    }
    
    for ( char *s = str; *s; ++s ) {
        if ( !isalpha(*s) ) continue;
        int k = 0;
        
        char *p = s;
        
        if ( strchr( strtolower( temp ), tolower( *s ) ) ) continue;
        
        int n = strlen(temp);
        temp[n] = *s;
        temp[n + 1] = '\0';

        while ( p ) {
            k++;
            p++;
            p = strchr( strtolower( p ), tolower( *s ) );
        }

        if ( k > i -> frqncy ) {
            free( i );
            i = ( alph* ) calloc ( H, sizeof( alph ) );
            if ( i == NULL ) {
                printf(" i's contiguous allocation failed");
                raise(SIGABRT);
            }
            r = 1;
            i->frqncy = k;
            i->chrctr = *s;
        }
        else if ( k == i -> frqncy ) {
            r = 1;
            for (alph *o = i; o < i + H; ++o, ++r )
                if ( !o -> chrctr ) {
                    o->frqncy = k;
                    o->chrctr = *s;
                    break;
                }
        }
    }
    
    alfalloc( &i, r );
    return i;
}

int main()
{
    char *str = ( char* ) malloc ( 400 );
    if ( str == NULL ) {
        printf(" memory allocation failed");
        raise(SIGABRT);
    }

    printf(" enter a string: ");
    gets( str );

    stralloc( &str);

    alph *i = frqncounter ( str );
    if ( !i->frqncy )
        printf(" there's no alphabetical characters");
    else {
        printf(" the most repeated characters are:");
        for(int r = 0; i[r].frqncy; ++r )
            printf("\n \"%c\" with %d occurrences", i[r].chrctr, i[r].frqncy);
    }
    
    free( str ); free( i );
    str = NULL; i = NULL;
    return 0;
}