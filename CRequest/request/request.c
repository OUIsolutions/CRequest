

CRequest newCRequest(const char *url){
    CRequest *self = (CRequest*) malloc(sizeof (CRequest));
    *self =(CRequest){0};
    self->cache_time = 60;
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
void CRequest_resset_body(CRequest *self){
    if(self->body){
        free(self->body);
    }
}
void CRequest_set_body(CRequest *self,unsigned char *body,long size){
    CRequest_resset_body(self);
    self->body_size = size;
    self->body = memcpy(self->body,body,size);
}

void CRequest_set_b64_body(CRequest *self,unsigned char *body,long size){
    CRequest_resset_body(self);
    self->body = (unsigned char*)dtw_base64_encode(body,size);
    self->body_size = (long)strlen((char*)self->body);
}

void CRequest_set_body_string(CRequest *self,const char *body){
    CRequest_resset_body(self);
    CRequest_set_body(self,(unsigned char*)body, (long)strlen(body));
}

void CRequest_set_body_json(CRequest *self,cJSON *body){
    CRequest_resset_body(self);
    self->body =(unsigned char*)cJSON_Print(body);
    self->body_size = (long)strlen((char*)self->body);

}
void CRequest_represent(CRequest *self){
    printf("Paramns:-------------------------------------------\n");
    CRequestDict_represent(self->paramns);
    printf("Headders:-------------------------------------------\n");
    CRequestDict_represent(self->paramns);
    printf("Body:------------------------------------------------\n");
    printf("size: %ld\n",self->body_size);
    printf("content:\n%s",(char*)self->body);
}