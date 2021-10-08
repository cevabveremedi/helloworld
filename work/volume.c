/*
    bu kodu o kadar detaylı açıklamadım, zaten ödevi yapıp gönderdin diye.
    karşılaştırma yapman için yazdım.
    (ödev sayfasında zaten birçok detay verilmiş, wav dosyaları nedir, nasıl tespit edilir vs)
    zaten recover ödevine bundan önce bakarsan volume baya çerez gelecektir.
*/

// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
// wav dosyalarının başında olan byte sayısı. (dosyayı tespit etmek için kullanacağız)
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    // tam olarak 4 argüman yoksa program duruyor.
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    // wav dosyasını açıyoruz ve input adını veriyoruz. eğer işlem sırasında hata çıktıysa program çalışmayı duruyor (error checking)
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // ikinci bir dosyayı da, yazmak için açıyoruz. yine error checking yapıyoruz. bunu da output olarak kullanacağız. modifiye edilmiş ses dosyası burada depolanacak.
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // kullanıcının girdiği factor değerini float'a çeviriyoruz (örneğin 4. argüman "2" ise sesin iki katına çıkması gerekiyordur)
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // header isimli 44 bytlık bir array oluşturuyoruz. 
    // bize verilen wav dosyasının headerını kopyalıyoruz, ve oluşturduğumuz output isimli dosyaya bu header'ı kopyalıyoruz.
    // böylece output isimli dosya gerçekten de bir wav dosyasına dönüşüyor.
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    // audio sample'ını depolamak için int16_t kullanmamız gerektiği ödev açıklamasında verilmiş. bunu depolamak için bir bufer oluşturuyoruz.
    // her seferinde 2 buffer'ın içine 2 byte okuyoruz.
    int16_t buffer;
    while(fread(&buffer, 2, 1, input))
    {
        // buffer değerini factor ile çarparak bizden istenen ses ayarını yapıyoruz.
        // daha sonra da output dosyasına, modifiye edilmiş bufferı yazıyoruz.
        buffer *= factor;
        fwrite(&buffer, 2, 1, output);
        // input dosyasını tamamen tarayana kadar bu işlem devam ediyor.
    }

    // Close files
    // her şey bittikten sonra açtığımız dosyaları güvenle kapatıyoruz.
    fclose(input);
    fclose(output);
}


/*
    programı kontrol ettim çalışıyor
    ./volume input.wav aa.wav 0.1
    ./volume input.wav aa.wav 3

    yine de göndermeden önce sen de bir kontrol et ne olur ne olmaz..
*/