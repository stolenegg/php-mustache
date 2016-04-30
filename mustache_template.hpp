
#ifndef PHP_MUSTACHE_TEMPLATE_HPP
#define PHP_MUSTACHE_TEMPLATE_HPP

#ifdef __cplusplus
extern "C" {
#endif

extern zend_class_entry * MustacheTemplate_ce_ptr;

PHP_MINIT_FUNCTION(mustache_template);

PHP_METHOD(MustacheTemplate, __construct);
PHP_METHOD(MustacheTemplate, __toString);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* PHP_MUSTACHE_TEMPLATE_HPP */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
