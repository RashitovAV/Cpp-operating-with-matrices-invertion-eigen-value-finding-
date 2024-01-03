
Task7 : main.o matrix_creator.o solution.o print_matrix.o
	g++ main.o matrix_creator.o solution.o print_matrix.o -o Task7 -O3

main.o : main.cpp
	g++ -c main.cpp -o main.o -O3
	
matrix_creator.o : matrix_creator.cpp
	g++ -c matrix_creator.cpp -o matrix_creator.o -O3
	
solution.o : solution.cpp
	g++ -c solution.cpp -o solution.o -O3
	
print_matrix.o : print_matrix.cpp
	g++ -c print_matrix.cpp -o print_matrix.o -O3

clean :
	rm Task7 *.o
	
