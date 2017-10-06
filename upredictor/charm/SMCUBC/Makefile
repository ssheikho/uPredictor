#Makefile - simple

CC=g++
CFLAGS=-Wall -c -std=c++0x

#Change this to point to root of S2 repository (for SADB on SMCServer) 
#SADB_PATH=../../../S2/
SADB_PATH=../third-party/CHARM-S2-Project/

LIBRARIES_DIR=../third-party/CHARM-S3-Project/Libraries/Linux/
DIRECTLINK_PATH=../third-party/CHARM-S3-Project/Linux/DirectLink/
LIBRARY_PATH=$(SADB_PATH)
INCLUDE_PATH=$(LIBRARIES_DIR)pacc-1.3.7/
LFLAGS=-L$(LIBRARY_PATH) $(LIBRARIES_DIR)/pacc-1.3.7/PACC/libpacc.a -lpthread
SMC_PROTOCOL_INCLUDES=SMC/SMCProtocol.h SMC/SMCProtocolServer.h
SMC_CLIENT_INCLUDES=SMC/Client.h SMC/SMC.h $(SMC_PROTOCOL_INCLUDES)
SMC_SERVER_INCLUDES=SMC/Server.h SMC/SMC.h $(SMC_PROTOCOL_INCLUDES)
EXEC=SMCClientTest SMCServer SMCClientSim

all: $(EXEC)

SMCClientTest: SMCClientTest.o SMCLib.a $(DIRECTLINK_PATH)DirectLinkLib.a $(LIBRARIES_DIR)pacc-1.3.7/PACC/libpacc.a
	$(CC) -o $@ $^ $(LFLAGS) -I$(SADB_PATH)

SMCServer: SMCServer.o SADBClient.o SMCLib.a $(DIRECTLINK_PATH)DirectLinkLib.a $(LIBRARIES_DIR)pacc-1.3.7/PACC/libpacc.a $(SADB_PATH)libSADB.a
	$(CC) -o $@ $^ $(LFLAGS) -I$(SADB_PATH)

SMCClientSim: SMCClientSim.o SMCLib.a $(DIRECTLINK_PATH)DirectLinkLib.a $(LIBRARIES_DIR)pacc-1.3.7/PACC/libpacc.a
	$(CC) -o $@ $^ $(LFLAGS)

SMCLib.a: Client.o Server.o SMCProtocolServer.o SMCProtocol.o
	ar rcs $@ $^

$(DIRECTLINK_PATH)DirectLinkLib.a:
	make -C $(DIRECTLINK_PATH)

SMCClientTest.o: SMCClient.cpp SMCClient.h $(SMC_CLIENT_INCLUDES)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) $< -o $@

SMCServer.o: SMCServer.cpp SMCServer.h $(SMC_SERVER_INCLUDES)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) -I$(SADB_PATH) $< -o $@

SMCClientSim.o: SMCClientSim.cpp SMCClientSim.h $(SMC_CLIENT_INCLUDES)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) $< -o $@

SMCProtocolServer.o: SMCProtocolServer.cpp $(SMC_PROTOCOL_INCLUDES)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) $< -o $@

SMCProtocol.o: SMCProtocol.cpp SMC/SMCProtocol.h
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) $< -o $@

Client.o: Client.cpp $(SMC_CLIENT_INCLUDES)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) $< -o $@

SADBClient.o: SADBClient.cpp $(SMC_CLIENT_INCLUDES)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) -I$(SADB_PATH) $< -o $@

Server.o: Server.cpp $(SMC_SERVER_INCLUDES)
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -I$(DIRECTLINK_PATH) $< -o $@

force: clean $(EXEC)

forceall: cleanall $(EXEC)

.PHONY: clean cleanall mrproper force update commit

cleanall: clean
	make -C $(DIRECTLINK_PATH) clean

mrproper: clean
	rm -rf $(EXEC) SMCLib.a
	@echo "Exec and library cleaned"

clean:
	rm -rf *.o
	@echo "Objects cleaned"

update:
	svn update
        
commit: 
	svn commit

#end of Makefile 
