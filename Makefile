build: lanParty.o
	gcc lanParty.o -o lanParty

lanParty.o: tema.c List.h Queue.h Stack.h Tree.h Utils.h
	gcc -c tema.c -o lanParty.o

run: tema.c
	./lanParty c.in d.in r.out

.PHONY: clean
clean:
	rm -f lanParty.o