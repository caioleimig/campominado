CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

# Verificação do sistema operacional
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)  # macOS
    RAYLIB_LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
else  # Linux
    RAYLIB_LIBS = -lraylib -lGL -lpthread -ldl -lrt -lm
endif

TARGET = campo_minado
SRCDIR = src
OBJDIR = obj

# Pega todos os arquivos .c na pasta src
SRCS = $(wildcard $(SRCDIR)/*.c)  
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(RAYLIB_LIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)
