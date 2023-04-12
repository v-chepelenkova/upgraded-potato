#pragma once

#include <map>
#include <string>
#include <variant>

#include "attributes.h"

class Object {
 public:
  Object(std::map<std::string,
         AttributeVariant> attributes) : attributes(std::move(attributes)) {}
  virtual ~Object() = default;

  virtual void SetAttribute(
      const std::pair<std::string, AttributeVariant> &newAttribute) {
    auto it = attributes.find(newAttribute.first);
    if(it != attributes.end()) {
      it->second = newAttribute.second;
    }
  }

  virtual AttributeVariant GetAttribute(const std::string &s) {
    // TODO: throw exception if there is no key like 's' in the map
    return attributes[s];
  }

 protected:
  std::map<std::string, AttributeVariant> attributes;
};
