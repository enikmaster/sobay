frontend:
	gcc -o frontend ./frontend/frontend.c ./frontend/frontendFunctions.c

backend:
	gcc -o backend ./backend/backend.c ./backend/users_lib.o ./backend/backendFuctions.c

all:
	gcc -o frontend ./frontend/frontend.c ./frontend/frontendFunctions.c 
	gcc -o backend ./backend/backend.c ./backend/users_lib.o ./backend/backendFuctions.c

clean:
	rm ./frontend/frontend
	rm ./backend/backend