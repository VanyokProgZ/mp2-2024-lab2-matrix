#include "tmatrix.h"
#include <ctime>
#include <gtest.h>
#include <random>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
	}
	TDynamicMatrix<int> m1 = m;
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
	}
	TDynamicMatrix<int> m1 = m;	
	for (auto i = 999; i >-1; i--) for (auto j = 999; j > -1; j--) {
		m1[j][i] = (i*100 + (j * 10 % 53) + 93) % 1000003;
	}
	EXPECT_NE(m, m1);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(8020);
	EXPECT_NO_THROW(m.size());
	EXPECT_EQ(m.size(), 8020);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(1000);
	srand(time(0));
	int i = rand() % 1000, j = rand() % 1000, el = rand()%2989231;
	m[i][j] = el;
	EXPECT_EQ(el, m[i][j]);
}

//<set negative index>------------------------>
TEST(TDynamicMatrix, throws_when_set_element_with_negative_index_out)	//get ����� ������� ��� �� ���� �����������
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(-1).at(32) = 5);
}
TEST(TDynamicMatrix, throws_when_set_element_with_negative_index_in)
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(2).at(-4) = 5);
}
//end----------------------------------------->

//set large index----------------------------->
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_out_eq_sz)
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(1000).at(32) = 5);
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_in_eq_sz)
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(102).at(1000) = 5);
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_out_gr_sz)
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(10000).at(32) = 8);
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_in_gr_sz)
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(102).at(10000) = 8);
}
//end---------------------------------------->

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
	}
	TDynamicMatrix<int> m1 = m;
	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
	}
	TDynamicMatrix<int> m1(1000);
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(500);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i%500][j%500] = i + j * 10;
	}
	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(m1.size(), m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(500);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i % 500][j % 500] = i + j * 10;
	}

	ASSERT_NO_THROW(m1 = m);
	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i][j] = i + j * 10;
	}

	ASSERT_NO_THROW(m1 == m);
	EXPECT_EQ(m1==m, 1);
}
TEST(TDynamicMatrix, compare_not_equal_matrices_return_false)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 13;
		m1[i][j] = i + j * 10;
	}

	ASSERT_NO_THROW(m1 == m);
	EXPECT_EQ(m1 == m, false);
}
TEST(TDynamicMatrix, compare_not_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 13;
		m1[i][j] = i + j * 10;
	}

	ASSERT_NO_THROW(m1 != m);
	EXPECT_EQ(m1 != m, 1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
	}

	ASSERT_NO_THROW(m == m);
	EXPECT_EQ(m == m, 1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1001);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i][j] = i + j * 10;
	}

	ASSERT_NO_THROW(m1 == m);
	EXPECT_NE(m1 == m, 1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1000);
	TDynamicMatrix<int> res(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i][j] = i + j * 10;
		res[i][j] = 2 * (i + j * 10);
	}

	ASSERT_NO_THROW(m + m1);
	
	EXPECT_EQ(m1 + m, res);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1001);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i][j] = i + j * 10;
	}

	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1000);
	TDynamicMatrix<int> res(1000);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i][j] = i + j * 10;
		res[i][j] = 0;
	}

	ASSERT_NO_THROW(m - m1);
	EXPECT_EQ(m1 - m, res);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(1000);
	TDynamicMatrix<int> m1(1001);
	for (auto i = 0; i < 1000; i++) for (auto j = 0; j < 1000; j++) {
		m[i][j] = i + j * 10;
		m1[i][j] = i + j * 10;
	}

	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, scalar_mult_matrix)
{
	TDynamicMatrix<int> m(10);
	TDynamicMatrix<int> m1(10);
	srand(time(0));
	auto el = rand() % 2738;
	for (auto i = 0; i < 10; i++) for (auto j = 0; j < 10; j++) {
		m[i][j] = i + j * 10;
		m1[i][j] = (i + j * 10)*el;
	}

	ASSERT_NO_THROW(m*el);
	EXPECT_EQ(m * el, m1);
}
TEST(TDynamicMatrix, matrix_mult_vector)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> r1(3);
	TDynamicVector<int> r(3);
	for (auto i = 0; i < 3; i++) {
		r[i] = i+23;
	}
	for (auto i = 0; i < 3; i++)
	{
		for (auto j = 0; j < 3; j++) {
			m[i][j] = j+i*10;
		}
	}
	r1[0] = 74;
	r1[1] = 794;
	r1[2] = 1514;

	ASSERT_NO_THROW(r = m * r);
	EXPECT_EQ(r, r1);

}
TEST(TDynamicMatrix, matrix_mult_matrix) {
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> mr(2);
	for (auto i = 1; i <= 2; i++) for (auto j = 1; j <= 2; j++) {
		m[i-1][j-1] = i * 13 + j;
		m1[i-1][j-1] = i + j * 73;
	}

	mr[0][0] = 2161;
	mr[0][1] = 4278;
	mr[1][0] = 4098;
	mr[1][1] = 8113;
	
	ASSERT_NO_THROW(m = m * m1);
	EXPECT_EQ(m, mr);
}
