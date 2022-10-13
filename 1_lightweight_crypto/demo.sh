

wget https://csrc.nist.gov/CSRC/media/Projects/lightweight-cryptography/documents/round-2/submissions-rnd2/ace.zip
unzip ace.zip
cd ace/Implementations/crypto_aead/aceae128v1/ref


for i in *.c; do gcc -c $i; done

ar -rcs libaceae128v1.a *.o

cp libaceae128v1.a ../../../../../
cd  ../../../../../

gcc -c test.c

gcc -o test_aceae128v1 test.o -L. -laceae128v1

