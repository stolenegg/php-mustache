
#include "mustache_private.hpp"

/* {{{ ZE2 OO definitions */
zend_class_entry * MustacheAST_ce_ptr;
static zend_object_handlers MustacheAST_obj_handlers;
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(MustacheAST____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
    ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(MustacheAST____sleep_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(MustacheAST__toArray_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(MustacheAST____toString_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(MustacheAST____wakeup_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ MustacheAST_methods */
static zend_function_entry MustacheAST_methods[] = {
    PHP_ME(MustacheAST, __construct, MustacheAST____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(MustacheAST, __sleep, MustacheAST____sleep_args, ZEND_ACC_PUBLIC)
    PHP_ME(MustacheAST, toArray, MustacheAST__toArray_args, ZEND_ACC_PUBLIC)
    PHP_ME(MustacheAST, __toString, MustacheAST____toString_args, ZEND_ACC_PUBLIC)
    PHP_ME(MustacheAST, __wakeup, MustacheAST____wakeup_args, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
/* }}} */

/* {{{ mustache_node_from_binary_string */
PHPAPI void mustache_node_from_binary_string(mustache::Node ** node, char * str, int len)
{
    std::vector<uint8_t> uint_str;
    uint_str.resize(len);
    int i = 0;
    for( i = 0; i < len; i++ ) {
        uint_str[i] = str[i];
    }

    size_t vpos = 0;
    *node = mustache::Node::unserialize(uint_str, 0, &vpos);
}
/* }}} */

/* {{{ mustache_node_to_binary_string */
PHPAPI void mustache_node_to_binary_string(mustache::Node * node, char ** estr, int * elen)
{
    std::vector<uint8_t> * serialPtr = node->serialize();
    std::vector<uint8_t> & serial = *serialPtr;
    int serialLen = serial.size();

    char * str = (char *) emalloc(sizeof(char *) * (serialLen + 1));
    for( int i = 0 ; i < serialLen; i++ ) {
        str[i] = (char) serial[i];
    }
    str[serialLen] = '\0';
    delete serialPtr;

    *elen = serialLen;
    *estr = str;
}
/* }}} */

/* {{{ mustache_node_to_zval */
PHPAPI void mustache_node_to_zval(mustache::Node * node, zval * current TSRMLS_DC)
{
    _DECLARE_ZVAL(children);
    _DECLARE_ZVAL(child);

    array_init(current);

    // Basic data
    add_assoc_long(current, "type", node->type);
    add_assoc_long(current, "flags", node->flags);
    if( NULL != node->data && node->data->length() > 0 ) {
        // @todo double-check the length of data - might need to be sizeof()
        php5to7_add_assoc_stringl_ex(current, ZEND_STRL("data"), (char *) node->data->c_str(), node->data->length());
    }

    // Children
    if( node->children.size() > 0 ) {
        _ALLOC_INIT_ZVAL(children);
        array_init(children);

        mustache::Node::Children::iterator it;
        for ( it = node->children.begin() ; it != node->children.end(); it++ ) {
            _ALLOC_INIT_ZVAL(child);
            mustache_node_to_zval(*it, child TSRMLS_CC);
            add_next_index_zval(children, child);
        }

        add_assoc_zval(current, "children", children);
        children = NULL;
    }

    // Partials
    if( node->partials.size() > 0 ) {
        _ALLOC_INIT_ZVAL(children);
        array_init(children);

        mustache::Node::Partials::iterator it;
        for ( it = node->partials.begin() ; it != node->partials.end(); it++ ) {
            _ALLOC_INIT_ZVAL(child);
            mustache_node_to_zval(&(it->second), child TSRMLS_CC);
            add_assoc_zval(children, it->first.c_str(), child);
        }

        add_assoc_zval(current, "partials", children);
        children = NULL;
    }
}
/* }}} */

/* {{{ php_mustache_ast_object_fetch_object */
#if PHP_MAJOR_VERSION < 7
PHPAPI struct php_obj_MustacheAST * php_mustache_ast_object_fetch_object(zval * zv TSRMLS_DC)
{
    return (struct php_obj_MustacheAST *) zend_object_store_get_object(zv TSRMLS_CC);
}
#else
static inline struct php_obj_MustacheAST * php_mustache_ast_fetch_object(zend_object * obj TSRMLS_DC)
{
    return (struct php_obj_MustacheAST *)((char *)(obj) - XtOffsetOf(struct php_obj_MustacheAST, std));
}

PHPAPI struct php_obj_MustacheAST * php_mustache_ast_object_fetch_object(zval * zv TSRMLS_DC)
{
    return php_mustache_ast_fetch_object(Z_OBJ_P(zv) TSRMLS_CC);
}
#endif
/* }}} */

/* {{{ MustacheAST_obj_free */
#if PHP_MAJOR_VERSION < 7
static void MustacheAST_obj_free(void *object TSRMLS_DC)
{
    struct php_obj_MustacheAST * payload = (struct php_obj_MustacheAST *) object;

    if( payload->node != NULL ) {
        try {
            delete payload->node;
        } catch(...) {
            mustache_exception_handler(TSRMLS_C);
        }
    }

    zend_object_std_dtor((zend_object *)object TSRMLS_CC);
    efree(object);
}
#else
static void MustacheAST_obj_free(zend_object * object TSRMLS_DC)
{
    struct php_obj_MustacheAST * payload = php_mustache_ast_fetch_object(object TSRMLS_CC);

    if( payload->node != NULL ) {
        try {
            delete payload->node;
        } catch (...) {
            mustache_exception_handler(TSRMLS_C);
        }
    }

    zend_object_std_dtor((zend_object *)object TSRMLS_CC);
}
#endif
/* }}} */

/* {{{ MustacheAST_obj_create */
#ifndef ZEND_ENGINE_3
static zend_object_value MustacheAST_obj_create(zend_class_entry * class_type TSRMLS_DC)
{
    zend_object_value retval;
    zval * tmp;

    struct php_obj_MustacheAST * payload = (struct php_obj_MustacheAST *) emalloc(sizeof(struct php_obj_MustacheAST));
    memset(payload, 0, sizeof(struct php_obj_MustacheAST));
    
    zend_object_std_init((zend_object *) payload, class_type TSRMLS_CC);
    
#if PHP_VERSION_ID < 50399
    zend_hash_copy(payload->std.properties, &(class_type->default_properties),
        (copy_ctor_func_t) zval_add_ref, NULL, sizeof(zval*));
#else
    object_properties_init(&payload->std, class_type);
#endif
    
    payload->node = NULL;

    retval.handle = zend_objects_store_put(payload, NULL, (zend_objects_free_object_storage_t) MustacheAST_obj_free, NULL TSRMLS_CC);
    retval.handlers = (zend_object_handlers *) &MustacheAST_obj_handlers;

    return retval;
}
#else
static zend_object * MustacheAST_obj_create(zend_class_entry * ce TSRMLS_DC)
{
    struct php_obj_MustacheAST * intern = (struct php_obj_MustacheAST *) ecalloc(1, sizeof(struct php_obj_MustacheAST) + zend_object_properties_size(ce));
    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    intern->std.handlers = &MustacheAST_obj_handlers;
    intern->node = NULL;

    return &intern->std;
}
#endif
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(mustache_ast)
{
    zend_class_entry ce;

    memcpy(&MustacheAST_obj_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
#ifdef ZEND_ENGINE_3
    MustacheAST_obj_handlers.offset = XtOffsetOf(struct php_obj_MustacheAST, std);
    MustacheAST_obj_handlers.free_obj = MustacheAST_obj_free;
#endif
    MustacheAST_obj_handlers.clone_obj = NULL;
    
    INIT_CLASS_ENTRY(ce, "MustacheAST", MustacheAST_methods);
    ce.create_object = MustacheAST_obj_create;
    
    MustacheAST_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
    MustacheAST_ce_ptr->create_object = MustacheAST_obj_create;
    
    zend_declare_property_null(MustacheAST_ce_ptr, ZEND_STRL("binaryString"), ZEND_ACC_PROTECTED TSRMLS_CC);
    
    return SUCCESS;
}
/* }}} */

/* {{{ proto void MustacheAST::__construct(string binaryString) */
PHP_METHOD(MustacheAST, __construct)
{
    char * str;
    strsize_t str_len;
    zval * _this_zval;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|s",
            &_this_zval, MustacheAST_ce_ptr, &str, &str_len) == FAILURE) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_MustacheAST * payload = php_mustache_ast_object_fetch_object(_this_zval TSRMLS_CC);

    // Check payload
    if( payload->node != NULL ) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "MustacheAST is already initialized");
        return;
    }

    // Unserialize
    try {
        mustache_node_from_binary_string(&payload->node, str, str_len);
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} MustacheAST::__construct */

/* {{{ proto void MustacheAST::__sleep() */
PHP_METHOD(MustacheAST, __sleep)
{
    zval * _this_zval = getThis();
    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_MustacheAST * payload = php_mustache_ast_object_fetch_object(_this_zval TSRMLS_CC);

    array_init(return_value);

    // Check payload
    if( payload->node == NULL ) {
        return;
    }

    // Serialize and store
    try {
        char * str = NULL;
        int len = 0;
        mustache_node_to_binary_string(payload->node, &str, &len);
        if( str != NULL ) {
            zend_update_property_stringl(MustacheAST_ce_ptr, _this_zval, ZEND_STRL("binaryString"), str, len TSRMLS_CC);
            php5to7_add_next_index_stringl(return_value, ZEND_STRL("binaryString"));
            efree(str);
        }
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} MustacheAST::__sleep */

/* {{{ proto array MustacheAST::toArray() */
PHP_METHOD(MustacheAST, toArray)
{
    zval * _this_zval = getThis();
    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_MustacheAST * payload = php_mustache_ast_object_fetch_object(_this_zval TSRMLS_CC);

    // Check payload
    if( payload->node == NULL ) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "MustacheAST was not initialized properly");
        return;
    }

    // Convert to PHP array
    try {
        mustache_node_to_zval(payload->node, return_value TSRMLS_CC);
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} MustacheAST::toArray */

/* {{{ proto string MustacheAST::__toString() */
PHP_METHOD(MustacheAST, __toString)
{
    zval * _this_zval = getThis();
    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_MustacheAST * payload = php_mustache_ast_object_fetch_object(_this_zval TSRMLS_CC);
    char * str = NULL;
    int len = 0;

    if( payload->node == NULL ) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "MustacheAST was not initialized properly");
        return;
    }

    try {
        // Convert to PHP binary string
        mustache_node_to_binary_string(payload->node, &str, &len);

        if( str != NULL ) {
            PHP5TO7_RETVAL_STRINGL(str, len);
            efree(str);
        }
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} MustacheAST::__toString */

/* {{{ proto void MustacheAST::__wakeup() */
PHP_METHOD(MustacheAST, __wakeup)
{
    zval * _this_zval = getThis();
    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_MustacheAST * payload = php_mustache_ast_object_fetch_object(_this_zval TSRMLS_CC);
    zval * value = php5to7_zend_read_property(Z_OBJCE_P(_this_zval), _this_zval, ZEND_STRL("binaryString"), 1);

    if( Z_TYPE_P(value) == IS_STRING && Z_STRLEN_P(value) > 0 ) {
        try {
            mustache_node_from_binary_string(&payload->node, Z_STRVAL_P(value), Z_STRLEN_P(value));
        } catch(...) {
            mustache_exception_handler(TSRMLS_C);
        }
    }
}
/* }}} MustacheAST::__wakeup */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
