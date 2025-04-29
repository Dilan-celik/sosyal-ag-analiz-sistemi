# Sosyal Ağ Grafiği Analiz Sistemi
Bu proje, sosyal ağlardaki kullanıcılar ve arkadaşlık ilişkileri üzerine analizler yapabilen bir C uygulamasıdır. Kırmızı-siyah ağaç (Red-Black Tree) veri yapısını kullanarak kullanıcılar verimli bir şekilde saklanır ve arkadaşlık ilişkileri bağlı listeler ile modellenir. Uygulama, kullanıcının etki alanını, arkadaş mesafelerini, ortak arkadaşları ve topluluk yapılarını analiz edebilmektedir.

## Özellikler
- **Kırmızı-siyah ağaç ile kullanıcı yönetimi (ekleme, arama)**

-**Bağlı liste ile arkadaşlık ilişkilerinin modellenmesi**

- **Belirli bir kullanıcı için:

ve 2. derece arkadaşların bulunması

Etki alanı (bağlı olduğu topluluğun büyüklüğü)

İkinci bir kullanıcı ile ortak arkadaşların listelenmesi

Sosyal ağ içerisindeki toplulukların (bağlı bileşenler) tespiti

veriseti.txt dosyasından veri yükleme

## Kullanım
Program çalıştırıldığında, sizden analiz yapılacak bir kullanıcı ID’si girmeniz istenir. Ardından:

Girilen kullanıcının 1. ve 2. derece arkadaşları yazdırılır.

Etki alanı (bulunduğu topluluğun boyutu) hesaplanır.

İkinci bir kullanıcı ID’si girilerek ortak arkadaşlar bulunur.

Sosyal ağdaki tüm topluluklar listelenir.

Örnek Çıktı
yaml
Kopyala
Düzenle
Arkadaslarini analiz etmek istediginiz kullanici ID'sini girin: 101
Kullanici ID: 101
Mesafe 1 arkadaslar: 102 103
Mesafe 2 arkadaslar: 104 105
Kullanici etkisi: 5
Ortak arkadas analizi icin ikinci ID'yi girin: 105
Ortak Arkadaslari Bulunan ID'ler (101 105):
Ortak arkadas sayisi: 1
Topluluk tespitine geciliyor:
Topluluk: 101 102 103 104 105
Dosya Yapısı
sosyalag.c – Ana kaynak dosya

veriseti.txt – Giriş verisi dosyası (kullanıcı ve arkadaşlık bilgileri)

Gereksinimler
C derleyicisi (GCC veya uyumlu bir derleyici)

Standart C kütüphaneleri
