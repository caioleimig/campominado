# 🧨 Campo Minado em C com Raylib

Este projeto é uma implementação do clássico **Campo Minado**, desenvolvido em **C** utilizando a biblioteca gráfica **[Raylib](https://www.raylib.com/)**.

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
### 2. use o make clean
```bash
make clean
```
### 3. use o make 
```bash
make 
```
## ▶ 4. Executando o jogo
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
   cd /caminho/para/o/projeto
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

