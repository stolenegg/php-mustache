
#include "mustache_private.hpp"

/* {{{ ZE2 OO definitions */
zend_class_entry * MustacheTemplate_ce_ptr;
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(MustacheTemplate____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
    ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(MustacheTemplate____toString_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ MustacheTemplate_methods */
static zend_function_entry MustacheTemplate_methods[] = {
    PHP_ME(MustacheTemplate, __construct, MustacheTemplate____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(MustacheTemplate, __toString, MustacheTemplate____toString_args, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(mustache_template)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "MustacheTemplate", MustacheTemplate_methods);
    MustacheTemplate_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
    
    zend_declare_property_null(MustacheTemplate_ce_ptr, "template", sizeof("template") - 1, ZEND_ACC_PROTECTED TSRMLS_CC);
    
    return SUCCESS;
}
/* }}} */

/* {{{ proto void MustacheTemplate::__construct(string tmpl) */
PHP_METHOD(MustacheTemplate, __construct)
{
    zval * _this_zval;
    char * template_str = NULL;
    strsize_t template_len = 0;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), (char *) "O|s",
                                     &_this_zval, MustacheTemplate_ce_ptr, &template_str, &template_len) == FAILURE) {
        return;
    }

    if( template_len > 0 && template_str != NULL ) {
        zend_update_property_stringl(Z_OBJCE_P(_this_zval), _this_zval,
                                     ZEND_STRL("template"), template_str, template_len TSRMLS_CC);
    }
}
/* }}} MustacheTemplate::__construct */

/* {{{ proto string MustacheTemplate::__toString() */
PHP_METHOD(MustacheTemplate, __toString)
{
    zval * _this_zval;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O",
                                     &_this_zval, MustacheTemplate_ce_ptr) == FAILURE ) {
        return;
    }

    zval * value = php5to7_zend_read_property(Z_OBJCE_P(_this_zval), _this_zval, ZEND_STRL("template"), 1);
    convert_to_string(value);
    RETURN_ZVAL(value, 1, 0);
}
/* }}} MustacheTemplate::__toString */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
