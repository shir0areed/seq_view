#include <seq_view.hpp>

#include <iostream>

using namespace SeqView;

namespace
{
	void Print(const seq_view<int>& seq)
	{
		for (auto x : seq)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	void PrintV(seq_view<int> seq)
	{
		for (auto x : seq)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	void PrintPtr(const seq_view<const int*>& seq)
	{
		for (auto x : seq)
			std::cout << *x << " ";
		std::cout << std::endl;
	}

	void PrintR(const seq_view<int&>& seq)
	{
		for (auto& x : seq)
			++x;
		for (auto& x : seq)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	void PrintStr(const seq_view<std::string>& seq)
	{
		for (auto x : seq)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	template<typename TElems, typename TSelector>
	class CSelect
	{
		const TElems& elems;
		const TSelector& selector;
	public:
		explicit CSelect(const TElems& elems, const TSelector& selector)
			: elems{ elems }, selector{ selector }
		{

		}

		auto operator [] (std::size_t i) const
			-> decltype(selector(elems[i]))
		{
			return selector(elems[i]);
		}

		std::size_t size() const { return elems.size(); }
	};
}

#include <vector>
#include <array>
#include <unordered_map>

int main()
{
	Print(seq_view<int>{std::vector<int>{5, 2, 3, 1, 4}});
	PrintV(seq_view<int>{std::vector<int>{5, 2, 3, 1, 4}});
	auto selector = [](int x) {return x * 2; };
	Print(seq_view<int>{CSelect<std::vector<int>, decltype(selector)>{ std::vector<int>{5, 2, 3, 1, 4}, selector }});
	Print(seq_view<int>{std::array<int, 5>{4, 3, 5, 2, 1}});
	Print(seq_view<int>{std::unordered_map<int, int>
	{
		{ 0, 3 },
		{ 1, 1 },
		{ 2, 2 },
		{ 3, 4 },
		{ 4, 5 },
	}});
	int ar[] = { 3, 4, 2, 5, 1 };
	Print(ar);
	seq_view<int> l1{ &ar[0], sizeof(ar) / sizeof(int) };
	Print(l1);
	seq_view<int>l2{ ar };
	Print(l2);
	const int* ar2[] = { &ar[0], &ar[3], &ar[2], &ar[1], &ar[4] };
	PrintPtr(ar2);
	seq_view<const int*>l3{ &ar2[0], sizeof(ar2) / sizeof(int*) };
	PrintPtr(l3);
	seq_view<const int*>l4{ ar2 };
	PrintPtr(l4);
	PrintR(ar);
	PrintStr(std::vector<std::string>{ "foo", "bar", "buzz" });
}
