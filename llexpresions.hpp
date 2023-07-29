/*
 * llexpresions.hpp
 *
 *  Created on: Jun 25, 2023
 *      Author: llanyro
 */

#ifndef LLPC_HEADER_LLEXPRESIONS_HPP_
#define LLPC_HEADER_LLEXPRESIONS_HPP_

#include "llanytypeslib.hpp"

namespace llcpp {
namespace header {
namespace expresions {
namespace bytes {

constexpr b64 bToKb = 1e-3;
constexpr b64 bToMb = 1e-6;
constexpr b64 bToGb = 1e-9;

constexpr b64 KbToB = 1e3;
constexpr b64 MbToB = 1e6;
constexpr b64 GbToB = 1e9;

} /* namespace bytes */
namespace buffers {

constexpr b64 WRITER_BUFFER_LEN = 256;
constexpr b64 VECTOR_BUFFER_LEN = 300;
constexpr b64 BUFFER_LEN = 300;
constexpr b64 VECTORLIST_BUFFER_INCREMENT_LEN = 128;
constexpr b64 ARRAY_DEFAULT_BUFFER_LEN = 300;
constexpr ui8 JEAII_ALGORITHM_BUFFER_SIZE = 10;

} /* namespace buffers */
namespace ascii {
constexpr ui8 MAYUS_MINUS_DIFF = 'a' - 'A';

} /* namespace ascii */
namespace list {
constexpr len_t npos = 0xffffffffffffffff;

} /* namespace list */
namespace strings {

constexpr ll_string_t NULL_VALUE_STR = "Value cannot be nullptr";
constexpr ll_string_t ZERO_BYTES_VALUE_STR = "Number of bytes provided cannot be 0";
constexpr StrPair nullpair = { "Nullstring", 11 };

} /* namespace strings */
namespace color {

// Text colors
constexpr ll_string_t RESET = "\033[0m";
constexpr ll_string_t BLACK = "\033[30m";
constexpr ll_string_t RED = "\033[31m";
constexpr ll_string_t GREEN = "\033[32m";
constexpr ll_string_t YELLOW = "\033[33m";
constexpr ll_string_t BLUE = "\033[34m";
constexpr ll_string_t MAGENTA = "\033[35m";
constexpr ll_string_t CYAN = "\033[36m";
constexpr ll_string_t WHITE = "\033[37m";

// Background colors
constexpr ll_string_t BG_RESET = "\033[49m";
constexpr ll_string_t BG_BLACK = "\033[40m";
constexpr ll_string_t BG_RED = "\033[41m";
constexpr ll_string_t BG_GREEN = "\033[42m";
constexpr ll_string_t BG_YELLOW = "\033[43m";
constexpr ll_string_t BG_BLUE = "\033[44m";
constexpr ll_string_t BG_MAGENTA = "\033[45m";
constexpr ll_string_t BG_CYAN = "\033[46m";
constexpr ll_string_t BG_WHITE = "\033[47m";

namespace pair {

constexpr StrPair RESET = { color::RESET, 4 };
constexpr StrPair BLACK = { color::BLACK, 5 };
constexpr StrPair RED = { color::RED, 5 };
constexpr StrPair GREEN = { color::GREEN, 5 };
constexpr StrPair YELLOW = { color::YELLOW, 5 };
constexpr StrPair BLUE = { color::BLUE, 5 };
constexpr StrPair MAGENTA = { color::MAGENTA, 5 };
constexpr StrPair CYAN = { color::CYAN, 5};
constexpr StrPair WHITE = { color::WHITE, 5 };

constexpr StrPair BG_RESET = { color::BG_RESET, 5 };
constexpr StrPair BG_BLACK = { color::BG_BLACK, 5 };
constexpr StrPair BG_RED = { color::BG_RED, 5 };
constexpr StrPair BG_GREEN = { color::BG_GREEN, 5 };
constexpr StrPair BG_YELLOW = { color::BG_YELLOW, 5 };
constexpr StrPair BG_BLUE = { color::BG_BLUE, 5 };
constexpr StrPair BG_MAGENTA = { color::BG_MAGENTA, 5 };
constexpr StrPair BG_CYAN = { color::BG_CYAN, 5 };
constexpr StrPair BG_WHITE = { color::BG_WHITE, 5 };

} /* namespace pair */
} /* namespace color */
namespace traits {
constexpr ll_string_t INVALID_LAMBDA_RETURN_bool = "Lambda function must return bool";
constexpr ll_string_t INVALID_LAMBDA_RETURN_i32 = "Lambda function must return i32";
} /* namespace traits */
namespace extensions {
#if defined(WINDOWS_SYSTEM)
constexpr ll_string_t DLL_EXTENSION_STR = ".dll";
#else
constexpr ll_string_t DLL_EXTENSION_STR = ".os";
#endif
} /* namespace extensions */

} /* namespace expresions */
} /* namespace header */
} /* namespace llcpp */

#endif /* LLPC_HEADER_LLEXPRESIONS_HPP_ */
