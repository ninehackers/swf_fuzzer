
#ifndef __REGFUZZ_H
#define __REGFUZZ_H

//#include <sys/types.h>
char* my_strndup(char* buf, unsigned int len);
extern unsigned long seed;
char *randomregex(char *buf, unsigned maxlen, unsigned char lenbias, unsigned flags);
void _set_seed(unsigned long s);
unsigned long _get_seed();
char *_getregex(unsigned lenbias, unsigned flags);

static char *ucp[] = {
    "LC", "Lu", "Ll", "Lt", "Lm", "Lo",
    "M", "Mn", "Mc", "Me", 
    "N", "Nd","Nl", "No",
    "P", "Pc", "Pd", "Ps", "Pe", "Pi", "Pf", "Po",
    "S", "Sm", "Sc", "Sk", "So", "Z", "Zs", "Zl", "Zp",
    "C", "Cc", "Cf", "Cs", "Co", "Cn",
    "BidiClass:L", "BidiClass:LRE", "BidiClass:LRO", "BidiClass:R",
    "BidiClass:AL", "BidiClass:RLE", "BidiClass:RLO", "BidiClass:PDF",
    "BidiClass:EN", "BidiClass:ES", "BidiClass:ET", "BidiClass:AN",
    "BidiClass:CS", "BidiClass:NSM", "BidiClass:BN", "BidiClass:B",
    "BidiClass:S", "BidiClass:WS", "BidiClass:ON",
    "Arabic", "Armenian", "Bengali", "Bopomofo", "Buhid", "CanadianAboriginal",
    "Cherokee", "Cyrillic", "Deseret", "Devanagari", "Ethiopic", "Georgian",
    "Gothic", "Greek", "Gujarati", "Gurmukhi", "Han", "Hangul", "Hanunoo",
    "Hebrew", "Hiragana", "Inherited", "Kannada", "Katakana", "Khmer",
    "Lao", "Latin", "Malayalam", "Mongolian", "Myanmar", "Ogham", "OldItalic",
    "Oriya", "Runic", "Sinhala", "Syriac", "Tagalog", "Tagbanwa", "Tamil",
    "Telugu", "Thaana", "Thai", "Tibetan", "Yi",
    "ASCIIHexDigit", "BidiControl", "Dash", "Deprecated", "Diacritic", 
    "Extender", "GraphemeLink", "HexDigit", "Hyphen", "Ideographic", 
    "IDSBinaryOperator", "IDSTrinaryOperator", "JoinControl", "LogicalOrderException", 
    "NoncharacterCodePoint", "OtherAlphabetic", "OtherDefaultIgnorableCodePoint", 
    "OtherGraphemeExtend", "OtherLowercase", "OtherMath", "OtherUppercase", 
    "QuotationMark", "Radical", "SoftDotted", "TerminalPunctuation", "UnifiedIdeograph", 
    "WhiteSpace",
    "Alphabetic", "Lowercase", "Uppercase", "Math", "ID_Start", "ID_Continue"
    "Any", "Assigned", "Unassigned", "Common"
};

static char *posix[] = {
    "alnum", "alpha", "ascii", "blank"
    "cntrl", "digit", "graph", "lower"
    "print", "punct", "space", "upper"
    "word", "xdigit"
};

/* -- flags -- */

/* specific engines, 12 reserved */
#define ENGINE_PCRE (1<<0)
#define ENGINE_PERL (1<<1)
#define ENGINE_RUBY (1<<2)
#define ENGINE_PYTHON (1<<3)
#define ENGINE_POSIX (1<<4)
#define ENGINE_TCL (1<<5)
#define ENGINE_GREP (1<<6)
/* ... */

/* features, 20 reserved */
#define UNICODE_PROPERTIES (1<<12)
#define POSIX_CHARCLASS (1<<13)
/* ... */

#endif
