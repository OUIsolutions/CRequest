

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
void CRequest_set_body_file(CRequest *self,const char *filename){
    self->private_body_file = strdup(filename);
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


char * CRequest_get_string_response(CRequest *self){
    bool is_binary;
    long size;
    unsigned char* content = CRequest_get_any_response(self, &size, &is_binary);
    if(is_binary){
        free(content);
        self->error = CREQUEST_NOT_A_STRING;
        self->error_menssage = "requisition its not a valid string\n";
        return NULL;
    }

    return (char*)content;
}

cJSON *CRequest_get_json_response(CRequest *self){
    char *content = CRequest_get_string_response(self);
    if(!content){
        return NULL;
    }

    cJSON *parsed  = cJSON_Parse(content);
    free(content);
    if(!parsed){
        self->error = CREQUEST_NOT_VALID_JSON;
        self->error_menssage = "requisition its not a valid json\n";
        return NULL;
    }

    return parsed;
}


CTextStack *private_CRequest_format_url(CRequest *self){
    CTextStack  *url = newCTextStack_string_empty();
    CTextStack_format(url, "%s", self->private_url);
    long size = self->private_paramns->size;
    if(!size){
        return url;
    }

    CTextStack * test_inclusion = newCTextStack_string(self->private_url);
    if(CTextStack_index_of(test_inclusion,"?") == -1 ){
        CTextStack_format(url,"?");
    }
    CTextStack_free(test_inclusion);
    if(size >= 1){
        CRequestKeyVal  *current = self->private_paramns->elements[0];
        CTextStack_format(url,"%s=%s",current->key,current->value);
    }
    if(size == 1){
        return url;
    }

    for(int i = 1;i <size; i++){
        CRequestKeyVal  *current = self->private_paramns->elements[i];
        CTextStack_format(url,"&%s=%s",current->key,current->value);
    }
    return url;


}


bool CRequest_valid_cache_file(CRequest *self,const char *file){

    if(!self->cache_time){
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