# 🧨 Campo Minado em C com Raylib

Este projeto é uma implementação do jogo **Campo Minado**, desenvolvido em **C** utilizando a biblioteca gráfica **[Raylib](https://www.raylib.com/)**.

## ⚙️ Requisitos

- macOS
- [Homebrew](https://brew.sh/)
- Compilador GCC ou Clang
- Biblioteca Raylib

## 📦 Instalando dependências no macOS

1. **Instale o Homebrew (caso ainda não tenha):**

   Abra o terminal e execute:
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

2. **Instale o Raylib:**
```bash
brew install raylib

3. **Verifique se o Raylib foi instalado corretamente:**
```bash
pkg-config --cflags --libs raylib

## 🛠️ Compilando o projeto:
Como o projeto está estruturado em múltiplos arquivos, você deve compilá-lo da seguinte forma:

No terminal, vá até a raiz do projeto (onde está localizada a pasta src/):
cd /caminho/para/o/projeto

Compile com o seguinte comando:
gcc src/*.c -Iinclude -o campominado -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

Executando o jogo

Se a compilação for bem-sucedida, execute o jogo com:

./campo_minado
