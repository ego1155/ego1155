#!/bin/sh

# If running on bash for Windows, any argument starting with a forward slash is automatically
# interpreted as a drive path. To stop that, you can prefix with 2 forward slashes instead
# of 1 - but in the specific case of openssl, that causes the first CN segment key to be read as
# "/O" instead of "O", and is skipped. We work around that by prefixing with a spurious segment,
# which will be skipped by openssl
function fixup_cn_subject() {
    local result="${1}"
    case $OSTYPE in
        msys|win32) result="//XX=x${result}"
    esac
    echo "$result"
}
# Usage example
#MY_SUBJECT=$(fixup_cn_subject "/C=GB/CN=foo")

set -e

curDir=$(pwd)

mkdir -p cert
cd cert
rm -rf *
#SUBJ_CA="/C=IN/ST=Gujrat/L=Ahmedabad/O=Pfxwall/CN=Pfxwall"
#SUBJ_SRV="/C=IN/ST=Gujrat/L=Ahmedabad/O=MakeInIndia/CN=MadeInIndia"
SUBJ_CA=$(fixup_cn_subject "/C=IN/ST=Gujrat/L=Ahmedabad/O=SunComputers/CN=SunComputers")
SUBJ_SRV=$(fixup_cn_subject "/C=IN/ST=Gujrat/L=Ahmedabad/O=MakeInIndia/CN=MadeInIndia")

DAYS=$((365 * 100))
openssl req -x509 -newkey rsa:4096 -days $DAYS -keyout ca-key.pem -out ca-cert.pem -nodes -subj $SUBJ_CA
#openssl x509 -in ca-cert.pem -noout -text
openssl req -newkey rsa:4096 -keyout server-key.pem -out server-req.pem -nodes -subj $SUBJ_SRV
openssl x509 -req -in server-req.pem -days $DAYS -CA ca-cert.pem -CAkey ca-key.pem -CAcreateserial -out server-cert.pem
openssl verify -CAfile ca-cert.pem server-cert.pem
cat ca-key.pem > ca.pem; cat ca-cert.pem >> ca.pem
cat server-key.pem > server.pem; cat server-cert.pem >> server.pem
openssl verify -CAfile ca.pem server.pem
cd ..
cp -fv cert/ca.pem $curDir/Sources/cert/ca.pem
cp -fv cert/server.pem $curDir/Sources/cert/server.pem
rm -rf cert/

cd $curDir

exit 0