

void private_CRequest_format_url(CRequest *self,CTextStack *comand);

void private_CRequest_format_headers(CRequest *self,CTextStack *comand);

void private_CRequest_format_curl_comand(CRequest *self,CTextStack *comand);



unsigned char * CRequest_get_any_response(CRequest *self, long *size, bool *is_binary);
