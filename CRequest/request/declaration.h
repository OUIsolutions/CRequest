

#include "request/request.h"

#ifdef CREQUEST_USE_LIBCURL
    #include "lib_get/lib_get.h"
#else
    #include "driver_get/driver_get.h"
#endif

