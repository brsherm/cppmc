#if !defined(CAMERA_H)
#define CAMERA_H

#include <math.h>
#include "src/util/vec3.h"

class Camera
{
  public:
    Camera(const int width, const int height);
    ~Camera();
    void move(const float Δx, const float Δy, const float Δz);
    void move_forward(const float Δ);
    void strafe(const float Δ);
    void pan(const float Δφ);
    void tilt(const float Δθ);
    void raise(const float Δz);
    void update_aspect_ratio(const int width, const int height);
    bool is_hot() const;
    void cool();
  private:
    vec3::vec3 position;  // eye vector
    vec3::vec3 look;      // look vector
    vec3::vec3 st;        // strafe vector — points to your right
    vec3::vec3 up;        // usually (0, 0, 1)
    float φ;              // azimuthal angle
    float θ;              // angle of inclination
    float θw;             // field of view (X)
    float θh;             // field of view (Y)
    float zn;             // distance of near plane
    float zf;             // distance of far plane
    float a;              // aspect ratio
    float f;              // focal length
    float v[16];          // view matrix
    float p[16];          // perspective matrix
    float m[16];          // final matrix
    bool hot;
    void update_look_vector();
    void update_strafe_vector();
    void update_view_matrix();
    void update_perspective_matrix();
    void update_final_matrix();
};


#endif // CAMERA_H