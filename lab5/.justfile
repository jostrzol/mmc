build:
	g++ ./epidemia.cpp -o ./out/epidemia

run: build
	cd out && ./epidemia