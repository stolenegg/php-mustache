
#include "mustache_private.hpp"

/* {{{ ZE2 OO definitions */
zend_class_entry * Mustache_ce_ptr;
static zend_object_handlers Mustache_obj_handlers;
/* }}} */

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO_EX(Mustache____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__getEscapeByDefault_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__getStartSequence_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__getStopSequence_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__setEscapeByDefault_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, escapeByDefault)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__setStartSequence_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, startSequence)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__setStopSequence_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, stopSequence)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__compile_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, tmpl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__execute_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, code)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__parse_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, tmpl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__render_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 3)
	ZEND_ARG_INFO(0, str)
        ZEND_ARG_INFO(0, vars)
        ZEND_ARG_INFO(0, partials)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__tokenize_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
	ZEND_ARG_INFO(0, tmpl)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(Mustache__debugDataStructure_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
        ZEND_ARG_INFO(0, vars)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ Mustache_methods */
static zend_function_entry Mustache_methods[] = {
    PHP_ME(Mustache, __construct, Mustache____construct_args, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
    PHP_ME(Mustache, getEscapeByDefault, Mustache__getEscapeByDefault_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, getStartSequence, Mustache__getStartSequence_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, getStopSequence, Mustache__getStopSequence_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, setEscapeByDefault, Mustache__setEscapeByDefault_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, setStartSequence, Mustache__setStartSequence_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, setStopSequence, Mustache__setStopSequence_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, compile, Mustache__compile_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, execute, Mustache__execute_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, parse, Mustache__parse_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, render, Mustache__render_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, tokenize, Mustache__tokenize_args, ZEND_ACC_PUBLIC)
    PHP_ME(Mustache, debugDataStructure, Mustache__debugDataStructure_args, ZEND_ACC_PUBLIC)
    PHP_FE_END
};
/* }}} */

/* {{{ php_mustache_mustache_object_fetch_object */
#ifndef ZEND_ENGINE_3
PHPAPI struct php_obj_Mustache * php_mustache_mustache_object_fetch_object(zval * zv TSRMLS_DC)
{
    return (struct php_obj_Mustache *) zend_object_store_get_object(zv TSRMLS_CC);
}
#else
static inline struct php_obj_Mustache * php_mustache_mustache_fetch_object(zend_object * obj TSRMLS_DC)
{
    return (struct php_obj_Mustache *) ((char *)(obj) - XtOffsetOf(struct php_obj_Mustache, std));
}

PHPAPI struct php_obj_Mustache * php_mustache_mustache_object_fetch_object(zval * zv TSRMLS_DC)
{
    return php_mustache_mustache_fetch_object(Z_OBJ_P(zv) TSRMLS_CC);
}
#endif
/* }}} */

/* {{{ Mustache_obj_free */
#ifndef ZEND_ENGINE_3
static void Mustache_obj_free(void * object TSRMLS_DC)
{
    struct php_obj_Mustache * payload = (struct php_obj_Mustache *) object;

    if( payload->mustache != NULL ) {
        try {
            delete payload->mustache;
        } catch(...) {
            mustache_exception_handler(TSRMLS_C);
        }
    }

    efree(object);
}
#else
static void Mustache_obj_free(zend_object * object TSRMLS_DC)
{
    struct php_obj_Mustache * payload = php_mustache_mustache_fetch_object(object TSRMLS_CC);

    if( payload->mustache != NULL ) {
        try {
            delete payload->mustache;
        } catch(...) {
            mustache_exception_handler(TSRMLS_C);
        }
    }

    zend_object_std_dtor((zend_object *) object TSRMLS_CC);
}
#endif
/* }}} */

/* {{{ Mustache_obj_create */
#ifndef ZEND_ENGINE_3
static zend_object_value Mustache_obj_create(zend_class_entry *class_type TSRMLS_DC)
{
    zend_object_value retval;
    struct php_obj_Mustache * payload = NULL;

    payload = (struct php_obj_Mustache *) ecalloc(1, sizeof(php_obj_Mustache));
    payload->std.ce = class_type;

    try {
        intern->mustache = mustache_new_Mustache(TSRMLS_C);
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
    
    retval.handle = zend_objects_store_put(payload, NULL, (zend_objects_free_object_storage_t) Mustache_obj_free, NULL TSRMLS_CC);
    retval.handlers = &Mustache_obj_handlers;

    return retval;
}
#else
static zend_object * Mustache_obj_create(zend_class_entry * ce TSRMLS_DC)
{
    struct php_obj_Mustache * intern;

    intern = (struct php_obj_Mustache *) ecalloc(1, sizeof(php_obj_Mustache) + zend_object_properties_size(ce));
    zend_object_std_init(&intern->std, ce TSRMLS_CC);
    intern->std.handlers = &Mustache_obj_handlers;

    try {
        intern->mustache = mustache_new_Mustache(TSRMLS_C);
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }

    return &intern->std;
}
#endif
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(mustache_mustache)
{
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Mustache", Mustache_methods);
    ce.create_object = Mustache_obj_create;
    Mustache_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);
    memcpy(&Mustache_obj_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
#ifdef ZEND_ENGINE_3
    Mustache_obj_handlers.offset = XtOffsetOf(php_obj_Mustache, std);
    Mustache_obj_handlers.free_obj = Mustache_obj_free;
#endif
    Mustache_obj_handlers.clone_obj = NULL;

    return SUCCESS;
}
/* }}} */

/* {{{ mustache_new_Mustache */
PHPAPI mustache::Mustache * mustache_new_Mustache(TSRMLS_D)
{
    mustache::Mustache * mustache = new mustache::Mustache();

    // Set ini settings
    if( MUSTACHEG(default_escape_by_default) ) {
        mustache->setEscapeByDefault(true);
    } else {
        mustache->setEscapeByDefault(false);
    }
    if( MUSTACHEG(default_start_sequence) ) {
        mustache->setStartSequence(MUSTACHEG(default_start_sequence), 0);
    }
    if( MUSTACHEG(default_stop_sequence) ) {
        mustache->setStopSequence(MUSTACHEG(default_stop_sequence), 0);
    }

    return mustache;
}
/* }}} */

/* {{{ mustache_parse_data_param */
PHPAPI bool mustache_parse_data_param(zval * data, mustache::Mustache * mustache, mustache::Data ** node TSRMLS_DC)
{
    struct php_obj_MustacheData * mdPayload = NULL;
  
    if( Z_TYPE_P(data) == IS_OBJECT ) {
        if( Z_OBJCE_P(data) == MustacheData_ce_ptr ) {
            mdPayload = php_mustache_data_object_fetch_object(data TSRMLS_CC);
            *node = mdPayload->data;
        } else {
            mustache_data_from_zval(*node, data TSRMLS_CC);
        }
    } else {
        mustache_data_from_zval(*node, data TSRMLS_CC);
    }
    return true;
}
/* }}} */

/* {{{ mustache_parse_partials_param */
static inline void mustache_parse_partial_param(char * key, zval * data,
        mustache::Mustache * mustache, mustache::Node::Partials * partials TSRMLS_DC)
{
    std::string ckey;
    std::string tmpl;
    mustache::Node node;
    mustache::Node * nodePtr = NULL;
    struct php_obj_MustacheAST * maPayload;

    if( Z_TYPE_P(data) == IS_STRING ) {
        // String key, string value
        ckey.assign(key);
        tmpl.assign(Z_STRVAL_P(data));
        partials->insert(std::make_pair(ckey, node));
        mustache->tokenize(&tmpl, &(*partials)[ckey]);
    } else if( Z_TYPE_P(data) == IS_OBJECT ) {
        // String key, object value
        if( Z_OBJCE_P(data) == MustacheTemplate_ce_ptr ) {
            zval * value = php5to7_zend_read_property(Z_OBJCE_P(data), data, ZEND_STRL("template"), 1);
            convert_to_string(value);
            std::string tmpstr(Z_STRVAL_P(value));
            ckey.assign(key);
            partials->insert(std::make_pair(ckey, node));
            mustache->tokenize(&tmpstr, &(*partials)[ckey]);
        } else if( Z_OBJCE_P(data) == MustacheAST_ce_ptr ) {
            ckey.assign(key);
            maPayload = php_mustache_ast_object_fetch_object(data TSRMLS_CC);
            partials->insert(std::make_pair(ckey, node));
            nodePtr = &(*partials)[ckey];
            nodePtr->type = mustache::Node::TypeContainer;
            nodePtr->child = maPayload->node;
        } else {
            php_error(E_WARNING, "Object not an instance of MustacheTemplate or MustacheAST");
        }
    } else {
        php_error(E_WARNING, "Partial array contains an invalid value");
    }
}

PHPAPI bool mustache_parse_partials_param(zval * array, mustache::Mustache * mustache,
        mustache::Node::Partials * partials TSRMLS_DC)
{
    HashTable * data_hash = NULL;
    ulong key_nindex = 0;

    // Ignore if not an array
    if( array == NULL || Z_TYPE_P(array) != IS_ARRAY ) {
        return false;
    }

    data_hash = HASH_OF(array);

#ifndef ZEND_ENGINE_3
    do {
        HashPosition data_pointer = NULL;
        zval ** data_entry = NULL;
        int key_type = 0;
        char * key_str = NULL;
        uint key_len = 0;

        zend_hash_internal_pointer_reset_ex(data_hash, &data_pointer);
        while( zend_hash_get_current_data_ex(data_hash, (void**) &data_entry, &data_pointer) == SUCCESS ) {
            key_type = zend_hash_get_current_key_ex(data_hash, &key_str, &key_len, &key_nindex, false, &data_pointer);
            if( key_type != HASH_KEY_IS_STRING ) {
                php_error(E_WARNING, "Partial array contains a non-string key");
            } else {
                mustache_parse_partial_param(key_str, *data_entry, mustache, partials TSRMLS_CC);
            }
            zend_hash_move_forward_ex(data_hash, &data_pointer);
        }
    } while(0);
#else
    do {
        zval * data_entry = NULL;
        zend_string * key = NULL;

        ZEND_HASH_FOREACH_KEY_VAL(data_hash, key_nindex, key, data_entry) {
            if( !key ) {
                php_error(E_WARNING, "Partial array contains a non-string key");
            } else {
                mustache_parse_partial_param(key->val, data_entry, mustache, partials TSRMLS_CC);
            }
        } ZEND_HASH_FOREACH_END();
    } while(0);
#endif
}
/* }}} */

/* {{{ mustache_parse_template_param */
PHPAPI bool mustache_parse_template_param(zval * tmpl, mustache::Mustache * mustache,
        mustache::Node ** node TSRMLS_DC)
{
    // Prepare template string
    if( Z_TYPE_P(tmpl) == IS_STRING ) {
        // Tokenize template
        char * tmpstr = Z_STRVAL_P(tmpl);
        *node = new mustache::Node();
        try {
            std::string templateStr(tmpstr/*, (size_t) Z_STRLEN_P(tmpl)*/);
            mustache->tokenize(&templateStr, *node);
        } catch (...) {
            delete *node; // Prevent leaks
            *node = NULL;
            throw;
        }
        return true;

    } else if( Z_TYPE_P(tmpl) == IS_OBJECT ) {
        // Use compiled template
        if( Z_OBJCE_P(tmpl) == MustacheTemplate_ce_ptr ) {
            zval * value = php5to7_zend_read_property(Z_OBJCE_P(tmpl), tmpl, ZEND_STRL("template"), 1);
            convert_to_string(value);
            std::string tmpstr(Z_STRVAL_P(value));

            if (!tmpstr.length()) {
                php_error(E_WARNING, "Empty MustacheTemplate");
                return false;
            } else {
                *node = new mustache::Node();
                try {
                    mustache->tokenize(&tmpstr, *node);
                } catch (...) {
                    delete *node; // Prevent leaks
                    *node = NULL;
                    throw;
                }
            }
            return true;
        } else if( Z_OBJCE_P(tmpl) == MustacheAST_ce_ptr ) {
            struct php_obj_MustacheAST *maPayload = php_mustache_ast_object_fetch_object(tmpl TSRMLS_CC);
            if( maPayload->node == NULL ) {
                php_error(E_WARNING, "Empty MustacheAST");
                return false;
            }
            *node = maPayload->node;
            return true;
        } else {
            php_error(E_WARNING, "Object not an instance of MustacheTemplate or MustacheAST");
            return false;
        }
    } else {
        php_error(E_WARNING, "Invalid argument");
        return false;
    }
}
/* }}} */

/* {{{ proto void Mustache::__construct() */
PHP_METHOD(Mustache, __construct)
{
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O",
                                     &_this_zval, Mustache_ce_ptr) == FAILURE ) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    // @todo
}
/* }}} Mustache::__construct */

/* {{{ proto boolean Mustache::getEscapeByDefault() */
PHP_METHOD(Mustache, getEscapeByDefault)
{
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O",
                                     &_this_zval, Mustache_ce_ptr) == FAILURE ) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);
    
    // Main
    if( payload->mustache->getEscapeByDefault() ) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} Mustache::getEscapeByDefault */

/* {{{ proto string Mustache::getStartSequence() */
PHP_METHOD(Mustache, getStartSequence)
{
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O",
                                     &_this_zval, Mustache_ce_ptr) == FAILURE ) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    const std::string & str = payload->mustache->getStartSequence();
    PHP5TO7_RETVAL_STRINGL(str.c_str(), str.length());
}
/* }}} Mustache::getStartSequence */

/* {{{ proto string Mustache::getStopSequence() */
PHP_METHOD(Mustache, getStopSequence)
{
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O",
                                     &_this_zval, Mustache_ce_ptr) == FAILURE ) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    // Main
    const std::string & str = payload->mustache->getStopSequence();
    PHP5TO7_RETVAL_STRINGL(str.c_str(), str.length());
}
/* }}} Mustache::getStopSequence */

/* {{{ proto boolean Mustache::setStartSequence(bool flag) */
PHP_METHOD(Mustache, setEscapeByDefault)
{
    long flag = 0;
    zval * _this_zval = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol",
                                     &_this_zval, Mustache_ce_ptr, &flag) == FAILURE) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    payload->mustache->setEscapeByDefault((bool) flag != 0);
    RETURN_TRUE;
}
/* }}} Mustache::setEscapeByDefault */

/* {{{ proto boolean Mustache::setStartSequence(string str) */
PHP_METHOD(Mustache, setStartSequence)
{
    zval * _this_zval;
    char * str;
    strsize_t str_len;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os",
                                     &_this_zval, Mustache_ce_ptr, &str, &str_len) == FAILURE) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    payload->mustache->setStartSequence(str/*, str_len*/);
    RETURN_TRUE;
}
/* }}} Mustache::setStartSequence */

/* {{{ proto boolean Mustache::setStopSequence(string str) */
PHP_METHOD(Mustache, setStopSequence)
{
    zval * _this_zval;
    char * str;
    strsize_t str_len;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os",
                                     &_this_zval, Mustache_ce_ptr, &str, &str_len) == FAILURE) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    payload->mustache->setStopSequence(str/*, str_len*/);
    RETURN_TRUE;
}
/* }}} Mustache::setStartSequence */

/* {{{ proto MustacheCode Mustache::compile(string template) */
PHP_METHOD(Mustache, compile)
{
    zval * _this_zval;
    zval * tmpl;
    zval * partials = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oz|z",
                                     &_this_zval, Mustache_ce_ptr, &tmpl, &partials) == FAILURE) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    try {
        // Prepare template tree
        mustache::Node templateNode;
        mustache::Node * templateNodePtr = &templateNode;
        if( !mustache_parse_template_param(tmpl, payload->mustache, &templateNodePtr TSRMLS_CC) ) {
            RETURN_FALSE;
        }

        // Prepare partials
        mustache::Node::Partials templatePartials;
        mustache_parse_partials_param(partials, payload->mustache, &templatePartials TSRMLS_CC);

        // Compile
        uint8_t * codes;
        size_t codes_length;
        payload->mustache->compile(templateNodePtr, &templatePartials, &codes, &codes_length);

        // Initialize new object
        object_init_ex(return_value, MustacheCode_ce_ptr);
        zend_update_property_stringl(MustacheCode_ce_ptr, return_value, ZEND_STRL("binaryString"),
                                     (char *) codes, codes_length TSRMLS_CC);
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} Mustache::compile */

/* {{{ proto string Mustache::execute(MustacheCode code) */
PHP_METHOD(Mustache, execute)
{
    zval * _this_zval;
    zval * code;
    zval * data;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "OOz",
                                     &_this_zval, Mustache_ce_ptr, &code, MustacheCode_ce_ptr, &data) == FAILURE ) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    try {
        // Prepare code
        zval rv;
        zval * value = php5to7_zend_read_property(Z_OBJCE_P(code), code, ZEND_STRL("binaryString"), 1);
        if( !value || Z_TYPE_P(value) != IS_STRING ) {
            RETURN_FALSE;
        }

        // Prepare template data
        mustache::Data templateData;
        mustache::Data * templateDataPtr = &templateData;
        if( !mustache_parse_data_param(data, payload->mustache, &templateDataPtr TSRMLS_CC) ) {
            RETURN_FALSE;
        }

        // Execute bytecode
        std::string output;
        payload->mustache->execute((uint8_t *) Z_STRVAL_P(value), Z_STRLEN_P(value), templateDataPtr, &output);

        // Output
        PHP5TO7_RETVAL_STRINGL(output.c_str(), output.length());
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} Mustache::execute */

/* {{{ proto MustacheAST Mustache::parse(string template) */
PHP_METHOD(Mustache, parse)
{
    zval * _this_zval;
    zval * tmpl;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oz",
                                     &_this_zval, Mustache_ce_ptr, &tmpl) == FAILURE ) {
        return;
    }

    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    try {
        // Check template parameter
        mustache::Node * templateNodePtr = NULL;
        if( !mustache_parse_template_param(tmpl, payload->mustache, &templateNodePtr TSRMLS_CC) ) {
            delete templateNodePtr;
            RETURN_FALSE;
        }

        // Handle return value
        if( Z_TYPE_P(tmpl) == IS_STRING ) {
            if( MustacheAST_ce_ptr == NULL ) {
                delete templateNodePtr;
                php_error_docref(NULL TSRMLS_CC, E_WARNING, "Class MustacheAST does not exist");
                RETURN_FALSE;
            }

          // Initialize new object
          object_init_ex(return_value, MustacheAST_ce_ptr);
          struct php_obj_MustacheAST * intern = php_mustache_ast_object_fetch_object(return_value TSRMLS_CC);
          intern->node = templateNodePtr;

        // Ref - not sure if this is required
    //    Z_SET_REFCOUNT_P(return_value, 1);
    //    Z_SET_ISREF_P(return_value);

        } else if( Z_TYPE_P(tmpl) == IS_OBJECT ) {
            // Handle return value for object parameter
            // @todo return the object itself?
            RETURN_TRUE;
        }
    
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} Mustache::parse */

/* {{{ proto string Mustache::render(mixed template, array data, array partials) */
PHP_METHOD(Mustache, render)
{
    zval * _this_zval;
    zval * tmpl;
    zval * data;
    zval * partials = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ozz|a/",
                                     &_this_zval, Mustache_ce_ptr, &tmpl, &data, &partials) == FAILURE ) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    try {
        // Prepare template tree
        mustache::Node templateNode;
        mustache::Node * templateNodePtr = &templateNode;
        if( !mustache_parse_template_param(tmpl, payload->mustache, &templateNodePtr TSRMLS_CC) ) {
            RETURN_FALSE;
        }

        // Prepare template data
        mustache::Data templateData;
        mustache::Data * templateDataPtr = &templateData;
        if( !mustache_parse_data_param(data, payload->mustache, &templateDataPtr TSRMLS_CC) ) {
            RETURN_FALSE;
        }

        // Tokenize partials
        mustache::Node::Partials templatePartials;
        mustache_parse_partials_param(partials, payload->mustache, &templatePartials TSRMLS_CC);

        // Reserve length of template
        std::string output;
        if( Z_TYPE_P(tmpl) == IS_STRING ) {
            output.reserve(Z_STRLEN_P(tmpl));
        }

        // Render template
        payload->mustache->render(templateNodePtr, templateDataPtr, &templatePartials, &output);

        // Output
        PHP5TO7_RETVAL_STRINGL(output.c_str(), output.length());
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} Mustache::render */

/* {{{ proto array Mustache::tokenize(string template) */
PHP_METHOD(Mustache, tokenize)
{
    zval * _this_zval;
    char * template_str;
    strsize_t template_len;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os",
                                     &_this_zval, Mustache_ce_ptr, &template_str, &template_len) == FAILURE) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    try {
        // Assign template to string
        std::string templateStr(template_str/*, template_len*/);

        // Tokenize template
        mustache::Node root;
        payload->mustache->tokenize(&templateStr, &root);

        // Convert to PHP array
        mustache_node_to_zval(&root, return_value TSRMLS_CC);
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} Mustache::tokenize */

/* {{{ proto array Mustache::debugDataStructure(array data) */
PHP_METHOD(Mustache, debugDataStructure)
{
    zval * _this_zval = NULL;
    zval * data = NULL;

    if( zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oz",
                                     &_this_zval, Mustache_ce_ptr, &data) == FAILURE ) {
        return;
    }

    zend_class_entry * _this_ce = Z_OBJCE_P(_this_zval);
    struct php_obj_Mustache * payload = php_mustache_mustache_object_fetch_object(_this_zval TSRMLS_CC);

    try {
        // Prepare template data
        mustache::Data templateData;
        mustache_data_from_zval(&templateData, data TSRMLS_CC);

        // Reverse template data
        mustache_data_to_zval(&templateData, return_value TSRMLS_CC);
    } catch(...) {
        mustache_exception_handler(TSRMLS_C);
    }
}
/* }}} Mustache::debugDataStructure */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
