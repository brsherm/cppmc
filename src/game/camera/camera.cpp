#include "camera.h"
#define π 3.14159265f

Camera::Camera(const int width, const int height)
{
  position.x = 0;
  position.y = 0;
  position.z = 1;
  θ = π / 2.;
  φ = π / 2.;
  up.x = 0;
  up.y = 0;
  up.z = 1;
  zn = 1.f / 16.f;
  zf = 256.f;
  f = 2.5f;
  hot = false;

  for (int i = 0; i < 16; i++) {
    p[i] = 0.f;
    v[i] = 0.f;
  }
  v[15] = 1.f;

  update_look_vector();
  update_aspect_ratio(width, height);
}

void Camera::move(const float Δx, const float Δy, const float Δz)
{
  position.x += Δx;
  position.y += Δy;
  position.z += Δz;
  update_view_matrix();
}

void Camera::move_forward(const float Δ)
{
  position.x += look.x * Δ;
  position.y += look.y * Δ;
  position.z += look.z * Δ;
  update_view_matrix();
}

void Camera::update_look_vector()
{
  look.x = cos(φ) * sin(θ);
  look.y = sin(φ) * sin(θ);
  look.z = cos(θ);
  update_strafe_vector();
  update_view_matrix();
}

void Camera::update_strafe_vector()
{
  vec3::cross(look, up, st);
  vec3::normalize(st);
}

void Camera::strafe(const float Δ)
{
  position.x += st.x * Δ;
  position.y += st.y * Δ;
  position.z += st.z * Δ;
  update_view_matrix();
}

void Camera::pan(const float Δφ)
{
  if (φ + Δφ >= 2 * π) φ += Δφ - 2 * π;
  else if (φ + Δφ < 0) φ += Δφ + 2 * π;
  else φ += Δφ;

  if (θ == 0) {
    up.x = cosf(φ + π) * sinf(π/2);
    up.y = sinf(φ + π) * sinf(π/2);
    up.z = cosf(π/2);
  } else if (θ == π) {
    up.x = cosf(φ) * sinf(π/2);
    up.y = sinf(φ) * sinf(π/2);
    up.z = cosf(π/2);
  }

  update_look_vector();
}

void Camera::tilt(const float Δθ)
{
  if (θ + Δθ >= π) {
    θ = π;
    up.x = cosf(φ) * sinf(π/2);
    up.y = sinf(φ) * sinf(π/2);
    up.z = cosf(π/2);
  } else if (θ + Δθ <= 0) {
    θ = 0;
    up.x = cosf(φ + π) * sinf(π/2);
    up.y = sinf(φ + π) * sinf(π/2);
    up.z = cosf(π/2);
  } else {
    θ = θ + Δθ;
    up.x = 0.f;
    up.y = 0.f;
    up.z = 1.f;
  }
  update_look_vector();
}

void Camera::raise(const float Δz)
{
  position.z += Δz;
  update_view_matrix();
}

void Camera::update_aspect_ratio(const int width, const int height)
{
  a = static_cast<float>(width) / static_cast<float>(height);
  θh = 2 * atan(1.f / f);
  θw = 2 * atan(a / f);
  update_perspective_matrix();
}

void Camera::update_view_matrix()
{
  vec3::vec3 u;
  vec3::cross(st, look, u);
  v[0] = st.x;
  v[1] = u.x;
  v[2] = -look.x;
  v[4] = st.y;
  v[5] = u.y;
  v[6] = -look.y;
  v[8] = st.z;
  v[9] = u.z;
  v[10] = -look.z;
  v[12] = -vec3::dot(st, position);
  v[13] = -vec3::dot(u, position);
  v[14] = vec3::dot(look, position);
  update_final_matrix();
}

void Camera::update_perspective_matrix()
{
  float t = tanf(θw / 2.f);
  p[0] = 1.f / (a * t);
  p[5] = 1.f / t;
  p[10] = (zn + zf) / (zn - zf);
  p[11] = -1.f;
  p[14] = (2.f * zn * zf) / (zn - zf);
  update_final_matrix();
}

void Camera::update_final_matrix()
{
  m[0] = v[0] * p[0];
  m[1] = v[1] * p[5];
  m[2] = v[2] * p[10];
  m[3] = v[2] * p[11];
  m[4] = v[4] * p[0];
  m[5] = v[5] * p[5];
  m[6] = v[6] * p[10];
  m[7] = v[6] * p[11];
  m[8] = v[8] * p[0];
  m[9] = v[9] * p[5];
  m[10] = v[10] * p[10];
  m[11] = v[10] * p[11];
  m[12] = v[12] * p[0];
  m[13] = v[13] * p[5];
  m[14] = v[14] * p[10] + p[14];
  m[15] = v[14] * p[11];
  hot = true;
}

bool Camera::is_hot() const
{
  return hot;
}

void Camera::cool()
{
  hot = false;
}

#undef PI