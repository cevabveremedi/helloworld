/*
    stdlib kütüphanesini dosya okuma fonksiyonlarını kullanmak için ekliyoruz.
    stdint kütüphanesini ise bir byte'ı belirlemek için.
    stdbool ise pek gerekli değil, bool (true, false) yerine int = 1, int = 0 da kullanabilirdik ama ekledim işte :p
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// bir byte, 8 bit unsigned integera eşit. işimizi kolaylaştırmak için yeni bir data tipi oluşturuyoruz BYTE adında.
typedef uint8_t BYTE;

// her bir jpg, uzunluğu 512 byte olan blokların birleşmesiyle oluştuğu için block_size'ı 512 olarak tanımladım.
#define Block_size 512
// file name size ise; kurtardığımız her bir resmi, belli bir isimle yazdıracağız 000.jpg, 001.jpg, ..., 025.jpg gibi...
// bu dosya ismi de tam 8 karakterden oluşuyor (0 0 0 . j p g '\0'), bu yüzden file name siz isimli değişkeni 8 olarak tanımladım.
#define File_name_size 8

// bu fonksiyonun açıklaması en altta, ona bakmalısın.
bool is_jpg_start(BYTE Buffer []);

int main(int argc, char *argv[])
{
    // eğer tam olarak iki argüman yoksa program çalışmayı durduyor.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // ikinci argüman kartın ismi olmalı ve bu isimdeki dosyayı açmayı deniyoruz. eğer isim yanlış girildiyse, böyle bir dosya yoksa
    // veya dosya bozuksa, açılmıyorsa program yine çalışmayı durduruyor.
    // eğer dosya sorunsuz açıldıysa ona "mem_card" ismini veriyorum, kartı okumaya hazırız.
    FILE* mem_card = fopen (argv[1], "r");
    if (mem_card == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    // toplam 512 byte depolayabilecek bir buffer oluşturuyorum. böylece bir jpg içindeki blokları tek tek depolayabiliriz.
    BYTE Buffer[Block_size];

    // kartta şimdiye kadar hiç jpg dosyası bulduk mu, bunu takip edeceğiz çünkü bütün jpgler birbiri ardına depolanıyor.
    // eğer karttaki çöp byteları taradıktan sonra ilk jpg'i bulduysak, diğer bütün jpgler de arka arkaya dizilmiştir.
    // son jpg'yi bulana kadar, veya bütün kartı tarayana kadar eminiz ki şuan okuduğumuz blok artık bir jpg'ye ait.
    bool first_jpg = false;

    // toplam kurtarılan dosya sayısı (kurtardığımız resimleri adlandırırken bu değişkenden yararlanacağız, 000.jpg gibi)
    int file_count = 0;

    // kurtardığımız her bir resim bloğu bu dosyada depolanıp yazılacak.
    FILE* image_file;

    // fread fonksiyonu; mem_card isimli kartımızdan, her seferinde 512 bytelık bilgi okuyup bunu bufferımıza yazıyor.
    // kartın içindeki bütün bytelar taranana kadar birer block okunmaya devam edecek.
    while(fread(Buffer, Block_size, 1, mem_card))
    {
        // her seferinde bufferımızı is_jpg_start fonksiyonuna gönderip, bufferdaki bilginin yeni bir jpg'ye ait olup olmadığını sorguluyoruz.
        // eğer bir jpg başlangıcı ise; (bu if'den sonra bir else-if daha var dikkat et)
        if (is_jpg_start(Buffer))
        {
            /*
                ve bu jpg, bulduğumuz ilk jpg ise ilk jpg'yi bulduğumuzu belirten değişkeni true yapıyoruz.
                bu noktadan sonra sıralı jpg'leri bulmaya başladık demektir. bütün kartı tarayana kadar devam
            */
            if(!first_jpg)
            {
                first_jpg = true;
            }
            else
            {
                // eğer bir jpg başlangıcına geldiysek, ve halihazırda ilk jpg daha önce bulunmuşsa, demek ki şuan yeni bir jpg bloğunu taradık demektir.
                // şimdiki image_file ile işimiz bittiğine göre onu kapatıp yeni bir dosya açabiliriz.
                fclose(image_file);
            }
            // yeni açacağımız dosyaya koyacağımız isim için 8 karakterlik bir string oluşturuyoruz.
            char file_name[File_name_size];
            // bu stringe, 00i.jpg adını veriyoruz (file count şuan kaçsa o resmi kurtarmışızdır, i değeri odur).
            // %03i.jpg, isimlendirmede yapılan ufak bir hile
            // "00" + file_count + ".jpg" gibi
            sprintf (file_name, "%03i.jpg", file_count);
            file_count++;

            // image_file'ı yazmak için açıyoruz. açma sırasında bir sorun çıkıyor mu diye kontrol ediyoruz.
            image_file = fopen(file_name, "w");
            if (image_file == NULL)
            {
                return 1;
            }
            // daha sonra buffer'ın içindeki bloğu image_file'a yazıyoruz.
            fwrite (Buffer, Block_size, 1, image_file);

            /*
                burada olanları şöyle özetleyeyim; 512 bytelık bir blok taradık ve buffer'a attık. daha sonra bu buffer'ı is_jpg_start fonksiyonuna gönderdik.
                eğer bu bufferda bir jpg başlangıcını bulmuşsak;;
                    -> demek ki yeni bir jpg'ye başladık; "image_file" isimli dosyaya tam bir jpg'yi yazdık ve bir resim kurtardık demektir. artık o dosyayı kapatabilir ve ona yazmayı bitirebiliriz.
                    -> veyaaa bu bulduğumuz başlangıç jpg'si, şimdiye kadar denk geldiğimiz ilk jpg. o halde zaten herhangi bir dosya açmadık bile. ilk jpg'yi bulduğumuzu raporluyoruz ve if else bloğunu geçiyoruz.
                if else bloğunun devamında, yeni bir dosya açıyoruz ve ona yazmaya başlıyoruz. taa ki yeni bir jpg bulana kadar. yenisini bulduğumuzda bu dosyaya yazmayı bırakıp yenisine geçeceğiz.
            */
        }
        else if (first_jpg)
        {
            // eğer bu bir jpg başlangıcı değilse; ama çoktan ilk jpg'mizi bulduysak
            // demek ki şuan hala, daha önce okunmaya başlanmış bir jpg'yi tarıyoruz demektir.
            // öyleyse image_file isimli dosyaya bu bloktaki bilgiyi yazabiliriz.
            fwrite(Buffer, Block_size, 1, image_file);
        }

        // yok eğer bir jpg başlangıcında değilsek ve daha önce de bir jpg bulamadıysak, şuan çöp bir bilgi tarıyoruzdur, geçebiliriz.
    }

    // kartla işimiz bittikten sonra, herhangi bir hafıza kaçağı olmaması için iki dosyayı da güvenli bir şekilde kapatıyoruz.
    fclose(mem_card);
    fclose(image_file);

    return 0;
}

/*
    Bu fonksiyonu cs50'nin eski bir videosunda görmüştüm. Kısaca şu işe yarıyor;
    buffer dizisinin ilk dört elemanına (byte) bakıyor. eğer ilk üç byte 0xff, 0xd8, 0xff ve
    dördüncü byte 0xe0 ile 0xef arasındaysa; bu dizi bir JPEG demektir. Olumlu bool dönüyor.
    Program, karttan okuduğu her 512 byte'ı bu fonksiyona göndererek jpg mi değil mi bunu kontrol edecek.
*/
bool is_jpg_start(BYTE Buffer[])
{
    return (Buffer[0] == 0xff && Buffer[1] == 0xd8 && Buffer[2] == 0xff && (Buffer[3] & 0xf0) == 0xe0);
}

// program sonu not:
// ./recover card.raw
// programı test ettim ama ne olur ne olmaz ödevi yüklemeden önce check50 ile bir kontrol edersin.
// eğer 50 tane resmi tek tek silmekle uğraşmak istemiyorsan şunu yaz rm -f *.jpg