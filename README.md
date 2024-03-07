# GLA (Graphics Linear Algebra)
A tiny C++ header-only linear algebra library for graphics.

This library is more of a personal project - 
if you are looking for a math or linear algebra library for *OpenGL*,
I'd recommend using more vast and sophisticated libraries, like [GLM](https://github.com/g-truc/glm).

All matrices are column-major by default and the transformation matrices follow the right handed coordinate system:
```cpp
    +y
     |
     |
     |________ 
    /        +x
+z /
```

Library also contains various additional functions that are not necessarily related to computer graphics.

## Vector
**Dimensions**
| 2 | 3 | 4 |
| - | - | - |

**Properties**
- [x] Size
- [x] Length
- [x] Squared length
- [x] Opposite
- [x] Normalized
- [x] Dot product
- [x] Cross product
- [x] Reflection
- [x] Distance

## Matrix
**Dimensions**
| 2x2 | 3x3 | 4x4 |
| --- | --- | --- |

**Properties**
- [x] Identity
- [x] Transpose
- [x] Cofactor
- [x] Adjugate
- [x] Inverse
- [x] Trace
- [x] Determinant
- [x] Submatrix

**Transformation**
- [x] Model matrix
- [x] View matrix
- [x] Projection matrix (perspective & orthographic)
- [x] Translation matrix
- [x] Rotation matrix
- [x] Scale matrix

## Example Usage
```cpp
#include <GLA/gla.h>        // include GLA
#include <GLA/debug.h>      // allows for formatted prints of vectors and matricies

int main(int argc, char *argv[])
{
    // initialization of a 4D vector
    gla::vec4 vector(-1, 3, 7.5F, 11);
    
    // print out formatted unit vector of the above vector
    gla::debug::print_vec(vector.normalized());

    std::cout << "\n" << std::endl;

    // declaration of a 4x4 matrix
    gla::mat4x4 matrix;
    
    // definition of matrix values
    float matrix_values[4][4] =
    {
        { 1, 4, 7, 0 },
        { 9, 5, 8, 4 },
        { 3, 6, 9, 1 },
        { 9, 7, 3, 3 },
    };

    // insertion of values into the matrix
    matrix.insert(matrix_values);

    // print out formatted transpose of the above 4x4 matrix
    gla::debug::print_mat(matrix.transpose());

    std::cout << "\n" << std::endl;

    std::cout << "minor of a submatrix: " << matrix.submatrix(1, 1).determinant() << std::endl;
  
    return 0;
}
```