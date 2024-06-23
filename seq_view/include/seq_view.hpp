#include <utility>

namespace SeqView
{
	// Describes an object which can refer to a sequence
	// to which elements can be accessed with operator [].
	// Unlike std::span, data contiguity is not required.
	// For example, it accepts:
	//   - std::vector
	//   - std::array
	//   - user-defined class with operator[] and size()
	//   - C-style array
	//   - pointer to the first element and the number of elements
	template<typename T>
	class seq_view
	{
	public:
		seq_view(const seq_view&) noexcept = default;

		template<typename U>
		seq_view(U&& elems, std::size_t numElems) noexcept
			: pElems{ const_cast<typename std::decay<U>::type*>(&elems) }, pSubscript{ &Subscript<U> }, numElems{ numElems }
		{
			static_assert(!std::is_pointer<typename std::decay<decltype(elems)>::type>::value, "pElems may not be a pointer of pointer");
		}

		template<typename U>
		seq_view(U* pElems, std::size_t numElems) noexcept
			: pElems{ const_cast<typename std::remove_const<U>::type*>(pElems) }, pSubscript{ &SubscriptPtr<U> }, numElems{ numElems }
		{
		}

		// enable_if prevents the copy constructor from being hidden
		template<typename U, typename = typename std::enable_if<!std::is_base_of<seq_view, typename std::decay<U>::type>::value>::type>
		seq_view(U&& elems) noexcept
			: seq_view(std::forward<U>(elems), GetNumElems(elems))
		{
		}

		// You cannot pass std::initializer_list because this object does not own the data.
		// The std::vector below gets expired when construction is completed.
		// If you want to pass immediate values to a function which takes a seq_view,
		// wrap with a container such as std::vector (it lives until the function call finishes).
		//seq_view(std::initializer_list<T> elems)
		//    : seq_view(std::vector<T>(elems))
		//{
		//}

		T operator [](std::size_t i) const
		{
			return (*pSubscript)(pElems, i);
		}

		class iterator
		{
		public:
			explicit iterator(const seq_view& outer, std::size_t i) noexcept
				: outer{ outer }, i{ i }
			{
			}

			bool operator != (const iterator& a) const noexcept { return i != a.i; }
			iterator& operator ++ () noexcept { ++i; return *this; }
			T operator * () const { return outer[i]; }

		private:
			const seq_view& outer;
			std::size_t i;
		};

		iterator begin() const noexcept { return iterator{ *this, 0 }; }
		iterator end() const noexcept { return iterator{ *this, numElems }; }

		std::size_t size() const noexcept { return numElems; }

	private:
		// can be replaced by std::size for C++17 or later
		template<typename U>
		static std::size_t GetNumElems(const U& elems)
			noexcept(noexcept(elems.size()))
		{
			return elems.size();
		}

		template<typename U, std::size_t NumElems>
		static std::size_t GetNumElems(const U(&)[NumElems]) noexcept
		{
			return NumElems;
		}

		template<typename U>
		static T Subscript(void* pElems, std::size_t i)
			noexcept(noexcept((*static_cast<typename std::remove_reference<U>::type*>(pElems))[i]))
		{
			return (*static_cast<typename std::remove_reference<U>::type*>(pElems))[i];
		}

		template<typename U>
		static T SubscriptPtr(void* elems, std::size_t i) noexcept
		{
			return static_cast<U*>(elems)[i];
		}

		void* const pElems;
		T(* const pSubscript)(void* pElems, std::size_t i);
		const std::size_t numElems;
	};
}
