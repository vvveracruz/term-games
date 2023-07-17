hello: clean
	g++ -std=c++11 src/hello.cpp -o Hello
	./Hello

bounce: clean
	g++ -lcurses src/bounce.cpp -o  Bounce
	./Bounce

bounce2: clean
	g++ -lcurses src/bounce2.cpp -o  Bounce2
	./Bounce2

snake: clean
	g++ -std=c++11 -lcurses src/snake.cpp -o  Snake
	./Snake

bounce3: clean
	g++ -std=c++11 -lcurses src/bounce3.cpp -o Bounce3
	./Bounce3

clean:
	rm -f ./Hello ./Bounce ./Bounce2 ./Snake ./Bounce3