//
// Created by mateusmoutinho on 05/09/23.
//
unsigned char * CRequest_get_any(CRequest *self,long *size,bool *is_binary){
    dtw_create_dir_recursively(self->cache_location);
    CTextStack *comand = newCTextStack_string_empty();
    CTextStack_format(comand, "curl %s", self->private_url);

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

    char *location = CRequest_get_cache_location(self);

    CTextStack_format(comand," -L -o  %s",location);
    printf("comando :%s\n",comand->rendered_text);

    system(comand->rendered_text);
    CTextStack_free(comand);
    free(location);
}