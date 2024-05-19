/* uuid extension for PHP */

#ifndef PHP_UUID_H
# define PHP_UUID_H

extern zend_module_entry uuid_module_entry;
# define phpext_uuid_ptr &uuid_module_entry

# define PHP_UUID_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_UUID)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_UUID_H */
