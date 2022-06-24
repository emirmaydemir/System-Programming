#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

// Emir Muhammet Aydemir 171419008  (Parametre olarak n sayısını alarak pi sayısını threadler yardımıyla hesaplayan program)
// Bu programda leibniz seri açılımını kullandım. Bu açılım ile pi sayısının tam olarak doğru hesaplanması için 500000 iterasyon gerekmektedir. Ancak sistemde max 32750 thread tanımlayabildiğimiz
//için %100 doğru bir sonuç elde etmemiz mümkün değildir. 32750 iterasyon ile 3.141623 degeri elde edilmektedir daha iyi sonuclar icin daha fazla iterasyon gerekmektedir. (PROGRAM İÇERSİNİDEKİ N DEĞERİ LEIBNIZ SERİSİNDEKİ İTERASYON SAYISINI BELİRLEMEKTEDİR)


double pi = 0; // pi degerinin global olarak tanimliyorum
//pthread_mutex_t lock;
sem_t semap; // threadlerin birbirlerini beklemesi için semaphore kullanıyorum bu sayede threadler kritik bölge içerisindek threadi bekleyerek sırayla çalışacaklar.

	//pthread_mutex_lock(&lock);
	//pthread_mutex_unlock(&lock);
void* pi_calculate(void *arg){ // bu fonksiyona sırayla gelen her bir thread pi değerini hesaplamam için bir iterasyon yapmaktadır. Yani 1 thread = 1 iterasyon

	int id = *(int *)arg; // threadin id değerini integere çeviriyorum
	int sign=1;  // eğer thread id si tek ise formül üçün değişkenimi negatif yapıyorum. Eğer th id si çift ise yine formül için pozitif yapıyorum.
	printf("thread %d\n", *(int *)arg);
	
	if (id % 2 == 0) //Eğer th id si çift ise formül için pozitif yapıyorum.
		sign = 1;
		
	else //Eğer thread id si tek ise formül için değişkenimi negatif yapıyorum.
		sign = -1;
	//pthread_mutex_lock(&lock);	
	
	pi =pi + (4*((double)sign / (2 * id + 1))); // 1 iterasyonu gerçekleştiren formülüm çıkan tüm sonuçları topluyorum ve böylece pi sayısına her iterasyonda daha çok yaklaşıyorum.
	
	//pthread_mutex_unlock(&lock);
	printf("hesaplanan pi degeri %lf\n",pi); // hesaplanan pi değeri
	sem_post(&semap); // threadin işi bitince semaphor üzerindeki kilidi kaldırıyorum.

}



int main(int argc, char* argv[]) {

if( argc != 2) // hatalı parametre girişi yapılırsa doğrusunu gösteren usage
{
printf("lutfen programi calistirirken sadece 1 adet parametre giriniz!!!\n");  // kullanıcıyı n değerini girmesi için uyarıyorum.
return 0;
}

int n = atoi(argv[1]); // kullanicinin girdigi parametre degerini integere çeviriyorum
int error; // thread oluşturulurken hata olup olmadığını bu değişken ile kontrol edeceğim
printf("n degeri %d\n",n); // kullanıcının  girdiği n değerniin ekrana yazdırıyorum
pthread_t tid[n]; // kullanıcının girdiği n sayısı kadar thread id oluşturuyorum
int number[n]; // her id nin değerini atamaç için oluşturduğum dizi



for(int i = 0; i<n; i++){
	number[i] = i;  // her thread id değerine karşılık integer değer ataması yapıyorum pi değeri hesaplanırken bu değerleri kullanacağım.
}

/*if(pthread_mutex_init(&lock, NULL) !=0){
	printf("\nhata\n");
	return 1;
}*/

for(int i = 0; i<n; i++){   // bu for döngüsü içerisinde threadlerimi oluşturuyorum. Kullanıcının girdiği n değeri kadar thread oluşuyor ve n iterasyon sonucu pi değeri hesaplanıyor.
	error = pthread_create(&(tid[i]), NULL, pi_calculate, (void*)&number[i]);  // ilk parametre thread id si, ikincisi argüman, üçüncüsü thread oluşunca gidilecek fonksiyon ve sonuncusu ise fonksiyona gönderilecek parametredir.
	if(error != 0){ // olusturulan threadler 32750 adetten fazlaysa ekrana uyarı mesajı veriyorum iterasyon max 32750 olmalıdır.
		printf("en fazla 32750 adet thread olusturabilirsiniz lutfen n degerini 32750 olarak ayarlayin hata kodu = %d\n",error);
		return 1;	
	}
	sem_wait(&semap); // thread oluşturulduğunda diğer threadlerin bunu beklemesi için semaphore kullandım.
	//sleep(0.5);

}

for(int i = 0; i<n; i++){
	pthread_join(tid[i], NULL);	// programın bitmeden önce threadlerin bitmesini beklemesi için join kullandım.
}
//pthread_mutex_destroy(&lock);
return 0; // program sonu.

}
