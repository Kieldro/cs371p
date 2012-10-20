// ------------------------------
// projects/matlab/TestMatlab.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestMatlab.c++ -o TestMatlab.app
 *     valgrind TestMatlab.app >& TestMatlab.out
 */

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include "Matrix.h"
#include "Matlab.h"

// ----------
// TestMatlab
// ----------

struct TestMatlab : CppUnit::TestFixture {
    // --------
    // test_cat
    // --------

    void test_horzcat_1() {
        Matrix<int> x(1, 2, 3);
        Matrix<int> y(1, 3, 3);
        Matrix<int> z(1, 5, 3);
        x = horzcat(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_horzcat_2() {
        Matrix<int> x(2, 1, 0);
        Matrix<int> y(2, 1, 3);
        Matrix<int> z(2, 2);
        z[0][1] = 3;
        z[1][1] = 3;
        x = horzcat(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_horzcat_3() {
        Matrix<int> x(1, 1, -1);
        Matrix<int> y(1, 1, 3);
        Matrix<int> z(1, 2, 3);
        z[0][0] = -1;
        x = horzcat(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_vertcat_1() {
        Matrix<int> x;
        Matrix<int> y;
        Matrix<int> z;
        x = vertcat(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_vertcat_2() {
        Matrix<int> x(2, 1, 1);
        Matrix<int> y(3, 1, 1);
        Matrix<int> z(5, 1, 1);
        x = vertcat(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_vertcat_3() {
        Matrix<int> x(2, 4);
        Matrix<int> y(1, 4);
        Matrix<int> z(3, 4);
        x = vertcat(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }
// ---------
    // test_diag
    // ---------

    void test_diag_1() {
        Matrix<int> x;
        Matrix<int> y;
        x = diag(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_diag_2() {
        Matrix<int> x(1, 1, 2);
        Matrix<int> y(1, 1, 2);
        x = diag(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_diag_3() {
        Matrix<int> x(2, 2, 5);
        Matrix<int> y(1, 2, 5);
        x = diag(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    // --------
    // test_dot
    // --------

    void test_dot_1() {
        Matrix<int> x(1, 1, 1);
        Matrix<int> y(1, 1, 1);
        Matrix<int> z(1, 1, 1);
        x = dot(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_dot_2() {
        Matrix<int> x(1, 2, 2);
        Matrix<int> y(1, 2, 1);
        Matrix<int> z(1, 1, 4);
        x = dot(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_dot_3() {
        Matrix<int> x(2, 1, 2);
        Matrix<int> y(2, 1, 1);
        Matrix<int> z(1, 1, 4);
        x = dot(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_dot_4() {
        Matrix<int> x(2, 2, 2);
        Matrix<int> y(2, 2);
        Matrix<int> z(1, 2, 2);

        y = eye<Matrix<int> >(2, 2);
        x = dot(x, y);
        CPPUNIT_ASSERT(x.eq(z));
    }

    // --------
    // test_eye
    // --------

    void test_eye_1() {
        Matrix<int> x;
        Matrix<int> y(2, 3);
        y[0][0] = 1;
        y[1][1] = 1;
        x = eye<Matrix<int> >(2, 3);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_eye_2() {
        Matrix<int> x;
        Matrix<int> y(1, 1, 1);
        x = eye<Matrix<int> >(1, 1);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_eye_3() {
        Matrix<int> x;
        Matrix<int> y(3, 2);
        y[0][0] = 1;
        y[1][1] = 1;
        x = eye<Matrix<int> >(3, 2);
        CPPUNIT_ASSERT(x.eq(y));
    }
    // -------------
    // test_linsolve
    // -------------

    void test_linsolve_1() {
        Matrix<double> A(2,2);
        Matrix<double> b(2,1);
        Matrix<double> z(2,1);

        A[0][0] = 1; A[0][1] = 2;
        A[1][0] = 3; A[1][1] = 4;

        b[0][0] = 2; b[1][0] = 6;

        z[0][0] = 2; z[1][0] = 0;

        Matrix<double> x = linsolve(A, b);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_linsolve_2() {
        Matrix<double> A(2,2);
        Matrix<double> b(2,1);
        Matrix<double> z(2,1);

        A[0][0] = 1; A[0][1] = 2;
        A[1][0] = 2; A[1][1] = 3;

        b[0][0] = 1; b[1][0] = 2;

        z[0][0] = 1; z[1][0] = 0;

        Matrix<double> x = linsolve(A, b);
        CPPUNIT_ASSERT(x.eq(z));
    }

    void test_linsolve_3() {
        Matrix<double> A(3,3);
        Matrix<double> b(3,1);
        Matrix<double> z(3,1);

        A[0][0] = -3; A[0][1] = 2; A[0][2] = -6;
        A[1][0] = 5; A[1][1] = 7; A[1][2] = -5;
        A[2][0] = 1; A[2][1] = 4; A[2][2] = -2;

        b[0][0] = 6; b[1][0] = 6; b[2][0] = 8;

        z[0][0] = -2; z[1][0] = 3; z[2][0] = 1;

        Matrix<double> x = linsolve(A, b);
        for (int i = 0; i < 3; ++i)
            CPPUNIT_ASSERT( (x[i][0] - z[i][0]) < 1E-3 );
    }

    // ---------------------------
    // test_gaussian_helper_method
    // ---------------------------

    void test_gauss_1() {
        Matrix<int> x(2,2,1);
        Matrix<int> y(2,2,0);
        y[0][0] = 1;
        y[0][1] = 1;
        x = gauss(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_gauss_2() {
        Matrix<int> x(2,2);
        Matrix<int> y(2,2);
        x[0][0] = 1; x[0][1] = 2;
        x[1][0] = 2; x[1][1] = 6;
        y[0][0] = 1; y[0][1] = 2;
                     y[1][1] = 2;
        x = gauss(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_gauss_3() {
        Matrix<int> x(2,2);
        Matrix<int> y(2,2);
        x[0][0] = 0; x[0][1] = 2;
        x[1][0] = 1; x[1][1] = 6;

        y[0][0] = 1; y[0][1] = 6;
        y[1][0] = 0; y[1][1] = 2;
        x = gauss(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_gauss_4() {
        Matrix<int> x(3,3);
        Matrix<int> y(3,3);
        x[0][0] = 0; x[0][1] = 2; x[0][2] = 3;
        x[1][0] = 1; x[1][1] = 6; x[1][2] = 2;
        x[1][0] = 1; x[1][1] = 6; x[1][2] = 2;

        y[0][0] = 1; y[0][1] = 6; y[0][2] = 2;
        y[1][0] = 0; y[1][1] = 2; y[1][2] = 3;

        x = gauss(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    // ---------
    // test_ones
    // ---------

    void test_ones_1() {
        Matrix<int> x;
        Matrix<int> y;
        x = ones<Matrix<int> >(0, 0);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_ones_2() {
        Matrix<int> x;
        Matrix<int> y(2, 3, 1);
        x = ones<Matrix<int> >(2, 3);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_ones_3() {
        Matrix<int> x;
        Matrix<int> y(1, 1, 1);
        x = ones<Matrix<int> >(1, 1);
        CPPUNIT_ASSERT(x.eq(y));
    }

    // ---------
    // test_rand
    // ---------

    void test_rand_1() {
        Matrix<double> x;
        x = rand<Matrix<double> >(2, 3);
        CPPUNIT_ASSERT(x.num_row() == 2);
        CPPUNIT_ASSERT(x.num_col() == 3);
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 3; ++j)
                CPPUNIT_ASSERT(x[i][j] != 0 && x[i][j] < 1);
    }

    void test_rand_2() {
        Matrix<int> x;
        x = rand<Matrix<int> >(0, 0);
        CPPUNIT_ASSERT(x.num_row() == 0);
        CPPUNIT_ASSERT(x.num_col() == 0);
    }

    void test_rand_3() {
        Matrix<double> x;
        x = rand<Matrix<double> >(10, 10);
        CPPUNIT_ASSERT(x.num_row() == 10);
        CPPUNIT_ASSERT(x.num_col() == 10);
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                CPPUNIT_ASSERT(x[i][j] != 0 && x[i][j] < 1);
    }

    // --------------
    // test_transpose
    // --------------

    void test_transpose_1() {
        Matrix<int> x(1, 1, 2);
        Matrix<int> y(1, 1, 2);
        x = transpose(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_transpose_2() {
        Matrix<int> x(1, 2, 1);
        Matrix<int> y(2, 1, 1);
        x = transpose(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_transpose_3() {
        Matrix<int> x(2, 2);
        x = eye<Matrix<int> >(2, 2);
        x = transpose(x);
        CPPUNIT_ASSERT(x.eq(x));
    }

    void test_transpose_4() {
        Matrix<int> x(2, 2);
        Matrix<int> y(2, 2);
        x[0][1] = 1;
        y[1][0] = 1;
        x = transpose(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    // ---------
    // test_tril
    // ---------

    void test_tril_1() {
        Matrix<int> x(1, 1, 1);
        Matrix<int> y(1, 1, 1);
        x = tril(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_tril_2() {
        Matrix<int> x(1, 2, 1);
        Matrix<int> y(1, 2, 0);
        y[0][0] = 1;
        x = tril(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_tril_3() {
        Matrix<int> x(2, 2, 1);
        Matrix<int> y(2, 2, 1);
        y[0][1] = 0;
        x = tril(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    // ---------
    // test_triu
    // ---------

    void test_triu_1() {
        Matrix<int> x(1, 1, 1);
        Matrix<int> y(1, 1, 1);
        x = triu(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_triu_2() {
        Matrix<int> x(1, 2, 1);
        Matrix<int> y(1, 2, 1);
        x = triu(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_triu_3() {
        Matrix<int> x(2, 2, 1);
        Matrix<int> y(2, 2, 1);
        y[1][0] = 0;
        x = triu(x);
        CPPUNIT_ASSERT(x.eq(y));
    }

    // ----------
    // test_zeros
    // ----------

    void test_zeros_1() {
        Matrix<int> x;
        Matrix<int> y;
        x = zeros<Matrix<int> >(0, 0);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_zeros_2() {
        Matrix<int> x(1, 1);
        Matrix<int> y(1, 1);
        x = zeros<Matrix<int> >(1, 1);
        CPPUNIT_ASSERT(x.eq(y));
    }

    void test_zeros_3() {
        Matrix<int> x(5, 5);
        Matrix<int> y(5, 5, 0);
        x = zeros<Matrix<int> >(5, 5);
        CPPUNIT_ASSERT(x.eq(y));
    }

    // -----
    // suite
    // -----

CPPUNIT_TEST_SUITE(TestMatlab);
        CPPUNIT_TEST(test_horzcat_1);
        CPPUNIT_TEST(test_horzcat_2);
        CPPUNIT_TEST(test_horzcat_3);
        CPPUNIT_TEST(test_vertcat_1);
        CPPUNIT_TEST(test_vertcat_2);
        CPPUNIT_TEST(test_vertcat_3);
        CPPUNIT_TEST(test_diag_1);
        CPPUNIT_TEST(test_diag_2);
        CPPUNIT_TEST(test_diag_3);
        CPPUNIT_TEST(test_eye_1);
        CPPUNIT_TEST(test_eye_2);
        CPPUNIT_TEST(test_eye_3);
        CPPUNIT_TEST(test_dot_1);
        CPPUNIT_TEST(test_dot_2);
        CPPUNIT_TEST(test_dot_3);
        CPPUNIT_TEST(test_dot_4);
        CPPUNIT_TEST(test_gauss_1);
        CPPUNIT_TEST(test_gauss_2);
        CPPUNIT_TEST(test_gauss_3);
        CPPUNIT_TEST(test_gauss_4);
        CPPUNIT_TEST(test_linsolve_1);
        CPPUNIT_TEST(test_linsolve_2);
        CPPUNIT_TEST(test_linsolve_3);
        CPPUNIT_TEST(test_ones_1);
        CPPUNIT_TEST(test_ones_2);
        CPPUNIT_TEST(test_ones_3);
        CPPUNIT_TEST(test_rand_1);
        CPPUNIT_TEST(test_rand_2);
        CPPUNIT_TEST(test_rand_3);
        CPPUNIT_TEST(test_transpose_1);
        CPPUNIT_TEST(test_transpose_2);
        CPPUNIT_TEST(test_transpose_3);
        CPPUNIT_TEST(test_transpose_4);
        CPPUNIT_TEST(test_tril_1);
        CPPUNIT_TEST(test_tril_2);
        CPPUNIT_TEST(test_tril_3);
        CPPUNIT_TEST(test_triu_1);
        CPPUNIT_TEST(test_triu_2);
        CPPUNIT_TEST(test_triu_3);
        CPPUNIT_TEST(test_zeros_1);
        CPPUNIT_TEST(test_zeros_2);
        CPPUNIT_TEST(test_zeros_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestMatlab.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestMatlab::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
