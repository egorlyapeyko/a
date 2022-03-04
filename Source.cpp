#include "Pqueue.h"

Priority_Queue& Priority_Queue::operator=(const Priority_Queue& Q)
{
	if (this != &Q)
	{
		Erase();
		Clone(Q);
	}
	return *this;
}

void Priority_Queue::Erase()
{
	while (pop());
	size_high = 0;
	size_medium = 0;
	size_low = 0;
	size = 0;
}



void Priority_Queue::move(QItem*& a, QItem*& b)
{
	a = b;
	b = nullptr;
}
   //from presentation
void Priority_Queue::move(Priority_Queue&& pq)
{
	move(front, pq.front);
	move(high_rear, pq.high_rear);
	move(medium_rear, pq.medium_rear);
	move(low_rear, pq.low_rear);
	size_high = pq.size_high;
	pq.size_high = NULL;
	size_medium = pq.size_medium;
	pq.size_medium = NULL;
	size_low = pq.size_low;
	pq.size_low = NULL;
	size = pq.size;
	pq.size = NULL;
}



// Standart constructor clone



void Priority_Queue::Clone(const Priority_Queue& q)
{
	QItem* tmp = q.front;
	for (unsigned i = 0; i < q.GetSize(); i++)
	{
		Push(tmp->info, tmp->status);
		tmp = tmp->next;
	}
}
Priority_Queue::Priority_Queue(const Priority_Queue& Q)
{
	size = 0;
	Clone(Q);
}

// peregruzka operatora

Priority_Queue& Priority_Queue::operator=(Priority_Queue&& pq) noexcept
{
	if (&pq == this)
		return *this;
	Erase();
	move(front, pq.front);
	move(high_rear, pq.high_rear);
	move(medium_rear, pq.medium_rear);
	move(low_rear, pq.low_rear);
	size = pq.size;
	size_high = pq.size_high;
	size_medium = pq.size_medium;
	size_low = pq.size_low;

	pq.size_high = 0;
	pq.size_medium = 0;
	pq.size_low = 0;
	pq.size = 0;
	return *this;
}

//check empty

bool Priority_Queue::IsEmpty() const
{
	return (size == 0);
}

Priority_Queue::~Priority_Queue()
{
	Erase();
}

int Priority_Queue::GetSize() const
{
	return size;
}

int Priority_Queue::GetSizeInHigh() const
{
	return size_high;
}

int Priority_Queue::GetSizeInMedium() const
{
	return size_medium;
}

int Priority_Queue::GetSizeInLow() const
{
	return size_low;
}



void Priority_Queue::Push(InfoType Ainfo, Priority prio_)
{
	if (int(prio_) < 1 || int(prio_) > PRIORITY_COUNT)
		throw logic_error("Error  inc. priority");
	//logic error better


	QItem* tmp1 = new QItem(Ainfo, prio_);
	// Method Push ochen mnogo koda

#pragma region one
	// vstavka v ochered. Sdvig ykazatelei
	if (prio_ == Priority(Priority::high)) {
		if (medium_rear != 0 || low_rear != 0) {
			if (high_rear != 0) {
				QItem* tmp2 = high_rear->next;
				high_rear->next = tmp1;
				tmp1->next = tmp2;
			}
			else {
				QItem* tmp2 = front;
				front = tmp1;
				tmp1->next = tmp2;
			}
		}
		if (medium_rear == 0 && low_rear == 0) {
			if (size > 0)
				high_rear->next = tmp1;
			else
				front = tmp1;
		}
		high_rear = tmp1;
		size_high++;
	}
	if (prio_ == Priority(Priority::medium)) {
		if (high_rear != 0 && low_rear == 0)
			if (medium_rear != 0)
				medium_rear->next = tmp1;
			else
				high_rear->next = tmp1;

		if (high_rear == 0 && low_rear == 0)
			if (medium_rear != 0)
				medium_rear->next = tmp1;
			else
				front = tmp1;

		if (high_rear == 0 && low_rear != 0) {
			if (medium_rear != 0) {
				QItem* tmp2 = medium_rear->next;
				medium_rear->next = tmp1;
				tmp1->next = tmp2;
			}
			else {
				QItem* tmp2 = front;
				front = tmp1;
				tmp1->next = tmp2;
			}
		}
		if (high_rear != 0 && low_rear != 0) {
			{
				if (medium_rear != 0) {
					QItem* tmp2 = medium_rear->next;
					medium_rear->next = tmp1;
					tmp1->next = tmp2;
				}
				else {
					QItem* tmp2 = high_rear->next;
					high_rear->next = tmp1;
					tmp1->next = tmp2;
				}
			}
		}

		medium_rear = tmp1;
		size_medium++;
	}
	if (prio_ == Priority(Priority::low)) {
		if (low_rear != 0)
			low_rear->next = tmp1;
		else
			if (size == 0)
				front = tmp1;
			else
				if (medium_rear != 0)
					medium_rear->next = tmp1;
				else
					high_rear->next = tmp1;
		low_rear = tmp1;
		size_low++;
	}
	size++;
#pragma endregion
}

bool Priority_Queue::pop()
{
	if (size == 0)
		return false;
	QItem* tmp = front;
	if ((front->status) == Priority::high)
		size_high--;
	if ((front->status) == Priority::medium)
		size_medium--;  // YBIRAEM ZAVISANIE YKAZATELEI
	if ((front->status) == Priority::low)
		size_low--;
	front = front->next;
	delete tmp;
	size--;
	if (size_low == 0)
		low_rear = 0;
	if (size_medium == 0) 
		medium_rear = 0;
	if (size_high == 0)
		high_rear = 0;
	if (size == 0)
	{
		
		medium_rear = 0;
		low_rear = 0;

		high_rear = 0;
	}
	return true;
}

InfoType Priority_Queue::GetFirst() const\
{
	if (size == 0)
		throw logic_error("Impossible to execute\GetFirst:queue is empty");
	return front->info;
}

string Priority_Queue::GetFirstPriority() const
{
	return PRIORITY_NAMES[(int)front->status - 1];
}

InfoType Priority_Queue::operator[](int M) const
{

	if ((M < 0) || (M >= size))
		throw exception("Impossible to execute\operator[]: invalid index");
	QItem* tmp = front;
	for (unsigned i = 0; i < M; i++)
		tmp = tmp->next;

	return tmp->info;
}

Priority_Queue::Priority_Queue(Priority_Queue&& pq) noexcept
{
	move(front, pq.front);
	move(high_rear, pq.high_rear);
	move(medium_rear, pq.medium_rear);
	move(low_rear, pq.low_rear);
	size = pq.size;
	pq.size = NULL;
	size_high = pq.size_high;
	pq.size_high = NULL;
	size_medium = pq.size_medium;
	pq.size_medium = NULL;
	size_low = pq.size_low;
	pq.size_low = NULL;
}