EMCC=emcc

all: code.c
	$(EMCC) -O3 -s WASM=1 -o main.js -s EXTRA_EXPORTED_RUNTIME_METHODS='["getValue", "setValue"]' -s EXPORTED_FUNCTIONS="['_calloc', '_findpath']" -s EXPORT_ES6=1 -s MODULARIZE=1 code.c
