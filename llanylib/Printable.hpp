//////////////////////////////////////////////
//	Printable.hpp							//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 8.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_PRINTABLE_HPP_) // Guard && version protector
	#if LLANYLIB_PRINTABLE_MAYOR_ != 8 || LLANYLIB_PRINTABLE_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "Printable.hpp version error!"
		#else
			#error "Printable.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_PRINTABLE_MAYOR_ || LLANYLIB_PRINTABLE_MINOR_

#else !defined(LLANYLIB_PRINTABLE_HPP_)
#define LLANYLIB_PRINTABLE_HPP_
#define LLANYLIB_PRINTABLE_MAYOR_ 0
#define LLANYLIB_PRINTABLE_MINOR_ 1

#include "types.hpp"

namespace llcpp {
namespace string {
class Parser;
class StringBuffer;
} // namespace string
namespace meta {
namespace parser {

class Printable {
	public:
		enum class PrintType {
			BadInited,

			StrPair,
			wStrPair,

			StringBuffer,
			String,
			Parser
		};
	public:
		Printable() noexcept {}
		virtual ~Printable() noexcept {}

		Printable(const Printable&) noexcept = delete;
		Printable& operator=(const Printable&) noexcept = delete;
		Printable(Printable&&) noexcept = delete;
		Printable& operator=(Printable&&) noexcept = delete;

		__LL_NODISCARD__ operator const Printable*() const noexcept { return this; }
		__LL_NODISCARD__ operator Printable*() noexcept { return this; }

		__LL_NODISCARD__ virtual PrintType getType() const noexcept = 0;

		__LL_NODISCARD__ virtual meta::StrPair getStrPair() const noexcept = 0;
		__LL_NODISCARD__ virtual meta::wStrPair getwStrPair() const noexcept = 0;
		__LL_NODISCARD__ virtual meta::Str getStr() const noexcept = 0;
		__LL_NODISCARD__ virtual meta::wStr getwStr() const noexcept = 0;

		virtual void useStringBuffer(const llcpp::string::StringBuffer& buffer) const noexcept = 0;
		virtual void useParser(llcpp::string::Parser* parser) const noexcept = 0;
		virtual void useParser(void* parser) const noexcept = 0;
};

} // namespace parser
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_PRINTABLE_HPP_
