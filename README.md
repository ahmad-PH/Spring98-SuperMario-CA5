# SuperMario - UTAP Spring98

This is a minimal, c++ implementation of the famous and nostalgic game [SuperMario](https://supermariobros.io/), which was chosen as a course project for the Advanced Programming course of University of Tehran, on the Spring 2019 semester. 
As a teaching assistant for this course who was in charge of designing this assignment, I felt compelled to write the code that was expected of the students, in order to make sure that the project was neither too big, nor too small. Also it would help bring out all those small ambiguities earlier, that would otherwise be discovered only after the students started working on the project, and thus help save both the TAs and students significant amounts of time.

This project is built using the [RSDL](https://github.com/UTAP/RSDL) (Ramtin's Simple DirectMedia Layer) library, which is a library developed to help students use the SDL library through a simpler and more object-oriented interface. 

## Getting Started

To play this game, you need to do the typical steps for running any c-based project.
First, clone the repository into a directory which we will call ‍‍‍`<mario-dir>` from now on. Then, change directory to `<mario-dir>/src`.
Then run 
```
make
```
to create the executable. Then run
```
./mario.out <level-file-address>
```
to play the game. The game currently has only one levels, and it will default to that one level if the executable is called without any arguments.

## Authors

* **Ahmad Pourihosseini** - [ahmad-PH](https://github.com/ahmad-PH)

## Acknowledgments

* all the assets in this project were picked from the two websites: [mariouniverse](http://www.mariouniverse.com/) and [themushroomkingdom](https://themushroomkingdom.net/wav.shtml).
