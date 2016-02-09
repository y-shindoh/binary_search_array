/* -*- coding: utf-8; tab-width: 4 -*- */
/**
 * @file	binary_search_array.hpp
 * @brief	配列で表現した平衡二分探索木 (binary search array)
 * @author	Yasutaka SHINDOH / 新堂 安孝
 */

#ifndef	__BINARY_SEARCH_ARRAY_HPP__
#define	__BINARY_SEARCH_ARRAY_HPP__	"binary_search_array.hpp"

#include <cstddef>
#include <cassert>
#include <vector>

namespace ys
{
	/**
	 * @class	配列で表現した平衡二分探索木 (binary search array)
	 * @note	親子へのポインタを持たず、インデックスの計算で代替する。
	 * @note	テンプレートの型 @a TYPE は木が保持するポインタが指す型。
	 * @note	ソート済み配列に対する二分探索より、
				配列で表現した平衡二分探索木の方が高速に探索できる。
				(see http://cglab.ca/~morin/misc/arraylayout/ )
	 */
	template<typename TYPE>
	class BinarySearchArray
	{
	private:

		std::vector<TYPE> tree_;	///< 二分探索木 (1始まり)
		const TYPE invalid_;		///< 不正値 (ターミネータ)

		/**
		 * 探索に用いる比較関数
		 * @note	2つの引数が等しい時は0を、
					第1引数が大きい場合は負の数を、そうでない場合は正の数を返す。
		 */
		int (* compare_)(const TYPE&, const TYPE&);

		/**
		 * メソッド @a prepare の本体
		 * @param[in]	input	処理対象の降順ソート済み配列
		 * @param[in]	i	ポインタを格納する二分探索木のインデックス
		 * @param[in]	s	引数 @a input の処理対象の始点
		 * @param[in]	e	引数 @a input の処理対象の終点
		 */
		void
		recursive_prepare(const TYPE* input,
						  size_t i,
						  size_t s,
						  size_t e)
			{
				size_t c = (s + e) / 2;
				tree_[i] = input[c];
				if (s < c) recursive_prepare(input, i * 2, s, c - 1);
				if (c < e) recursive_prepare(input, i * 2 + 1, c + 1, e);
			}

	public:

		/**
		 * コンストラクタ
		 * @param[in]	invalid	型 @a TYPE の不正値 (ターミネータ)
		 * @param[in]	compare	比較関数
		 */
		BinarySearchArray(const TYPE& invalid,
						  int (* compare)(const TYPE&, const TYPE&))
			: invalid_(invalid), compare_(compare)
			{
				;
			}

		/**
		 * 昇順ソート済み配列から平衡二分探索木を構築
		 * @param[in]	input	処理対象の昇順ソート済み配列 (重複はないものとする)
		 * @param[in]	length	引数 @a input の長さ
		 * @note	計算量はO(n)。ただしnは引数 @a length に準じる。
		 */
		void
		prepare(const TYPE* input,
				size_t length)
			{
				assert(input);
				assert(length);

				size_t l(1);
				while (l <= length) l *= 2;
				tree_.clear();
				tree_.resize(l, invalid_);

				recursive_prepare(input, 1, 0, length - 1);
			}

		/**
		 * 探索
		 * @param[in]	data	探索対象のデータを指すポインタ
		 * @return	引数 @a data にヒットした二部探索木の要素のインデックス
		 * @note	ヒットしなかった場合は @a 0 が返却される。
		 * @note	最悪計算量はO(log n)。ただしnは @a tree_ の要素数。
		 */
		size_t
		search(const TYPE& data) const
			{
				assert(compare_);

				size_t i(1);
				const size_t l = tree_.size();
				int v;

				while (i < l && tree_[i] != invalid_) {
					v = compare_(data, tree_[i]);
					if (v < 0) i = i * 2;
					else if (0 < v) i = i * 2 + 1;
					else return i;
				}

				return 0;
			}

		/**
		 * 二分探索木の配列の要素を取得
		 * @param[in]	i	要素のインデックス (1始まり)
		 * @return	配列の要素
		 */
		TYPE
		get(size_t i) const
			{
				assert(0 < i);
				assert(i < tree_.size());

				return tree_[i];
			}

		/**
		 * 二分探索木の配列の長さを取得
		 * @return	配列の長さ
		 */
		size_t
		size() const
			{
				return tree_.size();
			}
	};
};

#endif	// __BINARY_SEARCH_ARRAY_HPP__
