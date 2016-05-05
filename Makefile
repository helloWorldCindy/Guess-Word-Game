DEBUG= 
EXECS= main

exe:	$(EXECS)

main:	main.c
	gcc $(DEBUG) -o main main.c

clean:
	rm -f main
