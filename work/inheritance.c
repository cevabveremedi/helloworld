// Simulate genetic inheritance of blood type

/*
    fen bilgisi dersindeki kalıtım ve çaprazlama konusunun aynısı resmen. olasılık hesabını bilgisayara yaptırıyoruz sadece.
    bize neredeyse her şey verilmiş, bizim sadece create_family ve free_family fonkisyonlarını tamamlamamız gerekiyor.
    bu fonksiyonlarda da recursion kullanacağız. eğer recursion ile ilgili kafanda bir soru işareti varsa şu videoyu izle:
    https://youtu.be/aCPkszeKRa4
    burada çok güzel açıklanmış her şey.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    burada person isimli bir yapı oluşturulmuş. Linked listteki node'ları hatırla, genelde 1 int, 1 de "next" pointerı oluyor.
    bu yapıda ise int yerine 2 char var, 2 tane de next pointerı var.
    2 char, 2 alleli temsil ediyor, 2 pointer ise 2 ebeveyni.
    gerisine bakmaya pek gerek yok, create_family fonksiyonuna geçebiliriz.
*/

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

/*
    bu fonksiyona jenerasyon limiti gönderiliyor (diyelim ki limit 3 olsun) ve sonucunda bir person pointerı, ve o persona bağlı 
    3 kuşak diğer personların olmasını istiyor.

             3 -> bizden istenen kişi
            / \
           /   \
          2     2 -> onun ebeveynleri
         / \   / \ -> (fonksiyona gönderilen sayı büyüdükçe araya başka kuşaklar girecek)
        1   1 1   1 -> ilk kuşak.

    her kişinin genleri, ebeveynlerinin sahip olduğu genlerden rastgele seçilecek.
    1. kuşaktaki kişilerin genleri ise tamamen rastgele belirlenecek.
*/

// Create a new individual with `generations`
person *create_family(int generations)
{
    // Yeni bir person yaratmamız isteniyor. Malloc ile hafızadan bir person büyüklüğünde yer tahsis ediyoruz.
    // TODO: Allocate memory for new person
    person* temp = malloc(sizeof(person)*1);
    temp->parents[0] = temp->parents[1] = NULL;
    // Person ebeveynleri şimdilik boş.

    // ilk kuşağa gelene kadar, o kuşaktaki herkesin ebeveynlerini oluşturuyoruz.
    // Generation with parent data
    if (generations > 1)
    {
        // fonksiyon ilk kez bu noktaya geldiğinde, yarattığımız "temp" kişisinin ebeveynlerini oluşturmak için
        // tekrar create_family fonksiyonunu çağırıyoruz.
        // ebeveynlere de aynı şekilde 2 yeni ebeveyn atıyoruz (her seferinde 1. nesle daha da yaklaşarak)
        // en sonunda fonksiyon 1. nesle geliyor ve bu if koşuluna girmiyor -> if(generations > 1)
        // alltaki temp->parents[0] ile başlayan iki satır kodu inceledikten sonra 1. nesli görmek için else kısmını oku öncelikle.

        // TODO: Recursively create blood type histories for parents
        temp->parents[0] = create_family(generations-1);
        temp->parents[1] = create_family(generations-1);

        // 1. nesle rastgele allelleri verdikten sonra, o neslin bir küçüğünün yaratıldığı fonksiyona devam ediyoruz.

        // TODO: Randomly assign child alleles based on parents
        char x;
        while(1)
        {
            // Ben burada sonsuz bir döngü oluşturdum. x'e rastgele bir gen atıyorum. eğer bu gen 1. ebeveyninin genlerinden birine sahip değilse
            // tekrar rastgele bir gen atıyorum. 1. ebeveynin genlerinden biri denk gelene kadar devam ediyor.
            x = random_allele();
            if(x == temp->parents[0]->alleles[0] || x == temp->parents[0]->alleles[1])
            {
                // eğer 1. ebeveyndeki genlerden birine denk gelirsek sonsuz döngüden çıkıyoruz.
                break;
            }
        }
        // burada da ilk geni kaydediyoruz.
        temp->alleles[0] = x;
        while(1)
        {
            // burada da aynı işlemi, ikinci ebeveyne göre uyguluyoruz.
            x = random_allele();
            if(x == temp->parents[1]->alleles[0] || x == temp->parents[1]->alleles[1])
            {
                break;
            }
        }
        temp->alleles[1] = x;

        // her şey bittikten sonra bu kişiyi de dönüyoruz.
        // bundan sonra bundan bir küçük nesil için aynı işlemler uygulanacak.
        // en küçük nesile geldiğimizde de onu, parentları bağlanmış bir şekilde main fonksiyonuna dönmüş olacağız
    }

    // Generation without parent data
    else
    {
        // fonksiyon en sonunda 1. nesil için çağırıldığında bu nesil için ebeveyn oluşturmuyoruz (parents[0] = parents[1] = NULL;)
        // kurs tarafından bize hazır verilen random_allele fonksiyonuyla, 1. nesildeki kişilere rastgele genler atıyoruz.
        // devamında da yeni yarattığımız kişiyi dönüyoruz.

        // (not: burada parent pointerlarını null'a eşitlememizi söylüyor, en yaşlı nesil olduğu için. ben bunun tersini yaptım.)
        // (oluşturduğum her person'ın parent pointerlarını en baştan NULL'a eşitledim. önceki nesillerin parentlarını da bu şekilde recorsion ile halletim)
        // TODO: Set parent pointers to NULL
        temp->alleles[0] = random_allele();
        temp->alleles[1] = random_allele();
        // TODO: Randomly assign alleles
    }

    // yarattığımız person'ı dönüyoruz.
    // TODO: Return newly created person
    return temp;
}

// bu fonksiyon da baya standart bir recursion fonksiyonuyla, oluşturulan her person'ı siliyor (ram'den tahsis edilmiş her alanı boşaltıyor)

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    // eğer gönderdiğimiz person'a bağlı bir parent yoksa 1. nesle gelmişizdir, ilk önce bu arkadaşları siliyoruz.

    // TODO: Handle base case
    if(!p->parents[0] && !p->parents[1])
    {
        free(p);
        return;
    }

    // her bir person'ı silmeden önce ona bağlı parentları silmek için bu fonksiyonu parentlar için çağırıyoruz.

    // TODO: Free parents
    free_family(p->parents[0]);
    free_family(p->parents[1]);
    
    // en sonunda sonuncu nesil dahil herkes silinmiş oluyor. mutlu son

    // TODO: Free child
    free(p);
    return;
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
