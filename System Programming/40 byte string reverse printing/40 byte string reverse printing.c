#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
FILE *file; // dosya pointeri
int i; // döngülerde kullanıcak değişken
//char buffer[40];
char *read; // dosyadan okunan karakterleri bunun içerisine aktaracağız
char *temp1; // stringi ters çevirmede kullanılan pointer
char *temp2; // // stringi ters çevirmede kullanılan pointer
bool counter=true; // ilk 40 byte düz sonrasını ters yazdırmak için
int meter=2; // kaçıncı 40 lık byte üzerinde olduğumuzu anlamak için

if( argc!= 2) // hatalı parametre girişi yapılırsa doğrusunu gösteren usage
{
printf("usage: %s dosyaadi\n",argv[0]);
}
read = malloc(41*sizeof(char)); // bellekte yer ayırıyoruz 40 byte
printf("okunan dosyanin adi = %s \n",argv[1]); 
file = fopen(argv[1], "r"); // dosyamı okuma modunda açıyorum

if(file == NULL) // dosyam bulunamazsa hata mesajı verip programı sonlandırıyorum
{
printf("Dosya bulunamadi Lütfen dosya adini dogru girdiginizden emin olunuz\n");
return 0;
}
printf("ilk 40 byte: ");
while(!feof(file)) // dosyamın sonuna kadar okumasını sağlıyorum
{
while(fread(read,1,40,file) !=0 ) // dosyadan okunan 40 byte lik verileri read pointeri içerisine atıyorum
{
if(counter == true) // ilk 40 byte düz yazdırmak için
{
for(i=0; i<40; i++)
{
printf("%c",read[i]);
}
printf("\n");
counter = false;
}
else // ilk 40 byte sonrasını ters yazdırmak için
{
for(temp1 = read, temp2 = read + strlen(read)-1; temp2 > temp1; ++temp1, --temp2)
{
 *temp1 ^= *temp2;
 *temp2 ^= *temp1;
 *temp1 ^= *temp2;
}
printf("%d. 40 byte: ",meter);
meter = meter +1;
printf("%s\n",read);
//printf("%zu\n",sizeof(read));
}
//read = malloc(40*sizeof(char));
}

}

fclose(file); //dosyamı kapatıyorum
free(read); //bellekte ayrılan yeri serbest bırakıyorum
return 0;
}
