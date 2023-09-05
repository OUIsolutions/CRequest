import base64
text = ''

with open('drivers/curl','rb') as arq:
    content = arq.read()
    encoded = base64.b64encode(content).decode('utf8')
    text+= '#ifdef __linux__\n'
    text+=f'\t#define CREQUEST_DRIVER "{encoded}"\n'


text+='#endif'

with open('CRequest/driver.h','w') as arq:
    arq.write(text)