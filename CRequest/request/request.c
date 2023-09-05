

CRequest newCRequest(const char *url){
    CRequest *self = (CRequest*) malloc(sizeof (CRequest));
    *self =(CRequest){0};
    #ifdef __linux__
        self->binary_location= ".CRequest/curl";
    #endif
    #ifdef __win32__
        self->binary_location= ".CRequest/curl.exe";
    #endif

    self->use_cache = true;
    self->cache_location = ".CRequest/cache/";
    self->url = strdup(url);
    self->paramns = newCRequestDict();
    self->headers = newCRequestDict();

}


void CRequest_set_param(CRequest *self,const char *key, const char *value){
    CRequestDict_set_element(self->paramns,key,value);
}

void CRequest_set_headder(CRequest *self,const char *key, const char *value){
    CRequestDict_set_element(self->headers,key,value);

}


void CRequest_set_body(CRequest *self,const char *body){
    if(self->body){
        free(self->body);
    }

}

void CRequest_set_json(CRequest *self,cJSON *body);

