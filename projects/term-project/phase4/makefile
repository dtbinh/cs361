all: driver client server

driver: driver.o statemodel.o actions.o state.o accepting.o processing.o manufacturing.o shipping.o
	gcc driver.o statemodel.o actions.o state.o accepting.o processing.o manufacturing.o shipping.o -o driver 

client: client.o
	gcc client.o -o client 

server: server.o
	gcc server.o -o server 

client.o: client.c message.h
	gcc -c client.c -o client.o 

server.o: server.c
	gcc -c server.c -o server.o 

driver.o: driver.c actions.h statemodel.h
	gcc -c driver.c

actions.o: actions.c actions.h
	gcc -c actions.c -o actions.o 

statemodel.o: actions.h statemodel.h statemodel.c 
	gcc -c statemodel.c

state.o: state.h state.c
	gcc -c state.c -o state.o
	
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

