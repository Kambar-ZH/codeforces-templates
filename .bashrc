runcpp() {
	g++ -std=c++20 -O2 "$1"
	./a.out
}

unlimit() {
    ulimit -s 268435456
}