# Variables
LISTING_A_RAIZ=../../..



# Capitulo 2
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



# Capitulo 3
listing-3.1: 
	rm -rf bin/capitulo_3/print-pid.o && \
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.1 && \
	gcc $(CFLAGS) -o print-pid.o print-pid.c && \
	mv print-pid.o $(LISTING_A_RAIZ)/bin/capitulo_3

listing-3.2: 
	rm -rf bin/capitulo_3/system.o && \
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.2 && \
	gcc $(CFLAGS) -o system.o system.c && \
	mv system.o $(LISTING_A_RAIZ)/bin/capitulo_3

listing-3.3: 
	rm -rf bin/capitulo_3/fork.o &&\
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.3 && \
	gcc $(CFLAGS) -o fork.o fork.c && \
	mv fork.o $(LISTING_A_RAIZ)/bin/capitulo_3

listing-3.4: 
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.4 && gcc $(CFLAGS) -o fork-exec.o fork-exec.c && \
	mv fork-exec.o $(LISTING_A_RAIZ)/bin/capitulo_3