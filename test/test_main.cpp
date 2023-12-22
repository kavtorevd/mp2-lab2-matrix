#include <gtest.h>
#include "tmatrix.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}





TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> v(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> v(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> v(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> v(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> v1(v));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> v1(2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			v1[i][j] = i + j;
	TDynamicMatrix<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> v1(2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			v1[i][j] = i + j;
	TDynamicMatrix<int> v2(std::move(v1));
	EXPECT_NE(&v1, &v2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> v(5);
	EXPECT_EQ(5, v.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> v(4);
	ASSERT_NO_THROW(v[0][0] = 10);
	EXPECT_EQ(10, v.at(0, 0));
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v.at(-1, -4));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v.at(5, 3));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> v(4);
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(v, v = v);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> v(4), v1(4);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			v[i][j] = i;
	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> v(2), v1(4);
	v = v1;
	EXPECT_EQ(v1, v.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> v(4), v1(2);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			v[i][j] = i;
	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v(2), v1(2);
	EXPECT_EQ(true, v == v1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v1(2);
	EXPECT_EQ(true, v1 == v1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> v1(2), v2(4);
	EXPECT_EQ(false, v1 == v2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(4), v1(4), v2(4);
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++) {
			v[i][j] = i;
			v1[i][j] = j;
			v2[i][j] = i + j;

		}
	EXPECT_EQ(v2, v + v1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> v(4), v1(2);
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(4), v1(4), v2(4);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			v[i][j] = i;
			v1[i][j] = j;
			v2[i][j] = i - j;
		}
	}
	EXPECT_EQ(v2, v - v1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> v(4), v1(2);
	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);

	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	TDynamicVector<int> v1(arr1, 3), v3(v1);
	EXPECT_EQ(v1, v3);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	TDynamicVector<int> v1(arr1, 3), v3(std::move(v1));
	EXPECT_NE(&v1, &v3);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(10);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(10);
	ASSERT_ANY_THROW(v.at(11));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(v, v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(10), v1(10);
	ASSERT_NO_THROW(v = v1);
	EXPECT_EQ(v1, v = v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(10), v1(5);
	ASSERT_NO_THROW(v = v1);
	EXPECT_EQ(v1.size(), v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(10), v1(5);
	ASSERT_NO_THROW(v = v1);
	EXPECT_EQ(v1, v = v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	int* arr3 = new int[3] { 1, 2, 3 };
	TDynamicVector<int> v1(arr1, 3), v3(arr3, 3);
	EXPECT_EQ(v1, v3);

	delete[] arr1;
	delete[] arr3;
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(4);
	EXPECT_EQ(v1 == v1, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(4), v2(5);
	EXPECT_EQ(v1 == v2, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	int* arr3 = new int[3] { 4, 5, 6 };
	TDynamicVector<int> v1(arr1, 3), v3(arr3, 3);
	EXPECT_EQ(v3, v1 + 3);

	delete[] arr1;
	delete[] arr3;
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	int* arr3 = new int[3] { -2, -1, 0 };
	TDynamicVector<int> v1(arr1, 3), v3(arr3, 3);
	EXPECT_EQ(v3, v1 - 3);

	delete[] arr1;
	delete[] arr3;
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	int* arr3 = new int[3] { 3, 6, 9 };
	TDynamicVector<int> v1(arr1, 3), v3(arr3, 3);
	EXPECT_EQ(v3, v1 * 3);

	delete[] arr1;
	delete[] arr3;
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	int* arr2 = new int[3] { 2, 3, 4 };
	int* arr3 = new int[3] { 3, 5, 7 };
	TDynamicVector<int> v1(arr1, 3), v2(arr2, 3), v3(arr3, 3);
	EXPECT_EQ(v3, v1 + v2);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(4);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	int* arr2 = new int[3] { 2, 3, 4 };
	int* arr3 = new int[3] { -1, -1, -1 };
	TDynamicVector<int> v1(arr1, 3), v2(arr2, 3), v3(arr3, 3);
	EXPECT_EQ(v3, v1 - v2);

	delete[] arr1;
	delete[] arr2;
	delete[] arr3;
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(4);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	int* arr1 = new int[3] { 1, 2, 3 };
	int* arr2 = new int[3] { 2, 3, 4 };
	TDynamicVector<int> v1(arr1, 3), v2(arr2, 3);
	EXPECT_EQ(20, v1 * v2);

	delete[] arr1;
	delete[] arr2;
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(4);
	ASSERT_ANY_THROW(v1 * v2);
}
