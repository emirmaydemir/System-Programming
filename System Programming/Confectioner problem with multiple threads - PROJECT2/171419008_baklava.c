#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <ctype.h>
#include <stdbool.h>

#define Num 1

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;

char *buffer;
int count = 0;
char *malzemeler;   
FILE *fp;
char* file_name; // dosya adını tutan değişken
int res; //dosyadaki harf sayısını tutan değişken
bool S = false, U = false, F = false, G = false;
int say = 0;
int usta_num=0;

void* producer(void* args) { // bu fonksiyonun içerisinde usta numarası belirleniyor ve hangi malzemenin alındığı belirleniyor
    while (1) {
    
     if(count >= res || count < 0){
        	exit(0);
        }
        // Produce
      if((malzemeler[count] == 'S' && malzemeler[count+1] == 'U') || (malzemeler[count] == 'U' && malzemeler[count+1] == 'S')){
		usta_num=1;
	}
	if((malzemeler[count] == 'S' && malzemeler[count+1] == 'F') || (malzemeler[count] == 'F' && malzemeler[count+1] == 'S')){
		usta_num=2;
	}
	if((malzemeler[count] == 'S' && malzemeler[count+1] == 'G') || (malzemeler[count] == 'G' && malzemeler[count+1] == 'S')){
		usta_num=3;
	}
	if((malzemeler[count] == 'U' && malzemeler[count+1] == 'F') || (malzemeler[count] == 'F' && malzemeler[count+1] == 'U')){
		usta_num=4;
	}
	if((malzemeler[count] == 'U' && malzemeler[count+1] == 'G') || (malzemeler[count] == 'G' && malzemeler[count+1] == 'U')){
		usta_num=5;
	}
	if((malzemeler[count] == 'F' && malzemeler[count+1] == 'G') || (malzemeler[count] == 'G' && malzemeler[count+1] == 'F')){
		usta_num=6;
	}
        sleep(1);


        sem_wait(&semEmpty); // bunun ile producer fonka kilit koyuyoruz
        pthread_mutex_lock(&mutexBuffer); // bunun ile producerlerin kendi arasındaki yarışını engelliyoruz

         printf("toptancı %c ve %c teslim etmektedir\n",malzemeler[count],malzemeler[count+1]);
         count++;
          
	if(S == true && U == true && F == false && G == false){
	say = 0;
	printf("usta1 baklavayı hazırlıyor\n");
	printf("usta1 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta1 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == true && U == false && F == true && G == false){
	say = 0;
	printf("usta2 baklavayı hazırlıyor\n");
	printf("usta2 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta2 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == true && U == false && F == false && G == true){
	say = 0;
	printf("usta3 baklavayı hazırlıyor\n");
	printf("usta3 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta3 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == false && U == true && F == true && G == false){
	say = 0;
	printf("usta4 baklavayı hazırlıyor");
	printf("usta4 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta4 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == false && U == true && F == false && G == true){
	say = 0;
	printf("usta5 baklavayı hazırlıyor\n");
	printf("usta5 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta5 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == false && U == false && F == true && G == true){
	say = 0;
	printf("usta6 baklavayı hazırlıyor\n");
	printf("usta6 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta6 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}	
        pthread_mutex_unlock(&mutexBuffer); //kilidi açtık artık başka producer gelebilir
        sem_post(&semFull); //kilidi açtık artık başka consumer gelebilir
        //printf("urettt %d\n", x);
        sleep(1);
    }
}

void* consumer(void* args) { // bu fonksiyonda malzeme türüne göre usta belirlenir ve malzemesi tamamlanmış ustaların bilgileri ekrana çıktı olarak gelir.
    while (1) {
    if(count >= res || count < 0){
        	exit(0);
        }
        
        int y;
	if((malzemeler[count] == 'S' && malzemeler[count+1] == 'U') || (malzemeler[count] == 'U' && malzemeler[count+1] == 'S')){
		usta_num=1;
	}
	if((malzemeler[count] == 'S' && malzemeler[count+1] == 'F') || (malzemeler[count] == 'F' && malzemeler[count+1] == 'S')){
		usta_num=2;
	}
	if((malzemeler[count] == 'S' && malzemeler[count+1] == 'G') || (malzemeler[count] == 'G' && malzemeler[count+1] == 'S')){
		usta_num=3;
	}
	if((malzemeler[count] == 'U' && malzemeler[count+1] == 'F') || (malzemeler[count] == 'F' && malzemeler[count+1] == 'U')){
		usta_num=4;
	}
	if((malzemeler[count] == 'U' && malzemeler[count+1] == 'G') || (malzemeler[count] == 'G' && malzemeler[count+1] == 'U')){
		usta_num=5;
	}
	if((malzemeler[count] == 'F' && malzemeler[count+1] == 'G') || (malzemeler[count] == 'G' && malzemeler[count+1] == 'F')){
		usta_num=6;
	}
    

        sem_wait(&semFull); // bunun ile producer fonka kilit koyuyoruz
        pthread_mutex_lock(&mutexBuffer); // consumerler arası yarış için kili koyuyoruz
         if(malzemeler[count] == 'S' && S!=true){
        	S = true;
        	printf("usta%d %c yi aldı ve count = %d\n", usta_num, malzemeler[count], count);
        	printf("toptancı baklavayı bekliyor\n");
        	        count++;

        }
        if(malzemeler[count] == 'U' && U!=true){
        	U = true;
        	printf("usta%d %c yi aldı ve count = %d\n", usta_num, malzemeler[count], count);
        	printf("toptancı baklavayı bekliyor\n");
        	        count++;

        }
        if(malzemeler[count] == 'F' && F!=true){
        	F = true;
        	printf("usta%d %c yi aldı ve count = %d\n", usta_num, malzemeler[count], count);
        	printf("toptancı baklavayı bekliyor\n");
        	        count++;

        }
        if(malzemeler[count] == 'G' && G!=true){
        	G = true;
        	printf("usta%d %c yi aldı ve count = %d\n", usta_num, malzemeler[count], count);
        	printf("toptancı baklavayı bekliyor\n");
        	        count++;

        }

          
	if(S == true && U == true && F == false && G == false){
	say = 0;
	printf("usta1 baklavayı hazırlıyor\n");
	printf("usta1 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta1 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == true && U == false && F == true && G == false){
	say = 0;
	printf("usta2 baklavayı hazırlıyor\n");
	printf("usta2 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta2 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == true && U == false && F == false && G == true){
	say = 0;
	printf("usta3 baklavayı hazırlıyor\n");
	printf("usta3 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta3 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == false && U == true && F == true && G == false){
	say = 0;
	printf("usta4 baklavayı hazırlıyor");
	printf("usta4 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta4 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == false && U == true && F == false && G == true){
	say = 0;
	printf("usta5 baklavayı hazırlıyor\n");
	printf("usta5 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta5 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}
	if(S == false && U == false && F == true && G == true){
	say = 0;
	printf("usta6 baklavayı hazırlıyor\n");
	printf("usta6 baklavayı toptancıya teslim etti\n");
	printf("toptancı baklavayı aldı ve satmaya gitti\n");
	printf("usta6 un ve fıstık için bekliyor\n");
	S = false; U = false; F = false; G = false;
	}	
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);


    
        sleep(1);
    }
}

int findsize(){ // bu fonksiyonda dosyadaki malzeme sayısını buluyorum.
	FILE *fp = fopen(file_name, "r");
	 char c;
	 int sayac=-1;
	if(fp == NULL){
		fprintf(stderr,"HATA: %s dosya acilamiyor\n", file_name);
		return -1;
	}
	do{
          c = fgetc(fp);
          if(isspace(c) == 0){
    	  sayac = sayac + 1;
    	  }
         //strcat(malzemeler, &d);
         //if(c != '\0' && c != '\n')
         //strcpy(malzemeler,c);
         //malzemeler[sayac] = d;
         
    } while( c != EOF );
	fclose(fp);
	return sayac;

}

void readfile(){ //dosyadan okuduğum verileri bir pointer içerisine atıyorum
	FILE *fp = fopen(file_name, "r");
	char c;
	int sayac=-1;
	if(fp == NULL){
		fprintf(stderr,"HATA: %s dosya acilamiyor\n", file_name);
	}
	do{
          c = fgetc(fp);
          if(isspace(c) == 0){
          sayac = sayac + 1;
    	  malzemeler[sayac] = c;
    	  }
         //strcat(malzemeler, &d);
         //if(c != '\0' && c != '\n')
         //strcpy(malzemeler,c);
         //malzemeler[sayac] = d;
         
    } while( c != EOF );
    
    fclose(fp);  
}

int main(int argc, char* argv[]) {
     srand(time(NULL));
     if(argc < 2){
     fprintf(stderr,"Lütfen argüman giriniz ./171419008_baklava.c filename \n");
     exit(0);
    }
    if(argc > 2){
     fprintf(stderr,"Lütfen birden fazla argüman girmeyiniz \n");
     exit(0);
    }
    printf("usta1 Süt ve Un için beklemektedir.\n");    
    printf("usta2 Süt ve Fıstık için beklemektedir.\n");    
    printf("usta3 Süt ve şeker için beklemektedir.\n");   
    printf("usta4 Un ve Fıstık için beklemektedir.\n"); 
    printf("usta5 Un ve Şeker için beklemektedir.\n");
    printf("usta6 Fıstık ve Şeker için beklemektedir.\n");
    pthread_t tedarik[6], th[1]; 
    pthread_mutex_init(&mutexBuffer, NULL);
    file_name = argv[1];
    res = findsize();
    sem_init(&semEmpty, 0, 2);
    sem_init(&semFull, 0, 2);
    int i;
    
   
    // malloc ile dosyadaki malzeme sayısı kadar yer ayırıyorum.
    malzemeler = malloc(sizeof(char)*(res));
    buffer = malloc(sizeof(char)*(res));
    if(!malzemeler){
	fprintf(stderr,"Bellek tahsis hatası\n");
    }
    
    readfile();
    
    //tedarikçi ve usta threadlerin oluşturulması
    for (i = 0; i < 1; i++) {
       
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                fprintf(stderr,"Thread oluşturulamadı\n");
            }
        } 
         for (i = 0; i < 6; i++) {
       
            if (pthread_create(&tedarik[i], NULL, &consumer, NULL) != 0) {
                fprintf(stderr,"Thread oluşturulamadı\n");
            }
        } 
        
    
    for (i = 0; i < 1; i++) {
        if (pthread_join(th[i], NULL) != 0) {
          fprintf(stderr,"Thread oluşturulamadı\n");
        }
    }
    
     for (i = 0; i < 6; i++) {
        if (pthread_join(tedarik[i], NULL) != 0) {
          fprintf(stderr,"Thread oluşturulamadı\n");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    free(malzemeler);
    free(buffer); // bellekteki alanı serbest bırakıyorum.
    return 0;
}
