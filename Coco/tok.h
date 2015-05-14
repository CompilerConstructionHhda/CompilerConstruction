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
    tok_semi = -7
    //operator (+, -)
};

#endif	/* TOK_H */

