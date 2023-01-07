all:
	gcc -pthread -lpthread -o front frontend.c frontendFunctions.c
	gcc -pthread -lpthread -o back backend.c users_lib.o backendFunctions.c


frontend:
	gcc -lpthread -o front frontend.c frontendFunctions.c

backend:
	gcc -lpthread -o back backend.c users_lib.o backendFunctions.c


clean:
	rm front
	rm back
	rm BACKEND
	rm FRONT*