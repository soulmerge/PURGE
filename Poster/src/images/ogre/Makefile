all: runner

runner: TutorialApplication.o BaseApplication.o
	g++ -o runner TutorialApplication.o BaseApplication.o -lOgreMain -lOIS

TutorialApplication.o: TutorialApplication.cpp TutorialApplication.h
	g++ -c -I /usr/include/OIS/ -I /usr/include/OGRE/ TutorialApplication.cpp

BaseApplication.o: BaseApplication.cpp BaseApplication.h
	g++ -c -I /usr/include/OIS/ -I /usr/include/OGRE/ BaseApplication.cpp

