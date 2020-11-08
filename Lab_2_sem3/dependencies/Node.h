#pragma once

namespace sequences {

	template<class T> class Node {

	private:
		T content;
		Node<T>* next;
	public:
		Node(T newContent, Node* newNext) :
			content(newContent), next(newNext)
		{
		}
		Node(Node& node) :
			Node(node.content, node.next)
		{
		}
	public:
		T& GetContent()
		{
			return content;
		}
		Node<T>* Next() {
			return next;
		}
	public:
		void SetContent(T newContent) {
			content = newContent;
		}
		void SetNext(Node* newNext) {
			next = newNext;
		}
	public:
		~Node() {
			delete(next);
		}
	};
}
