

#define CREQUEST_NOT_RESPOND 1
#define CREQUEST_NOT_A_STRING 2
#define CREQUEST_NOT_VALID_JSON 3


typedef struct CRequest{

    const char * binary_location;
    const char *method;
    char *url;
    CRequestDict  *paramns;
    CRequestDict  *headers;

    bool error_code;
    char *error_menssage;

    char *body;

}CRequest;

CRequest newCRequest(const char *url);


void CRequest_set_param(CRequest *self,const char *key, const char *value);

void CRequest_set_headder(CRequest *self,const char *key, const char *value);

void CRequest_set_body(CRequest *self,const char *body);

void CRequest_set_json(CRequest *self,cJSON *body);


unsigned char * CRequest_get_binary(CRequest *self,long *size);

char * CRequest_get_string(CRequest *self);

cJSON *CRequest_get_json(CRequest *self);

void CRequest_represent(CRequest *self);

