#include "XmlHelper.hpp"

#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <vector>

#include <engine/core/math/Math.hpp>
#include <engine/Entity.hpp>

using namespace std;

namespace glPortal {

std::string XmlHelper::mandatoryAttributeMessage("Mandatory attribute has not been defined.");
std::string XmlHelper::invalidElementMessage("pushAttributeToVector received an invalid XML-Element.");
/**
  * Pushes vector coordinates from an XML-element to a Vector3f.
  * Trying to pull attributes from a non-existing element is considered an exception.
  */
void XmlHelper::pushAttributeVertexToVector(XMLElement *xmlElement, Vector3f &targetVector) {
  if(xmlElement) {
    int xQueryResult = xmlElement->QueryFloatAttribute("x", &targetVector.x);
    int yQueryResult = xmlElement->QueryFloatAttribute("y", &targetVector.y);
    int zQueryResult = xmlElement->QueryFloatAttribute("z", &targetVector.z);
    if(xQueryResult == XML_NO_ATTRIBUTE){
      throwMandatoryAttributeException("<x>");
    }
    if(yQueryResult == XML_NO_ATTRIBUTE){
      throwMandatoryAttributeException("<y>");
    }
    if(zQueryResult == XML_NO_ATTRIBUTE){
      throwMandatoryAttributeException("<z>");
    }
  } else {
    throw runtime_error(invalidElementMessage);
  }
}

void XmlHelper::throwMandatoryAttributeException(const std::string &message){
  throw runtime_error(mandatoryAttributeMessage + message);
}

void XmlHelper::extractPosition(XMLElement *xmlElement, Vector3f &position) {
  pushAttributeVertexToVector(xmlElement->FirstChildElement("position"), position);
}

void XmlHelper::extractRotation(XMLElement *xmlElement, Vector3f &rotation) {
  XMLElement *elm = xmlElement->FirstChildElement("rotation");
  if (elm) {
    pushAttributeVertexToVector(elm, rotation);
    rotation.x = rad(rotation.x);
    rotation.y = rad(rotation.y);
    rotation.z = rad(rotation.z);
  } else {
    rotation.x = rotation.y = rotation.z = 0;
  }
}

void XmlHelper::extractScale(XMLElement *xmlElement, Vector3f &scale) {
  pushAttributeVertexToVector(xmlElement->FirstChildElement("scale"), scale);
}

} /* namespace glPortal */
