all: driver client server

driver: driver.o statemodel.o actions.o state.o accepting.o processing.o manufacturing.o shipping.o
	gcc driver.o statemodel.o actions.o state.o accepting.o processing.o manufacturing.o shipping.o -o driver 

mySock.o: mySock.c mySock.h
	gcc mySock.c -o mySock.o

client: mySock.o client.o
	gcc client.o -o client 

server: mySock.o server.o
	gcc server.o -o server 

client.o: client.c
	gcc -c client.c 

server.o: server.c
	gcc -c server.c 

driver.o: driver.c actions.h statemodel.h
	gcc -c driver.c

actions.o: actions.c actions.h
	gcc -c actions.c 

statemodel.o: actions.h statemodel.h statemodel.c 
	gcc -c statemodel.c

state.o: state.h state.c
	gcc -c state.c 
	
accepting.o: state.h accepting.h accepting.c
	gcc -c accepting.c

processing.o: state.h processing.h processing.c
	gcc -c processing.c

manufacturing.o: state.h manufacturing.h manufacturing.c
	gcc -c manufacturing.c

shipping.o: state.h shipping.h shipping.c
	gcc -c shipping.c

clean:
	rm *.o ; rm driver ; rm client ; rm server

