#ifndef PURGEBRIDGE_OGRE_1_7_OGRERENDERER_H
#define PURGEBRIDGE_OGRE_1_7_OGRERENDERER_H 1

#include <map>
#include <string>
#include <OGRE/Ogre.h>
#include <PURGE/include.h>
#include <boost/lexical_cast.hpp>
#include "classes.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		class OgreRenderer : public virtual PURGE::Renderer
		{

			public:
				static OgreRenderer* createInstance(const std::string& resourceFolder);
				static OgreRenderer* getInstance();
				static void destroy();

				static Ogre::Vector3 convert(const PURGE::Vector3& v);
				static Ogre::Quaternion convert(const PURGE::Quaternion& q);
				static Ogre::ColourValue convert(const PURGE::Color& c);
				static Ogre::Radian convert(const PURGE::Angle& a);

				std::string createUniqueString(std::string prefix);

				Ogre::Root* getOgreRoot() const;
				Ogre::SceneManager* getOgreSceneManager() const;

				bool windowIsClosed(const PURGE::Window* window, bool currentStatus) const;
				void startRendering();
				void finishRendering();
				void _activate();
				void _deactivate();

				void printSceneGraph() const;

			private:
				static OgreRenderer* instance;
				std::map<std::string, int> lastStrings;
				Ogre::Root* ogreRoot;
				Ogre::SceneManager* ogreSceneManager;
				bool fullyInitialized;
				std::list<std::string> resourceLocations;

				OgreRenderer();

				void printHelper(Ogre::SceneNode* node, int indent) const;
				void _activateInstances();

		};

		inline OgreRenderer*
		OgreRenderer::createInstance(const std::string& resourceFolder)
		{
			assert(!instance);
			instance = new OgreRenderer();
			instance->resourceLocations.push_back(resourceFolder);
			return instance;
		}

		inline OgreRenderer*
		OgreRenderer::getInstance()
		{
			assert(instance);
			return instance;
		}

		inline Ogre::Vector3
		OgreRenderer::convert(const PURGE::Vector3& v)
		{
			return Ogre::Vector3(v.x(), v.y(), PURGE::CoordinateSystem::get().isLeftHanded() ? -v.z() : v.z());
		}

		inline Ogre::Quaternion
		OgreRenderer::convert(const PURGE::Quaternion& q)
		{
			if (!PURGE::CoordinateSystem::get().isLeftHanded())
			{
				return Ogre::Quaternion(q.w(), q.x(), q.y(), q.z());
			}
			PURGE::Angle angle;
			PURGE::Vector3 axis;
			q.getAngleAxis(angle, axis);
			Ogre::Quaternion result;
			result.FromAngleAxis(Ogre::Radian(-angle.radians()), Ogre::Vector3(axis.x(), axis.y(), axis.z()));
			return result;
		}

		inline Ogre::ColourValue
		OgreRenderer::convert(const PURGE::Color& c)
		{
			return Ogre::ColourValue(c.getRed(), c.getGreen(), c.getBlue());
		}

		inline Ogre::Radian
		OgreRenderer::convert(const PURGE::Angle& a)
		{
			return Ogre::Radian(a.radians());
		}

		inline
		OgreRenderer::OgreRenderer()
		{
			// Strange: rendering does not work if logging is disabled
			/*
			Ogre::LogManager * lm = new Ogre::LogManager();
			lm->createLog("", true, false, false);
			*/
		}

		inline std::string
		OgreRenderer::createUniqueString(std::string prefix)
		{
			return prefix + "-" + boost::lexical_cast<std::string>(++lastStrings[prefix]);
		}

		inline Ogre::Root*
		OgreRenderer::getOgreRoot() const
		{
			return ogreRoot;
		}

		inline Ogre::SceneManager*
		OgreRenderer::getOgreSceneManager() const
		{
			return ogreSceneManager;
		}

		inline void
		OgreRenderer::_activate()
		{
			fullyInitialized = false;
			ogreRoot = new Ogre::Root();
			// TODO: dummy resource location
			if (!ogreRoot->restoreConfig() && !ogreRoot->showConfigDialog())
			{
				throw "Could not load config";
			}
			ogreRoot->initialise(false);
			ogreSceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
			_activateInstances();
		}

		inline void
		OgreRenderer::_deactivate()
		{
			// TODO: implement
		}

	}

}

#endif /* PURGEBRIDGE_OGRE_1_7_OGRERENDERER_H */

