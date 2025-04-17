#pragma once

#include <cstdint>
#include <stdlib.h>

#include "Log.h"
#include "Stat.h"

#ifdef _WIN32
# define NOMINMAX
# include <WinSock2.h>
# pragma comment(lib, "Ws2_32.lib")
#else
# include <arpa/inet.h>
#endif

#ifdef _WIN32
#define PROTO_ALIGN_BEGIN __pragma(pack(push, 1))
#define PROTO_ALIGN_END   __pragma(pack(pop))
#else
#define PROTO_ALIGN_BEGIN _Pragma("pack(push, 1)")
#define PROTO_ALIGN_END   _Pragma("pack(pop)")
#endif

inline uint16_t R16(uint16_t v)
{
	return htons(v);
}

inline uint32_t R32(uint32_t v)
{
	return htonl(v);
}

inline uint64_t R64(uint64_t v)
{
#ifdef _WIN32
	return htonll(v);
#else
	return htobe64(v);
#endif
}

typedef uint8_t PRN;