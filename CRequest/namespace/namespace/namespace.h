
typedef struct CRequestNamespace{


    CRequest * (*newRequest)(const char *url);


    void (*add_query_parram)(CRequest *self, const char *key, const char *value);

    void (*add_headder)(CRequest *self, const char *key, const char *value);

    void (*set_body)(CRequest *self,unsigned char *body,long size);

    void (*set_b64_body)(CRequest *self,unsigned char *body,long size);

    void (*set_body_string)(CRequest *self,const char *body);


    void (*set_body_json)(CRequest *self,cJSON *body);


    void (*represent)(CRequest *self);
    void (*free)(CRequest *self);

}CRequestNamespace;

CRequestNamespace newCRequestNamespace();