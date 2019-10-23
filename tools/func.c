
PAREN_LEFT=1
PAREN_RIGHT=2


/*
 * Function: match_ABS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ABS(token_t * tokens){
    //ABS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ABS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ABS

/*
 * Function: match_ACOS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ACOS(token_t * tokens){
    //ACOS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ACOS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ACOS

/*
 * Function: match_ADDDATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ADDDATE(token_t * tokens){
    //ADDDATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ADDDATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('INTERVAL') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ADDDATE

/*
 * Function: match_ADDDATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ADDDATE(token_t * tokens){
    //ADDDATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ADDDATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_days(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ADDDATE

/*
 * Function: match_ADDTIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ADDTIME(token_t * tokens){
    //ADDTIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ADDTIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ADDTIME

/*
 * Function: match_ASCII
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ASCII(token_t * tokens){
    //ASCII
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ASCII') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ASCII

/*
 * Function: match_ASIN
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ASIN(token_t * tokens){
    //ASIN
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ASIN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ASIN

/*
 * Function: match_ATAN
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ATAN(token_t * tokens){
    //ATAN
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ATAN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ATAN

/*
 * Function: match_ATAN2
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ATAN2(token_t * tokens){
    //ATAN2
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ATAN2') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('Y') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ATAN2

/*
 * Function: match_BIN
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_BIN(token_t * tokens){
    //BIN
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('BIN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_BIN

/*
 * Function: match_BIT_LENGTH
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_BIT_LENGTH(token_t * tokens){
    //BIT_LENGTH
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('BIT_LENGTH') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_BIT_LENGTH

/*
 * Function: match_CEILING
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CEILING(token_t * tokens){
    //CEILING
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CEILING') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CEILING

/*
 * Function: match_CEIL
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CEIL(token_t * tokens){
    //CEIL
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CEIL') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CEIL

/*
 * Function: match_CHARACTER_LENGTH
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CHARACTER_LENGTH(token_t * tokens){
    //CHARACTER_LENGTH
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CHARACTER_LENGTH') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CHARACTER_LENGTH

/*
 * Function: match_CHAR_LENGTH
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CHAR_LENGTH(token_t * tokens){
    //CHAR_LENGTH
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CHAR_LENGTH') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CHAR_LENGTH

/*
 * Function: match_CHAR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CHAR(token_t * tokens){
    //CHAR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CHAR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_...(token);


    // CHAR ( N , ...  [ USING charset_name ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_2=token;
       if ( token.cmp('USING') != NULL ) token=next_token(token);        //data match
       if ( token != NULL ) token = match_charset_name(token);
       if ( token == NULL ) token = optional_token_2;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CHAR

/*
 * Function: match_CONCAT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONCAT(token_t * tokens){
    //CONCAT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CONCAT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_...(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CONCAT

/*
 * Function: match_CONCAT_WS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONCAT_WS(token_t * tokens){
    //CONCAT_WS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CONCAT_WS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_separator(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_...(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CONCAT_WS

/*
 * Function: match_CONVERT_TZ
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONVERT_TZ(token_t * tokens){
    //CONVERT_TZ
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CONVERT_TZ') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_dt(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_from_tz(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_to_tz(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CONVERT_TZ

/*
 * Function: match_CONV
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CONV(token_t * tokens){
    //CONV
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CONV') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_from_base(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_to_base(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CONV

/*
 * Function: match_COS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_COS(token_t * tokens){
    //COS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('COS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_COS

/*
 * Function: match_COT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_COT(token_t * tokens){
    //COT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('COT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_COT

/*
 * Function: match_CRC32
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CRC32(token_t * tokens){
    //CRC32
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CRC32') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CRC32

/*
 * Function: match_CURDATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURDATE(token_t * tokens){
    //CURDATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CURDATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CURDATE

/*
 * Function: match_CURRENT_DATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURRENT_DATE(token_t * tokens){
    //CURRENT_DATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CURRENT_DATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CURRENT_DATE

/*
 * Function: match_CURRENT_TIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURRENT_TIME(token_t * tokens){
    //CURRENT_TIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CURRENT_TIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // CURRENT_TIME (  [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_3=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_3;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CURRENT_TIME

/*
 * Function: match_CURRENT_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURRENT_TIMESTAMP(token_t * tokens){
    //CURRENT_TIMESTAMP
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CURRENT_TIMESTAMP') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // CURRENT_TIMESTAMP (  [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_4=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_4;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CURRENT_TIMESTAMP

/*
 * Function: match_CURTIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_CURTIME(token_t * tokens){
    //CURTIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('CURTIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // CURTIME (  [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_5=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_5;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_CURTIME

/*
 * Function: match_DATE_ADD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_ADD(token_t * tokens){
    //DATE_ADD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DATE_ADD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('INTERVAL') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DATE_ADD

/*
 * Function: match_DATE_SUB
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_SUB(token_t * tokens){
    //DATE_SUB
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DATE_SUB') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('INTERVAL') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DATE_SUB

/*
 * Function: match_DATEDIFF
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATEDIFF(token_t * tokens){
    //DATEDIFF
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DATEDIFF') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DATEDIFF

/*
 * Function: match_DATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE(token_t * tokens){
    //DATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DATE

/*
 * Function: match_DATE_FORMAT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_FORMAT(token_t * tokens){
    //DATE_FORMAT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DATE_FORMAT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_format(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DATE_FORMAT

/*
 * Function: match_DATE_SUB
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DATE_SUB(token_t * tokens){
    //DATE_SUB
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DATE_SUB') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('INTERVAL') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DATE_SUB

/*
 * Function: match_DAY
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAY(token_t * tokens){
    //DAY
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DAY') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DAY

/*
 * Function: match_DAYNAME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYNAME(token_t * tokens){
    //DAYNAME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DAYNAME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DAYNAME

/*
 * Function: match_DAYOFMONTH
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYOFMONTH(token_t * tokens){
    //DAYOFMONTH
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DAYOFMONTH') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DAYOFMONTH

/*
 * Function: match_DAYOFWEEK
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYOFWEEK(token_t * tokens){
    //DAYOFWEEK
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DAYOFWEEK') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DAYOFWEEK

/*
 * Function: match_DAYOFYEAR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DAYOFYEAR(token_t * tokens){
    //DAYOFYEAR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DAYOFYEAR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DAYOFYEAR

/*
 * Function: match_DEGREES
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_DEGREES(token_t * tokens){
    //DEGREES
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('DEGREES') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_DEGREES

/*
 * Function: match_ELT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ELT(token_t * tokens){
    //ELT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ELT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str3(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_...(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ELT

/*
 * Function: match_EXPORT_SET
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_EXPORT_SET(token_t * tokens){
    //EXPORT_SET
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('EXPORT_SET') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_bits(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_on(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_off(token);


    // EXPORT_SET ( bits , on , off [  , separator [  , number_of_bits ]  ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_6=token;
       if ( token != NULL ) token = match_,(token);
       if ( token != NULL ) token = match_separator(token);


       //  , separator [  , number_of_bits ] 
       if ( token != NULL ) {         //Match must be successfull to proceed
          token_t *optional_token_7=token;
          if ( token != NULL ) token = match_,(token);
          if ( token != NULL ) token = match_number_of_bits(token);
          if ( token == NULL ) token = optional_token_7;
       }//END Optional
       if ( token == NULL ) token = optional_token_6;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_EXPORT_SET

/*
 * Function: match_EXP
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_EXP(token_t * tokens){
    //EXP
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('EXP') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_EXP

/*
 * Function: match_EXTRACT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_EXTRACT(token_t * tokens){
    //EXTRACT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('EXTRACT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_unit(token);
    if ( token.cmp('FROM') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_EXTRACT

/*
 * Function: match_FIELD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FIELD(token_t * tokens){
    //FIELD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FIELD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str3(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_...(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FIELD

/*
 * Function: match_FIND_IN_SET
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FIND_IN_SET(token_t * tokens){
    //FIND_IN_SET
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FIND_IN_SET') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_strlist(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FIND_IN_SET

/*
 * Function: match_FLOOR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FLOOR(token_t * tokens){
    //FLOOR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FLOOR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FLOOR

/*
 * Function: match_FORMAT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FORMAT(token_t * tokens){
    //FORMAT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FORMAT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('D') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FORMAT

/*
 * Function: match_FORMAT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FORMAT(token_t * tokens){
    //FORMAT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FORMAT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('D') != NULL ) token=next_token(token);        //data match


    // FORMAT ( X , D [  , locale ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_8=token;
       if ( token != NULL ) token = match_,(token);
       if ( token != NULL ) token = match_locale(token);
       if ( token == NULL ) token = optional_token_8;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FORMAT

/*
 * Function: match_FROM_BASE64
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FROM_BASE64(token_t * tokens){
    //FROM_BASE64
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FROM_BASE64') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FROM_BASE64

/*
 * Function: match_FROM_DAYS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FROM_DAYS(token_t * tokens){
    //FROM_DAYS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FROM_DAYS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FROM_DAYS

/*
 * Function: match_FROM_UNIXTIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_FROM_UNIXTIME(token_t * tokens){
    //FROM_UNIXTIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('FROM_UNIXTIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_unix_timestamp(token);


    // FROM_UNIXTIME ( unix_timestamp [  , format ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_9=token;
       if ( token != NULL ) token = match_,(token);
       if ( token != NULL ) token = match_format(token);
       if ( token == NULL ) token = optional_token_9;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_FROM_UNIXTIME

/*
 * Function: match_HEX
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_HEX(token_t * tokens){
    //HEX
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('HEX') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N_or_S') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_HEX

/*
 * Function: match_HEX
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_HEX(token_t * tokens){
    //HEX
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('HEX') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
       if ( token != NULL ) token = match_str(token);


       if ( token == NULL ) {        
          token=token_or_10
       }//end OR  
    if ( token != NULL ) token = match_}(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_HEX

/*
 * Function: match_HOUR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_HOUR(token_t * tokens){
    //HOUR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('HOUR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_time(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_HOUR

/*
 * Function: match_INSERT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_INSERT(token_t * tokens){
    //INSERT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('INSERT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_newstr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_INSERT

/*
 * Function: match_INSTR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_INSTR(token_t * tokens){
    //INSTR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('INSTR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_substr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_INSTR

/*
 * Function: match_LAST_DAY
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LAST_DAY(token_t * tokens){
    //LAST_DAY
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LAST_DAY') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LAST_DAY

/*
 * Function: match_LCASE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LCASE(token_t * tokens){
    //LCASE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LCASE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LCASE

/*
 * Function: match_LEFT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LEFT(token_t * tokens){
    //LEFT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LEFT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LEFT

/*
 * Function: match_LENGTH
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LENGTH(token_t * tokens){
    //LENGTH
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LENGTH') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LENGTH

/*
 * Function: match_LN
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LN(token_t * tokens){
    //LN
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LN

/*
 * Function: match_LOAD_FILE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOAD_FILE(token_t * tokens){
    //LOAD_FILE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOAD_FILE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_file_name(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOAD_FILE

/*
 * Function: match_LOCALTIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOCALTIME(token_t * tokens){
    //LOCALTIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOCALTIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // LOCALTIME (  [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_11=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_11;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOCALTIME

/*
 * Function: match_LOCALTIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOCALTIMESTAMP(token_t * tokens){
    //LOCALTIMESTAMP
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOCALTIMESTAMP') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // LOCALTIMESTAMP (  [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_12=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_12;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOCALTIMESTAMP

/*
 * Function: match_LOCATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOCATE(token_t * tokens){
    //LOCATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOCATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_substr(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str(token);


    // LOCATE ( substr , str [  , pos ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_13=token;
       if ( token != NULL ) token = match_,(token);
       if ( token != NULL ) token = match_pos(token);
       if ( token == NULL ) token = optional_token_13;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOCATE

/*
 * Function: match_LOG10
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOG10(token_t * tokens){
    //LOG10
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOG10') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOG10

/*
 * Function: match_LOG2
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOG2(token_t * tokens){
    //LOG2
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOG2') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOG2

/*
 * Function: match_LOG
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOG(token_t * tokens){
    //LOG
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOG') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // LOG (  [ B ] , X )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_14=token;
       if ( token.cmp('B') != NULL ) token=next_token(token);        //data match
       if ( token == NULL ) token = optional_token_14;
    }//END Optional
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOG

/*
 * Function: match_LOWER
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LOWER(token_t * tokens){
    //LOWER
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LOWER') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LOWER

/*
 * Function: match_LPAD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LPAD(token_t * tokens){
    //LPAD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LPAD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_padstr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LPAD

/*
 * Function: match_LTRIM
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_LTRIM(token_t * tokens){
    //LTRIM
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('LTRIM') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_LTRIM

/*
 * Function: match_MAKEDATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MAKEDATE(token_t * tokens){
    //MAKEDATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MAKEDATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_year(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_dayofyear(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MAKEDATE

/*
 * Function: match_MAKE_SET
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MAKE_SET(token_t * tokens){
    //MAKE_SET
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MAKE_SET') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_bits(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_str2(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_...(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MAKE_SET

/*
 * Function: match_MAKETIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MAKETIME(token_t * tokens){
    //MAKETIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MAKETIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_hour(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_minute(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_second(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MAKETIME

/*
 * Function: match_MICROSECOND
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MICROSECOND(token_t * tokens){
    //MICROSECOND
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MICROSECOND') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MICROSECOND

/*
 * Function: match_MID
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MID(token_t * tokens){
    //MID
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MID') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MID

/*
 * Function: match_MINUTE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MINUTE(token_t * tokens){
    //MINUTE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MINUTE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_time(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MINUTE

/*
 * Function: match_MOD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MOD(token_t * tokens){
    //MOD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MOD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('M') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MOD

/*
 * Function: match_MONTH
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MONTH(token_t * tokens){
    //MONTH
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MONTH') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MONTH

/*
 * Function: match_MONTHNAME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_MONTHNAME(token_t * tokens){
    //MONTHNAME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('MONTHNAME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_MONTHNAME

/*
 * Function: match_NOW
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_NOW(token_t * tokens){
    //NOW
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('NOW') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // NOW (  [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_15=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_15;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_NOW

/*
 * Function: match_OCTET_LENGTH
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_OCTET_LENGTH(token_t * tokens){
    //OCTET_LENGTH
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('OCTET_LENGTH') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_OCTET_LENGTH

/*
 * Function: match_OCT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_OCT(token_t * tokens){
    //OCT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('OCT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_OCT

/*
 * Function: match_ORD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ORD(token_t * tokens){
    //ORD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ORD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ORD

/*
 * Function: match_PERIOD_ADD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_PERIOD_ADD(token_t * tokens){
    //PERIOD_ADD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('PERIOD_ADD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('P') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_PERIOD_ADD

/*
 * Function: match_PERIOD_DIFF
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_PERIOD_DIFF(token_t * tokens){
    //PERIOD_DIFF
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('PERIOD_DIFF') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('P1') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('P2') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_PERIOD_DIFF

/*
 * Function: match_PI
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_PI(token_t * tokens){
    //PI
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('PI') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_PI

/*
 * Function: match_POSITION
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_POSITION(token_t * tokens){
    //POSITION
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('POSITION') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_substr(token);
    if ( token.cmp('IN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_POSITION

/*
 * Function: match_POWER
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_POWER(token_t * tokens){
    //POWER
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('POWER') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('Y') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_POWER

/*
 * Function: match_POW
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_POW(token_t * tokens){
    //POW
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('POW') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('Y') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_POW

/*
 * Function: match_QUARTER
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_QUARTER(token_t * tokens){
    //QUARTER
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('QUARTER') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_QUARTER

/*
 * Function: match_QUOTE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_QUOTE(token_t * tokens){
    //QUOTE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('QUOTE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_QUOTE

/*
 * Function: match_RADIANS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RADIANS(token_t * tokens){
    //RADIANS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('RADIANS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_RADIANS

/*
 * Function: match_RAND
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RAND(token_t * tokens){
    //RAND
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('RAND') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // RAND (  [ N ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_16=token;
       if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
       if ( token == NULL ) token = optional_token_16;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_RAND

/*
 * Function: match_REPEAT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_REPEAT(token_t * tokens){
    //REPEAT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('REPEAT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_count(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_REPEAT

/*
 * Function: match_REPLACE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_REPLACE(token_t * tokens){
    //REPLACE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('REPLACE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_from_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_to_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_REPLACE

/*
 * Function: match_REVERSE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_REVERSE(token_t * tokens){
    //REVERSE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('REVERSE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_REVERSE

/*
 * Function: match_RIGHT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RIGHT(token_t * tokens){
    //RIGHT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('RIGHT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_RIGHT

/*
 * Function: match_ROUND
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_ROUND(token_t * tokens){
    //ROUND
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('ROUND') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match


    // ROUND ( X [  , D ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_17=token;
       if ( token != NULL ) token = match_,(token);
       if ( token.cmp('D') != NULL ) token=next_token(token);        //data match
       if ( token == NULL ) token = optional_token_17;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_ROUND

/*
 * Function: match_RPAD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RPAD(token_t * tokens){
    //RPAD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('RPAD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_padstr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_RPAD

/*
 * Function: match_RTRIM
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_RTRIM(token_t * tokens){
    //RTRIM
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('RTRIM') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_RTRIM

/*
 * Function: match_SECOND
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SECOND(token_t * tokens){
    //SECOND
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SECOND') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_time(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SECOND

/*
 * Function: match_SEC_TO_TIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SEC_TO_TIME(token_t * tokens){
    //SEC_TO_TIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SEC_TO_TIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_seconds(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SEC_TO_TIME

/*
 * Function: match_SIGN
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SIGN(token_t * tokens){
    //SIGN
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SIGN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SIGN

/*
 * Function: match_SIN
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SIN(token_t * tokens){
    //SIN
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SIN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SIN

/*
 * Function: match_SOUNDEX
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SOUNDEX(token_t * tokens){
    //SOUNDEX
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SOUNDEX') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SOUNDEX

/*
 * Function: match_SPACE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SPACE(token_t * tokens){
    //SPACE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SPACE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('N') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SPACE

/*
 * Function: match_SQRT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SQRT(token_t * tokens){
    //SQRT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SQRT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SQRT

/*
 * Function: match_STR_TO_DATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_STR_TO_DATE(token_t * tokens){
    //STR_TO_DATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('STR_TO_DATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_format(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_STR_TO_DATE

/*
 * Function: match_SUBDATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBDATE(token_t * tokens){
    //SUBDATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBDATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('INTERVAL') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_unit(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBDATE

/*
 * Function: match_SUBDATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBDATE(token_t * tokens){
    //SUBDATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBDATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_days(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBDATE

/*
 * Function: match_SUBSTRING_INDEX
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING_INDEX(token_t * tokens){
    //SUBSTRING_INDEX
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBSTRING_INDEX') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_delim(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_count(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBSTRING_INDEX

/*
 * Function: match_SUBSTRING
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING(token_t * tokens){
    //SUBSTRING
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBSTRING') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBSTRING

/*
 * Function: match_SUBSTRING
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING(token_t * tokens){
    //SUBSTRING
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBSTRING') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('FROM') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_pos(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBSTRING

/*
 * Function: match_SUBSTRING
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTRING(token_t * tokens){
    //SUBSTRING
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBSTRING') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBSTRING

/*
 * Function: match_SUBSTR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTR(token_t * tokens){
    //SUBSTR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBSTR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBSTR

/*
 * Function: match_SUBSTR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTR(token_t * tokens){
    //SUBSTR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBSTR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('FROM') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_pos(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBSTR

/*
 * Function: match_SUBSTR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBSTR(token_t * tokens){
    //SUBSTR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBSTR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_pos(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_len(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBSTR

/*
 * Function: match_SUBTIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SUBTIME(token_t * tokens){
    //SUBTIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SUBTIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SUBTIME

/*
 * Function: match_SYSDATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_SYSDATE(token_t * tokens){
    //SYSDATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('SYSDATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // SYSDATE (  [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_18=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_18;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_SYSDATE

/*
 * Function: match_TAN
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TAN(token_t * tokens){
    //TAN
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TAN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TAN

/*
 * Function: match_TIMEDIFF
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMEDIFF(token_t * tokens){
    //TIMEDIFF
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TIMEDIFF') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_expr2(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TIMEDIFF

/*
 * Function: match_TIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIME(token_t * tokens){
    //TIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TIME

/*
 * Function: match_TIME_FORMAT
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIME_FORMAT(token_t * tokens){
    //TIME_FORMAT
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TIME_FORMAT') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_time(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_format(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TIME_FORMAT

/*
 * Function: match_TIMESTAMPADD
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMESTAMPADD(token_t * tokens){
    //TIMESTAMPADD
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TIMESTAMPADD') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_interval(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_datetime_expr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TIMESTAMPADD

/*
 * Function: match_TIMESTAMPDIFF
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMESTAMPDIFF(token_t * tokens){
    //TIMESTAMPDIFF
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TIMESTAMPDIFF') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_unit(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_datetime_expr1(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_datetime_expr2(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TIMESTAMPDIFF

/*
 * Function: match_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIMESTAMP(token_t * tokens){
    //TIMESTAMP
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TIMESTAMP') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr1(token);


    // TIMESTAMP ( expr1 [  , expr2 ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_19=token;
       if ( token != NULL ) token = match_,(token);
       if ( token != NULL ) token = match_expr2(token);
       if ( token == NULL ) token = optional_token_19;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TIMESTAMP

/*
 * Function: match_TIME_TO_SEC
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TIME_TO_SEC(token_t * tokens){
    //TIME_TO_SEC
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TIME_TO_SEC') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_time(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TIME_TO_SEC

/*
 * Function: match_TO_BASE64
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TO_BASE64(token_t * tokens){
    //TO_BASE64
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TO_BASE64') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TO_BASE64

/*
 * Function: match_TO_DAYS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TO_DAYS(token_t * tokens){
    //TO_DAYS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TO_DAYS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TO_DAYS

/*
 * Function: match_TO_SECONDS
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TO_SECONDS(token_t * tokens){
    //TO_SECONDS
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TO_SECONDS') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_expr(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TO_SECONDS

/*
 * Function: match_TRIM
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TRIM(token_t * tokens){
    //TRIM
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TRIM') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // TRIM (  [ { BOTH | LEADING | TRAILING }  [ remstr ] FROM ] str )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_20=token;
          if ( token.cmp('BOTH') != NULL ) token=next_token(token);        //data match


          if ( token == NULL ) {        
             token=token_or_21
          }//end OR  


          if ( token == NULL ) {        
             token=token_or_21
          }//end OR  
       if ( token != NULL ) token = match_}(token);


       // { BOTH | LEADING | TRAILING }  [ remstr ] FROM
       if ( token != NULL ) {         //Match must be successfull to proceed
          token_t *optional_token_22=token;
          if ( token != NULL ) token = match_remstr(token);
          if ( token == NULL ) token = optional_token_22;
       }//END Optional
       if ( token.cmp('FROM') != NULL ) token=next_token(token);        //data match
       if ( token == NULL ) token = optional_token_20;
    }//END Optional
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TRIM

/*
 * Function: match_TRUNCATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_TRUNCATE(token_t * tokens){
    //TRUNCATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('TRUNCATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('X') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_,(token);
    if ( token.cmp('D') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_TRUNCATE

/*
 * Function: match_UCASE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UCASE(token_t * tokens){
    //UCASE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('UCASE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_UCASE

/*
 * Function: match_UNHEX
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UNHEX(token_t * tokens){
    //UNHEX
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('UNHEX') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_str(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_UNHEX

/*
 * Function: match_UNIX_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UNIX_TIMESTAMP(token_t * tokens){
    //UNIX_TIMESTAMP
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('UNIX_TIMESTAMP') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // UNIX_TIMESTAMP ( [ date ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_23=token;
       if ( token != NULL ) token = match_date(token);
       if ( token == NULL ) token = optional_token_23;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_UNIX_TIMESTAMP

/*
 * Function: match_UTC_DATE
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UTC_DATE(token_t * tokens){
    //UTC_DATE
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('UTC_DATE') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_UTC_DATE

/*
 * Function: match_UTC_TIMESTAMP
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UTC_TIMESTAMP(token_t * tokens){
    //UTC_TIMESTAMP
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('UTC_TIMESTAMP') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // UTC_TIMESTAMP ( [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_24=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_24;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_UTC_TIMESTAMP

/*
 * Function: match_UTC_TIME
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_UTC_TIME(token_t * tokens){
    //UTC_TIME
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('UTC_TIME') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match


    // UTC_TIME ( [ fsp ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_25=token;
       if ( token != NULL ) token = match_fsp(token);
       if ( token == NULL ) token = optional_token_25;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_UTC_TIME

/*
 * Function: match_WEEK
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_WEEK(token_t * tokens){
    //WEEK
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('WEEK') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);


    // WEEK ( date [  , mode ] )
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_26=token;
       if ( token != NULL ) token = match_,(token);
       if ( token != NULL ) token = match_mode(token);
       if ( token == NULL ) token = optional_token_26;
    }//END Optional
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_WEEK

/*
 * Function: match_WEEKDAY
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_WEEKDAY(token_t * tokens){
    //WEEKDAY
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('WEEKDAY') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_WEEKDAY

/*
 * Function: match_WEEKOFYEAR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_WEEKOFYEAR(token_t * tokens){
    //WEEKOFYEAR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('WEEKOFYEAR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_WEEKOFYEAR

/*
 * Function: match_YEAR
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_YEAR(token_t * tokens){
    //YEAR
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('YEAR') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_YEAR

/*
 * Function: match_YEARWEEK
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_YEARWEEK(token_t * tokens){
    //YEARWEEK
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('YEARWEEK') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_YEARWEEK

/*
 * Function: match_YEARWEEK
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_YEARWEEK(token_t * tokens){
    //YEARWEEK
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('YEARWEEK') != NULL ) token=next_token(token);        //data match
    if ( token.cmp('LEFT_PAREN') != NULL ) token=next_token(token);        //data match
    if ( token != NULL ) token = match_date(token);
    if ( token != NULL ) token = match_,(token);
    if ( token != NULL ) token = match_mode(token);
    if ( token.cmp('RIGHT_PAREN') != NULL ) token=next_token(token);        //data match


   return token;
}//end match_YEARWEEK

/*
 * Function: match_alpha
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_alpha(token_t * tokens){
    //alpha
    token_t * token=tokens;                //make a copy of the pointer

    if ( token.cmp('A-Z') != NULL ) token=next_token(token);        //data match


    if ( token == NULL ) {        
       token=token_or_27
    }//end OR  


   return token;
}//end match_alpha

/*
 * Function: match_string
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_string(token_t * tokens){
    //string
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL ) token = match_'(token);


    // ' [ * ] ' | " [ * ] "
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_28=token;
       if ( token != NULL ) token = match_*(token);
       if ( token == NULL ) token = optional_token_28;
    }//END Optional
    if ( token != NULL ) token = match_'(token);


    if ( token == NULL ) {        
       token=????
    }//end OR  


    // ' [ * ] ' | " [ * ] "
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_29=token;
       if ( token != NULL ) token = match_*(token);
       if ( token == NULL ) token = optional_token_29;
    }//END Optional
    if ( token != NULL ) token = match_"(token);


   return token;
}//end match_string

/*
 * Function: match_sign
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_sign(token_t * tokens){
    //sign
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL ) token = match_-(token);


    if ( token == NULL ) {        
       token=token_or_30
    }//end OR  


   return token;
}//end match_sign

/*
 * Function: match_unsigned_integer
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_unsigned_integer(token_t * tokens){
    //unsigned_integer
    token_t * token=tokens;                //make a copy of the pointer



    //  [ 0-9 ] +
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_31=token;
       if ( token != NULL ) token = match_0-9(token);
       if ( token == NULL ) token = optional_token_31;
    }//END Optional
    if ( token != NULL ) token = match_+(token);


   return token;
}//end match_unsigned_integer

/*
 * Function: match_signed_integer
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_signed_integer(token_t * tokens){
    //signed_integer
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL ) token = match_sign(token);
    if ( token != NULL ) token = match_integer(token);


   return token;
}//end match_signed_integer

/*
 * Function: match_integer
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_integer(token_t * tokens){
    //integer
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL ) token = match_unsigned_int(token);


    if ( token == NULL ) {        
       token=token_or_32
    }//end OR  


   return token;
}//end match_integer

/*
 * Function: match_number
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_number(token_t * tokens){
    //number
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL ) token = match_int(token);


    if ( token == NULL ) {        
       token=token_or_33
       if ( token != NULL ) token = match_int(token);
       if ( token != NULL ) token = match_.(token);
       if ( token != NULL ) token = match_unsigned_int(token);
    }//end OR  


    if ( token == NULL ) {        
       token=token_or_33
       if ( token != NULL ) token = match_.(token);
       if ( token != NULL ) token = match_unsigned_int(token);
    }//end OR  


    // int | { int . unsigned_int } |  { . unsigned_int }  [ E int ] 
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_34=token;
       if ( token.cmp('E') != NULL ) token=next_token(token);        //data match
       if ( token != NULL ) token = match_int(token);
       if ( token == NULL ) token = optional_token_34;
    }//END Optional


   return token;
}//end match_number

/*
 * Function: match_number
 * -----------------------------
 *   Generated: 2019-10-22
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_number(token_t * tokens){
    //number
    token_t * token=tokens;                //make a copy of the pointer

    if ( token != NULL ) token = match_int(token);


    if ( token == NULL ) {        
       token=token_or_35
       if ( token != NULL ) token = match_int(token);
          if ( token != NULL ) token = match_.(token);


          if ( token == NULL ) {        
             token=token_or_36
          }//end OR  


          if ( token == NULL ) {        
             token=token_or_36
          }//end OR  
          if ( token != NULL ) token = match_r(token);
          if ( token != NULL ) token = match_](token);
       if ( token != NULL ) token = match_}(token);
       if ( token != NULL ) token = match_unsigned_int(token);
    }//end OR  


    if ( token == NULL ) {        
       token=token_or_35
       if ( token != NULL ) token = match_.(token);
       if ( token != NULL ) token = match_unsigned_int(token);
    }//end OR  


    // int | { int { . | unsigned_int |  [ r ] } unsigned_int } |  { . unsigned_int }  [ E int ] 
    if ( token != NULL ) {         //Match must be successfull to proceed
       token_t *optional_token_37=token;
       if ( token.cmp('E') != NULL ) token=next_token(token);        //data match
       if ( token != NULL ) token = match_int(token);
       if ( token == NULL ) token = optional_token_37;
    }//END Optional


   return token;
}//end match_number
