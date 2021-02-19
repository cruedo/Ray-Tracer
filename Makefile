a.exe: main.cpp Image.cpp
	g++ -Wall -Wextra -std=c++20 main.cpp Image.cpp Vec3.cpp

clean: 
	rm *.exe *.bmp