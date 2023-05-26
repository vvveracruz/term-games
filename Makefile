hello: clean
	g++ -std=c++11 hello.cpp -o Hello
	./Hello

bounce: clean
	g++ -lcurses bounce.cpp -o  Bounce
	./Bounce

bounce2: clean
	g++ -lcurses bounce2.cpp -o  Bounce2
	./Bounce2

snake: clean
	g++ -std=c++11 -lcurses snake.cpp -o  Snake
	./Snake

life: clean
	g++ -lcurses life.cpp -o Life
	./Life

clean:
	rm -f ./Hello ./Bounce ./Bounce2 ./Snake