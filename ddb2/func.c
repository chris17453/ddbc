
#include "headers/bytecode.h"


/*
 * Function: match_ABS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ABS(token_t * tokens){
    // ABS: ABS ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ABS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ABS

/*
 * Function: match_ACOS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ACOS(token_t * tokens){
    // ACOS: ACOS ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ACOS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ACOS

/*
 * Function: match_ADDDATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ADDDATE(token_t * tokens){
    // ADDDATE: ADDDATE ( date, INTERVAL expr unit )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ADDDATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'INTERVAL') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ADDDATE

/*
 * Function: match_ADDDATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ADDDATE(token_t * tokens){
    // ADDDATE: ADDDATE ( expr, days )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ADDDATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_days(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ADDDATE

/*
 * Function: match_ADDTIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ADDTIME(token_t * tokens){
    // ADDTIME: ADDTIME ( expr1, expr2 )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ADDTIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ADDTIME

/*
 * Function: match_ASCII
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ASCII(token_t * tokens){
    // ASCII: ASCII ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ASCII') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ASCII

/*
 * Function: match_ASIN
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ASIN(token_t * tokens){
    // ASIN: ASIN ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ASIN') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ASIN

/*
 * Function: match_ATAN
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ATAN(token_t * tokens){
    // ATAN: ATAN ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ATAN') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ATAN

/*
 * Function: match_ATAN2
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ATAN2(token_t * tokens){
    // ATAN2: ATAN2 ( Y, X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ATAN2') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'Y') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ATAN2

/*
 * Function: match_BIN
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_BIN(token_t * tokens){
    // BIN: BIN ( N )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'BIN') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_BIN

/*
 * Function: match_BIT_LENGTH
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_BIT_LENGTH(token_t * tokens){
    // BIT_LENGTH: BIT_LENGTH ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'BIT_LENGTH') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_BIT_LENGTH

/*
 * Function: match_CEILING
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CEILING(token_t * tokens){
    // CEILING: CEILING ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CEILING') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CEILING

/*
 * Function: match_CEIL
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CEIL(token_t * tokens){
    // CEIL: CEIL ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CEIL') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CEIL

/*
 * Function: match_CHARACTER_LENGTH
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CHARACTER_LENGTH(token_t * tokens){
    // CHARACTER_LENGTH: CHARACTER_LENGTH ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CHARACTER_LENGTH') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CHARACTER_LENGTH

/*
 * Function: match_CHAR_LENGTH
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CHAR_LENGTH(token_t * tokens){
    // CHAR_LENGTH: CHAR_LENGTH ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CHAR_LENGTH') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CHAR_LENGTH

/*
 * Function: match_CHAR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CHAR(token_t * tokens){
    // CHAR: CHAR ( N, ...  [ USING charset_name ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CHAR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'...') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_2=token;
       if ( token != NULL && token_cmp(token,'USING') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_charset_name(token);
       if ( token == NULL ) token=opt_temp_2;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CHAR

/*
 * Function: match_CONCAT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONCAT(token_t * tokens){
    // CONCAT: CONCAT ( str1, str2, ... )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CONCAT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'...') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CONCAT

/*
 * Function: match_CONCAT_WS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONCAT_WS(token_t * tokens){
    // CONCAT_WS: CONCAT_WS ( separator, str1, str2, ... )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CONCAT_WS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_separator(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'...') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CONCAT_WS

/*
 * Function: match_CONVERT_TZ
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONVERT_TZ(token_t * tokens){
    // CONVERT_TZ: CONVERT_TZ ( dt, from_tz, to_tz )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CONVERT_TZ') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_dt(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_from_tz(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_to_tz(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CONVERT_TZ

/*
 * Function: match_CONV
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONV(token_t * tokens){
    // CONV: CONV ( N, from_base, to_base )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CONV') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_from_base(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_to_base(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CONV

/*
 * Function: match_COS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_COS(token_t * tokens){
    // COS: COS ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'COS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_COS

/*
 * Function: match_COT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_COT(token_t * tokens){
    // COT: COT ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'COT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_COT

/*
 * Function: match_CRC32
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CRC32(token_t * tokens){
    // CRC32: CRC32 ( expr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CRC32') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CRC32

/*
 * Function: match_CURDATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURDATE(token_t * tokens){
    // CURDATE: CURDATE (  )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CURDATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CURDATE

/*
 * Function: match_CURRENT_DATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURRENT_DATE(token_t * tokens){
    // CURRENT_DATE: CURRENT_DATE (  )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CURRENT_DATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CURRENT_DATE

/*
 * Function: match_CURRENT_TIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURRENT_TIME(token_t * tokens){
    // CURRENT_TIME: CURRENT_TIME (  [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CURRENT_TIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_3=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_3;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CURRENT_TIME

/*
 * Function: match_CURRENT_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURRENT_TIMESTAMP(token_t * tokens){
    // CURRENT_TIMESTAMP: CURRENT_TIMESTAMP (  [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CURRENT_TIMESTAMP') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_4=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_4;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CURRENT_TIMESTAMP

/*
 * Function: match_CURTIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURTIME(token_t * tokens){
    // CURTIME: CURTIME (  [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'CURTIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_5=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_5;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_CURTIME

/*
 * Function: match_DATE_ADD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_ADD(token_t * tokens){
    // DATE_ADD: DATE_ADD ( date, INTERVAL expr unit )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DATE_ADD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'INTERVAL') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DATE_ADD

/*
 * Function: match_DATE_SUB
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_SUB(token_t * tokens){
    // DATE_SUB: DATE_SUB ( date, INTERVAL expr unit )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DATE_SUB') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'INTERVAL') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DATE_SUB

/*
 * Function: match_DATEDIFF
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATEDIFF(token_t * tokens){
    // DATEDIFF: DATEDIFF ( expr1, expr2 )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DATEDIFF') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DATEDIFF

/*
 * Function: match_DATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE(token_t * tokens){
    // DATE: DATE ( expr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DATE

/*
 * Function: match_DATE_FORMAT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_FORMAT(token_t * tokens){
    // DATE_FORMAT: DATE_FORMAT ( date, format )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DATE_FORMAT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_format(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DATE_FORMAT

/*
 * Function: match_DATE_SUB
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_SUB(token_t * tokens){
    // DATE_SUB: DATE_SUB ( date, INTERVAL expr unit )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DATE_SUB') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'INTERVAL') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DATE_SUB

/*
 * Function: match_DAY
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAY(token_t * tokens){
    // DAY: DAY ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DAY') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DAY

/*
 * Function: match_DAYNAME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYNAME(token_t * tokens){
    // DAYNAME: DAYNAME ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DAYNAME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DAYNAME

/*
 * Function: match_DAYOFMONTH
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYOFMONTH(token_t * tokens){
    // DAYOFMONTH: DAYOFMONTH ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DAYOFMONTH') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DAYOFMONTH

/*
 * Function: match_DAYOFWEEK
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYOFWEEK(token_t * tokens){
    // DAYOFWEEK: DAYOFWEEK ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DAYOFWEEK') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DAYOFWEEK

/*
 * Function: match_DAYOFYEAR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYOFYEAR(token_t * tokens){
    // DAYOFYEAR: DAYOFYEAR ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DAYOFYEAR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DAYOFYEAR

/*
 * Function: match_DEGREES
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DEGREES(token_t * tokens){
    // DEGREES: DEGREES ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'DEGREES') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_DEGREES

/*
 * Function: match_ELT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ELT(token_t * tokens){
    // ELT: ELT ( N, str1, str2, str3, ... )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ELT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str3(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'...') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ELT

/*
 * Function: match_EXPORT_SET
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_EXPORT_SET(token_t * tokens){
    // EXPORT_SET: EXPORT_SET ( bits, on, off [ , separator [ , number_of_bits ] ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'EXPORT_SET') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_bits(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_on(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_off(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_6=token;
       if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_separator(token);

       // begin optional block
       if ( token =! NULL ) {
          token_t * opt_temp_7=token;
          if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
          if ( token != NULL ) token = match_number_of_bits(token);
          if ( token == NULL ) token=opt_temp_7;
       }// end optional block
       if ( token == NULL ) token=opt_temp_6;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_EXPORT_SET

/*
 * Function: match_EXP
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_EXP(token_t * tokens){
    // EXP: EXP ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'EXP') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_EXP

/*
 * Function: match_EXTRACT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_EXTRACT(token_t * tokens){
    // EXTRACT: EXTRACT ( unit FROM date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'EXTRACT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,'FROM') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_EXTRACT

/*
 * Function: match_FIELD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FIELD(token_t * tokens){
    // FIELD: FIELD ( str, str1, str2, str3, ... )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FIELD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str3(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'...') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FIELD

/*
 * Function: match_FIND_IN_SET
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FIND_IN_SET(token_t * tokens){
    // FIND_IN_SET: FIND_IN_SET ( str, strlist )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FIND_IN_SET') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_strlist(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FIND_IN_SET

/*
 * Function: match_FLOOR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FLOOR(token_t * tokens){
    // FLOOR: FLOOR ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FLOOR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FLOOR

/*
 * Function: match_FORMAT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FORMAT(token_t * tokens){
    // FORMAT: FORMAT ( X, D )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FORMAT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'D') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FORMAT

/*
 * Function: match_FORMAT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FORMAT(token_t * tokens){
    // FORMAT: FORMAT ( X, D [ , locale ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FORMAT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'D') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_8=token;
       if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_locale(token);
       if ( token == NULL ) token=opt_temp_8;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FORMAT

/*
 * Function: match_FROM_BASE64
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FROM_BASE64(token_t * tokens){
    // FROM_BASE64: FROM_BASE64 ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FROM_BASE64') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FROM_BASE64

/*
 * Function: match_FROM_DAYS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FROM_DAYS(token_t * tokens){
    // FROM_DAYS: FROM_DAYS ( N )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FROM_DAYS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FROM_DAYS

/*
 * Function: match_FROM_UNIXTIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FROM_UNIXTIME(token_t * tokens){
    // FROM_UNIXTIME: FROM_UNIXTIME ( unix_timestamp [ , format ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'FROM_UNIXTIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_unix_timestamp(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_9=token;
       if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_format(token);
       if ( token == NULL ) token=opt_temp_9;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_FROM_UNIXTIME

/*
 * Function: match_HEX
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_HEX(token_t * tokens){
    // HEX: HEX ( N_or_S )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'HEX') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N_or_S') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_HEX

/*
 * Function: match_HEX
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_HEX(token_t * tokens){
    // HEX: HEX ( { str|N  } )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'HEX') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin group block
    if ( token =! NULL ) {
       // Begin OR block
       token_t * or_temp_10=token;
       if ( token != NULL ) token = match_str(token);

       if ( token == NULL ) {        
          token=or_temp_10;
          if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
       }
    } // end group block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_HEX

/*
 * Function: match_HOUR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_HOUR(token_t * tokens){
    // HOUR: HOUR ( time )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'HOUR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_time(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_HOUR

/*
 * Function: match_INSERT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_INSERT(token_t * tokens){
    // INSERT: INSERT ( str, pos, len, newstr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'INSERT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_newstr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_INSERT

/*
 * Function: match_INSTR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_INSTR(token_t * tokens){
    // INSTR: INSTR ( str, substr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'INSTR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_substr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_INSTR

/*
 * Function: match_LAST_DAY
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LAST_DAY(token_t * tokens){
    // LAST_DAY: LAST_DAY ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LAST_DAY') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LAST_DAY

/*
 * Function: match_LCASE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LCASE(token_t * tokens){
    // LCASE: LCASE ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LCASE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LCASE

/*
 * Function: match_LEFT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LEFT(token_t * tokens){
    // LEFT: LEFT ( str, len )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LEFT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LEFT

/*
 * Function: match_LENGTH
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LENGTH(token_t * tokens){
    // LENGTH: LENGTH ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LENGTH') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LENGTH

/*
 * Function: match_LN
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LN(token_t * tokens){
    // LN: LN ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LN') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LN

/*
 * Function: match_LOAD_FILE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOAD_FILE(token_t * tokens){
    // LOAD_FILE: LOAD_FILE ( file_name )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOAD_FILE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_file_name(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOAD_FILE

/*
 * Function: match_LOCALTIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOCALTIME(token_t * tokens){
    // LOCALTIME: LOCALTIME (  [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOCALTIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_11=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_11;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOCALTIME

/*
 * Function: match_LOCALTIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOCALTIMESTAMP(token_t * tokens){
    // LOCALTIMESTAMP: LOCALTIMESTAMP (  [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOCALTIMESTAMP') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_12=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_12;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOCALTIMESTAMP

/*
 * Function: match_LOCATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOCATE(token_t * tokens){
    // LOCATE: LOCATE ( substr, str [ , pos ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOCATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_substr(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_13=token;
       if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_pos(token);
       if ( token == NULL ) token=opt_temp_13;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOCATE

/*
 * Function: match_LOG10
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOG10(token_t * tokens){
    // LOG10: LOG10 ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOG10') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOG10

/*
 * Function: match_LOG2
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOG2(token_t * tokens){
    // LOG2: LOG2 ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOG2') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOG2

/*
 * Function: match_LOG
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOG(token_t * tokens){
    // LOG: LOG (  [ B ], X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOG') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_14=token;
       if ( token != NULL && token_cmp(token,'B') != NULL ) token=next_token(token);
       if ( token == NULL ) token=opt_temp_14;
    }// end optional block
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOG

/*
 * Function: match_LOWER
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOWER(token_t * tokens){
    // LOWER: LOWER ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LOWER') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LOWER

/*
 * Function: match_LPAD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LPAD(token_t * tokens){
    // LPAD: LPAD ( str, len, padstr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LPAD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_padstr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LPAD

/*
 * Function: match_LTRIM
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LTRIM(token_t * tokens){
    // LTRIM: LTRIM ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'LTRIM') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_LTRIM

/*
 * Function: match_MAKEDATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MAKEDATE(token_t * tokens){
    // MAKEDATE: MAKEDATE ( year, dayofyear )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MAKEDATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_year(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_dayofyear(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MAKEDATE

/*
 * Function: match_MAKE_SET
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MAKE_SET(token_t * tokens){
    // MAKE_SET: MAKE_SET ( bits, str1, str2, ... )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MAKE_SET') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_bits(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'...') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MAKE_SET

/*
 * Function: match_MAKETIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MAKETIME(token_t * tokens){
    // MAKETIME: MAKETIME ( hour, minute, second )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MAKETIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_hour(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_minute(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_second(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MAKETIME

/*
 * Function: match_MICROSECOND
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MICROSECOND(token_t * tokens){
    // MICROSECOND: MICROSECOND ( expr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MICROSECOND') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MICROSECOND

/*
 * Function: match_MID
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MID(token_t * tokens){
    // MID: MID ( str, pos, len )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MID') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MID

/*
 * Function: match_MINUTE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MINUTE(token_t * tokens){
    // MINUTE: MINUTE ( time )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MINUTE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_time(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MINUTE

/*
 * Function: match_MOD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MOD(token_t * tokens){
    // MOD: MOD ( N, M )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MOD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'M') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MOD

/*
 * Function: match_MONTH
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MONTH(token_t * tokens){
    // MONTH: MONTH ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MONTH') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MONTH

/*
 * Function: match_MONTHNAME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MONTHNAME(token_t * tokens){
    // MONTHNAME: MONTHNAME ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'MONTHNAME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_MONTHNAME

/*
 * Function: match_NOW
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_NOW(token_t * tokens){
    // NOW: NOW (  [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'NOW') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_15=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_15;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_NOW

/*
 * Function: match_OCTET_LENGTH
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_OCTET_LENGTH(token_t * tokens){
    // OCTET_LENGTH: OCTET_LENGTH ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'OCTET_LENGTH') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_OCTET_LENGTH

/*
 * Function: match_OCT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_OCT(token_t * tokens){
    // OCT: OCT ( N )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'OCT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_OCT

/*
 * Function: match_ORD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ORD(token_t * tokens){
    // ORD: ORD ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ORD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ORD

/*
 * Function: match_PERIOD_ADD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_PERIOD_ADD(token_t * tokens){
    // PERIOD_ADD: PERIOD_ADD ( P, N )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'PERIOD_ADD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'P') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_PERIOD_ADD

/*
 * Function: match_PERIOD_DIFF
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_PERIOD_DIFF(token_t * tokens){
    // PERIOD_DIFF: PERIOD_DIFF ( P1, P2 )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'PERIOD_DIFF') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'P1') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'P2') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_PERIOD_DIFF

/*
 * Function: match_PI
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_PI(token_t * tokens){
    // PI: PI (  )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'PI') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_PI

/*
 * Function: match_POSITION
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_POSITION(token_t * tokens){
    // POSITION: POSITION ( substr IN str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'POSITION') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_substr(token);
    if ( token != NULL && token_cmp(token,'IN') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_POSITION

/*
 * Function: match_POWER
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_POWER(token_t * tokens){
    // POWER: POWER ( X, Y )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'POWER') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'Y') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_POWER

/*
 * Function: match_POW
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_POW(token_t * tokens){
    // POW: POW ( X, Y )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'POW') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'Y') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_POW

/*
 * Function: match_QUARTER
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_QUARTER(token_t * tokens){
    // QUARTER: QUARTER ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'QUARTER') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_QUARTER

/*
 * Function: match_QUOTE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_QUOTE(token_t * tokens){
    // QUOTE: QUOTE ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'QUOTE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_QUOTE

/*
 * Function: match_RADIANS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RADIANS(token_t * tokens){
    // RADIANS: RADIANS ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'RADIANS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_RADIANS

/*
 * Function: match_RAND
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RAND(token_t * tokens){
    // RAND: RAND (  [ N ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'RAND') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_16=token;
       if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
       if ( token == NULL ) token=opt_temp_16;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_RAND

/*
 * Function: match_REPEAT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_REPEAT(token_t * tokens){
    // REPEAT: REPEAT ( str, count )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'REPEAT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_count(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_REPEAT

/*
 * Function: match_REPLACE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_REPLACE(token_t * tokens){
    // REPLACE: REPLACE ( str, from_str, to_str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'REPLACE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_from_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_to_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_REPLACE

/*
 * Function: match_REVERSE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_REVERSE(token_t * tokens){
    // REVERSE: REVERSE ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'REVERSE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_REVERSE

/*
 * Function: match_RIGHT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RIGHT(token_t * tokens){
    // RIGHT: RIGHT ( str, len )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'RIGHT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_RIGHT

/*
 * Function: match_ROUND
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ROUND(token_t * tokens){
    // ROUND: ROUND ( X [ , D ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'ROUND') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_17=token;
       if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
       if ( token != NULL && token_cmp(token,'D') != NULL ) token=next_token(token);
       if ( token == NULL ) token=opt_temp_17;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_ROUND

/*
 * Function: match_RPAD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RPAD(token_t * tokens){
    // RPAD: RPAD ( str, len, padstr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'RPAD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_padstr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_RPAD

/*
 * Function: match_RTRIM
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RTRIM(token_t * tokens){
    // RTRIM: RTRIM ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'RTRIM') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_RTRIM

/*
 * Function: match_SECOND
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SECOND(token_t * tokens){
    // SECOND: SECOND ( time )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SECOND') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_time(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SECOND

/*
 * Function: match_SEC_TO_TIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SEC_TO_TIME(token_t * tokens){
    // SEC_TO_TIME: SEC_TO_TIME ( seconds )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SEC_TO_TIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_seconds(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SEC_TO_TIME

/*
 * Function: match_SIGN
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SIGN(token_t * tokens){
    // SIGN: SIGN ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SIGN') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SIGN

/*
 * Function: match_SIN
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SIN(token_t * tokens){
    // SIN: SIN ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SIN') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SIN

/*
 * Function: match_SOUNDEX
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SOUNDEX(token_t * tokens){
    // SOUNDEX: SOUNDEX ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SOUNDEX') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SOUNDEX

/*
 * Function: match_SPACE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SPACE(token_t * tokens){
    // SPACE: SPACE ( N )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SPACE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'N') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SPACE

/*
 * Function: match_SQRT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SQRT(token_t * tokens){
    // SQRT: SQRT ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SQRT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SQRT

/*
 * Function: match_STR_TO_DATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_STR_TO_DATE(token_t * tokens){
    // STR_TO_DATE: STR_TO_DATE ( str, format )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'STR_TO_DATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_format(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_STR_TO_DATE

/*
 * Function: match_SUBDATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBDATE(token_t * tokens){
    // SUBDATE: SUBDATE ( date, INTERVAL expr unit )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBDATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'INTERVAL') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBDATE

/*
 * Function: match_SUBDATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBDATE(token_t * tokens){
    // SUBDATE: SUBDATE ( expr, days )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBDATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_days(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBDATE

/*
 * Function: match_SUBSTRING_INDEX
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING_INDEX(token_t * tokens){
    // SUBSTRING_INDEX: SUBSTRING_INDEX ( str, delim, count )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBSTRING_INDEX') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_delim(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_count(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBSTRING_INDEX

/*
 * Function: match_SUBSTRING
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING(token_t * tokens){
    // SUBSTRING: SUBSTRING ( str, pos )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBSTRING') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBSTRING

/*
 * Function: match_SUBSTRING
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING(token_t * tokens){
    // SUBSTRING: SUBSTRING ( str FROM pos )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBSTRING') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,'FROM') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBSTRING

/*
 * Function: match_SUBSTRING
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING(token_t * tokens){
    // SUBSTRING: SUBSTRING ( str, pos, len )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBSTRING') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBSTRING

/*
 * Function: match_SUBSTR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTR(token_t * tokens){
    // SUBSTR: SUBSTR ( str, pos )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBSTR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBSTR

/*
 * Function: match_SUBSTR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTR(token_t * tokens){
    // SUBSTR: SUBSTR ( str FROM pos )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBSTR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,'FROM') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBSTR

/*
 * Function: match_SUBSTR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTR(token_t * tokens){
    // SUBSTR: SUBSTR ( str, pos, len )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBSTR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBSTR

/*
 * Function: match_SUBTIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBTIME(token_t * tokens){
    // SUBTIME: SUBTIME ( expr1, expr2 )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SUBTIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SUBTIME

/*
 * Function: match_SYSDATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SYSDATE(token_t * tokens){
    // SYSDATE: SYSDATE (  [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'SYSDATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_18=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_18;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_SYSDATE

/*
 * Function: match_TAN
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TAN(token_t * tokens){
    // TAN: TAN ( X )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TAN') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TAN

/*
 * Function: match_TIMEDIFF
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMEDIFF(token_t * tokens){
    // TIMEDIFF: TIMEDIFF ( expr1, expr2 )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TIMEDIFF') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TIMEDIFF

/*
 * Function: match_TIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIME(token_t * tokens){
    // TIME: TIME ( expr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TIME

/*
 * Function: match_TIME_FORMAT
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIME_FORMAT(token_t * tokens){
    // TIME_FORMAT: TIME_FORMAT ( time, format )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TIME_FORMAT') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_time(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_format(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TIME_FORMAT

/*
 * Function: match_TIMESTAMPADD
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMESTAMPADD(token_t * tokens){
    // TIMESTAMPADD: TIMESTAMPADD ( unit, interval, datetime_expr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TIMESTAMPADD') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_interval(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_datetime_expr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TIMESTAMPADD

/*
 * Function: match_TIMESTAMPDIFF
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMESTAMPDIFF(token_t * tokens){
    // TIMESTAMPDIFF: TIMESTAMPDIFF ( unit, datetime_expr1, datetime_expr2 )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TIMESTAMPDIFF') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_datetime_expr1(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_datetime_expr2(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TIMESTAMPDIFF

/*
 * Function: match_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMESTAMP(token_t * tokens){
    // TIMESTAMP: TIMESTAMP ( expr1 [ , expr2 ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TIMESTAMP') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr1(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_19=token;
       if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_expr2(token);
       if ( token == NULL ) token=opt_temp_19;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TIMESTAMP

/*
 * Function: match_TIME_TO_SEC
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIME_TO_SEC(token_t * tokens){
    // TIME_TO_SEC: TIME_TO_SEC ( time )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TIME_TO_SEC') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_time(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TIME_TO_SEC

/*
 * Function: match_TO_BASE64
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TO_BASE64(token_t * tokens){
    // TO_BASE64: TO_BASE64 ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TO_BASE64') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TO_BASE64

/*
 * Function: match_TO_DAYS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TO_DAYS(token_t * tokens){
    // TO_DAYS: TO_DAYS ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TO_DAYS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TO_DAYS

/*
 * Function: match_TO_SECONDS
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TO_SECONDS(token_t * tokens){
    // TO_SECONDS: TO_SECONDS ( expr )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TO_SECONDS') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TO_SECONDS

/*
 * Function: match_TRIM
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TRIM(token_t * tokens){
    // TRIM: TRIM (  [ { BOTH | LEADING | TRAILING  }  [ remstr ] FROM ] str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TRIM') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_20=token;

       // begin group block
       if ( token =! NULL ) {
          // Begin OR block
          token_t * or_temp_21=token;
          if ( token != NULL && token_cmp(token,'BOTH') != NULL ) token=next_token(token);

          if ( token == NULL ) {        
             token=or_temp_21;
             if ( token != NULL && token_cmp(token,'LEADING') != NULL ) token=next_token(token);
          }

          if ( token == NULL ) {        
             token=or_temp_21;
             if ( token != NULL && token_cmp(token,'TRAILING') != NULL ) token=next_token(token);
          }
       } // end group block

       // begin optional block
       if ( token =! NULL ) {
          token_t * opt_temp_22=token;
          if ( token != NULL ) token = match_remstr(token);
          if ( token == NULL ) token=opt_temp_22;
       }// end optional block
       if ( token != NULL && token_cmp(token,'FROM') != NULL ) token=next_token(token);
       if ( token == NULL ) token=opt_temp_20;
    }// end optional block
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TRIM

/*
 * Function: match_TRUNCATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TRUNCATE(token_t * tokens){
    // TRUNCATE: TRUNCATE ( X, D )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'TRUNCATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'X') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'D') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_TRUNCATE

/*
 * Function: match_UCASE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UCASE(token_t * tokens){
    // UCASE: UCASE ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'UCASE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_UCASE

/*
 * Function: match_UNHEX
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UNHEX(token_t * tokens){
    // UNHEX: UNHEX ( str )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'UNHEX') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_UNHEX

/*
 * Function: match_UNIX_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UNIX_TIMESTAMP(token_t * tokens){
    // UNIX_TIMESTAMP: UNIX_TIMESTAMP ( [ date ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'UNIX_TIMESTAMP') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_23=token;
       if ( token != NULL ) token = match_date(token);
       if ( token == NULL ) token=opt_temp_23;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_UNIX_TIMESTAMP

/*
 * Function: match_UTC_DATE
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UTC_DATE(token_t * tokens){
    // UTC_DATE: UTC_DATE (  )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'UTC_DATE') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_UTC_DATE

/*
 * Function: match_UTC_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UTC_TIMESTAMP(token_t * tokens){
    // UTC_TIMESTAMP: UTC_TIMESTAMP ( [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'UTC_TIMESTAMP') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_24=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_24;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_UTC_TIMESTAMP

/*
 * Function: match_UTC_TIME
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UTC_TIME(token_t * tokens){
    // UTC_TIME: UTC_TIME ( [ fsp ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'UTC_TIME') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_25=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token=opt_temp_25;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_UTC_TIME

/*
 * Function: match_WEEK
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_WEEK(token_t * tokens){
    // WEEK: WEEK ( date [ , mode ] )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'WEEK') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_26=token;
       if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_mode(token);
       if ( token == NULL ) token=opt_temp_26;
    }// end optional block
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_WEEK

/*
 * Function: match_WEEKDAY
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_WEEKDAY(token_t * tokens){
    // WEEKDAY: WEEKDAY ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'WEEKDAY') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_WEEKDAY

/*
 * Function: match_WEEKOFYEAR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_WEEKOFYEAR(token_t * tokens){
    // WEEKOFYEAR: WEEKOFYEAR ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'WEEKOFYEAR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_WEEKOFYEAR

/*
 * Function: match_YEAR
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_YEAR(token_t * tokens){
    // YEAR: YEAR ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'YEAR') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_YEAR

/*
 * Function: match_YEARWEEK
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_YEARWEEK(token_t * tokens){
    // YEARWEEK: YEARWEEK ( date )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'YEARWEEK') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_YEARWEEK

/*
 * Function: match_YEARWEEK
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_YEARWEEK(token_t * tokens){
    // YEARWEEK: YEARWEEK ( date, mode )
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL && token_cmp(token,'YEARWEEK') != NULL ) token=next_token(token);
    if ( token != NULL && token_cmp(token,'(') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL && token_cmp(token,',') != NULL ) token=next_token(token);
    if ( token != NULL ) token = match_mode(token);
    if ( token != NULL && token_cmp(token,')') != NULL ) token=next_token(token);


    return token;
} // end match_YEARWEEK

/*
 * Function: match_alpha
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_alpha(token_t * tokens){
    // alpha: {A-Z}| {a-z}
    token_t * token=tokens;                //make a copy of the pointer

    // Begin OR block
    token_t * or_temp_27=token;

    // begin group block
    if ( token =! NULL ) {
       // range
       if ( token != NULL && token_cmp_range(token,'A','Z') != NULL ) token=next_token(token);
    } // end group block

    if ( token == NULL ) {        
       token=or_temp_27;
       // range
       if ( token != NULL && token_cmp_range(token,'a','z') != NULL ) token=next_token(token);
    }


    return token;
} // end match_alpha

/*
 * Function: match_string
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_string(token_t * tokens){
    // string: '*'|"*"
    token_t * token=tokens;                //make a copy of the pointer

    // Begin OR block
    token_t * or_temp_28=token;
    if ( token != NULL && token_cmp(token,'\'*\'') != NULL ) token=next_token(token);

    if ( token == NULL ) {        
       token=or_temp_28;
       if ( token != NULL && token_cmp(token,'"*"') != NULL ) token=next_token(token);
    }


    return token;
} // end match_string

/*
 * Function: match_sign
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_sign(token_t * tokens){
    // sign: - | + 
    token_t * token=tokens;                //make a copy of the pointer

    // Begin OR block
    token_t * or_temp_29=token;
    if ( token != NULL && token_cmp(token,'-') != NULL ) token=next_token(token);

    if ( token == NULL ) {        
       token=or_temp_29;
       if ( token != NULL && token_cmp(token,'+') != NULL ) token=next_token(token);
    }


    return token;
} // end match_sign

/*
 * Function: match_unsigned_int
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_unsigned_int(token_t * tokens){
    // unsigned_int: 0-9
    token_t * token=tokens;                //make a copy of the pointer

    // range
    if ( token != NULL && token_cmp_range(token,'0','9') != NULL ) token=next_token(token);


    return token;
} // end match_unsigned_int

/*
 * Function: match_signed_int
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_signed_int(token_t * tokens){
    // signed_int: sign integer
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL ) token = match_sign(token);
    if ( token != NULL ) token = match_integer(token);


    return token;
} // end match_signed_int

/*
 * Function: match_integer
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_integer(token_t * tokens){
    // integer: unsigned_int | signed_int 
    token_t * token=tokens;                //make a copy of the pointer

    // Begin OR block
    token_t * or_temp_30=token;
    if ( token != NULL ) token = match_unsigned_int(token);

    if ( token == NULL ) {        
       token=or_temp_30;
       if ( token != NULL ) token = match_signed_int(token);
    }


    return token;
} // end match_integer

/*
 * Function: match_number
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_number(token_t * tokens){
    // number: int | { int . unsigned_int } |  { . unsigned_int }  [E int]
    token_t * token=tokens;                //make a copy of the pointer

    // Begin OR block
    token_t * or_temp_31=token;
    if ( token != NULL ) token = match_int(token);

    if ( token == NULL ) {        
       token=or_temp_31;
       if ( token != NULL ) token = match_int(token);
       if ( token != NULL && token_cmp(token,'.') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_unsigned_int(token);
    }

    if ( token == NULL ) {        
       token=or_temp_31;
       if ( token != NULL && token_cmp(token,'.') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_unsigned_int(token);
    }
    // end OR Block

    // begin optional block
    if ( token =! NULL ) {
       token_t * opt_temp_32=token;
       if ( token != NULL && token_cmp(token,'E') != NULL ) token=next_token(token);
       if ( token != NULL ) token = match_int(token);
       if ( token == NULL ) token=opt_temp_32;
    }// end optional block


    return token;
} // end match_number

/*
 * Function: match_functions
 * -----------------------------
 *   Generated: 2019-10-24
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */

token_t * match_function(token_t* tokens) {
    token_t * token=NULL;
    token=match_ABS(tokens);
    if (token!=NULL) return token; token=match_ACOS(tokens);
    if (token!=NULL) return token; token=match_ADDDATE(tokens);
    if (token!=NULL) return token; token=match_ADDDATE(tokens);
    if (token!=NULL) return token; token=match_ADDTIME(tokens);
    if (token!=NULL) return token; token=match_ASCII(tokens);
    if (token!=NULL) return token; token=match_ASIN(tokens);
    if (token!=NULL) return token; token=match_ATAN(tokens);
    if (token!=NULL) return token; token=match_ATAN2(tokens);
    if (token!=NULL) return token; token=match_BIN(tokens);
    if (token!=NULL) return token; token=match_BIT_LENGTH(tokens);
    if (token!=NULL) return token; token=match_CEILING(tokens);
    if (token!=NULL) return token; token=match_CEIL(tokens);
    if (token!=NULL) return token; token=match_CHARACTER_LENGTH(tokens);
    if (token!=NULL) return token; token=match_CHAR_LENGTH(tokens);
    if (token!=NULL) return token; token=match_CHAR(tokens);
    if (token!=NULL) return token; token=match_CONCAT(tokens);
    if (token!=NULL) return token; token=match_CONCAT_WS(tokens);
    if (token!=NULL) return token; token=match_CONVERT_TZ(tokens);
    if (token!=NULL) return token; token=match_CONV(tokens);
    if (token!=NULL) return token; token=match_COS(tokens);
    if (token!=NULL) return token; token=match_COT(tokens);
    if (token!=NULL) return token; token=match_CRC32(tokens);
    if (token!=NULL) return token; token=match_CURDATE(tokens);
    if (token!=NULL) return token; token=match_CURRENT_DATE(tokens);
    if (token!=NULL) return token; token=match_CURRENT_TIME(tokens);
    if (token!=NULL) return token; token=match_CURRENT_TIMESTAMP(tokens);
    if (token!=NULL) return token; token=match_CURTIME(tokens);
    if (token!=NULL) return token; token=match_DATE_ADD(tokens);
    if (token!=NULL) return token; token=match_DATE_SUB(tokens);
    if (token!=NULL) return token; token=match_DATEDIFF(tokens);
    if (token!=NULL) return token; token=match_DATE(tokens);
    if (token!=NULL) return token; token=match_DATE_FORMAT(tokens);
    if (token!=NULL) return token; token=match_DATE_SUB(tokens);
    if (token!=NULL) return token; token=match_DAY(tokens);
    if (token!=NULL) return token; token=match_DAYNAME(tokens);
    if (token!=NULL) return token; token=match_DAYOFMONTH(tokens);
    if (token!=NULL) return token; token=match_DAYOFWEEK(tokens);
    if (token!=NULL) return token; token=match_DAYOFYEAR(tokens);
    if (token!=NULL) return token; token=match_DEGREES(tokens);
    if (token!=NULL) return token; token=match_ELT(tokens);
    if (token!=NULL) return token; token=match_EXPORT_SET(tokens);
    if (token!=NULL) return token; token=match_EXP(tokens);
    if (token!=NULL) return token; token=match_EXTRACT(tokens);
    if (token!=NULL) return token; token=match_FIELD(tokens);
    if (token!=NULL) return token; token=match_FIND_IN_SET(tokens);
    if (token!=NULL) return token; token=match_FLOOR(tokens);
    if (token!=NULL) return token; token=match_FORMAT(tokens);
    if (token!=NULL) return token; token=match_FORMAT(tokens);
    if (token!=NULL) return token; token=match_FROM_BASE64(tokens);
    if (token!=NULL) return token; token=match_FROM_DAYS(tokens);
    if (token!=NULL) return token; token=match_FROM_UNIXTIME(tokens);
    if (token!=NULL) return token; token=match_HEX(tokens);
    if (token!=NULL) return token; token=match_HEX(tokens);
    if (token!=NULL) return token; token=match_HOUR(tokens);
    if (token!=NULL) return token; token=match_INSERT(tokens);
    if (token!=NULL) return token; token=match_INSTR(tokens);
    if (token!=NULL) return token; token=match_LAST_DAY(tokens);
    if (token!=NULL) return token; token=match_LCASE(tokens);
    if (token!=NULL) return token; token=match_LEFT(tokens);
    if (token!=NULL) return token; token=match_LENGTH(tokens);
    if (token!=NULL) return token; token=match_LN(tokens);
    if (token!=NULL) return token; token=match_LOAD_FILE(tokens);
    if (token!=NULL) return token; token=match_LOCALTIME(tokens);
    if (token!=NULL) return token; token=match_LOCALTIMESTAMP(tokens);
    if (token!=NULL) return token; token=match_LOCATE(tokens);
    if (token!=NULL) return token; token=match_LOG10(tokens);
    if (token!=NULL) return token; token=match_LOG2(tokens);
    if (token!=NULL) return token; token=match_LOG(tokens);
    if (token!=NULL) return token; token=match_LOWER(tokens);
    if (token!=NULL) return token; token=match_LPAD(tokens);
    if (token!=NULL) return token; token=match_LTRIM(tokens);
    if (token!=NULL) return token; token=match_MAKEDATE(tokens);
    if (token!=NULL) return token; token=match_MAKE_SET(tokens);
    if (token!=NULL) return token; token=match_MAKETIME(tokens);
    if (token!=NULL) return token; token=match_MICROSECOND(tokens);
    if (token!=NULL) return token; token=match_MID(tokens);
    if (token!=NULL) return token; token=match_MINUTE(tokens);
    if (token!=NULL) return token; token=match_MOD(tokens);
    if (token!=NULL) return token; token=match_MONTH(tokens);
    if (token!=NULL) return token; token=match_MONTHNAME(tokens);
    if (token!=NULL) return token; token=match_NOW(tokens);
    if (token!=NULL) return token; token=match_OCTET_LENGTH(tokens);
    if (token!=NULL) return token; token=match_OCT(tokens);
    if (token!=NULL) return token; token=match_ORD(tokens);
    if (token!=NULL) return token; token=match_PERIOD_ADD(tokens);
    if (token!=NULL) return token; token=match_PERIOD_DIFF(tokens);
    if (token!=NULL) return token; token=match_PI(tokens);
    if (token!=NULL) return token; token=match_POSITION(tokens);
    if (token!=NULL) return token; token=match_POWER(tokens);
    if (token!=NULL) return token; token=match_POW(tokens);
    if (token!=NULL) return token; token=match_QUARTER(tokens);
    if (token!=NULL) return token; token=match_QUOTE(tokens);
    if (token!=NULL) return token; token=match_RADIANS(tokens);
    if (token!=NULL) return token; token=match_RAND(tokens);
    if (token!=NULL) return token; token=match_REPEAT(tokens);
    if (token!=NULL) return token; token=match_REPLACE(tokens);
    if (token!=NULL) return token; token=match_REVERSE(tokens);
    if (token!=NULL) return token; token=match_RIGHT(tokens);
    if (token!=NULL) return token; token=match_ROUND(tokens);
    if (token!=NULL) return token; token=match_RPAD(tokens);
    if (token!=NULL) return token; token=match_RTRIM(tokens);
    if (token!=NULL) return token; token=match_SECOND(tokens);
    if (token!=NULL) return token; token=match_SEC_TO_TIME(tokens);
    if (token!=NULL) return token; token=match_SIGN(tokens);
    if (token!=NULL) return token; token=match_SIN(tokens);
    if (token!=NULL) return token; token=match_SOUNDEX(tokens);
    if (token!=NULL) return token; token=match_SPACE(tokens);
    if (token!=NULL) return token; token=match_SQRT(tokens);
    if (token!=NULL) return token; token=match_STR_TO_DATE(tokens);
    if (token!=NULL) return token; token=match_SUBDATE(tokens);
    if (token!=NULL) return token; token=match_SUBDATE(tokens);
    if (token!=NULL) return token; token=match_SUBSTRING_INDEX(tokens);
    if (token!=NULL) return token; token=match_SUBSTRING(tokens);
    if (token!=NULL) return token; token=match_SUBSTRING(tokens);
    if (token!=NULL) return token; token=match_SUBSTRING(tokens);
    if (token!=NULL) return token; token=match_SUBSTR(tokens);
    if (token!=NULL) return token; token=match_SUBSTR(tokens);
    if (token!=NULL) return token; token=match_SUBSTR(tokens);
    if (token!=NULL) return token; token=match_SUBTIME(tokens);
    if (token!=NULL) return token; token=match_SYSDATE(tokens);
    if (token!=NULL) return token; token=match_TAN(tokens);
    if (token!=NULL) return token; token=match_TIMEDIFF(tokens);
    if (token!=NULL) return token; token=match_TIME(tokens);
    if (token!=NULL) return token; token=match_TIME_FORMAT(tokens);
    if (token!=NULL) return token; token=match_TIMESTAMPADD(tokens);
    if (token!=NULL) return token; token=match_TIMESTAMPDIFF(tokens);
    if (token!=NULL) return token; token=match_TIMESTAMP(tokens);
    if (token!=NULL) return token; token=match_TIME_TO_SEC(tokens);
    if (token!=NULL) return token; token=match_TO_BASE64(tokens);
    if (token!=NULL) return token; token=match_TO_DAYS(tokens);
    if (token!=NULL) return token; token=match_TO_SECONDS(tokens);
    if (token!=NULL) return token; token=match_TRIM(tokens);
    if (token!=NULL) return token; token=match_TRUNCATE(tokens);
    if (token!=NULL) return token; token=match_UCASE(tokens);
    if (token!=NULL) return token; token=match_UNHEX(tokens);
    if (token!=NULL) return token; token=match_UNIX_TIMESTAMP(tokens);
    if (token!=NULL) return token; token=match_UTC_DATE(tokens);
    if (token!=NULL) return token; token=match_UTC_TIMESTAMP(tokens);
    if (token!=NULL) return token; token=match_UTC_TIME(tokens);
    if (token!=NULL) return token; token=match_WEEK(tokens);
    if (token!=NULL) return token; token=match_WEEKDAY(tokens);
    if (token!=NULL) return token; token=match_WEEKOFYEAR(tokens);
    if (token!=NULL) return token; token=match_YEAR(tokens);
    if (token!=NULL) return token; token=match_YEARWEEK(tokens);
    if (token!=NULL) return token; token=match_YEARWEEK(tokens);
    if (token!=NULL) return token; token=match_alpha(tokens);
    if (token!=NULL) return token; token=match_string(tokens);
    if (token!=NULL) return token; token=match_sign(tokens);
    if (token!=NULL) return token; token=match_unsigned_int(tokens);
    if (token!=NULL) return token; token=match_signed_int(tokens);
    if (token!=NULL) return token; token=match_integer(tokens);
    if (token!=NULL) return token; token=match_number(tokens);
    return token;
} // end match functions
