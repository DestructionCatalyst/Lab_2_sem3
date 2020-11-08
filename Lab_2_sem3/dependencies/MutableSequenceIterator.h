#pragma once

namespace sequences
{
	namespace iterators
	{
		template<class T> class MutableSequenceIterator {

		public:
			MutableSequenceIterator()
			{}
		public:
			virtual void SetContent(T content) = 0;

		};
	}
}