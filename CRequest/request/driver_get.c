//
// Created by mateusmoutinho on 05/09/23.
//
unsigned char * CRequest_get_any(CRequest *self,long *size,bool *is_binary){
    dtw_create_dir_recursively(self->cache_location);
    CTextStack *comand = newCTextStack_string_empty();

    if(self->use_native_curl){
        CTextStack_format(comand,"curl");
    }
    else{
        #ifdef __linux__
                CTextStack_format(comand,"./%s",self->binary_location);
        #elif _win32
                CTextStack_format(comand,"%s",self->binary_location);
        #endif
    }

    CTextStack_format(comand, " %s", self->private_url);

    if(self->private_paramns->size){
        if(!dtw_ends_with(self->private_url, "?")){
            CTextStack_format(comand,"?");
        }

        for(int i = 0; i < self->private_paramns->size; i++){
            CRequestKeyVal  *current = self->private_paramns->elements[i];
            CTextStack_format(comand,"&%s=%s",current->key,current->value);
        }
    }
    for(int i = 0; i < self->private_headers->size; i++){
        CRequestKeyVal  *current = self->private_headers->elements[i];
        CTextStack_format(comand," -H \"%s:%s\"",current->key,current->value);
    }

    CTextStack_format(comand, " -X %s", self->method);


    if(self->private_body_file){
        CTextStack_format(comand, " -d %s", self->private_body_file);
    }
    char * body_path = NULL;

    if(self->private_body){
        body_path = CRequest_get_cache_body_location(self);
        if(!CRequest_valid_cache_file(self,body_path)){
            dtw_write_any_content(body_path,self->private_body,self->private_body_size);
        }
        CTextStack_format(comand, " -d %s", body_path);
    }

    char *location = CRequest_get_cache_response_location(self);
    CTextStack_format(comand," -L -o  %s",location);
    printf("comando :%s\n",comand->rendered_text);

    system(comand->rendered_text);
    CTextStack_free(comand);

    unsigned  char *result = dtw_load_any_content(location,size,is_binary);
    free(location);
    if(body_path){
        free(body_path);
    }
    return result;
}