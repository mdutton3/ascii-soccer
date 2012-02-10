soccer.o: soccer.c soccer.h players.h
	gcc -w -c soccer.c

soccer: soccer.o 
	gcc -w soccer.o -o soccer -L./ -lcurses -lm \
		-least -leastcommon -lwest -lwestcommon

soccerboth: soccer.o 
	gcc -w soccer.o -o soccer -L./ -lcurses -ltermcap -lm \
		-least -lcommon -lwest 

clean: 
	rm -f *.o
	rm -f *.a
	rm -f soccer
	rm -f core

reallyclean: clean
	cleanteams
