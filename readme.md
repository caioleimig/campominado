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
![image](https://github.com/user-attachments/assets/de8bf39d-9bcb-4f50-8170-bd5c0b53e669)


### 2. Verificar se o Raylib foi instalado corretamente
Abra o terminal e execute:

![image](https://github.com/user-attachments/assets/205f656d-f192-464f-b8a0-2aefaf67c3b2)

---

## 🛠️ Compilando o projeto
Como o projeto está estruturado em múltiplos arquivos, você deve compilá-lo da seguinte forma:
### 1. Navegue até a raiz do projeto (onde está a pasta src/):
![image](https://github.com/user-attachments/assets/4efa8f0a-7e96-4bcc-a5d8-06ffb08759b8)

### 2. Compile com o comando:

![image](https://github.com/user-attachments/assets/ffa55fcb-af8b-4638-93ff-6e4c1a374ecf)

---

## ▶️ Executando o jogo
Se a compilação for bem-sucedida, execute o jogo com:

![image](https://github.com/user-attachments/assets/466ad94e-5917-40fc-979d-d8ff13aa8e3f)


🚩 **Campo Minado em C com Raylib**

Este projeto é uma implementação do clássico Campo Minado, desenvolvido em C utilizando a biblioteca gráfica Raylib.

---

### 🛠️ Requisitos

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
./campominado
```

Divirta-se jogando Campo Minado!

