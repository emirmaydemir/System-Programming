#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

// Emir Muhammet Aydemir 171419008 BLM3010 Sistem Programlama Proje1 Kelime Sayma Programı

static void stdin_calculate(size_t *line, size_t *word, size_t *letter) { // stdinden okuma işlemini gerçekleştiren fonksiyon
        int space = 0; // kelimeyi sayısını alırken boşluk karakterini de dikkate alıyorum. Ancak birden fazla boşluk olursa gereksiz yere kelime sayısıda artıyordu bunun önüne geçmek için birden fazla boşluk olma durumunu kontrol eden bir değişken oluşturdum.
    	int firstword = 0; // ilk karakterim boşluk olursa bunu kelime olarak sayıyordu bunun önüne geçmek için bunu kontrolünü sağlayan bir değişken oluşturdum.
    	char ch; // dosyadan okuduğum her karakteri içerisine attığım değişken.
    	while (read(0,&ch,1)) // stdinden her seferinde 1 karakter okuduğum döngü
    {
        ++*letter; // döngü her döndüğünde karakter sayısını 1 arttırıyorum.
        
       if(isspace(ch)){ // eğer gelen karakter boşluk ise space değişkenimi arttırıyorum birden fazla boşluğu kelime olarak algılamasın diye kullanacağım spaceyi
         space++;
       }
       else{ 
           space = 1;  // gelen değer boşluk değilse space değişkenimi resetliyorum  
           firstword = 1; // ilk karakterin boşluk olup olmadığının kontrolü için
       }
       
       if(firstword != 1)
            continue; // dosyanın başlangıcında boşluk varsa ilk harfe gelene kadar döngüyü başa sarıyorum

        if (ch == '\n' || ch == '\0') // eğer \n yani alt satıra geçme veya \0 yani dosya sonunu belirten karaktere rastlarsam satır değişkenimi arttırıyorum.
             ++*line;

        if (isspace(ch) && space < 3) // eğer boşluk, tab, satır atlama veya dosya sonunu belirten karakterlerden birine rastlarsam kelime değikenimi
            ++*word;
    }
    }

static void calculate(const char *filename, size_t *line, size_t *word, size_t *letter, int *file_ex) { // terminalden gelen dosyanın satır, kelime ve karakter sayısını bulan fonksiyon

    FILE *file = (filename && filename[0] == '-') ? stdin : fopen(filename, "r"); // fonksiyonuma parametre olarak gelen dosyayı okuma modunda açıyorum
    if (file == NULL) { // dosya bulunamadıysa ilgili hata mesajını döndürüyorum
        fprintf(stderr,"HATA: %s dosya acilamiyor\n", filename);
        *file_ex = 0; // dosya bulunamadıysa ekrana boş yere satır, kelime ve karakter bilgisi için 0,0,0 yazmasın diye kontrol amaçlı kullandığım değişkeni 0 yapıyorum.
        return;
    }
    int space = 0; // kelimeyi sayısını alırken boşluk karakterini de dikkate alıyorum. Ancak birden fazla boşluk olursa gereksiz yere kelime sayısıda artıyordu bunun önüne geçmek için birden fazla boşluk olma durumunu kontrol eden bir değişken oluşturdum.
    int firstword = 0; // ilk karakterim boşluk olursa bunu kelime olarak sayıyordu bunun önüne geçmek için bunu kontrolünü sağlayan bir değişken oluşturdum.
    char ch; // dosyadan okuduğum her karakteri içerisine attığım değişken.
     while ((ch = fgetc(file)) != EOF)  // fgetc ile karakter karakter dosyanın sonuna kadar okuyorum.
    {
        ++*letter; // döngü her döndüğünde karakter sayısını 1 arttırıyorum.
        
       if(isspace(ch)){ // eğer gelen karakter boşluk ise space değişkenimi arttırıyorum birden fazla boşluğu kelime olarak algılamasın diye kullanacağım spaceyi
         space++;
       }
       else{
           space = 1;   // gelen değer boşluk değilse space değişkenimi resetliyorum
           firstword = 1; // ilk karakterin boşluk olup olmadığının kontrolü için
       }
       
       if(firstword != 1)
            continue; // dosyanın başlangıcında boşluk varsa ilk harfe gelene kadar döngüyü başa sarıyorum

        
        if (ch == '\n' || ch == '\0') // eğer \n yani alt satıra geçme veya \0 yani dosya sonunu belirten karaktere rastlarsam satır değişkenimi arttırıyorum.
            ++*line;

        if (isspace(ch) && space < 3) // eğer boşluk, tab, satır atlama veya dosya sonunu belirten karakterlerden birine rastlarsam kelime değikenimi arttırıyorum.
            ++*word;
    }
    fclose(file); // işlemlerim bitince dosyamı kapatıyorum.
}

static void show(const char *filename, size_t line_total, size_t word_total, size_t letter_total, bool w, bool c, bool l, int file_ex) { // toplam satır, kelime ve karakter sayısını gösteren fonksiyon
    if(file_ex == 0) // dosya bulunamadıysa ekrana çıktı vermeden çıkmamı sağlayan şart bloğu
    	return;
    else if(w && c && l) // satır, kelime ve karakter bilgilerinin hepsini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu %5lu %5lu\n", filename, line_total, word_total, letter_total);
    else if(w && c && !l) // kelime ve karakter bilgilerini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu %5lu\n", filename, word_total, letter_total);
    else if(w && !c && l) // kelime ve satır bilgilerini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu %5lu\n", filename, line_total, word_total);
    else if(w && !c && !l) // kelime bilgisini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu\n", filename, word_total);
    else if(!w && c && l) // satır ve karakter bilgilerini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu %5lu\n", filename, line_total, letter_total);
    else if(!w && !c && l) // satır bilgisini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu\n", filename, line_total);
    else if(!w && c && !l) // karakter bilgisini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu\n", filename, letter_total); 
    else // hiç bir parametre girilmediyse satır, kelime ve karakter bilgilerinin hepsini göstermemi sağlanayan şart bloğu
    	printf("%s %2lu %5lu %5lu\n", filename, line_total, word_total, letter_total); 
}

int main(int argc, char* argv[]) {
    size_t line_total = 0; // birden fazla dosya veya stdin olursa diye toplam satır sayısını tutan değişken
    size_t word_total = 0; // birden fazla dosya veya stdin olursa diye toplam kelime sayısını tutan değişken
    size_t letter_total = 0; // birden fazla dosya veya stdin olursa diye toplam karakter sayısını tutan değişken
    bool w,c,l; // -w, -c veya -l parametre girişi yapılmış mı kontrolünü sağlayan değişkenler
    int file_ex=1; // girilen dosya bulunamadıysa ekranda satır kelime ve kararkter bilgileri 0,0,0 şeklinde yazıyordu. Bunun önüne geçmek için bu değişken ile kontrol sağlayarak dosya bulunamadıysa değer bastırmadan fonksiyonumu return ediyorum.
    w = c = l = false; // başlangıçta hiç bir parametre girilmediğini varsayıyorum.
    bool first_param = false; // sadece parametre girişi yapılırsa programı standart girişe yönlendirmek için kullandığım değişken.
    /*if (argc < 2) {
        puts("Dogru kullanim: ./ks filename");
        return 0;
    }*/
    
    if(argc > 1){   // 1'den fazla argüman girildiyse döngü ile tüm argümanları okumak için şart bloğu koyuyorum
    
     for (int i=1; i < argc; ++i) {  // Bu for döngüsünün amacı kullanıcı girişlerinden sadece -w, -c ve -l parametrelerini ayıklamak diğer giriş bilgilerini bir sonraki for döngüsünde okuyorum.
        if(strcmp(argv[i],"-w") == 0){ // eğer kullanıcı -w parametresini girdiyse w değişkenimi true yapıyorum
        	w = true;
        }
        else if(strcmp(argv[i],"-c") == 0){ // eğer kullanıcı -c parametresini girdiyse c değişkenimi true yapıyorum
        	c = true;
        }
        else if(strcmp(argv[i],"-l") == 0){ // eğer kullanıcı -l parametresini girdiyse l değişkenimi true yapıyorum
        	l = true;
        }
        }
        
     for (int i=1; i < argc; ++i) { // bu for döngüsünün amacı -w, -c ve -l dışında kalan girişleri dosya ise açmak + ise stdin girişine bakmasını sağlamaktır. Hatalı girişler için gerekli uyarılar sağlanmıştır.
     //printf("%s\n", argv[i]);
         size_t line = 0; // o an ki okunan dosyanın satır bilgisini tutan değişkenim fonksiyona parametre olarak gönderiyorum.
         size_t word = 0; // o an ki okunan dosyanın kelime bilgisini tutan değişkenim fonksiyona parametre olarak gönderiyorum.
         size_t letter = 0; // o an ki okunan dosyanın karakter bilgisini tutan değişkenim fonksiyona parametre olarak gönderiyorum.
         file_ex=1; // dosyanın bulunup bulunamadığının kontrolünü sağladığım değişken.
         if(strcmp(argv[i],"-w") == 0){  // eğer parametre girişi yapılmışsa bunu fonksiyona gönderip kodu bozmasın diye döngüyü başa sarıyorum bunun kontrolünü ilk for döngümde yapmıştım.
        	continue;
        }
        else if(strcmp(argv[i],"-c") == 0){ // eğer parametre girişi yapılmışsa bunu fonksiyona gönderip kodu bozmasın diye döngüyü başa sarıyorum bunun kontrolünü ilk for döngümde yapmıştım.
        	continue;
        }
        else if(strcmp(argv[i],"-l") == 0){ // eğer parametre girişi yapılmışsa bunu fonksiyona gönderip kodu bozmasın diye döngüyü başa sarıyorum bunun kontrolünü ilk for döngümde yapmıştım.
        	continue;
        }
        else if(strcmp(argv[i],"+") == 0){ // eğer kullanıcı + girişi yapmışsa stdin den okuması için stdin_calculate fonksiyonuma yönlendiriyorum. Sonrasında + değerini dosya sanıp okumasın diye döngüyü başa sarıyorum.
        	first_param = true; // 2.kez standart girişe gitmesini engelliyorum.
        	stdin_calculate(&line, &word, &letter);
        	show("-stdin- ", line, word, letter, w, c, l, 1);
        	line_total += line;
        	word_total += word;
        	letter_total += letter;
        	continue;
        }
        else if(argv[i][0] == '-'){ // kullanıcı hatalı parametre girişi yaptıysa ekrana uyarı mesajı verip 2 ile çıkış yapıyorum.
         fprintf(stderr, "HATA: bilinmeyen secenek %s \n", argv[i]);
         exit(2);
         }
        first_param = true; // 2.kez standart girişe gitmesini engelliyorum.
        calculate(argv[i], &line, &word, &letter, &file_ex); // her döngü de gelen dosyayı alıp ilgili satır, kelime ve karakter sayısını bulan fonksiyonuma gönderiyorum. file_ex ile dosyanın geçerli olup olmadığının kontrolünü sağlıyorum.
        show(argv[i], line, word, letter, w, c, l, file_ex);// her döngü de gelen dosyayı alıp ilgili satır, kelime ve karakter sayısını ekrana yazdıran fonksiyonuma gönderiyorum. file_ex ile dosyanın geçerli olup olmadığının kontrolünü sağlıyorum.
        line_total += line; // her döngü sonunda bulduğum satır sayısını toplam satır sayısına ekliyorum
        word_total += word; // her döngü sonunda bulduğum kelime sayısını toplam kelime sayısına ekliyorum
        letter_total += letter; // her döngü sonunda bulduğum karakter sayısını toplam karakter sayısına ekliyorum
    }
    }
    else{ // eğer argüman sayısı 1'den küçükse stdin den okumam gerektiği anlamına gelir o yüzden stdin_calculate fonksiyonuma yönlendiriyorum.
    	first_param = true; // 2.kez standart girişe gitmesini engelliyorum.
     	size_t line = 0;
        size_t word = 0;
        size_t letter = 0;
        stdin_calculate(&line, &word, &letter);
    	show("-stdin- ", line, word, letter, w, c, l, 1);
    }
    if(!first_param){ // sadece parametre girişi yapılırsa programı standart girişe yönlendiriyorum
    	size_t line = 0;
        size_t word = 0;
        size_t letter = 0;
        stdin_calculate(&line, &word, &letter);
    	show("-stdin- ", line, word, letter, w, c, l, 1);
    }
   
    if (argc > 2) { // eğer birden fazla argüman girilmişse toplam değerini ekranda gösterebilmek adına tüm satır, kelime ve karakter bilgilerinin toplamını gösteren fonksiyonumu çağırıyorum. 
        show("toplam", line_total, word_total, letter_total, w, c, l, 1);
    }
}
