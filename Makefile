PROJECT_NAME = ConsoleApplication
C_FILES = $(wildcard src/*.c)
O_FILES = $(patsubst %.c, %.o, $(C_FILES))


ALL_O_FILES = $(O_FILES) main.o

ConsoleApplication : $(ALL_O_FILES)
	gcc $(ALL_O_FILES) -o $(PROJECT_NAME)

main.o : main.c
	gcc -c main.c -o main.o

%.o : %.c 
	gcc -c $< -o $@

clean :
	rm -f $(PROJECT_NAME) $(O_FILES) main.o