

#include "request/request.c"

#ifdef CREQUEST_USE_LIBCURL
    #include "lib_get/lib_get.c"
#else
    #include "driver_get/driver_get.c"
#endif
