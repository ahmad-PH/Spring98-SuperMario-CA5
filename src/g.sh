g++ *.cpp -std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf -g
if [ $? == 0 ]
then
	./a.out
fi