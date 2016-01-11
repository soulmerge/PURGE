#include "OsgWindow.h"

#include "classes.h"
#include <iostream>

namespace PURGEBridge
{

	int
	OsgWindow::systemIndex = 0;

	OsgWindow::OsgWindow(OsgGraphics* bridge, PURGE::Window* window)
	         : PURGE::WindowTranscript(window)
	         , lastX(-1)
	         , lastY(-1)
	         , bridge(bridge)
	         , view(NULL)
	{
		//std::cout << "Creating window (" << topleftX << ", " << topleftY << ", " << width << ", " << height << ")" << std::endl;
		traits = new osg::GraphicsContext::Traits;
		traits->x = window->getLeft();
		traits->y = window->getTop();
		traits->width = window->getWidth();
		traits->height = window->getHeight();
		traits->windowDecoration = true;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;
		graphicsContext = static_cast<osgViewer::GraphicsWindow*>(osg::GraphicsContext::createGraphicsContext(traits.get()));
		for (unsigned int i = 0; i < 256; i++)
		{
			pressedKeys[i] = false;
		}
	}

	bool
	OsgWindow::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		switch (ea.getEventType())
		{
			case (osgGA::GUIEventAdapter::KEYDOWN):
				{
					PURGE::Key key(oisToPurge(ea));
					if (!pressedKeys[key])
					{
						pressedKeys[key] = true;
						keyPressed(key);
					}
				}
				break;
			case (osgGA::GUIEventAdapter::KEYUP):
				{
					PURGE::Key key(oisToPurge(ea));
					keyReleased(key);
					pressedKeys[key] = false;
				}
				break;
			case (osgGA::GUIEventAdapter::MOVE):
				{
					if (lastX != -1)
					{
						mouseMoved(PURGE::Point2(ea.getX(), ea.getY()), PURGE::Vector2((int) ea.getX() - lastX, (int) ea.getY() - lastY));
					}
					lastX = (int) ea.getX();
					lastY = (int) ea.getY();
					/*
					if (captureMouse)
					{
						int x, y, width, height;
						graphicsContext->getWindowRectangle(x, y, width, height);
						if (lastX < width * 0.25 || lastX > width * 0.75 || lastY < height * 0.25 || lastY > height * 0.75)
						{
							aa.requestWarpPointer(width * 0.5, height * 0.5);
							lastX = (int) (width * 0.5);
							lastY = (int) (height * 0.5);
						}
					}
					*/
				}
				break;
			default:
				break;
		}
		return true;
	}

	OsgWindow*
	OsgWindow::addEventHandler(osg::ref_ptr<osgViewer::View> view)
	{
		if (this->view == NULL)
		{
			this->view = view;
		}
		/*
		if (captureMouse)
		{
			int x, y, width, height;
			graphicsContext->getWindowRectangle(x, y, width, height);
			view->requestWarpPointer(width * 0.5, height * 0.5);
		}
		*/
		view->addEventHandler(this); 
		return this;
	}

	PURGE::Key
	OsgWindow::oisToPurge(const osgGA::GUIEventAdapter& ea) const
	{
		// TODO: Can't we really capture modifier keys?
		if (ea.getKey() > 0)
		{
			return PURGE::Key(charToKey(ea.getKey()));
		}
		else
		{
			switch(ea.getKey())
			{
				case osgGA::GUIEventAdapter::KEY_Space:
					return PURGE::KC_SPACE;
				case osgGA::GUIEventAdapter::KEY_BackSpace:
					return PURGE::KC_BACKSPACE;
				case osgGA::GUIEventAdapter::KEY_Tab:
					return PURGE::KC_TAB;
				case osgGA::GUIEventAdapter::KEY_Linefeed:
					return PURGE::KC_RETURN;
				case osgGA::GUIEventAdapter::KEY_Clear:
					return PURGE::KC_DELETE;
				case osgGA::GUIEventAdapter::KEY_Return:
					return PURGE::KC_RETURN;
				case osgGA::GUIEventAdapter::KEY_Pause:
					return PURGE::KC_PAUSE;
				case osgGA::GUIEventAdapter::KEY_Scroll_Lock:
					return PURGE::KC_SCROLL;
				case osgGA::GUIEventAdapter::KEY_Sys_Req:
					return PURGE::KC_SYSRQ;
				case osgGA::GUIEventAdapter::KEY_Escape:
					return PURGE::KC_ESCAPE;
				case osgGA::GUIEventAdapter::KEY_Delete:
					return PURGE::KC_DELETE;
				case osgGA::GUIEventAdapter::KEY_Home:
					return PURGE::KC_HOME;
				case osgGA::GUIEventAdapter::KEY_Left:
					return PURGE::KC_LEFT;
				case osgGA::GUIEventAdapter::KEY_Up:
					return PURGE::KC_UP;
				case osgGA::GUIEventAdapter::KEY_Right:
					return PURGE::KC_RIGHT;
				case osgGA::GUIEventAdapter::KEY_Down:
					return PURGE::KC_DOWN;
				case osgGA::GUIEventAdapter::KEY_Page_Up:
					return PURGE::KC_PGUP;
				case osgGA::GUIEventAdapter::KEY_Page_Down:
					return PURGE::KC_PGDOWN;
				case osgGA::GUIEventAdapter::KEY_End:
					return PURGE::KC_END;
				case osgGA::GUIEventAdapter::KEY_Begin:
					return PURGE::KC_HOME;
				case osgGA::GUIEventAdapter::KEY_Select:
					return PURGE::KC_MEDIASELECT;
				case osgGA::GUIEventAdapter::KEY_Print:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Execute:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Insert:
					return PURGE::KC_INSERT;
				case osgGA::GUIEventAdapter::KEY_Undo:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Redo:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Menu:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Find:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Cancel:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Help:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Break:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Script_switch:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Num_Lock:
					return PURGE::KC_NUMLOCK;
				case osgGA::GUIEventAdapter::KEY_KP_Space:
					return PURGE::KC_SPACE;
				case osgGA::GUIEventAdapter::KEY_KP_Tab:
					return PURGE::KC_TAB;
				case osgGA::GUIEventAdapter::KEY_KP_Enter:
					return PURGE::KC_NUMPADENTER;
				case osgGA::GUIEventAdapter::KEY_KP_F1:
					return PURGE::KC_F1;
				case osgGA::GUIEventAdapter::KEY_KP_F2:
					return PURGE::KC_F2;
				case osgGA::GUIEventAdapter::KEY_KP_F3:
					return PURGE::KC_F3;
				case osgGA::GUIEventAdapter::KEY_KP_F4:
					return PURGE::KC_F4;
				case osgGA::GUIEventAdapter::KEY_KP_Home:
					return PURGE::KC_HOME;
				case osgGA::GUIEventAdapter::KEY_KP_Left:
					return PURGE::KC_NUMPAD4;
				case osgGA::GUIEventAdapter::KEY_KP_Up:
					return PURGE::KC_NUMPAD8;
				case osgGA::GUIEventAdapter::KEY_KP_Right:
					return PURGE::KC_NUMPAD6;
				case osgGA::GUIEventAdapter::KEY_KP_Down:
					return PURGE::KC_NUMPAD2;
				case osgGA::GUIEventAdapter::KEY_KP_Page_Up:
					return PURGE::KC_NUMPAD9;
				case osgGA::GUIEventAdapter::KEY_KP_Page_Down:
					return PURGE::KC_NUMPAD3;
				case osgGA::GUIEventAdapter::KEY_KP_End:
					return PURGE::KC_NUMPAD1;
				case osgGA::GUIEventAdapter::KEY_KP_Begin:
					return PURGE::KC_NUMPAD7;
				case osgGA::GUIEventAdapter::KEY_KP_Insert:
					return PURGE::KC_NUMPAD0;
				case osgGA::GUIEventAdapter::KEY_KP_Delete:
					return PURGE::KC_NUMPADCOMMA;
				case osgGA::GUIEventAdapter::KEY_KP_Equal:
					return PURGE::KC_NUMPADEQUALS;
				case osgGA::GUIEventAdapter::KEY_KP_Multiply:
					return PURGE::KC_MULTIPLY;
				case osgGA::GUIEventAdapter::KEY_KP_Add:
					return PURGE::KC_ADD;
				case osgGA::GUIEventAdapter::KEY_KP_Separator:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_KP_Subtract:
					return PURGE::KC_SUBTRACT;
				case osgGA::GUIEventAdapter::KEY_KP_Decimal:
					return PURGE::KC_DECIMAL;
				case osgGA::GUIEventAdapter::KEY_KP_Divide:
					return PURGE::KC_DIVIDE;
				case osgGA::GUIEventAdapter::KEY_KP_0:
					return PURGE::KC_NUMPAD0;
				case osgGA::GUIEventAdapter::KEY_KP_1:
					return PURGE::KC_NUMPAD1;
				case osgGA::GUIEventAdapter::KEY_KP_2:
					return PURGE::KC_NUMPAD2;
				case osgGA::GUIEventAdapter::KEY_KP_3:
					return PURGE::KC_NUMPAD3;
				case osgGA::GUIEventAdapter::KEY_KP_4:
					return PURGE::KC_NUMPAD4;
				case osgGA::GUIEventAdapter::KEY_KP_5:
					return PURGE::KC_NUMPAD5;
				case osgGA::GUIEventAdapter::KEY_KP_6:
					return PURGE::KC_NUMPAD6;
				case osgGA::GUIEventAdapter::KEY_KP_7:
					return PURGE::KC_NUMPAD7;
				case osgGA::GUIEventAdapter::KEY_KP_8:
					return PURGE::KC_NUMPAD8;
				case osgGA::GUIEventAdapter::KEY_KP_9:
					return PURGE::KC_NUMPAD9;
				case osgGA::GUIEventAdapter::KEY_F1:
					return PURGE::KC_F1;
				case osgGA::GUIEventAdapter::KEY_F2:
					return PURGE::KC_F2;
				case osgGA::GUIEventAdapter::KEY_F3:
					return PURGE::KC_F3;
				case osgGA::GUIEventAdapter::KEY_F4:
					return PURGE::KC_F4;
				case osgGA::GUIEventAdapter::KEY_F5:
					return PURGE::KC_F5;
				case osgGA::GUIEventAdapter::KEY_F6:
					return PURGE::KC_F6;
				case osgGA::GUIEventAdapter::KEY_F7:
					return PURGE::KC_F7;
				case osgGA::GUIEventAdapter::KEY_F8:
					return PURGE::KC_F8;
				case osgGA::GUIEventAdapter::KEY_F9:
					return PURGE::KC_F9;
				case osgGA::GUIEventAdapter::KEY_F10:
					return PURGE::KC_F10;
				case osgGA::GUIEventAdapter::KEY_F11:
					return PURGE::KC_F11;
				case osgGA::GUIEventAdapter::KEY_F12:
					return PURGE::KC_F12;
				case osgGA::GUIEventAdapter::KEY_F13:
					return PURGE::KC_F13;
				case osgGA::GUIEventAdapter::KEY_F14:
					return PURGE::KC_F14;
				case osgGA::GUIEventAdapter::KEY_F15:
					return PURGE::KC_F15;
				case osgGA::GUIEventAdapter::KEY_F16:
				case osgGA::GUIEventAdapter::KEY_F17:
				case osgGA::GUIEventAdapter::KEY_F18:
				case osgGA::GUIEventAdapter::KEY_F19:
				case osgGA::GUIEventAdapter::KEY_F20:
				case osgGA::GUIEventAdapter::KEY_F21:
				case osgGA::GUIEventAdapter::KEY_F22:
				case osgGA::GUIEventAdapter::KEY_F23:
				case osgGA::GUIEventAdapter::KEY_F24:
				case osgGA::GUIEventAdapter::KEY_F25:
				case osgGA::GUIEventAdapter::KEY_F26:
				case osgGA::GUIEventAdapter::KEY_F27:
				case osgGA::GUIEventAdapter::KEY_F28:
				case osgGA::GUIEventAdapter::KEY_F29:
				case osgGA::GUIEventAdapter::KEY_F30:
				case osgGA::GUIEventAdapter::KEY_F31:
				case osgGA::GUIEventAdapter::KEY_F32:
				case osgGA::GUIEventAdapter::KEY_F33:
				case osgGA::GUIEventAdapter::KEY_F34:
				case osgGA::GUIEventAdapter::KEY_F35:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Shift_L:
					return PURGE::KC_LSHIFT;
				case osgGA::GUIEventAdapter::KEY_Shift_R:
					return PURGE::KC_RSHIFT;
				case osgGA::GUIEventAdapter::KEY_Control_L:
					return PURGE::KC_LCONTROL;
				case osgGA::GUIEventAdapter::KEY_Control_R:
					return PURGE::KC_RCONTROL;
				case osgGA::GUIEventAdapter::KEY_Caps_Lock:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Shift_Lock:
					return PURGE::KC_UNKNOWN;
				case osgGA::GUIEventAdapter::KEY_Meta_L:
				case osgGA::GUIEventAdapter::KEY_Alt_L:
					return PURGE::KC_LMENU;
				case osgGA::GUIEventAdapter::KEY_Meta_R:
				case osgGA::GUIEventAdapter::KEY_Alt_R:
					return PURGE::KC_RMENU;
				case osgGA::GUIEventAdapter::KEY_Super_L:
				case osgGA::GUIEventAdapter::KEY_Super_R:
				case osgGA::GUIEventAdapter::KEY_Hyper_L:
				case osgGA::GUIEventAdapter::KEY_Hyper_R:
				default:
					return PURGE::KC_UNKNOWN;
					break;
			}
		}
	}

}

