func="""ABS:                    ( X )
ACOS:                  ( X )
ADDDATE:               ( date , INTERVAL interval_expr )
ADDTIME:               ( expr1 , expr2 )
ASCII:                 ( str )
ASIN:                  ( X )
ATAN:                  ( X )
ATAN2:                 ( Y , X )
BIN:                   ( N )
BIT_LENGTH:            ( str )
CEILING:               ( X )
CEIL:                  ( X )
CHARACTER_LENGTH:      ( str )
CHAR_LENGTH:           ( str )
CHAR:                  ( N , N ...  [ USING charset_name ] )
CONCAT:                ( str , str  ... )
CONCAT_WS:             ( separator , str  ... )
CONVERT_TZ:            ( dt , from_tz , to_tz )
CONV:                  ( N , from_base , to_base )
COS:                   ( X )
COT:                   ( X )
CRC32:                 ( expr )
CURDATE:               (  )
CURRENT_DATE:          (  )
CURRENT_TIME:          (  [ fsp ] )
CURRENT_TIMESTAMP:     (  [ fsp ] )
CURTIME:               (  [ fsp ] )
DATE_ADD:              ( date , INTERVAL interval_expr )
DATEDIFF:              ( expr1 , expr2 )
DATE:                  ( expr )
DATE_FORMAT:           ( date , format )
DATE_SUB:              ( date , INTERVAL interval_expr )
DAY:                   ( date )
DAYNAME:               ( date )
DAYOFMONTH:            ( date )
DAYOFWEEK:             ( date )
DAYOFYEAR:             ( date )
DEGREES:               ( X )
ELT:                   ( N , str  ... )
EXPORT_SET:            ( bits , on , off [  , separator [  , number_of_bits ] ] )
EXP:                   ( X )
EXTRACT:               ( unit FROM date )
FIELD:                 ( str , str  ... )
FIND_IN_SET:           ( str , strlist )
FLOOR:                 ( X )
FORMAT:                ( X , D [  , locale ] )
FROM_BASE64:           ( str )
FROM_DAYS:             ( N )
FROM_UNIXTIME:         ( unix_timestamp [  , format ] )
GET_FORMAT:            ( [ DATE | TIME | DATETIME ] ,  [  EUR | USA | JIS | ISO | INTERNAL ] )
HEX:                   ( str|N   )
HOUR:                  ( time )
INSERT:                ( str , pos , len , newstr )
INSTR:                 ( str , substr )
LAST_DAY:              ( date )
LCASE:                 ( str )
LEFT:                  ( str , len )
LENGTH:                ( str )
LN:                    ( X )
LOAD_FILE:             ( file_name )
LOCALTIME:             ( [ fsp ] )
LOCALTIMESTAMP:        ( [ fsp ] )
LOCATE:                ( substr , str [  , pos ] )
LOG10:                 ( X )
LOG2:                  ( X )
LOG:                   ( [ B ] , X )
LOWER:                 ( str )
LPAD:                  ( str , len , padstr )
LTRIM:                 ( str )
MAKEDATE:              ( year , dayofyear )
MAKE_SET:              ( bits , str  ... )
MAKETIME:              ( hour , minute , second )
MICROSECOND:           ( expr )
MID:                   ( str , pos , len )
MINUTE:                ( time )
MOD:                   ( N , M )
MONTH:                 ( date )
MONTHNAME:             ( date )
NOW:                   (  [ fsp ] )
OCTET_LENGTH:          ( str )
OCT:                   ( N )
ORD:                   ( str )
PERIOD_ADD:            ( P , N )
PERIOD_DIFF:           ( P1 , P2 )
PI:                    (  )
POSITION:              ( substr IN str )
POWER:                 ( X , Y )
POW:                   ( X , Y )
QUARTER:               ( date )
QUOTE:                 ( str )
RADIANS:               ( X )
RAND:                  (  [ N ] )
REPEAT:                ( str , count )
REPLACE:               ( str , from_str , to_str )
REVERSE:               ( str )
RIGHT:                 ( str , len )
ROUND:                 ( X [  , D ] )
RPAD:                  ( str , len , padstr )
RTRIM:                 ( str )
SECOND:                ( time )
SEC_TO_TIME:           ( seconds )
SIGN:                  ( X )
SIN:                   ( X )
SOUNDEX:               ( str )
SPACE:                 ( N )
SQRT:                  ( X )
STR_TO_DATE:           ( str , format )
SUBDATE:               ( { date , INTERVAL interval_expr } | { expr , days } )
SUBSTRING_INDEX:       ( str , delim , count )
SUBSTRING:             ( { str , pos } | { str FROM pos } | { str , pos , len } )
SUBSTR:                ( { str , pos } | { str FROM pos } | { str , pos , len } )
SUBTIME:               ( expr1 , expr2 )
SYSDATE:               ( [ fsp ] )
TAN:                   ( X )
TIMEDIFF:              ( expr1 , expr2 )
TIME:                  ( expr )
TIME_FORMAT:           ( time , format )
TIMESTAMPADD:          ( unit , interval , datetime_expr )
TIMESTAMPDIFF:         ( unit , datetime_expr , datetime_expr )
TIMESTAMP:             ( expr1 [  , expr2 ] )
TIME_TO_SEC:           ( time      )
TO_BASE64:             ( str       )
TO_DAYS:               ( date      )
TO_SECONDS:            ( expr      )
TRIM:                  (  [ [ BOTH | LEADING | TRAILING  ]   remstr?  FROM ] str )
TRUNCATE:              ( X [, D ] )
UCASE:                 ( str )
UNHEX:                 ( str )
UNIX_TIMESTAMP:        (  date?  )
UTC_DATE:              (  )
UTC_TIMESTAMP:         ( [fsp]  )
UTC_TIME:              ( [fsp]  )
WEEK:                  ( date [  , mode ] )
WEEKDAY:               ( date )
WEEKOFYEAR:            ( date )
YEAR:                  ( date )
YEARWEEK:              ( date [ , mode ] )"""
lines=func.split("\n")
index=0
delimiters="[](),|{}"
for line in lines:
    try:
        name,args=line.split(":")
        for delimiter in delimiters:
            args=args.replace(delimiter," "+delimiter+" ")
        args=args.replace("  "," ")
        args=args.replace("  "," ")
        tokens=args.split(" ")
        new_args=""
        for token in tokens:
            
            if len(token)==0:
                continue
            elif token=='...':
                f_index=new_args.rfind(",")

                arg_part=new_args[f_index:]
                new_args=new_args[:f_index-1]
                new_args+=" ( "+arg_part+" )* "
                #new_args +="???"+arg_part+str(f_index)+"---"
            elif token=='|':
                new_args+=" | "
            elif token=='[':
                new_args+=" ( "
            elif token==']':
                new_args+=" ) ? "
            elif token=='{':
                new_args+=" ( "
            elif token=='}':
                new_args+=" ) "
            elif token=='(':
                new_args+=" [\(] "
            elif token==')':
                new_args+=" [\)] "
            elif token==',':
                new_args+=" , "
            elif token=='N':
                new_args+="{N}"
            elif token=='D':
                new_args+="{D}"
            elif token=='B':
                new_args+="{B}"
            elif token=='X':
                new_args+="{X}"
            elif token=='str':
                new_args+="{string}"
            elif token=='str1':
                new_args+="{string}"
            elif token=='str2':
                new_args+="{string}"
            elif token=='str3':
                new_args+="{string}"
            elif token=='expr':
                new_args+="{expr}"
            elif token=='expr1':
                new_args+="{expr}"
            elif token=='expr2':
                new_args+="{expr}"
            elif token=='expr3':
                new_args+="{expr}"
            elif token=='date':
                new_args+="{date}"
            
            elif token[0]>='A' and token[0]<='Z':
                new_args+=" "+token+" "
            else:
                new_args+=" {"+token+"} "

        print ("{0:20} {1} {2}".format(name+"_FUNC:",name,new_args) )
    except Exception as ex:
        print ex
        pass
    index+=1
