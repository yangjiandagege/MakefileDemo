include env.mk

CLIENT_OBJ = $(OBJPATH)/client.o
CLIENT_OBJ += $(OBJPATH)/login.o

SERVER_OBJ = $(OBJPATH)/server.o
SERVER_OBJ += $(OBJPATH)/login.o

all:linklist client server

client:login
	$(MAKE) -C $(BASEPATH)/src/client
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -o $(BASEPATH)/target/$@ $(INCLUDE) $(DYNAMIC_LIB_PATH)/linklist.so

server:login
	$(MAKE) -C $(BASEPATH)/src/server
	$(CC) $(CFLAGS) $(SERVER_OBJ) -o $(BASEPATH)/target/$@ $(INCLUDE) $(DYNAMIC_LIB_PATH)/linklist.so

login:
	$(MAKE) -C $(BASEPATH)/src/login

linklist:
	$(MAKE) -C $(BASEPATH)/src/linklist

clean:
	$(RM) $(OBJPATH)/*.o
	$(RM) $(BASEPATH)/target/*
	$(RM) -R $(BASEPATH)/lib/dynamic/* $(BASEPATH)/lib/static/*

clear:
	$(RM) $(BASEPATH)/bin/*.o

tar:
	make clean
	@tar -cvf `date +%Y%m%d-%H%M%S`.tar `ls|grep -v '.tar'`
