#include <Adafruit_NeoPixel.h>
#include <BluetoothSerial.h>
#include <Arduino.h>
BluetoothSerial serialBT;
#define PIN 18 // Pin Numarasi
#define NUMPIXELS 54 // Pixel Sayisi

// NOTASYONLAR:   R -> r    R'-> s    L -> l    L'-> m    U -> u    U'-> v    D -> d    D'-> e    F -> f    F'-> g    B -> b    B'-> c
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[] = {pixels.Color(150, 150, 150), pixels.Color(0, 150, 0),pixels.Color(150, 150, 0),pixels.Color(150, 0, 0),pixels.Color(0, 0, 150),pixels.Color(180, 45, 0)};
int values[] = {0,0,0,1,1,1,2,2,2,2,2,2,1,1,1,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,5,5,5,4,4,4,3,3,3,3,3,3,4,4,4,5,5,5,6,6,6};

int RRotate[] = {26, 25, 24, 23, 22, 21, 20, 19, 18, 48, 41, 30,    27, 44, 45, 46, 47, 42, 29, 28,     23, 22, 21, 20, 19, 18, 48, 41, 30, 26, 25, 24,   45, 46, 47, 42, 29, 28, 27, 44};
int RiRotate[] = {23, 22, 21, 20, 19, 18, 48, 41, 30, 26, 25, 24,    27, 44, 45, 46, 47, 42, 29, 28,    26, 25, 24, 23, 22, 21, 20, 19, 18, 48, 41, 30,   29, 28, 27, 44, 45, 46, 47, 42};
int LRotate[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 32, 39, 50,    51, 52, 53, 36, 35, 34, 33, 38,   3, 4, 5, 6, 7, 8, 32, 39, 50, 0, 1, 2,   53, 36, 35, 34, 33, 38, 51, 52};
int LiRotate[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 32, 39, 50,    51, 52, 53, 36, 35, 34, 33, 38,    32, 39, 50, 0, 1, 2, 3, 4, 5, 6, 7, 8,   33, 38, 51, 52, 53, 36, 35, 34};
int URotate[] = {3, 14, 21, 51, 52, 53, 48, 49, 50, 45, 46, 47,   0, 1, 2, 15, 20, 19, 18, 17,     51, 52, 53, 48, 49, 50, 45, 46, 47, 3, 14, 21,    18, 17, 0, 1, 2, 15, 20, 19};
int UiRotate[] = {3, 14, 21, 51, 52, 53, 48, 49, 50, 45, 46, 47,   0, 1, 2, 15, 20, 19, 18, 17,      45, 46, 47, 3, 14, 21, 51, 52, 53, 48, 49, 50,    2, 15, 20, 19, 18, 17, 0, 1};
int DRotate[] = {5, 12, 23, 27, 28, 29, 30, 31, 32, 33, 34, 35,   6, 11, 24, 25, 26, 9, 8, 7,    27, 28, 29, 30, 31, 32, 33, 34, 35, 5, 12, 23,   24, 25, 26, 9, 8, 7, 6, 11};
int DiRotate[] = {5, 12, 23, 27, 28, 29, 30, 31, 32, 33, 34, 35,   6, 11, 24, 25, 26, 9, 8, 7,     33, 34, 35, 5, 12, 23, 27, 28, 29, 30, 31, 32,   8, 7, 6, 11, 24, 25, 26, 9};
int FRotate[] = {2, 15, 20, 45, 44, 27, 24, 11, 6, 35, 36, 53,    3, 14, 21, 22, 23, 12, 5, 4,     45, 44, 27, 24, 11, 6, 35, 36, 53, 2, 15, 20,    21, 22, 23, 12, 5, 4, 3, 14};
int FiRotate[] = {2, 15, 20, 45, 44, 27, 24, 11, 6, 35, 36, 53,    3, 14, 21, 22, 23, 12, 5, 4,     35, 36, 53, 2, 15, 20, 45, 44, 27, 24, 11, 6,    5, 4, 3, 14, 21, 22, 23, 12};
int BRotate[] = {29, 42, 47, 18, 17, 0, 51, 38, 33, 8, 9, 26,    48, 49, 50, 39, 32, 31, 30, 41,    18, 17, 0, 51, 38, 33, 8, 9, 26, 29, 42, 47,    50, 39, 32, 31, 30, 41, 48, 49};
int BiRotate[] = {29, 42, 47, 18, 17, 0, 51, 38, 33, 8, 9, 26,    48, 49, 50, 39, 32, 31, 30, 41,     8, 9, 26, 29, 42, 47, 18, 17, 0, 51, 38, 33,    30, 41, 48, 49, 50, 39, 32, 31};

void setup() {
  serialBT.begin("Project QRKLY");
  pixels.begin();
  setInitialColors();
}
void loop() {
  if (serialBT.available() > 0) {
    char command = serialBT.read();
    switch(command) {
      case 'r': rotate(RRotate); break;
      case 's': rotate(RiRotate); break;
      case 'l': rotate(LRotate); break;
      case 'm': rotate(LiRotate); break;
      case 'u': rotate(URotate); break;
      case 'v': rotate(UiRotate); break;
      case 'd': rotate(DRotate); break;
      case 'e': rotate(DiRotate); break;
      case 'f': rotate(FRotate); break;
      case 'g': rotate(FiRotate); break;
      case 'b': rotate(BRotate); break;
      case 'c': rotate(BiRotate); break;
    }
    
  }
}
void setInitialColors() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i,colors[values[i]]);
  }
  pixels.show();
}
void rotate(int a[]) {
  // --- Çevre döngüsü: 12 LED ---
  uint32_t tempColor[12];
  for(int i = 0; i < 12; i++) {
    tempColor[i] = values[a[i]];
  }
  for(int i = 0; i < 12; i++) {
    pixels.setPixelColor(a[20 + i], colors[tempColor[i]]);
    values[a[20 + i]] = tempColor[i];
  }

  // --- Yüz döngüsü: 8 LED ---
  uint32_t faceColor[8];
  for(int i = 0; i < 8; i++) {
    faceColor[i] = values[a[12 + i]];
  }
  for(int i = 0; i < 8; i++) {
    pixels.setPixelColor(a[32 + i], colors[faceColor[i]]);
    values[a[32 + i]] = faceColor[i];
  }

  pixels.show();
}
