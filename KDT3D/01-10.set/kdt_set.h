#pragma once
#include <iostream>
#include <functional>
namespace kdt
{
	template<typename _Ty>
	class set;

	template<typename _Ty>
	struct FBSTNode;

	template<typename _Ty>
	class _Set_iterator
	{
		template<typename _Ty>
		friend class set;

	public:
		_Set_iterator() = default;
		_Set_iterator(set<_Ty>* InSet, FBSTNode<_Ty>* InNode)
			: Set(InSet)
			, Node(InNode) {}

		_Set_iterator(const _Set_iterator&) = default;
		_Set_iterator& operator=(const _Set_iterator&) = default;

		_Set_iterator& operator++()
		{
			Node = Set->BST_Successor(Node);
			return *this;
		}

		_Set_iterator& operator--()
		{
			Node = Set->BST_Predecessor(Node);
			return *this;
		}

		_NODISCARD _Ty& operator*() const noexcept
		{
			_ASSERT(Node);
			return Node->Key;
		}

		_NODISCARD _Ty& operator->() const noexcept
		{
			_ASSERT(Node);
			return Node->Key;
		}

		bool operator==(const _Set_iterator& InOther) const
		{
			if (Set == InOther.Set && Node == InOther.Node)
			{
				return true;
			}
			return false;
		}
		bool operator!=(const _Set_iterator& InOther) const
		{
			return !(*this == InOther);
		}

	private:
		set<_Ty>* Set = nullptr;
		FBSTNode<_Ty>* Node = nullptr;
	};

	//template<typename _Ty1, typename _Ty2>
	//struct FPair
	//{
	//	_Ty1 first;
	//	_Ty2 second;
	//};

	enum class ENodeType
	{
		Parent,
		Left, // Left Child
		Right, // Right Child
		End,
	};

	// template<typename _Ty1, typename _Ty2> // 만약에 map이였다면
	template<typename _Ty>
	// BST: Binary Search Tree(이진 탐색 트리)
	struct FBSTNode
	{
		//FPair Pair;
		_Ty Key{};

		FBSTNode* Parent = nullptr;
		FBSTNode* Left = nullptr;
		FBSTNode* Right = nullptr;

		FBSTNode* Nodes[(int)ENodeType::End] = {};
		
		FBSTNode() = default;
		FBSTNode(const _Ty& InKey, FBSTNode* InParent,
			FBSTNode* InLeft, FBSTNode* InRight) 
			: Key(InKey)
			, Parent(InParent)
			, Left(InLeft)
			, Right(InRight) {}
	};

	// 일단 int만 가정해서 처리
	template<typename _Ty>
	class set
	{
	public:
		using iterator = _Set_iterator<_Ty>;
		using Node = FBSTNode<_Ty>;

		set() = default;
		set(const set& InOther);
		set(set&& InOther) noexcept;
		~set();


		iterator insert(const _Ty& InValue);
		_NODISCARD iterator find(const _Ty& InValue);
		iterator erase(const iterator& It);

		_NODISCARD iterator begin();
		_NODISCARD iterator end();

		void print_Inorder();

	protected:
		// https://en.wikipedia.org/wiki/Binary_search_tree#cite_note-algo_cormen-10
		void BST_Insert(Node* z);
		Node* BST_Erase(Node* z);

		void ChangeParent(Node* u, Node* v);


		Node* Iterative_Tree_Search(Node* x, const _Ty& key);

		// 후임자 찾기
		Node* BST_Successor(Node* x);
		Node* BST_Minimum(Node* x);
		// 전임자 찾기
		Node* BST_Predecessor(Node* x);
		Node* BST_Maximum(Node* x);

		// ---------------------------------Traversal--------------------------------------
		// 순서대로 출력할 때 사용
		void Inorder_Tree_Walk(Node* x, std::function<void(Node*)> Function);

		// Tree를 복제할 때 사용 (부모-> 자식으로 향함)
		void Preorder_Tree_Walk(Node* x, std::function<void(Node*)> Function);
		
		// Tree를 delete 할 때 사용 (자식 -> 부모로 향함)
		void Postorder_Tree_Walk(Node* x, std::function<void(Node*)> Function);
		// ---------------------------------Traversal end----------------------------------

	private:
		FBSTNode<_Ty>* Root = nullptr;
		size_t Count = 0;
	};
}

#include "kdt_set.hpp"