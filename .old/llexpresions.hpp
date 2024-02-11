/*
*	llexpresions.hpp
*
*	Created on: Jun 25, 2023
 *	  Author: Francisco Julio Ruiz Fernandez
 *    Author: llanyro
*/

#ifndef LLCPP_HEADER_LLEXPRESIONS_HPP_
#define LLCPP_HEADER_LLEXPRESIONS_HPP_

#include "llanytypeslib.hpp"

namespace llcpp {
namespace header {
namespace expresions {

namespace bytes {

constexpr f64 bToKb = 1e-3;
constexpr f64 bToMb = 1e-6;
constexpr f64 bToGb = 1e-9;

constexpr b64 KbToB = static_cast<b64>(1e3);
constexpr b64 MbToB = static_cast<b64>(1e6);
constexpr b64 GbToB = static_cast<b64>(1e9);

} // namespace bytes
namespace buffers {

constexpr b64 WRITER_BUFFER_LEN = 256;
constexpr b64 VECTOR_BUFFER_LEN = 300;
constexpr b64 BUFFER_LEN = 300;
constexpr b64 VECTORLIST_BUFFER_INCREMENT_LEN = 128;
constexpr b64 ARRAY_DEFAULT_BUFFER_LEN = 300;
constexpr ui8 JEAII_ALGORITHM_BUFFER_SIZE = 10;

} // namespace buffers
namespace ascii {

enum class ASCII_Base {
    //control characters
    _NULL,                                           // NULL
    SOH,                                             // Start of Heading
    STX,                                             // Start of Text
    ETX,                                             // End of Text
    EOT,                                             // End of Transmission
    ENQ,                                             // Enquiry
    ACK,                                             // Acknowledgement
    BEL,                                             // Bell
    BS,                                              // Backspace
    TAB,                                             // Horizontal Tab
    LF,                                              // Line Feed 
    VT,                                              // Vertical Tab 
    FF,                                              // Form Feed 
    CR,                                              // Carriage Return
    SO,                                              // Shift Out 
    SI,                                              // Shift In 
    DLE,                                             // Data Link Escape 
    DC1,                                             // Device Control 1
    DC2,                                             // Device Control 2
    DC3,                                             // Device Control 3
    DC4,                                             // Device Control 4
    NAK,                                             // Negative Acknowledgement 
    SYN,                                             // Synchronous Idle 
    ETB,                                             // End of Transmission Block 
    CAN,                                             // Cancel
    EM,                                              // End of Medium 
    SUB,                                             // Substitute 
    ESC,                                             // Escape
    SF,                                              // File Separator
    GS,                                              // Group Separator
    RS,                                              // Record Separator
    US,                                              // Unit Separator

    //misc characters				                 

    SPACE,                                           // space
    EXCLAMAION_MARK,                                 // !
    QUOTATION_MARK_DOUBLE,                           // "
    HASHTAG,                                         // #
    SING_DOLLAR,                                     // $
    PRECENT,                                         // %
    AMPERSANT,                                       // &
    QUOTATION_MARK_SINGLE,                           // '
    PARENTHESES_OPEN,                                // (
    PARENTHESES_CLOSE,                               // )
    ASTERISK,                                        // *
    PLUS,                                            // +
    COMMA,                                           // ,
    MINUS,                                           // -
    DOT,                                             // .
    SLASH_FOWARD,                                    // /
    NUMBER_0,                                        // 0
    NUMBER_1,                                        // 1
    NUMBER_2,                                        // 2
    NUMBER_3,                                        // 3
    NUMBER_4,                                        // 4
    NUMBER_5,                                        // 5
    NUMBER_6,                                        // 6
    NUMBER_7,                                        // 7
    NUMBER_8,                                        // 8
    NUMBER_9,                                        // 9
    COLON,                                           // :
    COLON_SEMI,                                      // ;
    LESS_THAN,                                       // <
    EQUAL_TO,                                        // =
    GREATER_THAN,                                    // >
    QUESTION_MARK,                                   // ?
    SING_AT,                                         // @

    //upper case alphabet			                 

    A_UPPER,                                         // A
    B_UPPER,                                         // B
    C_UPPER,                                         // C
    D_UPPER,                                         // D
    E_UPPER,                                         // E
    F_UPPER,                                         // F
    G_UPPER,                                         // G
    H_UPPER,                                         // H
    I_UPPER,                                         // I
    J_UPPER,                                         // J
    K_UPPER,                                         // K
    L_UPPER,                                         // L
    M_UPPER,                                         // M
    N_UPPER,                                         // N
    O_UPPER,                                         // O
    P_UPPER,                                         // P
    Q_UPPER,                                         // Q
    R_UPPER,                                         // R
    S_UPPER,                                         // S
    T_UPPER,                                         // T
    U_UPPER,                                         // U
    V_UPPER,                                         // V
    W_UPPER,                                         // W
    X_UPPER,                                         // X
    Y_UPPER,                                         // Y
    Z_UPPER,                                         // Z

    //misc characters				                 

    BRACKET_OPEN,                                    // [
    SLASH_BACKWARD,                                  // \ 
    BRACKET_CLOSE,                                   // ]
    CARET,                                           // ^
    UNDERSCORE,                                      // _
    GRAVE_ACCENT,                                    // ` 

    //lower case alphabet			                 

    A_LOWER,                                         // a
    B_LOWER,                                         // b
    C_LOWER,                                         // c
    D_LOWER,                                         // d
    E_LOWER,                                         // e
    F_LOWER,                                         // f
    G_LOWER,                                         // g
    H_LOWER,                                         // h
    I_LOWER,                                         // i
    J_LOWER,                                         // j
    K_LOWER,                                         // k
    L_LOWER,                                         // l
    M_LOWER,                                         // m
    N_LOWER,                                         // n
    O_LOWER,                                         // o
    P_LOWER,                                         // p
    Q_LOWER,                                         // q
    R_LOWER,                                         // r
    S_LOWER,                                         // s
    T_LOWER,                                         // t
    U_LOWER,                                         // u
    V_LOWER,                                         // v
    W_LOWER,                                         // w
    X_LOWER,                                         // x
    Y_LOWER,                                         // y
    Z_LOWER,                                         // z

    //misc characters				                 

    BRACKET_CURLY_OPEN,                              // {
    VERTICAL_BAR,                                    // |
    BRACKET_CURLY_CLOSE,                             // }
    TILDE,                                           // ~

    DEL,                                             // Delete
};

enum class ASCII_0 {
    F1 = 59,
    F2 = 60,
    F3 = 61,
    F4 = 62,
    F5 = 63,
    F6 = 64,
    F7 = 65,
    F8 = 66,
    F9 = 67,
    F10 = 68,
    Undefined,
};
enum class ASCII_224 {
    ArrowUp = 72,
    ArrowDown = 80,
    ArrowLeft = 75,
    ArrowRight = 77,
    F11 = 133,
    F12 = 134,
    Undefined,
};

enum class ASCII {
#pragma region ControlCharacters
    _NULL,                                           // NULL
    SOH,                                             // Start of Heading
    STX,                                             // Start of Text
    ETX,                                             // End of Text
    EOT,                                             // End of Transmission
    ENQ,                                             // Enquiry
    ACK,                                             // Acknowledgement
    BEL,                                             // Bell
    BS,                                              // Backspace
    TAB,                                             // Horizontal Tab
    LF,                                              // Line Feed 
    VT,                                              // Vertical Tab 
    FF,                                              // Form Feed 
    CR,                                              // Carriage Return
    SO,                                              // Shift Out 
    SI,                                              // Shift In 
    DLE,                                             // Data Link Escape 
    DC1,                                             // Device Control 1
    DC2,                                             // Device Control 2
    DC3,                                             // Device Control 3
    DC4,                                             // Device Control 4
    NAK,                                             // Negative Acknowledgement 
    SYN,                                             // Synchronous Idle 
    ETB,                                             // End of Transmission Block 
    CAN,                                             // Cancel
    EM,                                              // End of Medium 
    SUB,                                             // Substitute 
    ESC,                                             // Escape
    SF,                                              // File Separator
    GS,                                              // Group Separator
    RS,                                              // Record Separator
    US,                                              // Unit Separator
#pragma endregion
#pragma region MiscCharacters
    SPACE,                                           // space
    EXCLAMAION_MARK,                                 // !
    QUOTATION_MARK_DOUBLE,                           // "
    HASHTAG,                                         // #
    SING_DOLLAR,                                     // $
    PRECENT,                                         // %
    AMPERSANT,                                       // &
    QUOTATION_MARK_SINGLE,                           // '
    PARENTHESES_OPEN,                                // (
    PARENTHESES_CLOSE,                               // )
    ASTERISK,                                        // *
    PLUS,                                            // +
    COMMA,                                           // ,
    MINUS,                                           // -
    DOT,                                             // .
    SLASH_FOWARD,                                    // /
    NUMBER_0,                                        // 0
    NUMBER_1,                                        // 1
    NUMBER_2,                                        // 2
    NUMBER_3,                                        // 3
    NUMBER_4,                                        // 4
    NUMBER_5,                                        // 5
    NUMBER_6,                                        // 6
    NUMBER_7,                                        // 7
    NUMBER_8,                                        // 8
    NUMBER_9,                                        // 9
    COLON,                                           // :
    COLON_SEMI,                                      // ;
    LESS_THAN,                                       // <
    EQUAL_TO,                                        // =
    GREATER_THAN,                                    // >
    QUESTION_MARK,                                   // ?
    SING_AT,                                         // @
#pragma endregion
#pragma region UpperCaseAlphabet
    A_UPPER,                                         // A
    B_UPPER,                                         // B
    C_UPPER,                                         // C
    D_UPPER,                                         // D
    E_UPPER,                                         // E
    F_UPPER,                                         // F
    G_UPPER,                                         // G
    H_UPPER,                                         // H
    I_UPPER,                                         // I
    J_UPPER,                                         // J
    K_UPPER,                                         // K
    L_UPPER,                                         // L
    M_UPPER,                                         // M
    N_UPPER,                                         // N
    O_UPPER,                                         // O
    P_UPPER,                                         // P
    Q_UPPER,                                         // Q
    R_UPPER,                                         // R
    S_UPPER,                                         // S
    T_UPPER,                                         // T
    U_UPPER,                                         // U
    V_UPPER,                                         // V
    W_UPPER,                                         // W
    X_UPPER,                                         // X
    Y_UPPER,                                         // Y
    Z_UPPER,                                         // Z
#pragma endregion
#pragma region MiscCharacters				                 
    BRACKET_OPEN,                                    // [
    SLASH_BACKWARD,                                  // \ 
    BRACKET_CLOSE,                                   // ]
    CARET,                                           // ^
    UNDERSCORE,                                      // _
    GRAVE_ACCENT,                                    // ` 
#pragma endregion
#pragma region LowerCaseAlphabet
    A_LOWER,                                         // a
    B_LOWER,                                         // b
    C_LOWER,                                         // c
    D_LOWER,                                         // d
    E_LOWER,                                         // e
    F_LOWER,                                         // f
    G_LOWER,                                         // g
    H_LOWER,                                         // h
    I_LOWER,                                         // i
    J_LOWER,                                         // j
    K_LOWER,                                         // k
    L_LOWER,                                         // l
    M_LOWER,                                         // m
    N_LOWER,                                         // n
    O_LOWER,                                         // o
    P_LOWER,                                         // p
    Q_LOWER,                                         // q
    R_LOWER,                                         // r
    S_LOWER,                                         // s
    T_LOWER,                                         // t
    U_LOWER,                                         // u
    V_LOWER,                                         // v
    W_LOWER,                                         // w
    X_LOWER,                                         // x
    Y_LOWER,                                         // y
    Z_LOWER,                                         // z
#pragma endregion
#pragma region MiscCharacters				                 
    BRACKET_CURLY_OPEN,                              // {
    VERTICAL_BAR,                                    // |
    BRACKET_CURLY_CLOSE,                             // }
    TILDE,                                           // ~
#pragma endregion
    DEL,                                             // Delete
#pragma region Ascii0
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,

#pragma endregion
#pragma region Ascii224
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    F11,
    F12,

#pragma endregion

    // None
    Undefined,
};

} // namespace ascii
namespace strings {

constexpr StrPair NULL_VALUE_STR = "Value cannot be nullptr";
constexpr StrPair ZERO_BYTES_VALUE_STR = "Number of bytes provided cannot be 0";

} // namespace strings
namespace extensions {
#if defined(WINDOWS_SYSTEM)
constexpr StrPair DLL_EXTENSION_STR = ".dll";
#else
constexpr StrPair DLL_EXTENSION_STR = ".os";
#endif
} // namespace extensions

/*!
 *	@template True
 *	@brief Gets a string of a bool
 *
 *	Gives a user a string that represents the bool provided
 *	true will be : "True"
 *	false will be: "False"
 *
 *	@param[in] v Bool value
 *
 *	@return String that represents bool value
 *
 *	@constexpr True
 *
 *	@thread_safety This function may be called from any thread.
 *
 *	@sa @ref llcpp
 *
 *	@since Added in version 1.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
__LL_NODISCARD__ constexpr ll_string_t getBoolString(const ll_bool_t v) {
    return v ? strings::TRUE_STR : strings::FALSE_STR;
}
/*!
 *	@template True
 *	@brief Gets a StrPair of a bool
 *
 *	Gives a user a string that represents the bool provided
 *	true will be : { "True", 4 }
 *	false will be: { "False", 5 }
 *
 *	@param[in] v Bool value
 *
 *	@return StrPair that represents bool value
 *
 *	@constexpr True
 *
 *	@thread_safety This function may be called from any thread.
 *
 *	@sa @ref llcpp
 *
 *	@since Added in version 1.0.
 *
 *	@ingroup llcpp
 *	@ingroup headers
 */
__LL_NODISCARD__ constexpr StrPair getBoolStringPair(const ll_bool_t v) {
    return v ? strings::TRUE_STR : strings::FALSE_STR;
}

} // namespace expresions
} // namespace header
} // namespace llcpp

#endif // LLCPP_HEADER_LLEXPRESIONS_HPP_
