
#include "mustache_private.hpp"

/* {{{ ZE2 OO definitions */
zend_class_entry * MustacheException_ce_ptr;
zend_class_entry * MustacheParserException_ce_ptr;
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(mustache_exceptions)
{
    zend_class_entry * exception_ce = zend_exception_get_default(TSRMLS_C);
    
    // MustacheException
    zend_class_entry mustache_exception_ce;
    INIT_CLASS_ENTRY(mustache_exception_ce, "MustacheException", NULL);
    MustacheException_ce_ptr = php5to7_register_internal_class_ex(&mustache_exception_ce, exception_ce);
    MustacheException_ce_ptr->create_object = exception_ce->create_object;
    
    // MustacheParserException
    zend_class_entry mustache_parser_exception_ce;
    INIT_CLASS_ENTRY(mustache_parser_exception_ce, "MustacheParserException", NULL);
    MustacheParserException_ce_ptr = php5to7_register_internal_class_ex(&mustache_parser_exception_ce, MustacheException_ce_ptr);
    MustacheParserException_ce_ptr->create_object = MustacheException_ce_ptr->create_object;
    
    return SUCCESS;
}
/* }}} */

/* {{{ mustache_exception_handler */
PHPAPI void mustache_exception_handler(TSRMLS_D)
{
    zval * exception;

    try {
        throw;
    } catch( mustache::TokenizerException& e ) {
#if PHP_API_VERSION < 20131218
        exception = zend_throw_exception_ex(MustacheParserException_ce_ptr,
            0 TSRMLS_CC, (char *) e.what(), "MustacheParserException");
#else
        zval ex;
        zend_object * obj = zend_throw_exception_ex(MustacheParserException_ce_ptr,
                0 TSRMLS_CC, (char *) e.what(), "MustacheParserException");
        ZVAL_OBJ(&ex, obj);
        exception = &ex;
#endif
	
        zend_update_property_long(MustacheParserException_ce_ptr, exception,
                                  ZEND_STRL("templateLineNo"), e.lineNo TSRMLS_CC);
        zend_update_property_long(MustacheParserException_ce_ptr, exception,
                                  ZEND_STRL("templateCharNo"), e.charNo TSRMLS_CC);
    } catch( mustache::Exception& e ) {
        zend_throw_exception_ex(MustacheException_ce_ptr, 0 TSRMLS_CC, (char *) e.what(), "MustacheException");
    } catch( std::bad_alloc& e ) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "%s", "Memory allocation failed.");
    } catch( std::runtime_error& e ) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "%s", e.what());
    } catch(...) {
        php_error_docref(NULL TSRMLS_CC, E_ERROR, "%s", "An unknown error has occurred.");
    }
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
