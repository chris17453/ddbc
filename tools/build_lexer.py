import datetime

functions=[
 {  'ABS':                  'ABS ( X )'  }, 
 {  'ACOS':                 'ACOS ( X )'  }, 
 {  'ADDDATE':              'ADDDATE ( date, INTERVAL expr unit )'  }, 
 {  'ADDDATE':              'ADDDATE ( expr, days )'  }, 
 {  'ADDTIME':              'ADDTIME ( expr1, expr2 )'  }, 
 {  'ASCII':                'ASCII ( str )'  }, 
 {  'ASIN':                 'ASIN ( X )'  }, 
 {  'ATAN':                 'ATAN ( X )'  }, 
 {  'ATAN2':                'ATAN2 ( Y, X )'  }, 
 {  'BIN':                  'BIN ( N )'  }, 
 {  'BIT_LENGTH':           'BIT_LENGTH ( str )'  }, 
 {  'CEILING':              'CEILING ( X )'  }, 
 {  'CEIL':                 'CEIL ( X )'  }, 
 {  'CHARACTER_LENGTH':     'CHARACTER_LENGTH ( str )'  }, 
 {  'CHAR_LENGTH':          'CHAR_LENGTH ( str )'  }, 
 {  'CHAR':                 'CHAR ( N, ...  [ USING charset_name ] )'  }, 
 {  'CONCAT':               'CONCAT ( str1, str2, ... )'  }, 
 {  'CONCAT_WS':            'CONCAT_WS ( separator, str1, str2, ... )'  }, 
 {  'CONVERT_TZ':           'CONVERT_TZ ( dt, from_tz, to_tz )'  }, 
 {  'CONV':                 'CONV ( N, from_base, to_base )'  }, 
 {  'COS':                  'COS ( X )'  }, 
 {  'COT':                  'COT ( X )'  }, 
 {  'CRC32':                'CRC32 ( expr )'  }, 
 {  'CURDATE':              'CURDATE (  )'  }, 
 {  'CURRENT_DATE':         'CURRENT_DATE (  )'  }, 
 {  'CURRENT_TIME':         'CURRENT_TIME (  [ fsp ] )'  }, 
 {  'CURRENT_TIMESTAMP':    'CURRENT_TIMESTAMP (  [ fsp ] )'  }, 
 {  'CURTIME':              'CURTIME (  [ fsp ] )'  }, 
 {  'DATE_ADD':             'DATE_ADD ( date, INTERVAL expr unit )'  }, 
 {  'DATE_SUB':             'DATE_SUB ( date, INTERVAL expr unit )'  }, 
 {  'DATEDIFF':             'DATEDIFF ( expr1, expr2 )'  }, 
 {  'DATE':                 'DATE ( expr )'  }, 
 {  'DATE_FORMAT':          'DATE_FORMAT ( date, format )'  }, 
 {  'DATE_SUB':             'DATE_SUB ( date, INTERVAL expr unit )'  }, 
 {  'DAY':                  'DAY ( date )'  }, 
 {  'DAYNAME':              'DAYNAME ( date )'  }, 
 {  'DAYOFMONTH':           'DAYOFMONTH ( date )'  }, 
 {  'DAYOFWEEK':            'DAYOFWEEK ( date )'  }, 
 {  'DAYOFYEAR':            'DAYOFYEAR ( date )'  }, 
 {  'DEGREES':              'DEGREES ( X )'  }, 
 {  'ELT':                  'ELT ( N, str1, str2, str3, ... )'  }, 
 {  'EXPORT_SET':           'EXPORT_SET ( bits, on, off [ , separator [ , number_of_bits ] ] )'  }, 
 {  'EXP':                  'EXP ( X )'  }, 
 {  'EXTRACT':              'EXTRACT ( unit FROM date )'  }, 
 {  'FIELD':                'FIELD ( str, str1, str2, str3, ... )'  }, 
 {  'FIND_IN_SET':          'FIND_IN_SET ( str, strlist )'  }, 
 {  'FLOOR':                'FLOOR ( X )'  }, 
 {  'FORMAT':               'FORMAT ( X, D )'  }, 
 {  'FORMAT':               'FORMAT ( X, D [ , locale ] )'  }, 
 {  'FROM_BASE64':          'FROM_BASE64 ( str )'  }, 
 {  'FROM_DAYS':            'FROM_DAYS ( N )'  }, 
 {  'FROM_UNIXTIME':        'FROM_UNIXTIME ( unix_timestamp [ , format ] )'  }, 
 #{  'GET_FORMAT':           "''GET_FORMAT ( { DATE|TIME|DATETIME  },  { \'EUR\'|\'USA\'|\'JIS\'|\'ISO\'|\'INTERNAL\' } )" }, 
 {  'HEX':                  'HEX ( N_or_S )'  }, 
 {  'HEX':                  'HEX ( { str|N  } )'  }, 
 {  'HOUR':                 'HOUR ( time )'  }, 
 {  'INSERT':               'INSERT ( str, pos, len, newstr )'  }, 
 {  'INSTR':                'INSTR ( str, substr )'  }, 
 {  'LAST_DAY':             'LAST_DAY ( date )'  }, 
 {  'LCASE':                'LCASE ( str )'  }, 
 {  'LEFT':                 'LEFT ( str, len )'  }, 
 {  'LENGTH':               'LENGTH ( str )'  }, 
 {  'LN':                   'LN ( X )'  }, 
 {  'LOAD_FILE':            'LOAD_FILE ( file_name )'  }, 
 {  'LOCALTIME':            'LOCALTIME (  [ fsp ] )'  }, 
 {  'LOCALTIMESTAMP':       'LOCALTIMESTAMP (  [ fsp ] )'  }, 
 {  'LOCATE':               'LOCATE ( substr, str [ , pos ] )'  }, 
 {  'LOG10':                'LOG10 ( X )'  }, 
 {  'LOG2':                 'LOG2 ( X )'  }, 
 {  'LOG':                  'LOG (  [ B ], X )'  }, 
 {  'LOWER':                'LOWER ( str )'  }, 
 {  'LPAD':                 'LPAD ( str, len, padstr )'  }, 
 {  'LTRIM':                'LTRIM ( str )'  }, 
 {  'MAKEDATE':             'MAKEDATE ( year, dayofyear )'  }, 
 {  'MAKE_SET':             'MAKE_SET ( bits, str1, str2, ... )'  }, 
 {  'MAKETIME':             'MAKETIME ( hour, minute, second )'  }, 
 {  'MICROSECOND':          'MICROSECOND ( expr )'  }, 
 {  'MID':                  'MID ( str, pos, len )'  }, 
 {  'MINUTE':               'MINUTE ( time )'  }, 
 {  'MOD':                  'MOD ( N, M )'  }, 
 {  'MONTH':                'MONTH ( date )'  }, 
 {  'MONTHNAME':            'MONTHNAME ( date )'  }, 
 {  'NOW':                  'NOW (  [ fsp ] )'  }, 
 {  'OCTET_LENGTH':         'OCTET_LENGTH ( str )'  }, 
 {  'OCT':                  'OCT ( N )'  }, 
 {  'ORD':                  'ORD ( str )'  }, 
 {  'PERIOD_ADD':           'PERIOD_ADD ( P, N )'  }, 
 {  'PERIOD_DIFF':          'PERIOD_DIFF ( P1, P2 )'  }, 
 {  'PI':                   'PI (  )'  }, 
 {  'POSITION':             'POSITION ( substr IN str )'  }, 
 {  'POWER':                'POWER ( X, Y )'  }, 
 {  'POW':                  'POW ( X, Y )'  }, 
 {  'QUARTER':              'QUARTER ( date )'  }, 
 {  'QUOTE':                'QUOTE ( str )'  }, 
 {  'RADIANS':              'RADIANS ( X )'  }, 
 {  'RAND':                 'RAND (  [ N ] )'  }, 
 {  'REPEAT':               'REPEAT ( str, count )'  }, 
 {  'REPLACE':              'REPLACE ( str, from_str, to_str )'  }, 
 {  'REVERSE':              'REVERSE ( str )'  }, 
 {  'RIGHT':                'RIGHT ( str, len )'  }, 
 {  'ROUND':                'ROUND ( X [ , D ] )'  }, 
 {  'RPAD':                 'RPAD ( str, len, padstr )'  }, 
 {  'RTRIM':                'RTRIM ( str )'  }, 
 {  'SECOND':               'SECOND ( time )'  }, 
 {  'SEC_TO_TIME':          'SEC_TO_TIME ( seconds )'  }, 
 {  'SIGN':                 'SIGN ( X )'  }, 
 {  'SIN':                  'SIN ( X )'  }, 
 {  'SOUNDEX':              'SOUNDEX ( str )'  }, 
 {  'SPACE':                'SPACE ( N )'  }, 
 {  'SQRT':                 'SQRT ( X )'  }, 
 {  'STR_TO_DATE':          'STR_TO_DATE ( str, format )'  }, 
 {  'SUBDATE':              'SUBDATE ( date, INTERVAL expr unit )'  }, 
 {  'SUBDATE':              'SUBDATE ( expr, days )'  }, 
 {  'SUBSTRING_INDEX':      'SUBSTRING_INDEX ( str, delim, count )'  }, 
 {  'SUBSTRING':            'SUBSTRING ( str, pos )'  }, 
 {  'SUBSTRING':            'SUBSTRING ( str FROM pos )'  }, 
 {  'SUBSTRING':            'SUBSTRING ( str, pos, len )'  }, 
 {  'SUBSTR':               'SUBSTR ( str, pos )'  }, 
 {  'SUBSTR':               'SUBSTR ( str FROM pos )'  }, 
 {  'SUBSTR':               'SUBSTR ( str, pos, len )'  }, 
 {  'SUBTIME':              'SUBTIME ( expr1, expr2 )'  }, 
 {  'SYSDATE':              'SYSDATE (  [ fsp ] )'  }, 
 {  'TAN':                  'TAN ( X )'  }, 
 {  'TIMEDIFF':             'TIMEDIFF ( expr1, expr2 )'  }, 
 {  'TIME':                 'TIME ( expr )'  }, 
 {  'TIME_FORMAT':          'TIME_FORMAT ( time, format )'  }, 
 {  'TIMESTAMPADD':         'TIMESTAMPADD ( unit, interval, datetime_expr )'  }, 
 {  'TIMESTAMPDIFF':        'TIMESTAMPDIFF ( unit, datetime_expr1, datetime_expr2 )'  }, 
 {  'TIMESTAMP':            'TIMESTAMP ( expr1 [ , expr2 ] )'  }, 
 {  'TIME_TO_SEC':          'TIME_TO_SEC ( time )'  }, 
 {  'TO_BASE64':            'TO_BASE64 ( str )'  }, 
 {  'TO_DAYS':              'TO_DAYS ( date )'  }, 
 {  'TO_SECONDS':           'TO_SECONDS ( expr )'  }, 
 {  'TRIM':                 'TRIM (  [ { BOTH | LEADING | TRAILING  }  [ remstr ] FROM ] str )'  }, 
 {  'TRUNCATE':             'TRUNCATE ( X, D )'  }, 
 {  'UCASE':                'UCASE ( str )'  }, 
 {  'UNHEX':                'UNHEX ( str )'  }, 
 {  'UNIX_TIMESTAMP':       'UNIX_TIMESTAMP ( [ date ] )'  }, 
 {  'UTC_DATE':             'UTC_DATE (  )'  }, 
 {  'UTC_TIMESTAMP':        'UTC_TIMESTAMP ( [ fsp ] )'  }, 
 {  'UTC_TIME':             'UTC_TIME ( [ fsp ] )'  }, 
 {  'WEEK':                 'WEEK ( date [ , mode ] )'  }, 
 {  'WEEKDAY':              'WEEKDAY ( date )'  }, 
 {  'WEEKOFYEAR':           'WEEKOFYEAR ( date )'  }, 
 {  'YEAR':                 'YEAR ( date )'  }, 
 {  'YEARWEEK':             'YEARWEEK ( date )'  }, 
 {  'YEARWEEK':             'YEARWEEK ( date, mode )'  }, 

 {  'alpha'               :  'A-Z | a-z' },
 {  'string'              :  '\'[*]\'|"[*]"' },
 {  'sign'                :  "- | + " },
 {  'unsigned_integer'    :  '[0-9]+' },
 {  'signed_integer'      :  'sign integer' },
 {  'integer'             :  'unsigned_int | signed_int ' },
 {  'number'              :  'int | { int . unsigned_int } |  { . unsigned_int }  [E int]' },
 {  'number'              :  'int | { int { . | unsigned_int | [ r ] } unsigned_int } |  { . unsigned_int }  [E int]' },
 # date 
 #fsp
 #str
 #remstr
 #expr
 #time
 #format
 #expr1
 #expr2
 #pos
 #len
 #days
 #unit
 #seconds
 #bits
 #str1
 #str2
 #charset_name
 #separator
 #dt, from_tz, to_tz
 #N, from_base, to_base
 #bits, on, off, separator, number_of_bits
 #locale
 #N_or_S
 #N
 #X
 #D
 #interval, datetime_expr
 #datetime_expr1
 #datetime_expr2
 #delim
 # count
]
# template out the matching

print("""
PAREN_LEFT=1
PAREN_RIGHT=2
""")


def clean_pattern(pattern):
    pattern=pattern.replace("|"," | ")
    pattern=pattern.replace("]"," ] ")
    pattern=pattern.replace("["," [ ")
    pattern=pattern.replace(","," , ")
    pattern=pattern.replace("  "," ")
    return pattern


def function_header(name,depth,pattern):
    if depth==0:
        o="""
/*
 * Function: match_{0}
 * -----------------------------
 *   Generated: {1}
 *      tokens: a pointer to the curent element in a linked list of tokens to search
 * 
 *     Success: Returns a the token AFTER the curent pattern match
 *              If the end of the list is reached the last token is passed
 *     Failure: Returns NULL
 */
token_t * match_{0}(token_t * tokens){{
    //{0}
    token_t * token=tokens;                //make a copy of the pointer
""".format(name,datetime.datetime.now().strftime("%Y-%m-%d"))
        print o


def get_padd(depth,spacer):
    padd=''
    for i in range(0,depth):
       padd=padd+spacer
    padd+="    "
    return padd

uid_int=1
    
def uid():
    global uid_int
    uid_int+=1
    return uid_int;


def build(name,pattern,depth=0):
    spacer="   "
    pattern=clean_pattern(pattern)
    function_header(name,depth,pattern)
    padd=get_padd(depth,spacer)
    
        
    tokens=pattern.split(" ")
    optional=None
    in_or=None
    index=0

    token=None
    last_token=None
    token_or="????"
    while 1:
        if index>=len(tokens):
            break
        last_token=token
        token=tokens[index]
        if token=='':
            index+=1
            continue;

        optional_depth=0
        group_depth=0
        in_chain=0
        distance=0
        # {  'number'              :  'int | { int { . | unsigned_int | [ r ] } unsigned_int } |  { . unsigned_int }  [E int]' },
        #print "-"+token
        if token!='|':
            for pre_index in range(0,len(tokens)):
                if tokens[pre_index]=='{':   group_depth+=1
                if tokens[pre_index]=='}':   group_depth-=1
                if tokens[pre_index]=='[':   optional_depth+=1
                if tokens[pre_index]==']':   optional_depth-=1

                if group_depth==0 and optional_depth==0:
                    if tokens[pre_index]=='|' and distance==1:
                        if in_chain==0:
                            in_chain=1
                            token_or="token_or_{0}".format(uid())
                            print padd+"token_t * {0}=token".format(token_or)
                        #   print index,pre_index
                        
                        #if index==pre_index:  print padd+"token_t * {0}=token;".format(token_or)
                    distance+=1;
                    if distance>1:
                        #print "NOT IN CHAIN"
                        in_chain=0
                
                    


        #next_token=tokens[index+1]
        
        if len(token)==0:
            index+=1
            continue
        if token==')':
            token="RIGHT_PAREN"
        if token=='(':
            token="LEFT_PAREN"
        if token=='{': 
            md=0
            for index2 in range(index,len(tokens)):
                if tokens[index2]=='{':
                    md+=1
                if tokens[index2]=='}':
                    md-=1
                if md==0:
                    sub_pattern=" ".join(tokens[index+1:index2])
                    #build(name,sub_pattern,depth+1)
                    index=index2
                    break
            continue

        if in_or:
            print padd+"}}//end OR  ".format(token)
            in_or=None
            index+=1
            continue

        if token[0]=='|':
            print "\n"
            print padd+"if ( token == NULL ) {{        ".format(token)
            print padd+spacer+"token={0}".format(token_or)
            in_or=True
            index+=1
            continue

        if token[0]=='[':
            uid_str=uid()
            print "\n"
            print padd+"// "+pattern
            print padd+"if ( token != NULL ) {{         //Match must be successfull to proceed".format(token)
            print padd+spacer+"token_t *optional_token_{0}=token;".format(uid_str)
            md=0
            for index2 in range(index,len(tokens)):
                if tokens[index2]=='[':
                    md+=1
                if tokens[index2]==']':
                    md-=1  
                if md==0:
                    sub_pattern=" ".join(tokens[index+1:index2])
                    #:"build(name,sub_pattern,depth+1)
                    index=index2+1
                    break
            
            print padd+spacer+"if ( token == NULL ) token = optional_token_{0};".format(uid_str)
            print padd+"}}//END Optional".format(token)
            continue            
            
        
        #if optional
        if token[0]>='A' and token[0]<='Z':
            print padd+"if ( token.cmp('{0}') != NULL ) token=next_token(token);        //data match".format(token)
        else:
            print padd+"if ( token != NULL ) token = match_{0}(token);".format(token)
             
        

        index+=1
    
    if depth==0:
        print "\n"
        print spacer+"return token;".format(name)
        print "}}//end match_{0}".format(name)

for function in functions:
    for key in function:
        build(key,function[key])




