#ifndef CPP_FLAGS_CPPFLAGS_HPP
#define CPP_FLAGS_CPPFLAGS_HPP

#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <type_traits>

namespace cppflags {

class Flag32
{
public:
    constexpr inline Flag32(int32_t value) noexcept : m_i(value) {}
    constexpr inline Flag32(uint32_t value) noexcept : m_i(value) {}
    constexpr inline Flag32(int8_t value) noexcept : m_i(static_cast<int32_t>(value)) {}
    constexpr inline Flag32(uint8_t  value) noexcept : m_i(static_cast<int32_t>(static_cast<uint32_t>(value))) {}
    constexpr inline Flag32(int16_t value) noexcept : m_i(static_cast<int32_t>(value)) {}
    constexpr inline Flag32(uint16_t  value) noexcept : m_i(static_cast<int32_t>(static_cast<uint32_t>(value))) {}

    constexpr inline operator int32_t() const noexcept { return m_i; }
    constexpr inline operator uint32_t() const noexcept { return static_cast<uint32_t>(m_i); }

private:
    int32_t m_i;
};

class Flag64
{
public:
    constexpr inline Flag64(int64_t value) noexcept : m_i(value) {}
    constexpr inline Flag64(uint64_t value) noexcept : m_i(value) {}
    constexpr inline Flag64(int8_t value) noexcept : m_i(static_cast<int64_t>(value)) {}
    constexpr inline Flag64(uint8_t  value) noexcept : m_i(static_cast<int64_t>(static_cast<uint64_t>(value))) {}
    constexpr inline Flag64(int16_t value) noexcept : m_i(static_cast<int64_t>(value)) {}
    constexpr inline Flag64(uint16_t  value) noexcept : m_i(static_cast<int64_t>(static_cast<uint64_t>(value))) {}
    constexpr inline Flag64(int32_t value) noexcept : m_i(static_cast<int64_t>(value)) {}
    constexpr inline Flag64(uint32_t value) noexcept : m_i(static_cast<int64_t>(static_cast<uint64_t>(value))) {}

    constexpr inline operator int64_t() const noexcept { return m_i; }
    constexpr inline operator uint64_t() const noexcept { return static_cast<uint64_t>(m_i); }

private:
    int64_t m_i;
};

template<typename Enum>
class Flags
{
    static_assert((std::is_enum<Enum>::value), "Flags is only usable on enumeration types.");

    using Underlying = std::underlying_type_t<Enum>;

public:
    using Int = std::conditional_t<
        (sizeof(Underlying) == 8),
        std::conditional_t<std::is_unsigned_v<Underlying>, uint64_t, int64_t>,
        std::conditional_t<std::is_unsigned_v<Underlying>, uint32_t, int32_t>
    >;
    using SInt = std::make_signed_t<Int>;
    using UInt = std::make_unsigned_t<Int>;
    using Flag = std::conditional_t<
        (sizeof(Int) == 8),
        Flag64,
        Flag32
    >;
    using EnumType = Enum;

public:
    constexpr inline Flags() noexcept : m_i(0) {}
    constexpr inline Flags(Enum flags) noexcept : m_i(static_cast<Int>(flags)) {}
    constexpr inline Flags(Flag flag) noexcept : m_i() {}

    constexpr inline Flags(std::initializer_list<Enum> flags) noexcept
        : m_i(initializerListHelper(flags.begin(), flags.end())) {
    }

    constexpr static inline Flags fromInt(Int i) noexcept { return Flags(Flag(i)); }
    constexpr inline Int toInt() const noexcept { return m_i; }

    constexpr inline Flags &operator&=(SInt mask) noexcept { m_i &= mask; return *this; }
    constexpr inline Flags &operator&=(UInt mask) noexcept { m_i &= mask; return *this; }
    constexpr inline Flags &operator&=(Flags mask) noexcept { m_i &= mask.m_i; return *this; }
    constexpr inline Flags &operator&=(Enum mask) noexcept { m_i &= static_cast<Int>(mask); return *this; }
    constexpr inline Flags &operator|=(Flags other) noexcept { m_i |= other.m_i; return *this; }
    constexpr inline Flags &operator|=(Enum other) noexcept { m_i |= static_cast<Int>(other); return *this; }
    constexpr inline Flags &operator^=(Flags other) noexcept { m_i ^= other.m_i; return *this; }
    constexpr inline Flags &operator^=(Enum other) noexcept { m_i ^= static_cast<Int>(other); return *this; }

    constexpr inline operator Int() const noexcept { return m_i; }
    constexpr inline bool operator!() const noexcept { return !m_i; }

    constexpr inline Flags operator|(Flags other) const noexcept
    { return Flags(Flag(m_i | other.m_i)); }
    constexpr inline Flags operator|(Enum other) const noexcept
    { return Flags(Flag(m_i | static_cast<Int>(other))); }
    constexpr inline Flags operator^(Flags other) const noexcept
    { return Flags(Flag(m_i ^ other.m_i)); }
    constexpr inline Flags operator^(Enum other) const noexcept
    { return Flags(Flag(m_i ^ static_cast<Int>(other))); }
    constexpr inline Flags operator&(SInt mask) const noexcept
    { return Flags(Flag(m_i & mask)); }
    constexpr inline Flags operator&(UInt mask) const noexcept
    { return Flags(Flag(m_i & mask)); }
    constexpr inline Flags operator&(Flags other) const noexcept
    { return Flags(Flag(m_i & other.m_i)); }
    constexpr inline Flags operator&(Enum other) const noexcept
    { return Flags(Flag(m_i & static_cast<Int>(other))); }
    constexpr inline Flags operator~() const noexcept
    { return Flags(Flag(~m_i)); }

    constexpr inline void operator+(Flags other) const noexcept = delete;
    constexpr inline void operator+(Enum other) const noexcept = delete;
    constexpr inline void operator+(int other) const noexcept = delete;
    constexpr inline void operator-(Flags other) const noexcept = delete;
    constexpr inline void operator-(Enum other) const noexcept = delete;
    constexpr inline void operator-(int other) const noexcept = delete;

    friend constexpr inline bool operator==(Flags lhs, Flags rhs) noexcept
    { return lhs.i == rhs.i; }
    friend constexpr inline bool operator!=(Flags lhs, Flags rhs) noexcept
    { return lhs.i != rhs.i; }
    friend constexpr inline bool operator==(Flags lhs, Enum rhs) noexcept
    { return lhs == Flags(rhs); }
    friend constexpr inline bool operator!=(Flags lhs, Enum rhs) noexcept
    { return lhs != Flags(rhs); }
    friend constexpr inline bool operator==(Enum lhs, Flags rhs) noexcept
    { return Flags(lhs) == rhs; }
    friend constexpr inline bool operator!=(Enum lhs, Flags rhs) noexcept
    { return Flags(lhs) != rhs; }

    constexpr inline bool testFlag(Enum flag) const noexcept
    { return testFlags(flag); }
    constexpr inline bool testFlags(Flags flags) const noexcept
    { return flags.m_i ? ((m_i & flags.m_i) == flags.m_i) : m_i == static_cast<Int>(0); }
    constexpr inline bool testAnyFlag(Enum flag) const noexcept
    { return testAnyFlags(flag); }
    constexpr inline bool testAnyFlags(Flags flags) const noexcept
    { return (m_i & flags.m_i) != static_cast<Int>(0); }
    constexpr inline Flags &setFlag(Enum flag, bool on = true) noexcept
    { return on ? (*this |= flag) : (*this &= ~Flags(flag)); }

private:
    constexpr static inline Int initializerListHelper(typename std::initializer_list<Enum>::const_iterator it,
                                                      typename std::initializer_list<Enum>::const_iterator end)
        noexcept
    {
        return (it == end ? static_cast<Int>(0) 
                          : (static_cast<Int>(*it) | initializerListHelper(it + 1, end)));
    }

private:
    Int m_i;
};

#define CPPFLAGS_DECLARE_FLAGS(EnumFlags, Enum) \
typedef EnumsFlags Flags<Enum>;

} // namespace cppflags

#endif // CPP_FLAGS_CPPFLAGS_HPP
