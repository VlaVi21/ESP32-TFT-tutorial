# TFT дисплей на ESP32
> ⚠️ ЦЕЙ ТУТОР ТИМЧАСОВО У РОЗРОБЦІ  

Привіт! 👋 Це мій невеличкий, але інформативний тутор про підключення та використання **TFT дисплею** з мікроконтролером **ESP32**.  
Для роботи ми будемо використовувати бібліотеку **[TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)**.  

Робота йде у **Visual Studio Code** з розширенням **PlatformIO**.

---

## Чому саме TFT_eSPI?

Багато хто починає з бібліотек **Adafruit_ST7735** чи **Adafruit_ILI9341**. Вони прості у використанні та добре документовані, але:  
- вони написані під **конкретні чіпи дисплеїв** (ST7735 або ILI9341),  
- швидкість малювання обмежена — цього вистачає для тексту, але важко для графіків чи анімації.  

Натомість **TFT_eSPI** має переваги:  
✔ Підтримує десятки різних контролерів дисплеїв (ST7735, ST7789, ILI9341, ILI9488 та інші).  
✔ Дуже швидка — оптимізована під ESP32.  
✔ Має купу прикладів: від простого тексту до годинників, графіків і навіть ігор.  
✔ Гнучка — можна легко налаштувати піни, кольори, шрифти.  

Тому я вибрав саме **TFT_eSPI**.

---

## Схема підключення

![Схема пікдлючення TFT дисплею до ESP32](images_2.0/Sh_TFT_V2(final).png)
*Особиста розробка, виконана у графічному редакторі.*

---

## Додавання бібліотеки у Visual Studio Code

У PlatformIO бібліотеки додаються через `platformio.ini` або через пошук у вкладці **Libraries**.  

Приклад у `platformio.ini`:  

```
[env:featheresp32]
platform = espressif32
board = featheresp32
framework = arduino

lib_deps =
    bodmer/TFT_eSPI @ ^2.5.43

monitor_speed = 115200
```
Приклад у вкладці **Libraries**:

![Крок 1](images_2.0/tutorVS_1.png)
*Крок 1*

![Крок 2](images_2.0/tutorVS_1.1.png)
*Крок 2*

![Крок 3](images_2.0/tutorVS_1.2.png)
*Крок 3*

*Раджу обирати версію, рекомендовану розробником цієї бібліотеки.*
---

## Налаштування пінів

У TFT_eSPI всі піни прописуються у файлі:
`.pio/libdeps/<project name>/TFT_eSPI/User_Setup.h`
Шлях до папки

![Шлях до папки з налаштуваннями пінів](images_2.0/VS_Lib_2.0.png)
*Шлях до папки з налаштуваннями пінів*

Там вказуємо:

*Крок 1 - Вибір драйверу дисплея*
![Крок 1](images_2.0/VS_1.jpg)

*Крок 2 - Вибір розміру екрану*
![Крок 2](images_2.0/VS_2.jpg)

*Крок 3 - Тип підключення (варіант ST7735)*
![Крок 3](images_2.0/VS_3.jpg)

*Крок 4 - Призначення пінів для ESP32*
![Крок 4](images_2.0/VS_4.jpg)

*Крок 5 - Налаштування шрифтів, які будуть у бібліотеці*
![Крок 5](images_2.0/VS_5.jpg)

*Крок 6 - Частота SPI (залишаємо все як є)*
![Крок 6](images_2.0/VS_6.jpg)

**Якщо ви підключили все згідно з моїми пінами, можете скопіювати й вставити мій код у папку. Я видалив зайві коментарі й залишив тільки необхідне для стабільної роботи. Але перед цим, будь ласка, уважно прочитайте весь файл.**
```
#define USER_SETUP_INFO User_Setup

#define ST7735_DRIVER       Define additional parameters below for this display

#define TFT_RGB_ORDER TFT_RGB   Colour order Red-Green-Blue

#define TFT_WIDTH  128
#define TFT_HEIGHT 160

#define ST7735_BLACKTAB

#define TFT_MISO -1
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   5   Chip select control pin
#define TFT_DC   16   Data Command control pin
#define TFT_RST  17   Reset pin (could connect to RST pin)

#define LOAD_GLCD    Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2   Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4   Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6   Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890-.apm
#define LOAD_FONT7   Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890-.
#define LOAD_FONT8   Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890-.

#define LOAD_GFXFF   FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

#define SPI_FREQUENCY  27000000

 Optional reduced SPI frequency for reading TFT
#define SPI_READ_FREQUENCY  20000000

 The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here
#define SPI_TOUCH_FREQUENCY  2500000
```
---

## Перевірка роботи ("Hello World")
Завантажте на плату цю прошивку:
```
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  tft.drawString("Hello World", 25, 10, 2); 

  delay(2000);

  tft.fillScreen(TFT_BLACK);
}

void loop() {
  tft.setTextColor(TFT_BLUE, TFT_BLACK); 
  tft.drawString("Hello GitHub", 25, 5, 2);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK); 
  tft.drawString("ESP32-TFT-tutorial", 5, 30, 2);

  tft.setTextColor(TFT_ORANGE, TFT_BLACK); 
  tft.drawString("Size 1", 5, 60, 1);

  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  tft.drawString("Size 4", 5, 75, 4);
}
```
Після прошивки ESP32 відобразить напис Hello World, а через 2 секунди з’явиться текст різного розміру та кольору.

![Приклад роботи дисплею, згідно моєї прошивки](images_2.0/Example_disp.jpg)

У коді, який я додав у вигляді файлу, є коментарі. Їх також можете переглянути.

---

## Приклади з бібліотеки

У TFT_eSPI є багато готових прикладів:
- простий вивід тексту,
- цифровий і аналоговий годинник,
- графіки,
- малювання картинок.

Вони знаходяться у папці Examples. Дуже раджу подивитися приклад з годинником і графіками — це швидко показує можливості бібліотеки.

---

## Особистий досвід

Мій перший серйозний досвід із TFT-дисплеями був у проєкті **метеостанції v1.2**, де я виводив температуру, вологість і стан датчиків.  
👉 [Посилання на метеостанцію](https://github.com/VlaVi21/ESP-NOW_MeteoStation_v1.2) 

---

## Поширені проблеми
- **Дисплей не показує нічого** → перевір живлення (часто треба 3.3V, але є й 5V версії). Також перевір підключення пінів згідно схеми, а також їх вірну ініціалізацію у файлі `User_Setup.h`.
- **Екран білий** → швидше за все, неправильні піни у `User_Setup.h`.
- **Текст "кривий" або кольори не ті** → вкажи правильний чіп контролера дисплею в `User_Setup.h`.  
- **VS Code лається на бібліотеку** → переконайся, що в `platformio.ini` додано `lib_deps = bodmer/TFT_eSPI`. І все відповідає поточній версії бібліотеки.  

---

## Ось і все! Це базовий старт із TFT дисплеєм на ESP32. Дякую за увагу!
