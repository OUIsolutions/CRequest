

CRequest * newCRequest(const char *url){
    CRequest *self = (CRequest*) malloc(sizeof (CRequest));
    *self =(CRequest){0};
    self->cache_time = 60;
    self->method = "GET";
    #ifdef __linux__
            self->binary_location= ".CRequest/curl";
    #elif _WIN32
            self->binary_location= ".CRequest/curl.exe";
    #endif

    self->delete_cache = true;
    self->clear_cache = true;
    self->cache_location = ".CRequest/cache/";
    self->private_url = strdup(url);
    self->private_paramns = newCRequestDict();
    self->private_headers = newCRequestDict();
    return self;

}


void CRequest_add_query_parram(CRequest *self, const char *key, const char *value){
    CRequestDict_set_element(self->private_paramns, key, value);
}

void CRequest_add_headder(CRequest *self, const char *key, const char *value){
    CRequestDict_set_element(self->private_headers, key, value);

}
void CRequest_resset_body(CRequest *self){
    if(self->private_body){
        free(self->private_body);
    }
}
void CRequest_set_body(CRequest *self,unsigned char *body,long size){
    CRequest_resset_body(self);
    self->private_body_size = size;
    self->private_body = malloc(size + 1);
    self->private_body = memcpy(self->private_body, body, size);
}
void CRequest_set_body_string(CRequest *self,const char *body){
    CRequest_set_body(self,(unsigned char*)body, (long)strlen(body));
}

void CRequest_set_b64_body(CRequest *self,unsigned char *body,long size){
    CRequest_resset_body(self);
    self->private_body = (unsigned char*)dtw_base64_encode(body, size);
    self->private_body_size = (long)strlen((char*)self->private_body);
}


void CRequest_set_body_json(CRequest *self,cJSON *body){
    CRequest_resset_body(self);
    self->private_body =(unsigned char*)cJSON_Print(body);
    self->private_body_size = (long)strlen((char*)self->private_body);

}

void CRequest_free(CRequest *self){
    CRequestDict_free(self->private_paramns);
    CRequestDict_free(self->private_headers);
    free(self->private_url);
    if(self->error_menssage){
        free(self->error_menssage);
    }
    if(self->private_body){
        free(self->private_body);
    }

    free(self);
}

char  * CRequest_assign_requisition(CRequest *self){
    DtwHash *hash = newDtwHash();
    DtwHash_digest_string(hash,self->method);
    DtwHash_digest_string(hash,self->private_url);
    for(int i = 0; i < self->private_paramns->size; i++){
        CRequestKeyVal *current = self->private_paramns->elements[i];
        DtwHash_digest_string(hash,current->key);
        DtwHash_digest_string(hash,current->key);
    }
    for(int i = 0; i < self->private_headers->size; i++){
        CRequestKeyVal *current = self->private_headers->elements[i];
        DtwHash_digest_string(hash,current->key);
        DtwHash_digest_string(hash,current->key);
    }
    if(self->private_body){
        DtwHash_digest_any(hash,self->private_body,self->private_body_size);
    }
    if(self->private_body_file){
        DtwHash_digest_file(hash,self->private_body_file);
    }
    char *result = strdup(hash->hash);
    DtwHash_free(hash);
    return result;
}

char * CRequest_get_cache_response_location(CRequest *self){
    CTextStack * location = newCTextStack_string_empty();
    char *sha = CRequest_assign_requisition(self);
    CTextStack_format(location,"%s/response/%s",self->cache_location,sha);
    free(sha);
    return CTextStack_self_transform_in_string_and_self_clear(location);
}


char * CRequest_get_cache_body_location(CRequest *self){
    CTextStack * location = newCTextStack_string_empty();
    char *sha = dtw_generate_sha_from_any(self->private_body,self->private_body_size);
    CTextStack_format(location,"%s/body/%s",self->cache_location,sha);
    free(sha);
    return CTextStack_self_transform_in_string_and_self_clear(location);

}

char * CRequest_get_string_response(CRequest *self){
    bool is_binary;
    long size;
    unsigned char* content = CRequest_get_any_response(self, &size, &is_binary);
    if(is_binary){
        free(content);
        return NULL;
    }
    return (char*)content;
}

cJSON *CRequest_get_json_response(CRequest *self){
    char *content = CRequest_get_string_response(self);
    cJSON *parsed  = cJSON_Parse(content);
    free(content);
    return parsed;
}

bool CRequest_valid_cache_file(CRequest *self,const char *file){
    if(self->delete_cache){
        return false;
    }
    if(dtw_entity_type(file) == DTW_NOT_FOUND){
        return false;
    }

    if(dtw_get_entity_last_motification_in_unix(file) + self->cache_time < time(NULL)){
        return  false;
    }
    return true;
}


void CRequest_represent(CRequest *self){

    printf("url:%s\n",self->private_url);
    if(self->private_paramns->size){
        printf("Paramns:\n");
        CRequestDict_represent(self->private_paramns);
    }

    if(self->private_headers->size){
        printf("Headders:\n");
        CRequestDict_represent(self->private_headers);
    }

    if(self->private_body){
        printf("Body:------------------------------------------------\n");
        printf("size: %ld\n",self->private_body_size);
        printf("content:\n%s",(char*)self->private_body);
    }



}