export CC="clang"
export CFLAGS="-all-static "
export LIBS="  -lcurl -lssl -lcrypto -ldl -lm -lz "
cd curl
 rm -r curl-8.2.1
unzip curl-8.2.1.zip
cd curl-8.2.1
chmod +x ./configure

./configure --enable-static   --with-openssl --prefix=/home/mateusmoutinho/Documentos/OUI/CRequest/curl/output
make
make install