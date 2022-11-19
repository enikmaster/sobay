frontend:
	gcc -o frontend ./frontend/frontend.c

backend:
	gcc -o backend ./backend/backend.c

all:
	gcc -o ./frontend/frontend ./frontend/frontend.c
	gcc -o ./frontend/backend ./backend/backend.c

clean:
	rm ./frontend/frontend
	rm ./backend/backend