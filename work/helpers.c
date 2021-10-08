#include "helpers.h"
#include <stdbool.h>
#include <math.h>

// Convert image to grayscale
/*
    (ödevi yüklerken bu uzun yorumları silebilirsin)
    (r = red, g = green, b = blue)
    Bir pikselin r, g, b değerleri (0 ile 255 arasında) eşit olduğunda grinin bir tonu ortaya çıkar.
    Resimdeki bütün pikselleri gri yaptığımızda ise "grayscale" efekti vermiş oluruz.
    Ancak, resimdeki bütün piksellere, aynı değeri verirsek ortaya sadece griden ibaret bir resim çıkar.
    Bu yüzden her piksele ayrı, kendilerine özel bir tonda gri vermemiz gerekir.
    Eğer r = g = b = 50 ise siyahımsı bir gri, r = g = b = 250 ise beyazımsı bir gri oluşur.
    Bu yüzden, her pikselin r, g, b değerlerinin ayrı ayrı ortalamasını alırsak
    ona uygun bir tonda gri elde edebiliriz (kırmızı bir pikselse, kırmızımsı bir gri)...
*/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Bir pikselin r, g, b değerlerinin ortalamasını bu değişken içinde saklayacağız.
    float gray;

    // Bu iki döngü ile resimdeki bütün pikselleri tek tek tarıyoruz.
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // image[j][i] pikselinin r, g, b değerlerini toplayıp 3'e bölüyoruz ve gray değişkeninde saklıyoruz.
            // Elde ettiğimiz ortalama, bize uygun tonu veriyor.
            gray = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3.0);

            // Bu pikselin bütün renk paketlerini aynı tona eşitlediğimizde uygun tondaki griyi elde ediyoruz.
            image[j][i].rgbtBlue = gray;
            image[j][i].rgbtGreen = gray;
            image[j][i].rgbtRed = gray;
        }
    }
    // her pikselin rengini ayrı ayrı düzenledikten sonra resme grayscale efekti vermiş oluyoruz.
}



// ----------------------------



// Bu fonksiyonu birazdan açıklayacağım.
int limit(int value)
{
    if (value > 255)
    {
        value = 255;
    }
    return value;
}

// Convert image to sepia
/*
    sepia fonksiyonu ennn kolay efekt. resimdeki bütün piksellerin r,g,b değerlerini, sana verilen formülle hesaplaman gerekiyor.
    formülü zaten ödevin sitesinde vermişler, şu;
        sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    bütün piksellere bu formülü uygulayacaksın. dikkat etmek gereken 2 küçük detay var sadece:
    1- formülü uyguladıktan sonra ortaya çıkan değer virgüllü bir sayı oluyor. ama r,g,b değerleri tam sayı olmak zorunda.
        bu yüzden round fonksiyonuyla, o değeri en yakın tam sayıya yuvarlaman lazım.
    2- bir pikselin r, g ve b değeri minimum 0, maksimum da 255 olabilir (detay: renk değeri 8 bit ile ifade ediliyor ve 8 bite de maks 255 sayısı sığıyor)
        ve bize verilen formülü uyguladıktan sonra çıkan bazı değerler, 255'in üstünde olabiliyor. Bu yüzden yukarıda gördüğün fonksiyon var. Hesapladığımız her değeri,
        önce round ile tam sayıya yuvarlıyoruz, sonra "limit" fonksiyonuna gönderiyoruz. eğer o sayı 255'den büyükse, 255 dönüyor. eğer küçükse, o sayı kaçsa onu dönüyor.
*/

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaBlue;
    int sepiaRed;
    int sepiaGreen;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // formülden çıkan sonucu önce tam sayıya yuvalıyoruz sonra limit fonksiyonuna gönderip, 255'den büyük olmadığına emin oluyoruz.
            sepiaBlue = limit(round(0.272 * image[j][i].rgbtRed + 0.534 * image[j][i].rgbtGreen + 0.131 * image[j][i].rgbtBlue));
            sepiaGreen = limit(round(0.349 * image[j][i].rgbtRed + 0.686 * image[j][i].rgbtGreen + 0.168 * image[j][i].rgbtBlue));
            sepiaRed = limit(round(0.393 * image[j][i].rgbtRed + 0.769 * image[j][i].rgbtGreen + 0.189 * image[j][i].rgbtBlue));

            // her pikseli bu formüle göre hesaplayıp eşitliyoruz.
            image[j][i].rgbtBlue = sepiaBlue;
            image[j][i].rgbtGreen = sepiaGreen;
            image[j][i].rgbtRed = sepiaRed;
        }
    }
}



// ----------------------------



// Reflect image horizontally
/*
    Bu fonksiyon biraz hileli. Resmi yatay düzlemde (Y eksenine göre) yansıtmak için birden fazla yöntem uygulanabilir.
    Dikkat edilmesi gereken nokta şu ki; resmin sadece sol yarısını taramak gerekiyor. Daha da detaylı açıklamak gerekirse;
    şöyle bir array düşün: int numbers[5] = {1, 2, 3, 4, 5}; bu diziyi yansıtmak, yani {5, 4, 3, 2, 1} haline getirmek için
    numbers[0] = numbers[4] ile, numbers[1] = numbers[3] ile yer değiştirmeli ve yarısına geldiğinde durmalı.
    çünkü sonuna kadar gidersen en son numbers[4] ile numbers[0] tekrar yer değiştirecek ve yine aynı diziyi elde etmiş olacağız.
    Bir resmi yansıtmak da bu örneğin 2 boyutlu hali.
    {1, 2, 3, 4, 5}    -> {5, 4, 3, 2, 1}
    {6, 7, 8, 9, 10}   -> {10, 9, 8, 7, 6}
    {11, ....}         -> {.... ,11}
    tek boyutta yaptığın şeyi bütün dizilere uyguladığın zaman 2 boyutta yatay yansıtma yapmış oluyorsun.
*/
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // use of a temporary array to swap values
    // temp dizisinin içinde uğradığımız pikselin r, g, b bilgilerini depolayacağız.
    int temp[3];

    // Bu döngüde ise dikkat edersen i, 0'dan, width / 2'ye kadar gidiyor.
    // Böylece resmin sadece sol tarafındaki pikselleri taramış oluyoruz.
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width / 2; i++)
        {
            // Temp dizisinde şuan taradığımız pikselin r,g,b bilgisini deopluyoruz.
            temp[0] = image[j][i].rgbtBlue;
            temp[1] = image[j][i].rgbtGreen;
            temp[2] = image[j][i].rgbtRed;
            
            //swap pixels with the ones on the opposite side of the picture and viceversa
            /*
                Şuan taradığımız pikselin r,g,b bilgisini, yansımasındaki piksele eşitliyoruz.
                i = 1 olduğunu düşün, width - i - 1, tam karşısındaki pikseli verir.
                üstte veridiğim örneği hatırla; numbers[5] = {1, 2, 3, 4, 5}
                bu örnekte width = 5 oluyor. yani i = 0 iken, 5 - 0 - 1 = 4 oluyor.
                numbers[0]'ı, numbers[4]'e eşitliyoruz. böylece ilk eleman, son elemana eşit oluyor.
                hatırlarsan bir önceki adımda, şimdiki pikselin değerlerini saklamıştık zaten.
                Yani temp = numbers[0]'a eşit şuan. numbers[0]'ı, numbers[4]'e eşitledikten sonra,
                diğer adımda numbers[4]'ü de temp'e eşitleyebiliriz. Böylece 0 ile 4 yer değiştirmiş olur.
            */
            image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;
            image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
            image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;

            // Burada da numbers[4]'ü temp'e eşitliyoruz.
            image[j][width - i - 1].rgbtBlue = temp[0];
            image[j][width - i - 1].rgbtGreen = temp[1];
            image[j][width - i - 1].rgbtRed = temp[2];

            // Sol yarıdaki bütün pikselleri bu şekilde taradıktan sonra resim yansıtılmış oluyor.
        }
    }
}



// ----------------------------



// Blur image
/*
    Blur fonksiyonunu düzgünce anlatabileceğimi sanmıyorum bu yüzden şu videoyu izlemeni tavsiye ederim:
    https://youtu.be/6opWB7DaFCY?list=PLhQjrBD2T3837jmUt0ep7Tpmnxdv9NVut
    Video ingilizce olabilir ama videodaki örneklere bakınca bile anlamaya yardımcı oluyor.
    Şöyle özetleyebilirim:
    Bir resme bulanıklaştırma efekti vermek için, her pikselin rengini, komşu piksellere yakınsamak gerekir.
    Bir pikselin komşuları, çevresindeki 8 diğer pikseldir.
    _____________
    |___|___|___|
    |___|_+_|___|
    |___|___|___|

    Ortadaki pikselin rengini komşulara yakınsarsak ve bunu bütün piksellere yaparsak, ortaya bulanıklaşmış bir resim çıkar.
    Bunu yapmak için, 8 komşu piksel ve şuan taradığımız pikselin (toplam 9 piksel) r, g ve b değerlerini kendi içlerinde
    ayrı ayrı toplayıp ortalamasını almak gerekiyor. Daha sonra da şimdiki pikselin r,g,b değerlerini,
    hesapladığımız bu r,g,b değerline eşitlemek gerekiyor. piksellere sırasıyla 1,2,3,4,5,6,7,8,9 diyelim. şuanki piksel de 5 olsun.
    r5 = (r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8 + r9) / 9
    g5 = (g1 + g2 + g3 + g4 + g5 + g6 + g7 + g7 + g9) / 9
    b5 = (b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9) / 9
    yapmamız gereken işlem bu. ve bunu bütün piksellere uygulamak gerekir.

    Dikkat edilmesi gereken 2 büyük, önemli nokta var ama. Burası çokomelli;

        1- Komşu pikselleri hesaplarken, array sınırlarının dışına çıkmamak gerekiyor. Örneğin resmin en sol köşesindeki piksele bakalım;
        Sol-üst köşedeki pikselin ne solunda ne de üzerinde bir komşusu var. yani kendisiyle birlikte toplam 4 piksel hesaplamak gerekir.
        Benzer bir şekilde en üst sıradaki herhangi bir piksele bakalım. Bu pikselin sağında, solunda, altında komşuları var ama üstünde yok.
        Bu yüzden kendisiyle birlikte 6 pikseli hesaplamamız gerek sadece. Yani yapacağımız algoritma, eğer "varolmayan" pikselleri hesaplamaya çalışırsa
        örneğin array[-1] numaralı elemana erişmeye çalışırsa, program hata verir ve çalışmaz. Buna dikkat etmek gerekiyor.
        
        2- Algoritmayı kurduk, sadece "varolan" komşuları güvenli bir şekilde hesapladık, ortalama r, ortalama g, ortalama b'yi bulduk.
        Yapmamız gereken şey şimdi elimizdeki pikseli bu ortalamalara eşitlemek değil mi? DEĞİL...
        Önceki fonksiyonlarda Komşu piksellerle hiçbir işimiz yoktu. Ama bu fonksiyonda, her piksel, komşu piksellerini de etkiliyor.
        Yani, eğer bütün pikselleri tararken, her taradığın pikseli de değiştirirsen; bir sonraki tarayacağın piksel, bu değişmiş pikselden etkilenecek.
        Yani her değiştirdiğin pikselle birlikte resim daha da bozulmaya başlayacak. Muhtemelen ilk birkaç pikselden sonra ortaya bembeyaz bir resim çıkacak (ya da bozuk)
        yapman gereken şey şu: öncelikle elimizdeki resmin güvenli bir kopyasını oluşturmalısın. Daha sonra, bozulmamış resmi tararken, diğer kopya üzerinde değişiklik yapmalısın.
        Böylece her pikselin değerini, bozulmamış, orijinal resimden hesaplarken, diğer kopyayı da değiştiriyor olacaksın. Program sona erdiğinde bozulmamış bir resim
        ve blur efekti elde etmiş olacaksın. Bu iki nokta, bu ödevi yapan neredeyse her öğrencinin düştüğü, düzeltmek için de saatlerce uğraştıkları detaylar, dikkatli ol.
*/
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // r, g, b ortalamalarını depolayacağımız değişkenler;
    int sumBlue;
    int sumGreen;
    int sumRed;

    // Her pikselin, potansiyel Komşu sayısını burada depolayacağız.
    float neighborCounter;

    // create a temporary table of colors to not alter the calculations
    // Orijinal resimle aynı büyüklükteki başka bir resim (ama pikselleri daha ayarlanmamış, boş bir resim şuan).
    RGBTRIPLE temp[height][width];

    // Bütün pikselleri tarıyoruz.
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // her döngüde toplam ve komşu değişkenlerini, bir sonraki hesaplama için sıfırlıyoruz (her piksel ayrı ayrı hesaplanacağı için)
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            neighborCounter = 0.00;

            // sums values of the pixel and 8 neighboring ones, skips iteration if it goes outside the pic
            
            // şimdiki piksel ve 8 (potansiyel) komşunun değerlerini hesaplıyoruz.
            // k sırasıyla -1, 0 ve 1 oluyor.
            for (int k = -1; k < 2; k++)
            {
                // Eğer yatay düzlemde j + k (yani potansiyel komşu piksel), resmin (yani 2 boyutlu dizinin) sınırları dışına çıkıyorsa, o komşuyu atlıyoruz (continue komutu ile).
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    //Benzer bir şekilde, eğer potansiyel komşu, dikey sınırların dışına çıkıyorsa onu atlıyoruz.
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    // sınır-dışındaki piksellerden kurtulduktan sonra gerçek pikseller kalıyor geriye.
                    // fark ettiysen şuan 4 dereceli bir for döngüsünün içindeyiz. ilk iki for döngüsünün içinde, her spesifik pikseli tarıyoruz.
                    // daha sonra, o pikselin komşularını bulmak için yine iki for döngüsü kuruyoruz ve çevresindeki 8 potansiyel komşuyu tarıyoruz.
                    // toplam r, g, b değerlerini buluyoruz.
                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    
                    // ve şuan hesapladığımız pikselin kaç gerçek komşusu olduğunu sayıyoruz (9 olabilir, 6 olabilir, 4 olabilir)... 
                    neighborCounter++;
                }
            }

            // üstteki iki for döngüsünden çıktıktan sonra, elimizde şunlar oluyor:
            // şuan taradığımız pikselin kaç tane komşusu varsa onu hesaplamış oluyoruz.
            // ve taradığımız piksel dahil, komşu piksellerin r,g,b değerlerinin toplamını buluyoruz.

            // averages the sum to make picture look blurrier

            // daha sonra toplam kırmızıyı, maviyi, yeşili komşu sayısına bölüp (ve en yakın tam sayıya yuvarlayıp) ortalamalarını alıyoruz.
            // ama şuan taradığımız orijinal resim üzerinde değil de, en başta oluşturduğumuz kopya resim üzerinde değişiklik yapıyoruz.
            // kopyanın, [i][j] koordinatlarındaki pikselinin renk paletini bu ortalamalara eşitliyoruz.
            temp[j][i].rgbtBlue = round(sumBlue / neighborCounter);
            temp[j][i].rgbtGreen = round(sumGreen / neighborCounter);
            temp[j][i].rgbtRed = round(sumRed / neighborCounter);
        }
    }

    // bütün döngü sona erdikten sonra orijinal fotoyu, Blurlanmış kopya fotoğrafa eşitliyoruz.
    // alttaki döngüde, orijinal resmin bütün piksellerini blurlanmış resmin piksellerine eşitliyor.

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}