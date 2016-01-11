#include <PURGE/include.h>
#include <Bridges/Ogre-1.7/OgreRenderer.h>
#include "test/TestScene1.h"
#include "test/TestScene2.h"
#include "test/TestScene3.h"
#include "test/TestScene4.h"
#include "test/TestScene5.h"
#include "test/TestScene6.h"
#include "test/TestScene7.h"
#include "test/TestScene8.h"
#include "test/TestScene81.h"
#include "test/TestScene82.h"
#include "test/TestScene9.h"
#include "test/TestScene10.h"
#include "test/TestScene11.h"
#include "test/TestScene12.h"
#include <iostream>

#include <ctype.h>
#include <algorithm>
#include <string>

int
main (int argc, char* argv[])
{
	try
	{
		TestScene* scene = NULL;
		int runner = 0;
		for (int i = 1; i < argc; i++)
		{
			std::string arg(argv[i]);
			std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
			if (0 == arg.compare("ogre") || 0 == arg.compare("ogre3d"))
			{
				runner = 1;
			}
			else if (0 == arg.compare("osg"))
			{
				runner = 2;
			}
			else if (0 == arg.compare("panda") || 0 == arg.compare("panda3d"))
			{
				runner = 3;
			}
			else if (0 == arg.compare("1"))
			{
				scene = new TestScene1();
			}
			else if (0 == arg.compare("2"))
			{
				scene = new TestScene2();
			}
			else if (0 == arg.compare("3"))
			{
				scene = new TestScene3();
			}
			else if (0 == arg.compare("4"))
			{
				scene = new TestScene4();
			}
			else if (0 == arg.compare("5"))
			{
				scene = new TestScene5();
			}
			else if (0 == arg.compare("6"))
			{
				scene = new TestScene6();
			}
			else if (0 == arg.compare("7"))
			{
				scene = new TestScene7();
			}
			else if (0 == arg.compare("8"))
			{
				scene = new TestScene8();
			}
			else if (0 == arg.compare("8.1"))
			{
				scene = new TestScene81();
			}
			else if (0 == arg.compare("8.2"))
			{
				scene = new TestScene82();
			}
			else if (0 == arg.compare("9"))
			{
				scene = new TestScene9();
			}
			else if (0 == arg.compare("10"))
			{
				scene = new TestScene10();
			}
			else if (0 == arg.compare("11"))
			{
				scene = new TestScene11();
			}
			else if (0 == arg.compare("12"))
			{
				scene = new TestScene12();
			}
			else if (0 != arg.compare("purge"))
			{
				throw std::string("Undefined runner: ") + arg;
			}
		}
		if (!scene)
		{
			throw "No scene was chosen";
		}
		// required for runPanda()
		argc = 1;
		switch (runner)
		{
			case 0:
				scene->runPURGE();
				break;
			case 1:
				scene->runOgre();
				break;
			case 2:
				scene->runOsg();
				break;
			case 3:
				scene->runPanda(argc, argv);
				break;
		}
		return EXIT_SUCCESS;
	}
	catch (std::string s)
	{
		std::cerr << "Exception: " << s << std::endl;
		return EXIT_FAILURE;
	}
	catch (char const* c)
	{
		std::cerr << "Exception: " << c << std::endl;
		return EXIT_FAILURE;
	}
}

