
listing-2.1:
	mkdir -p bin/capitulo_2; \
	cd src/capitulo_2/2.1; \
	gcc $(CFLAGS) -c arglist.c; \
	mv arglist.o ../../../bin/capitulo_2/

listing-2.2:
	mkdir -p bin/capitulo_2; \
	cd src/capitulo_2/2.2; \
	gcc $(CFLAGS) -c getopt_long.c; \
	mv getopt_long.o ../../../bin/capitulo_2/
