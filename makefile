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
	gcc $(CFLAGS) -o getopt_long getopt_long.c; \
	mv getopt_long ../../../bin/capitulo_2/

listing-2.3:
	mkdir -p bin/capitulo_2; \
	cd src/capitulo_2/2.3; \
	gcc -o print-env print-env.c; \
	mv print-env ../../../bin/capitulo_2/	

listing-2.4:
	mkdir -p bin/capitulo_2; \
	cd src/capitulo_2/2.4; \
	gcc -o client client.c; \
	mv client ../../../bin/capitulo_2/	

listing-2.6:
	mkdir -p bin/capitulo_2; \
	cd src/capitulo_2/2.6; \
	gcc -o readfile readfile.c; \
	mv readfile ../../../bin/capitulo_2/	
	@echo "No se olvide de mantener el archivo texto.txt en la carpeta bin/capitulo_2"


listing-2.8:
	@echo "Use el listing-2.7 porque van juntos"


listing-2.9:
	rm -rf bin/capitulo_2/tifftest.o && \
	rm -rf bin/capitulo_2/playa.tiff && \
	mkdir -p bin/capitulo_2 && \
	cd src/capitulo_2/2.9 && \
	gcc $(CFLAGS) -o tifftest.o tifftest.c -ltiff && \
	mv tifftest.o $(LISTING_A_RAIZ)/bin/capitulo_2 && \
	cp ./playa.tiff $(LISTING_A_RAIZ)/bin/capitulo_2


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
	rm -rf bin/capitulo_3/fork.o && \
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.3 && \
	gcc $(CFLAGS) -o fork.o fork.c && \
	mv fork.o $(LISTING_A_RAIZ)/bin/capitulo_3

listing-3.4: 
	rm -rf bin/capitulo_3/fork-exec.o && \
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.4 && \
	gcc $(CFLAGS) -o fork-exec.o fork-exec.c && \
	mv fork-exec.o $(LISTING_A_RAIZ)/bin/capitulo_3

listing-3.5:
	rm -rf bin/capitulo_3/sigusr1.o && \
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.5 && \
	gcc $(CFLAGS) -o sigusr1.o sigusr1.c && \
	mv sigusr1.o $(LISTING_A_RAIZ)/bin/capitulo_3

listing-3.6: 
	rm -rf bin/capitulo_3/zombie.o && \
	mkdir -p bin/capitulo_3 && \
	cd src/capitulo_3/3.6 && \
	gcc $(CFLAGS) -o zombie.o zombie.c && \
	mv zombie.o $(LISTING_A_RAIZ)/bin/capitulo_3


# Capitulo 4
listing-4.13:
	rm -rf bin/capitulo_4/spin-condvar.o && \
	mkdir -p bin/capitulo_4 && \
	cd src/capitulo_4/4.13 && \
	cc $(CFLAGS) -o spin-condvar.o spin-condvar.c -lpthread && \
	mv spin-condvar.o $(LISTING_A_RAIZ)/bin/capitulo_4

listing-4.14:
	rm -rf bin/capitulo_4/condvar.o && \
	mkdir -p bin/capitulo_4 && \
	cd src/capitulo_4/4.14 && \
	cc $(CFLAGS) -o condvar.o condvar.c -lpthread && \
	mv condvar.o $(LISTING_A_RAIZ)/bin/capitulo_4

listing-4.15:
	rm -rf bin/capitulo_4/thread-pid.o && \
	mkdir -p bin/capitulo_4 && \
	cd src/capitulo_4/4.15 && \
	cc $(CFLAGS) -o thread-pid.o thread-pid.c -lpthread && \
	mv thread-pid.o $(LISTING_A_RAIZ)/bin/capitulo_4