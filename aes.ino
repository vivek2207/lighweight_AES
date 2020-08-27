#include<AES.h>

AES aes;

byte key[]=

{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  };

  byte plain[ ]=
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    /* 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//t,h,i,s,i,s,e,x,a,m,p,l,e,f,o,r,
   0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//t,h,e,e,n,c,r,y,p,t,i,o,n,a,n,d,
   0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//d,e,c,r,y,p,t,i,o,n,p,l,e,a,s,e,
   0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//p,r,o,v,e,t,h,i,s,i,s,c,o,r,r,e,
   */ };

    byte my_iv[]=
    {
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,//t,h,i,s,i,s,i,n,i,t,i,a,l,v,e,c
      };

      byte cipher [4*N_BLOCK];
      byte check [4*N_BLOCK];


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.begin(57600);
  Serial.print("testing mode");
  prekey_test();

}


void prekey(int bits, int blocks)
{
  byte iv[N_BLOCK];
  long t0=micros();
  byte succ=aes.set_key(key, bits);
  long t1=micros()-t0;
  Serial.print("SET_KEY");
  //Serial.println("SET_KEY");
  Serial.print(" bits ");
  Serial.print("-> ");
  Serial.print((int) succ);
  Serial.print(" took ");
  Serial.print(" t1 ");
  Serial.println(" us ");
  
  t0=micros();

  if(blocks==1)
  succ=aes.encrypt(plain, cipher);

  else{
    for(byte i=0; i<16; i++)
      iv[i]=my_iv[i];
    succ=aes.cbc_encrypt (plain, cipher, blocks, iv);   
    }
  t1=micros()-t0;

  Serial.print (" encrypt ");
  Serial.print ((int) succ);
  Serial.print (" took ");
  Serial.print (t1);
  Serial.println (" us ");
  
  t0=micros();
  if(blocks==1)
    succ=aes.decrypt (cipher, plain);  
  else{
       for(byte i=0; i<16; i++)
        iv[i]=my_iv[i];
      succ=aes.cbc_decrypt (cipher, check, blocks, iv);   
    }
    t1=micros()-t0;

  Serial.print (" decrypt ");
  Serial.print ((int) succ);
  Serial.print (" took ");
  Serial.print (t1);
  Serial.println (" us ");

  for(byte ph=0; ph< (blocks==1 ? 3 :4); ph++){
    for(byte i=0; i<(ph<3 ? blocks*N_BLOCK : N_BLOCK); i++){
      byte val = ph == 0 ? plain [i]: ph==1 ? cipher [i] : ph == 2 ? check [i] :iv[i];
      Serial.print(val>>4, HEX); 
      Serial.print(val&15, HEX);
      Serial.print(" ");
      }
      Serial.println ();
    }
   } 

   void prekey_test (){
    prekey(128, 4);
    prekey(192, 3);
    prekey(256, 2);
    prekey(128, 1);
    prekey(192, 1);
    prekey(256, 1);
 }
