/* 
 * File:   tok.h
 * Author: orkanone
 *
 * Created on 9. Mai 2015, 09:20
 */

#ifndef TOK_H
#define	TOK_H

enum Tok{
    tok_eof = -1,
    tok_identifier = -2,
    tok_number = -3,
    tok_assign = -4,
    tok_plus = -5,
    tok_mult = -6,
    tok_semi = -7,
    tok_func_decl = -8,
    tok_func_name = -9,
    tok_left_par = -10,
    tok_right_par = -11,
    begin_code_block = -12,
    end_code_block = -13,
    tok_comma = -14
    //operator (+, -)
};

#endif	/* TOK_H */

