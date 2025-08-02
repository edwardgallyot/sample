#pragma once

#include <cstdint>
#include <cstddef>

namespace types {

// Integer types
using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

// Floating point types
using f32 = float;
using f64 = double;

// Character types
using char8 = unsigned char;
using char16 = char16_t;
using char32 = char32_t;

} // namespace types

// Global using declarations for convenience
using namespace types; 