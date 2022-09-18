#if !defined(VEC3_H)
#define VEC3_H

#include <string>

namespace vec3
{

  struct vec3
  {
    float x;
    float y;
    float z;
  };

  float dot(const vec3& a, const vec3& b);
  void cross(const vec3& a, const vec3& b, vec3& c);
  void normalize(vec3& v);
  std::string to_string(const vec3& v);

}

#endif // VEC3_H
