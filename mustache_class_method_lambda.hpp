
#ifndef PHP_MUSTACHE_CLASS_METHOD_LAMBDA_HPP
#define PHP_MUSTACHE_CLASS_METHOD_LAMBDA_HPP

#include "mustache_lambda.hpp"

#ifdef __cplusplus
extern "C" {
#endif

class ClassMethodLambda : public Lambda {
    private:
        zval * object;
        zval function_name;

    protected:
        int getUserFunctionParamCount();
#if PHP_MAJOR_VERSION >= 7
        int invokeUserFunction(zval *retval_ptr, int param_count, zval params[]);
#else
        int invokeUserFunction(zval **retval_ptr_ptr, int param_count, zval **params[] TSRMLS_DC);
#endif

    public:
        ClassMethodLambda(zval * object, const char * function_name_string) : object(object) {
            Z_ADDREF_P(object);
            PHP5TO7_ZVAL_STRING(&function_name, function_name_string);
        };
        ~ClassMethodLambda();
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* PHP_MUSTACHE_CLASS_METHOD_LAMBDA_HPP */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
