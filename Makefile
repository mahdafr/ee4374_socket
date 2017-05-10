bankClient: bankClient.o
	gcc -g -o $@ $^ -lm

bankClient.o: bankClient.c banking.h
	gcc -g -c bankClient.c

clean:
	rm *.o; rm bankClient

cleanWin:
	del *.o; del bankClient