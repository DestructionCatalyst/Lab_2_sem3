#pragma once

namespace sequences
{
	namespace iterators
	{
		template<class T> class SequenceIterator {

		public:
			SequenceIterator()
			{}
		public:
			virtual SequenceIterator<T>& operator++ () = 0;
			virtual T operator* () const = 0;
			virtual bool operator== (const SequenceIterator<T>& o) const = 0;
			virtual bool operator!= (const SequenceIterator<T>& o) const = 0;

		};
	}
}