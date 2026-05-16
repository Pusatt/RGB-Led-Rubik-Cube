#include <Adafruit_NeoPixel.h>
#include <BluetoothSerial.h>
#include <Arduino.h>

BluetoothSerial serialBT;
#define PIN 18
#define NUMPIXELS 54
#define ANIM_STEPS 8       // Animasyon adım sayısı
#define ANIM_DELAY 18      // Her adım arası ms (toplam ~144ms)

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[] = {
  pixels.Color(150, 150, 150),
  pixels.Color(0, 150, 0),
  pixels.Color(150, 150, 0),
  pixels.Color(150, 0, 0),
  pixels.Color(0, 0, 150),
  pixels.Color(180, 45, 0)
};

int values[] = {0,0,0,1,1,1,2,2,2,2,2,2,1,1,1,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,5,5,5,4,4,4,3,3,3,3,3,3,4,4,4,5,5,5,6,6,6};

int RRotate[]  = {26,25,24,23,22,21,20,19,18,48,41,30,  27,44,45,46,47,42,29,28,  23,22,21,20,19,18,48,41,30,26,25,24,  45,46,47,42,29,28,27,44};
int RiRotate[] = {23,22,21,20,19,18,48,41,30,26,25,24,  27,44,45,46,47,42,29,28,  26,25,24,23,22,21,20,19,18,48,41,30,  29,28,27,44,45,46,47,42};
int LRotate[]  = {0,1,2,3,4,5,6,7,8,32,39,50,           51,52,53,36,35,34,33,38,  3,4,5,6,7,8,32,39,50,0,1,2,           53,36,35,34,33,38,51,52};
int LiRotate[] = {0,1,2,3,4,5,6,7,8,32,39,50,           51,52,53,36,35,34,33,38,  32,39,50,0,1,2,3,4,5,6,7,8,           33,38,51,52,53,36,35,34};
int URotate[]  = {3,14,21,51,52,53,48,49,50,45,46,47,   0,1,2,15,20,19,18,17,     51,52,53,48,49,50,45,46,47,3,14,21,   18,17,0,1,2,15,20,19};
int UiRotate[] = {3,14,21,51,52,53,48,49,50,45,46,47,   0,1,2,15,20,19,18,17,     45,46,47,3,14,21,51,52,53,48,49,50,   2,15,20,19,18,17,0,1};
int DRotate[]  = {5,12,23,27,28,29,30,31,32,33,34,35,   6,11,24,25,26,9,8,7,      27,28,29,30,31,32,33,34,35,5,12,23,   24,25,26,9,8,7,6,11};
int DiRotate[] = {5,12,23,27,28,29,30,31,32,33,34,35,   6,11,24,25,26,9,8,7,      33,34,35,5,12,23,27,28,29,30,31,32,   8,7,6,11,24,25,26,9};
int FRotate[]  = {2,15,20,45,44,27,24,11,6,35,36,53,    3,14,21,22,23,12,5,4,     45,44,27,24,11,6,35,36,53,2,15,20,    21,22,23,12,5,4,3,14};
int FiRotate[] = {2,15,20,45,44,27,24,11,6,35,36,53,    3,14,21,22,23,12,5,4,     35,36,53,2,15,20,45,44,27,24,11,6,    5,4,3,14,21,22,23,12};
int BRotate[]  = {29,42,47,18,17,0,51,38,33,8,9,26,     48,49,50,39,32,31,30,41,  18,17,0,51,38,33,8,9,26,29,42,47,     50,39,32,31,30,41,48,49};
int BiRotate[] = {29,42,47,18,17,0,51,38,33,8,9,26,     48,49,50,39,32,31,30,41,  8,9,26,29,42,47,18,17,0,51,38,33,     30,41,48,49,50,39,32,31};

// Tüm etkilenen LED indekslerini bir diziye topla (çevre 12 + yüz 8 = 20)
void getAffectedLEDs(int a[], int out[], int &count) {
  count = 0;
  // Kaynak çevre (0-11) ve yüz (12-19) — tekrarları atla
  for (int i = 0; i < 20; i++) {
    bool found = false;
    for (int j = 0; j < count; j++) {
      if (out[j] == a[i]) { found = true; break; }
    }
    if (!found) out[count++] = a[i];
  }
  // Hedef çevre (20-31) ve yüz (32-39)
  for (int i = 20; i < 40; i++) {
    bool found = false;
    for (int j = 0; j < count; j++) {
      if (out[j] == a[i]) { found = true; break; }
    }
    if (!found) out[count++] = a[i];
  }
}

// Tek bir rengin parlaklığını 0.0-1.0 arasında ölçekle
uint32_t scaleColor(uint32_t color, float brightness) {
  uint8_t r = ((color >> 16) & 0xFF) * brightness;
  uint8_t g = ((color >> 8)  & 0xFF) * brightness;
  uint8_t b = ( color        & 0xFF) * brightness;
  return pixels.Color(r, g, b);
}

void animateMove(int a[]) {
  int affected[40];
  int count = 0;
  getAffectedLEDs(a, affected, count);

  // --- FAZ 1: Etkilenen LED'leri söndür ---
  for (int step = ANIM_STEPS; step >= 0; step--) {
    float brightness = (float)step / ANIM_STEPS;
    for (int i = 0; i < count; i++) {
      int idx = affected[i];
      uint32_t col = colors[values[idx]];
      pixels.setPixelColor(idx, scaleColor(col, brightness));
    }
    pixels.show();
    delay(ANIM_DELAY);
  }

  // --- Mantıksal hamleyi uygula ---
  // Çevre
  uint32_t tempColor[12];
  for (int i = 0; i < 12; i++) tempColor[i] = values[a[i]];
  for (int i = 0; i < 12; i++) values[a[20 + i]] = tempColor[i];

  // Yüz
  uint32_t faceColor[8];
  for (int i = 0; i < 8; i++) faceColor[i] = values[a[12 + i]];
  for (int i = 0; i < 8; i++) values[a[32 + i]] = faceColor[i];

  // --- FAZ 2: Yeni renklerde yak ---
  for (int step = 0; step <= ANIM_STEPS; step++) {
    float brightness = (float)step / ANIM_STEPS;
    for (int i = 0; i < count; i++) {
      int idx = affected[i];
      uint32_t col = colors[values[idx]];
      pixels.setPixelColor(idx, scaleColor(col, brightness));
    }
    pixels.show();
    delay(ANIM_DELAY);
  }
}

void setup() {
  serialBT.begin("Project QRKLY");
  pixels.begin();
  setInitialColors();
}

void loop() {
  if (serialBT.available() > 0) {
    char command = serialBT.read();
    switch (command) {
      case 'r': animateMove(RRotate);  break;
      case 's': animateMove(RiRotate); break;
      case 'l': animateMove(LRotate);  break;
      case 'm': animateMove(LiRotate); break;
      case 'u': animateMove(URotate);  break;
      case 'v': animateMove(UiRotate); break;
      case 'd': animateMove(DRotate);  break;
      case 'e': animateMove(DiRotate); break;
      case 'f': animateMove(FRotate);  break;
      case 'g': animateMove(FiRotate); break;
      case 'b': animateMove(BRotate);  break;
      case 'c': animateMove(BiRotate); break;
    }
  }
}

void setInitialColors() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, colors[values[i]]);
  }
  pixels.show();
}
