server: redis_server.c tcpsocket/soket.c
	gcc -o redis_server \
			ds/newstring.c \
			ds/utils.c \
			ds/linkedlist.c \
			ds/hashtable.c \
			ds/hashmap.c \
			ds/rediscommand.c \
			tcpsocket/soket.c \
			redis_server.c