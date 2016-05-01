
#ifndef PHP_MUSTACHE_EXCEPTIONS_HPP
#define PHP_MUSTACHE_EXCEPTIONS_HPP

#ifdef __cplusplus
extern "C" {
#endif

extern zend_class_entry * MustacheException_ce_ptr;
extern zend_class_entry * MustacheParserException_ce_ptr;

extern PHPAPI void mustache_exception_handler(TSRMLS_D);

PHP_MINIT_FUNCTION(mustache_exceptions);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* PHP_MUSTACHE_EXCEPTIONS_HPP */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
