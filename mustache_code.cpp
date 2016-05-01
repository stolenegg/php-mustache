
#include "mustache_private.hpp"

/* {{{ ZE2 OO definitions */
zend_class_entry * MustacheCode_ce_ptr;
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(MustacheCode____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
    ZEND_ARG_INFO(0, codeString)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(MustacheCode__toReadableString_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(MustacheCode____toString_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ MustacheCode_methods */
static zend_function_entry MustacheCode_methods[] = {
    PHP_ME(MustacheCode, __construct, MustacheCode____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(MustacheCode, toReadableString, MustacheCode__toReadableString_args, ZEND_ACC_PUBLIC)
    PHP_ME(MustacheCode, __toString, MustacheCode____toString_args, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(mustache_code)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "MustacheCode", MustacheCode_methods);
    MustacheCode_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
    
    zend_declare_property_null(MustacheCode_ce_ptr, ZEND_STRL("binaryString"), ZEND_ACC_PROTECTED TSRMLS_CC);
    
    return SUCCESS;
}
/* }}} */

/* {{{ proto void MustacheCode::__construct(string binaryString) */
PHP_METHOD(MustacheCode, __construct)
{
    char * str = NULL;
    strsize_t str_len = 0;
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|s",
                                     &_this_zval, MustacheCode_ce_ptr, &str, &str_len) == FAILURE) {
        return;
    }

    // Check if data was null
    if( str != NULL ) {
        zend_update_property_stringl(MustacheCode_ce_ptr, _this_zval,
                                     "binaryString", sizeof("binaryString") - 1, str, str_len TSRMLS_CC);
    }
}
/* }}} MustacheCode::__construct */

/* {{{ proto string MustacheCode::toReadableString() */
PHP_METHOD(MustacheCode, toReadableString)
{
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O",
                                     &_this_zval, MustacheCode_ce_ptr) == FAILURE) {
        return;
    }

    zval * value = php5to7_zend_read_property(Z_OBJCE_P(_this_zval), _this_zval, ZEND_STRL("binaryString"), 1);
    if( !value || Z_TYPE_P(value) != IS_STRING ) {
        RETURN_FALSE;
    }

    try {
        uint8_t * tmp = (uint8_t *) Z_STRVAL_P(value);
        size_t tmp_len = Z_STRLEN_P(value) * sizeof(uint8_t) / sizeof(char);

        // Print codes
        std::string * output = mustache::Compiler::print(tmp, tmp_len);

        // Copy
        if( output != NULL ) {
            PHP5TO7_RETVAL_STRINGL((char *) output->c_str(), output->length());
            delete output;
        }
    
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} MustacheCode::toReadableString */

/* {{{ proto string MustacheCode::__toString() */
PHP_METHOD(MustacheCode, __toString)
{
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), (char *) "O",
                                     &_this_zval, MustacheCode_ce_ptr) == FAILURE) {
        return;
    }

    zval * value = php5to7_zend_read_property(Z_OBJCE_P(_this_zval), _this_zval, ZEND_STRL("binaryString"), 1);
    if( value != NULL ) {
        convert_to_string(value);
        RETURN_ZVAL(value, 1, 0);
    }
}
/* }}} MustacheCode::__toString */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
