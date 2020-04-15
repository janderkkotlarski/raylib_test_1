#ifndef VEC_3_INT_H
#define VEC_3_INT_H

#include <raylib.h>

class vec_3_int
{
public:
  int m_x;
  int m_y;
  int m_z;

  vec_3_int(const int x,
            const int y,
            const int z)
  noexcept;

  vec_3_int(const float x,
            const float y,
            const float z)
  noexcept;

  vec_3_int(const Vector3 &vec)
  noexcept;

  Vector3 get_Vector3()
  const noexcept
  {
    return Vector3 { static_cast<float>(m_x),
                     static_cast<float>(m_y),
                     static_cast<float>(m_z) };
};

};



#endif // VEC_3_INT_H
