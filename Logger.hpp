#include <iostream>
#include <string>
#include <type_traits>

namespace utils
{
	
template<bool call_to_string>
struct LogItem;

template<>
struct LogItem<false>
{
	template<class T>
	static void join(std::string& s, T const& t)
	{
		s.append(t);
	}
	
	template<std::size_t N>
	static void join(std::string& s, char (&arr)[N])
	{
		s.append(arr, N);
	}
};

template<>
struct LogItem<true>
{
	template<class T>
	static void join(std::string& s, T t)
	{
		s+=std::to_string(t);
	}
};

template<class... Args>
void Log(Args... args)
{
	std::string s;
	(LogItem<std::is_integral_v<Args>>::join(s, args), ...);
	s+='\n';
	std::cout<<s;
}

}