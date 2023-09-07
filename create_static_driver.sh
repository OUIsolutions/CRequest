
export CC=clang
export CFLAGS=-static
cd curl curl-8.2.1
./configure --prefix=/home/mateusmoutinho/Documentos/OUI/CRequest/output  --with-openssl
make 
make install 