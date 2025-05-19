# 🧨 Campo Minado em C com Raylib

Campo Minado é uma implementação simples e interativa do clássico jogo Minesweeper, desenvolvida em C com a biblioteca gráfica **[Raylib](https://www.raylib.com/)**. O projeto foi pensado para rodar tanto no macOS quanto no Linux, sem depender de frameworks externos.

---

## ⚙️ Requisitos macOS

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
 ```

### 2. Instalar a raylib: 
Abra o terminal e execute:
```bash
brew install raylib
```

---

## 🛠️ Compilando o projeto
Como o projeto está estruturado em múltiplos arquivos, você deve compilá-lo da seguinte forma:
### 1. Navegue até a raiz do projeto:
```bash
cd/campominado
```
### 2. Use os comandos na ordem:
```bash
make clean
make
```

### ▶ 3. Executando o jogo
Se a compilação for bem-sucedida, execute o jogo com:
```bash
./campo_minado
```
---

## 🛠️ Requisitos Linux

* Linux Ubuntu
* Compilador GCC
* Biblioteca Raylib

---

### 📝 Instalando dependências no Ubuntu

1. **Atualize o sistema e instale o GCC:**
   Abra o terminal e execute:

   ```bash
   sudo apt update
   sudo apt install build-essential
   ```

2. **Instale a biblioteca Raylib:**
   Abra o terminal e execute:

   ```bash
   sudo apt install libraylib-dev
   ```

---

### ⚙️ Compilando o projeto

Como o projeto está estruturado em múltiplos arquivos, você deve compilá-lo da seguinte forma:

1. **Navegue até a raiz do projeto (onde está a pasta src/):**

   ```bash
   cd /campominado
   ```

2. **Compile com o comando:**

   ```bash
   gcc src/*.c -o campominado -lraylib -lm -lpthread -ldl -lrt -lX11
   ```

---

### ▶️ Executando o jogo

Se a compilação for bem-sucedida, execute o jogo com:

```bash
./campo_minado
```

Divirta-se jogando Campo Minado!
