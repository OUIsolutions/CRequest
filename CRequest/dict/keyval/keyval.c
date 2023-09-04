

CRequestKeyVal *newCRequestKeyVal(const char *key, const char *value){
    CRequestKeyVal *self =  (CRequestKeyVal*) malloc(sizeof (CRequestKeyVal));
    self->key = strdup(key);
    self->value = strdup(value);
    return self;
}

void CRequestKeyVal_represent(CRequestKeyVal *self){
    printf("\"%s\":\"%s\"",self->key,self->value);
}
