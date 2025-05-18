# 🧨 Campo Minado em C com Raylib

Este projeto é uma implementação do clássico **Campo Minado**, desenvolvido em **C** utilizando a biblioteca gráfica **[Raylib](https://www.raylib.com/)**.

---

## ⚙️ Requisitos

- macOS  
- [Homebrew](https://brew.sh/)  
- Compilador **GCC** ou **Clang**  
- Biblioteca **Raylib**

---

## 📦 Instalando dependências no macOS

### 1. Instalar o Homebrew (caso ainda não tenha)

Abra o terminal e execute:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
2. Instalar o Raylib
brew install raylib
3. Verificar se o Raylib foi instalado corretamente
pkg-config --cflags --libs raylib
🛠️ Compilando o projeto

Como o projeto está estruturado em múltiplos arquivos, você deve compilá-lo da seguinte forma:

1. Navegue até a raiz do projeto (onde está a pasta src/):
cd /caminho/para/o/projeto
2. Compile com o comando:
gcc src/*.c -Iinclude -o campominado -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
▶️ Executando o jogo

Se a compilação for bem-sucedida, execute o jogo com:

./campominado
