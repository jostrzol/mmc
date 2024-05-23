
build:
	g++ ./*.cpp -o ./out/ising

run: build
	cd out && ./ising