
export CC=clang
export CFLAGS=-static
./configure --prefix=/home/mateusmoutinho/Documentos/OUI/CRequest/output  --with-openssl
make 
make install 