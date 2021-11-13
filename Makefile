src = $(wildcard src/*.c)
arg = -s -o
out = bin/aur-install

build: $(src)
	mkdir -p bin
	$(CC) $(src) $(arg) $(out)

install: $(out)
	cp $(out) /usr/bin/aur-install
