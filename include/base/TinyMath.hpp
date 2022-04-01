// Support Code written by Michael D. Shah
// Updated by Seth Cooper and then the Breakout team
// Please do not redistribute without asking permission.

#ifndef TINYMATH_HPP
#define TINYMATH_HPP

#include <cmath>
#include <iostream>

#define RT_DEFAULT_MAX 1.e27f

// Forward references of each of the structs
template <typename T>
struct Vector3D;
template <typename T>
struct Matrix3D;
template <typename T>
struct Vector2D;

struct Ray;

// ----------------------- VECTOR 3D -------------------------------------------

/**
 * @brief A class for packaging values into a 3-dimensional vector and
 * performing operations on it. Primarily intended to be used for 3D Graphics.
 *
 * @tparam T type stored within the Vector3D, usually numerical
 */
template <typename T>
struct Vector3D {
  /**
   * @brief Direct member access to elements of this vector, in order: x, y, z
   */
  T x, y, z;

  /**
   * @brief Default constructor
   * @details 'why default?'
   * https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
   */
  Vector3D() = default;

  /**
   * @brief Construct a 3D vector with particular elements (in order)
   *
   * @param a 1st elem
   * @param b 2nd elem
   * @param c 3rd elem
   */
  Vector3D(T a, T b, T c) { x = a, y = b, z = c; }

  /**
   * @brief Copy constructor, change the elements of this vector to those of the
   * other vector.
   *
   * @tparam Y type of elements in the source vector
   * @param v Source vector
   */
  template <typename Y>
  explicit Vector3D(const Vector3D<Y>& v) {
    x = static_cast<T>(v.x), y = static_cast<T>(v.y), z = static_cast<T>(v.z);
  }

  /**
   * @brief Assignment operator for copying
   * Note that the copy can be between multiple underlying types.
   * If an operation involves two vectors with different types one must "cast"
   * it to another type using this function
   * @tparam Y
   * @param v
   * @return Vector3D<T>&
   */
  template <typename Y>
  Vector3D<T>& operator=(const Vector3D<Y>& v) {
    x = static_cast<T>(v.x), y = static_cast<T>(v.y), z = static_cast<T>(v.z);
    return (*this);
  }

  /**
   * @brief Index operator, allowing us to access the individual 
   * x,y,z components of our vector.
   * 
   * @param i 0-based idx to get
   * @return T& element type
   */
  T& operator[](int i) { return ((&x)[i]); }


  /**
   * @brief Index operator, allowing us to access the individual 
   * x,y,z components of our vector.
   * 
   * @param i idx to get
   * @return T& element type
   */
  const T& operator[](int i) const { return ((&x)[i]); }

  /**
   * @brief Multiply vector by a uniform-scalar.
   * 
   * @param s scalar to multiply with
   * @return Vector3D<T>& reference to this (now scaled) vector
   */
  Vector3D<T>& operator*=(T s) {
    x *= s, y *= s, z *= s;
    return (*this);
  }

  // Division Operator
  // No division by ints are allowed. All inputs need to be implicitly or
  // explicitly cast to float
  Vector3D<T>& operator/=(float s) {
    x /= s, y /= s, z /= s;
    return (*this);
  }

  // Addition operator
  Vector3D<T>& operator+=(const Vector3D<T>& v) {
    x += v.x, y += v.y, z += v.z;
    return (*this);
  }

  // Subtraction operator
  Vector3D<T>& operator-=(const Vector3D<T>& v) {
    x -= v.x, y -= v.y, z -= v.z;
    return (*this);
  }
};

// Print Vector
template <typename T>
std::ostream& operator<<(std::ostream& s, const Vector3D<T>& a) {
  s << "[" << a.x << ", " << a.y << ", " << a.z << "]";
  return s;
}

// Compute the dot product of a Vector3D
template <typename T>
inline float Dot(const Vector3D<T>& a, const Vector3D<T>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Multiplication of a vector by a scalar values
template <typename T>
inline Vector3D<T> operator*(const Vector3D<T>& v, T s) {
  return {v.x * s, v.y * s, v.z * s};
}

// Division of a vector by a scalar value.
template <typename T>
inline Vector3D<T> operator/(const Vector3D<T>& v, float s) {
  return {static_cast<T>(v.x / s), static_cast<T>(v.y / s),
          static_cast<T>(v.z / s)};
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
template <typename T>
inline Vector3D<T> operator-(const Vector3D<T>& v) {
  return {-v.x, -v.y, -v.z};
}

template <typename T>
inline bool operator==(const Vector3D<T>& lhs, const Vector3D<T>& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

// Return the magnitude of a vector
template <typename T>
inline float Magnitude(const Vector3D<T>& v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

// Add two vectors together
template <typename T>
inline Vector3D<T> operator+(const Vector3D<T>& a, const Vector3D<T>& b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

// Subtract two vectors
template <typename T>
inline Vector3D<T> operator-(const Vector3D<T>& a, const Vector3D<T>& b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

// Vector Projection
// Does not have a template to force users to cast to float
inline Vector3D<float> Project(const Vector3D<float>& a,
                               const Vector3D<float>& b) {
  float mag = Dot(a, b) / Dot(b, b);
  return b * mag;
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
template <typename T>
inline Vector3D<float> Normalize(const Vector3D<T>& v) {
  // Cast to float before returning
  Vector3D<float> out{v};
  return out / Magnitude(v);
}

// a x b (read: 'a crossed b')
// Produces a new vector perpendicular to a and b.
// (So long as a and b are not parallel which returns zero vector)
template <typename T>
inline Vector3D<T> CrossProduct(const Vector3D<T>& a, const Vector3D<T>& b) {
  return {a.y * b.z - b.y * a.z, b.x * a.z - a.x * b.z, a.x * b.y - b.x * a.y};
}

// ----------------------- VECTOR 2D -------------------------------------------

/**
 * @brief A class for packaging values into a 2-dimensional vector and
 * performing operations on it. Primarily intended to be used for 2D Graphics.
 *
 * @tparam T type stored within the Vector2D, usually numerical
 */
template <typename T>
struct Vector2D {
  /**
   * @brief Direct member access to elements of this vector, in order: x, y
   */
  T x, y;

  /**
   * @brief Default constructor
   * @details 'why default?'
   * https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
   */
  Vector2D() = default;

  /**
   * @brief Construct a 2D vector with particular elements (in order)
   *
   * @param a 1st elem
   * @param b 2nd elem
   * @param c 3rd elem
   */
  Vector2D(T a, T b) { x = a, y = b; }

  /**
   * @brief Copy constructor, change the elements of this vector to those of the
   * other vector.
   *
   * @tparam Y type of elements in the source vector
   * @param v Source vector
   */
  template <typename Y>
  explicit Vector2D(const Vector2D<Y>& v) {
    x = static_cast<T>(v.x), y = static_cast<T>(v.y);
  }

  /**
   * @brief Assignment operator for copying
   * Note that the copy can be between multiple underlying types.
   * If an operation involves two vectors with different types one must "cast"
   * it to another type using this function
   * @tparam Y
   * @param v
   * @return Vector2D<T>&
   */
  template <typename Y>
  Vector2D<T>& operator=(const Vector2D<Y>& v) {
    x = static_cast<T>(v.x), y = static_cast<T>(v.y);
    return (*this);
  }

  /**
   * @brief Index operator, allowing us to access the individual 
   * x,y components of our vector.
   * 
   * @param i idx to get
   * @return T& element type
   */
  T& operator[](int i) {
    return ((&x)[i]);
  }

  /**
   * @brief Index operator, allowing us to access the individual
   * x,y components of our vector.
   * 
   * @param i idx
   * @return const T& element type
   */
  const T& operator[](int i) const {
    return ((&x)[i]);
  }

  /**
   * @brief Multiply vector by a uniform-scalar.
   * 
   * @param s scalar to multiply with
   * @return Vector2D<T>& reference to this (now scaled) vector
   */
  Vector2D<T>& operator*=(T s) {
    x *= s, y *= s;
    return (*this);
  }

  // Division Operator
  // No division by ints are allowed. All inputs need to be implicitly or
  // explicitly cast to float
  Vector2D<T>& operator/=(float s) {
    x /= s, y /= s;
    return (*this);
  }

  // Addition operator
  Vector2D<T>& operator+=(const Vector2D<T>& v) {
    x += v.x, y += v.y;
    return (*this);
  }

  // Subtraction operator
  Vector2D<T>& operator-=(const Vector2D<T>& v) {
    x -= v.x, y -= v.y;
    return (*this);
  }
};

template <typename T>
inline bool operator==(const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

// Print Vector
template <typename T>
std::ostream& operator<<(std::ostream& s, const Vector2D<T>& a) {
  s << "[" << a.x << ", " << a.y << "]";
  return s;
}

// Compute the dot product of a Vector3D
template <typename T>
inline float Dot(const Vector2D<T>& a, const Vector2D<T>& b) {
  return a.x * b.x + a.y * b.y;
}

// Multiplication of a vector by a scalar values
template <typename T>
inline Vector2D<T> operator*(const Vector2D<T>& v, T s) {
  return {v.x * s, v.y * s};
}

// Division of a vector by a scalar value.
template <typename T>
inline Vector2D<T> operator/(const Vector2D<T>& v, float s) {
  return {static_cast<T>(v.x / s), static_cast<T>(v.y / s)};
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
template <typename T>
inline Vector2D<T> operator-(const Vector2D<T>& v) {
  return {-v.x, -v.y};
}

// Return the magnitude of a vector
template <typename T>
inline float Magnitude(const Vector2D<T>& v) {
  return std::sqrt(v.x * v.x + v.y * v.y);
}

// Add two vectors together
template <typename T>
inline Vector2D<T> operator+(const Vector2D<T>& a, const Vector2D<T>& b) {
  return {a.x + b.x, a.y + b.y};
}

// Subtract two vectors
template <typename T>
inline Vector2D<T> operator-(const Vector2D<T>& a, const Vector2D<T>& b) {
  return {a.x - b.x, a.y - b.y};
}

// Vector Projection
// Does not have a template to force users to cast to float
inline Vector2D<float> Project(const Vector2D<float>& a,
                               const Vector2D<float>& b) {
  float mag = Dot(a, b) / Dot(b, b);
  return b * mag;
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
template <typename T>
inline Vector2D<float> Normalize(const Vector2D<T>& v) {
  // Cast to float before returning
  Vector2D<float> out{v};
  return out / Magnitude(v);
}

// a x b (read: 'a crossed b')
// Produces a new vector perpendicular to a and b.
// (So long as a and b are not parallel which returns zero vector)
template <typename T>
inline T CrossProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
  return a.x * b.y - b.x * a.y;
}

// ----------------------- MATRIX 3D -------------------------------------------

/**
 * @brief A class representing a 3x3 matrix.
 *
 * @tparam T element type, usually numerical
 */
template <typename T>
struct Matrix3D {
 private:
  T n[3][3];  // Store each value of the matrix

 public:
  /**
   * @brief Construct a new empty 3D matrix
   */
  Matrix3D() = default;

  /**
   * @brief Construct a new 3D Matrix of scalar values, indexed [row,col]
   *
   * @param n00 value for mat[0,0]
   * @param n01 value for mat[0,1]
   * @param n02 value for mat[0,2]
   * @param n10 value for mat[1,0]
   * @param n11 value for mat[1,1]
   * @param n12 value for mat[1,1]
   * @param n20 value for mat[2,0]
   * @param n21 value for mat[2,1]
   * @param n22 value for mat[2,1]
   */
  Matrix3D(T n00, T n01, T n02, T n10, T n11, T n12, T n20, T n21, T n22) {
    n[0][0] = n00;
    n[0][1] = n01;
    n[0][2] = n02;
    n[1][0] = n10;
    n[1][1] = n11;
    n[1][2] = n12;
    n[2][0] = n20;
    n[2][1] = n21;
    n[2][2] = n22;
  }

  /**
   * @brief Construct a new 3D Matrix from 3 row vectors
   *
   * @param a values for 1st row of matrix
   * @param b values for 2nd row of matrix
   * @param c values for 3rd row of matrix
   */
  Matrix3D(const Vector3D<T>& a, const Vector3D<T>& b, const Vector3D<T>& c) {
    n[0][0] = a.x;
    n[0][1] = a.y;
    n[0][2] = a.z;
    n[1][0] = b.x;
    n[1][1] = b.y;
    n[1][2] = b.z;
    n[2][0] = c.x;
    n[2][1] = c.y;
    n[2][2] = c.z;
  }

  template <typename Y>
  explicit Matrix3D(Matrix3D<Y> mat) {
    n[0][0] = static_cast<T>(mat(0, 0));
    n[0][1] = static_cast<T>(mat(0, 1));
    n[0][2] = static_cast<T>(mat(0, 2));
    n[1][0] = static_cast<T>(mat(1, 0));
    n[1][1] = static_cast<T>(mat(1, 1));
    n[1][2] = static_cast<T>(mat(1, 2));
    n[2][0] = static_cast<T>(mat(2, 0));
    n[2][1] = static_cast<T>(mat(2, 1));
    n[2][2] = static_cast<T>(mat(2, 2));
  }

  template <typename Y>
  Matrix3D& operator=(Matrix3D<Y> mat) {
    n[0][0] = static_cast<T>(mat(0, 0));
    n[0][1] = static_cast<T>(mat(0, 1));
    n[0][2] = static_cast<T>(mat(0, 2));
    n[1][0] = static_cast<T>(mat(1, 0));
    n[1][1] = static_cast<T>(mat(1, 1));
    n[1][2] = static_cast<T>(mat(1, 2));
    n[2][0] = static_cast<T>(mat(2, 0));
    n[2][1] = static_cast<T>(mat(2, 1));
    n[2][2] = static_cast<T>(mat(2, 2));
    return *(this);
  }

  /**
   * @brief Index operator with two dimensions
   * Example: M(1,1) returns row 1 and column 1 of matrix M.
   *
   * @param i row idx to get
   * @param j col idx to get
   * @return T& reference to the element at the corresponding location
   */
  T& operator()(int i, int j) { return (n[i][j]); }

  /**
   * @brief Constant index operator with two dimensions
   * Example: M(1,1) returns row 1 and column 1 of matrix M.
   *
   * @param i row idx to get
   * @param j col idx to get
   * @return const T& reference to the element at the corresponding location
   */
  const T& operator()(int i, int j) const { return (n[i][j]); }

  /**
   * @brief Return a row from a matrix as a vector.
   *
   * @param i row idx to get
   * @return Vector3D<T>& referene to a matrix of the elements in the specified
   * row
   */
  Vector3D<T>& operator[](int i) {
    return (*reinterpret_cast<Vector3D<T>*>(n[i]));
  }

  // Return a row from a matrix as a vector.
  const Vector3D<T>& operator[](int i) const {
    return (*reinterpret_cast<const Vector3D<T>*>(n[i]));
  }

  /**
   * @brief Multiply matrix by a uniform-scalar.
   * 
   * @param s scalar to multiply with
   * @return Matrix3D<T>& reference to this (now scaled) matrix
   */
  Matrix3D<T>& operator*=(T s) {
    n[0][0] *= s;
    n[0][1] *= s;
    n[0][2] *= s;
    n[1][0] *= s;
    n[1][1] *= s;
    n[2][1] *= s;
    n[2][0] *= s;
    n[2][1] *= s;
    n[2][2] *= s;
    return (*this);
  }

  /**
   * @brief Divide matrix by uniform-scalar. No division by ints allowed,
   * all inputs need to be implicitly or explicitly cast to float.
   * 
   * @param s scalar to divide with
   * @return Matrix3D<T>& reference to this (now scaled) matrix
   */
  Matrix3D<T>& operator/=(float s) {
    n[0][0] /= s;
    n[0][1] /= s;
    n[0][2] /= s;
    n[1][0] /= s;
    n[1][1] /= s;
    n[2][1] /= s;
    n[2][0] /= s;
    n[2][1] /= s;
    n[2][2] /= s;
    return (*this);
  }

  // Addition operator
  Matrix3D<T>& operator+=(const Matrix3D<T>& v) {
    n[0][0] += v(0, 0);
    n[0][1] += v(0, 1);
    n[0][2] += v(0, 2);
    n[1][0] += v(1, 0);
    n[1][1] += v(1, 1);
    n[2][1] += v(1, 2);
    n[2][0] += v(2, 0);
    n[2][1] += v(2, 1);
    n[2][2] += v(2, 2);
    return (*this);
  }

  // Subtraction operator
  Matrix3D<T>& operator-=(const Matrix3D<T>& v) {
    n[0][0] -= v(0, 0);
    n[0][1] -= v(0, 1);
    n[0][2] -= v(0, 2);
    n[1][0] -= v(1, 0);
    n[1][1] -= v(1, 1);
    n[2][1] -= v(1, 2);
    n[2][0] -= v(2, 0);
    n[2][1] -= v(2, 1);
    n[2][2] -= v(2, 2);
    return (*this);
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& s, const Matrix3D<T>& a) {
  s << "[[" << a(0, 0) << ", " << a(0, 1) << ", " << a(0, 2) << "]"
    << std::endl;
  s << " [" << a(1, 0) << ", " << a(1, 1) << ", " << a(1, 2) << "]"
    << std::endl;
  s << " [" << a(2, 0) << ", " << a(2, 1) << ", " << a(2, 2) << "]]";
  return s;
}

template <typename T>
Matrix3D<T> operator+(const Matrix3D<T>& mat, const T s) {
  return {mat(0, 0) + s, mat(0, 1) + s, mat(0, 2) + s,
          mat(1, 0) + s, mat(1, 1) + s, mat(1, 2) + s,
          mat(2, 0) + s, mat(2, 1) + s, mat(2, 2) + s};
}

template <typename T>
Matrix3D<T> operator-(const Matrix3D<T>& mat, const T s) {
  return {mat(0, 0) - s, mat(0, 1) - s, mat(0, 2) - s,
          mat(1, 0) - s, mat(1, 1) - s, mat(1, 2) - s,
          mat(2, 0) - s, mat(2, 1) - s, mat(2, 2) - s};
}

template <typename T>
Matrix3D<T> operator*(const Matrix3D<T>& mat, const T s) {
  return {mat(0, 0) * s, mat(0, 1) * s, mat(0, 2) * s,
          mat(1, 0) * s, mat(1, 1) * s, mat(1, 2) * s,
          mat(2, 0) * s, mat(2, 1) * s, mat(2, 2) * s};
}

template <typename T>
Matrix3D<T> operator/(const Matrix3D<T>& mat, const float s) {
  return {mat(0, 0) / s, mat(0, 1) / s, mat(0, 2) / s,
          mat(1, 0) / s, mat(1, 1) / s, mat(1, 2) / s,
          mat(2, 0) / s, mat(2, 1) / s, mat(2, 2) / s};
}

template <typename T>
Matrix3D<T> operator+(const Matrix3D<T>& A, const Matrix3D<T>& B) {
  return {A(0, 0) + B(0, 0), A(0, 1) + B(0, 1), A(0, 2) + B(0, 2),
          A(1, 0) + B(1, 0), A(1, 1) + B(1, 1), A(1, 2) + B(1, 2),
          A(2, 0) + B(2, 0), A(2, 1) + B(2, 1), A(2, 2) + B(2, 2)};
}

// Matrix Multiplication
template <typename T>
Matrix3D<T> operator*(const Matrix3D<T>& A, const Matrix3D<T>& B) {
  Matrix3D<T> C;
  C(0, 0) = A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0);
  C(0, 1) = A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1);
  C(0, 2) = A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2);
  C(1, 0) = A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0);
  C(1, 1) = A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1);
  C(1, 2) = A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2);
  C(2, 0) = A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0);
  C(2, 1) = A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1);
  C(2, 2) = A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2);
  return C;
}

// Matrix multiply by a vector
template <typename T>
Vector3D<T> operator*(const Matrix3D<T>& M, const Vector3D<T>& v) {
  return {M(0, 0) * v[0] + M(0, 1) * v[1] + M(0, 2) * v[2],
          M(1, 0) * v[0] + M(1, 1) * v[1] + M(1, 2) * v[2],
          M(2, 0) * v[0] + M(2, 1) * v[1] + M(2, 2) * v[2]};
}

template <typename T>
Vector3D<T> operator*(const Vector3D<T>& v, const Matrix3D<T>& M) {
  return M * v;
}

template <typename T>
inline Matrix3D<T> Identity() {
  return {1, 0, 0, 0, 1, 0, 0, 0, 1};
}

template <typename T>
Matrix3D<T> Transpose(const Matrix3D<T>& mat) {
  return {mat(0, 0), mat(1, 0), mat(2, 0), mat(0, 1), mat(1, 1),
          mat(2, 1), mat(0, 2), mat(1, 2), mat(2, 2)};
}

template <typename T>
float Determinant(const Matrix3D<T>& mat) {
  return mat(0, 0) * (mat(1, 1) * mat(2, 2) - mat(2, 1) * mat(1, 2)) -
         mat(0, 1) * (mat(1, 0) * mat(2, 2) - mat(2, 0) * mat(1, 2)) +
         mat(0, 2) * (mat(1, 0) * mat(2, 1) - mat(2, 0) * mat(1, 1));
}

inline Matrix3D<float> RotationMatrix3dX(float angleRad) {
  return {1,
          0,
          0,
          0,
          std::cos(angleRad),
          -std::sin(angleRad),
          0,
          std::sin(angleRad),
          std::cos(angleRad)};
}

inline Matrix3D<float> RotationMatrix3dY(float angleRad) {
  return {std::cos(angleRad),  0, std::sin(angleRad), 0, 1, 0,
          -std::sin(angleRad), 0, std::cos(angleRad)};
}

inline Matrix3D<float> RotationMatrix3dZ(float angleRad) {
  return {std::cos(angleRad),
          -std::sin(angleRad),
          0,
          std::sin(angleRad),
          std::cos(angleRad),
          0,
          0,
          0,
          1};
}

inline Vector3D<float> RotateX(const Vector3D<float>& tensor, float angleRad) {
  return RotationMatrix3dX(angleRad) * tensor;
}

inline Vector3D<float> RotateY(const Vector3D<float>& tensor, float angleRad) {
  return RotationMatrix3dY(angleRad) * tensor;
}

inline Vector3D<float> RotateZ(const Vector3D<float>& tensor, float angleRad) {
  return RotationMatrix3dZ(angleRad) * tensor;
}

// ------------------------- RAY -----------------------------------------------

/**
 * @brief A class representing a 3-dimensional Ray of floats and performing
 * operations on it.
 */
struct Ray {
  /**
   * @brief The 3D origin point of this Ray.
   */
  Vector3D<float> origin;

  /**
   * @brief The 3D direction of this Ray.
   */
  Vector3D<float> direction;

  /**
   * @brief The ray type associated with this Ray.
   */
  unsigned int ray_type;

  // The min and max extents associated with this ray
  float tmin;
  float tmax;

  /**
   * @brief Default construct a new Ray object
   */
  Ray() = default;

  /**
   * @brief Construct a new Ray object from specified elements
   *
   * @param a the origin of this Ray
   * @param b the direction of this Ray
   * @param c the type of this Ray
   * @param d the min value for an element of this Ray (restrict range of
   * floats)
   * @param e the max value for an element of this Ray (restrict range of
   * floats)
   */
  Ray(Vector3D<float> a, Vector3D<float> b, unsigned int c, float d,
      float e = RT_DEFAULT_MAX) {
    origin = a, direction = b, ray_type = c, tmin = d, tmax = e;
  }
};

#endif
