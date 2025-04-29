# Sosyal Ağ Grafiği Analiz Sistemi

Kırmızı-siyah ağaç veri yapısı kullanarak sosyal ağ analizi yapan C uygulaması. Kullanıcı ilişkileri, etki analizi ve topluluk tespiti özellikleri içerir.

## Özellikler
- *Veri Yapıları*:
  - Kırmızı-siyah ağaç ile kullanıcı yönetimi
  - Bağlı liste ile arkadaşlık ilişkileri

- *Analiz Fonksiyonları*:
  - Mesafe 1. ve 2. derece arkadaş bulma
  - Kullanıcı etki alanı hesaplama
  - Ortak arkadaş analizi
  - Topluluk (bağlı bileşen) tespiti

- *Veri Yükleme*:
  - veriseti.txt dosyasından otomatik veri okuma
## Örnek Çıktı

- Arkadaslarini analiz etmek istediginiz kullanici ID'sini girin: 101
- Kullanici ID: 101
- Mesafe 1 arkadaslar: 102 103
- Mesafe 2 arkadaslar: 104 105
- Kullanici etkisi: 5
- Ortak arkadas analizi icin ikinci ID'yi girin: 105
- Ortak Arkadaslari Bulunan ID'ler (101 105):
- Ortak arkadas sayisi: 1
- Topluluk tespitine geciliyor:
- Topluluk: 101 102 103 104 105

## Gereksinimler
`C derleyicisi (GCC veya uyumlu bir derleyici)`
`Standart C kütüphaneleri`
