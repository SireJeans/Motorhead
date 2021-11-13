#pragma once

template <typename T, typename ArrType>
struct IsArrayOrRefOfType
{
	enum { value = false };
};

template <typename ArrType> 
struct IsArrayOrRefOfType<ArrType[], ArrType> { enum { value = true }; };
template <typename ArrType> 
struct IsArrayOrRefOfType<const ArrType[], ArrType> { enum { value = true }; };
template <typename ArrType>
struct IsArrayOrRefOfType<volatile ArrType[], ArrType> { enum { value = true }; };
template <typename ArrType>
 struct IsArrayOrRefOfType<const volatile ArrType[], ArrType> { enum { value = true }; };

template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<ArrType[N], ArrType> { enum { value = true }; };
template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<const ArrType[N], ArrType> { enum { value = true }; };
template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<volatile ArrType[N], ArrType> { enum { value = true }; };
template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<const volatile ArrType[N], ArrType> { enum { value = true }; };

template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<ArrType(&)[N], ArrType> { enum { value = true }; };
template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<const ArrType(&)[N], ArrType> { enum { value = true }; };
template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<volatile ArrType(&)[N], ArrType> { enum { value = true }; };
template <typename ArrType, unsigned int N>
 struct IsArrayOrRefOfType<const volatile ArrType(&)[N], ArrType> { enum { value = true }; };
