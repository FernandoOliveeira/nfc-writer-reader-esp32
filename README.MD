# 🔗 Gravador de Tags NFC com ESP32 + PN532

Este projeto permite gravar **tags NFC regraváveis (NTAG213/215/216)** com **links personalizados** (como Instagram, WhatsApp, sites ou cartões de visita digitais), utilizando um **ESP32 DevKit V1** e o **módulo PN532 V3** via I2C.

---

## 📦 Funcionalidades

- Detecta tags NFC de 13,56 MHz (ISO14443-A)
- Grava mensagens NDEF padrão com links de sites ou redes sociais
- Compatível com **NTAG213, NTAG215, NTAG216**
- Pode ser lido por qualquer celular com NFC (Android e iOS)
- Inclui monitor serial para debug
- Código limpo, comentado e expansível

---

## 🛠 Requisitos

- ESP32 DevKit V1
- Módulo NFC PN532 V3 (via I2C)
- Tag NFC NTAG215 (ou similar)
- Cabo micro USB
- VSCode com extensão PlatformIO **ou** Arduino IDE

---

## 🔧 Como usar

### 1. Clone o projeto

```bash
git clone https://github.com/seu-usuario/gravador-nfc-esp32.git
cd gravador-nfc-esp32
```

### 2. Abra no VSCode (PlatformIO)

- Instale a extensão **PlatformIO IDE**
- Abra a pasta do projeto
- Verifique se a placa está definida como `esp32dev` no `platformio.ini`
- Conecte o ESP32 via USB

### 3. Configure o link

Edite o link dentro do arquivo `src/main.cpp`:

```cpp
const char* url = "instagram.com/seuusuario";
```

Você pode trocar para qualquer URL curta, como:
- `instagram.com/seunome`
- `wa.me/5511999999999`
- `linktr.ee/seuprojeto`

### 4. Faça o upload

Clique em **"Upload"** no VSCode (ícone de seta), ou use:

```bash
pio run --target upload
```

### 5. Grave na tag

- Aproxime a tag NFC no leitor
- Verifique no Monitor Serial se a gravação foi concluída com sucesso

---

## 📱 Como testar

Aproxime a tag NFC de um celular com NFC habilitado. Ele deverá:
- Abrir o link gravado no navegador
- Ou redirecionar automaticamente para o app (Instagram, WhatsApp, etc.)

---

## 🚧 Próximos passos (em andamento)

- Menu com múltiplos links selecionáveis via botão
- Bloqueio da tag após gravação (somente leitura)
- Modo de leitura
- Adaptar um display LCD para visualizar a leitura e gravação

---

## 🛡 Segurança

Este projeto **não armazena nenhuma informação sensível por padrão**. Certifique-se de **não inserir dados pessoais no código** antes de publicá-lo em repositórios públicos.

---

## 📄 Licença

Distribuído sob a licença MIT. Sinta-se livre para usar, modificar e compartilhar!