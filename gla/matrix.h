#pragma once

#include "gla.h"

/*
    ┌----------------------------------------┐
    | all matrices are in column-major order |
    |                                        |
    | matrix[column][row]                    |
    └----------------------------------------┘

    ┌----------------------------------------┐
    | available properties:                  |
    |                                        |
    | [x] identity                           |
    | [x] transpose                          |
    | [x] cofactor                           |
    | [x] adjugate                           |
    | [x] inverse                            |
    | [x] trace                              |
    | [x] determinant                        |
    | [x] submatrix                          |
    └----------------------------------------┘
*/

#include "mat2x2.h"
#include "mat3x3.h"
#include "mat4x4.h"

#include "matrix_transform.h"