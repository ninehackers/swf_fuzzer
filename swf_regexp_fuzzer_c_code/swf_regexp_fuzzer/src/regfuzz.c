
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "regfuzz.h"

enum {
    REGEXMATCHEDPAIR, /* characters that only make sense in matched pairs */
    REGEXESCAPEDCHAR, /* escaped characters */
    REGEXSPECIALCHAR, /* characters with special meaning */
    REGEXQUANTIFY,    /* quantifiers, eg {m,n} */
    REGEXEXTENSION,   /* special extension */
    REGEXREPEATEDCHAR,/* repeat a rand character */
    REGEXRANDOM,      /* rand character */
    REGEXEND,         /* possible end of expression */
    REGEXCHAR,        /* rand character */
    REGEXPROPERTY,    /* unicode property (perl/pcre) */
    REGEXPOSIX,       /* posix property */
    NREGEXTYPES
};

//#define min(x,y) (((x) > (y)) ? (y) : (x))
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#define M(buf) (MAX(maxlen - strlen(buf), 0))
unsigned long seed = 0;

char* my_strndup(char* buf, unsigned int len) {
    char* tmp = NULL;
    int buf_len = 0;
    if (0 == buf) {
        return 0;
    }
    
    buf_len = strlen(buf);
    if (len > buf_len) {
        len = buf_len;
    }

    tmp = (char*)malloc(len + 1);
    if (NULL == tmp) {
        printf("malloc failed!\n");
        return 0;
    }

    if (len > 0) {
        memcpy(tmp, buf, len);
    }
    
    tmp[len] = 0;
    return tmp;
}

char *randomregex(char *buf, unsigned maxlen, unsigned char lenbias, unsigned flags)
{
    /* initialize to zero */
    memset(buf, '\0', maxlen);

    /* sanity checks */
    if (maxlen == 0) return buf;
    if (lenbias == 0) return buf;

    /* allow one for '\0' */
    maxlen--;

    /* fill the buffer up with rand regex patterns */
    while (M(buf)) {
        switch (rand() % NREGEXTYPES) {
            case REGEXMATCHEDPAIR: {
                /* choose a rand offset into the string */
                unsigned offset = rand() % (strlen(buf) + 1);
                /* split the string into start and rest */
                char *pre = my_strndup(buf, offset);
                char *rest = strdup(buf + offset);

                /* add a matched pair of characters, requires 2 or 3 bytes */
                switch (rand() % 6) {
                    case 0: _snprintf(buf, maxlen, "%s(%s)", pre, rest); break;
                    case 1: _snprintf(buf, maxlen, "(%s%s)", pre, rest); break;
                    case 2: _snprintf(buf, maxlen, "%s[%s]", pre, rest); break;
                    case 3: _snprintf(buf, maxlen, "[%s%s]", pre, rest); break;
                    case 4: _snprintf(buf, maxlen, "%s[^%s]", pre, rest); break;
                    case 5: _snprintf(buf, maxlen, "[^%s%s]", pre, rest); break;
                }
                free(pre);
                free(rest);
                break;
            }
            case REGEXESCAPEDCHAR: {
                char *tmp = strdup(buf);
                /* add one of the supported escaped characters */
                switch (rand() % 36) {
                    case 0: strncat(buf, "\\t", M(buf)); break;
                    case 1: strncat(buf, "\\n", M(buf)); break;
                    case 2: strncat(buf, "\\r", M(buf)); break;
                    case 3: strncat(buf, "\\f", M(buf)); break;
                    case 4: strncat(buf, "\\a", M(buf)); break;
                    case 5: strncat(buf, "\\e", M(buf)); break;
                    /* 257 is deliberate, possibly confuse parser */
                    case 6: _snprintf(buf, maxlen, "%s\\%03o", tmp,
                                rand() % 257); break;
                    case 7: _snprintf(buf, maxlen, "%s\\x%02X", tmp,
                                rand() % 257); break;
                    case 8: strncat(buf, "\\c", M(buf)); break;
                    case 9: strncat(buf, "\\l", M(buf)); break;
                    case 10: strncat(buf, "\\u", M(buf)); break;
                    case 11: strncat(buf, "\\L", M(buf)); break;
                    case 12: strncat(buf, "\\U", M(buf)); break;
                    case 13: strncat(buf, "\\E", M(buf)); break;
                    case 14: strncat(buf, "\\Q", M(buf)); break;
                    case 15: strncat(buf, "\\w", M(buf)); break;
                    case 16: strncat(buf, "\\W", M(buf)); break;
                    case 17: strncat(buf, "\\s", M(buf)); break;
                    case 18: strncat(buf, "\\S", M(buf)); break;
                    case 19: strncat(buf, "\\d", M(buf)); break;
                    case 20: strncat(buf, "\\D", M(buf)); break;
                    case 21: strncat(buf, "\\b", M(buf)); break;
                    case 22: strncat(buf, "\\B", M(buf)); break;
                    case 23: strncat(buf, "\\A", M(buf)); break;
                    case 24: strncat(buf, "\\Z", M(buf)); break;
                    case 25: strncat(buf, "\\z", M(buf)); break;
                    case 26: strncat(buf, "\\G", M(buf)); break;
                    case 27: _snprintf(buf, maxlen, "%s\\%d", tmp,
                        (rand() % 257) * (1 - 2 * (rand() % 2))); break;
                    /* 0x1ffff is deliberate */
                    case 28: _snprintf(buf, maxlen, "%s\\x{%x}", tmp,
                        rand() & 0x1ffff ); break;
                    case 29: strncat(buf, "\\N", M(buf)); break;
                    case 30: strncat(buf, "\\C", M(buf)); break;
                    case 31: strncat(buf, "\\pP", M(buf)); break;
                    case 32: strncat(buf, "\\p", M(buf)); break;
                    case 33: strncat(buf, "\\PP", M(buf)); break;
                    case 34: strncat(buf, "\\P", M(buf)); break;
                    case 35: strncat(buf, "\\X", M(buf)); break;
                }
                free(tmp);
                break;
            }
            case REGEXSPECIALCHAR:
                switch (rand() % 9) {
                    case 0: strncat(buf, "\\", M(buf)); break;
                    case 1: strncat(buf, "^", M(buf)); break;
                    case 2: strncat(buf, ".", M(buf)); break;
                    case 3: strncat(buf, "$", M(buf)); break;
                    case 4: strncat(buf, "|", M(buf)); break;
                    case 5: strncat(buf, "*", M(buf)); break;
                    case 6: strncat(buf, "+", M(buf)); break;
                    case 7: strncat(buf, "?", M(buf)); break;
                    case 8: strncat(buf, "-", M(buf)); break;
                    /* maybe close open parens */
                    // case 9: strncat(buf, ")", M(buf)); break;
                }
                break;
            case REGEXQUANTIFY: {
                char *tmp = strdup(buf);
                switch (rand() % 5) {
                    /* {42,-42} */
                    case 0: _snprintf(buf, maxlen, "%s{%d,%d}", tmp, 
                        (rand() % 256) * (1 - 2 * (rand() % 2)),
                        (rand() % 256) * (1 - 2 * (rand() % 2))); break;
                    /* {42} */
                    case 1: _snprintf(buf, maxlen, "%s{%d}", tmp,
                        (rand() % 256) * (1 - 2 * (rand() % 2))); break;
                    /* {,42} */ 
                    case 2: _snprintf(buf, maxlen, "%s{,%d}", tmp,
                        (rand() % 256) * (1 - 2 * (rand() % 2))); break;
                    /* {42,} */
                    case 3: _snprintf(buf, maxlen, "%s{%d,}", tmp,
                        (rand() % 256) * (1 - 2 * (rand() % 2))); break;
                    /* {} */
                    case 4: _snprintf(buf, maxlen, "%s{}", tmp); break;
                }
                free(tmp);
                break;
            }
            case REGEXEXTENSION: {
                /* choose a rand offset into the string */
                unsigned offset = rand() % (strlen(buf) + 1);
                /* split the string into start and rest */
                char *pre = my_strndup(buf, offset);
                char *rest = strdup(buf + offset);
                char *split;
                switch(rand() % 10) {
                    case 0: _snprintf(buf, maxlen, "%s(?#%s)", pre, rest); break;
                    case 1: _snprintf(buf, maxlen, "%s(?:%s)", pre, rest); break;
                    case 2: {
                        char flags[128];

                        /* initialise to zero */
                        memset(flags, '\0', sizeof(flags));

                        /* choose some flags to add */
                        if (rand() % 4) strcat(flags, "i");
                        if (rand() % 4) strcat(flags, "m");
                        if (rand() % 4) strcat(flags, "s");
                        if (rand() % 4) strcat(flags, "x");
                        if (rand() % 2) strcat(flags, "-");
                        if (rand() % 4) strcat(flags, "i");
                        if (rand() % 4) strcat(flags, "m");
                        if (rand() % 4) strcat(flags, "s");
                        if (rand() % 4) strcat(flags, "x");

                        /* now add them to the regex */
                        _snprintf(buf, maxlen, "%s(?%s:%s)", pre, flags, rest);
                        break;
                    }
                   case 3: _snprintf(buf, maxlen, "%s(?=%s)", pre, rest); break;
                   case 4: _snprintf(buf, maxlen, "%s(?!%s)", pre, rest); break;
                   case 5: _snprintf(buf, maxlen, "%s(?<=%s)", pre, rest); break;
                   case 6: _snprintf(buf, maxlen, "%s(?<!%s)", pre, rest); break;
                   case 7: _snprintf(buf, maxlen, "%s(?{%s})", pre, rest); break;
                   case 8: _snprintf(buf, maxlen, "%s(?>%s)", pre, rest); break;
                   case 10: _snprintf(buf, maxlen, "%s(??{%s})", pre, rest); break;                 
                   case 9: 
                        /* conditionals... */
                        offset = rand() % (strlen(rest) + 1);
                        split = my_strndup(rest, offset);
                        _snprintf(buf, maxlen, "%s(?(%s)%s)", pre, 
                            split, rest + offset); break;
                        free(split);
                        break;
                }
                free(pre);
                free(rest);
                break;
            }
            case REGEXRANDOM: {
                char str[2] = { '\0', '\0' };
                while (rand() % (lenbias / 2 + 1)) {
                    *str = rand() % 256;
                    strncat(buf, str, M(buf));
                } 
                break;
            }
            case REGEXREPEATEDCHAR: {
                size_t len = rand() % (lenbias * 4 + 1);
                char *tmp = (char*)malloc(len + 1);
                memset(tmp, rand() % 256, len), tmp[len] = '\0';
                strncat(buf, tmp, M(buf));
                free(tmp);
                break;
            }
            case REGEXCHAR: {
                char str[2] = { rand() % 256, 0 };
                strncat(buf, str, M(buf));
                break;
            }
            case REGEXEND:
                /* possibly end the expression, dpending on bias */
                if (rand() % lenbias == 0)
                    return buf;
                break;
            case REGEXPOSIX:
                if (flags & POSIX_CHARCLASS) {
                    char *tmp = strdup(buf);
                    _snprintf(buf, maxlen, "%s[:%s:]",
                        tmp, posix[rand() % (sizeof(posix) / sizeof(*posix))]); break;
                    free(tmp);
                }
                break;
            case REGEXPROPERTY: {
                if (flags & UNICODE_PROPERTIES) {
                    char *tmp = strdup(buf);
                    char *p = (rand() % 2) ? "P" : "p";
                    char *neg = (rand() % 2) ? "^" : "";
                    _snprintf(buf, maxlen, "%s\\%s{%s%s}",
                        tmp, p, neg, ucp[rand() % (sizeof(ucp) / sizeof(*ucp))]); break;
                    free(tmp);
                }
                break;
            }
        }
    }
    /* unreachable */
    return buf;
}

void _set_seed(unsigned long s) {
  //rand();
  seed = s;
  srand(seed);
}

unsigned long _get_seed() {
  return seed;
}

char *_getregex(unsigned lenbias, unsigned flags) {
   static char regex[8192];
   char *r = randomregex(regex, sizeof(regex), lenbias, flags);
   //_set_seed((unsigned long)rand());
   return r;
}

#ifdef STANDALONE
int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s [seed] [lenbias] [flags]\n", *argv);
        return 1;
    }
    _set_seed(atol(argv[1]));
    fprintf(stdout, "%s", _getregex(atol(argv[2]), atol(argv[3])));
    return 0;
}
#endif
