
build:
	mkdir -p out && g++ ./*.cpp -o ./out/ising

run *ARGS:
	./out/ising {{ARGS}}