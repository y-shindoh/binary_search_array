/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	main.cpp
 * @brief	binary_search_array.hppの動作確認コマンド
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#include <cstddef>
#include <cstdio>
#include <climits>
#include "binary_search_array.hpp"

/**
 * 比較関数
 */
int
compare(const int& left,
		const int& right)
{
	if (left < right) {
		return -1;
	}
	else if (left > right) {
		return 1;
	}
	else {
		return 0;
	}
}

/**
 * 二分探索木を標準出力に表示
 */
void
print(ys::BinarySearchArray<int>* tree,
	  int invalid)
{
	const size_t l = tree->size();
	int v;

	for (size_t i(0); i < l; ++i) {
		if (1 < i) std::printf(", ");
		v = tree->get(i);
		if (invalid != v) std::printf("[%lu] %d", i, v);
		else std::printf("[%lu] -", i);
	}
	std::printf("\n");
}

/**
 * binary_search_array.hppの動作確認コマンド
 */
int main()
{
	const int data_1[] = {0, 1, 2, 3, 4, 5, 6};
	const int data_2[] = {7, 8, 9, 10, 11, 12, 13, 14, 15};
	const int key(5);
	size_t flag;

	ys::BinarySearchArray<int>* tree = new ys::BinarySearchArray<int>(INT_MIN, compare);

	tree->prepare(data_1, sizeof(data_1)/sizeof(data_1[0]));
	print(tree, INT_MIN);
	flag = tree->search(key);
	std::printf("%d => %s\n", key, flag ? "found" : "not found");

	tree->prepare(data_2, sizeof(data_2)/sizeof(data_2[0]));
	print(tree, INT_MIN);
	flag = tree->search(key);
	std::printf("%d => %s\n", key, flag ? "found" : "not found");

	delete tree;

	return 0;
}
