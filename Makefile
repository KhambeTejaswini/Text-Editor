project : editormain.o editorfunctions.o editords.o 
	cc editormain.o editorfunctions.o editords.o -o project -lncurses
editormain.o: editormain.c editords.h editorfunctions.h
	cc -Wall -c editormain.c
editorfunctions.o: editorfunctions.c editorfunctions.h editords.h
	cc -Wall -c editorfunctions.c
editords.o: editords.c editords.h
	cc -Wall -c editords.c
