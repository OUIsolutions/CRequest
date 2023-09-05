

typedef struct CRequestKeyVal{
    char *key;
    char *value;
}CRequestKeyVal;

CRequestKeyVal *newCRequestKeyVal(const char *key, const char *value);

void CRequestKeyVal_free(CRequestKeyVal *self);

void CRequestKeyVal_represent(CRequestKeyVal *self);