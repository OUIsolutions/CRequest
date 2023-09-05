

CRequestDict * newCRequestDict(){

    CRequestDict *self = (CRequestDict*) malloc(sizeof (CRequestDict));
    self->elements = malloc(0);
    self->size = 0;
    return self;

}

void CRequestDict_set_element(CRequestDict *self,const char *key, const char *value){

    self->elements = (CRequestKeyVal**)realloc(
            self->elements,
            (self->size +1) * sizeof(CRequestKeyVal**)
    );

    self->elements[self->size] = newCRequestKeyVal(key,value);
    self->size+=1;

}

void CRequestDict_represent(CRequestDict *self){
    for (int i = 0; i < self->size; ++i) {
        CRequestKeyVal_represent(self->elements[i]);
        printf("\n");
    }
}

void CRequestDict_free(CRequestDict *self){
    for (int i = 0; i < self->size; ++i) {
        CRequestKeyVal_free(self->elements[i]);
        printf("\n");
    }
    free(self->elements);
    free(self);

}