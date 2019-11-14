// this holds the string you are tokenizing
typedef struct node_t {
  int len;
  int pos;
  int OK;
  int depth;
  int token_index;
  char *function;
  char *last_function;
  char *value;
  struct stack_t *token_stack;
  struct stack_t *stack;
  struct token_t *tokens;
} node_t;
void match_queries(node_t * n, char *last_method, int depth);
void match_select(node_t * n, char *last_method, int depth);
void match_select_expr(node_t * n, char *last_method, int depth);
void match_select_expr_list(node_t * n, char *last_method, int depth);
void match_subquery(node_t * n, char *last_method, int depth);
void match_expr(node_t * n, char *last_method, int depth);
void match_boolean_primary(node_t * n, char *last_method, int depth);
void match_predicate(node_t * n, char *last_method, int depth);
void match_bit_expr(node_t * n, char *last_method, int depth);
void match_operations(node_t * n, char *last_method, int depth);
void match_identifier_expr(node_t * n, char *last_method, int depth);
void match_simple_expr(node_t * n, char *last_method, int depth);
void match_literal(node_t * n, char *last_method, int depth);
void match_interval_expr(node_t * n, char *last_method, int depth);
void match_YEARS(node_t * n, char *last_method, int depth);
void match_QUARTERS(node_t * n, char *last_method, int depth);
void match_MONTHS(node_t * n, char *last_method, int depth);
void match_WEEKS(node_t * n, char *last_method, int depth);
void match_DAYS(node_t * n, char *last_method, int depth);
void match_HOURS(node_t * n, char *last_method, int depth);
void match_MINUTES(node_t * n, char *last_method, int depth);
void match_SECONDS(node_t * n, char *last_method, int depth);
void match_MICROSECONDS(node_t * n, char *last_method, int depth);
void match_MICROSECOND(node_t * n, char *last_method, int depth);
void match_SECOND(node_t * n, char *last_method, int depth);
void match_MINUTE(node_t * n, char *last_method, int depth);
void match_HOUR(node_t * n, char *last_method, int depth);
void match_DAY(node_t * n, char *last_method, int depth);
void match_WEEK(node_t * n, char *last_method, int depth);
void match_MONTH(node_t * n, char *last_method, int depth);
void match_QUARTER(node_t * n, char *last_method, int depth);
void match_YEAR(node_t * n, char *last_method, int depth);
void match_SECOND_MICROSECOND(node_t * n, char *last_method, int depth);
void match_MINUTE_MICROSECOND(node_t * n, char *last_method, int depth);
void match_MINUTE_SECOND(node_t * n, char *last_method, int depth);
void match_HOUR_MICROSECOND(node_t * n, char *last_method, int depth);
void match_HOUR_SECOND(node_t * n, char *last_method, int depth);
void match_HOUR_MINUTE(node_t * n, char *last_method, int depth);
void match_DAY_MICROSECOND(node_t * n, char *last_method, int depth);
void match_DAY_SECOND(node_t * n, char *last_method, int depth);
void match_DAY_MINUTE(node_t * n, char *last_method, int depth);
void match_DAY_HOUR(node_t * n, char *last_method, int depth);
void match_YEAR_MONTH(node_t * n, char *last_method, int depth);
void match_unknown(node_t * n, char *last_method, int depth);
void match_hex(node_t * n, char *last_method, int depth);
void match_bit(node_t * n, char *last_method, int depth);
void match_null(node_t * n, char *last_method, int depth);
void match_true(node_t * n, char *last_method, int depth);
void match_false(node_t * n, char *last_method, int depth);
void match_boolean(node_t * n, char *last_method, int depth);
void match_real(node_t * n, char *last_method, int depth);
void match_integer(node_t * n, char *last_method, int depth);
void match_signed_int(node_t * n, char *last_method, int depth);
void match_unsigned_int(node_t * n, char *last_method, int depth);
void match_sign(node_t * n, char *last_method, int depth);
void match_exponent(node_t * n, char *last_method, int depth);
void match_identifier(node_t * n, char *last_method, int depth);
void match_keywords(node_t * n, char *last_method, int depth);
void match_whitespace(node_t * n, char *last_method, int depth);
void match_string(node_t * n, char *last_method, int depth);
void match_single_quote_string(node_t * n, char *last_method, int depth);
void match_double_quote_string(node_t * n, char *last_method, int depth);
void match_query_delimiter(node_t * n, char *last_method, int depth);
void match_comparison_operator(node_t * n, char *last_method, int depth);
void match_comment(node_t * n, char *last_method, int depth);
void match_block_comment(node_t * n, char *last_method, int depth);
void match_single_comment(node_t * n, char *last_method, int depth);
void match_left_comment(node_t * n, char *last_method, int depth);
void match_right_comment(node_t * n, char *last_method, int depth);
void match_inline_comment(node_t * n, char *last_method, int depth);
void match_end_of_line(node_t * n, char *last_method, int depth);
void match_ABS_FUNC(node_t * n, char *last_method, int depth);
void match_ACOS_FUNC(node_t * n, char *last_method, int depth);
void match_ADDDATE_FUNC(node_t * n, char *last_method, int depth);
void match_ADDTIME_FUNC(node_t * n, char *last_method, int depth);
void match_ASCII_FUNC(node_t * n, char *last_method, int depth);
void match_ASIN_FUNC(node_t * n, char *last_method, int depth);
void match_ATAN_FUNC(node_t * n, char *last_method, int depth);
void match_ATAN2_FUNC(node_t * n, char *last_method, int depth);
void match_BIN_FUNC(node_t * n, char *last_method, int depth);
void match_BIT_LENGTH_FUNC(node_t * n, char *last_method, int depth);
void match_CEILING_FUNC(node_t * n, char *last_method, int depth);
void match_CEIL_FUNC(node_t * n, char *last_method, int depth);
void match_CHARACTER_LENGTH_FUNC(node_t * n, char *last_method, int depth);
void match_CHAR_LENGTH_FUNC(node_t * n, char *last_method, int depth);
void match_CHAR_FUNC(node_t * n, char *last_method, int depth);
void match_CONCAT_FUNC(node_t * n, char *last_method, int depth);
void match_CONCAT_WS_FUNC(node_t * n, char *last_method, int depth);
void match_CONVERT_TZ_FUNC(node_t * n, char *last_method, int depth);
void match_CONV_FUNC(node_t * n, char *last_method, int depth);
void match_COS_FUNC(node_t * n, char *last_method, int depth);
void match_COT_FUNC(node_t * n, char *last_method, int depth);
void match_CRC32_FUNC(node_t * n, char *last_method, int depth);
void match_CURDATE_FUNC(node_t * n, char *last_method, int depth);
void match_CURRENT_DATE_FUNC(node_t * n, char *last_method, int depth);
void match_CURRENT_TIME_FUNC(node_t * n, char *last_method, int depth);
void match_CURRENT_TIMESTAMP_FUNC(node_t * n, char *last_method, int depth);
void match_CURTIME_FUNC(node_t * n, char *last_method, int depth);
void match_DATE_ADD_FUNC(node_t * n, char *last_method, int depth);
void match_DATEDIFF_FUNC(node_t * n, char *last_method, int depth);
void match_DATE_FUNC(node_t * n, char *last_method, int depth);
void match_DATE_FORMAT_FUNC(node_t * n, char *last_method, int depth);
void match_DATE_SUB_FUNC(node_t * n, char *last_method, int depth);
void match_DAY_FUNC(node_t * n, char *last_method, int depth);
void match_DAYNAME_FUNC(node_t * n, char *last_method, int depth);
void match_DAYOFMONTH_FUNC(node_t * n, char *last_method, int depth);
void match_DAYOFWEEK_FUNC(node_t * n, char *last_method, int depth);
void match_DAYOFYEAR_FUNC(node_t * n, char *last_method, int depth);
void match_DEGREES_FUNC(node_t * n, char *last_method, int depth);
void match_ELT_FUNC(node_t * n, char *last_method, int depth);
void match_EXPORT_SET_FUNC(node_t * n, char *last_method, int depth);
void match_EXP_FUNC(node_t * n, char *last_method, int depth);
void match_EXTRACT_FUNC(node_t * n, char *last_method, int depth);
void match_FIELD_FUNC(node_t * n, char *last_method, int depth);
void match_FIND_IN_SET_FUNC(node_t * n, char *last_method, int depth);
void match_FLOOR_FUNC(node_t * n, char *last_method, int depth);
void match_FORMAT_FUNC(node_t * n, char *last_method, int depth);
void match_FROM_BASE64_FUNC(node_t * n, char *last_method, int depth);
void match_FROM_DAYS_FUNC(node_t * n, char *last_method, int depth);
void match_FROM_UNIXTIME_FUNC(node_t * n, char *last_method, int depth);
void match_GET_FORMAT_FUNC(node_t * n, char *last_method, int depth);
void match_HEX_FUNC(node_t * n, char *last_method, int depth);
void match_HOUR_FUNC(node_t * n, char *last_method, int depth);
void match_INSERT_FUNC(node_t * n, char *last_method, int depth);
void match_INSTR_FUNC(node_t * n, char *last_method, int depth);
void match_LAST_DAY_FUNC(node_t * n, char *last_method, int depth);
void match_LCASE_FUNC(node_t * n, char *last_method, int depth);
void match_LEFT_FUNC(node_t * n, char *last_method, int depth);
void match_LENGTH_FUNC(node_t * n, char *last_method, int depth);
void match_LN_FUNC(node_t * n, char *last_method, int depth);
void match_LOAD_FILE_FUNC(node_t * n, char *last_method, int depth);
void match_LOCALTIME_FUNC(node_t * n, char *last_method, int depth);
void match_LOCALTIMESTAMP_FUNC(node_t * n, char *last_method, int depth);
void match_LOCATE_FUNC(node_t * n, char *last_method, int depth);
void match_LOG10_FUNC(node_t * n, char *last_method, int depth);
void match_LOG2_FUNC(node_t * n, char *last_method, int depth);
void match_LOG_FUNC(node_t * n, char *last_method, int depth);
void match_LOWER_FUNC(node_t * n, char *last_method, int depth);
void match_LPAD_FUNC(node_t * n, char *last_method, int depth);
void match_LTRIM_FUNC(node_t * n, char *last_method, int depth);
void match_MAKEDATE_FUNC(node_t * n, char *last_method, int depth);
void match_MAKE_SET_FUNC(node_t * n, char *last_method, int depth);
void match_MAKETIME_FUNC(node_t * n, char *last_method, int depth);
void match_MICROSECOND_FUNC(node_t * n, char *last_method, int depth);
void match_MID_FUNC(node_t * n, char *last_method, int depth);
void match_MINUTE_FUNC(node_t * n, char *last_method, int depth);
void match_MOD_FUNC(node_t * n, char *last_method, int depth);
void match_MONTH_FUNC(node_t * n, char *last_method, int depth);
void match_MONTHNAME_FUNC(node_t * n, char *last_method, int depth);
void match_NOW_FUNC(node_t * n, char *last_method, int depth);
void match_OCTET_LENGTH_FUNC(node_t * n, char *last_method, int depth);
void match_OCT_FUNC(node_t * n, char *last_method, int depth);
void match_ORD_FUNC(node_t * n, char *last_method, int depth);
void match_PERIOD_ADD_FUNC(node_t * n, char *last_method, int depth);
void match_PERIOD_DIFF_FUNC(node_t * n, char *last_method, int depth);
void match_PI_FUNC(node_t * n, char *last_method, int depth);
void match_POSITION_FUNC(node_t * n, char *last_method, int depth);
void match_POWER_FUNC(node_t * n, char *last_method, int depth);
void match_POW_FUNC(node_t * n, char *last_method, int depth);
void match_QUARTER_FUNC(node_t * n, char *last_method, int depth);
void match_QUOTE_FUNC(node_t * n, char *last_method, int depth);
void match_RADIANS_FUNC(node_t * n, char *last_method, int depth);
void match_RAND_FUNC(node_t * n, char *last_method, int depth);
void match_REPEAT_FUNC(node_t * n, char *last_method, int depth);
void match_REPLACE_FUNC(node_t * n, char *last_method, int depth);
void match_REVERSE_FUNC(node_t * n, char *last_method, int depth);
void match_RIGHT_FUNC(node_t * n, char *last_method, int depth);
void match_ROUND_FUNC(node_t * n, char *last_method, int depth);
void match_RPAD_FUNC(node_t * n, char *last_method, int depth);
void match_RTRIM_FUNC(node_t * n, char *last_method, int depth);
void match_SECOND_FUNC(node_t * n, char *last_method, int depth);
void match_SEC_TO_TIME_FUNC(node_t * n, char *last_method, int depth);
void match_SIGN_FUNC(node_t * n, char *last_method, int depth);
void match_SIN_FUNC(node_t * n, char *last_method, int depth);
void match_SOUNDEX_FUNC(node_t * n, char *last_method, int depth);
void match_SPACE_FUNC(node_t * n, char *last_method, int depth);
void match_SQRT_FUNC(node_t * n, char *last_method, int depth);
void match_STR_TO_DATE_FUNC(node_t * n, char *last_method, int depth);
void match_SUBDATE_FUNC(node_t * n, char *last_method, int depth);
void match_SUBSTRING_INDEX_FUNC(node_t * n, char *last_method, int depth);
void match_SUBSTRING_FUNC(node_t * n, char *last_method, int depth);
void match_SUBSTR_FUNC(node_t * n, char *last_method, int depth);
void match_SUBTIME_FUNC(node_t * n, char *last_method, int depth);
void match_SYSDATE_FUNC(node_t * n, char *last_method, int depth);
void match_TAN_FUNC(node_t * n, char *last_method, int depth);
void match_TIMEDIFF_FUNC(node_t * n, char *last_method, int depth);
void match_TIME_FUNC(node_t * n, char *last_method, int depth);
void match_TIME_FORMAT_FUNC(node_t * n, char *last_method, int depth);
void match_TIMESTAMPADD_FUNC(node_t * n, char *last_method, int depth);
void match_TIMESTAMPDIFF_FUNC(node_t * n, char *last_method, int depth);
void match_TIMESTAMP_FUNC(node_t * n, char *last_method, int depth);
void match_TIME_TO_SEC_FUNC(node_t * n, char *last_method, int depth);
void match_TO_BASE64_FUNC(node_t * n, char *last_method, int depth);
void match_TO_DAYS_FUNC(node_t * n, char *last_method, int depth);
void match_TO_SECONDS_FUNC(node_t * n, char *last_method, int depth);
void match_TRIM_FUNC(node_t * n, char *last_method, int depth);
void match_TRUNCATE_FUNC(node_t * n, char *last_method, int depth);
void match_UCASE_FUNC(node_t * n, char *last_method, int depth);
void match_UNHEX_FUNC(node_t * n, char *last_method, int depth);
void match_UNIX_TIMESTAMP_FUNC(node_t * n, char *last_method, int depth);
void match_UTC_DATE_FUNC(node_t * n, char *last_method, int depth);
void match_UTC_TIMESTAMP_FUNC(node_t * n, char *last_method, int depth);
void match_UTC_TIME_FUNC(node_t * n, char *last_method, int depth);
void match_WEEK_FUNC(node_t * n, char *last_method, int depth);
void match_WEEKDAY_FUNC(node_t * n, char *last_method, int depth);
void match_WEEKOFYEAR_FUNC(node_t * n, char *last_method, int depth);
void match_YEAR_FUNC(node_t * n, char *last_method, int depth);
void match_YEARWEEK_FUNC(node_t * n, char *last_method, int depth);
void match_functions(node_t * n, char *last_method, int depth);
void match_B(node_t * n, char *last_method, int depth);
void match_bits(node_t * n, char *last_method, int depth);
void match_charset_name(node_t * n, char *last_method, int depth);
void match_count(node_t * n, char *last_method, int depth);
void match_D(node_t * n, char *last_method, int depth);
void match_date(node_t * n, char *last_method, int depth);
void match_datetime_expr(node_t * n, char *last_method, int depth);
void match_dayofyear(node_t * n, char *last_method, int depth);
void match_days(node_t * n, char *last_method, int depth);
void match_delim(node_t * n, char *last_method, int depth);
void match_dt(node_t * n, char *last_method, int depth);
void match_file_name(node_t * n, char *last_method, int depth);
void match_format(node_t * n, char *last_method, int depth);
void match_from_base(node_t * n, char *last_method, int depth);
void match_from_str(node_t * n, char *last_method, int depth);
void match_from_tz(node_t * n, char *last_method, int depth);
void match_fsp(node_t * n, char *last_method, int depth);
void match_hour(node_t * n, char *last_method, int depth);
void match_interval(node_t * n, char *last_method, int depth);
void match_len(node_t * n, char *last_method, int depth);
void match_locale(node_t * n, char *last_method, int depth);
void match_M(node_t * n, char *last_method, int depth);
void match_minute(node_t * n, char *last_method, int depth);
void match_mode(node_t * n, char *last_method, int depth);
void match_N(node_t * n, char *last_method, int depth);
void match_newstr(node_t * n, char *last_method, int depth);
void match_N_or_S(node_t * n, char *last_method, int depth);
void match_number_of_bits(node_t * n, char *last_method, int depth);
void match_off(node_t * n, char *last_method, int depth);
void match_on(node_t * n, char *last_method, int depth);
void match_P(node_t * n, char *last_method, int depth);
void match_padstr(node_t * n, char *last_method, int depth);
void match_pos(node_t * n, char *last_method, int depth);
void match_remstr(node_t * n, char *last_method, int depth);
void match_second(node_t * n, char *last_method, int depth);
void match_seconds(node_t * n, char *last_method, int depth);
void match_separator(node_t * n, char *last_method, int depth);
void match_strlist(node_t * n, char *last_method, int depth);
void match_substr(node_t * n, char *last_method, int depth);
void match_time(node_t * n, char *last_method, int depth);
void match_to_base(node_t * n, char *last_method, int depth);
void match_to_str(node_t * n, char *last_method, int depth);
void match_to_tz(node_t * n, char *last_method, int depth);
void match_unit(node_t * n, char *last_method, int depth);
void match_unix_timestamp(node_t * n, char *last_method, int depth);
void match_X(node_t * n, char *last_method, int depth);
void match_Y(node_t * n, char *last_method, int depth);
void match_year(node_t * n, char *last_method, int depth);
void match_catch_all(node_t * n, char *last_method, int depth);
node_t *match_function(char *data);
