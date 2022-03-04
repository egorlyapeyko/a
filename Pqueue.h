#pragma once
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

constexpr auto START_LINE_PRIORITY = __LINE__;
enum class Priority {
	high = 1,
	medium,
	low
};
constexpr auto PRIORITY_COUNT = __LINE__ - START_LINE_PRIORITY - 3;
const string PRIORITY_NAMES[] = { "high", "medium", "low" };

typedef int InfoType;


class Priority_Queue
{
private:
	struct QItem
	{
		InfoType info;
		Priority status;
		QItem* next;
		QItem(InfoType _info, Priority prioritet_) : info(_info), status(prioritet_), next(0) {}
	};
	QItem* front, * high_rear, * medium_rear, * low_rear;
	int size, size_high, size_medium, size_low;

	void Erase();
	void Clone(const Priority_Queue&);
	void move(QItem*&, QItem*&);
	void move(Priority_Queue&& other);
public:
	Priority_Queue() :front(0), high_rear(0), medium_rear(0), low_rear(0), size(0) {};
	Priority_Queue(const Priority_Queue&);
	
	bool IsEmpty() const;

	Priority_Queue(Priority_Queue&&) noexcept;

	~Priority_Queue();

	Priority_Queue& operator = (const Priority_Queue&);
	Priority_Queue& operator = (Priority_Queue&&) noexcept;

	
	int GetSizeInLow()const;
	int GetSizeInHigh()const;
	int GetSizeInMedium()const;

	void Push(InfoType Ainfo, Priority astatus);
	bool pop();
	int GetSize()const;
	InfoType GetFirst()const;
	string GetFirstPriority()const;
	InfoType operator [](int M)const;
	
};

