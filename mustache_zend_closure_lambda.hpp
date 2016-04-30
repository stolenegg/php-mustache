
#ifndef PHP_MUSTACHE_ZEND_CLOSURE_LAMBDA_HPP
#define PHP_MUSTACHE_ZEND_CLOSURE_LAMBDA_HPP

#include <Zend/zend_closures.h>

#include "mustache_lambda.hpp"

#ifdef __cplusplus
extern "C" {
#endif

class ZendClosureLambda : public Lambda {
    private:
        zval * closure;

    protected:
        int getUserFunctionParamCount();
#ifdef ZEND_ENGINE_3
        int invokeUserFunction(zval *retval_ptr, int param_count, zval params[]);
#else
        int invokeUserFunction(zval **retval_ptr_ptr, int param_count, zval **params[] TSRMLS_DC);
#endif

    public:
        ZendClosureLambda(zval * closure) : closure(closure) {
            Z_ADDREF_P(closure);
        };
        ~ZendClosureLambda();
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* PHP_MUSTACHE_ZEND_CLOSURE_LAMBDA_HPP */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
