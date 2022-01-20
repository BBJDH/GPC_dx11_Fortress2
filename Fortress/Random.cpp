#include "Random.h"
#include "stdafx.h"


#pragma region Random Ŭ���� ����
//�ߺ� ���� ���� ����
// ���� �� ~ ���� ���� ����(-������ ����, ������� unsigned int),
// �� ��� ����, �迭�� ���ʴ�� �־ ��ȯ(�����Ҵ�� �迭�� �����ͷ� ��ȯ)
// ex) 1~ 50 ����
//-> �����Ҵ����� size 50, �ʱ�ȭ�� 1~50, �ε��� ����
//index = rand()%size �� �޾� ���� ���� �ε����� ���� ���� ��� ��̿� �ְ�,
//index�� ���� �迭�� ���� ��(size-1)���� ��ü �� size 1 ���� 
// ->���� rand()%size ���� size�� 1���������Ƿ� �� �� �迭�� ���� rand���� ���ܵȴ�
//[12345] ���� 3�� ������ [1254]3  ([]�� rand�� ����, ���������� --size;)


// 1 2 3 4 5 6 7 8 9
// 0 1 2 3 4 5 6 7 8  rand()%9 ->0~8
// 5�� ����
// 1 2 3 4 5 9 7 8] 6
// rand()%8 
//
Random::Random(int const& start_num, int const& end_num, unsigned const& count) :arr_size(count)
{
	assert(end_num > start_num);
	assert(count > 0);

	unsigned size = end_num - start_num + 1;
	int value = start_num;

	int* const Arry_Range = new int[size] {};

	for (unsigned i = 0; i < size; ++i)
	{
		Arry_Range[i] = value++;
	}  //���� ����

	result = new int[count] {};


	for (unsigned i = 0; i < count; ++i)
	{
		int const index = rand() % size;
		result[i] = Arry_Range[index];
		Swap(Arry_Range[index], Arry_Range[size - 1]);
		--size;
	}

}
Random::Random(Random const& r) :result(r.result), arr_size(r.arr_size)
{}
int Random::GetResult(unsigned const& index)const
{
	assert(index < arr_size);
	return result[index];
}
bool Random::operator==(Random const& right_rand)const
{
	
	return this->result == right_rand.result;
}
bool Random::operator!=(Random const& right_rand)const
{
	return !(*this==right_rand);
}
//void Random::Print() const
//{
//	for (unsigned i = 0; i < arr_size; i++)
//	{
//		std::cout << result[i] << "\t";
//		if (i % 10 == 9)
//			std::cout << std::endl;
//	}
//	std::cout << std::endl;
//
//}

Random::operator int() const
{
	assert(result != nullptr);
	assert(arr_size == 1);
	return result[0];
}

Random& Random::operator=(Random const& right_rand)
{
	if (*this != right_rand)
	{
		delete[] result;
		this->arr_size = right_rand.arr_size;
		this->result = new int[this->arr_size];
		for (size_t i = 0; i < right_rand.arr_size; i++)
		{
			this->result[i] = right_rand.result[i];
		}
	}
	return *this;

}

Random::~Random()
{
	delete[] result;
}

constexpr void Random::Swap(int& a, int& b)
{
	int temp = 0;
	temp = a;
	a = b;
	b = temp;
}

#pragma endregion