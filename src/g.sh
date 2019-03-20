g++ *.cpp -std=c++11 -lSDL2 -lSDL2_image -lSDL2_ttf
if [ $? == 0 ]
then
	./a.out
fi