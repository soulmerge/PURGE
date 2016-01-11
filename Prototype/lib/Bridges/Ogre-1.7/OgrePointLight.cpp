#include "OgrePointLight.h"

#include "OgreRenderer.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		OgrePointLight::OgrePointLight(PURGE::PointLightDefinition* original)
		             : Transcription<PURGE::PointLightDefinition, OgrePointLight>(original)
		{
			ogreLight = OgreRenderer::getInstance()->getOgreSceneManager()->createLight();
			ogreLight->setType(Ogre::Light::LT_POINT);
			ogreLight->setDirection(OgreRenderer::convert(PURGE::CoordinateSystem::get().getForwardVector()));
			update(PURGE::Light::CHANGE_ENABLED);
			update(PURGE::Light::CHANGE_COLOR);
			update(PURGE::PointLight::CHANGE_RANGE);
		}

		void
		OgrePointLight::update(int change)
		{
			if (change == PURGE::Light::CHANGE_ENABLED)
			{
				ogreLight->setVisible(original->isEnabled());
			}
			else if (change == PURGE::Light::CHANGE_COLOR)
			{
				auto color(OgreRenderer::convert(original->getColor()));
				ogreLight->setDiffuseColour(color);
				ogreLight->setSpecularColour(color);
			}
			else if (change == PURGE::PointLight::CHANGE_RANGE)
			{
				ogreLight->setAttenuation(original->getRange(), 1, 0, 0);
			}
			else
			{
				throw std::string("OgrePointLight: unidentified change #") + boost::lexical_cast<std::string>(change);
			}
		}

		void
		OgrePointLight::destroy()
		{
			// TODO: implement
		}

	}

}

