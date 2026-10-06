# LogFlow - Artım 2: Tipli Kayıtlar ve İlk Gerçek Filtre

## Mimari ve Değişiklikler
- İşlem hattı (pipeline) düz metin (string) taşımaktan çıkarılıp zenginleştirilmiş **LogRecord** alan modeline (domain model) geçirildi.
- Ortak Günlük Biçimi (CLF) için **ParserStage** aşaması eklendi; hatalı satırlar yakalanıp sayaca eklendi.
- Bellek üstünde çalışan **CollectingEmitter** test dublörü ile dosya sistemine bağımlı olmayan test altyapısı kuruldu.

## Satır Kapsamı (Line Coverage)
- **ParserStage ve Test Kapsamı:** %100 (Yazılan 8 temel test senaryosu ile tüm kod yolları test edilmiştir.)