#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

// AD = Emir Muhammet Aydemir 
// No = 171 419 008
// BLM3010 1 Adet parent proccess ve 2 adet child process olan bir sistemde child processlerin biri toplama diğeri ise faktöriyel hesabı yapmaktadır. Parent ise childlerin bitmesini bekleyerek işlem sonunda bitti yazacaktır.

void hesapla(int sayi)
{
	int pid = fork(); // ilk çocuğu fork ediyorum
	int i; // for döngüsü içerisinde kullancağım değişken
	int toplam=0; // ilk processin hesaplayacağı toplam değerini tutacak değişken
	long faktoriyel=1;  // ikinci proccesin hesaplayacağı faktöriyel değerini tutan değişken
	
	if( pid > 0 )
	{
		int pid2 = fork(); // ana process çalıştığında fork etmek için bu koşulu koyduk
		
	if( pid2 > 0 ) // eğer hem pid > 0 hem de pid2 > 0 ise parent processe gelmiştir sıra
	{
		//parent
		while(wait(NULL)>0); // parent process child processlerin bitmesini bekler (sadece wait(NULL)) yaptığımda bazen beklemiyordu ben de while içerisine aldım
		printf("[ID = %d] Bitti\n",getpid());
		fflush(stdout);
	}
	else if( pid2 == 0) // pid2 == 0 ise sıra 2. çocuk processtedir
	{
		for(i=2;i<=sayi;i++)		//2. child
		{
			faktoriyel = faktoriyel * i; // komut satırında kullanıcının gönderdiği parametre kadar dönen bir döngü sonucu faktöriyel hesabı
		}
		printf("[ID = %d] %d sayisinin faktoriyel degeri = %ld \n",getpid(),sayi,faktoriyel); // getpid() ile şu an da çalışan process id sini alıyorum
		
	}
	}
	else if( pid == 0) // pid == 0 ise sıra ilk çocuk processtedir
	{
		for(i=1;i<=sayi;i++)		//1. child
		{
			toplam = toplam + i; // komut satırında kullanıcının gönderdiği parametre kadar dönen bir döngü sonucu girilen değere kadar olan sayıların toplam hesabı
		}		
		printf("[ID = %d] %d'e kadar olan pozitif tam sayilarin toplami = %d \n",getpid(),sayi,toplam); // getpid() ile şu an da çalışan process id sini alıyorum
	}
}



int main(int argc, char *argv[])
{
	int x = atoi(argv[1]); // kullanıcının komut satırında girdiği argümanı integere çeviriyorum
	//printf("%d",x);
	//char c = x;
	
	
	if(x == 0){    // eğer x == 0 ise sayı girilmemiştir bu yüzden hata mesajını verip programı sonlandırıyorum
		printf("%s pozitif tam sayi degildir lutfen dogru parametre girisi yapiniz!\n", argv[1]);
		return 0;
	}
	if(x < 0){ // eğer x < 0 ise pozitif tam sayı girilmemiştir hata mesajı verip programı sonlandırıyorum
		printf("%s pozitif tam sayi degildir lutfen dogru parametre girisi yapiniz!\n", argv[1]);
		return 0;
	}
	if(x > 20){ // x > 20 ise faktöriyel işleminin sonucu long sınırlarını aşacağı için kullanıcıyı bilgilendiriyorum
	printf("%s  den buyuk degerler long sinirlarini astigi icin faktoriyel hesabi yanlis olacaktir !\n", argv[1]);
	}
	if( argc!= 2) // hatalı parametre girişi yapılırsa doğrusunu gösteren usage : birden fazla parametre girişini falan engeller
	{
		printf("usage: tek parametre giriniz\n");
		return 0;
	}
	
	hesapla(x); // toplama ve faktöriyel hesabını yapan fonksiyon
}

