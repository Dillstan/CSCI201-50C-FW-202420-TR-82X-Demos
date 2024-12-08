all: product user main.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g main.cpp user product -o main
user: user.h user.cpp product
	g++ -pedantic-errors -fdiagnostics-color=always -g -c user.cpp -o user
product: product.h product.cpp
	g++ -pedantic-errors -fdiagnostics-color=always -g -c product.cpp -o product