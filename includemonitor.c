/* Includemonitor extension */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <time.h>
#include "php.h"
#include "ext/standard/info.h"
#include "php_includemonitor.h"
#include "includemonitor_arginfo.h"

ZEND_DECLARE_MODULE_GLOBALS(includemonitor);

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_API zend_op_array *includemonitor_compile_file(zend_file_handle *file_handle, int type)
{
    /** Hooking here **/
    char* log_file_config = INCLUDEMONITOR_G(log_file);

    if (log_file_config[0] != '\0') {
        FILE * logFile;
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        logFile = fopen(log_file_config, "a");
        fprintf(logFile, "%d-%02d-%02dT%02d:%02d:%02d;", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        fprintf(logFile, "%s\n", ZSTR_VAL(file_handle->filename));
        fclose(logFile);
    } else {
        fprintf( stderr, "No log file configured");
    }
    /** End of hook **/

	zend_op_array *res;
	res = compile_file(file_handle, type);
	return res;
}

zend_op_array *(*includemonitor_orig_compile_file)(zend_file_handle *file_handle, int type);

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("includemonitor.log_file", "", PHP_INI_ALL, OnUpdateString, log_file, zend_includemonitor_globals, includemonitor_globals)
PHP_INI_END()

PHP_MINIT_FUNCTION(includemonitor) /* {{{ */
{
	REGISTER_INI_ENTRIES();

	includemonitor_orig_compile_file = zend_compile_file;
	zend_compile_file = includemonitor_compile_file;

	return SUCCESS;
}
/* }}} */

PHP_MSHUTDOWN_FUNCTION(includemonitor) /* {{{ */
{
	if (zend_compile_file == includemonitor_compile_file) {
		zend_compile_file = includemonitor_orig_compile_file;
	}

	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

PHP_GINIT_FUNCTION(includemonitor) /* {{{ */
{
#if defined(COMPILE_DL_INCLUDEMONITOR) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	includemonitor_globals->log_file = "";
}

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(includemonitor)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "includemonitor support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ includemonitor_module_entry */
zend_module_entry includemonitor_module_entry = {
	STANDARD_MODULE_HEADER,
	"includemonitor",                    /* Extension name */
	NULL,                                /* zend_function_entry */
	PHP_MINIT(includemonitor),           /* PHP_MINIT - Module initialization */
	PHP_MSHUTDOWN(includemonitor),       /* PHP_MSHUTDOWN - Module shutdown */
	NULL,                                /* PHP_RINIT - Request initialization */
	NULL,                                /* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(includemonitor),           /* PHP_MINFO - Module info */
	PHP_INCLUDEMONITOR_VERSION,          /* Version */
    PHP_MODULE_GLOBALS(includemonitor),  /* Module globals */
    PHP_GINIT(includemonitor),           /* PHP_GINIT – Globals initialization */
    NULL,                                /* PHP_GSHUTDOWN – Globals shutdown */
    NULL,                                /* post deactivate */
    STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#ifdef COMPILE_DL_INCLUDEMONITOR
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(includemonitor)
#endif
