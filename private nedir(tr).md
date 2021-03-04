### credit = github:  [Yunus-C](https://github.com/Yunus-C) \

HTTP Server

HTTP Server, bir host yöntemidir.
Özellikle XAMPP ve Laragon yaygın olsa da Private Server'a özel olarak yapılan NodeJS host yöntemleri mevcutttur.
Size tavsiyem kesinlikle Laragon'dur, gayet sade ve anlaşılırdır.
Kısacası insanlar HTTP Server aracılığı ile sunucuya giriş yapar.
Genellikle HTTP Server çökertmeye yönelik flooder kullanan çok insan vardır, HTTP Server çöktüğü anda sunucuya giriş yapılamaz.
Yanlış HTTP Server ve Server Dosyaları ayrı yerlerde olsa bile sunucu IP & Port'u düzgün şekilde girilirse sunucu çalışır hatta bu yönteme genellikle redirect denir, CLOUDFLARE tarzı ünlü şirketlerde bu tarz yöntemler kullanmaktadır.

Server Dosyaları ve .cpp (kod dosyası)
Genellikle Private Server oyuncuları tarafından yanlış bilinen hatta .ccp olarak adlandıran insanlar bile var.
.cpp'nin anlamı C Plus Plus o da C++ demektir.
Genelde sunucularda klasörler bu şekildedir.
https://cdn.discordapp.com/attachments/816641278502371389/816643972633198592/unknown.png
server.exe sunucuyu başlatmak için gereken executive dosyasıdır, HTTP Server olmadan çalışmaz.
GTOSmanagement.exe genelde sunucudaki dünyaları & eşyaları bulmak için kullanılan basit bir dosya ayrıştırma yöntemidir.
Klasörler sunucudaki save (kayıt) dosyalarıdır.
.cpp olayına geri dönelim, böyle bir dosya ile karşılaşacağız.
https://cdn.discordapp.com/attachments/816641278502371389/816644795627864104/unknown.png

server.sln kodları derlemek için gereken bir derleyicidir.
server.cpp ana kodların bulunduğu dizindir, sunucu dosyalarını çoğu insan bu yüzden .cpp diye adlandırır.
.h uzantıları yardımcı kodlar yani kütüphanelerin olduğu dizinlerdir fakat bunları normal C++ kütüphanesiyle karıştırmayın.
#include <iostream> normal bir C++ kütüphanesidir.
#inlucde "stdafx.h" özel bir C++ kütüphanesidir ve uygulamayı yapan kişinin oluşturduğu ayrıştırma yöntemi diyebiliriz.
https://cdn.discordapp.com/attachments/816641278502371389/816646331144732712/unknown.png

.sln'i açtığınızda böyle bir ekranla karşılacaksınız.
Size bahsettiğim gibi sağ tarafta tüm kütüphaneler & kodlar bulunuyor.
İlk başta çok karışık gelecektir fakat yavaş yavaş ısınmaya başlarsınız.
Eğer olayımız Private Server ise buradaki Debug/Release kısmını Release yapmamız gerekir.  x86, 32 bit demektir. x64, 64 bit demektir. Genelde x86 kullanırız.
https://cdn.discordapp.com/attachments/816641278502371389/816647106353168394/unknown.png

Sağ taraftaki kısımdaki server yazan yere sağ tıklayarak menüyü açınız.
https://cdn.discordapp.com/attachments/816641278502371389/816647407252144169/unknown.png

En altta Özellikler yazan kısıma tıklayınız.
https://cdn.discordapp.com/attachments/816641278502371389/816647407252144169/unknown.png

Burada sadece bizi ilgilendiren kısım Windows SDK Sürümü ve Platform Araç Takımı'dır.
Peki, şimdi soracaksınız neye göre seçiyoruz bunları?
Windows SDK Sürümü genelde 10.0'dan başka olan sürümler tavsiye edilir.
https://cdn.discordapp.com/attachments/816641278502371389/816647953056923648/unknown.png
Platform Araç Takımı kısmında genelde programların hangi Visual Studio sürümü ile derleneceği belirtirler.
https://cdn.discordapp.com/attachments/816641278502371389/816648492126699570/unknown.png
Genelde 2019 (v142) seçilir.
Bu adımları bitirdiyseniz size ufaktan Derleme olayını bahsedeyim.
https://cdn.discordapp.com/attachments/816641278502371389/816649408861962240/unknown.png

Bahsettiğim menüyü açtıktan sonra Derle kısmına bastıktan sonra derlenmeye başlayacaktır. Bilgisayarınızın hızına göre değişiklik gösterebilir.
Derledikten sonra .cpp dosyalarının olduğu yerden Release klasörün içindeki server.exe'yi klasörlerinizin içine atınız.
https://cdn.discordapp.com/attachments/816641278502371389/816650238483497001/unknown.png
