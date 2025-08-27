#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI(); // створюємо об’єкт дисплею

void setup() {
  tft.init();
  tft.setRotation(2); // повертаємо дисплей на 90 градусів
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  //tft.setTextColor(Колір тексту, колір фону); 

  tft.drawString("Hello World", 25, 10, 2); 
  //tft.drawString("Ваш текст", x, y, розмір тексту); 
  delay(2000);

  tft.fillScreen(TFT_BLACK); //Очищую дисплей від попереднього тексту
}

void loop() {
  //Приклад виводу тексту з різним кольором та розміром шрифту
  tft.setTextColor(TFT_BLUE, TFT_BLACK); 
  tft.drawString("Hello GitHub", 25, 5, 2);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK); 
  tft.drawString("ESP32-TFT-tutorial", 5, 30, 2);

  tft.setTextColor(TFT_ORANGE, TFT_BLACK); 
  tft.drawString("Size 1", 5, 60, 1);

  tft.setTextColor(TFT_GREEN, TFT_BLACK); 
  tft.drawString("Size 4", 5, 75, 4);
}