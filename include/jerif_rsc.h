#ifndef __JERIF_RSC_H__
#define __JERIF_RSC_H__

#define SYMBOL_NULL 0
#define SYMBOL_TAB  9
#define SYMBOL_LF   10
#define SYMBOL_CR   13
#define SYMBOL_SPACE 32

#define SYMBOL_BRACE_OPEN    '{'
#define SYMBOL_BRACE_CLOSE   '}'
#define SYMBOL_BRACKET_OPEN  '['
#define SYMBOL_BRACKET_CLOSE ']'
#define SYMBOL_DOUBLE_QOUTE  '"'
#define SYMBOL_COLON         ':'
#define SYMBOL_COMMA         ','

#define SYMBOL_DATA_OTHER '_'
#define SYMBOL_DATA_BOOLEAN 'B'
#define SYMBOL_DATA_INTEGER 'I'
#define SYMBOL_DATA_STRING  'S'
#define SYMBOL_DATA_ERROR   'E'

#define SYMBOL_DATA_BOOL_TRUE   't'
#define SYMBOL_DATA_BOOL_FALSE  'f'

#define STR_TRUE    "true"
#define STR_FALSE   "false"

#define REGEX_PATTERN_BOOLEAN   "^(true|false)(,|}|]| |\n|\r|\t){1}.*$"
#define REGEX_PATTERN_INTEGER   "^[0-9]+(,|}|]| |\n|\r|\t){1}.*$"
#define REGEX_PATTERN_FLOAT     "^[0-9]+(.)[0-9]+(,|}|]| |\n|\r|\t){1}.*$"
#define REGEX_PATTERN_STRING    "^(.)*(\"){0}(,|:|}|]| |\n|\r|\t){1}.*$"
#endif //__JERIF_RSC_H__
