/* Includemonitor extension */

#ifndef PHP_INCLUDEMONITOR_H
#define PHP_INCLUDEMONITOR_H

extern zend_module_entry includemonitor_module_entry;
#define phpext_includemonitor_ptr &includemonitor_module_entry

#define PHP_INCLUDEMONITOR_VERSION "0.1.0"

ZEND_BEGIN_MODULE_GLOBALS(includemonitor)
    zend_long log_file;
ZEND_END_MODULE_GLOBALS(includemonitor)

ZEND_EXTERN_MODULE_GLOBALS(includemonitor)

#define INCLUDEMONITOR_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(includemonitor, v)

ZEND_API zend_op_array *includemonitor_compile_file(zend_file_handle *file_handle, int type);

#endif	/* PHP_INCLUDEMONITOR_H */
