# --- Değişkenler ---
CC = gcc
CFLAGS = -Wall -Wextra -g
LIBS = -lpthread  # Thread kütüphanesini buraya ekledik

# --- Hedefler ---

all: panel rocket 

# Panel hedefi: Hem panel.c hem de ringbuffer.c'yi BİRLİKTE derler
# Bağımlılıklar kısmına ringbuffer.c'yi de ekledik.
panel: panel.c ringbuffer.c
	$(CC) $(CFLAGS) panel.c ringbuffer.c -o panel $(LIBS)

# Rocket hedefi: Eğer rocket de buffer kullanıyorsa onu da böyle derle
rocket: rocket.c ringbuffer.c
	$(CC) $(CFLAGS) rocket.c ringbuffer.c -o rocket $(LIBS)

# Temizlik
clean:
	rm -f panel rocket