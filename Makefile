build: walsh.cpp statistics.cpp prinel.cpp crypto.cpp
	g++ walsh.cpp -Werror -Wall -Wextra -o walsh
	g++ statistics.cpp -Werror -Wall -Wextra -o statistics
	g++ prinel.cpp -Werror -Wall -Wextra -o prinel
	g++ crypto.cpp -Werror -Wall -Wextra -o crypto
	g++ regele.cpp -Werror -Wall -Wextra -o regele

run-p1: walsh
	./walsh

run-p2: statistics 
	./statistics

run-p3: prinel 
	./prinel

run-p4: crypto
	./crypto

run-p5: regele
	./regele

clean:
	rm walsh statistics prinel crypto regele
