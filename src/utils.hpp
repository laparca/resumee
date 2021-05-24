#ifndef RESUMEE_UTILS_HPP
#define RESUMEE_UTILS_HPP
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
#include <sstream>

template<typename InputIterator, typename OutputIterator>
OutputIterator intersperse(InputIterator first1, InputIterator last1, OutputIterator first2, typename std::iterator_traits<InputIterator>::value_type const& value)
{
    if (first1 != last1)
    {
        *first2++ = *first1++;

        InputIterator in_it = first1;
        OutputIterator out_it = first2;

        while(in_it != last1)
        {
            *out_it++ = value;
            *out_it++ = *in_it++;
        }
    }

    return first2;
}

//template<typename Container, typename OutputContainer>
//OutputContainer intersperse(Container const& c, typename Container::value_type const& value)
template<template<typename...>typename OutputContainer, typename Container>
OutputContainer<typename Container::value_type> intersperse(Container const& c, typename Container::value_type const& value)
{
    OutputContainer<typename Container::value_type> out;
    intersperse(std::begin(c), std::end(c), std::back_inserter(out), value);
    return out;
}

template<typename Container>
typename Container::value_type plain(Container&& cont)
{
    using value_type = typename Container::value_type;
    if (cont.size() == 0)
    {
        return value_type{};
    }

    return std::accumulate(std::begin(cont)+1, std::end(cont), *std::begin(cont));
}

template<typename Container>
std::string to_html_ul(Container const& c, std::string const& ul_extra = {}, std::string const& li_extra = {})
{
    std::stringstream stream{};

    if (c.size())
    {
        stream << "<ul " << ul_extra << ">";
        for (const auto& v : c)
            stream << "<li " << li_extra << ">" << v << "</li>";
        stream << "</ul>";

    }

    return stream.str();
}
#endif
