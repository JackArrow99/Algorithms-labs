#include "pch.h"
#include "../Lab2/Array.h"
#include "gtest/gtest.h"

//TESTS FOR int

// Empty array

TEST(IntArrayTest, DefaultConstructor)
{
	Array<int> a;
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.capacity(), 8);
}


// Non-default capacity

TEST(IntArrayTest, ConstructorCapacity)
{
	int capacity = 11;
	Array<int> a(capacity);

	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.capacity(), capacity);

	Array<std::string> b{ capacity };

	ASSERT_EQ(b.size(), 0);
	ASSERT_EQ(b.capacity(), capacity);
}


// Copy Constructor

TEST(IntArrayTest, CopyConstructor)
{
	int capacity = 10;
	int size = 5;
	Array<int> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert(i);

	Array<int> b(a);

	ASSERT_EQ(a.size(), b.size());
	ASSERT_EQ(a.capacity(), b.capacity());

	for (int i = 0; i < a.size(); ++i)
	{
		EXPECT_EQ(a[i], b[i]);
	}
}


// MoveConstructor

TEST(IntArrayTest, MoveConstructor)
{
	int capacity = 10;
	int size = 5;
	Array<int> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert(i);

	Array<int> b = std::move(a);

	EXPECT_EQ(size, b.size());
	EXPECT_EQ(capacity, b.capacity());

	for (int i = 0; i < size; ++i) {
		EXPECT_EQ(i, b[i]);
	}
}


//  Copy array

TEST(IntArrayTest, CopyFields)
{
	int capacity = 10;
	int size = 5;
	Array<int> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert(i * 2);

	Array<int> b{};
	b = a;

	EXPECT_EQ(size, b.size());
	EXPECT_EQ(capacity, b.capacity());
	EXPECT_EQ(size, a.size());

	for (int i = 0; i < a.size(); ++i) {
		EXPECT_EQ(b[i], a[i]);
	}
}


// Move fields

TEST(IntArrayTest, MoveFields)
{
	int capacity = 10;
	int size = 5;
	Array<int> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert(i * 2);

	Array<int> b{};
	b = std::move(a);

	EXPECT_EQ(size, b.size());
	EXPECT_EQ(capacity, b.capacity());

	for (int i = 0; i < a.size(); ++i) {
		EXPECT_EQ(b[i], i * 2);
	}
}


// Insert elements

TEST(IntArrayTest, Insert)
{
	int size = 30;
	Array<int> a(size);

	for (int i = 0; i < size; ++i)
		a.insert(i);

	ASSERT_EQ(a.size(), size);

	int value = 555;
	int index = 7;
	a.insert(index, value);

	for (int i = 0; i < index; ++i) {
		EXPECT_EQ(i, a[i]);
	}

	EXPECT_EQ(value, a[index]);

	for (int i = index; i < a.size() - 1; ++i) {
		EXPECT_EQ(i, a[i + 1]);
	}
}


// Remove element

TEST(IntArrayTest, Remove)
{
	int rempove_idx = 4;
	int size = 10;
	Array<int> a(size);

	for (int i = 0; i < size; ++i)
		a.insert(i);

	a.remove(rempove_idx);

	for (int i = 0; i < size - 1; ++i) {
		if (i < rempove_idx) {
			EXPECT_EQ(i, a[i]);
		}

		else if (i > rempove_idx) {
			EXPECT_EQ(i, a[i - 1]);
		}
	}
}
 

// Expand Capacity

TEST(IntArrayTest, CapacityExpand)
{
	int size = 10;
	Array<int> a(size);

	for (int i = 0; i < size; ++i)
		a.insert(i);

	EXPECT_EQ(size, a.capacity());
	a.insert(11);
	EXPECT_EQ(size * 2, a.capacity());
}


// Iterator

TEST(IntArrayTest, Iterator)
{
	int size = 5;
	Array<int> a(size);

	for (int i = 0; i < size; ++i)
		a.insert(i);


	int temp = 0;
	for (auto it = a.iterator(); it.hasNext(); it.next()) {
		EXPECT_EQ(it.get(), temp++);
	}
}


// Reverse Iterator

TEST(IntArrayTest, ReverseIterator)
{
	int size = 5;
	Array<int> a(size);

	for (int i = 0; i < size; ++i)
		a.insert(i);

	int temp = size - 1;
	for (auto it = a.reverseIterator(); it.hasNext(); it.next()) {
		EXPECT_EQ(it.get(), temp--);
	}
}


// TESTS FOR string

TEST(StringArrayTest, DefaultConstructor)
{
	Array<std::string> a;
	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.capacity(), 8);
}

TEST(StringArrayTest, ConstructorCapacity)
{
	int capacity = 11;
	Array<std::string> a(capacity);

	ASSERT_EQ(a.size(), 0);
	ASSERT_EQ(a.capacity(), capacity);
}

TEST(StringArrayTest, CopyConstructor)
{
	int capacity = 10;
	int size = 5;
	Array<std::string> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert("A");

	Array<std::string> b(a);

	ASSERT_EQ(a.size(), b.size());
	ASSERT_EQ(a.capacity(), b.capacity());

	for (int i = 0; i < a.size(); ++i)
	{
		EXPECT_EQ(a[i], b[i]);
	}
}

TEST(StringArrayTest, MoveConstructor)
{
	int capacity = 10;
	int size = 5;
	Array<std::string> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert("A");

	Array<std::string> b = std::move(a);

	EXPECT_EQ(size, b.size());
	EXPECT_EQ(capacity, b.capacity());

	for (int i = 0; i < size; ++i) {
		EXPECT_EQ("A", b[i]);
	}
}

TEST(StringArrayTest, CopyFields)
{
	int capacity = 10;
	int size = 5;
	Array<std::string> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert("A");

	Array<std::string> b{};
	b = a;

	EXPECT_EQ(size, b.size());
	EXPECT_EQ(capacity, b.capacity());
	EXPECT_EQ(size, a.size());

	for (int i = 0; i < a.size(); ++i) {
		EXPECT_EQ(b[i], a[i]);
	}
}

TEST(StringArrayTest, MoveFields)
{
	int capacity = 10;
	int size = 5;
	Array<std::string> a(capacity);
	for (int i = 0; i < size; ++i)
		a.insert("A");

	Array<std::string> b{};
	b = std::move(a);

	EXPECT_EQ(size, b.size());
	EXPECT_EQ(capacity, b.capacity());

	for (int i = 0; i < a.size(); ++i) {
		EXPECT_EQ(b[i], "A");
	}
}

TEST(StringArrayTest, Insert)
{
	int size = 30;
	Array<std::string> a(size);

	for (int i = 0; i < size; ++i)
		a.insert("A");

	ASSERT_EQ(a.size(), size);

	std::string value = "B";
	int index = 7;
	a.insert(index, value);

	for (int i = 0; i < index; ++i) {
		EXPECT_EQ("A", a[i]);
	}

	EXPECT_EQ(value, a[index]);

	for (int i = index; i < a.size() - 1; ++i) {
		EXPECT_EQ("A", a[i + 1]);
	}
}

TEST(StringArrayTest, Remove)
{
	int rempove_idx = 4;
	int size = 10;
	Array<std::string> a(size);

	for (int i = 0; i < size; ++i)
		a.insert("A");

	a.remove(rempove_idx);

	for (int i = 0; i < size - 1; ++i) {
		if (i < rempove_idx) {
			EXPECT_EQ("A", a[i]);
		}

		else if (i > rempove_idx) {
			EXPECT_EQ("A", a[i - 1]);
		}
	}
}

TEST(StringArrayTest, CapacityExpand)
{
	int size = 10;
	Array<std::string> a(size);

	for (int i = 0; i < size; ++i)
		a.insert("A");

	EXPECT_EQ(size, a.capacity());
	a.insert("B");
	EXPECT_EQ(size * 2, a.capacity());
}

TEST(StringArrayTest, Iterator)
{
	int size = 5;
	Array<std::string> a(size);

	for (int i = 0; i < size; ++i)
		a.insert("A");



	for (auto it = a.iterator(); it.hasNext(); it.next()) {
		EXPECT_EQ(it.get(), "A");
	}
}

TEST(StringArrayTest, ReverseIterator)
{
	int size = 5;
	Array<std::string> a(size);

	for (int i = 0; i < size; ++i)
		a.insert("A");

	for (auto it = a.reverseIterator(); it.hasNext(); it.next()) {
		EXPECT_EQ(it.get(), "A");
	}
}