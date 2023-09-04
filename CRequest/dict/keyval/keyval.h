

typedef struct CRequestKeyVal{
    char *key;
    char *value;
}CRequestKeyVal;

CRequestKeyVal *newCRequestKeyVal(const char *key, const char *value);

void CRequestKeyVal_represent(CRequestKeyVal *self);