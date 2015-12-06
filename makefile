MySqlConnector.o: MySqlConnector.cc
	g++ -c MySqlConnector.cc -lmysqlclient -L mysql-lib/ -Imysql-include/

libDBConnector.a: MySqlConnector.o
	ar -r libDBConnector.a MySqlConnector.o

test: test.cc libDBConnector.a 
	g++ -o mytest test.cc -L. -L mysql-lib/ -Imysql-include/ -lDBConnector -lmysqlclient -g

signup: signUp.c libDBConnector.a
	g++ -o signup  signUp.c -L. -L mysql-lib/ -Imysql-include/ -lDBConnector -lmysqlclient -g

libImSocket.a: Socket.cc ClientSock.cc ServerSock.cc
	g++ -c basicSocket.o Socket.cc
	g++ -c clientSocket.o ClietnSock.cc
	g++ -c serverSocket.o ServerSock.cc
	ar -r libImSocket.a basicSocet.o clientSocket.o serverSocket.o
