#include <cxxtest/TestSuite.h>

#include "base/TinyMath.hpp"

class TinyMathTestSuite : public CxxTest::TestSuite {
 public:
  const float EPSILON = 0.001f;

  // --------------------- VECTOR 3D TESTS -----------------------------------

  void testVector3DElementAccess() {
    {
      Vector3D<int> v{};
      TS_ASSERT_EQUALS(v[0], 0.0);
      TS_ASSERT_EQUALS(v[1], 0.0);
      TS_ASSERT_EQUALS(v[2], 0.0);

      const Vector3D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0], 0.0);
      TS_ASSERT_EQUALS(cv[1], 0.0);
      TS_ASSERT_EQUALS(cv[2], 0.0);
    }
    {
      Vector3D<float> v{0.1, 0.2, 0.3};
      TS_ASSERT_DELTA(v[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.2, EPSILON);
      TS_ASSERT_DELTA(v[2], 0.3, EPSILON);

      const Vector3D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], 0.2, EPSILON);
      TS_ASSERT_DELTA(cv[2], 0.3, EPSILON);
    }
    {
      Vector3D<double> v{-0.1, -0.2, -0.3};
      TS_ASSERT_DELTA(v[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], -0.2, EPSILON);
      TS_ASSERT_DELTA(v[2], -0.3, EPSILON);

      const Vector3D<double>& cv = v;
      TS_ASSERT_DELTA(cv[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], -0.2, EPSILON);
      TS_ASSERT_DELTA(cv[2], -0.3, EPSILON);
    }
  }

  void testVector3DElementAssignment() {
    {
      Vector3D<int> v{};
      v[0] = 0;
      v[1] = 1;
      v[2] = 2;

      // Copy constructor
      Vector3D<float> u{v};
      TS_ASSERT_DELTA(u[0], 0.0, EPSILON);
      TS_ASSERT_DELTA(u[1], 1.0, EPSILON);
      TS_ASSERT_DELTA(u[2], 2.0, EPSILON);

      const Vector3D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0], 0);
      TS_ASSERT_EQUALS(cv[1], 1);
      TS_ASSERT_EQUALS(cv[2], 2);
    }
    {
      Vector3D<float> v{};
      v[0] = 0.1;
      v[1] = 0.2;
      v[2] = 0.3;

      Vector3D<double> u{};
      u = v;
      TS_ASSERT_DELTA(u[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(u[1], 0.2, EPSILON);
      TS_ASSERT_DELTA(u[2], 0.3, EPSILON);

      const Vector3D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], 0.2, EPSILON);
      TS_ASSERT_DELTA(cv[2], 0.3, EPSILON);
    }
    {
      Vector3D<float> v{};
      v[0] = -0.1;
      v[1] = -0.2;
      v[2] = -0.3;

      Vector3D<float> u = v;
      TS_ASSERT_DELTA(u[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(u[1], -0.2, EPSILON);
      TS_ASSERT_DELTA(u[2], -0.3, EPSILON);

      const Vector3D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], -0.2, EPSILON);
      TS_ASSERT_DELTA(cv[2], -0.3, EPSILON);
    }
  }

  void testVector3DElementMultiplication() {
    {
      Vector3D<int> v{1, 1, 1};

      v *= 5;
      TS_ASSERT_EQUALS(v[0], 5.0);
      TS_ASSERT_EQUALS(v[1], 5.0);
      TS_ASSERT_EQUALS(v[2], 5.0);

      const Vector3D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0], 5.0);
      TS_ASSERT_EQUALS(cv[1], 5.0);
      TS_ASSERT_EQUALS(cv[2], 5.0);
    }
    {
      Vector3D<float> v;
      v[0] = 0.1;
      v[1] = 0.2;
      v[2] = 0.3;

      v *= 2;
      TS_ASSERT_DELTA(v[0], 0.2, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.4, EPSILON);
      TS_ASSERT_DELTA(v[2], 0.6, EPSILON);

      const Vector3D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], 0.2, EPSILON);
      TS_ASSERT_DELTA(cv[1], 0.4, EPSILON);
      TS_ASSERT_DELTA(cv[2], 0.6, EPSILON);
    }
    {
      Vector3D<double> v;
      v[0] = -0.1;
      v[1] = -0.2;
      v[2] = -0.3;

      v *= 2;
      TS_ASSERT_DELTA(v[0], -0.2, EPSILON);
      TS_ASSERT_DELTA(v[1], -0.4, EPSILON);
      TS_ASSERT_DELTA(v[2], -0.6, EPSILON);

      const Vector3D<double>& cv = v;
      TS_ASSERT_DELTA(cv[0], -0.2, EPSILON);
      TS_ASSERT_DELTA(cv[1], -0.4, EPSILON);
      TS_ASSERT_DELTA(cv[2], -0.6, EPSILON);
    }
  }

  void testVector3DElementDivision() {
    {
      Vector3D<int> v{25, 25, 25};

      v /= 5;
      TS_ASSERT_EQUALS(v[0], 5);
      TS_ASSERT_EQUALS(v[1], 5);
      TS_ASSERT_EQUALS(v[2], 5);
    }
    {
      Vector3D<float> v{5.1, 5.2, 5.3};

      v /= 5;
      TS_ASSERT_DELTA(v[0], 1.02, EPSILON);
      TS_ASSERT_DELTA(v[1], 1.04, EPSILON);
      TS_ASSERT_DELTA(v[2], 1.06, EPSILON);
    }
    {
      Vector3D<double> v{-0.1, -0.2, -0.3};

      v /= -1;
      TS_ASSERT_DELTA(v[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.2, EPSILON);
      TS_ASSERT_DELTA(v[2], 0.3, EPSILON);
    }
  }

  void testVector3DElementVectorAddition() {
    {
      Vector3D<int> u{5, 5, 5};

      Vector3D<int> v{5, 5, 5};

      v += u;
      TS_ASSERT_EQUALS(v[0], 10);
      TS_ASSERT_EQUALS(v[1], 10);
      TS_ASSERT_EQUALS(v[2], 10);
    }
    {
      Vector3D<float> u{5.f, 5.f, 5.f};

      Vector3D<float> v{5.1f, 5.2f, 5.3f};

      v += u;
      TS_ASSERT_DELTA(v[0], 10.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 10.2, EPSILON);
      TS_ASSERT_DELTA(v[2], 10.3, EPSILON);
    }
    {
      Vector3D<double> u{5., 5., 5.};

      Vector3D<double> v{-.1, -.2, -.3};

      v += u;
      TS_ASSERT_DELTA(v[0], 4.9, EPSILON);
      TS_ASSERT_DELTA(v[1], 4.8, EPSILON);
      TS_ASSERT_DELTA(v[2], 4.7, EPSILON);
    }
  }

  void testVector3DElementVectorSubtraction() {
    {
      Vector3D<int> u{5, 5, 5};

      Vector3D<int> v{5, 5, 5};

      v -= u;
      TS_ASSERT_EQUALS(v[0], 0);
      TS_ASSERT_EQUALS(v[1], 0);
      TS_ASSERT_EQUALS(v[2], 0);
    }
    {
      Vector3D<float> u{5.f, 5.f, 5.f};

      Vector3D<float> v{5.1f, 5.2f, 5.3f};

      v -= u;
      TS_ASSERT_DELTA(v[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.2, EPSILON);
      TS_ASSERT_DELTA(v[2], 0.3, EPSILON);
    }
    {
      Vector3D<double> u{5., 5., 5.};

      Vector3D<double> v{-.1, -.2, -.3};

      v -= u;
      TS_ASSERT_DELTA(v[0], -5.1, EPSILON);
      TS_ASSERT_DELTA(v[1], -5.2, EPSILON);
      TS_ASSERT_DELTA(v[2], -5.3, EPSILON);
    }
  }

  void testVector3DDotProduct() {
    {
      Vector3D<int> u{5, 5, 5};

      Vector3D<int> v{5, 5, 5};

      float z = Dot(u, v);
      TS_ASSERT_EQUALS(z, 75);
    }
    {
      Vector3D<float> u{5.f, 5.f, 5.f};

      Vector3D<float> v{5.1f, 5.2f, 5.3f};

      float z = Dot(u, v);
      TS_ASSERT_DELTA(z, 78.0, EPSILON)
    }
    {
      Vector3D<double> u{5., 5., 5.};

      Vector3D<double> v{-.1, -.2, -.3};

      float z = Dot(u, v);
      TS_ASSERT_DELTA(z, -3.0, EPSILON);
    }
  }

  void testVector3DMagnitude() {
    {
      Vector3D<int> v{5, 5, 5};

      float z = Magnitude(v);
      TS_ASSERT_DELTA(z, 8.66, EPSILON);
    }
    {
      Vector3D<float> v{};
      v[0] = 5.1;
      v[1] = 5.2;
      v[2] = 5.3;

      float z = Magnitude(v);
      TS_ASSERT_DELTA(z, 9.0077, EPSILON);
    }
    {
      Vector3D<double> v{};
      v[0] = -0.1;
      v[1] = -0.2;
      v[2] = -0.3;

      float z = Magnitude(v);
      TS_ASSERT_DELTA(z, 0.3741, EPSILON);
    }
  }

  void testVector3DProject() {
    {
      Vector3D<float> u{};
      u[0] = 5.0;
      u[1] = 5.0;
      u[2] = 5.0;

      Vector3D<float> v{};
      v[0] = 5.0;
      v[1] = 5.0;
      v[2] = 5.0;

      Vector3D<float> z = Project(u, v);
      TS_ASSERT_DELTA(z[0], 5.0, EPSILON);
      TS_ASSERT_DELTA(z[1], 5.0, EPSILON);
      TS_ASSERT_DELTA(z[2], 5.0, EPSILON);
    }
    {
      Vector3D<float> u{};
      u[0] = 5.0;
      u[1] = 5.0;
      u[2] = 5.0;

      Vector3D<float> v{};
      v[0] = 5.1;
      v[1] = 5.2;
      v[2] = 5.3;

      Vector3D<float> z = Project(u, v);
      TS_ASSERT_DELTA(z[0], 4.9026, EPSILON);
      TS_ASSERT_DELTA(z[1], 4.9987, EPSILON);
      TS_ASSERT_DELTA(z[2], 5.0948, EPSILON);
    }
    {
      Vector3D<float> u{};
      u[0] = 5.0;
      u[1] = 5.0;
      u[2] = 5.0;

      Vector3D<float> v{};
      v[0] = -0.1;
      v[1] = -0.2;
      v[2] = -0.3;

      Vector3D<float> z = Project(u, v);
      TS_ASSERT_DELTA(z[0], 2.1428, EPSILON);
      TS_ASSERT_DELTA(z[1], 4.2857, EPSILON);
      TS_ASSERT_DELTA(z[2], 6.4285, EPSILON);
    }
  }

  void testVector3DNormalize() {
    {
      Vector3D<int> v{};
      v[0] = 5.0;
      v[1] = 5.0;
      v[2] = 5.0;

      Vector3D<float> z = Normalize(v);
      TS_ASSERT_DELTA(z[0], 0.5773, EPSILON);
      TS_ASSERT_DELTA(z[1], 0.5773, EPSILON);
      TS_ASSERT_DELTA(z[2], 0.5773, EPSILON);
    }
    {
      Vector3D<float> v{};
      v[0] = 5.1;
      v[1] = 5.2;
      v[2] = 5.3;

      Vector3D<float> z = Normalize(v);
      TS_ASSERT_DELTA(z[0], 0.5661, EPSILON);
      TS_ASSERT_DELTA(z[1], 0.5772, EPSILON);
      TS_ASSERT_DELTA(z[2], 0.5883, EPSILON);
    }
    {
      Vector3D<double> v{};
      v[0] = -0.1;
      v[1] = -0.2;
      v[2] = -0.3;

      Vector3D<float> z = Normalize(v);
      TS_ASSERT_DELTA(z[0], -0.2672, EPSILON);
      TS_ASSERT_DELTA(z[1], -0.5345, EPSILON);
      TS_ASSERT_DELTA(z[2], -0.8017, EPSILON);
    }
  }

  void testVector3DCrossProduct() {
    {
      Vector3D<int> u{};
      u[0] = 5;
      u[1] = 5;
      u[2] = 5;

      Vector3D<int> v{};
      v[0] = 5;
      v[1] = 5;
      v[2] = 5;

      Vector3D<int> z = CrossProduct(u, v);
      TS_ASSERT_EQUALS(z[0], 0);
      TS_ASSERT_EQUALS(z[1], 0);
      TS_ASSERT_EQUALS(z[2], 0);
    }
    {
      Vector3D<float> u;
      u[0] = 5.0;
      u[1] = 5.0;
      u[2] = 5.0;

      Vector3D<float> v;
      v[0] = 5.1;
      v[1] = 5.2;
      v[2] = 5.3;

      Vector3D<float> z = CrossProduct(u, v);
      TS_ASSERT_DELTA(z[0], 0.5, EPSILON);
      TS_ASSERT_DELTA(z[1], -1.0, EPSILON);
      TS_ASSERT_DELTA(z[2], 0.5, EPSILON);
    }
    {
      Vector3D<double> u{};
      u[0] = 5.0;
      u[1] = 5.0;
      u[2] = 5.0;

      Vector3D<double> v{};
      v[0] = -0.1;
      v[1] = -0.2;
      v[2] = -0.3;

      Vector3D<double> z = CrossProduct(u, v);
      TS_ASSERT_DELTA(z[0], -0.5, EPSILON);
      TS_ASSERT_DELTA(z[1], 1.0, EPSILON);
      TS_ASSERT_DELTA(z[2], -0.5, EPSILON);
    }
  }

  // --------------------- VECTOR 2D TESTS -----------------------------------

  void testVector2DElementAccess() {
    {
      Vector2D<int> v{};
      TS_ASSERT_EQUALS(v[0], 0.0);
      TS_ASSERT_EQUALS(v[1], 0.0);

      const Vector2D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0], 0.0);
      TS_ASSERT_EQUALS(cv[1], 0.0);
    }
    {
      Vector2D<float> v{0.1, 0.2};
      TS_ASSERT_DELTA(v[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.2, EPSILON);

      const Vector2D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], 0.2, EPSILON);
    }
    {
      Vector2D<double> v{-0.1, -0.2};
      TS_ASSERT_DELTA(v[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], -0.2, EPSILON);

      const Vector2D<double>& cv = v;
      TS_ASSERT_DELTA(cv[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], -0.2, EPSILON);
    }
  }

  void testVector2DElementAssignment() {
    {
      Vector2D<int> v{};
      v[0] = 0;
      v[1] = 1;

      // Copy constructor
      Vector2D<float> u{v};
      TS_ASSERT_DELTA(u[0], 0.0, EPSILON);
      TS_ASSERT_DELTA(u[1], 1.0, EPSILON);

      const Vector2D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0], 0);
      TS_ASSERT_EQUALS(cv[1], 1);
    }
    {
      Vector2D<float> v{};
      v[0] = 0.1;
      v[1] = 0.2;

      Vector2D<double> u{};
      u = v;
      TS_ASSERT_DELTA(u[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(u[1], 0.2, EPSILON);

      const Vector2D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], 0.2, EPSILON);
    }
    {
      Vector2D<float> v{};
      v[0] = -0.1;
      v[1] = -0.2;

      Vector2D<float> u = v;
      TS_ASSERT_DELTA(u[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(u[1], -0.2, EPSILON);

      const Vector2D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], -0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1], -0.2, EPSILON);
    }
  }

  void testVector2DElementMultiplication() {
    {
      Vector2D<int> v{1, 1};

      v *= 5;
      TS_ASSERT_EQUALS(v[0], 5);
      TS_ASSERT_EQUALS(v[1], 5);

      const Vector2D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0], 5);
      TS_ASSERT_EQUALS(cv[1], 5);
    }
    {
      Vector2D<float> v;
      v[0] = 0.1;
      v[1] = 0.2;
      v[2] = 0.3;

      v *= 2;
      TS_ASSERT_DELTA(v[0], 0.2, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.4, EPSILON);

      const Vector2D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0], 0.2, EPSILON);
      TS_ASSERT_DELTA(cv[1], 0.4, EPSILON);
    }
    {
      Vector2D<double> v;
      v[0] = -0.1;
      v[1] = -0.2;

      v *= 2;
      TS_ASSERT_DELTA(v[0], -0.2, EPSILON);
      TS_ASSERT_DELTA(v[1], -0.4, EPSILON);

      const Vector2D<double>& cv = v;
      TS_ASSERT_DELTA(cv[0], -0.2, EPSILON);
      TS_ASSERT_DELTA(cv[1], -0.4, EPSILON);
    }
  }

  void testVector2DElementDivision() {
    {
      Vector2D<int> v{25, 25};

      v /= 5;
      TS_ASSERT_EQUALS(v[0], 5);
      TS_ASSERT_EQUALS(v[1], 5);
    }
    {
      Vector2D<float> v{5.1, 5.2};

      v /= 5;
      TS_ASSERT_DELTA(v[0], 1.02, EPSILON);
      TS_ASSERT_DELTA(v[1], 1.04, EPSILON);
    }
    {
      Vector2D<double> v{-0.1, -0.2};

      v /= -1;
      TS_ASSERT_DELTA(v[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.2, EPSILON);
    }
  }

  void testVector2DElementVectorAddition() {
    {
      Vector2D<int> u{5, 5};

      Vector2D<int> v{5, 5};

      v += u;
      TS_ASSERT_EQUALS(v[0], 10);
      TS_ASSERT_EQUALS(v[1], 10);
    }
    {
      Vector2D<float> u{5.f, 5.f};

      Vector2D<float> v{5.1f, 5.2f};

      v += u;
      TS_ASSERT_DELTA(v[0], 10.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 10.2, EPSILON);
    }
    {
      Vector2D<double> u{5., 5.};

      Vector2D<double> v{-.1, -.2};

      v += u;
      TS_ASSERT_DELTA(v[0], 4.9, EPSILON);
      TS_ASSERT_DELTA(v[1], 4.8, EPSILON);
    }
  }

  void testVector2DElementVectorSubtraction() {
    {
      Vector2D<int> u{5, 5};

      Vector2D<int> v{5, 5};

      v -= u;
      TS_ASSERT_EQUALS(v[0], 0);
      TS_ASSERT_EQUALS(v[1], 0);
    }
    {
      Vector2D<float> u{5.f, 5.f};

      Vector2D<float> v{5.1f, 5.2f};

      v -= u;
      TS_ASSERT_DELTA(v[0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1], 0.2, EPSILON);
    }
    {
      Vector2D<double> u{5., 5.};

      Vector2D<double> v{-.1, -.2};

      v -= u;
      TS_ASSERT_DELTA(v[0], -5.1, EPSILON);
      TS_ASSERT_DELTA(v[1], -5.2, EPSILON);
    }
  }

  void testVector2DSquaredDistance() {
    {
      Vector2D<int> u{5, 5};
      Vector2D<int> v{5, 5};
      TS_ASSERT_EQUALS(u.squaredDistance(v), 0);
      TS_ASSERT_EQUALS(v.squaredDistance(u), 0);
    }
    {
      Vector2D<float> u{5.3f, 10.1f};
      Vector2D<float> v{5.0f, -1.5f};
      const float expectedXDif = (5.3f - 5.0f);
      const float expectedYDif = (10.1f - (-1.5f));
      const float expected =
          (expectedXDif * expectedXDif) + (expectedYDif * expectedYDif);
      TS_ASSERT_DELTA(u.squaredDistance(v), expected, EPSILON);
      TS_ASSERT_DELTA(v.squaredDistance(u), expected, EPSILON);
    }
  }

  void testVector2DDotProduct() {
    {
      Vector2D<int> u{5, 5};

      Vector2D<int> v{5, 5};

      float z = Dot(u, v);
      TS_ASSERT_EQUALS(z, 50);
    }
    {
      Vector2D<float> u{
          5.f,
          5.f,
      };

      Vector2D<float> v{5.1f, 5.2f};

      float z = Dot(u, v);
      TS_ASSERT_DELTA(z, 51.5, EPSILON);
    }
    {
      Vector2D<double> u{5., 5.};

      Vector2D<double> v{-.1, -.2};

      double z = Dot(u, v);
      TS_ASSERT_DELTA(z, -1.5, EPSILON);
    }
  }

  void testVector2DMagnitude() {
    {
      Vector2D<int> v{5, 5};

      float z = Magnitude(v);
      TS_ASSERT_DELTA(z, 7.071, EPSILON);
    }
    {
      Vector2D<float> v{};
      v[0] = 5.1;
      v[1] = 5.2;

      float z = Magnitude(v);
      TS_ASSERT_DELTA(z, 7.2835, EPSILON);
    }
    {
      Vector2D<double> v{};
      v[0] = -0.1;
      v[1] = -0.2;

      double z = Magnitude(v);
      TS_ASSERT_DELTA(z, 0.223, EPSILON);
    }
  }

  void testVector2DProject() {
    {
      Vector2D<float> u{};
      u[0] = 5.0;
      u[1] = 5.0;

      Vector2D<float> v{};
      v[0] = 5.0;
      v[1] = 5.0;

      Vector2D<float> z = Project(u, v);
      TS_ASSERT_DELTA(z[0], 5.0, EPSILON);
      TS_ASSERT_DELTA(z[1], 5.0, EPSILON);
    }
    {
      Vector2D<float> u{};
      u[0] = 5.0;
      u[1] = 5.0;

      Vector2D<float> v{};
      v[0] = 5.1;
      v[1] = 5.2;

      Vector2D<float> z = Project(u, v);
      TS_ASSERT_DELTA(z[0], 4.9509, EPSILON);
      TS_ASSERT_DELTA(z[1], 5.0480, EPSILON);
    }
    {
      Vector2D<float> u{};
      u[0] = 5.0;
      u[1] = 5.0;

      Vector2D<float> v{};
      v[0] = -0.1;
      v[1] = -0.2;

      Vector2D<float> z = Project(u, v);
      TS_ASSERT_DELTA(z[0], 2.9999, EPSILON);
      TS_ASSERT_DELTA(z[1], 5.9999, EPSILON);
    }
  }

  void testVector2DNormalize() {
    {
      Vector2D<int> v{};
      v[0] = 5.0;
      v[1] = 5.0;

      Vector2D<float> z = Normalize(v);
      TS_ASSERT_DELTA(z[0], 0.7071, EPSILON);
      TS_ASSERT_DELTA(z[1], 0.7071, EPSILON);
    }
    {
      Vector2D<float> v{};
      v[0] = 5.1;
      v[1] = 5.2;

      Vector2D<float> z = Normalize(v);
      TS_ASSERT_DELTA(z[0], 0.7002, EPSILON);
      TS_ASSERT_DELTA(z[1], 0.7139, EPSILON);
    }
    {
      Vector3D<double> v{};
      v[0] = -0.1;
      v[1] = -0.2;

      Vector3D<float> z = Normalize(v);
      TS_ASSERT_DELTA(z[0], -0.4472, EPSILON);
      TS_ASSERT_DELTA(z[1], -0.8944, EPSILON);
    }
  }

  void testVector2DCrossProduct() {
    {
      Vector2D<int> u{};
      u[0] = 5;
      u[1] = 5;

      Vector2D<int> v{};
      v[0] = 5;
      v[1] = 5;

      int z = CrossProduct(u, v);
      TS_ASSERT_EQUALS(z, 0);
    }
    {
      Vector2D<float> u{};
      u[0] = 5.0;
      u[1] = 5.0;

      Vector2D<float> v;
      v[0] = 5.1;
      v[1] = 5.2;

      float z = CrossProduct(u, v);
      TS_ASSERT_DELTA(z, 0.5, EPSILON);
    }
    {
      Vector2D<double> u{};
      u[0] = 5.0;
      u[1] = 5.0;

      Vector2D<double> v{};
      v[0] = -0.1;
      v[1] = -0.2;

      double z = CrossProduct(u, v);
      TS_ASSERT_DELTA(z, -0.5, EPSILON);
    }
  }

  // --------------------- MATRIX 3D TESTS -----------------------------------

  void testMatrix3DElementAccess() {
    {
      Matrix3D<int> v{};
      TS_ASSERT_EQUALS(v[0][0], 0.0);
      TS_ASSERT_EQUALS(v[1][0], 0.0);

      const Matrix3D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0][0], 0.0);
      TS_ASSERT_EQUALS(cv[1][0], 0.0);
    }
    {
      Matrix3D<float> v{{0.1, 0.2, 0.3}, {0.1, 0.2, 0.3}, {0.1, 0.2, 0.3}};
      TS_ASSERT_DELTA(v[0][0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1][0], 0.1, EPSILON);

      const Matrix3D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0][0], 0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1][0], 0.1, EPSILON);
    }
    {
      Matrix3D<double> v{
          {-0.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}};
      TS_ASSERT_DELTA(v[0][0], -0.1, EPSILON);
      TS_ASSERT_DELTA(v[1][0], -0.1, EPSILON);

      const Matrix3D<double>& cv = v;
      TS_ASSERT_DELTA(cv[0][0], -0.1, EPSILON);
      TS_ASSERT_DELTA(cv[1][0], -0.1, EPSILON);
    }
  }

  void testMatrix3DElementMultiplication() {
    {
      Matrix3D<int> v{};

      v *= 5;
      TS_ASSERT_EQUALS(v[0][0], 0.0);
      TS_ASSERT_EQUALS(v[1][0], 0.0);

      const Matrix3D<int>& cv = v;
      TS_ASSERT_EQUALS(cv[0][0], 0.0);
      TS_ASSERT_EQUALS(cv[1][0], 0.0);
    }
    {
      Matrix3D<float> v{{0.1, 0.2, 0.3}, {0.1, 0.2, 0.3}, {0.1, 0.2, 0.3}};

      v *= 5;
      TS_ASSERT_DELTA(v[0][0], 0.5, EPSILON);
      TS_ASSERT_DELTA(v[1][0], 0.5, EPSILON);

      const Matrix3D<float>& cv = v;
      TS_ASSERT_DELTA(cv[0][0], 0.5, EPSILON);
      TS_ASSERT_DELTA(cv[1][0], 0.5, EPSILON);
    }
    {
      Matrix3D<double> v{
          {-0.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}};

      v *= 5;
      TS_ASSERT_DELTA(v[0][0], -0.5, EPSILON);
      TS_ASSERT_DELTA(v[1][0], -0.5, EPSILON);

      const Matrix3D<double>& cv = v;
      TS_ASSERT_DELTA(cv[0][0], -0.5, EPSILON);
      TS_ASSERT_DELTA(cv[1][0], -0.5, EPSILON);
    }
  }

  void testMatrix3DElementDivision() {
    {
      Matrix3D<int> v{};

      v /= 5;
      TS_ASSERT_EQUALS(v[0][0], 0);
      TS_ASSERT_EQUALS(v[1][0], 0);
      TS_ASSERT_EQUALS(v[2][0], 0);
    }
    {
      Matrix3D<float> v{{0.1, 0.2, 0.3}, {0.1, 0.2, 0.3}, {0.1, 0.2, 0.3}};

      v /= 5;
      TS_ASSERT_DELTA(v[0][0], 0.0199, EPSILON);
      TS_ASSERT_DELTA(v[1][0], 0.0199, EPSILON);
      TS_ASSERT_DELTA(v[2][0], 0.0199, EPSILON);
    }
    {
      Matrix3D<double> v{
          {-0.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}};

      v /= -1;
      TS_ASSERT_DELTA(v[0][0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[1][0], 0.1, EPSILON);
      TS_ASSERT_DELTA(v[2][0], 0.1, EPSILON);
    }
  }

  void testMatrix3DElementVectorAddition() {
    {
      Matrix3D<int> u{{4, 5, 6}, {2, 7, 4}, {1, 9, 8}};

      Matrix3D<int> v{{4, 5, 6}, {2, 7, 4}, {1, 9, 8}};

      v += u;
      TS_ASSERT_EQUALS(v[0][0], 8);
      TS_ASSERT_EQUALS(v[1][0], 4);
      TS_ASSERT_EQUALS(v[2][0], 2);
    }
    {
      Matrix3D<double> u{
          {-2.1, -0.2, -0.3}, {-9.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}};

      Matrix3D<double> v{
          {-5.1, -0.2, -0.3}, {-0.1, -5.2, -0.3}, {-0.1, -0.2, -5.3}};

      v += u;
      TS_ASSERT_DELTA(v[0][0], -7.2, EPSILON);
      TS_ASSERT_DELTA(v[1][0], -9.2, EPSILON);
      TS_ASSERT_DELTA(v[2][0], -0.2, EPSILON);
    }
    {
      Matrix3D<float> u{
          {-0.1, -0.2, -0.3}, {-0.1, -3.2, -0.3}, {-0.1, -0.2, -2.3}};

      Matrix3D<float> v{
          {-1.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}, {-0.1, -0.2, -1.3}};

      v += u;
      TS_ASSERT_DELTA(v[0][0], -1.2, EPSILON);
      TS_ASSERT_DELTA(v[1][0], -0.2, EPSILON);
      TS_ASSERT_DELTA(v[2][0], -0.2, EPSILON);
    }
  }

  void testMatrix3DElementVectorSubtraction() {
    {
      Matrix3D<int> u{{4, 5, 6}, {2, 7, 4}, {1, 9, 8}};

      Matrix3D<int> v{{4, 5, 6}, {2, 7, 4}, {1, 9, 8}};

      v -= u;
      TS_ASSERT_EQUALS(v[0][0], 0);
      TS_ASSERT_EQUALS(v[1][0], 0);
      TS_ASSERT_EQUALS(v[2][0], 0);
    }
    {
      Matrix3D<double> u{
          {-2.1, -0.2, -0.3}, {-9.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}};

      Matrix3D<double> v{
          {-5.1, -0.2, -0.3}, {-0.1, -5.2, -0.3}, {-0.1, -0.2, -5.3}};

      v -= u;
      TS_ASSERT_DELTA(v[0][0], -3, EPSILON);
      TS_ASSERT_DELTA(v[1][0], 9, EPSILON);
      TS_ASSERT_DELTA(v[2][0], 0, EPSILON);
    }
    {
      Matrix3D<float> u{
          {-0.1, -0.2, -0.3}, {-0.1, -3.2, -0.3}, {-0.1, -0.2, -2.3}};

      Matrix3D<float> v{
          {-1.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}, {-0.1, -0.2, -1.3}};

      v -= u;
      TS_ASSERT_DELTA(v[0][0], -1.0, EPSILON);
      TS_ASSERT_DELTA(v[1][0], 0.0, EPSILON);
      TS_ASSERT_DELTA(v[2][0], 0.0, EPSILON);
    }
  }

  void testMatrix3DElementTranspose() {
    {
      Matrix3D<int> v{{4, 5, 6}, {2, 7, 4}, {1, 9, 8}};

      v = Transpose(v);
      TS_ASSERT_EQUALS(v[0][0], 4);
      TS_ASSERT_EQUALS(v[1][0], 5);
      TS_ASSERT_EQUALS(v[2][0], 6);
    }
    {
      Matrix3D<double> v{
          {-2.1, -0.2, -0.3}, {-9.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}};

      v = Transpose(v);
      TS_ASSERT_DELTA(v[0][0], -2.1, EPSILON);
      TS_ASSERT_DELTA(v[1][0], -0.2, EPSILON);
      TS_ASSERT_DELTA(v[2][0], -0.3, EPSILON);
    }
    {
      Matrix3D<float> v{
          {-0.1, -0.2, -0.3}, {-0.1, -3.2, -0.3}, {-0.1, -0.2, -2.3}};

      v = Transpose(v);
      TS_ASSERT_DELTA(v[0][0], -0.1, EPSILON);
      TS_ASSERT_DELTA(v[1][0], -0.2, EPSILON);
      TS_ASSERT_DELTA(v[2][0], -0.3, EPSILON);
    }
  }

  void testMatrix3DElementDeterminant() {
    {
      Matrix3D<int> v{{4, 5, 6}, {2, 7, 4}, {1, 9, 8}};

      float u = Determinant(v);
      TS_ASSERT_EQUALS(u, 86);
    }
    {
      Matrix3D<double> v{
          {-2.1, -0.2, -0.3}, {-9.1, -0.2, -0.3}, {-0.1, -0.2, -0.3}};

      float u = Determinant(v);
      TS_ASSERT_DELTA(u, 0, EPSILON);
    }
    {
      Matrix3D<float> v{
          {-0.1, -0.2, -0.3}, {-0.1, -3.2, -0.3}, {-0.1, -0.2, -2.3}};

      float u = Determinant(v);
      TS_ASSERT_DELTA(u, -0.6, EPSILON);
    }
  }
};
