

#include "dependencies/doTheWorld.h"
#include "dependencies/CTextEngine.h"

#include "dict/declaration.h"
#include "request/request.h"
#include "namespace/namespace.h"


#include "dict/definition.h"
#include "request/request.c"
#ifdef CREQUEST_USE_LIBCURL
    #include "request/lib_get.c"
#else
    #include "request/driver_get.c"
#endif

#include "namespace/namespace.c"


