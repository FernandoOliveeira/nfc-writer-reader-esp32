#include <Wire.h>
#include <Adafruit_PN532.h>

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

const char* url = "LINK";  // sem https://

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando NFC...");

  nfc.begin();
  if (!nfc.getFirmwareVersion()) {
    Serial.println("PN532 não detectado.");
    while (1);
  }

  nfc.SAMConfig();
  Serial.println("Aproxime a tag NFC...");
}

void loop() {
  uint8_t uid[] = {0};
  uint8_t uidLength;

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    Serial.println("Tag detectada!");

    // 1. Construir payload NDEF para um URI
    const uint8_t uriPrefix = 0x03;  // 0x03 = "https://"
    size_t urlLen = strlen(url);
    size_t payloadLen = 1 + urlLen;

    // 2. Criar a estrutura NDEF completa
    uint8_t ndefMessage[128];  // sobra espaço
    int idx = 0;

    // TLV block
    ndefMessage[idx++] = 0x03;                 // NDEF TLV
    ndefMessage[idx++] = payloadLen + 5;       // Tamanho do NDEF
    ndefMessage[idx++] = 0xD1;                 // MB/ME/SR/TNF=1
    ndefMessage[idx++] = 0x01;                 // Tamanho do tipo
    ndefMessage[idx++] = payloadLen;           // Tamanho do payload
    ndefMessage[idx++] = 0x55;                 // Tipo: URI
    ndefMessage[idx++] = uriPrefix;            // Prefixo URI

    memcpy(&ndefMessage[idx], url, urlLen);
    idx += urlLen;

    ndefMessage[idx++] = 0xFE;  // Terminador TLV

    // 3. Gravar em blocos de 4 bytes a partir da página 4
    int page = 4;
    for (int i = 0; i < idx; i += 4) {
      uint8_t buffer[4] = {0x00, 0x00, 0x00, 0x00};
      for (int j = 0; j < 4 && (i + j) < idx; j++) {
        buffer[j] = ndefMessage[i + j];
      }

      if (!nfc.ntag2xx_WritePage(page, buffer)) {
        Serial.print("❌ Erro na página ");
        Serial.println(page);
        return;
      }

      page++;
    }

    Serial.println("✅ Link gravado com sucesso!");
    delay(2000);
  }
}
