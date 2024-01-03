
Task22 : main.o matrix_creator.o matrix_operations.o invertion.o print_matrix.o residual_norm.o synchronizer.o
	g++ main.o matrix_creator.o matrix_operations.o invertion.o print_matrix.o residual_norm.o synchronizer.o -o Task22 -O3 -pthread
	
main.o : main.cpp
	g++ -c main.cpp -o main.o -O3
	
matrix_creator.o : matrix_creator.cpp
	g++ -c matrix_creator.cpp -o matrix_creator.o -O3
	
matrix_operations.o : matrix_operations.cpp
	g++ -c matrix_operations.cpp -o matrix_operations.o -O3
	
invertion.o : invertion.cpp
	g++ -c invertion.cpp -o invertion.o -O3
	
print_matrix.o : print_matrix.cpp
	g++ -c print_matrix.cpp -o print_matrix.o -O3
	
residual_norm.o : residual_norm.cpp
	g++ -c residual_norm.cpp -o residual_norm.o -O3
	
synchronizer.o : synchronizer.cpp
	g++ -c synchronizer.cpp -o synchronizer.o -O3
clean :
	rm Task22 *.o
	
