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


} /* namespace strings */
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
