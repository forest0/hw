/* the parser for the TINY compiler */

/**********************************************************
*  CFGs of TINY  
*  
*  program -> stmt-sequence
*  
*  stmt-sequence -> stmt-sequence; statement 
*                   | statement
*  
*  statement -> if-stmt 
*               | repeat-stmt 
*               | assign-stmt
*               | read-stmt
*               | write-stmt
*               
*  if-stmt ->   if exp then stmt-sequence end
*               | if exp then stmt-sequence else stmt-sequence end
*               
*  // note that here keyword end used, so no dangling-else problem
*  
*  repeat-stmt ->   repeat stmt-sequence until exp
*  
*  assign-stmt ->   identifier := exp
*  
*  read-stmt   ->   read identifier
*  
*  write-stmt  ->   write exp
*  
*  exp         ->   simple-exp comparison-op simple-exp
*                   | simple-exp
*  
*  comparison-op    -> < | =
*  
*  simple-exp  ->   simple-exp addop term 
*                   | term
*                   
*  addop       ->   + | -
*  
*  term        ->   term mulop factor |factor
*  
*  mulop       ->   * | /
*  
*  factor      ->   ( exp ) | number | identifier
*  
***********************************************************/


#ifndef PARSE_H
#define PARSE_H

#include "globals.h"

struct TreeNode * parse(void);

#endif /* ifndef PARSE_H */
