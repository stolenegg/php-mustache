
#ifndef PHP_MUSTACHE_PRIVATE_HPP
#define PHP_MUSTACHE_PRIVATE_HPP

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "php_mustache.h"

#include <main/php_ini.h>
#include <main/php_variables.h>
#include <main/php_globals.h>
#include <main/SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_interfaces.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_compile.h>
#include <Zend/zend_closures.h>

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#include <stdint.h>

#if PHP_MAJOR_VERSION >= 7
#include <Zend/zend_string.h>
#endif

#include "php5to7.h"

#if PHP_MAJOR_VERSION < 7
#define _STRS ZEND_STRS
#else
#define _STRS ZEND_STRL
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <string>

#include "mustache.hpp"

#include "mustache_ast.hpp"
#include "mustache_code.hpp"
#include "mustache_class_method_lambda.hpp"
#include "mustache_data.hpp"
#include "mustache_exceptions.hpp"
#include "mustache_lambda.hpp"
#include "mustache_lambda_helper.hpp"
#include "mustache_mustache.hpp"
#include "mustache_template.hpp"
#include "mustache_zend_closure_lambda.hpp"

#endif /* PHP_MUSTACHE_PRIVATE_HPP */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: fdm=marker
 * vim: et sw=4 ts=4
 */
