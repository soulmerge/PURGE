#include "OgreSpotLight.h"

#include "OgreRenderer.h"

namespace PURGEBridge
{

	namespace Ogre_1_7
	{

		OgreSpotLight::OgreSpotLight(PURGE::SpotLightDefinition* original)
		             : Transcription<PURGE::SpotLightDefinition, OgreSpotLight>(original)
		{
			ogreLight = OgreRenderer::getInstance()->getOgreSceneManager()->createLight();
			ogreLight->setType(Ogre::Light::LT_SPOTLIGHT);
			ogreLight->setDirection(OgreRenderer::convert(PURGE::CoordinateSystem::get().getForwardVector()));
			update(PURGE::Light::CHANGE_ENABLED);
			update(PURGE::Light::CHANGE_COLOR);
			update(PURGE::SpotLight::CHANGE_ANGLE);
			update(PURGE::SpotLight::CHANGE_RANGE);
		}

		void
		OgreSpotLight::update(int change)
		{
			if (change == PURGE::Light::CHANGE_ENABLED)
			{
				// std::cout << "visible: " << (original->isEnabled() ? "true" : "false") << std::endl;
				ogreLight->setVisible(original->isEnabled());
			}
			else if (change == PURGE::Light::CHANGE_COLOR)
			{
				auto color(OgreRenderer::convert(original->getColor()));
				// std::cout << "color: " << color << std::endl;
				ogreLight->setDiffuseColour(color);
				ogreLight->setSpecularColour(color);
			}
			else if (change == PURGE::SpotLight::CHANGE_ANGLE)
			{
				auto angle(OgreRenderer::convert(original->getHalfAngle()));
				// std::cout << "angle: " << angle << std::endl;
				ogreLight->setSpotlightInnerAngle(angle);
				ogreLight->setSpotlightOuterAngle(angle);
			}
			else if (change == PURGE::SpotLight::CHANGE_RANGE)
			{
				// std::cout << "range: " << original->getRange() << std::endl;
				ogreLight->setAttenuation(original->getRange(), 1, 0, 0);
			}
			else
			{
				throw std::string("OgreSpotLight: unidentified change #") + boost::lexical_cast<std::string>(change);
			}
		}

		void
		OgreSpotLight::destroy()
		{
			// TODO: implement
		}

	}

}

