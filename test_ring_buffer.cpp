#include "test_ring_buffer.h"
#include "test.h"
#include "RingBuffer.h"

void test_push(){
	RingBuffer ring;
	for (int i = 0; i < 16; i++) {
		ASSERT(ring.push_back(i+1) == ErrorFilo::ok);
	}
	ASSERT(ring.push_back(17) == ErrorFilo::full);
	ring.flush();
	for (int i = 0; i < 16; i++) {
		ASSERT(ring.push_front(i+1) == ErrorFilo::ok);
	}
	ASSERT(ring.push_front(17) == ErrorFilo::full);
	ring.flush();
}
void test_pop(){
	RingBuffer ring;
	ASSERT(ring.pop_back() == ErrorFilo::empty);
	int er = ring.push_front(1);
	ASSERT(ring.pop_back() == ErrorFilo::ok);
	ring.flush();
	ASSERT(ring.pop_front() == ErrorFilo::empty);
	er = ring.push_front(1);
	ASSERT(ring.pop_front() == ErrorFilo::ok);
	ring.flush();
}
void test_get(){
	int ex;
	RingBuffer ring;
	ASSERT(ring.get_back(&ex) == ErrorFilo::empty);
	int er = ring.push_front(1);
	ASSERT(ring.get_back(&ex) == ErrorFilo::ok);
	ring.flush();
	ASSERT(ring.get_front(&ex) == ErrorFilo::empty);
	er = ring.push_front(1);
	ASSERT(ring.get_front(&ex) == ErrorFilo::ok);
	ring.flush();
	er = ring.push_front(1);
	er = ring.push_front(2);
	int element;
	er = ring.get_back(&element);
	ASSERT(element == 1);
	ring.flush();
	er = ring.push_front(1);
	er = ring.push_front(2);
	er = ring.get_front(&element);
	ASSERT(element == 2);
	ring.flush();
}


