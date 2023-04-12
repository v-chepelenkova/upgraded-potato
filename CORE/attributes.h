#pragma once

#include <string>
#include <variant>
#include <vector>

using AttributeVariant = std::variant<int,
                                      float,
                                      bool,
                                      std::string,
                                      std::vector<float>>;