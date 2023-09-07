/*
MIT License

Copyright (c) 2023 OUI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#if !defined(CREQUEST_USE_NATIVE_CURL) && !defined(CREQUEST_USE_LIBCURL) && !defined(CREQUEST_USE_CUSTOM_DRIVER)
    //these will embed the driver into the final binary
    #include "driver.h"
#endif


#include "dependencies/doTheWorld.h"
#include "dependencies/CTextEngine.h"

#include "dict/declaration.h"
#include "request/request.h"
#include "namespace/namespace.h"


#include "dict/definition.h"
#ifndef CREQUEST_USE_LIBCURL
#include "request/driver_get.c"
#else
#include "request/lib_get.c"
#endif

#include "request/request.c"
#include "namespace/namespace.c"


