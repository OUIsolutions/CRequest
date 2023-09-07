//
// Created by mateusmoutinho on 07/09/23.
//



CRequest * newCRequest(const char *url){
    CRequest *self = (CRequest*) malloc(sizeof (CRequest));
    *self =(CRequest){0};
    self->cache_time = 60;
    self->method = "GET";
#ifdef __linux__
    self->driver_location= ".CRequest/curl";
#elif _WIN32
    self->binary_location= ".CRequest/curl.exe";
#endif
    self->use_cache = true;

    self->cache_location = ".CRequest/cache/";
    self->private_url = strdup(url);
    self->private_paramns = newCRequestDict();
    self->private_headers = newCRequestDict();
    return self;

}
void CRequest_free(CRequest *self){
    CRequestDict_free(self->private_paramns);
    CRequestDict_free(self->private_headers);
    free(self->private_url);
    if(self->private_body_file){
        free(self->private_body_file);
    }
    if(self->private_body){
        free(self->private_body);
    }

    free(self);
}

