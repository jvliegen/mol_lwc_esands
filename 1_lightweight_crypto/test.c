#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "../2_data/random_8KiB.dat"
#define FILENAME "../2_data/random_64KiB.dat"
#define FILENAME "../2_data/random_1MiB.dat"
#define BUFFERSIZE 1024

int crypto_aead_encrypt(
  unsigned char *c, unsigned long long *clen,
  const unsigned char *m, unsigned long long mlen,
  const unsigned char *ad, unsigned long long adlen,
  const unsigned char *nsec,
  const unsigned char *npub,
  const unsigned char *k
);

int crypto_aead_decrypt(
  unsigned char *m, unsigned long long *mlen,
  unsigned char *nsec,
  const unsigned char *c, unsigned long long clen,
  const unsigned char *ad, unsigned long long adlen,
  const unsigned char *npub,
  const unsigned char *k
);


int main(void) {

  /* declare variables */
  unsigned char *plaintext;
  unsigned long long plaintext_length;
  unsigned char *plaintext_bis;
  unsigned long long plaintext_length_bis;

  unsigned char *authenticated_data;
  unsigned long long authenticated_data_length;

  unsigned char *ciphertext;
  unsigned long long *ciphertext_length;

  unsigned char *nsec;
  unsigned char *npub;
  unsigned char *key;

  unsigned char buffer[BUFFERSIZE];
  int rv, i, bytes_read, blockcounter=1;
  FILE * fh;


  /* allocate memory */
  key = (unsigned char *)malloc(16*sizeof(unsigned char));
  ciphertext = (unsigned char *)malloc(BUFFERSIZE*sizeof(unsigned char));
  ciphertext_length = (unsigned long long *)malloc(1*sizeof(unsigned long long));;
  nsec = (unsigned char *)malloc(1*sizeof(unsigned char));
  npub = (unsigned char *)malloc(1*sizeof(unsigned char));
  key = (unsigned char *)malloc(16*sizeof(unsigned char));
  *nsec = 01;
  *npub = 15;


  /* set the associated data */
  authenticated_data = "hello world";
  authenticated_data_length = (unsigned long long)(11);


  /* set the key */
  for(i=0;i<16;i++) {
    key[i] = 65 + i;
  }


  /* open the file */
  fh = fopen(FILENAME, "r");
  if(!fh) {
    printf("ERROR: Unable to open %s\n", FILENAME);
    return(1);
  }

  printf("key: \t\t\t%s\n", key);
  printf("\n");


  /* read data from file */
  rv = fread(buffer, sizeof(buffer), 1, fh); // read 10 bytes to our buffer
  while(rv) {
    printf("block counter: %d\n", blockcounter++);
    printf("\tplaintext: \t\t" );
    for(i=0;i<10;i++)
      printf("0x%02X ", buffer[i]);
    printf("...\n");


    /* Encrypt the ciphertext */
    rv = crypto_aead_encrypt(ciphertext, ciphertext_length, 
      &buffer[0], 1024, 
      authenticated_data, authenticated_data_length,
      nsec, npub, key);

    printf("\tciphertext: \t\t" );
    for(i=0;i<10;i++)
      printf("0x%02X ", ciphertext[i]);

    printf("...\n");


    /* Decrypt the ciphertext */
    rv = crypto_aead_decrypt(plaintext_bis, &plaintext_length_bis,
      nsec,
      ciphertext, *ciphertext_length, 
      authenticated_data, authenticated_data_length,
      npub, key);

    printf("\tplaintext_bis: \t\t" );
    for(i=0;i<10;i++)
      printf("0x%02X ", plaintext_bis[i]);
    printf("...\n");

    /* read new data from file */
    rv = fread(buffer, sizeof(buffer), 1, fh); // read 10 bytes to our buffer
  }


  /* close the file */
  fclose(fh);

  return 0;
}
