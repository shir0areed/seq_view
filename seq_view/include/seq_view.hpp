#include <utility>

namespace SeqView
{
	// Describes an object which can refer to a sequence
	// to which elements can be accessed with operator [].
	// Unlike std::span, data contiguity is not required.
	template<typename TValue>
	class seq_view
	{
	public:
		seq_view(const seq_view&) noexcept = default;

		template<typename U>
		seq_view(U&& data, std::size_t size) noexcept
			: pData{ const_cast<typename std::decay<U>::type*>(&data) }, pSubscript{ &Subscript<U> }, numElems{ size }
		{
			static_assert(!std::is_pointer<typename std::decay<decltype(data)>::type>::value, "pData may not be pointer of pointer");
		}

		template<typename U>
		seq_view(U* pData, std::size_t size) noexcept
			: pData{ const_cast<typename std::remove_const<U>::type*>(pData) }, pSubscript{ &SubscriptPtr<U> }, numElems{ size }
		{
		}

		// enable_if prevents the copy constructor from being hidden
		template<typename U, typename = typename std::enable_if<!std::is_base_of<seq_view, typename std::decay<U>::type>::value>::type>
		seq_view(U&& data) noexcept
			: seq_view(std::forward<U>(data), GetSize(data))
		{
		}

		// You cannot pass std::initializer_list because this object does not own the data.
		// The std::vector below gets expired when construction is completed.
		// If you want to pass immediate values to a function which takes a container_ref,
		// wrap with a container such as std::vector (it lives until the function call finishes).
		//container_ref(std::initializer_list<TValue> container)
		//    : container_ref(std::vector(container))
		//{
		//}

		TValue operator [](std::size_t i) const
		{
			return (*pSubscript)(pData, i);
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
			TValue operator * () const { return outer[i]; }

		private:
			const seq_view& outer;
			std::size_t i;
		};

		iterator begin() const noexcept { return iterator{ *this, 0 }; }
		iterator end() const noexcept { return iterator{ *this, numElems }; }

		std::size_t size() const noexcept { return numElems; }

	private:
		// can be replaced by std::size for C++17 or later
		template<typename T>
		std::size_t GetSize(const T& v)
		{
			return v.size();
		}

		template<typename T, std::size_t size>
		std::size_t GetSize(const T(&v)[size])
		{
			return size;
		}

		template<typename U>
		static TValue Subscript(void* pList, std::size_t i)
			noexcept(noexcept((*static_cast<typename std::remove_reference<U>::type*>(pList))[i]))
		{
			return (*static_cast<typename std::remove_reference<U>::type*>(pList))[i];
		}

		template<typename U>
		static TValue SubscriptPtr(void* pList, std::size_t i) noexcept
		{
			return static_cast<U*>(pList)[i];
		}

		void* const pData;
		TValue(* const pSubscript)(void* pData, std::size_t i);
		const std::size_t numElems;
	};
}
