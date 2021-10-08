// not: soru biraz detaylı, bu yüzden ödev sitesindeki videoları izlersen çok daha rahat anlarsın.
/*
    bu programda kullanılan veri yapılarını kısaca özetlemek gerekirse;
    --> array (dizi): hafızadan "sabit" bir büyüklükte alan tahsis eder. örneğin int x[5] dediğimiz zaman 5 tane int sığacak bir alana sahip oluruz.
        bir integer da 4 byte olduğu için bize RAM'den 20 bytelık sabit bir alan verilir. x[0] = 20 dediğimizde ilk 4 byte 20'yi depolamak için kullanılır.
        x[0]; bize ayrılan o sabit hafızanın başlangıç noktasını gösterir. eğer x[100] dersek; x[0]'da bir int depolandığı için (4 byte)
        bilgisayar 4*100 = 400 byte ilerideki bir hafıza noktasına erişmeye çalışır. eğer sen o hafızayı bu array için tahsis ettiysen herhangi bir sorun yaşamadan
        o hafızaya erişebilir ve orada depolanan bilgiyi kullanabilirsin. eğer sabit sayıda bir bilgi depoluyorsan (10 intlik yer ayırıp, daha sonra 15 int kullanman gerekmeyecekse)
        array'in anlık olarak bir hafızaya erişebilme yeteneği çok yararlı olacaktır. aradığın şeye anında erişebilirsin.
    
    --> Linked list (sıralı/zincir/bağlı liste): bir linked list oluşturmak için yeni bir struct kurmak zorundasın. bu listede depolayacağın şey bir integer olsun örneğin.
        typedef struct node
        {
            int number;
            struct node* next;
        } node;
        genelde oluşturulan bu yapıya "node" adı veriliyor ama başka herhangi bir şey de diyebilirsin. nasıl ki int, char, float vs bir veri tipi; node da artık öyle. char'ın içinde bir 
        karakter depoluyorsun. int'in içinde bir tam sayı depoluyorsun. int* 'ın içinde bir integer "adresi" depoluyorsun. node'un içinde de bir integer bir de int adresi depolayacaksın.
        böylece, array'in aksine, bu sefer depolayacağın verinin kaç adet olduğunu önden bilmek zorunda değilsin. bir node yaratırsın; içine ilk verini yerleştirirsin. daha sonra ikinci veriyi
        başka bir node'a yerleştirip; ilk node'un pointer'ını ikinci node'a yöneltirsin. böylece arrayin aksine hafızadan (ram), sabit ve düz bir alan almak yerine
        hem istediğin zaman istediğin sayıda alan tahsis edersin; hem de bu alanlar birbiri ardına olmak zorunda kalmaz, ram'in rastgele yerlerinde bulunabilir her bir node. yeter ki önceki node onu göstersin.
        Fakat linked list'in zararı da şu; artık array'de olduğu gibi "anlık" erişim hakkına sahip değilsin. örneğin arrayın ilk elemanı 125. hafıza adresindeyse 100.elemanını 525. hafıza adresinde çat diye buluyordun.
        linked list'de her eleman rastgele yerlerde. ve sen (genelde) sadece ilk node'un adresine sahipsin. 5. node'daki bilgiye erişmek için 1. node'dan, 2. node'a; 2'den 3'e, 3'den 4'e, 4'den de 5'e gitmen gerekiyor.
        ha elbette başka pozitif yönleri de var. örneğin array'de ekstra element eklemek zor olduğu kadar, ortadaki bir elementi yok etmek de zor. ancak linked list'de öyle değil. node'u siliyorsun, bu node'u gösteren
        önceki node'un pointerini da, bir sonraki node'a yöneltiyorsun, bu kadar. bu yüzden linked list sana genişlik sağlıyor, ekleme-silme işlemlerinde rahatlık sağlıyor.
        ancak array'ın hızından feragat etmek zorunda kalıyorsun, ayrıca linked list hafızada birazcık daha çok yer kaplıyor (her int için ayrıca bir de pointer depoladığın için)..
        
    --> Hash table (hash tablosu): hash table ise array ve linked list'in birleşimi gibi bir nevi. linked list'in esnekliğiyle, array'in hızını birleştiriyor. Biz bir array oluştururken, veri tipini de yazıyoruz değil mi?
        char x[5] 5 adet karakter depoluyor. int x[5] 5 adet tam sayı. float x[5]. 5 adet virgüllü sayı vs. peki ya birer 'node' depolarsak? yani node x[5] dediğimiz zaman; 5 ayrı linked list'i depolayabiliriz.
        25 tane veri depoluyoruz diyelim. sıradan bir linked listte 25. veriye ulaşmak için 25 kere işlem yapmak gerekirdi. hash tablosunda ise 5 tane linked listte 5er tane veri olursa, maksimum 5 kere işlem yapmak yeterli olacaktır.
        ama array'ın uzunluğu ile linked list uzunluğunu iyi oranlamak gerekir. yoksa elimizde upuzun zincirler oluşur ve hash tablosunu efektif kullanamayız, normal bi linked listten farkı kalmaz.
        işte hash tablosunun sorunu da burada ortaya çıkıyor. düzgün bir tablo yapmak gerçekten zor. diyelim ki ilk 1000 sayıyı depolayacasın, 10 tane de liste var. ilk yüz sayıyı ilk listeye, son yüz sayıyı da son listeye atman gerekiyor
        oluşturduğun hash fonksiyonu bunu kusursuz bir şekilde yapmalı. 901 de olsa 999 da olsa, bunları son listeye yönlendirmeli. 99'u ilk listeye yönlendirirken 100 olduğunda 2. listeye yönlendirmeli. 
        ve bunu son derece tutarlı bir şekilde yapmalı. 1000 kere de 66 sayısını göndersek, bize her seferinde aynı sonucu vermeli. sayıları düzgünce ayırmalı ancak bu olabildiğince de rastgele olmalı. iki farklı veri için aynı hash değerini vermemeli.
        bütün sayıları aynı listeye atmamalı. bir zaman sonra listeyi dengesizleştirmemeli vs.
        özetle: hash tablosu hızlı ve esnek ancak yapması zor (hem kodlama açısından zor (yani 10 tane veri depolamak için değmez), hem de bazı şeyler için düzgün bir hash tablosu yapmak pek mümkün olmayabiliyor).



    Bu programda yapılması gereken fonksiyonlar şu işe yarıyor:
    --> hash: bu fonksiyon, kendisine gönderilen kelimeye bir takım işlemler yapıp; o kelimeye olabildiğince özgü ve rastgele (ama tutarlı) bir sonuç gönderiyor.
    --> load: fonksiyona gönderilen dosyayı (sözlük) açıp, içindeki bütün kelimeleri tek tek okuyor. okuduğu kelimeleri hash fonksiyonuna gönderip oradan gelen bilgiye göre hash tablosunu oluşturup yüklüyor.
    --> size: bütün hash toplasını tarayıp toplam kaç kelime olduğunu hesaplıyor.
    --> check: kendisine gönderilen kelime, hash tablosunda var mı yok mu, hızlı bir şekilde kontrol ediyor. tabloya bütün ingilizce kelimeleri eklediğimize göre, eğer check bir kelimeyi tabloda bulamadıysa o kelime yanlıştır.
    --> unload: hash tablosu için hafızadan tahsis edilen bütün alanı temizliyor. önce yaratılan her node'u siliyor, ardından listelerin kendisini. program sona erdiğinde hiçbir hafıza kaçağı kalmamasını sağlıyor.
*/



// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    // LENGHT dictionary.h dosyasında belirlenmiş 45 olarak. ingilizcedeki en uzun kelime 45 harfmiş. bu yüzden her kelime için 46 harflik (bir de son karakter var '\0') bir string kullanıyoruz.
    char word[LENGTH + 1];
    struct node *next;
}
node;

// hash için baya güzel bir fonksiyon buldum internette, bu yüzden onu düşünmemize gerek yok pek. sadece N'yi olabildiğince büyük bir sayı olarak
// tanımlasak yeterli olur bizim için...
// Number of buckets in hash table
#define N 50000*'z'

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // kontrol için bize gelen kelime üzerinde bir değişiklik yapamıyoruz. bu yüzden bu kelimeyi kopyalayıp (malloc),
    // küçük harfli halini depoluyoruz (tolower(word[i])) çünkü büyük-küçük harf hassasiyeti olmaması lazım. 
    // "gitmek" kelimesi sözlükte varsa, "Gitmek" de doğru olmalı. hatta "GİTMEK" de.
    int i, len = strlen(word);
    char* word1 = malloc(sizeof(char)*(len + 1));
    for(i = 0; i<len; i++)
    {
        word1[i] = tolower(word[i]);
    }
    word1[i] = '\0';

    //kelimemizi hash fonksiyonuna gönderip bu kelimenin hash değerini alıyoruz.
    int list_index = hash(word1);
    // tablodaki ilgili link list'i seçiyoruz.
    node* temp = table[list_index];
    // listeyi sonuna kadar tarıyoruz.
    while(temp)
    {
        // eğer listede şuan taradığımız kelime, elimizdeki kelimeyse; sözlükte bulduk demektir. True dönebiliriz.
        if(!strcmp(word1, temp->word))
        {
            // fonksiyondan dönmeden önce "malloc" ile ayırdığımız alanı "free" ile boşaltıyoruz
            free(word1);
            return true;
        } 
        temp = temp->next;
    }
    // eğer listenin sonuna gelmiş ve hala true dönememişsek demek ki böyle bir kelime yoktur.
    // word1'i silip false dönebiliriz.
    free(word1);
    return false;
}


/*
    bu ödev için internetten hash tablosu bakmamıza müsaade edilmiş çünkü düzgün bir tane oluşturmak gerçekten çooook zor. ben de bir siteden bu yöntemi gördüm.
    direkt kopyalayıp yapıştırdım, beklediğimden de güzel çalıştı. aşağıya da ekledim kodu bulduğum kaynağı. sen bu fonksiyonu anlamaya çalışma pek, baya karışık.
    yani anlayabilirsin elbette ama uğraştığına değmez boşver :p birileri güzel bir hash fonksiyonu yapmış bize de kullanmak düşer.
*/

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 401;
    int c;

    while (*word != '\0') {
        hash = ((hash << 4) + (int)(*word)) % N;
        word++;
    }

    return hash % N;

    //source: https://cs50.stackexchange.com/questions/38753/cs50-good-hash-function-for-pset5-speller
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    /* 
        dictionary dosyasını açıyorum. if(!file) return false;
        if(file == NULL)
        {
            return false;
        }
        yazmanın kısa hali. hata kontrolü sadece.
    */
    FILE* file = fopen(dictionary, "r");
    if(!file) return false;

    // olabilecek en uzun kelimeyi göz önünde bulundararak bir string oluşturuyorum.
    char* word = malloc(sizeof(char)*(LENGTH + 1));
    // fcanf fonksiyonu da, sözlükten, string'in içine kelimeleri tek tek okumayı sağlıyor.
    while(fscanf(file, "%s", word) != EOF)
    {
        // yeni kelimemiz için bir node oluşturuyoruz.
        node* new = malloc(sizeof(node)*1);
        if(!new) return false;

        // node'un pointer'ını şuan için kullanmadığımızdan null'a eşitliyoruz. node'un depoladığı kelimeyi de string'e eşitliyoruz.
        new->next = NULL;
        strcpy(new->word, word);

        // oluşturduğumuz kelimenin hash değerini buluyoruz.
        int hash_value = hash(word);
        
        // eğer ilgili alanda çoktan bir node varsa; yeni node'un pointerını o noda eşitliyoruz ve yeni node'u ilk sıraya yerleştiriyoruz.
        // orada 100 tane de node olsa, tek seferde yeni node'umuzu listeye ekliyoruz.
        // not: if(table[hash_value]), yine kısa bir yazım şekli. if(table[hash_value] != NULL) demeye eşit.
        if(table[hash_value]) new->next = table[hash_value];
        table[hash_value] = new;
    }
    // bütün kelimelerle işimiz bittikten sonra sözlüğü ve stringi kapatıyoruz.
    // sözlüteki bütün kelimeleri hafızaya attığımız için işimiz kalmadı artık.
    free(word);
    fclose(file);
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // hash tablosundaki bütün listeleri ve listelerdeki bütün kelimeleri tarıyoruz, toplam kelime sayısını dönüyoruz.
    int totalNodes = 0;
    for(int i = 0; i<N; i++)
    {
        node* temp = table[i];
        // while(temp) ---> while(temp != NULL)
        while(temp)
        {
            totalNodes++;
            temp = temp->next;
        }
    }
    return totalNodes;
    // aslında böyle bütün kelimeleri tek tek saymak yerine bi tane global bir "total_words" değişkeni oluşturabilir; hafızaya yüklediğim her kelimeyi sayabilirdim.
    // bu fonksiyona da sadece return total_words; yazardım. hem fonksiyon yazmakla uğraşmazdım, hem de program birkaç milisaniye daha hızlı çalışırdı.
    // ama ödevde bizden muhtemelen böyle bir fonksiyon kurmamızı istiyorlar, ben de bu yüzden o kurnaz kısayolu uygulamadım :p
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    /*
        bu da tıpkı size fonksiyonu gibi, teker teker bütün listeleri ve listelerdeki nodeları tarıyor; ve taradığı her node'u da siliyor.
        hatta garanti olsun diye sildiğim node'ları saydım ve silmeye başlamadan önce de toplam node sayısını aldım. silme işlemi bittikten sonra
        eğer sildiğim sayı, toplam sayıya eşit değilse program False dönüyor.
        aslında bunu yapmama gerek yoktu çünkü bütün nodeların silineceğini zaten biliyorum. ama yine de güvenli bir dizayn olması her zaman iyidir.
        hızdan biraz feragat etmek gerekse bile...
    */
    int deletedNodes = 0;
    int totalNodes = size();
    for(int i = 0; i<N; i++)
    {
        // while(table[i] != NULL)
        while(table[i])
        {
            // ilk önce, sileceğim node'u kenara ayırıyorum.
            // daha sonra table'ın ilk node'unu; sileceğim node'un işaret ettiği node'a eşitliyorum.
            // sonra kenara ayırdığım node'u silip 'deleted' sayısını artırıyorum.
            node* temp = table[i];
            table[i] = table[i]->next;
            free(temp);
            deletedNodes++;
            // son node'u da sildikten sonra table[i] NULL'a eşit olacak. ondan sonra bu döngü bitecek ve sıra diğer table'a geçecek vs...
        }
    }
    // eğer deleted ile total eşit değilse false dönüyorum, değilse true.
    if(deletedNodes != totalNodes)
    {
        printf("total: %d\ndeleted: %d\n", totalNodes, deletedNodes);
        return false;
    }
    return true;
}

// ./speller texts/tolstoy.txt
// en uzun yazılardan biri bu, bunu çalıştırmanı tavsiye ederim
// test ettim, bir sıkıntı yok. ama yine de her zamanki gibi check50'ye de bir bak :p