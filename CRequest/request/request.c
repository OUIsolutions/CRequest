

CRequest * newCRequest(const char *url){
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
    self->clear_cache = true;
    self->cache_location = ".CRequest/cache/";
    self->url = strdup(url);
    self->paramns = newCRequestDict();
    self->headers = newCRequestDict();
    return self;

}


void CRequest_add_query_parram(CRequest *self, const char *key, const char *value){
    CRequestDict_set_element(self->paramns,key,value);
}

void CRequest_add_headder(CRequest *self, const char *key, const char *value){
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
    self->body = malloc(size +1);
    self->body = memcpy(self->body,body,size);
}
void CRequest_set_body_string(CRequest *self,const char *body){
    CRequest_set_body(self,(unsigned char*)body, (long)strlen(body));
}

void CRequest_set_b64_body(CRequest *self,unsigned char *body,long size){
    CRequest_resset_body(self);
    self->body = (unsigned char*)dtw_base64_encode(body,size);
    self->body_size = (long)strlen((char*)self->body);
}


void CRequest_set_body_json(CRequest *self,cJSON *body){
    CRequest_resset_body(self);
    self->body =(unsigned char*)cJSON_Print(body);
    self->body_size = (long)strlen((char*)self->body);

}

void CRequest_free(CRequest *self){
    CRequestDict_free(self->paramns);
    CRequestDict_free(self->headers);
    free(self->url);
    if(self->error_menssage){
        free(self->error_menssage);
    }
    if(self->body){
        free(self->body);
    }
    if(self->response){
        free(self->response);
    }
    free(self);
}

void CRequest_represent(CRequest *self){

    printf("url:%s\n",self->url);
    if(self->paramns->size){
        printf("Paramns:\n");
        CRequestDict_represent(self->paramns);
    }

    if(self->headers->size){
        printf("Headders:\n");
        CRequestDict_represent(self->headers);
    }

    if(self->body){
        printf("Body:------------------------------------------------\n");
        printf("size: %ld\n",self->body_size);
        printf("content:\n%s",(char*)self->body);
    }



}