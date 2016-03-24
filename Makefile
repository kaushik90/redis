server: redis_server.c tcpsocket/soket.c
	gcc -o redis_server \
			ds/newstring.c \
			ds/linkedlist.c \
			ds/hashtable.c \
			tcpsocket/soket.c \
			redis_server.c