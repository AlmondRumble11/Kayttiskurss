full_teht1: vk9teht1.o vk9teht1_function.o
	gcc vk9teht1.o vk9teht1_function.o -o full_teht1 -std=c99 -Wall -pedantic
vk9teht1.o: vk9teht1.c vk9teht1.h
	gcc vk9teht1.c -c -std=c99 -Wall -pedantic
vk9teht1_fuction.o: vk9teht1_function.c vk9teht1.h
	gcc vk9teht1_function -c -std=c99 -Wall -pedantic
	
