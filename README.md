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
