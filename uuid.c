#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_uuid.h"
#include "uuid_arginfo.h"

#include <stdlib.h>
#include <time.h>

#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHP_FUNCTION(uuid_v4)
{
	ZEND_PARSE_PARAMETERS_NONE();

	unsigned char data[16];
	char* uuid = (char*)malloc(37 * sizeof(char));

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 16; i++) {
        data[i] = rand() % 256;
    }

    data[6] = (data[6] & 0x0F) | 0x40;
    data[8] = (data[8] & 0x3F) | 0x80;

    sprintf(uuid,
            "%02x%02x%02x%02x-"
            "%02x%02x-"
            "%02x%02x-"
            "%02x%02x-"
            "%02x%02x%02x%02x%02x%02x",
            data[0], data[1], data[2], data[3],
            data[4], data[5],
            data[6], data[7],
            data[8], data[9],
            data[10], data[11], data[12], data[13], data[14], data[15]);

    RETURN_STRING(uuid);
}

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(uuid)
{
#if defined(ZTS) && defined(COMPILE_DL_UUID)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(uuid)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "uuid support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ uuid_module_entry */
zend_module_entry uuid_module_entry = {
	STANDARD_MODULE_HEADER,
	"uuid",					/* Extension name */
	ext_functions,					/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(uuid),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(uuid),			/* PHP_MINFO - Module info */
	PHP_UUID_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_UUID
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(uuid)
#endif
