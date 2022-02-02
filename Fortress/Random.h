#pragma once

//�ߺ� ���� ���� ����
// ���� �� ~ ���� ���� ����(-������ ����, ������� unsigned int),
// �� ��� ����, �迭�� ���ʴ�� �־ ��ȯ(�����Ҵ�� �迭�� �����ͷ� ��ȯ)
// ex) 1~ 50 ����
//-> �����Ҵ����� size 50, �ʱ�ȭ�� 1~50, �ε��� ����
//index = rand()%size �� �޾� ���� ���� �ε����� ���� ���� ��� ��̿� �ְ�,
//index�� ���� �迭�� ���� ��(size-1)���� ��ü �� size 1 ���� 
// ->���� rand()%size ���� size�� 1���������Ƿ� �� �� �迭�� ���� rand���� ���ܵȴ�
//[12345] ���� 3�� ������ [1254]3  ([]�� rand�� ����, ���������� --size;)
class Random 
{
private:
	constexpr void Swap(int& a, int& b);
	int* result;
	unsigned int arr_size;
	
public:

	Random() = default;
	Random(int const& start_num, int const& end_num, unsigned const& count);
	Random(Random const& r);
	int GetResult(unsigned const& index)const;
	bool operator ==(Random const & right_rand)const;
	bool operator !=(Random const & right_rand)const;
	Random& operator =(Random const & right_rand);
	operator int() const; //rand�� ���� ������ ��ȯ ����ϴ°��
	~Random();

	//void Print()const; //�ܼ� �׽�Ʈ��

};