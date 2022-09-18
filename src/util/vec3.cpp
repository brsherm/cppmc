#include "vec3.h"
#include "math.h"

namespace vec3
{

  float dot(const vec3& a, const vec3& b)
  {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  void cross(const vec3& a, const vec3& b, vec3& c)
  {
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
  }

  void normalize(vec3& v)
  {
    float mag = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (mag == 0) return;
    v.x /= mag;
    v.y /= mag;
    v.z /= mag;
  }

  std::string to_string(vec3& v)
  {
    return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")";
  }
}