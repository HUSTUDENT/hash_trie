/*
 *  Catch v2.0.0-develop.1
 *  Generated: 2017-08-05 11:29:14.014889
 *  ----------------------------------------------------------
 *  This file has been merged from multiple headers. Please don't edit it directly
 *  Copyright (c) 2017 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
#define TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED
// start catch.hpp


#ifdef __clang__
#    pragma clang system_header
#elif defined __GNUC__
#    pragma GCC system_header
#endif

// start catch_suppress_warnings.h

#ifdef __clang__
#   ifdef __ICC // icpc defines the __clang__ macro
#       pragma warning(push)
#       pragma warning(disable: 161 1682)
#   else // __ICC
#       pragma clang diagnostic ignored "-Wglobal-constructors"
#       pragma clang diagnostic ignored "-Wvariadic-macros"
#       pragma clang diagnostic ignored "-Wc99-extensions"
#       pragma clang diagnostic ignored "-Wunused-variable"
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wpadded"
#       pragma clang diagnostic ignored "-Wswitch-enum"
#       pragma clang diagnostic ignored "-Wcovered-switch-default"
#    endif
#elif defined __GNUC__
#    pragma GCC diagnostic ignored "-Wvariadic-macros"
#    pragma GCC diagnostic ignored "-Wunused-variable"
#    pragma GCC diagnostic ignored "-Wparentheses"

#    pragma GCC diagnostic push
#    pragma GCC diagnostic ignored "-Wpadded"
#endif
// end catch_suppress_warnings.h
#if defined(CATCH_CONFIG_MAIN) || defined(CATCH_CONFIG_RUNNER)
#  define CATCH_IMPL
#endif

#ifdef CATCH_IMPL
#  ifndef CLARA_CONFIG_MAIN
#    define CLARA_CONFIG_MAIN_NOT_DEFINED
#    define CLARA_CONFIG_MAIN
#  endif
#endif

// start catch_context.h

#include <memory>

namespace Catch {

    class TestCase;
    class Stream;
    struct IResultCapture;
    struct IRunner;
    struct IConfig;

    using IConfigPtr = std::shared_ptr<IConfig const>;

    struct IContext
    {
        virtual ~IContext();

        virtual IResultCapture* getResultCapture() = 0;
        virtual IRunner* getRunner() = 0;
        virtual IConfigPtr getConfig() const = 0;
    };

    struct IMutableContext : IContext
    {
        virtual ~IMutableContext();
        virtual void setResultCapture( IResultCapture* resultCapture ) = 0;
        virtual void setRunner( IRunner* runner ) = 0;
        virtual void setConfig( IConfigPtr const& config ) = 0;
    };

    IContext& getCurrentContext();
    IMutableContext& getCurrentMutableContext();
    void cleanUpContext();
}

// end catch_context.h
// start catch_tag_alias_autoregistrar.h

// start catch_common.h

// start catch_compiler_capabilities.h

// Detect a number of compiler features - by compiler
// The following features are defined:
//
// CATCH_CONFIG_COUNTER : is the __COUNTER__ macro supported?
// CATCH_CONFIG_WINDOWS_SEH : is Windows SEH supported?
// CATCH_CONFIG_POSIX_SIGNALS : are POSIX signals supported?
// ****************
// Note to maintainers: if new toggles are added please document them
// in configuration.md, too
// ****************

// In general each macro has a _NO_<feature name> form
// (e.g. CATCH_CONFIG_NO_POSIX_SIGNALS) which disables the feature.
// Many features, at point of detection, define an _INTERNAL_ macro, so they
// can be combined, en-mass, with the _NO_ forms later.

#ifdef __cplusplus

#  if __cplusplus >= 201402L
#    define CATCH_CPP14_OR_GREATER
#  endif

#endif

#ifdef __clang__

#       define CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS \
            _Pragma( "clang diagnostic push" ) \
            _Pragma( "clang diagnostic ignored \"-Wexit-time-destructors\"" )
#       define CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS \
            _Pragma( "clang diagnostic pop" )

#       define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
            _Pragma( "clang diagnostic push" ) \
            _Pragma( "clang diagnostic ignored \"-Wparentheses\"" )
#       define CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS \
            _Pragma( "clang diagnostic pop" )

#endif // __clang__

////////////////////////////////////////////////////////////////////////////////
// We know some environments not to support full POSIX signals
#if defined(__CYGWIN__) || defined(__QNX__)

#   if !defined(CATCH_CONFIG_POSIX_SIGNALS)
#       define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#   endif

#endif

#ifdef __OS400__
#       define CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS
#       define CATCH_CONFIG_COLOUR_NONE
#endif

////////////////////////////////////////////////////////////////////////////////
// Cygwin
#ifdef __CYGWIN__

// Required for some versions of Cygwin to declare gettimeofday
// see: http://stackoverflow.com/questions/36901803/gettimeofday-not-declared-in-this-scope-cygwin
#   define _BSD_SOURCE

#endif // __CYGWIN__

////////////////////////////////////////////////////////////////////////////////
// Borland
#ifdef __BORLANDC__

#endif // __BORLANDC__

////////////////////////////////////////////////////////////////////////////////
// EDG
#ifdef __EDG_VERSION__

#endif // __EDG_VERSION__

////////////////////////////////////////////////////////////////////////////////
// Digital Mars
#ifdef __DMC__

#endif // __DMC__

////////////////////////////////////////////////////////////////////////////////
// GCC
#ifdef __GNUC__

#endif // __GNUC__

////////////////////////////////////////////////////////////////////////////////
// Visual C++
#ifdef _MSC_VER

#define CATCH_INTERNAL_CONFIG_WINDOWS_SEH

#endif // _MSC_VER

////////////////////////////////////////////////////////////////////////////////

// Use __COUNTER__ if the compiler supports it
#if ( defined _MSC_VER && _MSC_VER >= 1300 ) || \
    ( defined __GNUC__  && ( __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3 )) ) || \
    ( defined __clang__ && __clang_major__ >= 3 )

#define CATCH_INTERNAL_CONFIG_COUNTER

#endif

// Now set the actual defines based on the above + anything the user has configured

// Use of __COUNTER__ is suppressed if __JETBRAINS_IDE__ is #defined (meaning we're being parsed by a JetBrains IDE for
// analytics) because, at time of writing, __COUNTER__ is not properly handled by it.
// This does not affect compilation
#if defined(CATCH_INTERNAL_CONFIG_COUNTER) && !defined(CATCH_CONFIG_NO_COUNTER) && !defined(CATCH_CONFIG_COUNTER) && !defined(__JETBRAINS_IDE__)
#   define CATCH_CONFIG_COUNTER
#endif
#if defined(CATCH_INTERNAL_CONFIG_WINDOWS_SEH) && !defined(CATCH_CONFIG_NO_WINDOWS_SEH) && !defined(CATCH_CONFIG_WINDOWS_SEH)
#   define CATCH_CONFIG_WINDOWS_SEH
#endif
// This is set by default, because we assume that unix compilers are posix-signal-compatible by default.
#if !defined(CATCH_INTERNAL_CONFIG_NO_POSIX_SIGNALS) && !defined(CATCH_CONFIG_NO_POSIX_SIGNALS) && !defined(CATCH_CONFIG_POSIX_SIGNALS)
#   define CATCH_CONFIG_POSIX_SIGNALS
#endif

#if !defined(CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS
#   define CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS
#endif
#if !defined(CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS)
#   define CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS
#   define CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS
#endif

// end catch_compiler_capabilities.h
#define INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line ) name##line
#define INTERNAL_CATCH_UNIQUE_NAME_LINE( name, line ) INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line )
#ifdef CATCH_CONFIG_COUNTER
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __COUNTER__ )
#else
#  define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __LINE__ )
#endif

#define INTERNAL_CATCH_STRINGIFY2( expr ) #expr
#define INTERNAL_CATCH_STRINGIFY( expr ) INTERNAL_CATCH_STRINGIFY2( expr )

#include <iosfwd>
#include <string>
#include <cstdint>

namespace Catch {

    struct IConfig;

    struct CaseSensitive { enum Choice {
        Yes,
        No
    }; };

    class NonCopyable {
        NonCopyable( NonCopyable const& )              = delete;
        NonCopyable( NonCopyable && )                  = delete;
        NonCopyable& operator = ( NonCopyable const& ) = delete;
        NonCopyable& operator = ( NonCopyable && )     = delete;

    protected:
        NonCopyable() {}
        virtual ~NonCopyable();
    };

    struct SourceLineInfo {

        SourceLineInfo() noexcept;
        SourceLineInfo( char const* _file, std::size_t _line ) noexcept;

        SourceLineInfo(SourceLineInfo const& other)          = default;
        SourceLineInfo( SourceLineInfo && )                  = default;
        SourceLineInfo& operator = ( SourceLineInfo const& ) = default;
        SourceLineInfo& operator = ( SourceLineInfo && )     = default;

        bool empty() const noexcept;
        bool operator == ( SourceLineInfo const& other ) const noexcept;
        bool operator < ( SourceLineInfo const& other ) const noexcept;

        char const* file;
        std::size_t line;
    };

    std::ostream& operator << ( std::ostream& os, SourceLineInfo const& info );

    // This is just here to avoid compiler warnings with macro constants and boolean literals
    bool isTrue( bool value );
    bool alwaysTrue();
    bool alwaysFalse();

    void seedRng( IConfig const& config );
    unsigned int rngSeed();

    // Use this in variadic streaming macros to allow
    //    >> +StreamEndStop
    // as well as
    //    >> stuff +StreamEndStop
    struct StreamEndStop {
        std::string operator+() const;
    };
    template<typename T>
    T const& operator + ( T const& value, StreamEndStop ) {
        return value;
    }
}

#define CATCH_INTERNAL_LINEINFO \
    ::Catch::SourceLineInfo( __FILE__, static_cast<std::size_t>( __LINE__ ) )

// end catch_common.h
namespace Catch {

    struct RegistrarForTagAliases {
        RegistrarForTagAliases( char const* alias, char const* tag, SourceLineInfo const& lineInfo );
    };

} // end namespace Catch

#define CATCH_REGISTER_TAG_ALIAS( alias, spec ) namespace{ Catch::RegistrarForTagAliases INTERNAL_CATCH_UNIQUE_NAME( AutoRegisterTagAlias )( alias, spec, CATCH_INTERNAL_LINEINFO ); }

// end catch_tag_alias_autoregistrar.h
// start catch_test_registry.hpp

// start catch_interfaces_testcase.h

#include <vector>
#include <memory>

namespace Catch {

    class TestSpec;

    struct ITestInvoker {
        virtual void invoke () const = 0;
        virtual ~ITestInvoker();
    };

    using ITestCasePtr = std::shared_ptr<ITestInvoker>;

    class TestCase;
    struct IConfig;

    struct ITestCaseRegistry {
        virtual ~ITestCaseRegistry();
        virtual std::vector<TestCase> const& getAllTests() const = 0;
        virtual std::vector<TestCase> const& getAllTestsSorted( IConfig const& config ) const = 0;
    };

    bool matchTest( TestCase const& testCase, TestSpec const& testSpec, IConfig const& config );
    std::vector<TestCase> filterTests( std::vector<TestCase> const& testCases, TestSpec const& testSpec, IConfig const& config );
    std::vector<TestCase> const& getAllTestCasesSorted( IConfig const& config );

}

// end catch_interfaces_testcase.h
// start catch_stringref.h

namespace Catch {

    class String;
    class StringData;

    /// A non-owning string class (similar to the forthcoming std::string_view)
    /// Note that, because a StringRef may be a substring of another string,
    /// it may not be null terminated. c_str() must return a null terminated
    /// string, however, and so the StringRef will internally take ownership
    /// (taking a copy), if necessary. In theory this ownership is not externally
    /// visible - but it does mean (substring) StringRefs should not be shared between
    /// threads.
    class StringRef {
        friend struct StringRefTestAccess;
        friend class StringData;
        friend class StringBuilder;

        using size_type = unsigned long;

        char const* m_start;
        size_type m_size;

        StringData const* m_data = nullptr;

        void takeOwnership();

    public: // construction/ assignment
        StringRef() noexcept;
        StringRef( StringRef const& other ) noexcept;
        StringRef( StringRef&& other ) noexcept;
        StringRef( char const* rawChars ) noexcept;
        StringRef( char const* rawChars, size_type size ) noexcept;
        StringRef( String const& other ) noexcept;
        StringRef( String&& other ) noexcept;
        ~StringRef() noexcept;

        auto operator = ( StringRef other ) noexcept -> StringRef&;

        void swap( StringRef& other ) noexcept;

    public: // operators
        auto operator == ( StringRef const& other ) const noexcept -> bool;
        auto operator != ( StringRef const& other ) const noexcept -> bool;

        auto operator[] ( size_type index ) const noexcept -> char;

    public: // named queries
        auto empty() const noexcept -> bool;
        auto size() const noexcept -> size_type;
        auto c_str() const -> char const*;

    public: // substrings and searches
        auto substr( size_type start, size_type size ) const noexcept -> StringRef;

    private: // ownership queries - may not be consistent between calls
        auto isOwned() const noexcept -> bool;
        auto isSubstring() const noexcept -> bool;
        auto data() const noexcept -> char const*;
    };

    auto operator + ( StringRef const& lhs, StringRef const& rhs ) -> String;
    auto operator + ( StringRef const& lhs, char const* rhs ) -> String;
    auto operator + ( char const* lhs, StringRef const& rhs ) -> String;

} // namespace Catch

// end catch_stringref.h
namespace Catch {

template<typename C>
class TestInvokerAsMethod : public ITestInvoker {
    void (C::*m_testAsMethod)();
public:
    TestInvokerAsMethod( void (C::*testAsMethod)() ) noexcept : m_testAsMethod( testAsMethod ) {}

    void invoke() const override {
        C obj;
        (obj.*m_testAsMethod)();
    }
};

auto makeTestInvoker( void(*testAsFunction)() ) noexcept -> ITestInvoker*;

template<typename C>
auto makeTestInvoker( void (C::*testAsMethod)() ) noexcept -> ITestInvoker* {
    return new(std::nothrow) TestInvokerAsMethod<C>( testAsMethod );
}

struct NameAndTags {
    NameAndTags( StringRef name_ = "", StringRef tags_ = "" ) noexcept;
    StringRef name;
    StringRef tags;
};

struct AutoReg : NonCopyable {
    AutoReg( ITestInvoker* invoker, SourceLineInfo const& lineInfo, StringRef classOrMethod, NameAndTags const& nameAndTags ) noexcept;
    ~AutoReg() = default;
};

} // end namespace Catch

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TESTCASE2( TestName, ... ) \
        static void TestName(); \
        CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &TestName ), CATCH_INTERNAL_LINEINFO, "", Catch::NameAndTags{ __VA_ARGS__ } ); } \
        CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS \
        static void TestName()
    #define INTERNAL_CATCH_TESTCASE( ... ) \
        INTERNAL_CATCH_TESTCASE2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_METHOD_AS_TEST_CASE( QualifiedMethod, ... ) \
        CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS \
        namespace{ Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar )( Catch::makeTestInvoker( &QualifiedMethod ), CATCH_INTERNAL_LINEINFO, "&" #QualifiedMethod, Catch::NameAndTags{ __VA_ARGS__ } ); } \
        CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_TEST_CASE_METHOD2( TestName, ClassName, ... )\
        CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS \
        namespace{ \
            struct TestName : ClassName{ \
                void test(); \
            }; \
            Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME( autoRegistrar ) ( Catch::makeTestInvoker( &TestName::test ), CATCH_INTERNAL_LINEINFO, #ClassName, Catch::NameAndTags{ __VA_ARGS__ } ); \
        } \
        CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS \
        void TestName::test()
    #define INTERNAL_CATCH_TEST_CASE_METHOD( ClassName, ... ) \
        INTERNAL_CATCH_TEST_CASE_METHOD2( INTERNAL_CATCH_UNIQUE_NAME( ____C_A_T_C_H____T_E_S_T____ ), ClassName, __VA_ARGS__ )

    ///////////////////////////////////////////////////////////////////////////////
    #define INTERNAL_CATCH_REGISTER_TESTCASE( Function, ... ) \
        CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS \
        Catch::AutoReg( Catch::makeTestInvoker( Function ), CATCH_INTERNAL_LINEINFO, "", Catch::NameAndTags{ __VA_ARGS__ } ); \
        CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS

// end catch_test_registry.hpp
// start catch_capture.hpp

// start catch_result_builder.h

// start catch_result_type.h

namespace Catch {

    // ResultWas::OfType enum
    struct ResultWas { enum OfType {
        Unknown = -1,
        Ok = 0,
        Info = 1,
        Warning = 2,

        FailureBit = 0x10,

        ExpressionFailed = FailureBit | 1,
        ExplicitFailure = FailureBit | 2,

        Exception = 0x100 | FailureBit,

        ThrewException = Exception | 1,
        DidntThrowException = Exception | 2,

        FatalErrorCondition = 0x200 | FailureBit

    }; };

    bool isOk( ResultWas::OfType resultType );
    bool isJustInfo( int flags );

    // ResultDisposition::Flags enum
    struct ResultDisposition { enum Flags {
        Normal = 0x01,

        ContinueOnFailure = 0x02,   // Failures fail test, but execution continues
        FalseTest = 0x04,           // Prefix expression with !
        SuppressFail = 0x08         // Failures are reported but do not fail the test
    }; };

    ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs );

    bool shouldContinueOnFailure( int flags );
    bool isFalseTest( int flags );
    bool shouldSuppressFailure( int flags );

} // end namespace Catch

// end catch_result_type.h
// start catch_assertionresult.h

#include <string>

namespace Catch {

    struct STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison;

    struct DecomposedExpression
    {
        DecomposedExpression() = default;
        DecomposedExpression( DecomposedExpression const& ) = default;
        DecomposedExpression& operator = ( DecomposedExpression const& ) = delete;

        virtual ~DecomposedExpression() = default;
        virtual bool isBinaryExpression() const;
        virtual void reconstructExpression( std::string& dest ) const = 0;

        // Only simple binary comparisons can be decomposed.
        // If more complex check is required then wrap sub-expressions in parentheses.
        template<typename T> STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator + ( T const& );
        template<typename T> STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator - ( T const& );
        template<typename T> STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator * ( T const& );
        template<typename T> STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator / ( T const& );
        template<typename T> STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator % ( T const& );
        template<typename T> STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator && ( T const& );
        template<typename T> STATIC_ASSERT_Expression_Too_Complex_Please_Rewrite_As_Binary_Comparison& operator || ( T const& );
    };

    struct AssertionInfo
    {
        AssertionInfo() = default;
        AssertionInfo(  char const * _macroName,
                        SourceLineInfo const& _lineInfo,
                        char const * _capturedExpression,
                        ResultDisposition::Flags _resultDisposition);

        char const * macroName = nullptr;
        SourceLineInfo lineInfo;
        char const * capturedExpression = nullptr;
        ResultDisposition::Flags resultDisposition = ResultDisposition::Normal;
    };

    struct AssertionResultData
    {
        void negate( bool parenthesize );
        std::string const& reconstructExpression() const;

        mutable DecomposedExpression const* decomposedExpression = nullptr;
        mutable std::string reconstructedExpression;
        std::string message;
        ResultWas::OfType resultType = ResultWas::Unknown;
        bool negated = false;
        bool parenthesized = false;
    };

    class AssertionResult {
    public:
        AssertionResult();
        AssertionResult( AssertionInfo const& info, AssertionResultData const& data );
        ~AssertionResult();

        AssertionResult( AssertionResult const& )              = default;
        AssertionResult( AssertionResult && )                  = default;
        AssertionResult& operator = ( AssertionResult const& ) = default;
        AssertionResult& operator = ( AssertionResult && )     = default;

        bool isOk() const;
        bool succeeded() const;
        ResultWas::OfType getResultType() const;
        bool hasExpression() const;
        bool hasMessage() const;
        std::string getExpression() const;
        std::string getExpressionInMacro() const;
        bool hasExpandedExpression() const;
        std::string getExpandedExpression() const;
        std::string getMessage() const;
        SourceLineInfo getSourceInfo() const;
        std::string getTestMacroName() const;
        void discardDecomposedExpression() const;
        void expandDecomposedExpression() const;

    protected:
        AssertionInfo m_info;
        AssertionResultData m_resultData;
    };

} // end namespace Catch

// end catch_assertionresult.h
// start catch_matchers.hpp

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

#include <string>
#include <vector>

namespace Catch {
namespace Matchers {
    namespace Impl {

        template<typename ArgT> struct MatchAllOf;
        template<typename ArgT> struct MatchAnyOf;
        template<typename ArgT> struct MatchNotOf;

        class MatcherUntypedBase {
        public:
            MatcherUntypedBase() = default;
            MatcherUntypedBase ( MatcherUntypedBase const& ) = default;
            MatcherUntypedBase& operator = ( MatcherUntypedBase const& ) = delete;
            std::string toString() const;

        protected:
            virtual ~MatcherUntypedBase() = default;
            virtual std::string describe() const = 0;
            mutable std::string m_cachedToString;
        };

        template<typename ObjectT>
        struct MatcherMethod {
            virtual bool match( ObjectT const& arg ) const = 0;
        };
        template<typename PtrT>
        struct MatcherMethod<PtrT*> {
            virtual bool match( PtrT* arg ) const = 0;
        };

        template<typename ObjectT, typename ComparatorT = ObjectT>
        struct MatcherBase : MatcherUntypedBase, MatcherMethod<ObjectT> {

            MatchAllOf<ComparatorT> operator && ( MatcherBase const& other ) const;
            MatchAnyOf<ComparatorT> operator || ( MatcherBase const& other ) const;
            MatchNotOf<ComparatorT> operator ! () const;
        };

        template<typename ArgT>
        struct MatchAllOf : MatcherBase<ArgT> {
            bool match( ArgT const& arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (!matcher->match(arg))
                        return false;
                }
                return true;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " and ";
                    description += matcher->toString();
                }
                description += " )";
                return description;
            }

            MatchAllOf<ArgT>& operator && ( MatcherBase<ArgT> const& other ) {
                m_matchers.push_back( &other );
                return *this;
            }

            std::vector<MatcherBase<ArgT> const*> m_matchers;
        };
        template<typename ArgT>
        struct MatchAnyOf : MatcherBase<ArgT> {

            bool match( ArgT const& arg ) const override {
                for( auto matcher : m_matchers ) {
                    if (matcher->match(arg))
                        return true;
                }
                return false;
            }
            std::string describe() const override {
                std::string description;
                description.reserve( 4 + m_matchers.size()*32 );
                description += "( ";
                bool first = true;
                for( auto matcher : m_matchers ) {
                    if( first )
                        first = false;
                    else
                        description += " or ";
                    description += matcher->toString();
                }
                description += " )";
                return description;
            }

            MatchAnyOf<ArgT>& operator || ( MatcherBase<ArgT> const& other ) {
                m_matchers.push_back( &other );
                return *this;
            }

            std::vector<MatcherBase<ArgT> const*> m_matchers;
        };

        template<typename ArgT>
        struct MatchNotOf : MatcherBase<ArgT> {

            MatchNotOf( MatcherBase<ArgT> const& underlyingMatcher ) : m_underlyingMatcher( underlyingMatcher ) {}

            bool match( ArgT const& arg ) const override {
                return !m_underlyingMatcher.match( arg );
            }

            std::string describe() const override {
                return "not " + m_underlyingMatcher.toString();
            }
            MatcherBase<ArgT> const& m_underlyingMatcher;
        };

        template<typename ObjectT, typename ComparatorT>
        MatchAllOf<ComparatorT> MatcherBase<ObjectT, ComparatorT>::operator && ( MatcherBase const& other ) const {
            return MatchAllOf<ComparatorT>() && *this && other;
        }
        template<typename ObjectT, typename ComparatorT>
        MatchAnyOf<ComparatorT> MatcherBase<ObjectT, ComparatorT>::operator || ( MatcherBase const& other ) const {
            return MatchAnyOf<ComparatorT>() || *this || other;
        }
        template<typename ObjectT, typename ComparatorT>
        MatchNotOf<ComparatorT> MatcherBase<ObjectT, ComparatorT>::operator ! () const {
            return MatchNotOf<ComparatorT>( *this );
        }

    } // namespace Impl

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred
    // - deprecated: prefer ||, && and !
    template<typename T>
    Impl::MatchNotOf<T> Not( Impl::MatcherBase<T> const& underlyingMatcher ) {
        return Impl::MatchNotOf<T>( underlyingMatcher );
    }
    template<typename T>
    Impl::MatchAllOf<T> AllOf( Impl::MatcherBase<T> const& m1, Impl::MatcherBase<T> const& m2 ) {
        return Impl::MatchAllOf<T>() && m1 && m2;
    }
    template<typename T>
    Impl::MatchAllOf<T> AllOf( Impl::MatcherBase<T> const& m1, Impl::MatcherBase<T> const& m2, Impl::MatcherBase<T> const& m3 ) {
        return Impl::MatchAllOf<T>() && m1 && m2 && m3;
    }
    template<typename T>
    Impl::MatchAnyOf<T> AnyOf( Impl::MatcherBase<T> const& m1, Impl::MatcherBase<T> const& m2 ) {
        return Impl::MatchAnyOf<T>() || m1 || m2;
    }
    template<typename T>
    Impl::MatchAnyOf<T> AnyOf( Impl::MatcherBase<T> const& m1, Impl::MatcherBase<T> const& m2, Impl::MatcherBase<T> const& m3 ) {
        return Impl::MatchAnyOf<T>() || m1 || m2 || m3;
    }

} // namespace Matchers

using namespace Matchers;
using Matchers::Impl::MatcherBase;

} // namespace Catch

#endif // CATCH_CONFIG_DISABLE_MATCHERS

// end catch_matchers.hpp
#include <sstream>

namespace Catch {

    struct TestFailureException{};

    template<typename T> class ExpressionLhs;

    struct CopyableStream {
        CopyableStream() = default;
        CopyableStream( CopyableStream const& other );
        CopyableStream& operator=( CopyableStream const& other );

        std::ostringstream oss;
    };

    class ResultBuilder : public DecomposedExpression {
    public:
        ResultBuilder(  char const* macroName,
                        SourceLineInfo const& lineInfo,
                        char const* capturedExpression,
                        ResultDisposition::Flags resultDisposition);
        ~ResultBuilder();

        template<typename T>
        ExpressionLhs<T const&> operator <= ( T const& operand );
        ExpressionLhs<bool> operator <= ( bool value );

        template<typename T>
        ResultBuilder& operator << ( T const& value ) {
            stream().oss << value;
            return *this;
        }

        ResultBuilder& setResultType( ResultWas::OfType result );
        ResultBuilder& setResultType( bool result );

        void endExpression( DecomposedExpression const& expr );

        void reconstructExpression( std::string& dest ) const override;

        AssertionResult build() const;
        AssertionResult build( DecomposedExpression const& expr ) const;

        void useActiveException( ResultDisposition::Flags resultDisposition = ResultDisposition::Normal );
        void captureResult( ResultWas::OfType resultType );
        void captureExpression();
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
        void captureExpectedException( std::string const& expectedMessage );
        void captureExpectedException( Matchers::Impl::MatcherBase<std::string> const& matcher );
#endif // CATCH_CONFIG_DISABLE_MATCHERS
        void handleResult( AssertionResult const& result );
        void react();
        bool shouldDebugBreak() const;
        bool allowThrows() const;

        template<typename ArgT, typename MatcherT>
        void captureMatch( ArgT const& arg, MatcherT const& matcher, char const* matcherString );

        void setExceptionGuard();
        void unsetExceptionGuard();

    private:
        AssertionInfo m_assertionInfo;
        AssertionResultData m_data;

        CopyableStream& stream();
        static CopyableStream& s_stream();

        bool m_shouldDebugBreak = false;
        bool m_shouldThrow = false;
        bool m_guardException = false;
        bool m_usedStream = false;
    };

} // namespace Catch

// Include after due to circular dependency:
// start catch_expression_lhs.hpp

// start catch_evaluate.hpp

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4389) // '==' : signed/unsigned mismatch
#pragma warning(disable:4312) // Converting int to T* using reinterpret_cast (issue on x64 platform)
#endif

#include <cstddef>

namespace Catch {
namespace Internal {

    enum Operator {
        IsEqualTo,
        IsNotEqualTo,
        IsLessThan,
        IsGreaterThan,
        IsLessThanOrEqualTo,
        IsGreaterThanOrEqualTo
    };

    const char* operatorName(Operator op);

    template<typename T>
    T& opCast(T const& t) { return const_cast<T&>(t); }
    std::nullptr_t opCast(std::nullptr_t);

    // So the compare overloads can be operator agnostic we convey the operator as a template
    // enum, which is used to specialise an Evaluator for doing the comparison.
    template<typename T1, typename T2, Operator Op>
    struct Evaluator{};

    template<typename T1, typename T2>
    struct Evaluator<T1, T2, IsEqualTo> {
        static bool evaluate( T1 const& lhs, T2 const& rhs) {
            return bool( opCast( lhs ) ==  opCast( rhs ) );
        }
    };
    template<typename T1, typename T2>
    struct Evaluator<T1, T2, IsNotEqualTo> {
        static bool evaluate( T1 const& lhs, T2 const& rhs ) {
            return bool( opCast( lhs ) != opCast( rhs ) );
        }
    };
    template<typename T1, typename T2>
    struct Evaluator<T1, T2, IsLessThan> {
        static bool evaluate( T1 const& lhs, T2 const& rhs ) {
            return bool( opCast( lhs ) < opCast( rhs ) );
        }
    };
    template<typename T1, typename T2>
    struct Evaluator<T1, T2, IsGreaterThan> {
        static bool evaluate( T1 const& lhs, T2 const& rhs ) {
            return bool( opCast( lhs ) > opCast( rhs ) );
        }
    };
    template<typename T1, typename T2>
    struct Evaluator<T1, T2, IsGreaterThanOrEqualTo> {
        static bool evaluate( T1 const& lhs, T2 const& rhs ) {
            return bool( opCast( lhs ) >= opCast( rhs ) );
        }
    };
    template<typename T1, typename T2>
    struct Evaluator<T1, T2, IsLessThanOrEqualTo> {
        static bool evaluate( T1 const& lhs, T2 const& rhs ) {
            return bool( opCast( lhs ) <= opCast( rhs ) );
        }
    };

    template<Operator Op, typename T1, typename T2>
    bool applyEvaluator( T1 const& lhs, T2 const& rhs ) {
        return Evaluator<T1, T2, Op>::evaluate( lhs, rhs );
    }

    // This level of indirection allows us to specialise for integer types
    // to avoid signed/ unsigned warnings

    // "base" overload
    template<Operator Op, typename T1, typename T2>
    bool compare( T1 const& lhs, T2 const& rhs ) {
        return Evaluator<T1, T2, Op>::evaluate( lhs, rhs );
    }

	template<Operator Op>
	bool compare( void const* lhs, void const* rhs ) {
		return Evaluator<void const*, void const*, Op>::evaluate( lhs, rhs );
	}

    // unsigned X to int
    template<Operator Op> bool compare( unsigned int lhs, int rhs ) {
        return applyEvaluator<Op>( lhs, static_cast<unsigned int>( rhs ) );
    }
    template<Operator Op> bool compare( unsigned long lhs, int rhs ) {
        return applyEvaluator<Op>( lhs, static_cast<unsigned int>( rhs ) );
    }
    template<Operator Op> bool compare( unsigned char lhs, int rhs ) {
        return applyEvaluator<Op>( lhs, static_cast<unsigned int>( rhs ) );
    }

    // unsigned X to long
    template<Operator Op> bool compare( unsigned int lhs, long rhs ) {
        return applyEvaluator<Op>( lhs, static_cast<unsigned long>( rhs ) );
    }
    template<Operator Op> bool compare( unsigned long lhs, long rhs ) {
        return applyEvaluator<Op>( lhs, static_cast<unsigned long>( rhs ) );
    }
    template<Operator Op> bool compare( unsigned char lhs, long rhs ) {
        return applyEvaluator<Op>( lhs, static_cast<unsigned long>( rhs ) );
    }

    // int to unsigned X
    template<Operator Op> bool compare( int lhs, unsigned int rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned int>( lhs ), rhs );
    }
    template<Operator Op> bool compare( int lhs, unsigned long rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned int>( lhs ), rhs );
    }
    template<Operator Op> bool compare( int lhs, unsigned char rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned int>( lhs ), rhs );
    }

    // long to unsigned X
    template<Operator Op> bool compare( long lhs, unsigned int rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( long lhs, unsigned long rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( long lhs, unsigned char rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned long>( lhs ), rhs );
    }

    // pointer to long (when comparing against NULL)
    template<Operator Op, typename T> bool compare( long lhs, T* rhs ) {
        return Evaluator<void const*, void const*, Op>::evaluate( reinterpret_cast<void const*>( lhs ), rhs );
    }
    template<Operator Op, typename T> bool compare( T* lhs, long rhs ) {
        return Evaluator<void const*, void const*, Op>::evaluate( lhs, reinterpret_cast<void const*>( rhs ) );
    }

    // pointer to int (when comparing against NULL)
    template<Operator Op, typename T> bool compare( int lhs, T* rhs ) {
        return Evaluator<void const*, void const*, Op>::evaluate( reinterpret_cast<void const*>( lhs ), rhs );
    }
    template<Operator Op, typename T> bool compare( T* lhs, int rhs ) {
        return Evaluator<void const*, void const*, Op>::evaluate( lhs, reinterpret_cast<void const*>( rhs ) );
    }

    // long long to unsigned X
    template<Operator Op> bool compare( long long lhs, unsigned int rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( long long lhs, unsigned long rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( long long lhs, unsigned long long rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( long long lhs, unsigned char rhs ) {
        return applyEvaluator<Op>( static_cast<unsigned long>( lhs ), rhs );
    }

    // unsigned long long to X
    template<Operator Op> bool compare( unsigned long long lhs, int rhs ) {
        return applyEvaluator<Op>( static_cast<long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( unsigned long long lhs, long rhs ) {
        return applyEvaluator<Op>( static_cast<long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( unsigned long long lhs, long long rhs ) {
        return applyEvaluator<Op>( static_cast<long>( lhs ), rhs );
    }
    template<Operator Op> bool compare( unsigned long long lhs, char rhs ) {
        return applyEvaluator<Op>( static_cast<long>( lhs ), rhs );
    }

    // pointer to long long (when comparing against NULL)
    template<Operator Op, typename T> bool compare( long long lhs, T* rhs ) {
        return Evaluator<void const*, void const*, Op>::evaluate( reinterpret_cast<T*>( lhs ), rhs );
    }
    template<Operator Op, typename T> bool compare( T* lhs, long long rhs ) {
        return Evaluator<void const*, void const*, Op>::evaluate( lhs, reinterpret_cast<T*>( rhs ) );
    }

    // pointer to nullptr_t (when comparing against nullptr)
    template<Operator Op, typename T> bool compare( std::nullptr_t, T* rhs ) {
        return Evaluator<void const*, void const*, Op>::evaluate( nullptr, rhs );
    }
    template<Operator Op, typename T> bool compare( T* lhs, std::nullptr_t ) {
        return Evaluator<void const*, void const*, Op>::evaluate( lhs, nullptr );
    }

} // end of namespace Internal
} // end of namespace Catch

#ifdef _MSC_VER
#pragma warning(pop)
#endif

// end catch_evaluate.hpp
// start catch_tostring.h

#include <sstream>
#include <vector>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <string>

#ifdef __OBJC__
// start catch_objc_arc.hpp

#import <Foundation/Foundation.h>

#ifdef __has_feature
#define CATCH_ARC_ENABLED __has_feature(objc_arc)
#else
#define CATCH_ARC_ENABLED 0
#endif

void arcSafeRelease( NSObject* obj );
id performOptionalSelector( id obj, SEL sel );

#if !CATCH_ARC_ENABLED
inline void arcSafeRelease( NSObject* obj ) {
    [obj release];
}
inline id performOptionalSelector( id obj, SEL sel ) {
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED
#define CATCH_ARC_STRONG
#else
inline void arcSafeRelease( NSObject* ){}
inline id performOptionalSelector( id obj, SEL sel ) {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
#endif
    if( [obj respondsToSelector: sel] )
        return [obj performSelector: sel];
#ifdef __clang__
#pragma clang diagnostic pop
#endif
    return nil;
}
#define CATCH_UNSAFE_UNRETAINED __unsafe_unretained
#define CATCH_ARC_STRONG __strong
#endif

// end catch_objc_arc.hpp
#endif

// We need a dummy global operator<< so we can bring it into Catch namespace later
struct Catch_global_namespace_dummy;
std::ostream& operator<<(std::ostream&, Catch_global_namespace_dummy);

namespace Catch {
    // Bring in operator<< from global namespace into Catch namespace
    using ::operator<<;

    namespace Detail {

        extern const std::string unprintableString;

        std::string rawMemoryToString( const void *object, std::size_t size );

        template<typename T>
        std::string rawMemoryToString( const T& object ) {
          return rawMemoryToString( &object, sizeof(object) );
        }

        template<typename T>
        class IsStreamInsertable {
            template<typename SS, typename TT>
            static auto test(int)
                -> decltype(std::declval<SS&>() << std::declval<TT>(), std::true_type());

            template<typename, typename>
            static auto test(...)->std::false_type;

        public:
            static const bool value = decltype(test<std::ostream, const T&>(0))::value;
        };

    } // namespace Detail

    // If we decide for C++14, change these to enable_if_ts
    template <typename T>
    struct StringMaker {
        template <typename Fake = T>
        static
        typename std::enable_if<::Catch::Detail::IsStreamInsertable<Fake>::value, std::string>::type
            convert(const Fake& t) {
                std::ostringstream sstr;
                sstr << t;
                return sstr.str();
        }

        template <typename Fake = T>
        static
        typename std::enable_if<!::Catch::Detail::IsStreamInsertable<Fake>::value, std::string>::type
            convert(const Fake&) {
                return Detail::unprintableString;
        }
    };

    namespace Detail {

        // This function dispatches all stringification requests inside of Catch.
        // Should be preferably called fully qualified, like ::Catch::Detail::stringify
        template <typename T>
        std::string stringify(const T& e) {
            return ::Catch::StringMaker<typename std::remove_cv<typename std::remove_reference<T>::type>::type>::convert(e);
        }

    } // namespace Detail

    // Some predefined specializations

    template<>
    struct StringMaker<std::string> {
        static std::string convert(const std::string& str);
    };
    template<>
    struct StringMaker<std::wstring> {
        static std::string convert(const std::wstring& wstr);
    };

    template<>
    struct StringMaker<char const *> {
        static std::string convert(char const * str);
    };
    template<>
    struct StringMaker<char *> {
        static std::string convert(char * str);
    };
    template<>
    struct StringMaker<wchar_t const *> {
        static std::string convert(wchar_t const * str);
    };
    template<>
    struct StringMaker<wchar_t *> {
        static std::string convert(wchar_t * str);
    };

    template<int SZ>
    struct StringMaker<char[SZ]> {
        static std::string convert(const char* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };
    template<int SZ>
    struct StringMaker<signed char[SZ]> {
        static std::string convert(const char* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };
    template<int SZ>
    struct StringMaker<unsigned char[SZ]> {
        static std::string convert(const char* str) {
            return ::Catch::Detail::stringify(std::string{ str });
        }
    };

    template<>
    struct StringMaker<int> {
        static std::string convert(int value);
    };
    template<>
    struct StringMaker<long> {
        static std::string convert(long value);
    };
    template<>
    struct StringMaker<long long> {
        static std::string convert(long long value);
    };
    template<>
    struct StringMaker<unsigned int> {
        static std::string convert(unsigned int value);
    };
    template<>
    struct StringMaker<unsigned long> {
        static std::string convert(unsigned long value);
    };
    template<>
    struct StringMaker<unsigned long long> {
        static std::string convert(unsigned long long value);
    };

    template<>
    struct StringMaker<bool> {
        static std::string convert(bool b);
    };

    template<>
    struct StringMaker<char> {
        static std::string convert(char c);
    };
    template<>
    struct StringMaker<signed char> {
        static std::string convert(signed char c);
    };
    template<>
    struct StringMaker<unsigned char> {
        static std::string convert(unsigned char c);
    };

    template<>
    struct StringMaker<std::nullptr_t> {
        static std::string convert(std::nullptr_t);
    };

    template<>
    struct StringMaker<float> {
        static std::string convert(float value);
    };
    template<>
    struct StringMaker<double> {
        static std::string convert(double value);
    };

    template <typename T>
    struct StringMaker<T*> {
        template <typename U>
        static std::string convert(U* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

    template <typename R, typename C>
    struct StringMaker<R C::*> {
        static std::string convert(R C::* p) {
            if (p) {
                return ::Catch::Detail::rawMemoryToString(p);
            } else {
                return "nullptr";
            }
        }
    };

    namespace Detail {
        template<typename InputIterator>
        std::string rangeToString(InputIterator first, InputIterator last) {
            std::ostringstream oss;
            oss << "{ ";
            if (first != last) {
                oss << ::Catch::Detail::stringify(*first);
                for (++first; first != last; ++first)
                    oss << ", " << ::Catch::Detail::stringify(*first);
            }
            oss << " }";
            return oss.str();
        }
    }

    template<typename T, typename Allocator>
    struct StringMaker<std::vector<T, Allocator> > {
        static std::string convert( std::vector<T,Allocator> const& v ) {
            return ::Catch::Detail::rangeToString( v.begin(), v.end() );
        }
    };

    // === Pair ===
    template<typename T1, typename T2>
    struct StringMaker<std::pair<T1, T2> > {
        static std::string convert(const std::pair<T1, T2>& pair) {
            std::ostringstream oss;
            oss << "{ "
                << ::Catch::Detail::stringify(pair.first)
                << ", "
                << ::Catch::Detail::stringify(pair.second)
                << " }";
            return oss.str();
        }
    };

    namespace Detail {
        template<
            typename Tuple,
            std::size_t N = 0,
            bool = (N < std::tuple_size<Tuple>::value)
            >
            struct TupleElementPrinter {
            static void print(const Tuple& tuple, std::ostream& os) {
                os << (N ? ", " : " ")
                    << ::Catch::Detail::stringify(std::get<N>(tuple));
                TupleElementPrinter<Tuple, N + 1>::print(tuple, os);
            }
        };

        template<
            typename Tuple,
            std::size_t N
        >
            struct TupleElementPrinter<Tuple, N, false> {
            static void print(const Tuple&, std::ostream&) {}
        };

    }

    template<typename ...Types>
    struct StringMaker<std::tuple<Types...>> {
        static std::string convert(const std::tuple<Types...>& tuple) {
            std::ostringstream os;
            os << '{';
            Detail::TupleElementPrinter<std::tuple<Types...>>::print(tuple, os);
            os << " }";
            return os.str();
        }
    };

    template<typename T>
    struct EnumStringMaker {
        static std::string convert(const T& t) {
            return ::Catch::Detail::stringify(static_cast<typename std::underlying_type<T>::type>(t));
        }
    };

#ifdef __OBJC__
    template<>
    struct StringMaker<NSString*> {
        static std::string convert(NSString* nsstring);
    };
    template<>
    struct StringMaker<NSString* CATCH_ARC_STRONG> {
        static std::string convert(NSString * CATCH_ARC_STRONG nsstring);
    };
    template<>
    struct StringMaker<NSObject *> {
        static std::string convert(NSObject* nsObject);
    };
#endif

} // namespace Catch

// end catch_tostring.h
namespace Catch {

template<typename LhsT, Internal::Operator Op, typename RhsT>
class BinaryExpression;

template<typename ArgT, typename MatcherT>
class MatchExpression;

// Wraps the LHS of an expression and overloads comparison operators
// for also capturing those and RHS (if any)
template<typename T>
class ExpressionLhs : public DecomposedExpression {
public:
    ExpressionLhs( ResultBuilder& rb, T lhs ) : m_rb( rb ), m_lhs( lhs ) {}

    ExpressionLhs( ExpressionLhs const& ) = default;
    ExpressionLhs& operator = ( const ExpressionLhs& ) = delete;

    template<typename RhsT>
    BinaryExpression<T, Internal::IsEqualTo, RhsT const&>
    operator == ( RhsT const& rhs ) {
        return captureExpression<Internal::IsEqualTo>( rhs );
    }

    template<typename RhsT>
    BinaryExpression<T, Internal::IsNotEqualTo, RhsT const&>
    operator != ( RhsT const& rhs ) {
        return captureExpression<Internal::IsNotEqualTo>( rhs );
    }

    template<typename RhsT>
    BinaryExpression<T, Internal::IsLessThan, RhsT const&>
    operator < ( RhsT const& rhs ) {
        return captureExpression<Internal::IsLessThan>( rhs );
    }

    template<typename RhsT>
    BinaryExpression<T, Internal::IsGreaterThan, RhsT const&>
    operator > ( RhsT const& rhs ) {
        return captureExpression<Internal::IsGreaterThan>( rhs );
    }

    template<typename RhsT>
    BinaryExpression<T, Internal::IsLessThanOrEqualTo, RhsT const&>
    operator <= ( RhsT const& rhs ) {
        return captureExpression<Internal::IsLessThanOrEqualTo>( rhs );
    }

    template<typename RhsT>
    BinaryExpression<T, Internal::IsGreaterThanOrEqualTo, RhsT const&>
    operator >= ( RhsT const& rhs ) {
        return captureExpression<Internal::IsGreaterThanOrEqualTo>( rhs );
    }

    BinaryExpression<T, Internal::IsEqualTo, bool> operator == ( bool rhs ) {
        return captureExpression<Internal::IsEqualTo>( rhs );
    }

    BinaryExpression<T, Internal::IsNotEqualTo, bool> operator != ( bool rhs ) {
        return captureExpression<Internal::IsNotEqualTo>( rhs );
    }

    void endExpression() {
        m_truthy = m_lhs ? true : false;
        m_rb
            .setResultType( m_truthy )
            .endExpression( *this );
    }

    void reconstructExpression( std::string& dest ) const override {
        dest = ::Catch::Detail::stringify( m_lhs );
    }

private:
    template<Internal::Operator Op, typename RhsT>
    BinaryExpression<T, Op, RhsT&> captureExpression( RhsT& rhs ) const {
        return BinaryExpression<T, Op, RhsT&>( m_rb, m_lhs, rhs );
    }

    template<Internal::Operator Op>
    BinaryExpression<T, Op, bool> captureExpression( bool rhs ) const {
        return BinaryExpression<T, Op, bool>( m_rb, m_lhs, rhs );
    }

private:
    ResultBuilder& m_rb;
    T m_lhs;
    bool m_truthy = false;
};

template<typename LhsT, Internal::Operator Op, typename RhsT>
class BinaryExpression : public DecomposedExpression {
public:
    BinaryExpression( ResultBuilder& rb, LhsT lhs, RhsT rhs )
        : m_rb( rb ), m_lhs( lhs ), m_rhs( rhs ) {}

    BinaryExpression( BinaryExpression const& ) = default;
    BinaryExpression& operator = ( BinaryExpression const& ) = delete;

    void endExpression() const {
        m_rb
            .setResultType( Internal::compare<Op>( m_lhs, m_rhs ) )
            .endExpression( *this );
    }

    bool isBinaryExpression() const override {
        return true;
    }

    void reconstructExpression( std::string& dest ) const override {
        std::string lhs = ::Catch::Detail::stringify( m_lhs );
        std::string rhs = ::Catch::Detail::stringify( m_rhs );
        char delim = lhs.size() + rhs.size() < 40 &&
                     lhs.find('\n') == std::string::npos &&
                     rhs.find('\n') == std::string::npos ? ' ' : '\n';
        dest.reserve( 7 + lhs.size() + rhs.size() );
                   // 2 for spaces around operator
                   // 2 for operator
                   // 2 for parentheses (conditionally added later)
                   // 1 for negation (conditionally added later)
        dest = lhs;
        dest += delim;
        dest += Internal::operatorName(Op);
        dest += delim;
        dest += rhs;
    }

private:
    ResultBuilder& m_rb;
    LhsT m_lhs;
    RhsT m_rhs;
};

template<typename ArgT, typename MatcherT>
class MatchExpression : public DecomposedExpression {
public:
    MatchExpression( ArgT arg, MatcherT matcher, char const* matcherString )
        : m_arg( arg ), m_matcher( matcher ), m_matcherString( matcherString ) {}

    bool isBinaryExpression() const override {
        return true;
    }

    void reconstructExpression( std::string& dest ) const override {
        std::string matcherAsString = m_matcher.toString();
        dest = ::Catch::Detail::stringify( m_arg );
        dest += ' ';
        if( matcherAsString == Detail::unprintableString )
            dest += m_matcherString;
        else
            dest += matcherAsString;
    }

private:
    ArgT m_arg;
    MatcherT m_matcher;
    char const* m_matcherString;
};

} // end namespace Catch

// end catch_expression_lhs.hpp

namespace Catch {

    template<typename T>
    ExpressionLhs<T const&> ResultBuilder::operator <= ( T const& operand ) {
        return ExpressionLhs<T const&>( *this, operand );
    }

    inline ExpressionLhs<bool> ResultBuilder::operator <= ( bool value ) {
        return ExpressionLhs<bool>( *this, value );
    }

    template<typename ArgT, typename MatcherT>
    void ResultBuilder::captureMatch( ArgT const& arg, MatcherT const& matcher,
                                             char const* matcherString ) {
        MatchExpression<ArgT const&, MatcherT const&> expr( arg, matcher, matcherString );
        setResultType( matcher.match( arg ) );
        endExpression( expr );
    }

} // namespace Catch

// end catch_result_builder.h
// start catch_message.h

#include <string>
#include <sstream>

namespace Catch {

    struct MessageInfo {
        MessageInfo(    std::string const& _macroName,
                        SourceLineInfo const& _lineInfo,
                        ResultWas::OfType _type );

        std::string macroName;
        SourceLineInfo lineInfo;
        ResultWas::OfType type;
        std::string message;
        unsigned int sequence;

        bool operator == ( MessageInfo const& other ) const;
        bool operator < ( MessageInfo const& other ) const;
    private:
        static unsigned int globalCount;
    };

    struct MessageBuilder {
        MessageBuilder( std::string const& macroName,
                        SourceLineInfo const& lineInfo,
                        ResultWas::OfType type );

        template<typename T>
        MessageBuilder& operator << ( T const& value ) {
            m_stream << value;
            return *this;
        }

        MessageInfo m_info;
        std::ostringstream m_stream;
    };

    class ScopedMessage {
    public:
        ScopedMessage( MessageBuilder const& builder );
        ~ScopedMessage();

        MessageInfo m_info;
    };

} // end namespace Catch

// end catch_message.h
// start catch_interfaces_capture.h

#include <string>
// start catch_interfaces_reporter.h

// start catch_section_info.h

// start catch_totals.hpp

#include <cstddef>

namespace Catch {

    struct Counts {
        Counts operator - ( Counts const& other ) const;
        Counts& operator += ( Counts const& other );

        std::size_t total() const;
        bool allPassed() const;
        bool allOk() const;

        std::size_t passed = 0;
        std::size_t failed = 0;
        std::size_t failedButOk = 0;
    };

    struct Totals {

        Totals operator - ( Totals const& other ) const;
        Totals& operator += ( Totals const& other );

        Totals delta( Totals const& prevTotals ) const;

        Counts assertions;
        Counts testCases;
    };
}

// end catch_totals.hpp
#include <string>

namespace Catch {

    struct SectionInfo {
        SectionInfo
            (   SourceLineInfo const& _lineInfo,
                std::string const& _name,
                std::string const& _description = std::string() );

        std::string name;
        std::string description;
        SourceLineInfo lineInfo;
    };

    struct SectionEndInfo {
        SectionEndInfo( SectionInfo const& _sectionInfo, Counts const& _prevAssertions, double _durationInSeconds );

        SectionInfo sectionInfo;
        Counts prevAssertions;
        double durationInSeconds;
    };

} // end namespace Catch

// end catch_section_info.h
// start catch_config.hpp

// start catch_test_spec_parser.hpp

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_test_spec.hpp

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

// start catch_wildcard_pattern.hpp

#include <stdexcept>

namespace Catch
{
    class WildcardPattern {
        enum WildcardPosition {
            NoWildcard = 0,
            WildcardAtStart = 1,
            WildcardAtEnd = 2,
            WildcardAtBothEnds = WildcardAtStart | WildcardAtEnd
        };

    public:

        WildcardPattern( std::string const& pattern, CaseSensitive::Choice caseSensitivity );
        virtual ~WildcardPattern() = default;
        virtual bool matches( std::string const& str ) const;

    private:
        std::string adjustCase( std::string const& str ) const;
        CaseSensitive::Choice m_caseSensitivity;
        WildcardPosition m_wildcard = NoWildcard;
        std::string m_pattern;
    };
}

// end catch_wildcard_pattern.hpp
// start catch_test_case_info.h

#include <string>
#include <vector>
#include <memory>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace Catch {

    struct ITestInvoker;

    struct TestCaseInfo {
        enum SpecialProperties{
            None = 0,
            IsHidden = 1 << 1,
            ShouldFail = 1 << 2,
            MayFail = 1 << 3,
            Throws = 1 << 4,
            NonPortable = 1 << 5,
            Benchmark = 1 << 6
        };

        TestCaseInfo(   std::string const& _name,
                        std::string const& _className,
                        std::string const& _description,
                        std::vector<std::string> const& _tags,
                        SourceLineInfo const& _lineInfo );

        friend void setTags( TestCaseInfo& testCaseInfo, std::vector<std::string> tags );

        bool isHidden() const;
        bool throws() const;
        bool okToFail() const;
        bool expectedToFail() const;

        std::string tagsAsString() const;

        std::string name;
        std::string className;
        std::string description;
        std::vector<std::string> tags;
        std::vector<std::string> lcaseTags;
        SourceLineInfo lineInfo;
        SpecialProperties properties;
    };

    class TestCase : public TestCaseInfo {
    public:

        TestCase( ITestInvoker* testCase, TestCaseInfo const& info );

        TestCase withName( std::string const& _newName ) const;

        void invoke() const;

        TestCaseInfo const& getTestCaseInfo() const;

        bool operator == ( TestCase const& other ) const;
        bool operator < ( TestCase const& other ) const;

    private:
        std::shared_ptr<ITestInvoker> test;
    };

    TestCase makeTestCase(  ITestInvoker* testCase,
                            std::string const& className,
                            std::string const& name,
                            std::string const& description,
                            SourceLineInfo const& lineInfo );
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_case_info.h
#include <string>
#include <vector>
#include <memory>

namespace Catch {

    class TestSpec {
        struct Pattern {
            virtual ~Pattern() = default;
            virtual bool matches( TestCaseInfo const& testCase ) const = 0;
        };
        using PatternPtr = std::shared_ptr<Pattern>;

        class NamePattern : public Pattern {
        public:
            NamePattern( std::string const& name );
            virtual ~NamePattern() = default;
            virtual bool matches( TestCaseInfo const& testCase ) const override;
        private:
            WildcardPattern m_wildcardPattern;
        };

        class TagPattern : public Pattern {
        public:
            TagPattern( std::string const& tag );
            virtual ~TagPattern() = default;
            virtual bool matches( TestCaseInfo const& testCase ) const override;
        private:
            std::string m_tag;
        };

        class ExcludedPattern : public Pattern {
        public:
            ExcludedPattern( PatternPtr const& underlyingPattern );
            virtual ~ExcludedPattern() = default;
            virtual bool matches( TestCaseInfo const& testCase ) const override;
        private:
            PatternPtr m_underlyingPattern;
        };

        struct Filter {
            std::vector<PatternPtr> m_patterns;

            bool matches( TestCaseInfo const& testCase ) const;
        };

    public:
        bool hasFilters() const;
        bool matches( TestCaseInfo const& testCase ) const;

    private:
        std::vector<Filter> m_filters;

        friend class TestSpecParser;
    };
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec.hpp
// start catch_string_manip.h

#include <string>
#include <iosfwd>

namespace Catch {

    bool startsWith( std::string const& s, std::string const& prefix );
    bool startsWith( std::string const& s, char prefix );
    bool endsWith( std::string const& s, std::string const& suffix );
    bool endsWith( std::string const& s, char suffix );
    bool contains( std::string const& s, std::string const& infix );
    void toLowerInPlace( std::string& s );
    std::string toLower( std::string const& s );
    std::string trim( std::string const& str );
    bool replaceInPlace( std::string& str, std::string const& replaceThis, std::string const& withThis );

    struct pluralise {
        pluralise( std::size_t count, std::string const& label );

        friend std::ostream& operator << ( std::ostream& os, pluralise const& pluraliser );

        std::size_t m_count;
        std::string m_label;
    };
}

// end catch_string_manip.h
// start catch_interfaces_tag_alias_registry.h

#include <string>

namespace Catch {

    struct TagAlias;

    struct ITagAliasRegistry {
        virtual ~ITagAliasRegistry();
        // Nullptr if not present
        virtual TagAlias const* find( std::string const& alias ) const = 0;
        virtual std::string expandAliases( std::string const& unexpandedTestSpec ) const = 0;

        static ITagAliasRegistry const& get();
    };

} // end namespace Catch

// end catch_interfaces_tag_alias_registry.h
namespace Catch {

    class TestSpecParser {
        enum Mode{ None, Name, QuotedName, Tag, EscapedName };
        Mode m_mode = None;
        bool m_exclusion = false;
        std::size_t m_start = std::string::npos, m_pos = 0;
        std::string m_arg;
        std::vector<std::size_t> m_escapeChars;
        TestSpec::Filter m_currentFilter;
        TestSpec m_testSpec;
        ITagAliasRegistry const* m_tagAliases = nullptr;

    public:
        TestSpecParser( ITagAliasRegistry const& tagAliases );

        TestSpecParser& parse( std::string const& arg );
        TestSpec testSpec();

    private:
        void visitChar( char c );
        void startNewMode( Mode mode, std::size_t start );
        void escape();
        std::string subString() const;

        template<typename T>
        void addPattern() {
            std::string token = subString();
            for( size_t i = 0; i < m_escapeChars.size(); ++i )
                token = token.substr( 0, m_escapeChars[i]-m_start-i ) + token.substr( m_escapeChars[i]-m_start-i+1 );
            m_escapeChars.clear();
            if( startsWith( token, "exclude:" ) ) {
                m_exclusion = true;
                token = token.substr( 8 );
            }
            if( !token.empty() ) {
                TestSpec::PatternPtr pattern = std::make_shared<T>( token );
                if( m_exclusion )
                    pattern = std::make_shared<TestSpec::ExcludedPattern>( pattern );
                m_currentFilter.m_patterns.push_back( pattern );
            }
            m_exclusion = false;
            m_mode = None;
        }

        void addFilter();
    };
    TestSpec parseTestSpec( std::string const& arg );

} // namespace Catch

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_test_spec_parser.hpp
// start catch_interfaces_config.h

#include <iosfwd>
#include <string>
#include <vector>
#include <memory>

namespace Catch {

    enum class Verbosity {
        Quiet = 0,
        Normal,
        High
    };

    struct WarnAbout { enum What {
        Nothing = 0x00,
        NoAssertions = 0x01
    }; };

    struct ShowDurations { enum OrNot {
        DefaultForReporter,
        Always,
        Never
    }; };
    struct RunTests { enum InWhatOrder {
        InDeclarationOrder,
        InLexicographicalOrder,
        InRandomOrder
    }; };
    struct UseColour { enum YesOrNo {
        Auto,
        Yes,
        No
    }; };

    class TestSpec;

    struct IConfig : NonCopyable {

        virtual ~IConfig();

        virtual bool allowThrows() const = 0;
        virtual std::ostream& stream() const = 0;
        virtual std::string name() const = 0;
        virtual bool includeSuccessfulResults() const = 0;
        virtual bool shouldDebugBreak() const = 0;
        virtual bool warnAboutMissingAssertions() const = 0;
        virtual int abortAfter() const = 0;
        virtual bool showInvisibles() const = 0;
        virtual ShowDurations::OrNot showDurations() const = 0;
        virtual TestSpec const& testSpec() const = 0;
        virtual RunTests::InWhatOrder runOrder() const = 0;
        virtual unsigned int rngSeed() const = 0;
        virtual UseColour::YesOrNo useColour() const = 0;
        virtual std::vector<std::string> const& getSectionsToRun() const = 0;
        virtual Verbosity verbosity() const = 0;
    };

    using IConfigPtr = std::shared_ptr<IConfig const>;
}

// end catch_interfaces_config.h
// start catch_stream.h

// start catch_streambuf.h

#include <streambuf>

namespace Catch {

    class StreamBufBase : public std::streambuf {
    public:
        virtual ~StreamBufBase() noexcept;
    };
}

// end catch_streambuf.h
#include <streambuf>
#include <ostream>
#include <fstream>
#include <memory>

namespace Catch {

    std::ostream& cout();
    std::ostream& cerr();

    struct IStream {
        virtual ~IStream() noexcept;
        virtual std::ostream& stream() const = 0;
    };

    class FileStream : public IStream {
        mutable std::ofstream m_ofs;
    public:
        FileStream( std::string const& filename );
        ~FileStream() noexcept override;
    public: // IStream
        std::ostream& stream() const override;
    };

    class CoutStream : public IStream {
        mutable std::ostream m_os;
    public:
        CoutStream();
        ~CoutStream() noexcept override;

    public: // IStream
        std::ostream& stream() const override;
    };

    class DebugOutStream : public IStream {
        std::unique_ptr<StreamBufBase> m_streamBuf;
        mutable std::ostream m_os;
    public:
        DebugOutStream();
        ~DebugOutStream() noexcept override;

    public: // IStream
        std::ostream& stream() const override;
    };
}

// end catch_stream.h
#include <memory>
#include <vector>
#include <string>

#ifndef CATCH_CONFIG_CONSOLE_WIDTH
#define CATCH_CONFIG_CONSOLE_WIDTH 80
#endif

namespace Catch {

    struct ConfigData {
        bool listTests = false;
        bool listTags = false;
        bool listReporters = false;
        bool listTestNamesOnly = false;

        bool showSuccessfulTests = false;
        bool shouldDebugBreak = false;
        bool noThrow = false;
        bool showHelp = false;
        bool showInvisibles = false;
        bool filenamesAsTags = false;

        int abortAfter = -1;
        unsigned int rngSeed = 0;

        Verbosity verbosity = Verbosity::Normal;
        WarnAbout::What warnings = WarnAbout::Nothing;
        ShowDurations::OrNot showDurations = ShowDurations::DefaultForReporter;
        RunTests::InWhatOrder runOrder = RunTests::InDeclarationOrder;
        UseColour::YesOrNo useColour = UseColour::Auto;

        std::string outputFilename;
        std::string name;
        std::string processName;

        std::vector<std::string> reporterNames;
        std::vector<std::string> testsOrTags;
        std::vector<std::string> sectionsToRun;
    };

    class Config : public IConfig {
        virtual void dummy();
    public:

        Config() = default;
        Config( ConfigData const& data );
        virtual ~Config() = default;

        std::string const& getFilename() const;

        bool listTests() const;
        bool listTestNamesOnly() const;
        bool listTags() const;
        bool listReporters() const;

        std::string getProcessName() const;

        std::vector<std::string> const& getReporterNames() const;
        std::vector<std::string> const& getSectionsToRun() const override;

        virtual TestSpec const& testSpec() const override;

        bool showHelp() const;

        // IConfig interface
        bool allowThrows() const override;
        std::ostream& stream() const override;
        std::string name() const override;
        bool includeSuccessfulResults() const override;
        bool warnAboutMissingAssertions() const override;
        ShowDurations::OrNot showDurations() const override;
        RunTests::InWhatOrder runOrder() const override;
        unsigned int rngSeed() const override;
        UseColour::YesOrNo useColour() const override;
        bool shouldDebugBreak() const override;
        int abortAfter() const override;
        bool showInvisibles() const override;
        Verbosity verbosity() const override;

    private:

        IStream const* openStream();
        ConfigData m_data;

        std::unique_ptr<IStream const> m_stream;
        TestSpec m_testSpec;
    };

} // end namespace Catch

// end catch_config.hpp
// start catch_option.hpp

namespace Catch {

    // An optional type
    template<typename T>
    class Option {
    public:
        Option() : nullableValue( nullptr ) {}
        Option( T const& _value )
        : nullableValue( new( storage ) T( _value ) )
        {}
        Option( Option const& _other )
        : nullableValue( _other ? new( storage ) T( *_other ) : nullptr )
        {}

        ~Option() {
            reset();
        }

        Option& operator= ( Option const& _other ) {
            if( &_other != this ) {
                reset();
                if( _other )
                    nullableValue = new( storage ) T( *_other );
            }
            return *this;
        }
        Option& operator = ( T const& _value ) {
            reset();
            nullableValue = new( storage ) T( _value );
            return *this;
        }

        void reset() {
            if( nullableValue )
                nullableValue->~T();
            nullableValue = nullptr;
        }

        T& operator*() { return *nullableValue; }
        T const& operator*() const { return *nullableValue; }
        T* operator->() { return nullableValue; }
        const T* operator->() const { return nullableValue; }

        T valueOr( T const& defaultValue ) const {
            return nullableValue ? *nullableValue : defaultValue;
        }

        bool some() const { return nullableValue != nullptr; }
        bool none() const { return nullableValue == nullptr; }

        bool operator !() const { return nullableValue == nullptr; }
        explicit operator bool() const {
            return some();
        }

    private:
        T *nullableValue;
        alignas(alignof(T)) char storage[sizeof(T)];
    };

} // end namespace Catch

// end catch_option.hpp
#include <string>
#include <iosfwd>
#include <map>
#include <set>
#include <memory>

namespace Catch {

    struct ReporterConfig {
        explicit ReporterConfig( IConfigPtr const& _fullConfig );

        ReporterConfig( IConfigPtr const& _fullConfig, std::ostream& _stream );

        std::ostream& stream() const;
        IConfigPtr fullConfig() const;

    private:
        std::ostream* m_stream;
        IConfigPtr m_fullConfig;
    };

    struct ReporterPreferences {
        bool shouldRedirectStdOut = false;
    };

    template<typename T>
    struct LazyStat : Option<T> {
        LazyStat& operator=( T const& _value ) {
            Option<T>::operator=( _value );
            used = false;
            return *this;
        }
        void reset() {
            Option<T>::reset();
            used = false;
        }
        bool used = false;
    };

    struct TestRunInfo {
        TestRunInfo( std::string const& _name );
        std::string name;
    };
    struct GroupInfo {
        GroupInfo(  std::string const& _name,
                    std::size_t _groupIndex,
                    std::size_t _groupsCount );

        std::string name;
        std::size_t groupIndex;
        std::size_t groupsCounts;
    };

    struct AssertionStats {
        AssertionStats( AssertionResult const& _assertionResult,
                        std::vector<MessageInfo> const& _infoMessages,
                        Totals const& _totals );

        AssertionStats( AssertionStats const& )              = default;
        AssertionStats( AssertionStats && )                  = default;
        AssertionStats& operator = ( AssertionStats const& ) = default;
        AssertionStats& operator = ( AssertionStats && )     = default;
        virtual ~AssertionStats()                            = default;

        AssertionResult assertionResult;
        std::vector<MessageInfo> infoMessages;
        Totals totals;
    };

    struct SectionStats {
        SectionStats(   SectionInfo const& _sectionInfo,
                        Counts const& _assertions,
                        double _durationInSeconds,
                        bool _missingAssertions );
        SectionStats( SectionStats const& )              = default;
        SectionStats( SectionStats && )                  = default;
        SectionStats& operator = ( SectionStats const& ) = default;
        SectionStats& operator = ( SectionStats && )     = default;
        virtual ~SectionStats()                          = default;

        SectionInfo sectionInfo;
        Counts assertions;
        double durationInSeconds;
        bool missingAssertions;
    };

    struct TestCaseStats {
        TestCaseStats(  TestCaseInfo const& _testInfo,
                        Totals const& _totals,
                        std::string const& _stdOut,
                        std::string const& _stdErr,
                        bool _aborting );

        TestCaseStats( TestCaseStats const& )              = default;
        TestCaseStats( TestCaseStats && )                  = default;
        TestCaseStats& operator = ( TestCaseStats const& ) = default;
        TestCaseStats& operator = ( TestCaseStats && )     = default;
        virtual ~TestCaseStats()                           = default;

        TestCaseInfo testInfo;
        Totals totals;
        std::string stdOut;
        std::string stdErr;
        bool aborting;
    };

    struct TestGroupStats {
        TestGroupStats( GroupInfo const& _groupInfo,
                        Totals const& _totals,
                        bool _aborting );
        TestGroupStats( GroupInfo const& _groupInfo );

        TestGroupStats( TestGroupStats const& )              = default;
        TestGroupStats( TestGroupStats && )                  = default;
        TestGroupStats& operator = ( TestGroupStats const& ) = default;
        TestGroupStats& operator = ( TestGroupStats && )     = default;
        virtual ~TestGroupStats()                            = default;

        GroupInfo groupInfo;
        Totals totals;
        bool aborting;
    };

    struct TestRunStats {
        TestRunStats(   TestRunInfo const& _runInfo,
                        Totals const& _totals,
                        bool _aborting );

        TestRunStats( TestRunStats const& )              = default;
        TestRunStats( TestRunStats && )                  = default;
        TestRunStats& operator = ( TestRunStats const& ) = default;
        TestRunStats& operator = ( TestRunStats && )     = default;
        virtual ~TestRunStats()                          = default;

        TestRunInfo runInfo;
        Totals totals;
        bool aborting;
    };

    struct BenchmarkInfo {
        std::string name;
    };
    struct BenchmarkStats {
        BenchmarkInfo info;
        size_t iterations;
        uint64_t elapsedTimeInNanoseconds;
    };
    class MultipleReporters;

    struct IStreamingReporter {
        virtual ~IStreamingReporter() = default;

        // Implementing class must also provide the following static methods:
        // static std::string getDescription();
        // static std::set<Verbosity> getSupportedVerbosities()

        virtual ReporterPreferences getPreferences() const = 0;

        virtual void noMatchingTestCases( std::string const& spec ) = 0;

        virtual void testRunStarting( TestRunInfo const& testRunInfo ) = 0;
        virtual void testGroupStarting( GroupInfo const& groupInfo ) = 0;

        virtual void testCaseStarting( TestCaseInfo const& testInfo ) = 0;
        virtual void sectionStarting( SectionInfo const& sectionInfo ) = 0;

        // *** experimental ***
        virtual void benchmarkStarting( BenchmarkInfo const& ) {}

        virtual void assertionStarting( AssertionInfo const& assertionInfo ) = 0;

        // The return value indicates if the messages buffer should be cleared:
        virtual bool assertionEnded( AssertionStats const& assertionStats ) = 0;

        // *** experimental ***
        virtual void benchmarkEnded( BenchmarkStats const& ) {}

        virtual void sectionEnded( SectionStats const& sectionStats ) = 0;
        virtual void testCaseEnded( TestCaseStats const& testCaseStats ) = 0;
        virtual void testGroupEnded( TestGroupStats const& testGroupStats ) = 0;
        virtual void testRunEnded( TestRunStats const& testRunStats ) = 0;

        virtual void skipTest( TestCaseInfo const& testInfo ) = 0;

        virtual bool isMulti() const;
    };
    using IStreamingReporterPtr = std::unique_ptr<IStreamingReporter>;

    struct IReporterFactory {
        virtual ~IReporterFactory() = default;
        virtual IStreamingReporterPtr create( ReporterConfig const& config ) const = 0;
        virtual std::string getDescription() const = 0;
    };
    using IReporterFactoryPtr = std::shared_ptr<IReporterFactory>;

    struct IReporterRegistry {
        using FactoryMap = std::map<std::string, IReporterFactoryPtr>;
        using Listeners = std::vector<IReporterFactoryPtr>;

        virtual ~IReporterRegistry() = default;
        virtual IStreamingReporterPtr create( std::string const& name, IConfigPtr const& config ) const = 0;
        virtual FactoryMap const& getFactories() const = 0;
        virtual Listeners const& getListeners() const = 0;
    };

    void addReporter( IStreamingReporterPtr& existingReporter, IStreamingReporterPtr&& additionalReporter );

} // end namespace Catch

// end catch_interfaces_reporter.h

namespace Catch {

    class TestCase;
    class AssertionResult;
    struct AssertionInfo;
    struct SectionInfo;
    struct SectionEndInfo;
    struct MessageInfo;
    class ScopedMessageBuilder;
    struct Counts;

    struct IResultCapture {

        virtual ~IResultCapture();

        virtual void assertionStarting( AssertionInfo const& info ) = 0;
        virtual void assertionEnded( AssertionResult const& result ) = 0;
        virtual bool sectionStarted(    SectionInfo const& sectionInfo,
                                        Counts& assertions ) = 0;
        virtual void sectionEnded( SectionEndInfo const& endInfo ) = 0;
        virtual void sectionEndedEarly( SectionEndInfo const& endInfo ) = 0;

        virtual void benchmarkStarting( BenchmarkInfo const& info ) = 0;
        virtual void benchmarkEnded( BenchmarkStats const& stats ) = 0;

        virtual void pushScopedMessage( MessageInfo const& message ) = 0;
        virtual void popScopedMessage( MessageInfo const& message ) = 0;

        virtual std::string getCurrentTestName() const = 0;
        virtual const AssertionResult* getLastResult() const = 0;

        virtual void exceptionEarlyReported() = 0;

        virtual void handleFatalErrorCondition( std::string const& message ) = 0;

        virtual bool lastAssertionPassed() = 0;
        virtual void assertionPassed() = 0;
        virtual void assertionRun() = 0;
    };

    IResultCapture& getResultCapture();
}

// end catch_interfaces_capture.h
// start catch_debugger.h

// start catch_platform.h

#ifdef __APPLE__
# include <TargetConditionals.h>
# if TARGET_OS_MAC == 1
#  define CATCH_PLATFORM_MAC
# elif TARGET_OS_IPHONE == 1
#  define CATCH_PLATFORM_IPHONE
# endif

#elif defined(linux) || defined(__linux) || defined(__linux__)
#  define CATCH_PLATFORM_LINUX

#elif defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER)
#  define CATCH_PLATFORM_WINDOWS
#endif

// end catch_platform.h
#include <string>

namespace Catch{

    bool isDebuggerActive();
    void writeToDebugConsole( std::string const& text );
}

#ifdef CATCH_PLATFORM_MAC

    #define CATCH_TRAP() __asm__("int $3\n" : : ) /* NOLINT */

#elif defined(CATCH_PLATFORM_LINUX)
    // If we can use inline assembler, do it because this allows us to break
    // directly at the location of the failing check instead of breaking inside
    // raise() called from it, i.e. one stack frame below.
    #if defined(__GNUC__) && (defined(__i386) || defined(__x86_64))
        #define CATCH_TRAP() asm volatile ("int $3") /* NOLINT */
    #else // Fall back to the generic way.
        #include <signal.h>

        #define CATCH_TRAP() raise(SIGTRAP)
    #endif
#elif defined(_MSC_VER)
    #define CATCH_TRAP() __debugbreak()
#elif defined(__MINGW32__)
    extern "C" __declspec(dllimport) void __stdcall DebugBreak();
    #define CATCH_TRAP() DebugBreak()
#endif

#ifdef CATCH_TRAP
    #define CATCH_BREAK_INTO_DEBUGGER() if( Catch::isDebuggerActive() ) { CATCH_TRAP(); }
#else
    #define CATCH_BREAK_INTO_DEBUGGER() Catch::alwaysTrue();
#endif

// end catch_debugger.h
// start catch_interfaces_runner.h

namespace Catch {
    class TestCase;

    struct IRunner {
        virtual ~IRunner();
        virtual bool aborting() const = 0;
    };
}

// end catch_interfaces_runner.h
#if defined(CATCH_CONFIG_FAST_COMPILE)
///////////////////////////////////////////////////////////////////////////////
// We can speedup compilation significantly by breaking into debugger lower in
// the callstack, because then we don't have to expand CATCH_BREAK_INTO_DEBUGGER
// macro in each assertion
#define INTERNAL_CATCH_REACT( resultBuilder ) \
    resultBuilder.react();

///////////////////////////////////////////////////////////////////////////////
// Another way to speed-up compilation is to omit local try-catch for REQUIRE*
// macros.
// This can potentially cause false negative, if the test code catches
// the exception before it propagates back up to the runner.
#define INTERNAL_CATCH_TEST_NO_TRY( macroName, resultDisposition, expr ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #expr, resultDisposition ); \
        __catchResult.setExceptionGuard(); \
        CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
        ( __catchResult <= expr ).endExpression(); \
        CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS \
        __catchResult.unsetExceptionGuard(); \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::isTrue( false && static_cast<bool>( !!(expr) ) ) ) // expr here is never evaluated at runtime but it forces the compiler to give it a look
// The double negation silences MSVC's C4800 warning, the static_cast forces short-circuit evaluation if the type has overloaded &&.
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define INTERNAL_CHECK_THAT_NO_TRY( macroName, matcher, resultDisposition, arg ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #arg ", " #matcher, resultDisposition ); \
        __catchResult.setExceptionGuard(); \
        __catchResult.captureMatch( arg, matcher, #matcher ); \
        __catchResult.unsetExceptionGuard(); \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#else
///////////////////////////////////////////////////////////////////////////////
// In the event of a failure works out if the debugger needs to be invoked
// and/or an exception thrown and takes appropriate action.
// This needs to be done as a macro so the debugger will stop in the user
// source code rather than in Catch library code
#define INTERNAL_CATCH_REACT( resultBuilder ) \
    if( resultBuilder.shouldDebugBreak() ) CATCH_BREAK_INTO_DEBUGGER(); \
    resultBuilder.react();
#endif

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TEST( macroName, resultDisposition, ... ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #__VA_ARGS__, resultDisposition ); \
        try { \
            CATCH_INTERNAL_SUPPRESS_PARENTHESES_WARNINGS \
            ( __catchResult <= __VA_ARGS__ ).endExpression(); \
            CATCH_INTERNAL_UNSUPPRESS_PARENTHESES_WARNINGS \
        } \
        catch( ... ) { \
            __catchResult.useActiveException( resultDisposition ); \
        } \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::isTrue( false && static_cast<bool>( !!(__VA_ARGS__) ) ) ) // the expression here is never evaluated at runtime but it forces the compiler to give it a look
    // The double negation silences MSVC's C4800 warning, the static_cast forces short-circuit evaluation if the type has overloaded &&.

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_IF( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_ELSE( macroName, resultDisposition, ... ) \
    INTERNAL_CATCH_TEST( macroName, resultDisposition, __VA_ARGS__ ); \
    if( !Catch::getResultCapture().lastAssertionPassed() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_NO_THROW( macroName, resultDisposition, ... ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #__VA_ARGS__, resultDisposition ); \
        try { \
            static_cast<void>(__VA_ARGS__); \
            __catchResult.captureResult( Catch::ResultWas::Ok ); \
        } \
        catch( ... ) { \
            __catchResult.useActiveException( resultDisposition ); \
        } \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS( macroName, resultDisposition, ... ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #__VA_ARGS__, resultDisposition); \
        if( __catchResult.allowThrows() ) \
            try { \
                static_cast<void>(__VA_ARGS__); \
                __catchResult.captureResult( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( ... ) { \
                __catchResult.captureExpectedException( "" ); \
            } \
        else \
            __catchResult.captureResult( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_AS( macroName, exceptionType, resultDisposition, expr ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #expr ", " #exceptionType, resultDisposition ); \
        if( __catchResult.allowThrows() ) \
            try { \
                static_cast<void>(expr); \
                __catchResult.captureResult( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( exceptionType const& ) { \
                __catchResult.captureResult( Catch::ResultWas::Ok ); \
            } \
            catch( ... ) { \
                __catchResult.useActiveException( resultDisposition ); \
            } \
        else \
            __catchResult.captureResult( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_MSG( macroName, messageType, resultDisposition, ... ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, "", resultDisposition ); \
        __catchResult << __VA_ARGS__ + ::Catch::StreamEndStop(); \
        __catchResult.captureResult( messageType ); \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_INFO( macroName, log ) \
    Catch::ScopedMessage INTERNAL_CATCH_UNIQUE_NAME( scopedMessage ) = Catch::MessageBuilder( macroName, CATCH_INTERNAL_LINEINFO, Catch::ResultWas::Info ) << log;

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CHECK_THAT( macroName, matcher, resultDisposition, arg ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #arg ", " #matcher, resultDisposition ); \
        try { \
            __catchResult.captureMatch( arg, matcher, #matcher ); \
        } catch( ... ) { \
            __catchResult.useActiveException( resultDisposition ); \
        } \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_STR_MATCHES( macroName, resultDisposition, matcher, ... ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #__VA_ARGS__ ", " #matcher, resultDisposition); \
        if( __catchResult.allowThrows() ) \
            try { \
                static_cast<void>(__VA_ARGS__); \
                __catchResult.captureResult( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( ... ) { \
                __catchResult.captureExpectedException( matcher ); \
            } \
        else \
            __catchResult.captureResult( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_THROWS_MATCHES( macroName, exceptionType, resultDisposition, matcher, expr ) \
    do { \
        Catch::ResultBuilder __catchResult( macroName, CATCH_INTERNAL_LINEINFO, #expr ", " #exceptionType ", " #matcher, resultDisposition ); \
        if( __catchResult.allowThrows() ) \
            try { \
                static_cast<void>(expr); \
                __catchResult.captureResult( Catch::ResultWas::DidntThrowException ); \
            } \
            catch( exceptionType const& ex ) { \
                __catchResult.captureMatch( ex, matcher, #matcher ); \
            } \
            catch( ... ) { \
                __catchResult.useActiveException( resultDisposition ); \
            } \
        else \
            __catchResult.captureResult( Catch::ResultWas::Ok ); \
        INTERNAL_CATCH_REACT( __catchResult ) \
    } while( Catch::alwaysFalse() )
#endif // CATCH_CONFIG_DISABLE_MATCHERS

// end catch_capture.hpp
// start catch_section.h

// start catch_timer.h

#include <stdint.h>

namespace Catch {

    auto getCurrentNanosecondsSinceEpoch() -> uint64_t;
    auto getEstimatedClockResolution() -> uint64_t;

    class Timer {
        uint64_t m_nanoseconds = 0;
    public:
        void start();
        auto getElapsedNanoseconds() const -> unsigned int;
        auto getElapsedMicroseconds() const -> unsigned int;
        auto getElapsedMilliseconds() const -> unsigned int;
        auto getElapsedSeconds() const -> double;
    };

} // namespace Catch

// end catch_timer.h
#include <string>

namespace Catch {

    class Section : NonCopyable {
    public:
        Section( SectionInfo const& info );
        ~Section();

        // This indicates whether the section should be executed or not
        explicit operator bool() const;

    private:
        SectionInfo m_info;

        std::string m_name;
        Counts m_assertions;
        bool m_sectionIncluded;
        Timer m_timer;
    };

} // end namespace Catch

    #define INTERNAL_CATCH_SECTION( ... ) \
        if( Catch::Section const& INTERNAL_CATCH_UNIQUE_NAME( catch_internal_Section ) = Catch::SectionInfo( CATCH_INTERNAL_LINEINFO, __VA_ARGS__ ) )

// end catch_section.h
// start catch_benchmark.h

#include <cstdint>
#include <string>

namespace Catch {

    class BenchmarkLooper {

        std::string m_name;
        size_t m_count = 0;
        size_t m_iterationsToRun = 1;
        uint64_t m_resolution;
        Timer m_timer;
    public:
        // Keep most of this inline as it's on the code path that is being timed
        BenchmarkLooper( StringRef name )
        :   m_name( name.c_str() ),
            m_resolution( getEstimatedClockResolution()*10 )
        {
            reportStart();
            m_timer.start();
        }

        explicit operator bool() {
            if( m_count < m_iterationsToRun )
                return true;
            return needsMoreIterations();
        }

        void increment() {
            ++m_count;
        }

        void reportStart() const;
        auto needsMoreIterations() -> bool;
    };

} // end namespace Catch

#define BENCHMARK( name ) \
    for( Catch::BenchmarkLooper looper( name ); looper; looper.increment() )

// end catch_benchmark.h
// start catch_interfaces_exception.h

#include <string>
#include <vector>

// start catch_interfaces_registry_hub.h

#include <string>
#include <memory>

namespace Catch {

    class TestCase;
    struct ITestCaseRegistry;
    struct IExceptionTranslatorRegistry;
    struct IExceptionTranslator;
    struct IReporterRegistry;
    struct IReporterFactory;
    struct ITagAliasRegistry;
    class StartupExceptionRegistry;

    using IReporterFactoryPtr = std::shared_ptr<IReporterFactory>;

    struct IRegistryHub {
        virtual ~IRegistryHub();

        virtual IReporterRegistry const& getReporterRegistry() const = 0;
        virtual ITestCaseRegistry const& getTestCaseRegistry() const = 0;
        virtual ITagAliasRegistry const& getTagAliasRegistry() const = 0;

        virtual IExceptionTranslatorRegistry& getExceptionTranslatorRegistry() = 0;

        virtual StartupExceptionRegistry const& getStartupExceptionRegistry() const = 0;
    };

    struct IMutableRegistryHub {
        virtual ~IMutableRegistryHub();
        virtual void registerReporter( std::string const& name, IReporterFactoryPtr const& factory ) = 0;
        virtual void registerListener( IReporterFactoryPtr const& factory ) = 0;
        virtual void registerTest( TestCase const& testInfo ) = 0;
        virtual void registerTranslator( const IExceptionTranslator* translator ) = 0;
        virtual void registerTagAlias( std::string const& alias, std::string const& tag, SourceLineInfo const& lineInfo ) = 0;
        virtual void registerStartupException() noexcept = 0;
    };

    IRegistryHub& getRegistryHub();
    IMutableRegistryHub& getMutableRegistryHub();
    void cleanUp();
    std::string translateActiveException();

}

// end catch_interfaces_registry_hub.h
namespace Catch {
    using exceptionTranslateFunction = std::string(*)();

    struct IExceptionTranslator;
    using ExceptionTranslators = std::vector<std::unique_ptr<IExceptionTranslator const>>;

    struct IExceptionTranslator {
        virtual ~IExceptionTranslator();
        virtual std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const = 0;
    };

    struct IExceptionTranslatorRegistry {
        virtual ~IExceptionTranslatorRegistry();

        virtual std::string translateActiveException() const = 0;
    };

    class ExceptionTranslatorRegistrar {
        template<typename T>
        class ExceptionTranslator : public IExceptionTranslator {
        public:

            ExceptionTranslator( std::string(*translateFunction)( T& ) )
            : m_translateFunction( translateFunction )
            {}

            std::string translate( ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd ) const override {
                try {
                    if( it == itEnd )
                        throw;
                    else
                        return (*it)->translate( it+1, itEnd );
                }
                catch( T& ex ) {
                    return m_translateFunction( ex );
                }
            }

        protected:
            std::string(*m_translateFunction)( T& );
        };

    public:
        template<typename T>
        ExceptionTranslatorRegistrar( std::string(*translateFunction)( T& ) ) {
            getMutableRegistryHub().registerTranslator
                ( new ExceptionTranslator<T>( translateFunction ) );
        }
    };
}

///////////////////////////////////////////////////////////////////////////////
#define INTERNAL_CATCH_TRANSLATE_EXCEPTION2( translatorName, signature ) \
    static std::string translatorName( signature ); \
    namespace{ Catch::ExceptionTranslatorRegistrar INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionRegistrar )( &translatorName ); }\
    static std::string translatorName( signature )

#define INTERNAL_CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION2( INTERNAL_CATCH_UNIQUE_NAME( catch_internal_ExceptionTranslator ), signature )

// end catch_interfaces_exception.h
// start catch_approx.hpp

#include <algorithm>
#include <cmath>

#include <type_traits>

namespace Catch {
namespace Detail {

    class Approx {
    public:
        explicit Approx ( double value );

        static Approx custom();

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx operator()( T const& value ) {
            Approx approx( static_cast<double>(value) );
            approx.epsilon( m_epsilon );
            approx.margin( m_margin );
            approx.scale( m_scale );
            return approx;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        explicit Approx( T const& value ): Approx(static_cast<double>(value))
        {}

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator == ( const T& lhs, Approx const& rhs ) {
            // Thanks to Richard Harris for his help refining this formula
            auto lhs_v = static_cast<double>(lhs);
            bool relativeOK = std::fabs(lhs_v - rhs.m_value) < rhs.m_epsilon * (rhs.m_scale + (std::max)(std::fabs(lhs_v), std::fabs(rhs.m_value)));
            if (relativeOK) {
                return true;
            }
            return std::fabs(lhs_v - rhs.m_value) < rhs.m_margin;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator == ( Approx const& lhs, const T& rhs ) {
            return operator==( rhs, lhs );
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator != ( T const& lhs, Approx const& rhs ) {
            return !operator==( lhs, rhs );
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator != ( Approx const& lhs, T const& rhs ) {
            return !operator==( rhs, lhs );
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator <= ( T const& lhs, Approx const& rhs ) {
            return static_cast<double>(lhs) < rhs.m_value || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator <= ( Approx const& lhs, T const& rhs ) {
            return lhs.m_value < static_cast<double>(rhs) || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator >= ( T const& lhs, Approx const& rhs ) {
            return static_cast<double>(lhs) > rhs.m_value || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        friend bool operator >= ( Approx const& lhs, T const& rhs ) {
            return lhs.m_value > static_cast<double>(rhs) || lhs == rhs;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx& epsilon( T const& newEpsilon ) {
            m_epsilon = static_cast<double>(newEpsilon);
            return *this;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx& margin( T const& newMargin ) {
            m_margin = static_cast<double>(newMargin);
            return *this;
        }

        template <typename T, typename = typename std::enable_if<std::is_constructible<double, T>::value>::type>
        Approx& scale( T const& newScale ) {
            m_scale = static_cast<double>(newScale);
            return *this;
        }

        std::string toString() const;

    private:
        double m_epsilon;
        double m_margin;
        double m_scale;
        double m_value;
    };
}

template<>
struct StringMaker<Catch::Detail::Approx> {
    static std::string convert(Catch::Detail::Approx const& value);
};

} // end namespace Catch

// end catch_approx.hpp
// start catch_matchers_string.h

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

#include <string>

namespace Catch {
namespace Matchers {

    namespace StdString {

        struct CasedString
        {
            CasedString( std::string const& str, CaseSensitive::Choice caseSensitivity );
            std::string adjustString( std::string const& str ) const;
            std::string caseSensitivitySuffix() const;

            CaseSensitive::Choice m_caseSensitivity;
            std::string m_str;
        };

        struct StringMatcherBase : MatcherBase<std::string> {
            StringMatcherBase( std::string const& operation, CasedString const& comparator );
            std::string describe() const override;

            CasedString m_comparator;
            std::string m_operation;
        };

        struct EqualsMatcher : StringMatcherBase {
            EqualsMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };
        struct ContainsMatcher : StringMatcherBase {
            ContainsMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };
        struct StartsWithMatcher : StringMatcherBase {
            StartsWithMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };
        struct EndsWithMatcher : StringMatcherBase {
            EndsWithMatcher( CasedString const& comparator );
            bool match( std::string const& source ) const override;
        };

    } // namespace StdString

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    StdString::EqualsMatcher Equals( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::ContainsMatcher Contains( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::EndsWithMatcher EndsWith( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );
    StdString::StartsWithMatcher StartsWith( std::string const& str, CaseSensitive::Choice caseSensitivity = CaseSensitive::Yes );

} // namespace Matchers
} // namespace Catch

#endif // CATCH_CONFIG_DISABLE_MATCHERS

// end catch_matchers_string.h
// start catch_matchers_vector.h

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

namespace Catch {
namespace Matchers {

    namespace Vector {

        template<typename T>
        struct ContainsElementMatcher : MatcherBase<std::vector<T>, T> {

            ContainsElementMatcher(T const &comparator) : m_comparator( comparator) {}

            bool match(std::vector<T> const &v) const override {
                for (auto const& el : v) {
                    if (el == m_comparator) {
                        return true;
                    }
                }
                return false;
            }

            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            T const& m_comparator;
        };

        template<typename T>
        struct ContainsMatcher : MatcherBase<std::vector<T>, std::vector<T> > {

            ContainsMatcher(std::vector<T> const &comparator) : m_comparator( comparator ) {}

            bool match(std::vector<T> const &v) const override {
                // !TBD: see note in EqualsMatcher
                if (m_comparator.size() > v.size())
                    return false;
                for (auto const& comparator : m_comparator) {
                    auto present = false;
                    for (const auto& el : v) {
                        if (el == comparator) {
                            present = true;
                            break;
                        }
                    }
                    if (!present) {
                        return false;
                    }
                }
                return true;
            }
            std::string describe() const override {
                return "Contains: " + ::Catch::Detail::stringify( m_comparator );
            }

            std::vector<T> const& m_comparator;
        };

        template<typename T>
        struct EqualsMatcher : MatcherBase<std::vector<T>, std::vector<T> > {

            EqualsMatcher(std::vector<T> const &comparator) : m_comparator( comparator ) {}

            bool match(std::vector<T> const &v) const override {
                // !TBD: This currently works if all elements can be compared using !=
                // - a more general approach would be via a compare template that defaults
                // to using !=. but could be specialised for, e.g. std::vector<T> etc
                // - then just call that directly
                if (m_comparator.size() != v.size())
                    return false;
                for (size_t i = 0; i < v.size(); ++i)
                    if (m_comparator[i] != v[i])
                        return false;
                return true;
            }
            std::string describe() const override {
                return "Equals: " + ::Catch::Detail::stringify( m_comparator );
            }
            std::vector<T> const& m_comparator;
        };

    } // namespace Vector

    // The following functions create the actual matcher objects.
    // This allows the types to be inferred

    template<typename T>
    Vector::ContainsMatcher<T> Contains( std::vector<T> const& comparator ) {
        return Vector::ContainsMatcher<T>( comparator );
    }

    template<typename T>
    Vector::ContainsElementMatcher<T> VectorContains( T const& comparator ) {
        return Vector::ContainsElementMatcher<T>( comparator );
    }

    template<typename T>
    Vector::EqualsMatcher<T> Equals( std::vector<T> const& comparator ) {
        return Vector::EqualsMatcher<T>( comparator );
    }

} // namespace Matchers
} // namespace Catch

#endif // CATCH_CONFIG_DISABLE_MATCHERS

// end catch_matchers_vector.h
// These files are included here so the single_include script doesn't put them
// in the conditionally compiled sections

#ifdef __OBJC__
// start catch_objc.hpp

#import <objc/runtime.h>

#include <string>

// NB. Any general catch headers included here must be included
// in catch.hpp first to make sure they are included by the single
// header for non obj-usage

///////////////////////////////////////////////////////////////////////////////
// This protocol is really only here for (self) documenting purposes, since
// all its methods are optional.
@protocol OcFixture

@optional

-(void) setUp;
-(void) tearDown;

@end

namespace Catch {

    class OcMethod : public ITestInvoker {

    public:
        OcMethod( Class cls, SEL sel ) : m_cls( cls ), m_sel( sel ) {}

        virtual void invoke() const {
            id obj = [[m_cls alloc] init];

            performOptionalSelector( obj, @selector(setUp)  );
            performOptionalSelector( obj, m_sel );
            performOptionalSelector( obj, @selector(tearDown)  );

            arcSafeRelease( obj );
        }
    private:
        virtual ~OcMethod() {}

        Class m_cls;
        SEL m_sel;
    };

    namespace Detail{

        inline std::string getAnnotation(   Class cls,
                                            std::string const& annotationName,
                                            std::string const& testCaseName ) {
            NSString* selStr = [[NSString alloc] initWithFormat:@"Catch_%s_%s", annotationName.c_str(), testCaseName.c_str()];
            SEL sel = NSSelectorFromString( selStr );
            arcSafeRelease( selStr );
            id value = performOptionalSelector( cls, sel );
            if( value )
                return [(NSString*)value UTF8String];
            return "";
        }
    }

    inline size_t registerTestMethods() {
        size_t noTestMethods = 0;
        int noClasses = objc_getClassList( nullptr, 0 );

        Class* classes = (CATCH_UNSAFE_UNRETAINED Class *)malloc( sizeof(Class) * noClasses);
        objc_getClassList( classes, noClasses );

        for( int c = 0; c < noClasses; c++ ) {
            Class cls = classes[c];
            {
                u_int count;
                Method* methods = class_copyMethodList( cls, &count );
                for( u_int m = 0; m < count ; m++ ) {
                    SEL selector = method_getName(methods[m]);
                    std::string methodName = sel_getName(selector);
                    if( startsWith( methodName, "Catch_TestCase_" ) ) {
                        std::string testCaseName = methodName.substr( 15 );
                        std::string name = Detail::getAnnotation( cls, "Name", testCaseName );
                        std::string desc = Detail::getAnnotation( cls, "Description", testCaseName );
                        const char* className = class_getName( cls );

                        getMutableRegistryHub().registerTest( makeTestCase( new OcMethod( cls, selector ), className, name.c_str(), desc.c_str(), SourceLineInfo() ) );
                        noTestMethods++;
                    }
                }
                free(methods);
            }
        }
        return noTestMethods;
    }

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

    namespace Matchers {
        namespace Impl {
        namespace NSStringMatchers {

            struct StringHolder : MatcherBase<NSString*>{
                StringHolder( NSString* substr ) : m_substr( [substr copy] ){}
                StringHolder( StringHolder const& other ) : m_substr( [other.m_substr copy] ){}
                StringHolder() {
                    arcSafeRelease( m_substr );
                }

                bool match( NSString* arg ) const override {
                    return false;
                }

                NSString* m_substr;
            };

            struct Equals : StringHolder {
                Equals( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &&
                            [str isEqualToString:m_substr];
                }

                std::string describe() const override {
                    return "equals string: " + Catch::toString( m_substr );
                }
            };

            struct Contains : StringHolder {
                Contains( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const {
                    return  (str != nil || m_substr == nil ) &&
                            [str rangeOfString:m_substr].location != NSNotFound;
                }

                std::string describe() const override {
                    return "contains string: " + Catch::toString( m_substr );
                }
            };

            struct StartsWith : StringHolder {
                StartsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &&
                            [str rangeOfString:m_substr].location == 0;
                }

                std::string describe() const override {
                    return "starts with: " + Catch::toString( m_substr );
                }
            };
            struct EndsWith : StringHolder {
                EndsWith( NSString* substr ) : StringHolder( substr ){}

                bool match( NSString* str ) const override {
                    return  (str != nil || m_substr == nil ) &&
                            [str rangeOfString:m_substr].location == [str length] - [m_substr length];
                }

                std::string describe() const override {
                    return "ends with: " + Catch::toString( m_substr );
                }
            };

        } // namespace NSStringMatchers
        } // namespace Impl

        inline Impl::NSStringMatchers::Equals
            Equals( NSString* substr ){ return Impl::NSStringMatchers::Equals( substr ); }

        inline Impl::NSStringMatchers::Contains
            Contains( NSString* substr ){ return Impl::NSStringMatchers::Contains( substr ); }

        inline Impl::NSStringMatchers::StartsWith
            StartsWith( NSString* substr ){ return Impl::NSStringMatchers::StartsWith( substr ); }

        inline Impl::NSStringMatchers::EndsWith
            EndsWith( NSString* substr ){ return Impl::NSStringMatchers::EndsWith( substr ); }

    } // namespace Matchers

    using namespace Matchers;

#endif // CATCH_CONFIG_DISABLE_MATCHERS

} // namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define OC_TEST_CASE( name, desc )\
+(NSString*) INTERNAL_CATCH_UNIQUE_NAME( Catch_Name_test ) \
{\
return @ name; \
}\
+(NSString*) INTERNAL_CATCH_UNIQUE_NAME( Catch_Description_test ) \
{ \
return @ desc; \
} \
-(void) INTERNAL_CATCH_UNIQUE_NAME( Catch_TestCase_test )

// end catch_objc.hpp
#endif

#ifdef CATCH_IMPL
// start catch_impl.hpp

// Collect all the implementation files together here
// These are the equivalent of what would usually be cpp files

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif

// start catch_notimplemented_exception.h

#include <exception>

namespace Catch {

    class NotImplementedException : public std::exception
    {
    public:
        NotImplementedException( SourceLineInfo const& lineInfo );

        virtual ~NotImplementedException() noexcept = default;

        virtual const char* what() const noexcept override;

    private:
        std::string m_what;
        SourceLineInfo m_lineInfo;
    };

} // end namespace Catch

///////////////////////////////////////////////////////////////////////////////
#define CATCH_NOT_IMPLEMENTED throw Catch::NotImplementedException( CATCH_INTERNAL_LINEINFO )

// end catch_notimplemented_exception.h
// Temporary hack to fix separately provided reporters
// start catch_reporter_bases.hpp

// start catch_enforce.h

#include <sstream>
#include <stdexcept>

#define CATCH_PREPARE_EXCEPTION( type, msg ) \
    type( static_cast<std::ostringstream&&>( std::ostringstream() << msg ).str() )
#define CATCH_INTERNAL_ERROR( msg ) \
    throw CATCH_PREPARE_EXCEPTION( std::logic_error, CATCH_INTERNAL_LINEINFO << ": Internal Catch error: " << msg);
#define CATCH_ERROR( msg ) \
    throw CATCH_PREPARE_EXCEPTION( std::domain_error, msg )
#define CATCH_ENFORCE( condition, msg ) \
    do{ if( !(condition) ) CATCH_ERROR( msg ); } while(false)

// end catch_enforce.h
#include <algorithm>
#include <cstring>
#include <cfloat>
#include <cstdio>
#include <assert.h>
#include <memory>

namespace Catch {
    void prepareExpandedExpression(AssertionResult& result);

    // Returns double formatted as %.3f (format expected on output)
    std::string getFormattedDuration( double duration );

    template<typename DerivedT>
    struct StreamingReporterBase : IStreamingReporter {

        StreamingReporterBase( ReporterConfig const& _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            CATCH_ENFORCE( DerivedT::getSupportedVerbosities().count( m_config->verbosity() ), "Verbosity level not supported by this reporter" );
        }

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set<Verbosity> getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        ~StreamingReporterBase() override = default;

        void noMatchingTestCases(std::string const&) override {}

        void testRunStarting(TestRunInfo const& _testRunInfo) override {
            currentTestRunInfo = _testRunInfo;
        }
        void testGroupStarting(GroupInfo const& _groupInfo) override {
            currentGroupInfo = _groupInfo;
        }

        void testCaseStarting(TestCaseInfo const& _testInfo) override  {
            currentTestCaseInfo = _testInfo;
        }
        void sectionStarting(SectionInfo const& _sectionInfo) override {
            m_sectionStack.push_back(_sectionInfo);
        }

        void sectionEnded(SectionStats const& /* _sectionStats */) override {
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const& /* _testCaseStats */) override {
            currentTestCaseInfo.reset();
        }
        void testGroupEnded(TestGroupStats const& /* _testGroupStats */) override {
            currentGroupInfo.reset();
        }
        void testRunEnded(TestRunStats const& /* _testRunStats */) override {
            currentTestCaseInfo.reset();
            currentGroupInfo.reset();
            currentTestRunInfo.reset();
        }

        void skipTest(TestCaseInfo const&) override {
            // Don't do anything with this by default.
            // It can optionally be overridden in the derived class.
        }

        IConfigPtr m_config;
        std::ostream& stream;

        LazyStat<TestRunInfo> currentTestRunInfo;
        LazyStat<GroupInfo> currentGroupInfo;
        LazyStat<TestCaseInfo> currentTestCaseInfo;

        std::vector<SectionInfo> m_sectionStack;
        ReporterPreferences m_reporterPrefs;
    };

    template<typename DerivedT>
    struct CumulativeReporterBase : IStreamingReporter {
        template<typename T, typename ChildNodeT>
        struct Node {
            explicit Node( T const& _value ) : value( _value ) {}
            virtual ~Node() {}

            using ChildNodes = std::vector<std::shared_ptr<ChildNodeT>>;
            T value;
            ChildNodes children;
        };
        struct SectionNode {
            explicit SectionNode(SectionStats const& _stats) : stats(_stats) {}
            virtual ~SectionNode() = default;

            bool operator == (SectionNode const& other) const {
                return stats.sectionInfo.lineInfo == other.stats.sectionInfo.lineInfo;
            }
            bool operator == (std::shared_ptr<SectionNode> const& other) const {
                return operator==(*other);
            }

            SectionStats stats;
            using ChildSections = std::vector<std::shared_ptr<SectionNode>>;
            using Assertions = std::vector<AssertionStats>;
            ChildSections childSections;
            Assertions assertions;
            std::string stdOut;
            std::string stdErr;
        };

        struct BySectionInfo {
            BySectionInfo( SectionInfo const& other ) : m_other( other ) {}
            BySectionInfo( BySectionInfo const& other ) : m_other( other.m_other ) {}
            bool operator() (std::shared_ptr<SectionNode> const& node) const {
                return ((node->stats.sectionInfo.name == m_other.name) &&
                        (node->stats.sectionInfo.lineInfo == m_other.lineInfo));
            }
            void operator=(BySectionInfo const&) = delete;

        private:
            SectionInfo const& m_other;
        };

        using TestCaseNode = Node<TestCaseStats, SectionNode>;
        using TestGroupNode = Node<TestGroupStats, TestCaseNode>;
        using TestRunNode = Node<TestRunStats, TestGroupNode>;

        CumulativeReporterBase( ReporterConfig const& _config )
        :   m_config( _config.fullConfig() ),
            stream( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = false;
            CATCH_ENFORCE( DerivedT::getSupportedVerbosities().count( m_config->verbosity() ), "Verbosity level not supported by this reporter" );
        }
        ~CumulativeReporterBase() override = default;

        ReporterPreferences getPreferences() const override {
            return m_reporterPrefs;
        }

        static std::set<Verbosity> getSupportedVerbosities() {
            return { Verbosity::Normal };
        }

        void testRunStarting( TestRunInfo const& ) override {}
        void testGroupStarting( GroupInfo const& ) override {}

        void testCaseStarting( TestCaseInfo const& ) override {}

        void sectionStarting( SectionInfo const& sectionInfo ) override {
            SectionStats incompleteStats( sectionInfo, Counts(), 0, false );
            std::shared_ptr<SectionNode> node;
            if( m_sectionStack.empty() ) {
                if( !m_rootSection )
                    m_rootSection = std::make_shared<SectionNode>( incompleteStats );
                node = m_rootSection;
            }
            else {
                SectionNode& parentNode = *m_sectionStack.back();
                typename SectionNode::ChildSections::const_iterator it =
                    std::find_if(   parentNode.childSections.begin(),
                                    parentNode.childSections.end(),
                                    BySectionInfo( sectionInfo ) );
                if( it == parentNode.childSections.end() ) {
                    node = std::make_shared<SectionNode>( incompleteStats );
                    parentNode.childSections.push_back( node );
                }
                else
                    node = *it;
            }
            m_sectionStack.push_back( node );
            m_deepestSection = std::move(node);
        }

        void assertionStarting(AssertionInfo const&) override {}

        bool assertionEnded(AssertionStats const& assertionStats) override {
            assert(!m_sectionStack.empty());
            SectionNode& sectionNode = *m_sectionStack.back();
            sectionNode.assertions.push_back(assertionStats);
            // AssertionResult holds a pointer to a temporary DecomposedExpression,
            // which getExpandedExpression() calls to build the expression string.
            // Our section stack copy of the assertionResult will likely outlive the
            // temporary, so it must be expanded or discarded now to avoid calling
            // a destroyed object later.
            prepareExpandedExpression(sectionNode.assertions.back().assertionResult);
            return true;
        }
        void sectionEnded(SectionStats const& sectionStats) override {
            assert(!m_sectionStack.empty());
            SectionNode& node = *m_sectionStack.back();
            node.stats = sectionStats;
            m_sectionStack.pop_back();
        }
        void testCaseEnded(TestCaseStats const& testCaseStats) override {
            auto node = std::make_shared<TestCaseNode>(testCaseStats);
            assert(m_sectionStack.size() == 0);
            node->children.push_back(m_rootSection);
            m_testCases.push_back(node);
            m_rootSection.reset();

            assert(m_deepestSection);
            m_deepestSection->stdOut = testCaseStats.stdOut;
            m_deepestSection->stdErr = testCaseStats.stdErr;
        }
        void testGroupEnded(TestGroupStats const& testGroupStats) override {
            auto node = std::make_shared<TestGroupNode>(testGroupStats);
            node->children.swap(m_testCases);
            m_testGroups.push_back(node);
        }
        void testRunEnded(TestRunStats const& testRunStats) override {
            auto node = std::make_shared<TestRunNode>(testRunStats);
            node->children.swap(m_testGroups);
            m_testRuns.push_back(node);
            testRunEndedCumulative();
        }
        virtual void testRunEndedCumulative() = 0;

        void skipTest(TestCaseInfo const&) override {}

        IConfigPtr m_config;
        std::ostream& stream;
        std::vector<AssertionStats> m_assertions;
        std::vector<std::vector<std::shared_ptr<SectionNode>>> m_sections;
        std::vector<std::shared_ptr<TestCaseNode>> m_testCases;
        std::vector<std::shared_ptr<TestGroupNode>> m_testGroups;

        std::vector<std::shared_ptr<TestRunNode>> m_testRuns;

        std::shared_ptr<SectionNode> m_rootSection;
        std::shared_ptr<SectionNode> m_deepestSection;
        std::vector<std::shared_ptr<SectionNode>> m_sectionStack;
        ReporterPreferences m_reporterPrefs;
    };

    template<char C>
    char const* getLineOfChars() {
        static char line[CATCH_CONFIG_CONSOLE_WIDTH] = {0};
        if( !*line ) {
            std::memset( line, C, CATCH_CONFIG_CONSOLE_WIDTH-1 );
            line[CATCH_CONFIG_CONSOLE_WIDTH-1] = 0;
        }
        return line;
    }
    inline char const* getBoxCharsAcross() {
        static char line[CATCH_CONFIG_CONSOLE_WIDTH] = {0};
        if( !*line ) {
            std::memset( line, '-', CATCH_CONFIG_CONSOLE_WIDTH-1 );
            line[CATCH_CONFIG_CONSOLE_WIDTH-1] = 0;
            line[0] = '+';
            line[CATCH_CONFIG_CONSOLE_WIDTH-2] = '+';
        }
        return line;
    }

    struct TestEventListenerBase : StreamingReporterBase<TestEventListenerBase> {
        TestEventListenerBase( ReporterConfig const& _config );

        void assertionStarting(AssertionInfo const&) override;
        bool assertionEnded(AssertionStats const&) override;
    };

} // end namespace Catch

// end catch_reporter_bases.hpp
// start catch_reporter_registrars.hpp

namespace Catch {

    template<typename T>
    class ReporterRegistrar {

        class ReporterFactory : public IReporterFactory {

            virtual IStreamingReporterPtr create( ReporterConfig const& config ) const override {
                return std::unique_ptr<T>( new T( config ) );
            }

            virtual std::string getDescription() const override {
                return T::getDescription();
            }
        };

    public:

        ReporterRegistrar( std::string const& name ) {
            getMutableRegistryHub().registerReporter( name, std::make_shared<ReporterFactory>() );
        }
    };

    template<typename T>
    class ListenerRegistrar {

        class ListenerFactory : public IReporterFactory {

            virtual IStreamingReporterPtr create( ReporterConfig const& config ) const override {
                return std::make_shared<T>( config );
            }
            virtual std::string getDescription() const override {
                return std::string();
            }
        };

    public:

        ListenerRegistrar() {
            getMutableRegistryHub().registerListener( std::make_shared<ListenerFactory>() );
        }
    };
}

#define INTERNAL_CATCH_REGISTER_REPORTER( name, reporterType ) \
    namespace{ Catch::ReporterRegistrar<reporterType> catch_internal_RegistrarFor##reporterType( name ); }

// Deprecated - use the form without INTERNAL_
#define INTERNAL_CATCH_REGISTER_LISTENER( listenerType ) \
    namespace{ Catch::ListenerRegistrar<listenerType> catch_internal_RegistrarFor##listenerType; }

#define CATCH_REGISTER_LISTENER( listenerType ) \
    namespace{ Catch::ListenerRegistrar<listenerType> catch_internal_RegistrarFor##listenerType; }

// end catch_reporter_registrars.hpp
//

// start catch_leak_detector.h

namespace Catch {

    struct LeakDetector {
        LeakDetector();
    };

}
// end catch_leak_detector.h
// start catch_session.hpp

// start catch_commandline.hpp

// start catch_clara.h

// Use Catch's value for console width (store Clara's off to the side, if present)
#ifdef CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#undef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#endif
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_CONFIG_CONSOLE_WIDTH-1

// start clara.hpp
// v1.0
// See https://github.com/philsquared/Clara


#ifndef CATCH_CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_CONFIG_CONSOLE_WIDTH 80
#endif

// ----------- #included from clara_textflow.hpp -----------

// TextFlowCpp
//
// A single-header library for wrapping and laying out basic text, by Phil Nash
//
// This work is licensed under the BSD 2-Clause license.
// See the accompanying LICENSE file, or the one at https://opensource.org/licenses/BSD-2-Clause
//
// This project is hosted at https://github.com/philsquared/textflowcpp


#include <cassert>
#include <ostream>
#include <sstream>
#include <vector>

#ifndef CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH 80
#endif

namespace Catch { namespace clara { namespace TextFlow {

    inline auto isWhitespace( char c ) -> bool {
        static std::string chars = " \t\n\r";
        return chars.find( c ) != std::string::npos;
    }
    inline auto isBreakableBefore( char c ) -> bool {
        static std::string chars = "[({<|";
        return chars.find( c ) != std::string::npos;
    }
    inline auto isBreakableAfter( char c ) -> bool {
        static std::string chars = "])}>.,:;*+-=&/\\";
        return chars.find( c ) != std::string::npos;
    }

    class Columns;

    class Column {
        std::vector<std::string> m_strings;
        size_t m_width = CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH;
        size_t m_indent = 0;
        size_t m_initialIndent = std::string::npos;

    public:
        class iterator {
            friend Column;

            Column const& m_column;
            size_t m_stringIndex = 0;
            size_t m_pos = 0;

            size_t m_len = 0;
            size_t m_end = 0;
            bool m_suffix = false;

            iterator( Column const& column, size_t stringIndex )
            :   m_column( column ),
                m_stringIndex( stringIndex )
            {}

            auto line() const -> std::string const& { return m_column.m_strings[m_stringIndex]; }

            auto isBoundary( size_t at ) const -> bool {
                assert( at > 0 );
                assert( at <= line().size() );

                return at == line().size() ||
                       ( isWhitespace( line()[at] ) && !isWhitespace( line()[at-1] ) ) ||
                       isBreakableBefore( line()[at] ) ||
                       isBreakableAfter( line()[at-1] );
            }

            void calcLength() {
                assert( m_stringIndex < m_column.m_strings.size() );

                m_suffix = false;
                auto width = m_column.m_width-indent();
                m_end = m_pos;
                while( m_end < line().size() && line()[m_end] != '\n' )
                    ++m_end;

                if( m_end < m_pos + width ) {
                    m_len = m_end - m_pos;
                }
                else {
                    size_t len = width;
                    while (len > 0 && !isBoundary(m_pos + len))
                        --len;
                    while (len > 0 && isWhitespace( line()[m_pos + len - 1] ))
                        --len;

                    if (len > 0) {
                        m_len = len;
                    } else {
                        m_suffix = true;
                        m_len = width - 1;
                    }
                }
            }

            auto indent() const -> size_t {
                auto initial = m_pos == 0 && m_stringIndex == 0 ? m_column.m_initialIndent : std::string::npos;
                return initial == std::string::npos ? m_column.m_indent : initial;
            }

            auto addIndentAndSuffix(std::string const &plain) const -> std::string {
                return std::string( indent(), ' ' ) + (m_suffix ? plain + "-" : plain);
            }

        public:
            explicit iterator( Column const& column ) : m_column( column ) {
                assert( m_column.m_width > m_column.m_indent );
                assert( m_column.m_initialIndent == std::string::npos || m_column.m_width > m_column.m_initialIndent );
                calcLength();
                if( m_len == 0 )
                    m_stringIndex++; // Empty string
            }

            auto operator *() const -> std::string {
                assert( m_stringIndex < m_column.m_strings.size() );
                assert( m_pos < m_end );
                if( m_pos + m_column.m_width < m_end )
                    return addIndentAndSuffix(line().substr(m_pos, m_len));
                else
                    return addIndentAndSuffix(line().substr(m_pos, m_end - m_pos));
            }

            auto operator ++() -> iterator& {
                m_pos += m_len;
                if( m_pos < line().size() && line()[m_pos] == '\n' )
                    m_pos += 1;
                else
                    while( m_pos < line().size() && isWhitespace( line()[m_pos] ) )
                        ++m_pos;

                if( m_pos == line().size() ) {
                    m_pos = 0;
                    ++m_stringIndex;
                }
                if( m_stringIndex < m_column.m_strings.size() )
                    calcLength();
                return *this;
            }
            auto operator ++(int) -> iterator {
                iterator prev( *this );
                operator++();
                return prev;
            }

            auto operator ==( iterator const& other ) const -> bool {
                return
                    m_pos == other.m_pos &&
                    m_stringIndex == other.m_stringIndex &&
                    &m_column == &other.m_column;
            }
            auto operator !=( iterator const& other ) const -> bool {
                return !operator==( other );
            }
        };
        using const_iterator = iterator;

        explicit Column( std::string const& text ) { m_strings.push_back( text ); }

        auto width( size_t newWidth ) -> Column& {
            assert( newWidth > 0 );
            m_width = newWidth;
            return *this;
        }
        auto indent( size_t newIndent ) -> Column& {
            m_indent = newIndent;
            return *this;
        }
        auto initialIndent( size_t newIndent ) -> Column& {
            m_initialIndent = newIndent;
            return *this;
        }

        auto width() const -> size_t { return m_width; }
        auto begin() const -> iterator { return iterator( *this ); }
        auto end() const -> iterator { return { *this, m_strings.size() }; }

        inline friend std::ostream& operator << ( std::ostream& os, Column const& col ) {
            bool first = true;
            for( auto line : col ) {
                if( first )
                    first = false;
                else
                    os << "\n";
                os <<  line;
            }
            return os;
        }

        auto operator + ( Column const& other ) -> Columns;

        auto toString() const -> std::string {
            std::ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    class Spacer : public Column {

    public:
        explicit Spacer( size_t spaceWidth ) : Column( "" ) {
            width( spaceWidth );
        }
    };

    class Columns {
        std::vector<Column> m_columns;

    public:

        class iterator {
            friend Columns;
            struct EndTag {};

            std::vector<Column> const& m_columns;
            std::vector<Column::iterator> m_iterators;
            size_t m_activeIterators;

            iterator( Columns const& columns, EndTag )
            :   m_columns( columns.m_columns ),
                m_activeIterators( 0 )
            {
                m_iterators.reserve( m_columns.size() );

                for( auto const& col : m_columns )
                    m_iterators.push_back( col.end() );
            }

        public:
            explicit iterator( Columns const& columns )
            :   m_columns( columns.m_columns ),
                m_activeIterators( m_columns.size() )
            {
                m_iterators.reserve( m_columns.size() );

                for( auto const& col : m_columns )
                    m_iterators.push_back( col.begin() );
            }

            auto operator ==( iterator const& other ) const -> bool {
                return m_iterators == other.m_iterators;
            }
            auto operator !=( iterator const& other ) const -> bool {
                return m_iterators != other.m_iterators;
            }
            auto operator *() const -> std::string {
                std::string row, padding;

                for( size_t i = 0; i < m_columns.size(); ++i ) {
                    auto width = m_columns[i].width();
                    if( m_iterators[i] != m_columns[i].end() ) {
                        std::string col = *m_iterators[i];
                        row += padding + col;
                        if( col.size() < width )
                            padding = std::string( width - col.size(), ' ' );
                        else
                            padding = "";
                    }
                    else {
                        padding += std::string( width, ' ' );
                    }
                }
                return row;
            }
            auto operator ++() -> iterator& {
                for( size_t i = 0; i < m_columns.size(); ++i ) {
                    if (m_iterators[i] != m_columns[i].end())
                        ++m_iterators[i];
                }
                return *this;
            }
            auto operator ++(int) -> iterator {
                iterator prev( *this );
                operator++();
                return prev;
            }
        };
        using const_iterator = iterator;

        auto begin() const -> iterator { return iterator( *this ); }
        auto end() const -> iterator { return { *this, iterator::EndTag() }; }

        auto operator += ( Column const& col ) -> Columns& {
            m_columns.push_back( col );
            return *this;
        }
        auto operator + ( Column const& col ) -> Columns {
            Columns combined = *this;
            combined += col;
            return combined;
        }

        inline friend std::ostream& operator << ( std::ostream& os, Columns const& cols ) {

            bool first = true;
            for( auto line : cols ) {
                if( first )
                    first = false;
                else
                    os << "\n";
                os << line;
            }
            return os;
        }

        auto toString() const -> std::string {
            std::ostringstream oss;
            oss << *this;
            return oss.str();
        }
    };

    inline auto Column::operator + ( Column const& other ) -> Columns {
        Columns cols;
        cols += *this;
        cols += other;
        return cols;
    }
}}} // namespace Catch::clara::TextFlow

// ----------- end of #include from clara_textflow.hpp -----------
// ........... back in clara.hpp

#include <memory>
#include <set>
#include <algorithm>

#if !defined(CLARA_PLATFORM_WINDOWS) && ( defined(WIN32) || defined(__WIN32__) || defined(_WIN32) || defined(_MSC_VER) )
#define CLARA_PLATFORM_WINDOWS

#endif

namespace Catch { namespace clara {
namespace detail {

    // Traits for extracting arg and return type of lambdas (for single argument lambdas)
    template<typename L>
    struct UnaryLambdaTraits : UnaryLambdaTraits<decltype(&L::operator())> {};

    template<typename ClassT, typename ReturnT, typename... Args>
    struct UnaryLambdaTraits<ReturnT(ClassT::*)(Args...) const> {
        static const bool isValid = false;
    };

    template<typename ClassT, typename ReturnT, typename ArgT>
    struct UnaryLambdaTraits<ReturnT(ClassT::*)(ArgT) const> {
        static const bool isValid = true;
        using ArgType = typename std::remove_const<typename std::remove_reference<ArgT>::type>::type;;
        using ReturnType = ReturnT;
    };

    class TokenStream;

    // Transport for raw args (copied from main args, or supplied via init list for testing)
    class Args {
        friend TokenStream;
        std::string m_exeName;
        std::vector<std::string> m_args;

    public:
        Args(int argc, char *argv[]) {
            m_exeName = argv[0];
            for (int i = 1; i < argc; ++i)
                m_args.push_back(argv[i]);
        }

        Args(std::initializer_list<std::string> args)
        :   m_exeName( *args.begin() ),
            m_args( args.begin()+1, args.end() )
        {}

        auto exeName() const -> std::string {
            return m_exeName;
        }
    };

    // Wraps a token coming from a token stream. These may not directly correspond to strings as a single string
    // may encode an option + its argument if the : or = form is used
    enum class TokenType {
        Option, Argument
    };
    struct Token {
        TokenType type;
        std::string token;
    };

    // Abstracts iterators into args as a stream of tokens, with option arguments uniformly handled
    class TokenStream {
        using Iterator = std::vector<std::string>::const_iterator;
        Iterator it;
        Iterator itEnd;
        std::vector<Token> m_tokenBuffer;

        void loadBuffer() {
            m_tokenBuffer.resize(0);

            // Skip any empty strings
            while (it != itEnd && it->empty())
                ++it;

            if (it != itEnd) {
                auto const &next = *it;
                if (next[0] == '-' || next[0] == '/') {
                    auto delimiterPos = next.find_first_of(" :=");
                    if (delimiterPos != std::string::npos) {
                        m_tokenBuffer.push_back({TokenType::Option, next.substr(0, delimiterPos)});
                        m_tokenBuffer.push_back({TokenType::Argument, next.substr(delimiterPos + 1)});
                    } else {
                        if (next[1] != '-' && next.size() > 2) {
                            std::string opt = "- ";
                            for (size_t i = 1; i < next.size(); ++i) {
                                opt[1] = next[i];
                                m_tokenBuffer.push_back({TokenType::Option, opt});
                            }
                        } else {
                            m_tokenBuffer.push_back({TokenType::Option, next});
                        }
                    }
                } else {
                    m_tokenBuffer.push_back({TokenType::Argument, next});
                }
            }
        }

    public:
        explicit TokenStream(Args const &args) : TokenStream(args.m_args.begin(), args.m_args.end()) {}

        TokenStream(Iterator it, Iterator itEnd) : it(it), itEnd(itEnd) {
            loadBuffer();
        }

        explicit operator bool() const {
            return !m_tokenBuffer.empty() || it != itEnd;
        }

        auto count() const -> size_t { return m_tokenBuffer.size() + (itEnd - it); }

        auto operator*() const -> Token {
            assert(!m_tokenBuffer.empty());
            return m_tokenBuffer.front();
        }

        auto operator->() const -> Token const * {
            assert(!m_tokenBuffer.empty());
            return &m_tokenBuffer.front();
        }

        auto operator++() -> TokenStream & {
            if (m_tokenBuffer.size() >= 2) {
                m_tokenBuffer.erase(m_tokenBuffer.begin());
            } else {
                if (it != itEnd)
                    ++it;
                loadBuffer();
            }
            return *this;
        }
    };

    class ResultBase {
    public:
        enum Type {
            Ok, LogicError, RuntimeError
        };

    protected:
        ResultBase(Type type) : m_type(type) {}
        virtual ~ResultBase() = default;

        virtual void enforceOk() const = 0;

        Type m_type;
    };

    template<typename T>
    class ResultValueBase : public ResultBase {
    public:
        auto value() const -> T const & {
            enforceOk();
            return m_value;
        }

    protected:
        ResultValueBase(Type type) : ResultBase(type) {}

        ResultValueBase(ResultValueBase const &other) : ResultBase(other) {
            if (m_type == ResultBase::Ok)
                new(&m_value) T(other.m_value);
        }

        ResultValueBase(Type, T const &value) : ResultBase(Ok) {
            new(&m_value) T(value);
        }

        auto operator=(ResultValueBase const &other) -> ResultValueBase & {
            if (m_type == ResultBase::Ok)
                m_value.~T();
            ResultBase::operator=(other);
            if (m_type == ResultBase::Ok)
                new(&m_value) T(other.m_value);
            return *this;
        }

        ~ResultValueBase() {
            if (m_type == Ok)
                m_value.~T();
        }

        union {
            T m_value;
        };
    };

    template<>
    class ResultValueBase<void> : public ResultBase {
    protected:
        using ResultBase::ResultBase;
    };

    template<typename T = void>
    class BasicResult : public ResultValueBase<T> {
    public:
        template<typename U>
        explicit BasicResult(BasicResult<U> const &other)
                :   ResultValueBase<T>(other.type()),
                    m_errorMessage(other.errorMessage()) {
            assert(type() != ResultBase::Ok);
        }

        static auto ok() -> BasicResult { return {ResultBase::Ok}; }

        template<typename U>
        static auto ok(U const &value) -> BasicResult { return {ResultBase::Ok, value}; }

        static auto logicError(std::string const &message) -> BasicResult { return {ResultBase::LogicError, message}; }

        static auto runtimeError(std::string const &message) -> BasicResult {
            return {ResultBase::RuntimeError, message};
        }

        explicit operator bool() const { return m_type == ResultBase::Ok; }

        auto type() const -> ResultBase::Type { return m_type; }

        auto errorMessage() const -> std::string { return m_errorMessage; }

    protected:
        virtual void enforceOk() const {
            // !TBD: If no exceptions, std::terminate here or something
            switch (m_type) {
                case ResultBase::LogicError:
                    throw std::logic_error(m_errorMessage);
                case ResultBase::RuntimeError:
                    throw std::runtime_error(m_errorMessage);
                case ResultBase::Ok:
                    break;
            }
        }

        std::string m_errorMessage; // Only populated if resultType is an error

        BasicResult(ResultBase::Type type, std::string const &message)
                : ResultValueBase<T>(type),
                  m_errorMessage(message) {
            assert(m_type != ResultBase::Ok);
        }

        using ResultValueBase<T>::ResultValueBase;
        using ResultBase::m_type;
    };

    enum class ParseResultType {
        Matched, NoMatch, ShortCircuitAll, ShortCircuitSame
    };

    class ParseState {
    public:

        ParseState(ParseResultType type, TokenStream const &remainingTokens)
                : m_type(type),
                  m_remainingTokens(remainingTokens) {}

        auto type() const -> ParseResultType { return m_type; }

        auto remainingTokens() const -> TokenStream { return m_remainingTokens; }

    private:
        ParseResultType m_type;
        TokenStream m_remainingTokens;
    };

    using Result = BasicResult<void>;
    using ParserResult = BasicResult<ParseResultType>;
    using InternalParseResult = BasicResult<ParseState>;

    struct HelpColumns {
        std::string left;
        std::string right;
    };

    template<typename T>
    inline auto convertInto(std::string const &source, T& target) -> ParserResult {
        std::stringstream ss;
        ss << source;
        ss >> target;
        if (ss.fail())
            return ParserResult::runtimeError("Unable to convert '" + source + "' to destination type");
        else
            return ParserResult::ok(ParseResultType::Matched);
    }
    inline auto convertInto(std::string const &source, std::string& target) -> ParserResult {
        target = source;
        return ParserResult::ok(ParseResultType::Matched);
    }
    inline auto convertInto(std::string const &source, bool &target) -> ParserResult {
        std::string srcLC = source;
        std::transform(srcLC.begin(), srcLC.end(), srcLC.begin(), [](char c) { return static_cast<char>( ::tolower(c) ); } );
        if (srcLC == "y" || srcLC == "1" || srcLC == "true" || srcLC == "yes" || srcLC == "on")
            target = true;
        else if (srcLC == "n" || srcLC == "0" || srcLC == "false" || srcLC == "no" || srcLC == "off")
            target = false;
        else
            return ParserResult::runtimeError("Expected a boolean value but did not recognise: '" + source + "'");
        return ParserResult::ok(ParseResultType::Matched);
    }

    struct BoundRefBase {
        BoundRefBase() = default;

        BoundRefBase(BoundRefBase const &) = delete;

        BoundRefBase(BoundRefBase &&) = delete;

        BoundRefBase &operator=(BoundRefBase const &) = delete;

        BoundRefBase &operator=(BoundRefBase &&) = delete;

        virtual ~BoundRefBase() = default;

        virtual auto isFlag() const -> bool = 0;

        virtual auto isContainer() const -> bool { return false; }

        virtual auto setValue(std::string const &arg) -> ParserResult = 0;

        virtual auto setFlag(bool flag) -> ParserResult = 0;
    };

    struct BoundValueRefBase : BoundRefBase {
        auto isFlag() const -> bool override { return false; }

        auto setFlag(bool) -> ParserResult override {
            return ParserResult::logicError("Flags can only be set on boolean fields");
        }
    };

    struct BoundFlagRefBase : BoundRefBase {
        auto isFlag() const -> bool override { return true; }

        auto setValue(std::string const &arg) -> ParserResult override {
            bool flag;
            auto result = convertInto(arg, flag);
            if (result)
                setFlag(flag);
            return result;
        }
    };

    template<typename T>
    struct BoundRef : BoundValueRefBase {
        T &m_ref;

        explicit BoundRef(T &ref) : m_ref(ref) {}

        auto setValue(std::string const &arg) -> ParserResult override {
            return convertInto(arg, m_ref);
        }
    };

    template<typename T>
    struct BoundRef<std::vector<T>> : BoundValueRefBase {
        std::vector<T> &m_ref;

        explicit BoundRef(std::vector<T> &ref) : m_ref(ref) {}

        auto isContainer() const -> bool override { return true; }

        auto setValue(std::string const &arg) -> ParserResult override {
            T temp;
            auto result = convertInto(arg, temp);
            if (result)
                m_ref.push_back(temp);
            return result;
        }
    };

    struct BoundFlagRef : BoundFlagRefBase {
        bool &m_ref;

        explicit BoundFlagRef(bool &ref) : m_ref(ref) {}

        auto setFlag(bool flag) -> ParserResult override {
            m_ref = flag;
            return ParserResult::ok(ParseResultType::Matched);
        }
    };

    template<typename ReturnType>
    struct LambdaInvoker {
        static_assert(std::is_same<ReturnType, ParserResult>::value, "Lambda must return void or clara::ParserResult");

        template<typename L, typename ArgType>
        static auto invoke(L const &lambda, ArgType const &arg) -> ParserResult {
            return lambda(arg);
        }
    };

    template<>
    struct LambdaInvoker<void> {
        template<typename L, typename ArgType>
        static auto invoke(L const &lambda, ArgType const &arg) -> ParserResult {
            lambda(arg);
            return ParserResult::ok(ParseResultType::Matched);
        }
    };

    template<typename ArgType, typename L>
    inline auto invokeLambda(L const &lambda, std::string const &arg) -> ParserResult {
        ArgType temp;
        auto result = convertInto(arg, temp);
        return !result
               ? result
               : LambdaInvoker<typename UnaryLambdaTraits<L>::ReturnType>::invoke(lambda, temp);
    };

    template<typename L>
    struct BoundLambda : BoundValueRefBase {
        L m_lambda;

        static_assert( UnaryLambdaTraits<L>::isValid, "Supplied lambda must take exactly one argument" );
        explicit BoundLambda(L const &lambda) : m_lambda(lambda) {}

        auto setValue(std::string const &arg) -> ParserResult override {
            return invokeLambda<typename UnaryLambdaTraits<L>::ArgType>(m_lambda, arg);
        }
    };

    template<typename L>
    struct BoundFlagLambda : BoundFlagRefBase {
        L m_lambda;

        static_assert( UnaryLambdaTraits<L>::isValid, "Supplied lambda must take exactly one argument" );
        static_assert( std::is_same<typename UnaryLambdaTraits<L>::ArgType, bool>::value, "flags must be boolean" );

        explicit BoundFlagLambda(L const &lambda) : m_lambda(lambda) {}

        auto setFlag(bool flag) -> ParserResult override {
            return LambdaInvoker<typename UnaryLambdaTraits<L>::ReturnType>::invoke(m_lambda, flag);
        }
    };

    enum class Optionality {
        Optional, Required
    };

    struct Parser;

    class ParserBase {
    public:
        virtual ~ParserBase() = default;
        virtual auto validate() const -> Result { return Result::ok(); }
        virtual auto parse( std::string const& exeName, TokenStream const &tokens) const -> InternalParseResult  = 0;
        virtual auto cardinality() const -> size_t { return 1; }

        auto parse(Args const &args) const -> InternalParseResult {
            return parse( args.exeName(), TokenStream(args));
        }
    };

    template<typename DerivedT>
    class ComposableParserImpl : public ParserBase {
    public:
        template<typename T>
        auto operator+(T const &other) const -> Parser;
    };

    // Common code and state for Args and Opts
    template<typename DerivedT>
    class ParserRefImpl : public ComposableParserImpl<DerivedT> {
    protected:
        Optionality m_optionality = Optionality::Optional;
        std::shared_ptr<BoundRefBase> m_ref;
        std::string m_hint;
        std::string m_description;

        explicit ParserRefImpl(std::shared_ptr<BoundRefBase> const &ref) : m_ref(ref) {}

    public:
        template<typename T>
        ParserRefImpl(T &ref, std::string const &hint) : m_ref(std::make_shared<BoundRef<T>>(ref)), m_hint(hint) {}

        template<typename LambdaT>
        ParserRefImpl(LambdaT const &ref, std::string const &hint) : m_ref(std::make_shared<BoundLambda<LambdaT>>(ref)),
                                                                     m_hint(hint) {}

        auto operator()(std::string const &description) -> DerivedT & {
            m_description = description;
            return static_cast<DerivedT &>( *this );
        }

        auto optional() -> DerivedT & {
            m_optionality = Optionality::Optional;
            return static_cast<DerivedT &>( *this );
        };

        auto required() -> DerivedT & {
            m_optionality = Optionality::Required;
            return static_cast<DerivedT &>( *this );
        };

        auto isOptional() const -> bool {
            return m_optionality == Optionality::Optional;
        }

        auto cardinality() const -> size_t override {
            if (m_ref->isContainer())
                return 0;
            else
                return 1;
        }

        auto hint() const -> std::string { return m_hint; }
    };

    class ExeName : public ComposableParserImpl<ExeName> {
        std::shared_ptr<std::string> m_name;
        std::shared_ptr<BoundRefBase> m_ref;

        template<typename LambdaT>
        static auto makeRef(LambdaT const &lambda) -> std::shared_ptr<BoundRefBase> {
            return std::make_shared<BoundLambda<LambdaT>>(lambda);
        }

    public:
        ExeName() : m_name(std::make_shared<std::string>("<executable>")) {}

        explicit ExeName(std::string &ref) : ExeName() {
            m_ref = std::make_shared<BoundRef<std::string>>( ref );
        }

        template<typename LambdaT>
        explicit ExeName( LambdaT const& lambda ) : ExeName() {
            m_ref = std::make_shared<BoundLambda<LambdaT>>( lambda );
        }

        // The exe name is not parsed out of the normal tokens, but is handled specially
        auto parse( std::string const&, TokenStream const &tokens ) const -> InternalParseResult override {
            return InternalParseResult::ok(ParseState(ParseResultType::NoMatch, tokens));
        }

        auto name() const -> std::string { return *m_name; }
        auto set( std::string const& newName ) -> ParserResult {

            auto lastSlash = newName.find_last_of( "\\/" );
            auto filename = (lastSlash == std::string::npos)
                    ? newName
                    : newName.substr( lastSlash+1 );

            *m_name = filename;
            if( m_ref )
                return m_ref->setValue( filename );
            else
                return ParserResult::ok( ParseResultType::Matched );
        }
    };

    class Arg : public ParserRefImpl<Arg> {
    public:
        using ParserRefImpl::ParserRefImpl;

        auto parse(std::string const &, TokenStream const &tokens) const -> InternalParseResult override {
            auto validationResult = validate();
            if (!validationResult)
                return InternalParseResult(validationResult);

            auto remainingTokens = tokens;
            auto const &token = *remainingTokens;
            if (token.type != TokenType::Argument)
                return InternalParseResult::ok(ParseState(ParseResultType::NoMatch, remainingTokens));

            auto result = m_ref->setValue(remainingTokens->token);
            if (!result)
                return InternalParseResult(result);
            else
                return InternalParseResult::ok(ParseState(ParseResultType::Matched, ++remainingTokens));
        }
    };

    inline auto normaliseOpt(std::string const &optName) -> std::string {
        if (optName[0] == '/')
            return "-" + optName.substr(1);
        else
            return optName;
    }

    class Opt : public ParserRefImpl<Opt> {
    protected:
        std::vector<std::string> m_optNames;

    public:
        template<typename LambdaT>
        explicit Opt( LambdaT const &ref ) : ParserRefImpl(std::make_shared<BoundFlagLambda<LambdaT>>(ref)) {}

        explicit Opt( bool &ref ) : ParserRefImpl(std::make_shared<BoundFlagRef>(ref)) {}

        template<typename LambdaT>
        Opt( LambdaT const &ref, std::string const &hint ) : ParserRefImpl( ref, hint ) {}

        template<typename T>
        Opt( T &ref, std::string const &hint ) : ParserRefImpl( ref, hint ) {}

        auto operator[](std::string const &optName) -> Opt & {
            m_optNames.push_back(optName);
            return *this;
        }

        auto getHelpColumns() const -> std::vector<HelpColumns> {
            std::ostringstream oss;
            bool first = true;
            for (auto const &opt : m_optNames) {
                if (first)
                    first = false;
                else
                    oss << ", ";
                oss << opt;
            }
            if (!m_hint.empty())
                oss << " <" << m_hint << ">";
            return {{oss.str(), m_description}};
        }

        auto isMatch(std::string const &optToken) const -> bool {
#ifdef CLARA_PLATFORM_WINDOWS
            auto normalisedToken = normaliseOpt( optToken );
#else
            auto const &normalisedToken = optToken;
#endif
            for (auto const &name : m_optNames) {
                if (normaliseOpt(name) == normalisedToken)
                    return true;
            }
            return false;
        }

        using ParserBase::parse;

        auto parse( std::string const&, TokenStream const &tokens ) const -> InternalParseResult override {
            auto validationResult = validate();
            if (!validationResult)
                return InternalParseResult(validationResult);

            auto remainingTokens = tokens;
            if (remainingTokens && remainingTokens->type == TokenType::Option) {
                auto const &token = *remainingTokens;
                if (isMatch(token.token)) {
                    if (m_ref->isFlag()) {
                        auto result = m_ref->setFlag(true);
                        if (!result)
                            return InternalParseResult(result);
                        if (result.value() == ParseResultType::ShortCircuitAll)
                            return InternalParseResult::ok(ParseState(result.value(), remainingTokens));
                    } else {
                        ++remainingTokens;
                        if (!remainingTokens)
                            return InternalParseResult::runtimeError("Expected argument following " + token.token);
                        auto const &argToken = *remainingTokens;
                        if (argToken.type != TokenType::Argument)
                            return InternalParseResult::runtimeError("Expected argument following " + token.token);
                        auto result = m_ref->setValue(argToken.token);
                        if (!result)
                            return InternalParseResult(result);
                        if (result.value() == ParseResultType::ShortCircuitAll)
                            return InternalParseResult::ok(ParseState(result.value(), remainingTokens));
                    }
                    return InternalParseResult::ok(ParseState(ParseResultType::Matched, ++remainingTokens));
                }
            }
            return InternalParseResult::ok(ParseState(ParseResultType::NoMatch, remainingTokens));
        }

        auto validate() const -> Result override {
            if (m_optNames.empty())
                return Result::logicError("No options supplied to Opt");
            for (auto const &name : m_optNames) {
                if (name.empty())
                    return Result::logicError("Option name cannot be empty");
                if (name[0] != '-' && name[0] != '/')
                    return Result::logicError("Option name must begin with '-' or '/'");
            }
            return ParserRefImpl::validate();
        }
    };

    struct Help : Opt {
        Help( bool &showHelpFlag )
        :   Opt([&]( bool flag ) {
            showHelpFlag = flag;
                return ParserResult::ok(ParseResultType::ShortCircuitAll);
            })
        {
            static_cast<Opt &>(*this)
                    ("display usage information")
                    ["-?"]["-h"]["--help"]
                    .optional();
        }
    };

    struct Parser : ParserBase {

        mutable ExeName m_exeName;
        std::vector<Opt> m_options;
        std::vector<Arg> m_args;

        auto operator+=(ExeName const &exeName) -> Parser & {
            m_exeName = exeName;
            return *this;
        }

        auto operator+=(Arg const &arg) -> Parser & {
            m_args.push_back(arg);
            return *this;
        }

        auto operator+=(Opt const &opt) -> Parser & {
            m_options.push_back(opt);
            return *this;
        }

        auto operator+=(Parser const &other) -> Parser & {
            m_options.insert(m_options.end(), other.m_options.begin(), other.m_options.end());
            m_args.insert(m_args.end(), other.m_args.begin(), other.m_args.end());
            return *this;
        }

        template<typename T>
        auto operator+(T const &other) const -> Parser {
            return Parser(*this) += other;
        }

        auto getHelpColumns() const -> std::vector<HelpColumns> {
            std::vector<HelpColumns> cols;
            for (auto const &o : m_options) {
                auto childCols = o.getHelpColumns();
                cols.insert(cols.end(), childCols.begin(), childCols.end());
            }
            return cols;
        }

        void writeToStream(std::ostream &os) const {
            if (!m_exeName.name().empty()) {
                os << "usage:\n" << "  " << m_exeName.name() << " ";
                bool required = true, first = true;
                for (auto const &arg : m_args) {
                    if (first)
                        first = false;
                    else
                        os << " ";
                    if (arg.isOptional() && required) {
                        os << "[";
                        required = false;
                    }
                    os << "<" << arg.hint() << ">";
                    if (arg.cardinality() == 0)
                        os << " ... ";
                }
                if (!required)
                    os << "]";
                if (!m_options.empty())
                    os << " options";
                os << "\n\nwhere options are:" << std::endl;
            }

            auto rows = getHelpColumns();
            size_t consoleWidth = CATCH_CLARA_CONFIG_CONSOLE_WIDTH;
            size_t optWidth = 0;
            for (auto const &cols : rows)
                optWidth = std::max(optWidth, cols.left.size() + 2);

            for (auto const &cols : rows) {
                auto row =
                        TextFlow::Column(cols.left).width(optWidth).indent(2) +
                        TextFlow::Spacer(4) +
                        TextFlow::Column(cols.right).width(consoleWidth - 7 - optWidth);
                os << row << std::endl;
            }
        }

        friend auto operator<<(std::ostream &os, Parser const &parser) -> std::ostream & {
            parser.writeToStream(os);
            return os;
        }

        auto validate() const -> Result override {
            for (auto const &opt : m_options) {
                auto result = opt.validate();
                if (!result)
                    return result;
            }
            for (auto const &arg : m_args) {
                auto result = arg.validate();
                if (!result)
                    return result;
            }
            return Result::ok();
        }

        using ParserBase::parse;

        auto parse( std::string const& exeName, TokenStream const &tokens) const -> InternalParseResult override {
            std::vector<ParserBase const *> allParsers;
            allParsers.reserve(m_args.size() + m_options.size());
            std::set<ParserBase const *> requiredParsers;

            for (auto const &opt : m_options) {
                allParsers.push_back(&opt);
                if (!opt.isOptional())
                    requiredParsers.insert(&opt);
            }

            size_t optionalArgs = 0;
            for (auto const &arg : m_args) {
                allParsers.push_back(&arg);
                if (!arg.isOptional()) {
                    if (optionalArgs > 0)
                        return InternalParseResult::logicError(
                                "Required arguments must preceed any optional arguments");
                    else
                        ++optionalArgs;
                    requiredParsers.insert(&arg);
                }
            }

            m_exeName.set( exeName );

            auto result = InternalParseResult::ok(ParseState(ParseResultType::NoMatch, tokens));
            while (result.value().remainingTokens()) {
                auto remainingTokenCount = result.value().remainingTokens().count();
                for (auto parser : allParsers) {
                    result = parser->parse( exeName, result.value().remainingTokens() );
                    if (!result || result.value().type() != ParseResultType::NoMatch) {
                        if (parser->cardinality() == 1)
                            allParsers.erase(std::remove(allParsers.begin(), allParsers.end(), parser),
                                             allParsers.end());
                        requiredParsers.erase(parser);
                        break;
                    }
                }
                if (!result || remainingTokenCount == result.value().remainingTokens().count())
                    return result;
            }
            // !TBD Check missing required options
            return result;
        }
    };

    template<typename DerivedT>
    template<typename T>
    auto ComposableParserImpl<DerivedT>::operator+(T const &other) const -> Parser {
        return Parser() + static_cast<DerivedT const &>( *this ) + other;
    }
} // namespace detail

// A Combined parser
using detail::Parser;

// A parser for options
using detail::Opt;

// A parser for arguments
using detail::Arg;

// Wrapper for argc, argv from main()
using detail::Args;

// Specifies the name of the executable
using detail::ExeName;

// Convenience wrapper for option parser that specifies the help option
using detail::Help;

// enum of result types from a parse
using detail::ParseResultType;

// Result type for parser operation
using detail::ParserResult;

}} // namespace Catch::clara

// end clara.hpp
// Restore Clara's value for console width, if present
#ifdef CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#define CATCH_CLARA_TEXTFLOW_CONFIG_CONSOLE_WIDTH CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#undef CATCH_TEMP_CLARA_CONFIG_CONSOLE_WIDTH
#endif

// end catch_clara.h
namespace Catch {

    clara::Parser makeCommandLineParser( ConfigData& config );

} // end namespace Catch

// end catch_commandline.hpp
// start catch_console_colour.hpp

namespace Catch {

    struct Colour {
        enum Code {
            None = 0,

            White,
            Red,
            Green,
            Blue,
            Cyan,
            Yellow,
            Grey,

            Bright = 0x10,

            BrightRed = Bright | Red,
            BrightGreen = Bright | Green,
            LightGrey = Bright | Grey,
            BrightWhite = Bright | White,

            // By intention
            FileName = LightGrey,
            Warning = Yellow,
            ResultError = BrightRed,
            ResultSuccess = BrightGreen,
            ResultExpectedFailure = Warning,

            Error = BrightRed,
            Success = Green,

            OriginalExpression = Cyan,
            ReconstructedExpression = Yellow,

            SecondaryText = LightGrey,
            Headers = White
        };

        // Use constructed object for RAII guard
        Colour( Code _colourCode );
        Colour( Colour&& other ) noexcept;
        Colour& operator=( Colour&& other ) noexcept;
        ~Colour();

        // Use static method for one-shot changes
        static void use( Code _colourCode );

    private:
        bool m_moved = false;
    };

    std::ostream& operator << ( std::ostream& os, Colour const& );

} // end namespace Catch

// end catch_console_colour.hpp
// start catch_list.h

#include <set>

namespace Catch {

    std::size_t listTests( Config const& config );

    std::size_t listTestsNamesOnly( Config const& config );

    struct TagInfo {
        void add( std::string const& spelling );
        std::string all() const;

        std::set<std::string> spellings;
        std::size_t count = 0;
    };

    std::size_t listTags( Config const& config );

    std::size_t listReporters( Config const& /*config*/ );

    Option<std::size_t> list( Config const& config );

} // end namespace Catch

// end catch_list.h
// start catch_run_context.hpp

// start catch_test_case_tracker.hpp

#include <string>
#include <vector>
#include <memory>

CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS

namespace Catch {
namespace TestCaseTracking {

    struct NameAndLocation {
        std::string name;
        SourceLineInfo location;

        NameAndLocation( std::string const& _name, SourceLineInfo const& _location );
    };

    struct ITracker;

    using ITrackerPtr = std::shared_ptr<ITracker>;

    struct ITracker {
        virtual ~ITracker() = default;

        // static queries
        virtual NameAndLocation const& nameAndLocation() const = 0;

        // dynamic queries
        virtual bool isComplete() const = 0; // Successfully completed or failed
        virtual bool isSuccessfullyCompleted() const = 0;
        virtual bool isOpen() const = 0; // Started but not complete
        virtual bool hasChildren() const = 0;

        virtual ITracker& parent() = 0;

        // actions
        virtual void close() = 0; // Successfully complete
        virtual void fail() = 0;
        virtual void markAsNeedingAnotherRun() = 0;

        virtual void addChild( ITrackerPtr const& child ) = 0;
        virtual ITrackerPtr findChild( NameAndLocation const& nameAndLocation ) = 0;
        virtual void openChild() = 0;

        // Debug/ checking
        virtual bool isSectionTracker() const = 0;
        virtual bool isIndexTracker() const = 0;
    };

    class TrackerContext {

        enum RunState {
            NotStarted,
            Executing,
            CompletedCycle
        };

        ITrackerPtr m_rootTracker;
        ITracker* m_currentTracker = nullptr;
        RunState m_runState = NotStarted;

    public:

        static TrackerContext& instance();

        ITracker& startRun();
        void endRun();

        void startCycle();
        void completeCycle();

        bool completedCycle() const;
        ITracker& currentTracker();
        void setCurrentTracker( ITracker* tracker );
    };

    class TrackerBase : public ITracker {
    protected:
        enum CycleState {
            NotStarted,
            Executing,
            ExecutingChildren,
            NeedsAnotherRun,
            CompletedSuccessfully,
            Failed
        };

        class TrackerHasName {
            NameAndLocation m_nameAndLocation;
        public:
            TrackerHasName( NameAndLocation const& nameAndLocation );
            bool operator ()( ITrackerPtr const& tracker ) const;
        };

        using Children = std::vector<ITrackerPtr>;
        NameAndLocation m_nameAndLocation;
        TrackerContext& m_ctx;
        ITracker* m_parent;
        Children m_children;
        CycleState m_runState = NotStarted;

    public:
        TrackerBase( NameAndLocation const& nameAndLocation, TrackerContext& ctx, ITracker* parent );

        NameAndLocation const& nameAndLocation() const override;
        bool isComplete() const override;
        bool isSuccessfullyCompleted() const override;
        bool isOpen() const override;
        bool hasChildren() const override;

        void addChild( ITrackerPtr const& child ) override;

        ITrackerPtr findChild( NameAndLocation const& nameAndLocation ) override;
        ITracker& parent() override;

        void openChild() override;

        bool isSectionTracker() const override;
        bool isIndexTracker() const override;

        void open();

        void close() override;
        void fail() override;
        void markAsNeedingAnotherRun() override;

    private:
        void moveToParent();
        void moveToThis();
    };

    class SectionTracker : public TrackerBase {
        std::vector<std::string> m_filters;
    public:
        SectionTracker( NameAndLocation const& nameAndLocation, TrackerContext& ctx, ITracker* parent );

        bool isSectionTracker() const override;

        static SectionTracker& acquire( TrackerContext& ctx, NameAndLocation const& nameAndLocation );

        void tryOpen();

        void addInitialFilters( std::vector<std::string> const& filters );
        void addNextFilters( std::vector<std::string> const& filters );
    };

    class IndexTracker : public TrackerBase {
        int m_size;
        int m_index = -1;
    public:
        IndexTracker( NameAndLocation const& nameAndLocation, TrackerContext& ctx, ITracker* parent, int size );

        bool isIndexTracker() const override;
        void close() override;

        static IndexTracker& acquire( TrackerContext& ctx, NameAndLocation const& nameAndLocation, int size );

        int index() const;

        void moveNext();
    };

} // namespace TestCaseTracking

using TestCaseTracking::ITracker;
using TestCaseTracking::TrackerContext;
using TestCaseTracking::SectionTracker;
using TestCaseTracking::IndexTracker;

} // namespace Catch

CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS

// end catch_test_case_tracker.hpp
// start catch_fatal_condition.h

#include <string>

namespace Catch {

    // Report the error condition
    void reportFatal( std::string const& message );

} // namespace Catch

#if defined ( CATCH_PLATFORM_WINDOWS ) /////////////////////////////////////////
// start catch_windows_h_proxy.h


#if defined(CATCH_PLATFORM_WINDOWS)
#  if !defined(NOMINMAX) && !defined(CATCH_CONFIG_NO_NOMINMAX)
#    define CATCH_DEFINED_NOMINMAX
#    define NOMINMAX
#  endif
#  if !defined(WIN32_LEAN_AND_MEAN) && !defined(CATCH_CONFIG_NO_WIN32_LEAN_AND_MEAN)
#    define CATCH_DEFINED_WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif
#endif

#ifdef __AFXDLL
#include <AfxWin.h>
#else
#include <windows.h>
#endif

#ifdef CATCH_DEFINED_NOMINMAX
#  undef NOMINMAX
#endif
#ifdef CATCH_DEFINED_WIN32_LEAN_AND_MEAN
#  undef WIN32_LEAN_AND_MEAN
#endif

// end catch_windows_h_proxy.h

#  if !defined ( CATCH_CONFIG_WINDOWS_SEH )

namespace Catch {
    struct FatalConditionHandler {
        void reset();
    };
}

#  else // CATCH_CONFIG_WINDOWS_SEH is defined

namespace Catch {

    struct FatalConditionHandler {

        static LONG CALLBACK handleVectoredException(PEXCEPTION_POINTERS ExceptionInfo);
        FatalConditionHandler();
        static void reset();
        ~FatalConditionHandler();

    private:
        static bool isSet;
        static ULONG guaranteeSize;
        static PVOID exceptionHandlerHandle;
    };

} // namespace Catch

#  endif // CATCH_CONFIG_WINDOWS_SEH

#else // Not Windows - assumed to be POSIX compatible //////////////////////////

#  if !defined(CATCH_CONFIG_POSIX_SIGNALS)

namespace Catch {
    struct FatalConditionHandler {
        void reset();
    };
}

#  else // CATCH_CONFIG_POSIX_SIGNALS is defined

#include <signal.h>

namespace Catch {

    struct FatalConditionHandler {

        static bool isSet;
        static struct sigaction oldSigActions[];// [sizeof(signalDefs) / sizeof(SignalDefs)];
        static stack_t oldSigStack;
        static char altStackMem[];

        static void handleSignal( int sig );

        FatalConditionHandler();
        ~FatalConditionHandler();
        static void reset();
    };

} // namespace Catch

#  endif // CATCH_CONFIG_POSIX_SIGNALS

#endif // not Windows

// end catch_fatal_condition.h
#include <string>

namespace Catch {

    class StreamRedirect {

    public:
        StreamRedirect(std::ostream& stream, std::string& targetString);

        ~StreamRedirect();

    private:
        std::ostream& m_stream;
        std::streambuf* m_prevBuf;
        std::ostringstream m_oss;
        std::string& m_targetString;
    };

    ///////////////////////////////////////////////////////////////////////////

    class RunContext : public IResultCapture, public IRunner {

    public:
        RunContext( RunContext const& ) = delete;
        RunContext& operator =( RunContext const& ) = delete;

        explicit RunContext(IConfigPtr const& _config, IStreamingReporterPtr&& reporter);

        virtual ~RunContext();

        void testGroupStarting(std::string const& testSpec, std::size_t groupIndex, std::size_t groupsCount);
        void testGroupEnded(std::string const& testSpec, Totals const& totals, std::size_t groupIndex, std::size_t groupsCount);

        Totals runTest(TestCase const& testCase);

        IConfigPtr config() const;
        IStreamingReporter& reporter() const;

    private: // IResultCapture

        void assertionStarting(AssertionInfo const& info) override;
        void assertionEnded(AssertionResult const& result) override;

        bool sectionStarted( SectionInfo const& sectionInfo, Counts& assertions ) override;
        bool testForMissingAssertions(Counts& assertions);

        void sectionEnded(SectionEndInfo const& endInfo) override;
        void sectionEndedEarly(SectionEndInfo const& endInfo) override;

        void benchmarkStarting( BenchmarkInfo const& info ) override;
        void benchmarkEnded( BenchmarkStats const& stats ) override;

        void pushScopedMessage(MessageInfo const& message) override;
        void popScopedMessage(MessageInfo const& message) override;

        std::string getCurrentTestName() const override;

        const AssertionResult* getLastResult() const override;

        void exceptionEarlyReported() override;

        void handleFatalErrorCondition(std::string const& message) override;

        bool lastAssertionPassed() override;

        void assertionPassed() override;

        void assertionRun() override;

    public:
        // !TBD We need to do this another way!
        bool aborting() const override;

    private:

        void runCurrentTest(std::string& redirectedCout, std::string& redirectedCerr);
        void invokeActiveTestCase();

    private:

        ResultBuilder makeUnexpectedResultBuilder() const;

        void handleUnfinishedSections();

        TestRunInfo m_runInfo;
        IMutableContext& m_context;
        TestCase const* m_activeTestCase = nullptr;
        ITracker* m_testCaseTracker;
        AssertionResult m_lastResult;

        IConfigPtr m_config;
        Totals m_totals;
        IStreamingReporterPtr m_reporter;
        std::vector<MessageInfo> m_messages;
        AssertionInfo m_lastAssertionInfo;
        std::vector<SectionEndInfo> m_unfinishedSections;
        std::vector<ITracker*> m_activeSections;
        TrackerContext m_trackerContext;
        size_t m_prevPassed = 0;
        bool m_shouldReportUnexpected = true;
    };

    IResultCapture& getResultCapture();

} // end namespace Catch

// end catch_run_context.hpp
// start catch_version.h

#include <iosfwd>

namespace Catch {

    // Versioning information
    struct Version {
        Version( Version const& ) = delete;
        Version& operator=( Version const& ) = delete;
        Version(    unsigned int _majorVersion,
                    unsigned int _minorVersion,
                    unsigned int _patchNumber,
                    char const * const _branchName,
                    unsigned int _buildNumber );

        unsigned int const majorVersion;
        unsigned int const minorVersion;
        unsigned int const patchNumber;

        // buildNumber is only used if branchName is not null
        char const * const branchName;
        unsigned int const buildNumber;

        friend std::ostream& operator << ( std::ostream& os, Version const& version );
    };

    Version const& libraryVersion();
}

// end catch_version.h
// start catch_startup_exception_registry.h

#include <vector>
#include <exception>

namespace Catch {

    class StartupExceptionRegistry {
    public:
        void add(std::exception_ptr const& exception) noexcept;
        std::vector<std::exception_ptr> const& getExceptions() const noexcept;
    private:
        std::vector<std::exception_ptr> m_exceptions;
    };

} // end namespace Catch

// end catch_startup_exception_registry.h
// start catch_text.h

namespace Catch {
    using namespace clara::TextFlow;
}

// end catch_text.h
#include <fstream>
#include <cstdlib>
#include <limits>

namespace Catch {

    IStreamingReporterPtr createReporter( std::string const& reporterName, IConfigPtr const& config ) {
        auto reporter = getRegistryHub().getReporterRegistry().create( reporterName, config );
        CATCH_ENFORCE( reporter, "No reporter registered with name: '" << reporterName << "'" );

        return reporter;
    }

    IStreamingReporterPtr makeReporter( std::shared_ptr<Config> const& config ) {
        auto const& reporterNames = config->getReporterNames();
        if( reporterNames.empty() )
            return createReporter( "console", config );

        IStreamingReporterPtr reporter;
        for( auto const& name : reporterNames )
            addReporter( reporter, createReporter( name, config ) );
        return reporter;
    }
    void addListeners( IStreamingReporterPtr& reporters, IConfigPtr const& config ) {
        auto const& listeners = getRegistryHub().getReporterRegistry().getListeners();
        for( auto const& listener : listeners )
            addReporter(reporters, listener->create( ReporterConfig( config ) ) );
    }

    Totals runTests( std::shared_ptr<Config> const& config ) {

        IStreamingReporterPtr reporter = makeReporter( config );
        addListeners( reporter, config );

        RunContext context( config, std::move( reporter ) );

        Totals totals;

        context.testGroupStarting( config->name(), 1, 1 );

        TestSpec testSpec = config->testSpec();
        if( !testSpec.hasFilters() )
            testSpec = TestSpecParser( ITagAliasRegistry::get() ).parse( "~[.]" ).testSpec(); // All not hidden tests

        std::vector<TestCase> const& allTestCases = getAllTestCasesSorted( *config );
        for( auto const& testCase : allTestCases ) {
            if( !context.aborting() && matchTest( testCase, testSpec, *config ) )
                totals += context.runTest( testCase );
            else
                context.reporter().skipTest( testCase );
        }

        context.testGroupEnded( config->name(), totals, 1, 1 );
        return totals;
    }

    void applyFilenamesAsTags( IConfig const& config ) {
        auto& tests = const_cast<std::vector<TestCase>&>( getAllTestCasesSorted( config ) );
        for( auto& testCase : tests ) {
            auto tags = testCase.tags;

            std::string filename = testCase.lineInfo.file;
            std::string::size_type lastSlash = filename.find_last_of( "\\/" );
            if( lastSlash != std::string::npos )
                filename = filename.substr( lastSlash+1 );

            std::string::size_type lastDot = filename.find_last_of( '.' );
            if( lastDot != std::string::npos )
                filename = filename.substr( 0, lastDot );

            tags.push_back( "#" + filename );
            setTags( testCase, tags );
        }
    }

    class Session : NonCopyable {
        static const int MaxExitCode;
    public:

        Session() {
            static bool alreadyInstantiated = false;
            if( alreadyInstantiated )
                CATCH_INTERNAL_ERROR( "Only one instance of Catch::Session can ever be used" );
            alreadyInstantiated = true;
            m_cli = makeCommandLineParser( m_configData );
        }
        ~Session() override {
            Catch::cleanUp();
        }

        void showHelp() const {
            Catch::cout()
                    << "\nCatch v" << libraryVersion() << "\n"
                    << m_cli << std::endl
                    << "For more detailed usage please see the project docs\n" << std::endl;
        }

        int applyCommandLine( int argc, char* argv[] ) {
            auto result = m_cli.parse( clara::Args( argc, argv ) );
            if( !result ) {
                Catch::cerr()
                    << Colour( Colour::Red )
                    << "\nError(s) in input:\n"
                    << Column( result.errorMessage() ).indent( 2 )
                    << "\n\n";

                Catch::cerr() << m_cli << std::endl;
                return MaxExitCode;
            }

            if( m_configData.showHelp )
                showHelp();
            m_config.reset();
            return 0;
        }

        void useConfigData( ConfigData const& configData ) {
            m_configData = configData;
            m_config.reset();
        }

        int run( int argc, char* argv[] ) {
            const auto& exceptions = getRegistryHub().getStartupExceptionRegistry().getExceptions();
            if ( !exceptions.empty() ) {
                Catch::cerr() << "Errors occured during startup!" << '\n';
                // iterate over all exceptions and notify user
                for ( const auto& ex_ptr : exceptions ) {
                    try {
                        std::rethrow_exception(ex_ptr);
                    } catch ( std::exception const& ex ) {
                        Catch::cerr() << ex.what() << '\n';
                    }
                }
                return 1;
            }
            int returnCode = applyCommandLine( argc, argv );
            if( returnCode == 0 )
                returnCode = run();
            return returnCode;
        }

    #if defined(WIN32) && defined(UNICODE)
        int run( int argc, wchar_t* const argv[] ) {

            char **utf8Argv = new char *[ argc ];

            for ( int i = 0; i < argc; ++i ) {
                int bufSize = WideCharToMultiByte( CP_UTF8, 0, argv[i], -1, NULL, 0, NULL, NULL );

                utf8Argv[ i ] = new char[ bufSize ];

                WideCharToMultiByte( CP_UTF8, 0, argv[i], -1, utf8Argv[i], bufSize, NULL, NULL );
            }

            int returnCode = run( argc, utf8Argv );

            for ( int i = 0; i < argc; ++i )
                delete [] utf8Argv[ i ];

            delete [] utf8Argv;

            return returnCode;
        }
    #endif

        int run() {
            if( m_configData.showHelp )
                return 0;

            try
            {
                config(); // Force config to be constructed

                seedRng( *m_config );

                if( m_configData.filenamesAsTags )
                    applyFilenamesAsTags( *m_config );

                // Handle list request
                if( Option<std::size_t> listed = list( config() ) )
                    return static_cast<int>( *listed );

                return (std::min)( MaxExitCode, static_cast<int>( runTests( m_config ).assertions.failed ) );
            }
            catch( std::exception& ex ) {
                Catch::cerr() << ex.what() << std::endl;
                return MaxExitCode;
            }
        }

        clara::Parser const& cli() const {
            return m_cli;
        }
        void cli( clara::Parser const& newParser ) {
            m_cli = newParser;
        }
        ConfigData& configData() {
            return m_configData;
        }
        Config& config() {
            if( !m_config )
                m_config = std::make_shared<Config>( m_configData );
            return *m_config;
        }
    private:
        clara::Parser m_cli;
        ConfigData m_configData;
        std::shared_ptr<Config> m_config;
    };

    const int Session::MaxExitCode = 255;

} // end namespace Catch

// end catch_session.hpp
// start catch_stream.hpp

#include <stdexcept>
#include <cstdio>
#include <iostream>

namespace Catch {

    template<typename WriterF, size_t bufferSize=256>
    class StreamBufImpl : public StreamBufBase {
        char data[bufferSize];
        WriterF m_writer;

    public:
        StreamBufImpl() {
            setp( data, data + sizeof(data) );
        }

        ~StreamBufImpl() noexcept {
            StreamBufImpl::sync();
        }

    private:
        int overflow( int c ) override {
            sync();

            if( c != EOF ) {
                if( pbase() == epptr() )
                    m_writer( std::string( 1, static_cast<char>( c ) ) );
                else
                    sputc( static_cast<char>( c ) );
            }
            return 0;
        }

        int sync() override {
            if( pbase() != pptr() ) {
                m_writer( std::string( pbase(), static_cast<std::string::size_type>( pptr() - pbase() ) ) );
                setp( pbase(), epptr() );
            }
            return 0;
        }
    };

    ///////////////////////////////////////////////////////////////////////////

    FileStream::FileStream( std::string const& filename ) {
        m_ofs.open( filename.c_str() );
        CATCH_ENFORCE( !m_ofs.fail(), "Unable to open file: '" << filename << "'" );
    }

    std::ostream& FileStream::stream() const {
        return m_ofs;
    }

    struct OutputDebugWriter {

        void operator()( std::string const&str ) {
            writeToDebugConsole( str );
        }
    };

    DebugOutStream::DebugOutStream()
    :   m_streamBuf( new StreamBufImpl<OutputDebugWriter>() ),
        m_os( m_streamBuf.get() )
    {}

    std::ostream& DebugOutStream::stream() const {
        return m_os;
    }

    // Store the streambuf from cout up-front because
    // cout may get redirected when running tests
    CoutStream::CoutStream()
    :   m_os( Catch::cout().rdbuf() )
    {}

    std::ostream& CoutStream::stream() const {
        return m_os;
    }

#ifndef CATCH_CONFIG_NOSTDOUT // If you #define this you must implement these functions
    std::ostream& cout() {
        return std::cout;
    }
    std::ostream& cerr() {
        return std::cerr;
    }
#endif
}

// end catch_stream.hpp
// Cpp files will be included in the single-header file here
// start catch_approx.cpp

#include <limits>

namespace Catch {
namespace Detail {

    Approx::Approx ( double value )
    :   m_epsilon( std::numeric_limits<float>::epsilon()*100 ),
        m_margin( 0.0 ),
        m_scale( 1.0 ),
        m_value( value )
    {}

    Approx Approx::custom() {
        return Approx( 0 );
    }

    std::string Approx::toString() const {
        std::ostringstream oss;
        oss << "Approx( " << ::Catch::Detail::stringify( m_value ) << " )";
        return oss.str();
    }

} // end namespace Detail

std::string StringMaker<Catch::Detail::Approx>::convert(Catch::Detail::Approx const& value) {
    return value.toString();
}

} // end namespace Catch
// end catch_approx.cpp
// start catch_assertionresult.cpp

namespace Catch {

    bool DecomposedExpression::isBinaryExpression() const {
        return false;
    }

    AssertionInfo::AssertionInfo(   char const * _macroName,
                                    SourceLineInfo const& _lineInfo,
                                    char const * _capturedExpression,
                                    ResultDisposition::Flags _resultDisposition)
    :   macroName( _macroName ),
        lineInfo( _lineInfo ),
        capturedExpression( _capturedExpression ),
        resultDisposition( _resultDisposition )
    {}

    void AssertionResultData::negate( bool parenthesize ) {
        negated = !negated;
        parenthesized = parenthesize;
        if( resultType == ResultWas::Ok )
            resultType = ResultWas::ExpressionFailed;
        else if( resultType == ResultWas::ExpressionFailed )
            resultType = ResultWas::Ok;
    }

    std::string const& AssertionResultData::reconstructExpression() const {
        if( decomposedExpression != nullptr ) {
            decomposedExpression->reconstructExpression( reconstructedExpression );
            if( parenthesized ) {
                reconstructedExpression.insert( 0, 1, '(' );
                reconstructedExpression.append( 1, ')' );
            }
            if( negated ) {
                reconstructedExpression.insert( 0, 1, '!' );
            }
            decomposedExpression = nullptr;
        }
        return reconstructedExpression;
    }

    AssertionResult::AssertionResult() {}

    AssertionResult::AssertionResult( AssertionInfo const& info, AssertionResultData const& data )
    :   m_info( info ),
        m_resultData( data )
    {}

    AssertionResult::~AssertionResult() {}

    // Result was a success
    bool AssertionResult::succeeded() const {
        return Catch::isOk( m_resultData.resultType );
    }

    // Result was a success, or failure is suppressed
    bool AssertionResult::isOk() const {
        return Catch::isOk( m_resultData.resultType ) || shouldSuppressFailure( m_info.resultDisposition );
    }

    ResultWas::OfType AssertionResult::getResultType() const {
        return m_resultData.resultType;
    }

    bool AssertionResult::hasExpression() const {
        return m_info.capturedExpression[0] != 0;
    }

    bool AssertionResult::hasMessage() const {
        return !m_resultData.message.empty();
    }

    std::string AssertionResult::getExpression() const {
        if (isFalseTest(m_info.resultDisposition))
            return '!' + std::string(m_info.capturedExpression);
        else
            return std::string(m_info.capturedExpression);
    }

    std::string AssertionResult::getExpressionInMacro() const {
        if( m_info.macroName[0] == 0 )
            return std::string(m_info.capturedExpression);
        else
            return std::string(m_info.macroName) + "( " + m_info.capturedExpression + " )";
    }

    bool AssertionResult::hasExpandedExpression() const {
        return hasExpression() && getExpandedExpression() != getExpression();
    }

    std::string AssertionResult::getExpandedExpression() const {
        return m_resultData.reconstructExpression();
    }

    std::string AssertionResult::getMessage() const {
        return m_resultData.message;
    }
    SourceLineInfo AssertionResult::getSourceInfo() const {
        return m_info.lineInfo;
    }

    std::string AssertionResult::getTestMacroName() const {
        return m_info.macroName;
    }

    void AssertionResult::discardDecomposedExpression() const {
        m_resultData.decomposedExpression = nullptr;
    }

    void AssertionResult::expandDecomposedExpression() const {
        m_resultData.reconstructExpression();
    }

} // end namespace Catch
// end catch_assertionresult.cpp
// start catch_benchmark.cpp

namespace Catch {

    void BenchmarkLooper::reportStart() const {
        getResultCapture().benchmarkStarting( { m_name } );
    }
    auto BenchmarkLooper::needsMoreIterations() -> bool {
        auto elapsed = m_timer.getElapsedNanoseconds();

        // Exponentially increasing iterations until we're confident in our timer resolution
        if( elapsed < m_resolution ) {
            m_iterationsToRun *= 10;
            return true;
        }

        getResultCapture().benchmarkEnded( { { m_name }, m_count, elapsed } );
        return false;
    }

} // end namespace Catch
// end catch_benchmark.cpp
// start catch_commandline.cpp

#include <fstream>
#include <ctime>

namespace Catch {

    clara::Parser makeCommandLineParser( ConfigData& config ) {

        using namespace clara;

        auto const setWarning = [&]( std::string const& warning ) {
                if( warning != "NoAssertions" )
                    return ParserResult::runtimeError( "Unrecognised warning: '" + warning + "'" );
                config.warnings = static_cast<WarnAbout::What>( config.warnings | WarnAbout::NoAssertions );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const loadTestNamesFromFile = [&]( std::string const& filename ) {
                std::ifstream f( filename.c_str() );
                if( !f.is_open() )
                    return ParserResult::runtimeError( "Unable to load input file: '" + filename + "'" );

                std::string line;
                while( std::getline( f, line ) ) {
                    line = trim(line);
                    if( !line.empty() && !startsWith( line, '#' ) ) {
                        if( !startsWith( line, '"' ) )
                            line = '"' + line + '"';
                        config.testsOrTags.push_back( line + ',' );
                    }
                }
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setTestOrder = [&]( std::string const& order ) {
                if( startsWith( "declared", order ) )
                    config.runOrder = RunTests::InDeclarationOrder;
                else if( startsWith( "lexical", order ) )
                    config.runOrder = RunTests::InLexicographicalOrder;
                else if( startsWith( "random", order ) )
                    config.runOrder = RunTests::InRandomOrder;
                else
                    return clara::ParserResult::runtimeError( "Unrecognised ordering: '" + order + "'" );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setRngSeed = [&]( std::string const& seed ) {
                if( seed != "time" )
                    return clara::detail::convertInto( seed, config.rngSeed );
                config.rngSeed = static_cast<unsigned int>( std::time(nullptr) );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setColourUsage = [&]( std::string const& useColour ) {
                    auto mode = toLower( useColour );

                    if( mode == "yes" )
                        config.useColour = UseColour::Yes;
                    else if( mode == "no" )
                        config.useColour = UseColour::No;
                    else if( mode == "auto" )
                        config.useColour = UseColour::Auto;
                    else
                        return ParserResult::runtimeError( "colour mode must be one of: auto, yes or no. '" + useColour + "' not recognised" );
                return ParserResult::ok( ParseResultType::Matched );
            };
        auto const setVerbosity = [&]( std::string const& verbosity ) {
            auto lcVerbosity = toLower( verbosity );
            if( lcVerbosity == "quiet" )
                config.verbosity = Verbosity::Quiet;
            else if( lcVerbosity == "normal" )
                config.verbosity = Verbosity::Normal;
            else if( lcVerbosity == "high" )
                config.verbosity = Verbosity::High;
            else
                return ParserResult::runtimeError( "Unrecognised verbosity, '" + verbosity + "'" );
            return ParserResult::ok( ParseResultType::Matched );
        };

        auto cli
            = ExeName( config.processName )
            + Help( config.showHelp )
            + Opt( config.listTests )
                ["-l"]["--list-tests"]
                ( "list all/matching test cases" )
            + Opt( config.listTags )
                ["-t"]["--list-tags"]
                ( "list all/matching tags" )
            + Opt( config.showSuccessfulTests )
                ["-s"]["--success"]
                ( "include successful tests in output" )
            + Opt( config.shouldDebugBreak )
                ["-b"]["--break"]
                ( "break into debugger on failure" )
            + Opt( config.noThrow )
                ["-e"]["--nothrow"]
                ( "skip exception tests" )
            + Opt( config.showInvisibles )
                ["-i"]["--invisibles"]
                ( "show invisibles (tabs, newlines)" )
            + Opt( config.outputFilename, "filename" )
                ["-o"]["--out"]
                ( "output filename" )
            + Opt( config.reporterNames, "name" )
                ["-r"]["--reporter"]
                ( "reporter to use (defaults to console)" )
            + Opt( config.name, "name" )
                ["-n"]["--name"]
                ( "suite name" )
            + Opt( [&]( bool ){ config.abortAfter = 1; } )
                ["-a"]["--abort"]
                ( "abort at first failure" )
            + Opt( [&]( int x ){ config.abortAfter = x; }, "no. failures" )
                ["-x"]["--abortx"]
                ( "abort after x failures" )
            + Opt( setWarning, "warning name" )
                ["-w"]["--warn"]
                ( "enable warnings" )
            + Opt( [&]( bool ) { config.showDurations = ShowDurations::Always; } )
                ["-d"]["--durations"]
                ( "show test durations" )
            + Opt( loadTestNamesFromFile, "filename" )
                ["-f"]["--input-file"]
                ( "load test names to run from a file" )
            + Opt( config.filenamesAsTags )
                ["-#"]["--filenames-as-tags"]
                ( "adds a tag for the filename" )
            + Opt( config.sectionsToRun, "section name" )
                ["-c"]["--section"]
                ( "specify section to run" )
            + Opt( setVerbosity, "quiet|normal|high" )
                ["-v"]["--verbosity"]
                ( "set output verbosity" )
            + Opt( config.listTestNamesOnly )
                ["--list-test-names-only"]
                ( "list all/matching test cases names only" )
            + Opt( config.listReporters )
                ["--list-reporters"]
                ( "list all reporters" )
            + Opt( setTestOrder, "decl|lex|rand" )
                ["--order"]
                ( "test case order (defaults to decl)" )
            + Opt( setRngSeed, "'time'|number" )
                ["--rng-seed"]
                ( "set a specific seed for random numbers" )
            + Opt( setColourUsage, "yes|no" )
                ["--use-colour"]
                ( "should output be colourised" )

            + Arg( config.testsOrTags, "test name|pattern|tags" )
                ( "which test or tests to use" );

        return cli;
    }

} // end namespace Catch
// end catch_commandline.cpp
// start catch_common.cpp

#include <cstring>
#include <ostream>

namespace Catch {

    SourceLineInfo::SourceLineInfo() noexcept : file(""), line( 0 ){}
    SourceLineInfo::SourceLineInfo( char const* _file, std::size_t _line ) noexcept
    :   file( _file ),
        line( _line )
    {}
    bool SourceLineInfo::empty() const noexcept {
        return file[0] == '\0';
    }
    bool SourceLineInfo::operator == ( SourceLineInfo const& other ) const noexcept {
        return line == other.line && (file == other.file || std::strcmp(file, other.file) == 0);
    }
    bool SourceLineInfo::operator < ( SourceLineInfo const& other ) const noexcept {
        return line < other.line || ( line == other.line && (std::strcmp(file, other.file) < 0));
    }

    void seedRng( IConfig const& config ) {
        if( config.rngSeed() != 0 )
            std::srand( config.rngSeed() );
    }
    unsigned int rngSeed() {
        return getCurrentContext().getConfig()->rngSeed();
    }

    std::ostream& operator << ( std::ostream& os, SourceLineInfo const& info ) {
#ifndef __GNUG__
        os << info.file << '(' << info.line << ')';
#else
        os << info.file << ':' << info.line;
#endif
        return os;
    }

    bool isTrue( bool value ){ return value; }
    bool alwaysTrue() { return true; }
    bool alwaysFalse() { return false; }

    std::string StreamEndStop::operator+() const {
        return std::string();
    }

}
// end catch_common.cpp
// start catch_config.cpp

namespace Catch {

    Config::Config( ConfigData const& data )
    :   m_data( data ),
        m_stream( openStream() )
    {
        if( !data.testsOrTags.empty() ) {
            TestSpecParser parser( ITagAliasRegistry::get() );
            for( auto const& testOrTags : data.testsOrTags )
                parser.parse( testOrTags );
            m_testSpec = parser.testSpec();
        }
    }

    std::string const& Config::getFilename() const {
        return m_data.outputFilename ;
    }

    bool Config::listTests() const          { return m_data.listTests; }
    bool Config::listTestNamesOnly() const  { return m_data.listTestNamesOnly; }
    bool Config::listTags() const           { return m_data.listTags; }
    bool Config::listReporters() const      { return m_data.listReporters; }

    std::string Config::getProcessName() const { return m_data.processName; }

    std::vector<std::string> const& Config::getReporterNames() const { return m_data.reporterNames; }
    std::vector<std::string> const& Config::getSectionsToRun() const { return m_data.sectionsToRun; }

    TestSpec const& Config::testSpec() const { return m_testSpec; }

    bool Config::showHelp() const { return m_data.showHelp; }

    // IConfig interface
    bool Config::allowThrows() const                   { return !m_data.noThrow; }
    std::ostream& Config::stream() const               { return m_stream->stream(); }
    std::string Config::name() const                   { return m_data.name.empty() ? m_data.processName : m_data.name; }
    bool Config::includeSuccessfulResults() const      { return m_data.showSuccessfulTests; }
    bool Config::warnAboutMissingAssertions() const    { return m_data.warnings & WarnAbout::NoAssertions; }
    ShowDurations::OrNot Config::showDurations() const { return m_data.showDurations; }
    RunTests::InWhatOrder Config::runOrder() const     { return m_data.runOrder; }
    unsigned int Config::rngSeed() const               { return m_data.rngSeed; }
    UseColour::YesOrNo Config::useColour() const       { return m_data.useColour; }
    bool Config::shouldDebugBreak() const              { return m_data.shouldDebugBreak; }
    int Config::abortAfter() const                     { return m_data.abortAfter; }
    bool Config::showInvisibles() const                { return m_data.showInvisibles; }
    Verbosity Config::verbosity() const                { return m_data.verbosity; }

    IStream const* Config::openStream() {
        if( m_data.outputFilename.empty() )
            return new CoutStream();
        else if( m_data.outputFilename[0] == '%' ) {
            if( m_data.outputFilename == "%debug" )
                return new DebugOutStream();
            else
                CATCH_ERROR( "Unrecognised stream: '" << m_data.outputFilename << "'" );
        }
        else
            return new FileStream( m_data.outputFilename );
    }

} // end namespace Catch
// end catch_config.cpp
// start catch_console_colour.cpp

// start catch_errno_guard.h

namespace Catch {

    class ErrnoGuard {
    public:
        ErrnoGuard();
        ~ErrnoGuard();
    private:
        int m_oldErrno;
    };

}

// end catch_errno_guard.h
namespace Catch {
    namespace {

        struct IColourImpl {
            virtual ~IColourImpl() = default;
            virtual void use( Colour::Code _colourCode ) = 0;
        };

        struct NoColourImpl : IColourImpl {
            void use( Colour::Code ) {}

            static IColourImpl* instance() {
                static NoColourImpl s_instance;
                return &s_instance;
            }
        };

    } // anon namespace
} // namespace Catch

#if !defined( CATCH_CONFIG_COLOUR_NONE ) && !defined( CATCH_CONFIG_COLOUR_WINDOWS ) && !defined( CATCH_CONFIG_COLOUR_ANSI )
#   ifdef CATCH_PLATFORM_WINDOWS
#       define CATCH_CONFIG_COLOUR_WINDOWS
#   else
#       define CATCH_CONFIG_COLOUR_ANSI
#   endif
#endif

#if defined ( CATCH_CONFIG_COLOUR_WINDOWS ) /////////////////////////////////////////

namespace Catch {
namespace {

    class Win32ColourImpl : public IColourImpl {
    public:
        Win32ColourImpl() : stdoutHandle( GetStdHandle(STD_OUTPUT_HANDLE) )
        {
            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
            GetConsoleScreenBufferInfo( stdoutHandle, &csbiInfo );
            originalForegroundAttributes = csbiInfo.wAttributes & ~( BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY );
            originalBackgroundAttributes = csbiInfo.wAttributes & ~( FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
        }

        virtual void use( Colour::Code _colourCode ) override {
            switch( _colourCode ) {
                case Colour::None:      return setTextAttribute( originalForegroundAttributes );
                case Colour::White:     return setTextAttribute( FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );
                case Colour::Red:       return setTextAttribute( FOREGROUND_RED );
                case Colour::Green:     return setTextAttribute( FOREGROUND_GREEN );
                case Colour::Blue:      return setTextAttribute( FOREGROUND_BLUE );
                case Colour::Cyan:      return setTextAttribute( FOREGROUND_BLUE | FOREGROUND_GREEN );
                case Colour::Yellow:    return setTextAttribute( FOREGROUND_RED | FOREGROUND_GREEN );
                case Colour::Grey:      return setTextAttribute( 0 );

                case Colour::LightGrey:     return setTextAttribute( FOREGROUND_INTENSITY );
                case Colour::BrightRed:     return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_RED );
                case Colour::BrightGreen:   return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_GREEN );
                case Colour::BrightWhite:   return setTextAttribute( FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );

                case Colour::Bright: CATCH_INTERNAL_ERROR( "not a colour" );
            }
        }

    private:
        void setTextAttribute( WORD _textAttribute ) {
            SetConsoleTextAttribute( stdoutHandle, _textAttribute | originalBackgroundAttributes );
        }
        HANDLE stdoutHandle;
        WORD originalForegroundAttributes;
        WORD originalBackgroundAttributes;
    };

    IColourImpl* platformColourInstance() {
        static Win32ColourImpl s_instance;

        IConfigPtr config = getCurrentContext().getConfig();
        UseColour::YesOrNo colourMode = config
            ? config->useColour()
            : UseColour::Auto;
        if( colourMode == UseColour::Auto )
            colourMode = UseColour::Yes;
        return colourMode == UseColour::Yes
            ? &s_instance
            : NoColourImpl::instance();
    }

} // end anon namespace
} // end namespace Catch

#elif defined( CATCH_CONFIG_COLOUR_ANSI ) //////////////////////////////////////

#include <unistd.h>

namespace Catch {
namespace {

    // use POSIX/ ANSI console terminal codes
    // Thanks to Adam Strzelecki for original contribution
    // (http://github.com/nanoant)
    // https://github.com/philsquared/Catch/pull/131
    class PosixColourImpl : public IColourImpl {
    public:
        virtual void use( Colour::Code _colourCode ) override {
            switch( _colourCode ) {
                case Colour::None:
                case Colour::White:     return setColour( "[0m" );
                case Colour::Red:       return setColour( "[0;31m" );
                case Colour::Green:     return setColour( "[0;32m" );
                case Colour::Blue:      return setColour( "[0;34m" );
                case Colour::Cyan:      return setColour( "[0;36m" );
                case Colour::Yellow:    return setColour( "[0;33m" );
                case Colour::Grey:      return setColour( "[1;30m" );

                case Colour::LightGrey:     return setColour( "[0;37m" );
                case Colour::BrightRed:     return setColour( "[1;31m" );
                case Colour::BrightGreen:   return setColour( "[1;32m" );
                case Colour::BrightWhite:   return setColour( "[1;37m" );

                case Colour::Bright: CATCH_INTERNAL_ERROR( "not a colour" );
            }
        }
        static IColourImpl* instance() {
            static PosixColourImpl s_instance;
            return &s_instance;
        }

    private:
        void setColour( const char* _escapeCode ) {
            Catch::cout() << '\033' << _escapeCode;
        }
    };

    IColourImpl* platformColourInstance() {
        ErrnoGuard guard;
        IConfigPtr config = getCurrentContext().getConfig();
        UseColour::YesOrNo colourMode = config
            ? config->useColour()
            : UseColour::Auto;
        if( colourMode == UseColour::Auto )
            colourMode = isatty(STDOUT_FILENO)
                ? UseColour::Yes
                : UseColour::No;
        return colourMode == UseColour::Yes
            ? PosixColourImpl::instance()
            : NoColourImpl::instance();
    }

} // end anon namespace
} // end namespace Catch

#else  // not Windows or ANSI ///////////////////////////////////////////////

namespace Catch {

    static IColourImpl* platformColourInstance() { return NoColourImpl::instance(); }

} // end namespace Catch

#endif // Windows/ ANSI/ None

namespace Catch {

    Colour::Colour( Code _colourCode ) { use( _colourCode ); }
    Colour::Colour( Colour&& rhs ) noexcept {
        m_moved = rhs.m_moved;
        rhs.m_moved = true;
    }
    Colour& Colour::operator=( Colour&& rhs ) noexcept {
        m_moved = rhs.m_moved;
        rhs.m_moved  = true;
        return *this;
    }

    Colour::~Colour(){ if( !m_moved ) use( None ); }

    void Colour::use( Code _colourCode ) {
        static IColourImpl* impl = platformColourInstance();
        impl->use( _colourCode );
    }

    std::ostream& operator << ( std::ostream& os, Colour const& ) {
        return os;
    }

} // end namespace Catch
// end catch_console_colour.cpp
// start catch_context.cpp

namespace Catch {

    class Context : public IMutableContext, NonCopyable {

    public: // IContext
        virtual IResultCapture* getResultCapture() override {
            return m_resultCapture;
        }
        virtual IRunner* getRunner() override {
            return m_runner;
        }

        virtual IConfigPtr getConfig() const override {
            return m_config;
        }

    public: // IMutableContext
        virtual void setResultCapture( IResultCapture* resultCapture ) override {
            m_resultCapture = resultCapture;
        }
        virtual void setRunner( IRunner* runner ) override {
            m_runner = runner;
        }
        virtual void setConfig( IConfigPtr const& config ) override {
            m_config = config;
        }

        friend IMutableContext& getCurrentMutableContext();

    private:
        IConfigPtr m_config;
        IRunner* m_runner = nullptr;
        IResultCapture* m_resultCapture = nullptr;
    };

    namespace {
        Context* currentContext = nullptr;
    }
    IMutableContext& getCurrentMutableContext() {
        if( !currentContext )
            currentContext = new Context();
        return *currentContext;
    }
    IContext& getCurrentContext() {
        return getCurrentMutableContext();
    }

    void cleanUpContext() {
        delete currentContext;
        currentContext = nullptr;
    }
}
// end catch_context.cpp
// start catch_debugger.cpp

#ifdef CATCH_PLATFORM_MAC

    #include <assert.h>
    #include <stdbool.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <sys/sysctl.h>

    namespace Catch{

        // The following function is taken directly from the following technical note:
        // http://developer.apple.com/library/mac/#qa/qa2004/qa1361.html

        // Returns true if the current process is being debugged (either
        // running under the debugger or has a debugger attached post facto).
        bool isDebuggerActive(){

            int                 mib[4];
            struct kinfo_proc   info;
            size_t              size;

            // Initialize the flags so that, if sysctl fails for some bizarre
            // reason, we get a predictable result.

            info.kp_proc.p_flag = 0;

            // Initialize mib, which tells sysctl the info we want, in this case
            // we're looking for information about a specific process ID.

            mib[0] = CTL_KERN;
            mib[1] = KERN_PROC;
            mib[2] = KERN_PROC_PID;
            mib[3] = getpid();

            // Call sysctl.

            size = sizeof(info);
            if( sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, nullptr, 0) != 0 ) {
                Catch::cerr() << "\n** Call to sysctl failed - unable to determine if debugger is active **\n" << std::endl;
                return false;
            }

            // We're being debugged if the P_TRACED flag is set.

            return ( (info.kp_proc.p_flag & P_TRACED) != 0 );
        }
    } // namespace Catch

#elif defined(CATCH_PLATFORM_LINUX)
    #include <fstream>
    #include <string>

    namespace Catch{
        // The standard POSIX way of detecting a debugger is to attempt to
        // ptrace() the process, but this needs to be done from a child and not
        // this process itself to still allow attaching to this process later
        // if wanted, so is rather heavy. Under Linux we have the PID of the
        // "debugger" (which doesn't need to be gdb, of course, it could also
        // be strace, for example) in /proc/$PID/status, so just get it from
        // there instead.
        bool isDebuggerActive(){
            // Libstdc++ has a bug, where std::ifstream sets errno to 0
            // This way our users can properly assert over errno values
            ErrnoGuard guard;
            std::ifstream in("/proc/self/status");
            for( std::string line; std::getline(in, line); ) {
                static const int PREFIX_LEN = 11;
                if( line.compare(0, PREFIX_LEN, "TracerPid:\t") == 0 ) {
                    // We're traced if the PID is not 0 and no other PID starts
                    // with 0 digit, so it's enough to check for just a single
                    // character.
                    return line.length() > PREFIX_LEN && line[PREFIX_LEN] != '0';
                }
            }

            return false;
        }
    } // namespace Catch
#elif defined(_MSC_VER)
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
    namespace Catch {
        bool isDebuggerActive() {
            return IsDebuggerPresent() != 0;
        }
    }
#elif defined(__MINGW32__)
    extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
    namespace Catch {
        bool isDebuggerActive() {
            return IsDebuggerPresent() != 0;
        }
    }
#else
    namespace Catch {
       bool isDebuggerActive() { return false; }
    }
#endif // Platform

#ifdef CATCH_PLATFORM_WINDOWS

    namespace Catch {
        void writeToDebugConsole( std::string const& text ) {
            ::OutputDebugStringA( text.c_str() );
        }
    }
#else
    namespace Catch {
        void writeToDebugConsole( std::string const& text ) {
            // !TBD: Need a version for Mac/ XCode and other IDEs
            Catch::cout() << text;
        }
    }
#endif // Platform
// end catch_debugger.cpp
// start catch_errno_guard.cpp

#include <cerrno>

namespace Catch {
        ErrnoGuard::ErrnoGuard():m_oldErrno(errno){}
        ErrnoGuard::~ErrnoGuard() { errno = m_oldErrno; }
}
// end catch_errno_guard.cpp
// start catch_evaluate.cpp

namespace Catch {
namespace Internal {

    const char* operatorName(Operator op) {
        switch (op) {
            case IsEqualTo:
                return "==";
            case IsNotEqualTo:
                return "!=";
            case IsLessThan:
                return "<";
            case IsGreaterThan:
                return ">";
            case IsLessThanOrEqualTo:
                return "<=";
            case IsGreaterThanOrEqualTo:
                return ">=";
            default:
                CATCH_ERROR("Attempting to translate unknown operator!");
        }
    }

    // nullptr_t support based on pull request #154 from Konstantin Baumann
    std::nullptr_t opCast(std::nullptr_t) { return nullptr; }

} // end of namespace Internal
} // end of namespace Catch
// end catch_evaluate.cpp
// start catch_exception_translator_registry.cpp

// start catch_exception_translator_registry.h

#include <vector>
#include <string>
#include <memory>

namespace Catch {

    class ExceptionTranslatorRegistry : public IExceptionTranslatorRegistry {
    public:
        ~ExceptionTranslatorRegistry();
        virtual void registerTranslator( const IExceptionTranslator* translator );
        virtual std::string translateActiveException() const override;
        std::string tryTranslators() const;

    private:
        std::vector<std::unique_ptr<IExceptionTranslator const>> m_translators;
    };
}

// end catch_exception_translator_registry.h
#ifdef __OBJC__
#import "Foundation/Foundation.h"
#endif

namespace Catch {

    ExceptionTranslatorRegistry::~ExceptionTranslatorRegistry() {
    }

    void ExceptionTranslatorRegistry::registerTranslator( const IExceptionTranslator* translator ) {
        m_translators.push_back( std::unique_ptr<const IExceptionTranslator>( translator ) );
    }

    std::string ExceptionTranslatorRegistry::translateActiveException() const {
        try {
#ifdef __OBJC__
            // In Objective-C try objective-c exceptions first
            @try {
                return tryTranslators();
            }
            @catch (NSException *exception) {
                return Catch::toString( [exception description] );
            }
#else
            return tryTranslators();
#endif
        }
        catch( TestFailureException& ) {
            throw;
        }
        catch( std::exception& ex ) {
            return ex.what();
        }
        catch( std::string& msg ) {
            return msg;
        }
        catch( const char* msg ) {
            return msg;
        }
        catch(...) {
            return "Unknown exception";
        }
    }

    std::string ExceptionTranslatorRegistry::tryTranslators() const {
        if( m_translators.empty() )
            throw;
        else
            return m_translators[0]->translate( m_translators.begin()+1, m_translators.end() );
    }
}
// end catch_exception_translator_registry.cpp
// start catch_fatal_condition.cpp

namespace Catch {

    // Report the error condition
    void reportFatal( std::string const& message ) {
        IContext& context = Catch::getCurrentContext();
        IResultCapture* resultCapture = context.getResultCapture();
        resultCapture->handleFatalErrorCondition( message );
    }

} // namespace Catch

#if defined ( CATCH_PLATFORM_WINDOWS ) /////////////////////////////////////////

#  if !defined ( CATCH_CONFIG_WINDOWS_SEH )

namespace Catch {
    void FatalConditionHandler::reset() {}
}

#  else // CATCH_CONFIG_WINDOWS_SEH is defined

namespace Catch {
    struct SignalDefs { DWORD id; const char* name; };

    // There is no 1-1 mapping between signals and windows exceptions.
    // Windows can easily distinguish between SO and SigSegV,
    // but SigInt, SigTerm, etc are handled differently.
    SignalDefs signalDefs[] = {
        { EXCEPTION_ILLEGAL_INSTRUCTION,  "SIGILL - Illegal instruction signal" },
        { EXCEPTION_STACK_OVERFLOW, "SIGSEGV - Stack overflow" },
        { EXCEPTION_ACCESS_VIOLATION, "SIGSEGV - Segmentation violation signal" },
        { EXCEPTION_INT_DIVIDE_BY_ZERO, "Divide by zero error" },
    };

    LONG CALLBACK FatalConditionHandler::handleVectoredException(PEXCEPTION_POINTERS ExceptionInfo) {
        for (int i = 0; i < sizeof(signalDefs) / sizeof(SignalDefs); ++i) {
            if (ExceptionInfo->ExceptionRecord->ExceptionCode == signalDefs[i].id) {
                reportFatal(signalDefs[i].name);
            }
        }
        // If its not an exception we care about, pass it along.
        // This stops us from eating debugger breaks etc.
        return EXCEPTION_CONTINUE_SEARCH;
    }

    FatalConditionHandler::FatalConditionHandler() {
        isSet = true;
        // 32k seems enough for Catch to handle stack overflow,
        // but the value was found experimentally, so there is no strong guarantee
        guaranteeSize = 32 * 1024;
        exceptionHandlerHandle = nullptr;
        // Register as first handler in current chain
        exceptionHandlerHandle = AddVectoredExceptionHandler(1, handleVectoredException);
        // Pass in guarantee size to be filled
        SetThreadStackGuarantee(&guaranteeSize);
    }

    void FatalConditionHandler::reset() {
        if (isSet) {
            // Unregister handler and restore the old guarantee
            RemoveVectoredExceptionHandler(exceptionHandlerHandle);
            SetThreadStackGuarantee(&guaranteeSize);
            exceptionHandlerHandle = nullptr;
            isSet = false;
        }
    }

    FatalConditionHandler::~FatalConditionHandler() {
        reset();
    }

bool FatalConditionHandler::isSet = false;
ULONG FatalConditionHandler::guaranteeSize = 0;
PVOID FatalConditionHandler::exceptionHandlerHandle = nullptr;

} // namespace Catch

#  endif // CATCH_CONFIG_WINDOWS_SEH

#else // Not Windows - assumed to be POSIX compatible //////////////////////////

#  if !defined(CATCH_CONFIG_POSIX_SIGNALS)

namespace Catch {
    void FatalConditionHandler::reset() {}
}

#  else // CATCH_CONFIG_POSIX_SIGNALS is defined

#include <signal.h>

namespace Catch {

    struct SignalDefs {
        int id;
        const char* name;
    };
    SignalDefs signalDefs[] = {
        { SIGINT,  "SIGINT - Terminal interrupt signal" },
        { SIGILL,  "SIGILL - Illegal instruction signal" },
        { SIGFPE,  "SIGFPE - Floating point error signal" },
        { SIGSEGV, "SIGSEGV - Segmentation violation signal" },
        { SIGTERM, "SIGTERM - Termination request signal" },
        { SIGABRT, "SIGABRT - Abort (abnormal termination) signal" }
    };

    void FatalConditionHandler::handleSignal( int sig ) {
        std::string name = "<unknown signal>";
        for (std::size_t i = 0; i < sizeof(signalDefs) / sizeof(SignalDefs); ++i) {
            SignalDefs &def = signalDefs[i];
            if (sig == def.id) {
                name = def.name;
                break;
            }
        }
        reset();
        reportFatal(name);
        raise( sig );
    }

    FatalConditionHandler::FatalConditionHandler() {
        isSet = true;
        stack_t sigStack;
        sigStack.ss_sp = altStackMem;
        sigStack.ss_size = SIGSTKSZ;
        sigStack.ss_flags = 0;
        sigaltstack(&sigStack, &oldSigStack);
        struct sigaction sa = { };

        sa.sa_handler = handleSignal;
        sa.sa_flags = SA_ONSTACK;
        for (std::size_t i = 0; i < sizeof(signalDefs)/sizeof(SignalDefs); ++i) {
            sigaction(signalDefs[i].id, &sa, &oldSigActions[i]);
        }
    }

    FatalConditionHandler::~FatalConditionHandler() {
        reset();
    }

    void FatalConditionHandler::reset() {
        if( isSet ) {
            // Set signals back to previous values -- hopefully nobody overwrote them in the meantime
            for( std::size_t i = 0; i < sizeof(signalDefs)/sizeof(SignalDefs); ++i ) {
                sigaction(signalDefs[i].id, &oldSigActions[i], nullptr);
            }
            // Return the old stack
            sigaltstack(&oldSigStack, nullptr);
            isSet = false;
        }
    }

    bool FatalConditionHandler::isSet = false;
    struct sigaction FatalConditionHandler::oldSigActions[sizeof(signalDefs)/sizeof(SignalDefs)] = {};
    stack_t FatalConditionHandler::oldSigStack = {};
    char FatalConditionHandler::altStackMem[SIGSTKSZ] = {};

} // namespace Catch

#  endif // CATCH_CONFIG_POSIX_SIGNALS

#endif // not Windows
// end catch_fatal_condition.cpp
// start catch_interfaces_reporter.cpp

// start catch_reporter_multi.h

namespace Catch {

    class MultipleReporters : public IStreamingReporter {
        using Reporters = std::vector<IStreamingReporterPtr>;
        Reporters m_reporters;

    public:
        void add( IStreamingReporterPtr&& reporter );

    public: // IStreamingReporter

        ReporterPreferences getPreferences() const override;

        void noMatchingTestCases( std::string const& spec ) override;

    static std::set<Verbosity> getSupportedVerbosities();

        void testRunStarting( TestRunInfo const& testRunInfo ) override;
        void testGroupStarting( GroupInfo const& groupInfo ) override;
        void testCaseStarting( TestCaseInfo const& testInfo ) override;
        void sectionStarting( SectionInfo const& sectionInfo ) override;
        void assertionStarting( AssertionInfo const& assertionInfo ) override;

        // The return value indicates if the messages buffer should be cleared:
        bool assertionEnded( AssertionStats const& assertionStats ) override;
        void sectionEnded( SectionStats const& sectionStats ) override;
        void testCaseEnded( TestCaseStats const& testCaseStats ) override;
        void testGroupEnded( TestGroupStats const& testGroupStats ) override;
        void testRunEnded( TestRunStats const& testRunStats ) override;

        void skipTest( TestCaseInfo const& testInfo ) override;
        bool isMulti() const override;

    };

} // end namespace Catch
// end catch_reporter_multi.h
namespace Catch {

    ReporterConfig::ReporterConfig( IConfigPtr const& _fullConfig )
    :   m_stream( &_fullConfig->stream() ), m_fullConfig( _fullConfig ) {}

    ReporterConfig::ReporterConfig( IConfigPtr const& _fullConfig, std::ostream& _stream )
    :   m_stream( &_stream ), m_fullConfig( _fullConfig ) {}

    std::ostream& ReporterConfig::stream() const { return *m_stream; }
    IConfigPtr ReporterConfig::fullConfig() const { return m_fullConfig; }

    TestRunInfo::TestRunInfo( std::string const& _name ) : name( _name ) {}

    GroupInfo::GroupInfo(  std::string const& _name,
                           std::size_t _groupIndex,
                           std::size_t _groupsCount )
    :   name( _name ),
        groupIndex( _groupIndex ),
        groupsCounts( _groupsCount )
    {}

     AssertionStats::AssertionStats( AssertionResult const& _assertionResult,
                                     std::vector<MessageInfo> const& _infoMessages,
                                     Totals const& _totals )
    :   assertionResult( _assertionResult ),
        infoMessages( _infoMessages ),
        totals( _totals )
    {
        if( assertionResult.hasMessage() ) {
            // Copy message into messages list.
            // !TBD This should have been done earlier, somewhere
            MessageBuilder builder( assertionResult.getTestMacroName(), assertionResult.getSourceInfo(), assertionResult.getResultType() );
            builder << assertionResult.getMessage();
            builder.m_info.message = builder.m_stream.str();

            infoMessages.push_back( builder.m_info );
        }
    }

    SectionStats::SectionStats(  SectionInfo const& _sectionInfo,
                                 Counts const& _assertions,
                                 double _durationInSeconds,
                                 bool _missingAssertions )
    :   sectionInfo( _sectionInfo ),
        assertions( _assertions ),
        durationInSeconds( _durationInSeconds ),
        missingAssertions( _missingAssertions )
    {}

    TestCaseStats::TestCaseStats(  TestCaseInfo const& _testInfo,
                                   Totals const& _totals,
                                   std::string const& _stdOut,
                                   std::string const& _stdErr,
                                   bool _aborting )
    : testInfo( _testInfo ),
        totals( _totals ),
        stdOut( _stdOut ),
        stdErr( _stdErr ),
        aborting( _aborting )
    {}

    TestGroupStats::TestGroupStats( GroupInfo const& _groupInfo,
                                    Totals const& _totals,
                                    bool _aborting )
    :   groupInfo( _groupInfo ),
        totals( _totals ),
        aborting( _aborting )
    {}

    TestGroupStats::TestGroupStats( GroupInfo const& _groupInfo )
    :   groupInfo( _groupInfo ),
        aborting( false )
    {}

    TestRunStats::TestRunStats(   TestRunInfo const& _runInfo,
                    Totals const& _totals,
                    bool _aborting )
    :   runInfo( _runInfo ),
        totals( _totals ),
        aborting( _aborting )
    {}

    bool IStreamingReporter::isMulti() const { return false; }

    void addReporter( IStreamingReporterPtr& existingReporter, IStreamingReporterPtr&& additionalReporter ) {

        if( !existingReporter ) {
            existingReporter = std::move( additionalReporter );
            return;
        }

        MultipleReporters* multi = nullptr;

        if( existingReporter->isMulti() ) {
            multi = static_cast<MultipleReporters*>( existingReporter.get() );
        }
        else {
            auto newMulti = std::unique_ptr<MultipleReporters>( new MultipleReporters );
            newMulti->add( std::move( existingReporter ) );
            multi = newMulti.get();
            existingReporter = std::move( newMulti );
        }
        multi->add( std::move( additionalReporter ) );
    }

} // end namespace Catch
// end catch_interfaces_reporter.cpp
// start catch_leak_detector.cpp

namespace Catch {

#ifdef CATCH_CONFIG_WINDOWS_CRTDBG
#include <crtdbg.h>

	LeakDetector::LeakDetector() {
		int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		flag |= _CRTDBG_LEAK_CHECK_DF;
		flag |= _CRTDBG_ALLOC_MEM_DF;
		_CrtSetDbgFlag(flag);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
		// Change this to leaking allocation's number to break there
		_CrtSetBreakAlloc(-1);
	}

#else

    LeakDetector::LeakDetector(){}

#endif

}
// end catch_leak_detector.cpp
// start catch_list.cpp

#include <limits>
#include <algorithm>
#include <iomanip>

namespace Catch {

    std::size_t listTests( Config const& config ) {
        TestSpec testSpec = config.testSpec();
        if( config.testSpec().hasFilters() )
            Catch::cout() << "Matching test cases:\n";
        else {
            Catch::cout() << "All available test cases:\n";
            testSpec = TestSpecParser( ITagAliasRegistry::get() ).parse( "*" ).testSpec();
        }

        auto matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const& testCaseInfo : matchedTestCases ) {
            Colour::Code colour = testCaseInfo.isHidden()
                ? Colour::SecondaryText
                : Colour::None;
            Colour colourGuard( colour );

            Catch::cout() << Column( testCaseInfo.name ).initialIndent( 2 ).indent( 4 ) << "\n";
            if( config.verbosity() >= Verbosity::High ) {
                Catch::cout() << Column( Catch::Detail::stringify( testCaseInfo.lineInfo ) ).indent(4) << std::endl;
                std::string description = testCaseInfo.description;
                if( description.empty() )
                    description = "(NO DESCRIPTION)";
                Catch::cout() << Column( description ).indent(4) << std::endl;
            }
            if( !testCaseInfo.tags.empty() )
                Catch::cout() << Column( testCaseInfo.tagsAsString() ).indent( 6 ) << "\n";
        }

        if( !config.testSpec().hasFilters() )
            Catch::cout() << pluralise( matchedTestCases.size(), "test case" ) << '\n' << std::endl;
        else
            Catch::cout() << pluralise( matchedTestCases.size(), "matching test case" ) << '\n' << std::endl;
        return matchedTestCases.size();
    }

    std::size_t listTestsNamesOnly( Config const& config ) {
        TestSpec testSpec = config.testSpec();
        if( !config.testSpec().hasFilters() )
            testSpec = TestSpecParser( ITagAliasRegistry::get() ).parse( "*" ).testSpec();
        std::size_t matchedTests = 0;
        std::vector<TestCase> matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const& testCaseInfo : matchedTestCases ) {
            matchedTests++;
            if( startsWith( testCaseInfo.name, '#' ) )
               Catch::cout() << '"' << testCaseInfo.name << '"';
            else
               Catch::cout() << testCaseInfo.name;
            if ( config.verbosity() >= Verbosity::High )
                Catch::cout() << "\t@" << testCaseInfo.lineInfo;
            Catch::cout() << std::endl;
        }
        return matchedTests;
    }

    void TagInfo::add( std::string const& spelling ) {
        ++count;
        spellings.insert( spelling );
    }

    std::string TagInfo::all() const {
        std::string out;
        for( auto const& spelling : spellings )
            out += "[" + spelling + "]";
        return out;
    }

    std::size_t listTags( Config const& config ) {
        TestSpec testSpec = config.testSpec();
        if( config.testSpec().hasFilters() )
            Catch::cout() << "Tags for matching test cases:\n";
        else {
            Catch::cout() << "All available tags:\n";
            testSpec = TestSpecParser( ITagAliasRegistry::get() ).parse( "*" ).testSpec();
        }

        std::map<std::string, TagInfo> tagCounts;

        std::vector<TestCase> matchedTestCases = filterTests( getAllTestCasesSorted( config ), testSpec, config );
        for( auto const& testCase : matchedTestCases ) {
            for( auto const& tagName : testCase.getTestCaseInfo().tags ) {
                std::string lcaseTagName = toLower( tagName );
                auto countIt = tagCounts.find( lcaseTagName );
                if( countIt == tagCounts.end() )
                    countIt = tagCounts.insert( std::make_pair( lcaseTagName, TagInfo() ) ).first;
                countIt->second.add( tagName );
            }
        }

        for( auto const& tagCount : tagCounts ) {
            std::ostringstream oss;
            oss << "  " << std::setw(2) << tagCount.second.count << "  ";
            auto wrapper = Column( tagCount.second.all() )
                                                    .initialIndent( 0 )
                                                    .indent( oss.str().size() )
                                                    .width( CATCH_CONFIG_CONSOLE_WIDTH-10 );
            Catch::cout() << oss.str() << wrapper << '\n';
        }
        Catch::cout() << pluralise( tagCounts.size(), "tag" ) << '\n' << std::endl;
        return tagCounts.size();
    }

    std::size_t listReporters( Config const& /*config*/ ) {
        Catch::cout() << "Available reporters:\n";
        IReporterRegistry::FactoryMap const& factories = getRegistryHub().getReporterRegistry().getFactories();
        std::size_t maxNameLen = 0;
        for( auto const& factoryKvp : factories )
            maxNameLen = (std::max)( maxNameLen, factoryKvp.first.size() );

        for( auto const& factoryKvp : factories ) {
            Catch::cout()
                    << Column( factoryKvp.first + ":" )
                            .indent(2)
                            .width( 5+maxNameLen )
                    +  Column( factoryKvp.second->getDescription() )
                            .initialIndent(0)
                            .indent(2)
                            .width( CATCH_CONFIG_CONSOLE_WIDTH - maxNameLen-8 )
                    << "\n";
        }
        Catch::cout() << std::endl;
        return factories.size();
    }

    Option<std::size_t> list( Config const& config ) {
        Option<std::size_t> listedCount;
        if( config.listTests() )
            listedCount = listedCount.valueOr(0) + listTests( config );
        if( config.listTestNamesOnly() )
            listedCount = listedCount.valueOr(0) + listTestsNamesOnly( config );
        if( config.listTags() )
            listedCount = listedCount.valueOr(0) + listTags( config );
        if( config.listReporters() )
            listedCount = listedCount.valueOr(0) + listReporters( config );
        return listedCount;
    }

} // end namespace Catch
// end catch_list.cpp
// start catch_matchers.cpp

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

namespace Catch {
namespace Matchers {
    namespace Impl {

        std::string MatcherUntypedBase::toString() const {
            if( m_cachedToString.empty() )
                m_cachedToString = describe();
            return m_cachedToString;
        }

    } // namespace Impl
} // namespace Matchers

using namespace Matchers;
using Matchers::Impl::MatcherBase;

} // namespace Catch

#endif // CATCH_CONFIG_DISABLE_MATCHERS
// end catch_matchers.cpp
// start catch_matchers_string.cpp

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)

namespace Catch {
namespace Matchers {

    namespace StdString {

        CasedString::CasedString( std::string const& str, CaseSensitive::Choice caseSensitivity )
        :   m_caseSensitivity( caseSensitivity ),
            m_str( adjustString( str ) )
        {}
        std::string CasedString::adjustString( std::string const& str ) const {
            return m_caseSensitivity == CaseSensitive::No
                   ? toLower( str )
                   : str;
        }
        std::string CasedString::caseSensitivitySuffix() const {
            return m_caseSensitivity == CaseSensitive::No
                   ? " (case insensitive)"
                   : std::string();
        }

        StringMatcherBase::StringMatcherBase( std::string const& operation, CasedString const& comparator )
        : m_comparator( comparator ),
          m_operation( operation ) {
        }

        std::string StringMatcherBase::describe() const {
            std::string description;
            description.reserve(5 + m_operation.size() + m_comparator.m_str.size() +
                                        m_comparator.caseSensitivitySuffix().size());
            description += m_operation;
            description += ": \"";
            description += m_comparator.m_str;
            description += "\"";
            description += m_comparator.caseSensitivitySuffix();
            return description;
        }

        EqualsMatcher::EqualsMatcher( CasedString const& comparator ) : StringMatcherBase( "equals", comparator ) {}

        bool EqualsMatcher::match( std::string const& source ) const {
            return m_comparator.adjustString( source ) == m_comparator.m_str;
        }

        ContainsMatcher::ContainsMatcher( CasedString const& comparator ) : StringMatcherBase( "contains", comparator ) {}

        bool ContainsMatcher::match( std::string const& source ) const {
            return contains( m_comparator.adjustString( source ), m_comparator.m_str );
        }

        StartsWithMatcher::StartsWithMatcher( CasedString const& comparator ) : StringMatcherBase( "starts with", comparator ) {}

        bool StartsWithMatcher::match( std::string const& source ) const {
            return startsWith( m_comparator.adjustString( source ), m_comparator.m_str );
        }

        EndsWithMatcher::EndsWithMatcher( CasedString const& comparator ) : StringMatcherBase( "ends with", comparator ) {}

        bool EndsWithMatcher::match( std::string const& source ) const {
            return endsWith( m_comparator.adjustString( source ), m_comparator.m_str );
        }

    } // namespace StdString

    StdString::EqualsMatcher Equals( std::string const& str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::EqualsMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::ContainsMatcher Contains( std::string const& str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::ContainsMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::EndsWithMatcher EndsWith( std::string const& str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::EndsWithMatcher( StdString::CasedString( str, caseSensitivity) );
    }
    StdString::StartsWithMatcher StartsWith( std::string const& str, CaseSensitive::Choice caseSensitivity ) {
        return StdString::StartsWithMatcher( StdString::CasedString( str, caseSensitivity) );
    }

} // namespace Matchers
} // namespace Catch

#endif // CATCH_CONFIG_DISABLE_MATCHERS
// end catch_matchers_string.cpp
// start catch_message.cpp

namespace Catch {

    MessageInfo::MessageInfo(   std::string const& _macroName,
                                SourceLineInfo const& _lineInfo,
                                ResultWas::OfType _type )
    :   macroName( _macroName ),
        lineInfo( _lineInfo ),
        type( _type ),
        sequence( ++globalCount )
    {}

    bool MessageInfo::operator==( MessageInfo const& other ) const {
        return sequence == other.sequence;
    }

    bool MessageInfo::operator<( MessageInfo const& other ) const {
        return sequence < other.sequence;
    }

    // This may need protecting if threading support is added
    unsigned int MessageInfo::globalCount = 0;

    ////////////////////////////////////////////////////////////////////////////

    Catch::MessageBuilder::MessageBuilder( std::string const& macroName,
                                           SourceLineInfo const& lineInfo,
                                           ResultWas::OfType type )
        :m_info(macroName, lineInfo, type) {}

    ////////////////////////////////////////////////////////////////////////////

    ScopedMessage::ScopedMessage( MessageBuilder const& builder )
    : m_info( builder.m_info )
    {
        m_info.message = builder.m_stream.str();
        getResultCapture().pushScopedMessage( m_info );
    }

    ScopedMessage::~ScopedMessage() {
        if ( !std::uncaught_exception() ){
            getResultCapture().popScopedMessage(m_info);
        }
    }

} // end namespace Catch
// end catch_message.cpp
// start catch_notimplemented_exception.cpp

#include <sstream>

namespace Catch {

    NotImplementedException::NotImplementedException( SourceLineInfo const& lineInfo )
    :   m_lineInfo( lineInfo ) {
        std::ostringstream oss;
        oss << lineInfo << ": function ";
        oss << "not implemented";
        m_what = oss.str();
    }

    const char* NotImplementedException::what() const noexcept {
        return m_what.c_str();
    }

} // end namespace Catch
// end catch_notimplemented_exception.cpp
// start catch_registry_hub.cpp

// start catch_test_case_registry_impl.hpp

#include <vector>
#include <set>
#include <algorithm>
#include <ios>

namespace Catch {

    class TestCase;
    struct IConfig;

    struct RandomNumberGenerator {
        using result_type = std::ptrdiff_t;

        result_type operator()( result_type n ) const;

        static constexpr result_type min() { return 0; }
        static constexpr result_type max() { return 1000000; }
        result_type operator()() const;
        template<typename V>
        static void shuffle( V& vector ) {
            RandomNumberGenerator rng;
            std::shuffle( vector.begin(), vector.end(), rng );
        }
    };

    std::vector<TestCase> sortTests( IConfig const& config, std::vector<TestCase> const& unsortedTestCases );
    bool matchTest( TestCase const& testCase, TestSpec const& testSpec, IConfig const& config );

    void enforceNoDuplicateTestCases( std::vector<TestCase> const& functions );

    std::vector<TestCase> filterTests( std::vector<TestCase> const& testCases, TestSpec const& testSpec, IConfig const& config );
    std::vector<TestCase> const& getAllTestCasesSorted( IConfig const& config );

    class TestRegistry : public ITestCaseRegistry {
    public:
        virtual ~TestRegistry() = default;

        virtual void registerTest( TestCase const& testCase );

        std::vector<TestCase> const& getAllTests() const override;
        std::vector<TestCase> const& getAllTestsSorted( IConfig const& config ) const override;

    private:
        std::vector<TestCase> m_functions;
        mutable RunTests::InWhatOrder m_currentSortOrder = RunTests::InDeclarationOrder;
        mutable std::vector<TestCase> m_sortedFunctions;
        size_t m_unnamedCount = 0;
        std::ios_base::Init m_ostreamInit; // Forces cout/ cerr to be initialised
    };

    ///////////////////////////////////////////////////////////////////////////

    class TestInvokerAsFunction : public ITestInvoker {
        void(*m_testAsFunction)();
    public:
        TestInvokerAsFunction( void(*testAsFunction)() ) noexcept;

        void invoke() const override;
    };

    std::string extractClassName( std::string const& classOrQualifiedMethodName );

    ///////////////////////////////////////////////////////////////////////////

} // end namespace Catch

// end catch_test_case_registry_impl.hpp
// start catch_reporter_registry.hpp

#include <map>

namespace Catch {

    class ReporterRegistry : public IReporterRegistry {

    public:

        ~ReporterRegistry() override {}

        IStreamingReporterPtr create( std::string const& name, IConfigPtr const& config ) const override {
            FactoryMap::const_iterator it =  m_factories.find( name );
            if( it == m_factories.end() )
                return nullptr;
            return it->second->create( ReporterConfig( config ) );
        }

        void registerReporter( std::string const& name, IReporterFactoryPtr const& factory ) {
            m_factories.insert( { name, factory } );
        }
        void registerListener( IReporterFactoryPtr const& factory ) {
            m_listeners.push_back( factory );
        }

        FactoryMap const& getFactories() const override {
            return m_factories;
        }
        Listeners const& getListeners() const override {
            return m_listeners;
        }

    private:
        FactoryMap m_factories;
        Listeners m_listeners;
    };
}

// end catch_reporter_registry.hpp
// start catch_tag_alias_registry.h

// start catch_tag_alias.h

#include <string>

namespace Catch {

    struct TagAlias {
        TagAlias(std::string const& _tag, SourceLineInfo _lineInfo);

        std::string tag;
        SourceLineInfo lineInfo;
    };

} // end namespace Catch

// end catch_tag_alias.h
#include <map>

namespace Catch {

    class TagAliasRegistry : public ITagAliasRegistry {
    public:
        ~TagAliasRegistry() override;
        TagAlias const* find( std::string const& alias ) const override;
        std::string expandAliases( std::string const& unexpandedTestSpec ) const override;
        void add( std::string const& alias, std::string const& tag, SourceLineInfo const& lineInfo );

    private:
        std::map<std::string, TagAlias> m_registry;
    };

} // end namespace Catch

// end catch_tag_alias_registry.h
namespace Catch {

    namespace {

        class RegistryHub : public IRegistryHub, public IMutableRegistryHub,
                            private NonCopyable {

        public: // IRegistryHub
            RegistryHub() {
            }
            IReporterRegistry const& getReporterRegistry() const override {
                return m_reporterRegistry;
            }
            ITestCaseRegistry const& getTestCaseRegistry() const override {
                return m_testCaseRegistry;
            }
            IExceptionTranslatorRegistry& getExceptionTranslatorRegistry() override {
                return m_exceptionTranslatorRegistry;
            }
            ITagAliasRegistry const& getTagAliasRegistry() const override {
                return m_tagAliasRegistry;
            }
            StartupExceptionRegistry const& getStartupExceptionRegistry() const override {
                return m_exceptionRegistry;
            }

        public: // IMutableRegistryHub
            void registerReporter( std::string const& name, IReporterFactoryPtr const& factory ) override {
                m_reporterRegistry.registerReporter( name, factory );
            }
            void registerListener( IReporterFactoryPtr const& factory ) override {
                m_reporterRegistry.registerListener( factory );
            }
            void registerTest( TestCase const& testInfo ) override {
                m_testCaseRegistry.registerTest( testInfo );
            }
            void registerTranslator( const IExceptionTranslator* translator ) override {
                m_exceptionTranslatorRegistry.registerTranslator( translator );
            }
            void registerTagAlias( std::string const& alias, std::string const& tag, SourceLineInfo const& lineInfo ) override {
                m_tagAliasRegistry.add( alias, tag, lineInfo );
            }
            void registerStartupException() noexcept override {
                m_exceptionRegistry.add(std::current_exception());
            }

        private:
            TestRegistry m_testCaseRegistry;
            ReporterRegistry m_reporterRegistry;
            ExceptionTranslatorRegistry m_exceptionTranslatorRegistry;
            TagAliasRegistry m_tagAliasRegistry;
            StartupExceptionRegistry m_exceptionRegistry;
        };

        // Single, global, instance
        RegistryHub*& getTheRegistryHub() {
            static RegistryHub* theRegistryHub = nullptr;
            if( !theRegistryHub )
                theRegistryHub = new RegistryHub();
            return theRegistryHub;
        }
    }

    IRegistryHub& getRegistryHub() {
        return *getTheRegistryHub();
    }
    IMutableRegistryHub& getMutableRegistryHub() {
        return *getTheRegistryHub();
    }
    void cleanUp() {
        delete getTheRegistryHub();
        getTheRegistryHub() = nullptr;
        cleanUpContext();
    }
    std::string translateActiveException() {
        return getRegistryHub().getExceptionTranslatorRegistry().translateActiveException();
    }

} // end namespace Catch
// end catch_registry_hub.cpp
// start catch_result_builder.cpp

#include <cassert>

namespace Catch {

    CopyableStream::CopyableStream( CopyableStream const& other ) {
        oss << other.oss.str();
    }
    CopyableStream& CopyableStream::operator=( CopyableStream const& other ) {
        oss.str(std::string());
        oss << other.oss.str();
        return *this;
    }

    ResultBuilder::ResultBuilder(   char const* macroName,
                                    SourceLineInfo const& lineInfo,
                                    char const* capturedExpression,
                                    ResultDisposition::Flags resultDisposition )
    :   m_assertionInfo( macroName, lineInfo, capturedExpression, resultDisposition)
    {
        getCurrentContext().getResultCapture()->assertionStarting( m_assertionInfo );
    }

    ResultBuilder::~ResultBuilder() {
#if defined(CATCH_CONFIG_FAST_COMPILE)
        if ( m_guardException ) {
            stream().oss << "Exception translation was disabled by CATCH_CONFIG_FAST_COMPILE";
            captureResult( ResultWas::ThrewException );
            getCurrentContext().getResultCapture()->exceptionEarlyReported();
        }
#endif
    }

    ResultBuilder& ResultBuilder::setResultType( ResultWas::OfType result ) {
        m_data.resultType = result;
        return *this;
    }
    ResultBuilder& ResultBuilder::setResultType( bool result ) {
        m_data.resultType = result ? ResultWas::Ok : ResultWas::ExpressionFailed;
        return *this;
    }

    void ResultBuilder::endExpression( DecomposedExpression const& expr ) {
        // Flip bool results if FalseTest flag is set
        if( isFalseTest( m_assertionInfo.resultDisposition ) ) {
            m_data.negate( expr.isBinaryExpression() );
        }

        getResultCapture().assertionRun();

        if(getCurrentContext().getConfig()->includeSuccessfulResults()
            || m_data.resultType != ResultWas::Ok) {
            AssertionResult result = build( expr );
            handleResult( result );
        }
        else
            getResultCapture().assertionPassed();
    }

    void ResultBuilder::useActiveException( ResultDisposition::Flags resultDisposition ) {
        m_assertionInfo.resultDisposition = resultDisposition;
        stream().oss << Catch::translateActiveException();
        captureResult( ResultWas::ThrewException );
    }

    void ResultBuilder::captureResult( ResultWas::OfType resultType ) {
        setResultType( resultType );
        captureExpression();
    }
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
    void ResultBuilder::captureExpectedException( std::string const& expectedMessage ) {
        if( expectedMessage.empty() )
            captureExpectedException( Matchers::Impl::MatchAllOf<std::string>() );
        else
            captureExpectedException( Matchers::Equals( expectedMessage ) );
    }

    void ResultBuilder::captureExpectedException( Matchers::Impl::MatcherBase<std::string> const& matcher ) {

        assert( !isFalseTest( m_assertionInfo.resultDisposition ) );
        AssertionResultData data = m_data;
        data.resultType = ResultWas::Ok;
        data.reconstructedExpression = m_assertionInfo.capturedExpression;

        std::string actualMessage = Catch::translateActiveException();
        if( !matcher.match( actualMessage ) ) {
            data.resultType = ResultWas::ExpressionFailed;
            data.reconstructedExpression = std::move(actualMessage);
        }
        AssertionResult result( m_assertionInfo, data );
        handleResult( result );
    }
#endif // CATCH_CONFIG_DISABLE_MATCHERS
    void ResultBuilder::captureExpression() {
        AssertionResult result = build();
        handleResult( result );
    }

    void ResultBuilder::handleResult( AssertionResult const& result )
    {
        getResultCapture().assertionEnded( result );

        if( !result.isOk() ) {
            if( getCurrentContext().getConfig()->shouldDebugBreak() )
                m_shouldDebugBreak = true;
            if( getCurrentContext().getRunner()->aborting() || (m_assertionInfo.resultDisposition & ResultDisposition::Normal) )
                m_shouldThrow = true;
        }
    }

    void ResultBuilder::react() {
#if defined(CATCH_CONFIG_FAST_COMPILE)
        if (m_shouldDebugBreak) {
            ///////////////////////////////////////////////////////////////////
            // To inspect the state during test, you need to go one level up the callstack
            // To go back to the test and change execution, jump over the throw statement
            ///////////////////////////////////////////////////////////////////
            CATCH_BREAK_INTO_DEBUGGER();
        }
#endif
        if( m_shouldThrow )
            throw Catch::TestFailureException();
    }

    bool ResultBuilder::shouldDebugBreak() const { return m_shouldDebugBreak; }
    bool ResultBuilder::allowThrows() const { return getCurrentContext().getConfig()->allowThrows(); }

    AssertionResult ResultBuilder::build() const
    {
        return build( *this );
    }

    // CAVEAT: The returned AssertionResult stores a pointer to the argument expr,
    //         a temporary DecomposedExpression, which in turn holds references to
    //         operands, possibly temporary as well.
    //         It should immediately be passed to handleResult; if the expression
    //         needs to be reported, its string expansion must be composed before
    //         the temporaries are destroyed.
    AssertionResult ResultBuilder::build( DecomposedExpression const& expr ) const {
        assert( m_data.resultType != ResultWas::Unknown );
        AssertionResultData data = m_data;

        if(m_usedStream)
            data.message = s_stream().oss.str();
        data.decomposedExpression = &expr; // for lazy reconstruction
        return AssertionResult( m_assertionInfo, data );
    }

    void ResultBuilder::reconstructExpression( std::string& dest ) const {
        dest = m_assertionInfo.capturedExpression;
    }

    void ResultBuilder::setExceptionGuard() {
        m_guardException = true;
    }
    void ResultBuilder::unsetExceptionGuard() {
        m_guardException = false;
    }

    CopyableStream& ResultBuilder::stream() {
        if( !m_usedStream ) {
            m_usedStream = true;
            s_stream().oss.str("");
        }
        return s_stream();
    }

    CopyableStream& ResultBuilder::s_stream() {
        static CopyableStream s;
        return s;
    }

} // end namespace Catch
// end catch_result_builder.cpp
// start catch_result_type.cpp

namespace Catch {

    bool isOk( ResultWas::OfType resultType ) {
        return ( resultType & ResultWas::FailureBit ) == 0;
    }
    bool isJustInfo( int flags ) {
        return flags == ResultWas::Info;
    }

    ResultDisposition::Flags operator | ( ResultDisposition::Flags lhs, ResultDisposition::Flags rhs ) {
        return static_cast<ResultDisposition::Flags>( static_cast<int>( lhs ) | static_cast<int>( rhs ) );
    }

    bool shouldContinueOnFailure( int flags )    { return ( flags & ResultDisposition::ContinueOnFailure ) != 0; }
    bool isFalseTest( int flags )                { return ( flags & ResultDisposition::FalseTest ) != 0; }
    bool shouldSuppressFailure( int flags )      { return ( flags & ResultDisposition::SuppressFail ) != 0; }

} // end namespace Catch
// end catch_result_type.cpp
// start catch_run_context.cpp

#include <cassert>
#include <algorithm>

namespace Catch {

    StreamRedirect::StreamRedirect(std::ostream& stream, std::string& targetString)
        : m_stream(stream),
        m_prevBuf(stream.rdbuf()),
        m_targetString(targetString) {
        stream.rdbuf(m_oss.rdbuf());
    }

    StreamRedirect::~StreamRedirect() {
        m_targetString += m_oss.str();
        m_stream.rdbuf(m_prevBuf);
    }

    RunContext::RunContext(IConfigPtr const& _config, IStreamingReporterPtr&& reporter)
        : m_runInfo(_config->name()),
        m_context(getCurrentMutableContext()),
        m_config(_config),
        m_reporter(std::move(reporter)) {
        m_context.setRunner(this);
        m_context.setConfig(m_config);
        m_context.setResultCapture(this);
        m_reporter->testRunStarting(m_runInfo);
    }

    RunContext::~RunContext() {
        m_reporter->testRunEnded(TestRunStats(m_runInfo, m_totals, aborting()));
    }

    void RunContext::testGroupStarting(std::string const& testSpec, std::size_t groupIndex, std::size_t groupsCount) {
        m_reporter->testGroupStarting(GroupInfo(testSpec, groupIndex, groupsCount));
    }

    void RunContext::testGroupEnded(std::string const& testSpec, Totals const& totals, std::size_t groupIndex, std::size_t groupsCount) {
        m_reporter->testGroupEnded(TestGroupStats(GroupInfo(testSpec, groupIndex, groupsCount), totals, aborting()));
    }

    Totals RunContext::runTest(TestCase const& testCase) {
        Totals prevTotals = m_totals;

        std::string redirectedCout;
        std::string redirectedCerr;

        TestCaseInfo testInfo = testCase.getTestCaseInfo();

        m_reporter->testCaseStarting(testInfo);

        m_activeTestCase = &testCase;

        ITracker& rootTracker = m_trackerContext.startRun();
        assert(rootTracker.isSectionTracker());
        static_cast<SectionTracker&>(rootTracker).addInitialFilters(m_config->getSectionsToRun());
        do {
            m_trackerContext.startCycle();
            m_testCaseTracker = &SectionTracker::acquire(m_trackerContext, TestCaseTracking::NameAndLocation(testInfo.name, testInfo.lineInfo));
            runCurrentTest(redirectedCout, redirectedCerr);
        } while (!m_testCaseTracker->isSuccessfullyCompleted() && !aborting());

        Totals deltaTotals = m_totals.delta(prevTotals);
        if (testInfo.expectedToFail() && deltaTotals.testCases.passed > 0) {
            deltaTotals.assertions.failed++;
            deltaTotals.testCases.passed--;
            deltaTotals.testCases.failed++;
        }
        m_totals.testCases += deltaTotals.testCases;
        m_reporter->testCaseEnded(TestCaseStats(testInfo,
                                  deltaTotals,
                                  redirectedCout,
                                  redirectedCerr,
                                  aborting()));

        m_activeTestCase = nullptr;
        m_testCaseTracker = nullptr;

        return deltaTotals;
    }

    IConfigPtr RunContext::config() const {
        return m_config;
    }

    IStreamingReporter& RunContext::reporter() const {
        return *m_reporter;
    }

    void RunContext::assertionStarting(AssertionInfo const& info) {
        m_reporter->assertionStarting( info );
    }
    void RunContext::assertionEnded(AssertionResult const & result) {
        if (result.getResultType() == ResultWas::Ok) {
            m_totals.assertions.passed++;
        } else if (!result.isOk()) {
            m_totals.assertions.failed++;
        }

        // We have no use for the return value (whether messages should be cleared), because messages were made scoped
        // and should be let to clear themselves out.
        static_cast<void>(m_reporter->assertionEnded(AssertionStats(result, m_messages, m_totals)));

        // Reset working state
        m_lastAssertionInfo = AssertionInfo("", m_lastAssertionInfo.lineInfo, "{Unknown expression after the reported line}", m_lastAssertionInfo.resultDisposition);
        m_lastResult = result;
    }

    bool RunContext::sectionStarted(SectionInfo const & sectionInfo, Counts & assertions) {
        ITracker& sectionTracker = SectionTracker::acquire(m_trackerContext, TestCaseTracking::NameAndLocation(sectionInfo.name, sectionInfo.lineInfo));
        if (!sectionTracker.isOpen())
            return false;
        m_activeSections.push_back(&sectionTracker);

        m_lastAssertionInfo.lineInfo = sectionInfo.lineInfo;

        m_reporter->sectionStarting(sectionInfo);

        assertions = m_totals.assertions;

        return true;
    }

    bool RunContext::testForMissingAssertions(Counts& assertions) {
        if (assertions.total() != 0)
            return false;
        if (!m_config->warnAboutMissingAssertions())
            return false;
        if (m_trackerContext.currentTracker().hasChildren())
            return false;
        m_totals.assertions.failed++;
        assertions.failed++;
        return true;
    }

    void RunContext::sectionEnded(SectionEndInfo const & endInfo) {
        Counts assertions = m_totals.assertions - endInfo.prevAssertions;
        bool missingAssertions = testForMissingAssertions(assertions);

        if (!m_activeSections.empty()) {
            m_activeSections.back()->close();
            m_activeSections.pop_back();
        }

        m_reporter->sectionEnded(SectionStats(endInfo.sectionInfo, assertions, endInfo.durationInSeconds, missingAssertions));
        m_messages.clear();
    }

    void RunContext::sectionEndedEarly(SectionEndInfo const & endInfo) {
        if (m_unfinishedSections.empty())
            m_activeSections.back()->fail();
        else
            m_activeSections.back()->close();
        m_activeSections.pop_back();

        m_unfinishedSections.push_back(endInfo);
    }
    void RunContext::benchmarkStarting( BenchmarkInfo const& info ) {
        m_reporter->benchmarkStarting( info );
    }
    void RunContext::benchmarkEnded( BenchmarkStats const& stats ) {
        m_reporter->benchmarkEnded( stats );
    }

    void RunContext::pushScopedMessage(MessageInfo const & message) {
        m_messages.push_back(message);
    }

    void RunContext::popScopedMessage(MessageInfo const & message) {
        m_messages.erase(std::remove(m_messages.begin(), m_messages.end(), message), m_messages.end());
    }

    std::string RunContext::getCurrentTestName() const {
        return m_activeTestCase
            ? m_activeTestCase->getTestCaseInfo().name
            : std::string();
    }

    const AssertionResult * RunContext::getLastResult() const {
        return &m_lastResult;
    }

    void RunContext::exceptionEarlyReported() {
        m_shouldReportUnexpected = false;
    }

    void RunContext::handleFatalErrorCondition(std::string const & message) {
        // Don't rebuild the result -- the stringification itself can cause more fatal errors
        // Instead, fake a result data.
        AssertionResultData tempResult;
        tempResult.resultType = ResultWas::FatalErrorCondition;
        tempResult.message = message;
        AssertionResult result(m_lastAssertionInfo, tempResult);

        getResultCapture().assertionEnded(result);

        handleUnfinishedSections();

        // Recreate section for test case (as we will lose the one that was in scope)
        TestCaseInfo const& testCaseInfo = m_activeTestCase->getTestCaseInfo();
        SectionInfo testCaseSection(testCaseInfo.lineInfo, testCaseInfo.name, testCaseInfo.description);

        Counts assertions;
        assertions.failed = 1;
        SectionStats testCaseSectionStats(testCaseSection, assertions, 0, false);
        m_reporter->sectionEnded(testCaseSectionStats);

        TestCaseInfo testInfo = m_activeTestCase->getTestCaseInfo();

        Totals deltaTotals;
        deltaTotals.testCases.failed = 1;
        m_reporter->testCaseEnded(TestCaseStats(testInfo,
                                  deltaTotals,
                                  std::string(),
                                  std::string(),
                                  false));
        m_totals.testCases.failed++;
        testGroupEnded(std::string(), m_totals, 1, 1);
        m_reporter->testRunEnded(TestRunStats(m_runInfo, m_totals, false));
    }

    bool RunContext::lastAssertionPassed() {
         return m_totals.assertions.passed == (m_prevPassed + 1);
    }

    void RunContext::assertionPassed() {
        ++m_totals.assertions.passed;
        m_lastAssertionInfo.capturedExpression = "{Unknown expression after the reported line}";
        m_lastAssertionInfo.macroName = "";
    }

    void RunContext::assertionRun() {
        m_prevPassed = m_totals.assertions.passed;
    }

    bool RunContext::aborting() const {
        return m_totals.assertions.failed == static_cast<std::size_t>(m_config->abortAfter());
    }

    void RunContext::runCurrentTest(std::string & redirectedCout, std::string & redirectedCerr) {
        TestCaseInfo const& testCaseInfo = m_activeTestCase->getTestCaseInfo();
        SectionInfo testCaseSection(testCaseInfo.lineInfo, testCaseInfo.name, testCaseInfo.description);
        m_reporter->sectionStarting(testCaseSection);
        Counts prevAssertions = m_totals.assertions;
        double duration = 0;
        m_shouldReportUnexpected = true;
        try {
            m_lastAssertionInfo = AssertionInfo("TEST_CASE", testCaseInfo.lineInfo, "", ResultDisposition::Normal);

            seedRng(*m_config);

            Timer timer;
            timer.start();
            if (m_reporter->getPreferences().shouldRedirectStdOut) {
                StreamRedirect coutRedir(cout(), redirectedCout);
                StreamRedirect cerrRedir(cerr(), redirectedCerr);
                invokeActiveTestCase();
            } else {
                invokeActiveTestCase();
            }
            duration = timer.getElapsedSeconds();
        } catch (TestFailureException&) {
            // This just means the test was aborted due to failure
        } catch (...) {
            // Under CATCH_CONFIG_FAST_COMPILE, unexpected exceptions under REQUIRE assertions
            // are reported without translation at the point of origin.
            if (m_shouldReportUnexpected) {
                makeUnexpectedResultBuilder().useActiveException();
            }
        }
        m_testCaseTracker->close();
        handleUnfinishedSections();
        m_messages.clear();

        Counts assertions = m_totals.assertions - prevAssertions;
        bool missingAssertions = testForMissingAssertions(assertions);

        if (testCaseInfo.okToFail()) {
            std::swap(assertions.failedButOk, assertions.failed);
            m_totals.assertions.failed -= assertions.failedButOk;
            m_totals.assertions.failedButOk += assertions.failedButOk;
        }

        SectionStats testCaseSectionStats(testCaseSection, assertions, duration, missingAssertions);
        m_reporter->sectionEnded(testCaseSectionStats);
    }

    void RunContext::invokeActiveTestCase() {
        FatalConditionHandler fatalConditionHandler; // Handle signals
        m_activeTestCase->invoke();
        fatalConditionHandler.reset();
    }

    ResultBuilder RunContext::makeUnexpectedResultBuilder() const {
        return ResultBuilder(m_lastAssertionInfo.macroName,
                             m_lastAssertionInfo.lineInfo,
                             m_lastAssertionInfo.capturedExpression,
                             m_lastAssertionInfo.resultDisposition);
    }

    void RunContext::handleUnfinishedSections() {
        // If sections ended prematurely due to an exception we stored their
        // infos here so we can tear them down outside the unwind process.
        for (auto it = m_unfinishedSections.rbegin(),
             itEnd = m_unfinishedSections.rend();
             it != itEnd;
             ++it)
            sectionEnded(*it);
        m_unfinishedSections.clear();
    }

    IResultCapture& getResultCapture() {
        if (IResultCapture* capture = getCurrentContext().getResultCapture())
            return *capture;
        else
            CATCH_INTERNAL_ERROR("No result capture instance");
    }

}
// end catch_run_context.cpp
// start catch_section.cpp

namespace Catch {

    Section::Section( SectionInfo const& info )
    :   m_info( info ),
        m_sectionIncluded( getResultCapture().sectionStarted( m_info, m_assertions ) )
    {
        m_timer.start();
    }

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4996) // std::uncaught_exception is deprecated in C++17
#endif
    Section::~Section() {
        if( m_sectionIncluded ) {
            SectionEndInfo endInfo( m_info, m_assertions, m_timer.getElapsedSeconds() );
            if( std::uncaught_exception() )
                getResultCapture().sectionEndedEarly( endInfo );
            else
                getResultCapture().sectionEnded( endInfo );
        }
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

    // This indicates whether the section should be executed or not
    Section::operator bool() const {
        return m_sectionIncluded;
    }

} // end namespace Catch
// end catch_section.cpp
// start catch_section_info.cpp

namespace Catch {

    SectionInfo::SectionInfo
        (   SourceLineInfo const& _lineInfo,
            std::string const& _name,
            std::string const& _description )
    :   name( _name ),
        description( _description ),
        lineInfo( _lineInfo )
    {}

    SectionEndInfo::SectionEndInfo( SectionInfo const& _sectionInfo, Counts const& _prevAssertions, double _durationInSeconds )
    : sectionInfo( _sectionInfo ), prevAssertions( _prevAssertions ), durationInSeconds( _durationInSeconds )
    {}

} // end namespace Catch
// end catch_section_info.cpp
// start catch_startup_exception_registry.cpp

namespace Catch {
    void StartupExceptionRegistry::add( std::exception_ptr const& exception ) noexcept {
        try {
            m_exceptions.push_back(exception);
        }
        catch(...) {
            // If we run out of memory during start-up there's really not a lot more we can do about it
            std::terminate();
        }
    }

    std::vector<std::exception_ptr> const& StartupExceptionRegistry::getExceptions() const noexcept {
        return m_exceptions;
    }

} // end namespace Catch
// end catch_startup_exception_registry.cpp
// start catch_string.cpp

// start catch_string.h

namespace Catch {

    class StringData;
    class StringRef;
    class StringBuilder;

    /// An owning, ref-counted, immutable string type.
    /// The ref count (not visible here as it is defined in StringData) is atomic
    /// so instances should be safe to share across threads
    class String {
        friend class StringRef;
        friend class StringBuilder;

        StringData const* m_data = nullptr;
    public:
        using size_type = unsigned long;

        String();
        String( StringRef const& stringRef );
        String( char const* rawString );
        String( String const& other );
        String( String&& other ) noexcept;
        String( StringBuilder&& stringBuf );

        ~String() noexcept;

        auto operator = ( String const& other ) -> String&;

        auto operator == ( StringRef const& other ) const noexcept -> bool;
        auto operator == ( char const* other ) const noexcept -> bool;

        auto empty() const noexcept -> bool;
        auto size() const noexcept -> size_type;
        auto c_str() const noexcept -> char const*;
    };

} // namespace Catch

// end catch_string.h
// start catch_stringbuilder.h

namespace Catch {

    class String;
    class StringData;

    /// A mutable container for string data
    /// Use to build up strings before transferring to an immutable String.
    /// Construct the String using the rvalue reference constructor (which
    /// will usually involve std::move-ing the StringBuilder). This will transfer
    /// The underlying buffer without any extra allocations or ref counts.
    class StringBuilder {
        friend class String;
    public:
        using size_type = unsigned long;

        StringBuilder();
        StringBuilder( size_type initialCapacity );
        StringBuilder( StringRef const& str, size_type initialCapacity );
        StringBuilder( StringBuilder const& other, size_type initialCapacity );
        StringBuilder( StringBuilder&& other ) noexcept;
        StringBuilder( String&& other );
        StringBuilder( String const& other );
        ~StringBuilder() noexcept;

        void swap( StringBuilder& other ) noexcept;

        auto size() const noexcept -> size_type;
        auto capacity() const noexcept -> size_type;

        /// Grows the buffer to exactly the capacity requested, or
        /// does nothing if it is already at least as big
        void reserve(size_type capacity);

        /// Grows the buffer exponentially (from a baseline of 32 bytes)
        /// until it is at least as large as the requested capacity -
        /// or does nothing if already large enough
        void reserveExponential(size_type capacity);

        /// Writes the string at the current insertion point then moves
        /// the insertion point forward by the string length.
        /// If the buffer needs to grow to accomodate the string it does so
        /// using the exponential strategy
        void append( StringRef const& str );

        friend auto operator << ( StringBuilder& sb, StringRef sr ) -> StringBuilder&;
        friend auto operator << ( StringBuilder&& sb, StringRef sr ) -> StringBuilder&&;

        /// Writes the contents of the string ref into the buffer at
        /// the indexed location.
        /// The bounds are not checked! Use append() to just add to the
        /// end of the buffer, extending it if the capacity is not enough.
        void writeTo( size_type index, StringRef const& str );

    private:
        size_type m_size = 0;
        StringData* m_data;
    };

} // namespace Catch

// end catch_stringbuilder.h
// start catch_stringdata.h

#include <atomic>

namespace Catch {

    class StringRef;

    class StringData {
        mutable std::atomic<unsigned int> m_refs;
    public:
        unsigned int size;
        union {
            char chars[1];
        };

        auto isUniquelyOwned() const noexcept -> bool {
            return m_refs == 1;
        }
        static auto getEmpty() -> StringData*;
        static auto create( StringRef const& stringRef ) -> StringData*;
        static auto create( StringRef const& stringRef, unsigned long capacity ) -> StringData*;

        void addRef() const noexcept {
            if( m_refs > 0 )
                ++m_refs;
        }
        void release() const noexcept {
            unsigned int refs = m_refs;
            if( refs > 1 )
                --m_refs;
            else if( refs == 1 )
                delete[] reinterpret_cast<char const*>( this );
        }
    private:
        StringData( unsigned int initialRef = 1 );
        StringData( StringRef const& stringRef, unsigned long capacity );

        StringData( StringData const& ) = delete;
        StringData& operator=( StringData const& ) = delete;
    };

} // namespace Catch

// end catch_stringdata.h
#include <ostream>

namespace Catch {

    String::String()
    : m_data( StringData::getEmpty() )
    {}

    String::String( StringRef const& stringRef )
    : m_data( StringData::create( stringRef ) )
    {}

    String::String( char const* rawString )
    : String( StringRef( rawString ) )
    {}

    String::String( String const& other )
    : m_data( other.m_data )
    {
        m_data->addRef();
    }
    String::String( String&& other ) noexcept
    : m_data( other.m_data )
    {
        other.m_data = StringData::getEmpty();
    }
    String::String( StringBuilder&& stringBuf )
    : m_data( stringBuf.m_data )
    {
        // const_cast is ok here because we are taking ownership
        const_cast<StringData*>( m_data )->size = stringBuf.size();
        stringBuf.m_data = StringData::getEmpty();
        stringBuf.m_size = 0;
    }

    String::~String() noexcept {
        m_data->release();
    }

    auto String::operator = ( String const& other ) -> String& {
        m_data = other.m_data;
        m_data->addRef();
        return *this;
    }

    auto String::empty() const noexcept -> bool {
        return m_data->size == 0;
    }
    auto String::size() const noexcept -> size_type {
        return m_data->size;
    }
    auto String::c_str() const noexcept -> char const* {
        return m_data->chars;
    }

    auto String::operator == ( StringRef const& other ) const noexcept -> bool {
        return other == StringRef( *this );
    }
    auto String::operator == ( char const* other ) const noexcept -> bool {
        return StringRef( other ) == StringRef( *this );
    }

    std::ostream& operator << ( std::ostream& os, String const& str ) {
        os << str.c_str();
        return os;
    }

} // namespace Catch
// end catch_string.cpp
// start catch_string_manip.cpp

#include <algorithm>
#include <ostream>
#include <cstring>
#include <cctype>

namespace Catch {

    bool startsWith( std::string const& s, std::string const& prefix ) {
        return s.size() >= prefix.size() && std::equal(prefix.begin(), prefix.end(), s.begin());
    }
    bool startsWith( std::string const& s, char prefix ) {
        return !s.empty() && s[0] == prefix;
    }
    bool endsWith( std::string const& s, std::string const& suffix ) {
        return s.size() >= suffix.size() && std::equal(suffix.rbegin(), suffix.rend(), s.rbegin());
    }
    bool endsWith( std::string const& s, char suffix ) {
        return !s.empty() && s[s.size()-1] == suffix;
    }
    bool contains( std::string const& s, std::string const& infix ) {
        return s.find( infix ) != std::string::npos;
    }
    char toLowerCh(char c) {
        return static_cast<char>( std::tolower( c ) );
    }
    void toLowerInPlace( std::string& s ) {
        std::transform( s.begin(), s.end(), s.begin(), toLowerCh );
    }
    std::string toLower( std::string const& s ) {
        std::string lc = s;
        toLowerInPlace( lc );
        return lc;
    }
    std::string trim( std::string const& str ) {
        static char const* whitespaceChars = "\n\r\t ";
        std::string::size_type start = str.find_first_not_of( whitespaceChars );
        std::string::size_type end = str.find_last_not_of( whitespaceChars );

        return start != std::string::npos ? str.substr( start, 1+end-start ) : std::string();
    }

    bool replaceInPlace( std::string& str, std::string const& replaceThis, std::string const& withThis ) {
        bool replaced = false;
        std::size_t i = str.find( replaceThis );
        while( i != std::string::npos ) {
            replaced = true;
            str = str.substr( 0, i ) + withThis + str.substr( i+replaceThis.size() );
            if( i < str.size()-withThis.size() )
                i = str.find( replaceThis, i+withThis.size() );
            else
                i = std::string::npos;
        }
        return replaced;
    }

    pluralise::pluralise( std::size_t count, std::string const& label )
    :   m_count( count ),
        m_label( label )
    {}

    std::ostream& operator << ( std::ostream& os, pluralise const& pluraliser ) {
        os << pluraliser.m_count << ' ' << pluraliser.m_label;
        if( pluraliser.m_count != 1 )
            os << 's';
        return os;
    }

}
// end catch_string_manip.cpp
// start catch_stringbuilder.cpp

#include <cstring>
#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace Catch {

    static const StringBuilder::size_type s_minimumCapacity = 32;

    StringBuilder::StringBuilder()
    :   m_data( StringData::getEmpty() )
    {}

    StringBuilder::StringBuilder( size_type initialCapacity )
    :   m_size( 0 ),
        m_data( StringData::create( StringRef(), initialCapacity ) )
    {}
    StringBuilder::StringBuilder( StringRef const& str, size_type initialCapacity )
    :   m_size( str.size() ),
        m_data( StringData::create( str, initialCapacity ) )
    {}
    StringBuilder::StringBuilder( StringBuilder const& other, size_type initialCapacity )
    :   StringBuilder( StringRef( other.m_data->chars, other.m_size ), initialCapacity )
    {}
    StringBuilder::StringBuilder( StringBuilder&& other ) noexcept
    :   StringBuilder()
    {
        swap( other );
    }
    StringBuilder::StringBuilder( String&& str )
    :   m_size( str.size() ),
        m_data( StringData::getEmpty() )
    {
        if( str.m_data->isUniquelyOwned() )
        {
            std::swap( m_data, const_cast<StringData*&>( str.m_data ) );
        }
        else
        {
            size_type initialCapacity = std::min( s_minimumCapacity, m_size );
            m_data = StringData::create( str, initialCapacity );
        }
    }
    StringBuilder::StringBuilder( String const& other )
    : StringBuilder( StringRef( other ), std::min( s_minimumCapacity, other.size() ) )
    {}

    StringBuilder::~StringBuilder() noexcept {
        m_data->release();
    }

    auto StringBuilder::size() const noexcept -> size_type {
        return m_size;
    }

    void StringBuilder::swap( StringBuilder& other ) noexcept {
        std::swap( m_size, other.m_size );
        std::swap( m_data, other.m_data );
    }
    void StringBuilder::reserve( size_type minimumCapacity ) {
        if( minimumCapacity > capacity() ) {
            StringBuilder temp( *this, minimumCapacity );
            swap( temp );
        }
    }
    void StringBuilder::reserveExponential( size_type minimumCapacity ) {
        if( minimumCapacity > capacity() ) {
            size_type candidateCapacity = capacity() < s_minimumCapacity ? s_minimumCapacity : capacity()*2;
            while( candidateCapacity < minimumCapacity )
                candidateCapacity = candidateCapacity * 3/2; // grow factor of 1.5
            StringBuilder temp( *this, candidateCapacity );
            swap( temp );
        }
    }
    auto StringBuilder::capacity() const noexcept -> size_type {
        return m_data->size;
    }
    void StringBuilder::writeTo( size_type index, StringRef const& str ) {
        assert( index + str.size() < capacity() );
        if( str.size() > 0 )
            std::memcpy( m_data->chars+index, str.data(), str.size() );
    }
    void StringBuilder::append( StringRef const& str ) {
        reserveExponential( m_size + str.size() + 1 );
        writeTo( m_size, str );
        m_size += str.size();
        m_data->chars[m_size] = '\0';
    }

    auto operator << ( StringBuilder& sb, StringRef sr ) -> StringBuilder& {
        sb.append( sr );
        return sb;
    }
    auto operator << ( StringBuilder&& sb, StringRef sr ) -> StringBuilder&& {
        sb.append( sr );
        return std::move( sb );
    }

} // namespace Catch
// end catch_stringbuilder.cpp
// start catch_stringdata.cpp

#include <new>
#include <cstring>
#include <cassert>

namespace Catch {

    auto StringData::getEmpty() -> StringData* {
        static StringData s_empty( 0 );
        return &s_empty;
    }
    auto StringData::create( StringRef const& stringRef ) -> StringData* {
        return create( stringRef, stringRef.size() );
    }
    auto StringData::create( StringRef const& stringRef, unsigned long capacity ) -> StringData* {
        if( capacity == 0 ) {
            return getEmpty();
        }
        else {
            assert( stringRef.size() <= capacity );
            auto bufferLen = sizeof(StringData)+capacity;
            void* buffer = new char[bufferLen];

            return new(buffer) StringData( stringRef, capacity );
        }
    }
    StringData::StringData( unsigned int initialRef )
    :   m_refs( initialRef ),
        size( 0 )
    {}
    StringData::StringData( StringRef const& stringRef, unsigned long capacity )
    :   m_refs( 1 ),
        size( capacity)
    {
        std::memcpy( chars, stringRef.data(), stringRef.size() );
        chars[stringRef.size() ] = 0;
    }

} // namespace Catch
// end catch_stringdata.cpp
// start catch_stringref.cpp

#include <cstring>
#include <ostream>
#include <cassert>

namespace Catch {

    auto getEmptyStringRef() -> StringRef {
        static StringRef s_emptyStringRef("");
        return s_emptyStringRef;
    }

    StringRef::StringRef() noexcept
    :   StringRef( getEmptyStringRef() )
    {}

    StringRef::StringRef( StringRef const& other ) noexcept
    :   m_start( other.m_start ),
        m_size( other.m_size ),
        m_data( other.m_data )
    {
        if( m_data )
            m_data->addRef();
    }

    StringRef::StringRef( StringRef&& other ) noexcept
    :   m_start( other.m_start ),
        m_size( other.m_size ),
        m_data( other.m_data )
    {
        other.m_data = nullptr;
    }

    StringRef::StringRef( char const* rawChars ) noexcept
    :   m_start( rawChars ),
        m_size( static_cast<size_type>( std::strlen( rawChars ) ) )
    {
        assert( rawChars != nullptr );
    }

    StringRef::StringRef( char const* rawChars, size_type size ) noexcept
    :   m_start( rawChars ),
        m_size( size )
    {
        size_type rawSize = rawChars == nullptr ? 0 : static_cast<size_type>( std::strlen( rawChars ) );
        if( rawSize < size )
            m_size = rawSize;
    }

    StringRef::StringRef( String const& other ) noexcept
    :   m_start( other.c_str() ),
        m_size( other.size() ),
        m_data( nullptr )
    {}

    StringRef::StringRef( String&& str ) noexcept
    :   m_start( str.c_str() ),
        m_size( str.size() ),
        m_data( str.m_data )
    {
        str.m_data = StringData::getEmpty();
    }

    StringRef::~StringRef() noexcept {
        if( isOwned() )
            m_data->release();
    }

    auto StringRef::operator = ( StringRef other ) noexcept -> StringRef& {
        swap( other );
        return *this;
    }

    void StringRef::swap( StringRef& other ) noexcept {
        std::swap( m_start, other.m_start );
        std::swap( m_size, other.m_size );
        std::swap( m_data, other.m_data );
    }

    auto StringRef::c_str() const -> char const* {
        if( isSubstring() )
           const_cast<StringRef*>( this )->takeOwnership();
        return m_start;
    }
    auto StringRef::data() const noexcept -> char const* {
        return m_start;
    }

    auto StringRef::isOwned() const noexcept -> bool {
        return m_data != nullptr;
    }
    auto StringRef::isSubstring() const noexcept -> bool {
        return m_start[m_size] != '\0';
    }

    void StringRef::takeOwnership() {
        if( !isOwned() ) {
            StringRef temp = String( *this );
            swap( temp );
        }
    }
    auto StringRef::substr( size_type start, size_type size ) const noexcept -> StringRef {
        if( start < m_size )
            return StringRef( m_start+start, size );
        else
            return StringRef();
    }
    auto StringRef::operator == ( StringRef const& other ) const noexcept -> bool {
        return
            size() == other.size() &&
            (std::strncmp( m_start, other.m_start, size() ) == 0);
    }
    auto StringRef::operator != ( StringRef const& other ) const noexcept -> bool {
        return !operator==( other );
    }

    auto StringRef::operator[](size_type index) const noexcept -> char {
        return m_start[index];
    }

    auto StringRef::empty() const noexcept -> bool {
        return m_size == 0;
    }

    auto StringRef::size() const noexcept -> size_type {
        return m_size;
    }

    auto operator + ( StringRef const& lhs, StringRef const& rhs ) -> String {
        StringBuilder buf;
        buf.reserve( lhs.size() + rhs.size() );
        buf.append( lhs );
        buf.append( rhs );
        return String( std::move( buf ) );
    }
    auto operator + ( StringRef const& lhs, const char* rhs ) -> String {
        return lhs + StringRef( rhs );
    }
    auto operator + ( char const* lhs, StringRef const& rhs ) -> String {
        return StringRef( lhs ) + rhs;
    }

    std::ostream& operator << ( std::ostream& os, StringRef const& str ) {
        return os << str.c_str();
    }

} // namespace Catch
// end catch_stringref.cpp
// start catch_tag_alias.cpp

namespace Catch {
    TagAlias::TagAlias(std::string const & _tag, SourceLineInfo _lineInfo): tag(_tag), lineInfo(_lineInfo) {}
}
// end catch_tag_alias.cpp
// start catch_tag_alias_autoregistrar.cpp

namespace Catch {

    RegistrarForTagAliases::RegistrarForTagAliases(char const* alias, char const* tag, SourceLineInfo const& lineInfo) {
        try {
            getMutableRegistryHub().registerTagAlias(alias, tag, lineInfo);
        } catch (...) {
            // Do not throw when constructing global objects, instead register the exception to be processed later
            getMutableRegistryHub().registerStartupException();
        }
    }

}
// end catch_tag_alias_autoregistrar.cpp
// start catch_tag_alias_registry.cpp

namespace Catch {

    TagAliasRegistry::~TagAliasRegistry() {}

    TagAlias const* TagAliasRegistry::find( std::string const& alias ) const {
        auto it = m_registry.find( alias );
        if( it != m_registry.end() )
            return &(it->second);
        else
            return nullptr;
    }

    std::string TagAliasRegistry::expandAliases( std::string const& unexpandedTestSpec ) const {
        std::string expandedTestSpec = unexpandedTestSpec;
        for( auto const& registryKvp : m_registry ) {
            std::size_t pos = expandedTestSpec.find( registryKvp.first );
            if( pos != std::string::npos ) {
                expandedTestSpec =  expandedTestSpec.substr( 0, pos ) +
                                    registryKvp.second.tag +
                                    expandedTestSpec.substr( pos + registryKvp.first.size() );
            }
        }
        return expandedTestSpec;
    }

    void TagAliasRegistry::add( std::string const& alias, std::string const& tag, SourceLineInfo const& lineInfo ) {
        CATCH_ENFORCE( startsWith(alias, "[@") && endsWith(alias, ']'),
                      "error: tag alias, '" << alias << "' is not of the form [@alias name].\n" << lineInfo );

        CATCH_ENFORCE( m_registry.insert(std::make_pair(alias, TagAlias(tag, lineInfo))).second,
                      "error: tag alias, '" << alias << "' already registered.\n"
                      << "\tFirst seen at: " << find(alias)->lineInfo << "\n"
                      << "\tRedefined at: " << lineInfo );
    }

    ITagAliasRegistry::~ITagAliasRegistry() {}

    ITagAliasRegistry const& ITagAliasRegistry::get() {
        return getRegistryHub().getTagAliasRegistry();
    }

} // end namespace Catch
// end catch_tag_alias_registry.cpp
// start catch_test_case_info.cpp

#include <cctype>
#include <exception>
#include <algorithm>

namespace Catch {

    TestCaseInfo::SpecialProperties parseSpecialTag( std::string const& tag ) {
        if( startsWith( tag, '.' ) ||
            tag == "hide" ||
            tag == "!hide" )
            return TestCaseInfo::IsHidden;
        else if( tag == "!throws" )
            return TestCaseInfo::Throws;
        else if( tag == "!shouldfail" )
            return TestCaseInfo::ShouldFail;
        else if( tag == "!mayfail" )
            return TestCaseInfo::MayFail;
        else if( tag == "!nonportable" )
            return TestCaseInfo::NonPortable;
        else if( tag == "!benchmark" )
            return static_cast<TestCaseInfo::SpecialProperties>( TestCaseInfo::Benchmark | TestCaseInfo::IsHidden );
        else
            return TestCaseInfo::None;
    }
    bool isReservedTag( std::string const& tag ) {
        return parseSpecialTag( tag ) == TestCaseInfo::None && tag.size() > 0 && !std::isalnum( tag[0] );
    }
    void enforceNotReservedTag( std::string const& tag, SourceLineInfo const& _lineInfo ) {
        CATCH_ENFORCE( !isReservedTag(tag),
                      "Tag name: [" << tag << "] is not allowed.\n"
                      << "Tag names starting with non alpha-numeric characters are reserved\n"
                      << _lineInfo );
    }

    TestCase makeTestCase(  ITestInvoker* _testCase,
                            std::string const& _className,
                            std::string const& _name,
                            std::string const& _descOrTags,
                            SourceLineInfo const& _lineInfo )
    {
        bool isHidden( startsWith( _name, "./" ) ); // Legacy support

        // Parse out tags
        std::vector<std::string> tags;
        std::string desc, tag;
        bool inTag = false;
        for( std::size_t i = 0; i < _descOrTags.size(); ++i ) {
            char c = _descOrTags[i];
            if( !inTag ) {
                if( c == '[' )
                    inTag = true;
                else
                    desc += c;
            }
            else {
                if( c == ']' ) {
                    TestCaseInfo::SpecialProperties prop = parseSpecialTag( tag );
                    if( prop == TestCaseInfo::IsHidden )
                        isHidden = true;
                    else if( prop == TestCaseInfo::None )
                        enforceNotReservedTag( tag, _lineInfo );

                    tags.push_back( tag );
                    tag.clear();
                    inTag = false;
                }
                else
                    tag += c;
            }
        }
        if( isHidden ) {
            tags.push_back( "hide" );
            tags.push_back( "." );
        }

        TestCaseInfo info( _name, _className, desc, tags, _lineInfo );
        return TestCase( _testCase, info );
    }

    void setTags( TestCaseInfo& testCaseInfo, std::vector<std::string> tags ) {
        std::sort(begin(tags), end(tags));
        tags.erase(std::unique(begin(tags), end(tags)), end(tags));
        testCaseInfo.lcaseTags.clear();

        for( auto const& tag : tags ) {
            std::string lcaseTag = toLower( tag );
            testCaseInfo.properties = static_cast<TestCaseInfo::SpecialProperties>( testCaseInfo.properties | parseSpecialTag( lcaseTag ) );
            testCaseInfo.lcaseTags.push_back( lcaseTag );
        }
        testCaseInfo.tags = std::move(tags);
    }

    TestCaseInfo::TestCaseInfo( std::string const& _name,
                                std::string const& _className,
                                std::string const& _description,
                                std::vector<std::string> const& _tags,
                                SourceLineInfo const& _lineInfo )
    :   name( _name ),
        className( _className ),
        description( _description ),
        lineInfo( _lineInfo ),
        properties( None )
    {
        setTags( *this, _tags );
    }

    bool TestCaseInfo::isHidden() const {
        return ( properties & IsHidden ) != 0;
    }
    bool TestCaseInfo::throws() const {
        return ( properties & Throws ) != 0;
    }
    bool TestCaseInfo::okToFail() const {
        return ( properties & (ShouldFail | MayFail ) ) != 0;
    }
    bool TestCaseInfo::expectedToFail() const {
        return ( properties & (ShouldFail ) ) != 0;
    }

    std::string TestCaseInfo::tagsAsString() const {
        std::string ret;
        // '[' and ']' per tag
        size_t full_size = 2 * tags.size();
        for (const auto& tag : tags) {
            full_size += tag.size();
        }
        ret.reserve(full_size);
        for (const auto& tag : tags) {
            ret.push_back('[');
            ret.append(tag);
            ret.push_back(']');
        }

        return ret;
    }

    TestCase::TestCase( ITestInvoker* testCase, TestCaseInfo const& info ) : TestCaseInfo( info ), test( testCase ) {}

    TestCase TestCase::withName( std::string const& _newName ) const {
        TestCase other( *this );
        other.name = _newName;
        return other;
    }

    void TestCase::invoke() const {
        test->invoke();
    }

    bool TestCase::operator == ( TestCase const& other ) const {
        return  test.get() == other.test.get() &&
                name == other.name &&
                className == other.className;
    }

    bool TestCase::operator < ( TestCase const& other ) const {
        return name < other.name;
    }

    TestCaseInfo const& TestCase::getTestCaseInfo() const
    {
        return *this;
    }

} // end namespace Catch
// end catch_test_case_info.cpp
// start catch_test_case_registry_impl.cpp

#include <sstream>

namespace Catch {

    RandomNumberGenerator::result_type RandomNumberGenerator::operator()( result_type n ) const { return std::rand() % n; }
    RandomNumberGenerator::result_type RandomNumberGenerator::operator()() const { return std::rand() % max(); }

    std::vector<TestCase> sortTests( IConfig const& config, std::vector<TestCase> const& unsortedTestCases ) {

        std::vector<TestCase> sorted = unsortedTestCases;

        switch( config.runOrder() ) {
            case RunTests::InLexicographicalOrder:
                std::sort( sorted.begin(), sorted.end() );
                break;
            case RunTests::InRandomOrder:
                seedRng( config );
                RandomNumberGenerator::shuffle( sorted );
                break;
            case RunTests::InDeclarationOrder:
                // already in declaration order
                break;
        }
        return sorted;
    }
    bool matchTest( TestCase const& testCase, TestSpec const& testSpec, IConfig const& config ) {
        return testSpec.matches( testCase ) && ( config.allowThrows() || !testCase.throws() );
    }

    void enforceNoDuplicateTestCases( std::vector<TestCase> const& functions ) {
        std::set<TestCase> seenFunctions;
        for( auto const& function : functions ) {
            auto prev = seenFunctions.insert( function );
            CATCH_ENFORCE( prev.second,
                    "error: TEST_CASE( \"" << function.name << "\" ) already defined.\n"
                    << "\tFirst seen at " << prev.first->getTestCaseInfo().lineInfo << "\n"
                    << "\tRedefined at " << function.getTestCaseInfo().lineInfo );
        }
    }

    std::vector<TestCase> filterTests( std::vector<TestCase> const& testCases, TestSpec const& testSpec, IConfig const& config ) {
        std::vector<TestCase> filtered;
        filtered.reserve( testCases.size() );
        for( auto const& testCase : testCases )
            if( matchTest( testCase, testSpec, config ) )
                filtered.push_back( testCase );
        return filtered;
    }
    std::vector<TestCase> const& getAllTestCasesSorted( IConfig const& config ) {
        return getRegistryHub().getTestCaseRegistry().getAllTestsSorted( config );
    }

    void TestRegistry::registerTest( TestCase const& testCase ) {
        std::string name = testCase.getTestCaseInfo().name;
        if( name.empty() ) {
            std::ostringstream oss;
            oss << "Anonymous test case " << ++m_unnamedCount;
            return registerTest( testCase.withName( oss.str() ) );
        }
        m_functions.push_back( testCase );
    }

    std::vector<TestCase> const& TestRegistry::getAllTests() const {
        return m_functions;
    }
    std::vector<TestCase> const& TestRegistry::getAllTestsSorted( IConfig const& config ) const {
        if( m_sortedFunctions.empty() )
            enforceNoDuplicateTestCases( m_functions );

        if(  m_currentSortOrder != config.runOrder() || m_sortedFunctions.empty() ) {
            m_sortedFunctions = sortTests( config, m_functions );
            m_currentSortOrder = config.runOrder();
        }
        return m_sortedFunctions;
    }

    ///////////////////////////////////////////////////////////////////////////
    TestInvokerAsFunction::TestInvokerAsFunction( void(*testAsFunction)() ) noexcept : m_testAsFunction( testAsFunction ) {}

    void TestInvokerAsFunction::invoke() const {
        m_testAsFunction();
    }

    std::string extractClassName( std::string const& classOrQualifiedMethodName ) {
        std::string className = classOrQualifiedMethodName;
        if( startsWith( className, '&' ) )
        {
            std::size_t lastColons = className.rfind( "::" );
            std::size_t penultimateColons = className.rfind( "::", lastColons-1 );
            if( penultimateColons == std::string::npos )
                penultimateColons = 1;
            className = className.substr( penultimateColons, lastColons-penultimateColons );
        }
        return className;
    }

} // end namespace Catch
// end catch_test_case_registry_impl.cpp
// start catch_test_case_tracker.cpp

#include <algorithm>
#include <assert.h>
#include <stdexcept>
#include <memory>

CATCH_INTERNAL_SUPPRESS_ETD_WARNINGS

namespace Catch {
namespace TestCaseTracking {

    NameAndLocation::NameAndLocation( std::string const& _name, SourceLineInfo const& _location )
    :   name( _name ),
        location( _location )
    {}

    TrackerContext& TrackerContext::instance() {
        static TrackerContext s_instance;
        return s_instance;
    }

    ITracker& TrackerContext::startRun() {
        m_rootTracker = std::make_shared<SectionTracker>( NameAndLocation( "{root}", CATCH_INTERNAL_LINEINFO ), *this, nullptr );
        m_currentTracker = nullptr;
        m_runState = Executing;
        return *m_rootTracker;
    }

    void TrackerContext::endRun() {
        m_rootTracker.reset();
        m_currentTracker = nullptr;
        m_runState = NotStarted;
    }

    void TrackerContext::startCycle() {
        m_currentTracker = m_rootTracker.get();
        m_runState = Executing;
    }
    void TrackerContext::completeCycle() {
        m_runState = CompletedCycle;
    }

    bool TrackerContext::completedCycle() const {
        return m_runState == CompletedCycle;
    }
    ITracker& TrackerContext::currentTracker() {
        return *m_currentTracker;
    }
    void TrackerContext::setCurrentTracker( ITracker* tracker ) {
        m_currentTracker = tracker;
    }

    TrackerBase::TrackerHasName::TrackerHasName( NameAndLocation const& nameAndLocation ) : m_nameAndLocation( nameAndLocation ) {}
    bool TrackerBase::TrackerHasName::operator ()( ITrackerPtr const& tracker ) const {
        return
            tracker->nameAndLocation().name == m_nameAndLocation.name &&
            tracker->nameAndLocation().location == m_nameAndLocation.location;
    }

    TrackerBase::TrackerBase( NameAndLocation const& nameAndLocation, TrackerContext& ctx, ITracker* parent )
    :   m_nameAndLocation( nameAndLocation ),
        m_ctx( ctx ),
        m_parent( parent )
    {}

    NameAndLocation const& TrackerBase::nameAndLocation() const {
        return m_nameAndLocation;
    }
    bool TrackerBase::isComplete() const {
        return m_runState == CompletedSuccessfully || m_runState == Failed;
    }
    bool TrackerBase::isSuccessfullyCompleted() const {
        return m_runState == CompletedSuccessfully;
    }
    bool TrackerBase::isOpen() const {
        return m_runState != NotStarted && !isComplete();
    }
    bool TrackerBase::hasChildren() const {
        return !m_children.empty();
    }

    void TrackerBase::addChild( ITrackerPtr const& child ) {
        m_children.push_back( child );
    }

    ITrackerPtr TrackerBase::findChild( NameAndLocation const& nameAndLocation ) {
        auto it = std::find_if( m_children.begin(), m_children.end(), TrackerHasName( nameAndLocation ) );
        return( it != m_children.end() )
            ? *it
            : nullptr;
    }
    ITracker& TrackerBase::parent() {
        assert( m_parent ); // Should always be non-null except for root
        return *m_parent;
    }

    void TrackerBase::openChild() {
        if( m_runState != ExecutingChildren ) {
            m_runState = ExecutingChildren;
            if( m_parent )
                m_parent->openChild();
        }
    }

    bool TrackerBase::isSectionTracker() const { return false; }
    bool TrackerBase::isIndexTracker() const { return false; }

    void TrackerBase::open() {
        m_runState = Executing;
        moveToThis();
        if( m_parent )
            m_parent->openChild();
    }

    void TrackerBase::close() {

        // Close any still open children (e.g. generators)
        while( &m_ctx.currentTracker() != this )
            m_ctx.currentTracker().close();

        switch( m_runState ) {
            case NeedsAnotherRun:
                break;

            case Executing:
                m_runState = CompletedSuccessfully;
                break;
            case ExecutingChildren:
                if( m_children.empty() || m_children.back()->isComplete() )
                    m_runState = CompletedSuccessfully;
                break;

            case NotStarted:
            case CompletedSuccessfully:
            case Failed:
                CATCH_INTERNAL_ERROR( "Illogical state: " << m_runState );

            default:
                CATCH_INTERNAL_ERROR( "Unknown state: " << m_runState );
        }
        moveToParent();
        m_ctx.completeCycle();
    }
    void TrackerBase::fail() {
        m_runState = Failed;
        if( m_parent )
            m_parent->markAsNeedingAnotherRun();
        moveToParent();
        m_ctx.completeCycle();
    }
    void TrackerBase::markAsNeedingAnotherRun() {
        m_runState = NeedsAnotherRun;
    }

    void TrackerBase::moveToParent() {
        assert( m_parent );
        m_ctx.setCurrentTracker( m_parent );
    }
    void TrackerBase::moveToThis() {
        m_ctx.setCurrentTracker( this );
    }

    SectionTracker::SectionTracker( NameAndLocation const& nameAndLocation, TrackerContext& ctx, ITracker* parent )
    :   TrackerBase( nameAndLocation, ctx, parent )
    {
        if( parent ) {
            while( !parent->isSectionTracker() )
                parent = &parent->parent();

            SectionTracker& parentSection = static_cast<SectionTracker&>( *parent );
            addNextFilters( parentSection.m_filters );
        }
    }

    bool SectionTracker::isSectionTracker() const { return true; }

    SectionTracker& SectionTracker::acquire( TrackerContext& ctx, NameAndLocation const& nameAndLocation ) {
        std::shared_ptr<SectionTracker> section;

        ITracker& currentTracker = ctx.currentTracker();
        if( ITrackerPtr childTracker = currentTracker.findChild( nameAndLocation ) ) {
            assert( childTracker );
            assert( childTracker->isSectionTracker() );
            section = std::static_pointer_cast<SectionTracker>( childTracker );
        }
        else {
            section = std::make_shared<SectionTracker>( nameAndLocation, ctx, &currentTracker );
            currentTracker.addChild( section );
        }
        if( !ctx.completedCycle() )
            section->tryOpen();
        return *section;
    }

    void SectionTracker::tryOpen() {
        if( !isComplete() && (m_filters.empty() || m_filters[0].empty() ||  m_filters[0] == m_nameAndLocation.name ) )
            open();
    }

    void SectionTracker::addInitialFilters( std::vector<std::string> const& filters ) {
        if( !filters.empty() ) {
            m_filters.push_back(""); // Root - should never be consulted
            m_filters.push_back(""); // Test Case - not a section filter
            m_filters.insert( m_filters.end(), filters.begin(), filters.end() );
        }
    }
    void SectionTracker::addNextFilters( std::vector<std::string> const& filters ) {
        if( filters.size() > 1 )
            m_filters.insert( m_filters.end(), ++filters.begin(), filters.end() );
    }

    IndexTracker::IndexTracker( NameAndLocation const& nameAndLocation, TrackerContext& ctx, ITracker* parent, int size )
    :   TrackerBase( nameAndLocation, ctx, parent ),
        m_size( size )
    {}

    bool IndexTracker::isIndexTracker() const { return true; }

    IndexTracker& IndexTracker::acquire( TrackerContext& ctx, NameAndLocation const& nameAndLocation, int size ) {
        std::shared_ptr<IndexTracker> tracker;

        ITracker& currentTracker = ctx.currentTracker();
        if( ITrackerPtr childTracker = currentTracker.findChild( nameAndLocation ) ) {
            assert( childTracker );
            assert( childTracker->isIndexTracker() );
            tracker = std::static_pointer_cast<IndexTracker>( childTracker );
        }
        else {
            tracker = std::make_shared<IndexTracker>( nameAndLocation, ctx, &currentTracker, size );
            currentTracker.addChild( tracker );
        }

        if( !ctx.completedCycle() && !tracker->isComplete() ) {
            if( tracker->m_runState != ExecutingChildren && tracker->m_runState != NeedsAnotherRun )
                tracker->moveNext();
            tracker->open();
        }

        return *tracker;
    }

    int IndexTracker::index() const { return m_index; }

    void IndexTracker::moveNext() {
        m_index++;
        m_children.clear();
    }

    void IndexTracker::close() {
        TrackerBase::close();
        if( m_runState == CompletedSuccessfully && m_index < m_size-1 )
            m_runState = Executing;
    }

} // namespace TestCaseTracking

using TestCaseTracking::ITracker;
using TestCaseTracking::TrackerContext;
using TestCaseTracking::SectionTracker;
using TestCaseTracking::IndexTracker;

} // namespace Catch

CATCH_INTERNAL_UNSUPPRESS_ETD_WARNINGS
// end catch_test_case_tracker.cpp
// start catch_test_registry.cpp

namespace Catch {

    auto makeTestInvoker( void(*testAsFunction)() ) noexcept -> ITestInvoker* {
        return new(std::nothrow) TestInvokerAsFunction( testAsFunction );
    }

    NameAndTags::NameAndTags( StringRef name_ , StringRef tags_ ) noexcept : name( name_ ), tags( tags_ ) {}

    AutoReg::AutoReg( ITestInvoker* invoker, SourceLineInfo const& lineInfo, StringRef classOrMethod, NameAndTags const& nameAndTags ) noexcept {
        try {
            getMutableRegistryHub()
                    .registerTest(
                        makeTestCase(
                            invoker,
                            extractClassName( classOrMethod.c_str() ),
                            nameAndTags.name.c_str(),
                            nameAndTags.tags.c_str(),
                            lineInfo));
        } catch (...) {
            // Do not throw when constructing global objects, instead register the exception to be processed later
            getMutableRegistryHub().registerStartupException();
        }
    }
}
// end catch_test_registry.cpp
// start catch_test_spec.cpp

#include <algorithm>
#include <string>
#include <vector>
#include <memory>

namespace Catch {

    TestSpec::NamePattern::NamePattern( std::string const& name )
    : m_wildcardPattern( toLower( name ), CaseSensitive::No )
    {}
    bool TestSpec::NamePattern::matches( TestCaseInfo const& testCase ) const {
        return m_wildcardPattern.matches( toLower( testCase.name ) );
    }

    TestSpec::TagPattern::TagPattern( std::string const& tag ) : m_tag( toLower( tag ) ) {}
    bool TestSpec::TagPattern::matches( TestCaseInfo const& testCase ) const {
        return std::find(begin(testCase.lcaseTags),
                         end(testCase.lcaseTags),
                         m_tag) != end(testCase.lcaseTags);
    }

    TestSpec::ExcludedPattern::ExcludedPattern( PatternPtr const& underlyingPattern ) : m_underlyingPattern( underlyingPattern ) {}
    bool TestSpec::ExcludedPattern::matches( TestCaseInfo const& testCase ) const { return !m_underlyingPattern->matches( testCase ); }

    bool TestSpec::Filter::matches( TestCaseInfo const& testCase ) const {
        // All patterns in a filter must match for the filter to be a match
        for( auto const& pattern : m_patterns ) {
            if( !pattern->matches( testCase ) )
                return false;
        }
        return true;
    }

    bool TestSpec::hasFilters() const {
        return !m_filters.empty();
    }
    bool TestSpec::matches( TestCaseInfo const& testCase ) const {
        // A TestSpec matches if any filter matches
        for( auto const& filter : m_filters )
            if( filter.matches( testCase ) )
                return true;
        return false;
    }
}
// end catch_test_spec.cpp
// start catch_test_spec_parser.cpp

namespace Catch {

    TestSpecParser::TestSpecParser( ITagAliasRegistry const& tagAliases ) : m_tagAliases( &tagAliases ) {}

    TestSpecParser& TestSpecParser::parse( std::string const& arg ) {
        m_mode = None;
        m_exclusion = false;
        m_start = std::string::npos;
        m_arg = m_tagAliases->expandAliases( arg );
        m_escapeChars.clear();
        for( m_pos = 0; m_pos < m_arg.size(); ++m_pos )
            visitChar( m_arg[m_pos] );
        if( m_mode == Name )
            addPattern<TestSpec::NamePattern>();
        return *this;
    }
    TestSpec TestSpecParser::testSpec() {
        addFilter();
        return m_testSpec;
    }

    void TestSpecParser::visitChar( char c ) {
        if( m_mode == None ) {
            switch( c ) {
            case ' ': return;
            case '~': m_exclusion = true; return;
            case '[': return startNewMode( Tag, ++m_pos );
            case '"': return startNewMode( QuotedName, ++m_pos );
            case '\\': return escape();
            default: startNewMode( Name, m_pos ); break;
            }
        }
        if( m_mode == Name ) {
            if( c == ',' ) {
                addPattern<TestSpec::NamePattern>();
                addFilter();
            }
            else if( c == '[' ) {
                if( subString() == "exclude:" )
                    m_exclusion = true;
                else
                    addPattern<TestSpec::NamePattern>();
                startNewMode( Tag, ++m_pos );
            }
            else if( c == '\\' )
                escape();
        }
        else if( m_mode == EscapedName )
            m_mode = Name;
        else if( m_mode == QuotedName && c == '"' )
            addPattern<TestSpec::NamePattern>();
        else if( m_mode == Tag && c == ']' )
            addPattern<TestSpec::TagPattern>();
    }
    void TestSpecParser::startNewMode( Mode mode, std::size_t start ) {
        m_mode = mode;
        m_start = start;
    }
    void TestSpecParser::escape() {
        if( m_mode == None )
            m_start = m_pos;
        m_mode = EscapedName;
        m_escapeChars.push_back( m_pos );
    }
    std::string TestSpecParser::subString() const { return m_arg.substr( m_start, m_pos - m_start ); }

    void TestSpecParser::addFilter() {
        if( !m_currentFilter.m_patterns.empty() ) {
            m_testSpec.m_filters.push_back( m_currentFilter );
            m_currentFilter = TestSpec::Filter();
        }
    }

    TestSpec parseTestSpec( std::string const& arg ) {
        return TestSpecParser( ITagAliasRegistry::get() ).parse( arg ).testSpec();
    }

} // namespace Catch
// end catch_test_spec_parser.cpp
// start catch_timer.cpp

#include <chrono>

namespace Catch {

    auto getCurrentNanosecondsSinceEpoch() -> uint64_t {
        return std::chrono::duration_cast<std::chrono::nanoseconds>( std::chrono::high_resolution_clock::now().time_since_epoch() ).count();
    }

    auto estimateClockResolution() -> uint64_t {
        uint64_t sum = 0;
        static const uint64_t iterations = 1000000;

        for( size_t i = 0; i < iterations; ++i ) {

            uint64_t ticks;
            uint64_t baseTicks = getCurrentNanosecondsSinceEpoch();
            do {
                ticks = getCurrentNanosecondsSinceEpoch();
            }
            while( ticks == baseTicks );

            auto delta = ticks - baseTicks;
            sum += delta;
        }

        // We're just taking the mean, here. To do better we could take the std. dev and exclude outliers
        // - and potentially do more iterations if there's a high variance.
        return sum/iterations;
    }
    auto getEstimatedClockResolution() -> uint64_t {
        static auto s_resolution = estimateClockResolution();
        return s_resolution;
    }

    void Timer::start() {
       m_nanoseconds = getCurrentNanosecondsSinceEpoch();
    }
    auto Timer::getElapsedNanoseconds() const -> unsigned int {
        return static_cast<unsigned int>(getCurrentNanosecondsSinceEpoch() - m_nanoseconds);
    }
    auto Timer::getElapsedMicroseconds() const -> unsigned int {
        return static_cast<unsigned int>(getElapsedNanoseconds()/1000);
    }
    auto Timer::getElapsedMilliseconds() const -> unsigned int {
        return static_cast<unsigned int>(getElapsedMicroseconds()/1000);
    }
    auto Timer::getElapsedSeconds() const -> double {
        return getElapsedMicroseconds()/1000000.0;
    }

} // namespace Catch
// end catch_timer.cpp
// start catch_tostring.cpp

#include <iomanip>

namespace Catch {

namespace Detail {

    const std::string unprintableString = "{?}";

    namespace {
        const int hexThreshold = 255;

        struct Endianness {
            enum Arch { Big, Little };

            static Arch which() {
                union _{
                    int asInt;
                    char asChar[sizeof (int)];
                } u;

                u.asInt = 1;
                return ( u.asChar[sizeof(int)-1] == 1 ) ? Big : Little;
            }
        };
    }

    std::string rawMemoryToString( const void *object, std::size_t size ) {
        // Reverse order for little endian architectures
        int i = 0, end = static_cast<int>( size ), inc = 1;
        if( Endianness::which() == Endianness::Little ) {
            i = end-1;
            end = inc = -1;
        }

        unsigned char const *bytes = static_cast<unsigned char const *>(object);
        std::ostringstream os;
        os << "0x" << std::setfill('0') << std::hex;
        for( ; i != end; i += inc )
             os << std::setw(2) << static_cast<unsigned>(bytes[i]);
       return os.str();
    }
}

template<typename T>
std::string fpToString( T value, int precision ) {
    std::ostringstream oss;
    oss << std::setprecision( precision )
        << std::fixed
        << value;
    std::string d = oss.str();
    std::size_t i = d.find_last_not_of( '0' );
    if( i != std::string::npos && i != d.size()-1 ) {
        if( d[i] == '.' )
            i++;
        d = d.substr( 0, i+1 );
    }
    return d;
}

//// ======================================================= ////
//
//   Out-of-line defs for full specialization of StringMaker
//
//// ======================================================= ////

std::string StringMaker<std::string>::convert(const std::string& str) {
    if (!getCurrentContext().getConfig()->showInvisibles()) {
        return '"' + str + '"';
    }

    std::string s("\"");
    for (char c : str) {
        switch (c) {
        case '\n':
            s.append("\\n");
            break;
        case '\t':
            s.append("\\t");
            break;
        default:
            s.push_back(c);
            break;
        }
    }
    s.append("\"");
    return s;
}

std::string StringMaker<std::wstring>::convert(const std::wstring& wstr) {
    std::string s;
    s.reserve(wstr.size());
    for (auto c : wstr) {
        s += (c <= 0xff) ? static_cast<char>(c) : '?';
    }
    return ::Catch::Detail::stringify(s);
}

std::string StringMaker<char const*>::convert(char const* str) {
    if (str) {
        return ::Catch::Detail::stringify(std::string{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker<char*>::convert(char* str) {
    if (str) {
        return ::Catch::Detail::stringify(std::string{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker<wchar_t const*>::convert(wchar_t const * str) {
    if (str) {
        return ::Catch::Detail::stringify(std::wstring{ str });
    } else {
        return{ "{null string}" };
    }
}
std::string StringMaker<wchar_t *>::convert(wchar_t * str) {
    if (str) {
        return ::Catch::Detail::stringify(std::wstring{ str });
    } else {
        return{ "{null string}" };
    }
}

std::string StringMaker<int>::convert(int value) {
    return ::Catch::Detail::stringify(static_cast<long long>(value));
}
std::string StringMaker<long>::convert(long value) {
    return ::Catch::Detail::stringify(static_cast<long long>(value));
}
std::string StringMaker<long long>::convert(long long value) {
    std::ostringstream oss;
    oss << value;
    if (value > Detail::hexThreshold) {
        oss << " (0x" << std::hex << value << ')';
    }
    return oss.str();
}

std::string StringMaker<unsigned int>::convert(unsigned int value) {
    return ::Catch::Detail::stringify(static_cast<unsigned long long>(value));
}
std::string StringMaker<unsigned long>::convert(unsigned long value) {
    return ::Catch::Detail::stringify(static_cast<unsigned long long>(value));
}
std::string StringMaker<unsigned long long>::convert(unsigned long long value) {
    std::ostringstream oss;
    oss << value;
    if (value > Detail::hexThreshold) {
        oss << " (0x" << std::hex << value << ')';
    }
    return oss.str();
}

std::string StringMaker<bool>::convert(bool b) {
    return b ? "true" : "false";
}

std::string StringMaker<char>::convert(char value) {
    if (value == '\r') {
        return "'\\r'";
    } else if (value == '\f') {
        return "'\\f'";
    } else if (value == '\n') {
        return "'\\n'";
    } else if (value == '\t') {
        return "'\\t'";
    } else if ('\0' <= value && value < ' ') {
        return ::Catch::Detail::stringify(static_cast<unsigned int>(value));
    } else {
        char chstr[] = "' '";
        chstr[1] = value;
        return chstr;
    }
}
std::string StringMaker<signed char>::convert(signed char c) {
    return ::Catch::Detail::stringify(static_cast<char>(c));
}
std::string StringMaker<unsigned char>::convert(unsigned char c) {
    return ::Catch::Detail::stringify(static_cast<char>(c));
}

std::string StringMaker<std::nullptr_t>::convert(std::nullptr_t) {
    return "nullptr";
}

std::string StringMaker<float>::convert(float value) {
    return fpToString(value, 5) + 'f';
}
std::string StringMaker<double>::convert(double value) {
    return fpToString(value, 10);
}

#ifdef __OBJC__
std::string StringMaker<NSString*>::convert(NSString* nsstring) {
    if (!nsstring)
        return "nil";
    return "@" + toString([nsstring UTF8String]);
}
std::string StringMaker<NSString * CATCH_ARC_STRONG>::convert(NSString* CATCH_ARC_STRONG nsstring) {
    if (!nsstring)
        return "nil";
    return "@" + toString([nsstring UTF8String]);
}
std::string StringMaker<NSObject*>::convert(NSObject* nsObject) {
    return ::Catch::Detail::stringify([nsObject description]);
}
#endif

} // end namespace Catch
// end catch_tostring.cpp
// start catch_totals.cpp

namespace Catch {

    Counts Counts::operator - ( Counts const& other ) const {
        Counts diff;
        diff.passed = passed - other.passed;
        diff.failed = failed - other.failed;
        diff.failedButOk = failedButOk - other.failedButOk;
        return diff;
    }

    Counts& Counts::operator += ( Counts const& other ) {
        passed += other.passed;
        failed += other.failed;
        failedButOk += other.failedButOk;
        return *this;
    }

    std::size_t Counts::total() const {
        return passed + failed + failedButOk;
    }
    bool Counts::allPassed() const {
        return failed == 0 && failedButOk == 0;
    }
    bool Counts::allOk() const {
        return failed == 0;
    }

    Totals Totals::operator - ( Totals const& other ) const {
        Totals diff;
        diff.assertions = assertions - other.assertions;
        diff.testCases = testCases - other.testCases;
        return diff;
    }

    Totals& Totals::operator += ( Totals const& other ) {
        assertions += other.assertions;
        testCases += other.testCases;
        return *this;
    }

    Totals Totals::delta( Totals const& prevTotals ) const {
        Totals diff = *this - prevTotals;
        if( diff.assertions.failed > 0 )
            ++diff.testCases.failed;
        else if( diff.assertions.failedButOk > 0 )
            ++diff.testCases.failedButOk;
        else
            ++diff.testCases.passed;
        return diff;
    }

}
// end catch_totals.cpp
// start catch_version.cpp

#include <ostream>

namespace Catch {

    Version::Version
        (   unsigned int _majorVersion,
            unsigned int _minorVersion,
            unsigned int _patchNumber,
            char const * const _branchName,
            unsigned int _buildNumber )
    :   majorVersion( _majorVersion ),
        minorVersion( _minorVersion ),
        patchNumber( _patchNumber ),
        branchName( _branchName ),
        buildNumber( _buildNumber )
    {}

    std::ostream& operator << ( std::ostream& os, Version const& version ) {
        os  << version.majorVersion << '.'
            << version.minorVersion << '.'
            << version.patchNumber;
        // branchName is never null -> 0th char is \0 if it is empty
        if (version.branchName[0]) {
            os << '-' << version.branchName
               << '.' << version.buildNumber;
        }
        return os;
    }

    Version const& libraryVersion() {
        static Version version( 2, 0, 0, "develop", 1 );
        return version;
    }

}
// end catch_version.cpp
// start catch_wildcard_pattern.cpp

namespace Catch {

    WildcardPattern::WildcardPattern( std::string const& pattern,
                                      CaseSensitive::Choice caseSensitivity )
    :   m_caseSensitivity( caseSensitivity ),
        m_pattern( adjustCase( pattern ) )
    {
        if( startsWith( m_pattern, '*' ) ) {
            m_pattern = m_pattern.substr( 1 );
            m_wildcard = WildcardAtStart;
        }
        if( endsWith( m_pattern, '*' ) ) {
            m_pattern = m_pattern.substr( 0, m_pattern.size()-1 );
            m_wildcard = static_cast<WildcardPosition>( m_wildcard | WildcardAtEnd );
        }
    }

    bool WildcardPattern::matches( std::string const& str ) const {
        switch( m_wildcard ) {
            case NoWildcard:
                return m_pattern == adjustCase( str );
            case WildcardAtStart:
                return endsWith( adjustCase( str ), m_pattern );
            case WildcardAtEnd:
                return startsWith( adjustCase( str ), m_pattern );
            case WildcardAtBothEnds:
                return contains( adjustCase( str ), m_pattern );
            default:
                CATCH_INTERNAL_ERROR( "Unknown enum" );
        }
    }

    std::string WildcardPattern::adjustCase( std::string const& str ) const {
        return m_caseSensitivity == CaseSensitive::No ? toLower( str ) : str;
    }
}
// end catch_wildcard_pattern.cpp
// start catch_xmlwriter.cpp

// start catch_xmlwriter.hpp

#include <sstream>
#include <vector>

namespace Catch {

    class XmlEncode {
    public:
        enum ForWhat { ForTextNodes, ForAttributes };

        XmlEncode( std::string const& str, ForWhat forWhat = ForTextNodes );

        void encodeTo( std::ostream& os ) const;

        friend std::ostream& operator << ( std::ostream& os, XmlEncode const& xmlEncode );

    private:
        std::string m_str;
        ForWhat m_forWhat;
    };

    class XmlWriter {
    public:

        class ScopedElement {
        public:
            ScopedElement( XmlWriter* writer );

            ScopedElement( ScopedElement&& other ) noexcept;
            ScopedElement& operator=( ScopedElement&& other ) noexcept;

            ~ScopedElement();

            ScopedElement& writeText( std::string const& text, bool indent = true );

            template<typename T>
            ScopedElement& writeAttribute( std::string const& name, T const& attribute ) {
                m_writer->writeAttribute( name, attribute );
                return *this;
            }

        private:
            mutable XmlWriter* m_writer = nullptr;
        };

        XmlWriter( std::ostream& os = Catch::cout() );
        ~XmlWriter();

        XmlWriter( XmlWriter const& ) = delete;
        XmlWriter& operator=( XmlWriter const& ) = delete;

        XmlWriter& startElement( std::string const& name );

        ScopedElement scopedElement( std::string const& name );

        XmlWriter& endElement();

        XmlWriter& writeAttribute( std::string const& name, std::string const& attribute );

        XmlWriter& writeAttribute( std::string const& name, bool attribute );

        template<typename T>
        XmlWriter& writeAttribute( std::string const& name, T const& attribute ) {
            m_oss.clear();
            m_oss.str(std::string());
            m_oss << attribute;
            return writeAttribute( name, m_oss.str() );
        }

        XmlWriter& writeText( std::string const& text, bool indent = true );

        XmlWriter& writeComment( std::string const& text );

        void writeStylesheetRef( std::string const& url );

        XmlWriter& writeBlankLine();

        void ensureTagClosed();

    private:

        void writeDeclaration();

        void newlineIfNecessary();

        bool m_tagIsOpen = false;
        bool m_needsNewline = false;
        std::vector<std::string> m_tags;
        std::string m_indent;
        std::ostream& m_os;
        std::ostringstream m_oss;
    };

}

// end catch_xmlwriter.hpp
#include <iomanip>

namespace Catch {

    XmlEncode::XmlEncode( std::string const& str, ForWhat forWhat )
    :   m_str( str ),
        m_forWhat( forWhat )
    {}

    void XmlEncode::encodeTo( std::ostream& os ) const {

        // Apostrophe escaping not necessary if we always use " to write attributes
        // (see: http://www.w3.org/TR/xml/#syntax)

        for( std::size_t i = 0; i < m_str.size(); ++ i ) {
            char c = m_str[i];
            switch( c ) {
                case '<':   os << "&lt;"; break;
                case '&':   os << "&amp;"; break;

                case '>':
                    // See: http://www.w3.org/TR/xml/#syntax
                    if( i > 2 && m_str[i-1] == ']' && m_str[i-2] == ']' )
                        os << "&gt;";
                    else
                        os << c;
                    break;

                case '\"':
                    if( m_forWhat == ForAttributes )
                        os << "&quot;";
                    else
                        os << c;
                    break;

                default:
                    // Escape control chars - based on contribution by @espenalb in PR #465 and
                    // by @mrpi PR #588
                    if ( ( c >= 0 && c < '\x09' ) || ( c > '\x0D' && c < '\x20') || c=='\x7F' ) {
                        // see http://stackoverflow.com/questions/404107/why-are-control-characters-illegal-in-xml-1-0
                        os << "\\x" << std::uppercase << std::hex << std::setfill('0') << std::setw(2)
                           << static_cast<int>( c );
                    }
                    else
                        os << c;
            }
        }
    }

    std::ostream& operator << ( std::ostream& os, XmlEncode const& xmlEncode ) {
        xmlEncode.encodeTo( os );
        return os;
    }

    XmlWriter::ScopedElement::ScopedElement( XmlWriter* writer )
    :   m_writer( writer )
    {}

    XmlWriter::ScopedElement::ScopedElement( ScopedElement&& other ) noexcept
    :   m_writer( other.m_writer ){
        other.m_writer = nullptr;
    }
    XmlWriter::ScopedElement& XmlWriter::ScopedElement::operator=( ScopedElement&& other ) noexcept {
        if ( m_writer ) {
            m_writer->endElement();
        }
        m_writer = other.m_writer;
        other.m_writer = nullptr;
        return *this;
    }

    XmlWriter::ScopedElement::~ScopedElement() {
        if( m_writer )
            m_writer->endElement();
    }

    XmlWriter::ScopedElement& XmlWriter::ScopedElement::writeText( std::string const& text, bool indent ) {
        m_writer->writeText( text, indent );
        return *this;
    }

    XmlWriter::XmlWriter( std::ostream& os ) : m_os( os )
    {
        writeDeclaration();
    }

    XmlWriter::~XmlWriter() {
        while( !m_tags.empty() )
            endElement();
    }

    XmlWriter& XmlWriter::startElement( std::string const& name ) {
        ensureTagClosed();
        newlineIfNecessary();
        m_os << m_indent << '<' << name;
        m_tags.push_back( name );
        m_indent += "  ";
        m_tagIsOpen = true;
        return *this;
    }

    XmlWriter::ScopedElement XmlWriter::scopedElement( std::string const& name ) {
        ScopedElement scoped( this );
        startElement( name );
        return scoped;
    }

    XmlWriter& XmlWriter::endElement() {
        newlineIfNecessary();
        m_indent = m_indent.substr( 0, m_indent.size()-2 );
        if( m_tagIsOpen ) {
            m_os << "/>";
            m_tagIsOpen = false;
        }
        else {
            m_os << m_indent << "</" << m_tags.back() << ">";
        }
        m_os << std::endl;
        m_tags.pop_back();
        return *this;
    }

    XmlWriter& XmlWriter::writeAttribute( std::string const& name, std::string const& attribute ) {
        if( !name.empty() && !attribute.empty() )
            m_os << ' ' << name << "=\"" << XmlEncode( attribute, XmlEncode::ForAttributes ) << '"';
        return *this;
    }

    XmlWriter& XmlWriter::writeAttribute( std::string const& name, bool attribute ) {
        m_os << ' ' << name << "=\"" << ( attribute ? "true" : "false" ) << '"';
        return *this;
    }

    XmlWriter& XmlWriter::writeText( std::string const& text, bool indent ) {
        if( !text.empty() ){
            bool tagWasOpen = m_tagIsOpen;
            ensureTagClosed();
            if( tagWasOpen && indent )
                m_os << m_indent;
            m_os << XmlEncode( text );
            m_needsNewline = true;
        }
        return *this;
    }

    XmlWriter& XmlWriter::writeComment( std::string const& text ) {
        ensureTagClosed();
        m_os << m_indent << "<!--" << text << "-->";
        m_needsNewline = true;
        return *this;
    }

    void XmlWriter::writeStylesheetRef( std::string const& url ) {
        m_os << "<?xml-stylesheet type=\"text/xsl\" href=\"" << url << "\"?>\n";
    }

    XmlWriter& XmlWriter::writeBlankLine() {
        ensureTagClosed();
        m_os << '\n';
        return *this;
    }

    void XmlWriter::ensureTagClosed() {
        if( m_tagIsOpen ) {
            m_os << ">" << std::endl;
            m_tagIsOpen = false;
        }
    }

    void XmlWriter::writeDeclaration() {
        m_os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    }

    void XmlWriter::newlineIfNecessary() {
        if( m_needsNewline ) {
            m_os << std::endl;
            m_needsNewline = false;
        }
    }
}
// end catch_xmlwriter.cpp
// start catch_reporter_bases.cpp

#include <cstring>
#include <cfloat>
#include <cstdio>
#include <assert.h>
#include <memory>

namespace Catch {
    void prepareExpandedExpression(AssertionResult& result) {
        if (result.isOk())
            result.discardDecomposedExpression();
        else
            result.expandDecomposedExpression();
    }

    // Because formatting using c++ streams is stateful, drop down to C is required
    // Alternatively we could use stringstream, but its performance is... not good.
    std::string getFormattedDuration( double duration ) {
        // Max exponent + 1 is required to represent the whole part
        // + 1 for decimal point
        // + 3 for the 3 decimal places
        // + 1 for null terminator
        const size_t maxDoubleSize = DBL_MAX_10_EXP + 1 + 1 + 3 + 1;
        char buffer[maxDoubleSize];

        // Save previous errno, to prevent sprintf from overwriting it
        ErrnoGuard guard;
#ifdef _MSC_VER
        sprintf_s(buffer, "%.3f", duration);
#else
        sprintf(buffer, "%.3f", duration);
#endif
        return std::string(buffer);
    }

    TestEventListenerBase::TestEventListenerBase(ReporterConfig const & _config)
        :StreamingReporterBase(_config) {}

    void TestEventListenerBase::assertionStarting(AssertionInfo const &) {}

    bool TestEventListenerBase::assertionEnded(AssertionStats const &) {
        return false;
    }

} // end namespace Catch
// end catch_reporter_bases.cpp
// start catch_reporter_compact.cpp

namespace {

#ifdef CATCH_PLATFORM_MAC
    const char* failedString() { return "FAILED"; }
    const char* passedString() { return "PASSED"; }
#else
    const char* failedString() { return "failed"; }
    const char* passedString() { return "passed"; }
#endif

    // Colour::LightGrey
    Catch::Colour::Code dimColour() { return Catch::Colour::FileName; }

    std::string bothOrAll( std::size_t count ) {
        return count == 1 ? std::string() :
               count == 2 ? "both " : "all " ;
    }
}

namespace Catch {

    struct CompactReporter : StreamingReporterBase<CompactReporter> {

        using StreamingReporterBase::StreamingReporterBase;

        ~CompactReporter() override;

        static std::string getDescription() {
            return "Reports test results on a single line, suitable for IDEs";
        }

        ReporterPreferences getPreferences() const override {
            ReporterPreferences prefs;
            prefs.shouldRedirectStdOut = false;
            return prefs;
        }

        void noMatchingTestCases( std::string const& spec ) override {
            stream << "No test cases matched '" << spec << '\'' << std::endl;
        }

        void assertionStarting( AssertionInfo const& ) override {}

        bool assertionEnded( AssertionStats const& _assertionStats ) override {
            AssertionResult const& result = _assertionStats.assertionResult;

            bool printInfoMessages = true;

            // Drop out if result was successful and we're not printing those
            if( !m_config->includeSuccessfulResults() && result.isOk() ) {
                if( result.getResultType() != ResultWas::Warning )
                    return false;
                printInfoMessages = false;
            }

            AssertionPrinter printer( stream, _assertionStats, printInfoMessages );
            printer.print();

            stream << std::endl;
            return true;
        }

        void sectionEnded(SectionStats const& _sectionStats) override {
            if (m_config->showDurations() == ShowDurations::Always) {
                stream << getFormattedDuration(_sectionStats.durationInSeconds) << " s: " << _sectionStats.sectionInfo.name << std::endl;
            }
        }

        void testRunEnded( TestRunStats const& _testRunStats ) override {
            printTotals( _testRunStats.totals );
            stream << '\n' << std::endl;
            StreamingReporterBase::testRunEnded( _testRunStats );
        }

    private:
        class AssertionPrinter {
        public:
            AssertionPrinter& operator= ( AssertionPrinter const& ) = delete;
            AssertionPrinter( AssertionPrinter const& ) = delete;
            AssertionPrinter( std::ostream& _stream, AssertionStats const& _stats, bool _printInfoMessages )
            : stream( _stream )
            , result( _stats.assertionResult )
            , messages( _stats.infoMessages )
            , itMessage( _stats.infoMessages.begin() )
            , printInfoMessages( _printInfoMessages )
            {}

            void print() {
                printSourceInfo();

                itMessage = messages.begin();

                switch( result.getResultType() ) {
                    case ResultWas::Ok:
                        printResultType( Colour::ResultSuccess, passedString() );
                        printOriginalExpression();
                        printReconstructedExpression();
                        if ( ! result.hasExpression() )
                            printRemainingMessages( Colour::None );
                        else
                            printRemainingMessages();
                        break;
                    case ResultWas::ExpressionFailed:
                        if( result.isOk() )
                            printResultType( Colour::ResultSuccess, failedString() + std::string( " - but was ok" ) );
                        else
                            printResultType( Colour::Error, failedString() );
                        printOriginalExpression();
                        printReconstructedExpression();
                        printRemainingMessages();
                        break;
                    case ResultWas::ThrewException:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "unexpected exception with message:" );
                        printMessage();
                        printExpressionWas();
                        printRemainingMessages();
                        break;
                    case ResultWas::FatalErrorCondition:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "fatal error condition with message:" );
                        printMessage();
                        printExpressionWas();
                        printRemainingMessages();
                        break;
                    case ResultWas::DidntThrowException:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "expected exception, got none" );
                        printExpressionWas();
                        printRemainingMessages();
                        break;
                    case ResultWas::Info:
                        printResultType( Colour::None, "info" );
                        printMessage();
                        printRemainingMessages();
                        break;
                    case ResultWas::Warning:
                        printResultType( Colour::None, "warning" );
                        printMessage();
                        printRemainingMessages();
                        break;
                    case ResultWas::ExplicitFailure:
                        printResultType( Colour::Error, failedString() );
                        printIssue( "explicitly" );
                        printRemainingMessages( Colour::None );
                        break;
                    // These cases are here to prevent compiler warnings
                    case ResultWas::Unknown:
                    case ResultWas::FailureBit:
                    case ResultWas::Exception:
                        printResultType( Colour::Error, "** internal error **" );
                        break;
                }
            }

        private:
            void printSourceInfo() const {
                Colour colourGuard( Colour::FileName );
                stream << result.getSourceInfo() << ':';
            }

            void printResultType( Colour::Code colour, std::string const& passOrFail ) const {
                if( !passOrFail.empty() ) {
                    {
                        Colour colourGuard( colour );
                        stream << ' ' << passOrFail;
                    }
                    stream << ':';
                }
            }

            void printIssue( std::string const& issue ) const {
                stream << ' ' << issue;
            }

            void printExpressionWas() {
                if( result.hasExpression() ) {
                    stream << ';';
                    {
                        Colour colour( dimColour() );
                        stream << " expression was:";
                    }
                    printOriginalExpression();
                }
            }

            void printOriginalExpression() const {
                if( result.hasExpression() ) {
                    stream << ' ' << result.getExpression();
                }
            }

            void printReconstructedExpression() const {
                if( result.hasExpandedExpression() ) {
                    {
                        Colour colour( dimColour() );
                        stream << " for: ";
                    }
                    stream << result.getExpandedExpression();
                }
            }

            void printMessage() {
                if ( itMessage != messages.end() ) {
                    stream << " '" << itMessage->message << '\'';
                    ++itMessage;
                }
            }

            void printRemainingMessages( Colour::Code colour = dimColour() ) {
                if ( itMessage == messages.end() )
                    return;

                // using messages.end() directly yields (or auto) compilation error:
                std::vector<MessageInfo>::const_iterator itEnd = messages.end();
                const std::size_t N = static_cast<std::size_t>( std::distance( itMessage, itEnd ) );

                {
                    Colour colourGuard( colour );
                    stream << " with " << pluralise( N, "message" ) << ':';
                }

                for(; itMessage != itEnd; ) {
                    // If this assertion is a warning ignore any INFO messages
                    if( printInfoMessages || itMessage->type != ResultWas::Info ) {
                        stream << " '" << itMessage->message << '\'';
                        if ( ++itMessage != itEnd ) {
                            Colour colourGuard( dimColour() );
                            stream << " and";
                        }
                    }
                }
            }

        private:
            std::ostream& stream;
            AssertionResult const& result;
            std::vector<MessageInfo> messages;
            std::vector<MessageInfo>::const_iterator itMessage;
            bool printInfoMessages;
        };

        // Colour, message variants:
        // - white: No tests ran.
        // -   red: Failed [both/all] N test cases, failed [both/all] M assertions.
        // - white: Passed [both/all] N test cases (no assertions).
        // -   red: Failed N tests cases, failed M assertions.
        // - green: Passed [both/all] N tests cases with M assertions.

        void printTotals( const Totals& totals ) const {
            if( totals.testCases.total() == 0 ) {
                stream << "No tests ran.";
            }
            else if( totals.testCases.failed == totals.testCases.total() ) {
                Colour colour( Colour::ResultError );
                const std::string qualify_assertions_failed =
                    totals.assertions.failed == totals.assertions.total() ?
                        bothOrAll( totals.assertions.failed ) : std::string();
                stream <<
                    "Failed " << bothOrAll( totals.testCases.failed )
                              << pluralise( totals.testCases.failed, "test case"  ) << ", "
                    "failed " << qualify_assertions_failed <<
                                 pluralise( totals.assertions.failed, "assertion" ) << '.';
            }
            else if( totals.assertions.total() == 0 ) {
                stream <<
                    "Passed " << bothOrAll( totals.testCases.total() )
                              << pluralise( totals.testCases.total(), "test case" )
                              << " (no assertions).";
            }
            else if( totals.assertions.failed ) {
                Colour colour( Colour::ResultError );
                stream <<
                    "Failed " << pluralise( totals.testCases.failed, "test case"  ) << ", "
                    "failed " << pluralise( totals.assertions.failed, "assertion" ) << '.';
            }
            else {
                Colour colour( Colour::ResultSuccess );
                stream <<
                    "Passed " << bothOrAll( totals.testCases.passed )
                              << pluralise( totals.testCases.passed, "test case"  ) <<
                    " with "  << pluralise( totals.assertions.passed, "assertion" ) << '.';
            }
        }
    };

    CompactReporter::~CompactReporter() {}

    INTERNAL_CATCH_REGISTER_REPORTER( "compact", CompactReporter )

} // end namespace Catch
// end catch_reporter_compact.cpp
// start catch_reporter_console.cpp

#include <cfloat>
#include <cstdio>

namespace {
    std::size_t makeRatio( std::size_t number, std::size_t total ) {
        std::size_t ratio = total > 0 ? CATCH_CONFIG_CONSOLE_WIDTH * number/ total : 0;
        return ( ratio == 0 && number > 0 ) ? 1 : ratio;
    }

    std::size_t& findMax( std::size_t& i, std::size_t& j, std::size_t& k ) {
        if( i > j && i > k )
            return i;
        else if( j > k )
            return j;
        else
            return k;
    }

    struct ColumnInfo {
        enum Justification { Left, Right };
        std::string name;
        int width;
        Justification justification;
    };
    struct ColumnBreak {};
    struct RowBreak {};

    class TablePrinter {
        std::ostream& m_os;
        std::vector<ColumnInfo> m_columnInfos;
        std::ostringstream m_oss;
        int m_currentColumn = -1;
        bool m_isOpen = false;

    public:
        TablePrinter( std::ostream& os, std::vector<ColumnInfo> const& columnInfos )
        :   m_os( os ),
            m_columnInfos( columnInfos )
        {}

        auto columnInfos() const -> std::vector<ColumnInfo> const& {
            return m_columnInfos;
        }

        void open() {
            if( !m_isOpen ) {
                m_isOpen = true;
                *this << RowBreak();
                for( auto const& info : m_columnInfos )
                    *this << info.name << ColumnBreak();
                *this << RowBreak();
            }
        }
        void close() {
            if( m_isOpen ) {
                *this << RowBreak();
                m_os << std::endl;
                m_isOpen = false;
            }
        }

        template<typename T>
        friend TablePrinter& operator << ( TablePrinter& tp, T const& value ) {
            tp.m_oss << value;
            return tp;
        }

        friend TablePrinter& operator << ( TablePrinter& tp, ColumnBreak ) {
            auto colStr = tp.m_oss.str();
            tp.m_oss.str("");
            tp.open();
            if( tp.m_currentColumn == static_cast<int>(tp.m_columnInfos.size()-1) ) {
                tp.m_currentColumn = -1;
                tp.m_os << "\n";
            }
            if( tp.m_currentColumn == -1 )
                tp.m_os << "|";
            tp.m_currentColumn++;

            auto colInfo = tp.m_columnInfos[tp.m_currentColumn];
            auto padding = ( colStr.size()+2 < static_cast<size_t>( colInfo.width ) )
                ? std::string( colInfo.width-(colStr.size()+2), ' ' )
                : std::string();
            if( colInfo.justification == ColumnInfo::Left )
                tp.m_os << " " << colStr << padding << " |";
            else
                tp.m_os << " " << padding << colStr << " |";
            return tp;
        }

        friend TablePrinter& operator << ( TablePrinter& tp, RowBreak ) {
            if( tp.m_currentColumn > 0 ) {
                tp.m_os << "\n";
                tp.m_currentColumn = -1;
            }
            tp.m_os << Catch::getBoxCharsAcross() << "\n";
            return tp;
        }
    };
}

namespace Catch {

    struct ConsoleReporter : StreamingReporterBase<ConsoleReporter> {
        TablePrinter m_tablePrinter;

        ConsoleReporter( ReporterConfig const& config )
        :   StreamingReporterBase( config ),
            m_tablePrinter( config.stream(),
                            {
                                { "benchmark name", CATCH_CONFIG_CONSOLE_WIDTH-42, ColumnInfo::Left },
                                { "iters", 8, ColumnInfo::Right },
                                { "elapsed ns", 14, ColumnInfo::Right },
                                { "average", 14, ColumnInfo::Right }
                            } )
        {}
        ~ConsoleReporter() override;
        static std::string getDescription() {
            return "Reports test results as plain lines of text";
        }

        void noMatchingTestCases( std::string const& spec ) override {
            stream << "No test cases matched '" << spec << '\'' << std::endl;
        }

        void assertionStarting( AssertionInfo const& ) override {
        }

        bool assertionEnded( AssertionStats const& _assertionStats ) override {
            AssertionResult const& result = _assertionStats.assertionResult;

            bool includeResults = m_config->includeSuccessfulResults() || !result.isOk();

            // Drop out if result was successful but we're not printing them.
            if( !includeResults && result.getResultType() != ResultWas::Warning )
                return false;

            lazyPrint();

            AssertionPrinter printer( stream, _assertionStats, includeResults );
            printer.print();
            stream << std::endl;
            return true;
        }

        void sectionStarting( SectionInfo const& _sectionInfo ) override {
            m_headerPrinted = false;
            StreamingReporterBase::sectionStarting( _sectionInfo );
        }
        void sectionEnded( SectionStats const& _sectionStats ) override {
            m_tablePrinter.close();
            if( _sectionStats.missingAssertions ) {
                lazyPrint();
                Colour colour( Colour::ResultError );
                if( m_sectionStack.size() > 1 )
                    stream << "\nNo assertions in section";
                else
                    stream << "\nNo assertions in test case";
                stream << " '" << _sectionStats.sectionInfo.name << "'\n" << std::endl;
            }
            if( m_config->showDurations() == ShowDurations::Always ) {
                stream << getFormattedDuration(_sectionStats.durationInSeconds) << " s: " << _sectionStats.sectionInfo.name << std::endl;
            }
            if( m_headerPrinted ) {
                m_headerPrinted = false;
            }
            StreamingReporterBase::sectionEnded( _sectionStats );
        }

        void benchmarkStarting( BenchmarkInfo const& info ) override {
            lazyPrintWithoutClosingBenchmarkTable();

            auto nameCol = Column( info.name ).width( m_tablePrinter.columnInfos()[0].width-2 );

            bool firstLine = true;
            for( auto line : nameCol ) {
                if( !firstLine )
                    m_tablePrinter << ColumnBreak() << ColumnBreak() << ColumnBreak();
                else
                    firstLine = false;

                m_tablePrinter << line << ColumnBreak();
            }
        }
        void benchmarkEnded( BenchmarkStats const& stats ) override {
            // !TBD: report average times in natural units?
            m_tablePrinter
                    << stats.iterations << ColumnBreak()
                    << stats.elapsedTimeInNanoseconds << ColumnBreak()
                    << stats.elapsedTimeInNanoseconds/stats.iterations << " ns" << ColumnBreak();
        }

        void testCaseEnded( TestCaseStats const& _testCaseStats ) override {
            m_tablePrinter.close();
            StreamingReporterBase::testCaseEnded( _testCaseStats );
            m_headerPrinted = false;
        }
        void testGroupEnded( TestGroupStats const& _testGroupStats ) override {
            if( currentGroupInfo.used ) {
                printSummaryDivider();
                stream << "Summary for group '" << _testGroupStats.groupInfo.name << "':\n";
                printTotals( _testGroupStats.totals );
                stream << '\n' << std::endl;
            }
            StreamingReporterBase::testGroupEnded( _testGroupStats );
        }
        void testRunEnded( TestRunStats const& _testRunStats ) override {
            printTotalsDivider( _testRunStats.totals );
            printTotals( _testRunStats.totals );
            stream << std::endl;
            StreamingReporterBase::testRunEnded( _testRunStats );
        }

    private:

        class AssertionPrinter {
        public:
            AssertionPrinter& operator= ( AssertionPrinter const& ) = delete;
            AssertionPrinter( AssertionPrinter const& ) = delete;
            AssertionPrinter( std::ostream& _stream, AssertionStats const& _stats, bool _printInfoMessages )
            :   stream( _stream ),
                stats( _stats ),
                result( _stats.assertionResult ),
                colour( Colour::None ),
                message( result.getMessage() ),
                messages( _stats.infoMessages ),
                printInfoMessages( _printInfoMessages )
            {
                switch( result.getResultType() ) {
                    case ResultWas::Ok:
                        colour = Colour::Success;
                        passOrFail = "PASSED";
                        //if( result.hasMessage() )
                        if( _stats.infoMessages.size() == 1 )
                            messageLabel = "with message";
                        if( _stats.infoMessages.size() > 1 )
                            messageLabel = "with messages";
                        break;
                    case ResultWas::ExpressionFailed:
                        if( result.isOk() ) {
                            colour = Colour::Success;
                            passOrFail = "FAILED - but was ok";
                        }
                        else {
                            colour = Colour::Error;
                            passOrFail = "FAILED";
                        }
                        if( _stats.infoMessages.size() == 1 )
                            messageLabel = "with message";
                        if( _stats.infoMessages.size() > 1 )
                            messageLabel = "with messages";
                        break;
                    case ResultWas::ThrewException:
                        colour = Colour::Error;
                        passOrFail = "FAILED";
                        messageLabel = "due to unexpected exception with ";
                        if (_stats.infoMessages.size() == 1)
                            messageLabel += "message";
                        if (_stats.infoMessages.size() > 1)
                            messageLabel += "messages";
                        break;
                    case ResultWas::FatalErrorCondition:
                        colour = Colour::Error;
                        passOrFail = "FAILED";
                        messageLabel = "due to a fatal error condition";
                        break;
                    case ResultWas::DidntThrowException:
                        colour = Colour::Error;
                        passOrFail = "FAILED";
                        messageLabel = "because no exception was thrown where one was expected";
                        break;
                    case ResultWas::Info:
                        messageLabel = "info";
                        break;
                    case ResultWas::Warning:
                        messageLabel = "warning";
                        break;
                    case ResultWas::ExplicitFailure:
                        passOrFail = "FAILED";
                        colour = Colour::Error;
                        if( _stats.infoMessages.size() == 1 )
                            messageLabel = "explicitly with message";
                        if( _stats.infoMessages.size() > 1 )
                            messageLabel = "explicitly with messages";
                        break;
                    // These cases are here to prevent compiler warnings
                    case ResultWas::Unknown:
                    case ResultWas::FailureBit:
                    case ResultWas::Exception:
                        passOrFail = "** internal error **";
                        colour = Colour::Error;
                        break;
                }
            }

            void print() const {
                printSourceInfo();
                if( stats.totals.assertions.total() > 0 ) {
                    if( result.isOk() )
                        stream << '\n';
                    printResultType();
                    printOriginalExpression();
                    printReconstructedExpression();
                }
                else {
                    stream << '\n';
                }
                printMessage();
            }

        private:
            void printResultType() const {
                if( !passOrFail.empty() ) {
                    Colour colourGuard( colour );
                    stream << passOrFail << ":\n";
                }
            }
            void printOriginalExpression() const {
                if( result.hasExpression() ) {
                    Colour colourGuard( Colour::OriginalExpression );
                    stream  << "  ";
                    stream << result.getExpressionInMacro();
                    stream << '\n';
                }
            }
            void printReconstructedExpression() const {
                if( result.hasExpandedExpression() ) {
                    stream << "with expansion:\n";
                    Colour colourGuard( Colour::ReconstructedExpression );
                    stream << Column( result.getExpandedExpression() ).indent(2) << '\n';
                }
            }
            void printMessage() const {
                if( !messageLabel.empty() )
                    stream << messageLabel << ':' << '\n';
                for( auto const& msg : messages ) {
                    // If this assertion is a warning ignore any INFO messages
                    if( printInfoMessages || msg.type != ResultWas::Info )
                        stream << Column( msg.message ).indent(2) << '\n';
                }
            }
            void printSourceInfo() const {
                Colour colourGuard( Colour::FileName );
                stream << result.getSourceInfo() << ": ";
            }

            std::ostream& stream;
            AssertionStats const& stats;
            AssertionResult const& result;
            Colour::Code colour;
            std::string passOrFail;
            std::string messageLabel;
            std::string message;
            std::vector<MessageInfo> messages;
            bool printInfoMessages;
        };

        void lazyPrint() {

            m_tablePrinter.close();
            lazyPrintWithoutClosingBenchmarkTable();
        }

        void lazyPrintWithoutClosingBenchmarkTable() {

            if( !currentTestRunInfo.used )
                lazyPrintRunInfo();
            if( !currentGroupInfo.used )
                lazyPrintGroupInfo();

            if( !m_headerPrinted ) {
                printTestCaseAndSectionHeader();
                m_headerPrinted = true;
            }
        }
        void lazyPrintRunInfo() {
            stream  << '\n' << getLineOfChars<'~'>() << '\n';
            Colour colour( Colour::SecondaryText );
            stream  << currentTestRunInfo->name
                    << " is a Catch v"  << libraryVersion() << " host application.\n"
                    << "Run with -? for options\n\n";

            if( m_config->rngSeed() != 0 )
                stream << "Randomness seeded to: " << m_config->rngSeed() << "\n\n";

            currentTestRunInfo.used = true;
        }
        void lazyPrintGroupInfo() {
            if( !currentGroupInfo->name.empty() && currentGroupInfo->groupsCounts > 1 ) {
                printClosedHeader( "Group: " + currentGroupInfo->name );
                currentGroupInfo.used = true;
            }
        }
        void printTestCaseAndSectionHeader() {
            assert( !m_sectionStack.empty() );
            printOpenHeader( currentTestCaseInfo->name );

            if( m_sectionStack.size() > 1 ) {
                Colour colourGuard( Colour::Headers );

                auto
                    it = m_sectionStack.begin()+1, // Skip first section (test case)
                    itEnd = m_sectionStack.end();
                for( ; it != itEnd; ++it )
                    printHeaderString( it->name, 2 );
            }

            SourceLineInfo lineInfo = m_sectionStack.back().lineInfo;

            if( !lineInfo.empty() ){
                stream << getLineOfChars<'-'>() << '\n';
                Colour colourGuard( Colour::FileName );
                stream << lineInfo << '\n';
            }
            stream << getLineOfChars<'.'>() << '\n' << std::endl;
        }

        void printClosedHeader( std::string const& _name ) {
            printOpenHeader( _name );
            stream << getLineOfChars<'.'>() << '\n';
        }
        void printOpenHeader( std::string const& _name ) {
            stream  << getLineOfChars<'-'>() << '\n';
            {
                Colour colourGuard( Colour::Headers );
                printHeaderString( _name );
            }
        }

        // if string has a : in first line will set indent to follow it on
        // subsequent lines
        void printHeaderString( std::string const& _string, std::size_t indent = 0 ) {
            std::size_t i = _string.find( ": " );
            if( i != std::string::npos )
                i+=2;
            else
                i = 0;
            stream << Column( _string ).indent( indent+i ).initialIndent( indent ) << '\n';
        }

        struct SummaryColumn {

            SummaryColumn( std::string const& _label, Colour::Code _colour )
            :   label( _label ),
                colour( _colour )
            {}
            SummaryColumn addRow( std::size_t count ) {
                std::ostringstream oss;
                oss << count;
                std::string row = oss.str();
                for( auto& oldRow : rows ) {
                    while( oldRow.size() < row.size() )
                        oldRow = ' ' + oldRow;
                    while( oldRow.size() > row.size() )
                        row = ' ' + row;
                }
                rows.push_back( row );
                return *this;
            }

            std::string label;
            Colour::Code colour;
            std::vector<std::string> rows;

        };

        void printTotals( Totals const& totals ) {
            if( totals.testCases.total() == 0 ) {
                stream << Colour( Colour::Warning ) << "No tests ran\n";
            }
            else if( totals.assertions.total() > 0 && totals.testCases.allPassed() ) {
                stream << Colour( Colour::ResultSuccess ) << "All tests passed";
                stream << " ("
                        << pluralise( totals.assertions.passed, "assertion" ) << " in "
                        << pluralise( totals.testCases.passed, "test case" ) << ')'
                        << '\n';
            }
            else {

                std::vector<SummaryColumn> columns;
                columns.push_back( SummaryColumn( "", Colour::None )
                                        .addRow( totals.testCases.total() )
                                        .addRow( totals.assertions.total() ) );
                columns.push_back( SummaryColumn( "passed", Colour::Success )
                                        .addRow( totals.testCases.passed )
                                        .addRow( totals.assertions.passed ) );
                columns.push_back( SummaryColumn( "failed", Colour::ResultError )
                                        .addRow( totals.testCases.failed )
                                        .addRow( totals.assertions.failed ) );
                columns.push_back( SummaryColumn( "failed as expected", Colour::ResultExpectedFailure )
                                        .addRow( totals.testCases.failedButOk )
                                        .addRow( totals.assertions.failedButOk ) );

                printSummaryRow( "test cases", columns, 0 );
                printSummaryRow( "assertions", columns, 1 );
            }
        }
        void printSummaryRow( std::string const& label, std::vector<SummaryColumn> const& cols, std::size_t row ) {
            for( auto col : cols ) {
                std::string value = col.rows[row];
                if( col.label.empty() ) {
                    stream << label << ": ";
                    if( value != "0" )
                        stream << value;
                    else
                        stream << Colour( Colour::Warning ) << "- none -";
                }
                else if( value != "0" ) {
                    stream  << Colour( Colour::LightGrey ) << " | ";
                    stream  << Colour( col.colour )
                            << value << ' ' << col.label;
                }
            }
            stream << '\n';
        }

        void printTotalsDivider( Totals const& totals ) {
            if( totals.testCases.total() > 0 ) {
                std::size_t failedRatio = makeRatio( totals.testCases.failed, totals.testCases.total() );
                std::size_t failedButOkRatio = makeRatio( totals.testCases.failedButOk, totals.testCases.total() );
                std::size_t passedRatio = makeRatio( totals.testCases.passed, totals.testCases.total() );
                while( failedRatio + failedButOkRatio + passedRatio < CATCH_CONFIG_CONSOLE_WIDTH-1 )
                    findMax( failedRatio, failedButOkRatio, passedRatio )++;
                while( failedRatio + failedButOkRatio + passedRatio > CATCH_CONFIG_CONSOLE_WIDTH-1 )
                    findMax( failedRatio, failedButOkRatio, passedRatio )--;

                stream << Colour( Colour::Error ) << std::string( failedRatio, '=' );
                stream << Colour( Colour::ResultExpectedFailure ) << std::string( failedButOkRatio, '=' );
                if( totals.testCases.allPassed() )
                    stream << Colour( Colour::ResultSuccess ) << std::string( passedRatio, '=' );
                else
                    stream << Colour( Colour::Success ) << std::string( passedRatio, '=' );
            }
            else {
                stream << Colour( Colour::Warning ) << std::string( CATCH_CONFIG_CONSOLE_WIDTH-1, '=' );
            }
            stream << '\n';
        }
        void printSummaryDivider() {
            stream << getLineOfChars<'-'>() << '\n';
        }

    private:
        bool m_headerPrinted = false;
    };

    INTERNAL_CATCH_REGISTER_REPORTER( "console", ConsoleReporter )

    ConsoleReporter::~ConsoleReporter() {}

} // end namespace Catch
// end catch_reporter_console.cpp
// start catch_reporter_junit.cpp

#include <assert.h>

#include <ctime>
#include <algorithm>

namespace Catch {

    namespace {
        std::string getCurrentTimestamp() {
            // Beware, this is not reentrant because of backward compatibility issues
            // Also, UTC only, again because of backward compatibility (%z is C++11)
            time_t rawtime;
            std::time(&rawtime);
            const size_t timeStampSize = sizeof("2017-01-16T17:06:45Z");

#ifdef _MSC_VER
            std::tm timeInfo = {};
            gmtime_s(&timeInfo, &rawtime);
#else
            std::tm* timeInfo;
            timeInfo = std::gmtime(&rawtime);
#endif

            char timeStamp[timeStampSize];
            const char * const fmt = "%Y-%m-%dT%H:%M:%SZ";

#ifdef _MSC_VER
            std::strftime(timeStamp, timeStampSize, fmt, &timeInfo);
#else
            std::strftime(timeStamp, timeStampSize, fmt, timeInfo);
#endif
            return std::string(timeStamp);
        }

        std::string fileNameTag(const std::vector<std::string> &tags) {
            auto it = std::find_if(begin(tags),
                                   end(tags),
                                   [] (std::string const& tag) {return tag.front() == '#'; });
            if (it != tags.end())
                return it->substr(1);
            return std::string();
        }
    }

    class JunitReporter : public CumulativeReporterBase<JunitReporter> {
    public:
        JunitReporter( ReporterConfig const& _config )
        :   CumulativeReporterBase( _config ),
            xml( _config.stream() )
        {
            m_reporterPrefs.shouldRedirectStdOut = true;
        }

        ~JunitReporter() override;

        static std::string getDescription() {
            return "Reports test results in an XML format that looks like Ant's junitreport target";
        }

        void noMatchingTestCases( std::string const& /*spec*/ ) override {}

        void testRunStarting( TestRunInfo const& runInfo ) override {
            CumulativeReporterBase::testRunStarting( runInfo );
            xml.startElement( "testsuites" );
        }

        void testGroupStarting( GroupInfo const& groupInfo ) override {
            suiteTimer.start();
            stdOutForSuite.str("");
            stdErrForSuite.str("");
            unexpectedExceptions = 0;
            CumulativeReporterBase::testGroupStarting( groupInfo );
        }

        void testCaseStarting( TestCaseInfo const& testCaseInfo ) override {
            m_okToFail = testCaseInfo.okToFail();
        }
        bool assertionEnded( AssertionStats const& assertionStats ) override {
            if( assertionStats.assertionResult.getResultType() == ResultWas::ThrewException && !m_okToFail )
                unexpectedExceptions++;
            return CumulativeReporterBase::assertionEnded( assertionStats );
        }

        void testCaseEnded( TestCaseStats const& testCaseStats ) override {
            stdOutForSuite << testCaseStats.stdOut;
            stdErrForSuite << testCaseStats.stdErr;
            CumulativeReporterBase::testCaseEnded( testCaseStats );
        }

        void testGroupEnded( TestGroupStats const& testGroupStats ) override {
            double suiteTime = suiteTimer.getElapsedSeconds();
            CumulativeReporterBase::testGroupEnded( testGroupStats );
            writeGroup( *m_testGroups.back(), suiteTime );
        }

        void testRunEndedCumulative() override {
            xml.endElement();
        }

        void writeGroup( TestGroupNode const& groupNode, double suiteTime ) {
            XmlWriter::ScopedElement e = xml.scopedElement( "testsuite" );
            TestGroupStats const& stats = groupNode.value;
            xml.writeAttribute( "name", stats.groupInfo.name );
            xml.writeAttribute( "errors", unexpectedExceptions );
            xml.writeAttribute( "failures", stats.totals.assertions.failed-unexpectedExceptions );
            xml.writeAttribute( "tests", stats.totals.assertions.total() );
            xml.writeAttribute( "hostname", "tbd" ); // !TBD
            if( m_config->showDurations() == ShowDurations::Never )
                xml.writeAttribute( "time", "" );
            else
                xml.writeAttribute( "time", suiteTime );
            xml.writeAttribute( "timestamp", getCurrentTimestamp() );

            // Write test cases
            for( auto const& child : groupNode.children )
                writeTestCase( *child );

            xml.scopedElement( "system-out" ).writeText( trim( stdOutForSuite.str() ), false );
            xml.scopedElement( "system-err" ).writeText( trim( stdErrForSuite.str() ), false );
        }

        void writeTestCase( TestCaseNode const& testCaseNode ) {
            TestCaseStats const& stats = testCaseNode.value;

            // All test cases have exactly one section - which represents the
            // test case itself. That section may have 0-n nested sections
            assert( testCaseNode.children.size() == 1 );
            SectionNode const& rootSection = *testCaseNode.children.front();

            std::string className = stats.testInfo.className;

            if( className.empty() ) {
                className = fileNameTag(stats.testInfo.tags);
                if ( className.empty() )
                    className = "global";
            }

            if ( !m_config->name().empty() )
                className = m_config->name() + "." + className;

            writeSection( className, "", rootSection );
        }

        void writeSection(  std::string const& className,
                            std::string const& rootName,
                            SectionNode const& sectionNode ) {
            std::string name = trim( sectionNode.stats.sectionInfo.name );
            if( !rootName.empty() )
                name = rootName + '/' + name;

            if( !sectionNode.assertions.empty() ||
                !sectionNode.stdOut.empty() ||
                !sectionNode.stdErr.empty() ) {
                XmlWriter::ScopedElement e = xml.scopedElement( "testcase" );
                if( className.empty() ) {
                    xml.writeAttribute( "classname", name );
                    xml.writeAttribute( "name", "root" );
                }
                else {
                    xml.writeAttribute( "classname", className );
                    xml.writeAttribute( "name", name );
                }
                xml.writeAttribute( "time", ::Catch::Detail::stringify( sectionNode.stats.durationInSeconds ) );

                writeAssertions( sectionNode );

                if( !sectionNode.stdOut.empty() )
                    xml.scopedElement( "system-out" ).writeText( trim( sectionNode.stdOut ), false );
                if( !sectionNode.stdErr.empty() )
                    xml.scopedElement( "system-err" ).writeText( trim( sectionNode.stdErr ), false );
            }
            for( auto const& childNode : sectionNode.childSections )
                if( className.empty() )
                    writeSection( name, "", *childNode );
                else
                    writeSection( className, name, *childNode );
        }

        void writeAssertions( SectionNode const& sectionNode ) {
            for( auto const& assertion : sectionNode.assertions )
                writeAssertion( assertion );
        }
        void writeAssertion( AssertionStats const& stats ) {
            AssertionResult const& result = stats.assertionResult;
            if( !result.isOk() ) {
                std::string elementName;
                switch( result.getResultType() ) {
                    case ResultWas::ThrewException:
                    case ResultWas::FatalErrorCondition:
                        elementName = "error";
                        break;
                    case ResultWas::ExplicitFailure:
                        elementName = "failure";
                        break;
                    case ResultWas::ExpressionFailed:
                        elementName = "failure";
                        break;
                    case ResultWas::DidntThrowException:
                        elementName = "failure";
                        break;

                    // We should never see these here:
                    case ResultWas::Info:
                    case ResultWas::Warning:
                    case ResultWas::Ok:
                    case ResultWas::Unknown:
                    case ResultWas::FailureBit:
                    case ResultWas::Exception:
                        elementName = "internalError";
                        break;
                }

                XmlWriter::ScopedElement e = xml.scopedElement( elementName );

                xml.writeAttribute( "message", result.getExpandedExpression() );
                xml.writeAttribute( "type", result.getTestMacroName() );

                std::ostringstream oss;
                if( !result.getMessage().empty() )
                    oss << result.getMessage() << '\n';
                for( auto const& msg : stats.infoMessages )
                    if( msg.type == ResultWas::Info )
                        oss << msg.message << '\n';

                oss << "at " << result.getSourceInfo();
                xml.writeText( oss.str(), false );
            }
        }

        XmlWriter xml;
        Timer suiteTimer;
        std::ostringstream stdOutForSuite;
        std::ostringstream stdErrForSuite;
        unsigned int unexpectedExceptions = 0;
        bool m_okToFail = false;
    };

    JunitReporter::~JunitReporter() {}
    INTERNAL_CATCH_REGISTER_REPORTER( "junit", JunitReporter )

} // end namespace Catch
// end catch_reporter_junit.cpp
// start catch_reporter_multi.cpp

namespace Catch {

    void MultipleReporters::add( IStreamingReporterPtr&& reporter ) {
        m_reporters.push_back( std::move( reporter ) );
    }

    ReporterPreferences MultipleReporters::getPreferences() const {
        return m_reporters[0]->getPreferences();
    }

    std::set<Verbosity> MultipleReporters::getSupportedVerbosities() {
        return { };
    }

    void MultipleReporters::noMatchingTestCases( std::string const& spec ) {
        for( auto const& reporter : m_reporters )
            reporter->noMatchingTestCases( spec );
    }

    void MultipleReporters::testRunStarting( TestRunInfo const& testRunInfo ) {
        for( auto const& reporter : m_reporters )
            reporter->testRunStarting( testRunInfo );
    }

    void MultipleReporters::testGroupStarting( GroupInfo const& groupInfo ) {
        for( auto const& reporter : m_reporters )
            reporter->testGroupStarting( groupInfo );
    }

    void MultipleReporters::testCaseStarting( TestCaseInfo const& testInfo ) {
        for( auto const& reporter : m_reporters )
            reporter->testCaseStarting( testInfo );
    }

    void MultipleReporters::sectionStarting( SectionInfo const& sectionInfo ) {
        for( auto const& reporter : m_reporters )
            reporter->sectionStarting( sectionInfo );
    }

    void MultipleReporters::assertionStarting( AssertionInfo const& assertionInfo ) {
        for( auto const& reporter : m_reporters )
            reporter->assertionStarting( assertionInfo );
    }

    // The return value indicates if the messages buffer should be cleared:
    bool MultipleReporters::assertionEnded( AssertionStats const& assertionStats ) {
        bool clearBuffer = false;
        for( auto const& reporter : m_reporters )
            clearBuffer |= reporter->assertionEnded( assertionStats );
        return clearBuffer;
    }

    void MultipleReporters::sectionEnded( SectionStats const& sectionStats ) {
        for( auto const& reporter : m_reporters )
            reporter->sectionEnded( sectionStats );
    }

    void MultipleReporters::testCaseEnded( TestCaseStats const& testCaseStats ) {
        for( auto const& reporter : m_reporters )
            reporter->testCaseEnded( testCaseStats );
    }

    void MultipleReporters::testGroupEnded( TestGroupStats const& testGroupStats ) {
        for( auto const& reporter : m_reporters )
            reporter->testGroupEnded( testGroupStats );
    }

    void MultipleReporters::testRunEnded( TestRunStats const& testRunStats ) {
        for( auto const& reporter : m_reporters )
            reporter->testRunEnded( testRunStats );
    }

    void MultipleReporters::skipTest( TestCaseInfo const& testInfo ) {
        for( auto const& reporter : m_reporters )
            reporter->skipTest( testInfo );
    }

    bool MultipleReporters::isMulti() const {
        return true;
    }

} // end namespace Catch
// end catch_reporter_multi.cpp
// start catch_reporter_xml.cpp

namespace Catch {
    class XmlReporter : public StreamingReporterBase<XmlReporter> {
    public:
        XmlReporter( ReporterConfig const& _config )
        :   StreamingReporterBase( _config ),
            m_xml(_config.stream())
        {
            m_reporterPrefs.shouldRedirectStdOut = true;
        }

        ~XmlReporter() override;

        static std::string getDescription() {
            return "Reports test results as an XML document";
        }

        virtual std::string getStylesheetRef() const {
            return std::string();
        }

        void writeSourceInfo( SourceLineInfo const& sourceInfo ) {
            m_xml
                .writeAttribute( "filename", sourceInfo.file )
                .writeAttribute( "line", sourceInfo.line );
        }

    public: // StreamingReporterBase

        void noMatchingTestCases( std::string const& s ) override {
            StreamingReporterBase::noMatchingTestCases( s );
        }

        void testRunStarting( TestRunInfo const& testInfo ) override {
            StreamingReporterBase::testRunStarting( testInfo );
            std::string stylesheetRef = getStylesheetRef();
            if( !stylesheetRef.empty() )
                m_xml.writeStylesheetRef( stylesheetRef );
            m_xml.startElement( "Catch" );
            if( !m_config->name().empty() )
                m_xml.writeAttribute( "name", m_config->name() );
        }

        void testGroupStarting( GroupInfo const& groupInfo ) override {
            StreamingReporterBase::testGroupStarting( groupInfo );
            m_xml.startElement( "Group" )
                .writeAttribute( "name", groupInfo.name );
        }

        void testCaseStarting( TestCaseInfo const& testInfo ) override {
            StreamingReporterBase::testCaseStarting(testInfo);
            m_xml.startElement( "TestCase" )
                .writeAttribute( "name", trim( testInfo.name ) )
                .writeAttribute( "description", testInfo.description )
                .writeAttribute( "tags", testInfo.tagsAsString() );

            writeSourceInfo( testInfo.lineInfo );

            if ( m_config->showDurations() == ShowDurations::Always )
                m_testCaseTimer.start();
            m_xml.ensureTagClosed();
        }

        void sectionStarting( SectionInfo const& sectionInfo ) override {
            StreamingReporterBase::sectionStarting( sectionInfo );
            if( m_sectionDepth++ > 0 ) {
                m_xml.startElement( "Section" )
                    .writeAttribute( "name", trim( sectionInfo.name ) )
                    .writeAttribute( "description", sectionInfo.description );
                writeSourceInfo( sectionInfo.lineInfo );
                m_xml.ensureTagClosed();
            }
        }

        void assertionStarting( AssertionInfo const& ) override { }

        bool assertionEnded( AssertionStats const& assertionStats ) override {

            AssertionResult const& result = assertionStats.assertionResult;

            bool includeResults = m_config->includeSuccessfulResults() || !result.isOk();

            if( includeResults ) {
                // Print any info messages in <Info> tags.
                for( auto const& msg : assertionStats.infoMessages ) {
                    if( msg.type == ResultWas::Info ) {
                        m_xml.scopedElement( "Info" )
                                .writeText( msg.message );
                    } else if ( msg.type == ResultWas::Warning ) {
                        m_xml.scopedElement( "Warning" )
                                .writeText( msg.message );
                    }
                }
            }

            // Drop out if result was successful but we're not printing them.
            if( !includeResults && result.getResultType() != ResultWas::Warning )
                return true;

            // Print the expression if there is one.
            if( result.hasExpression() ) {
                m_xml.startElement( "Expression" )
                    .writeAttribute( "success", result.succeeded() )
                    .writeAttribute( "type", result.getTestMacroName() );

                writeSourceInfo( result.getSourceInfo() );

                m_xml.scopedElement( "Original" )
                    .writeText( result.getExpression() );
                m_xml.scopedElement( "Expanded" )
                    .writeText( result.getExpandedExpression() );
            }

            // And... Print a result applicable to each result type.
            switch( result.getResultType() ) {
                case ResultWas::ThrewException:
                    m_xml.startElement( "Exception" );
                    writeSourceInfo( result.getSourceInfo() );
                    m_xml.writeText( result.getMessage() );
                    m_xml.endElement();
                    break;
                case ResultWas::FatalErrorCondition:
                    m_xml.startElement( "FatalErrorCondition" );
                    writeSourceInfo( result.getSourceInfo() );
                    m_xml.writeText( result.getMessage() );
                    m_xml.endElement();
                    break;
                case ResultWas::Info:
                    m_xml.scopedElement( "Info" )
                        .writeText( result.getMessage() );
                    break;
                case ResultWas::Warning:
                    // Warning will already have been written
                    break;
                case ResultWas::ExplicitFailure:
                    m_xml.startElement( "Failure" );
                    writeSourceInfo( result.getSourceInfo() );
                    m_xml.writeText( result.getMessage() );
                    m_xml.endElement();
                    break;
                default:
                    break;
            }

            if( result.hasExpression() )
                m_xml.endElement();

            return true;
        }

        void sectionEnded( SectionStats const& sectionStats ) override {
            StreamingReporterBase::sectionEnded( sectionStats );
            if( --m_sectionDepth > 0 ) {
                XmlWriter::ScopedElement e = m_xml.scopedElement( "OverallResults" );
                e.writeAttribute( "successes", sectionStats.assertions.passed );
                e.writeAttribute( "failures", sectionStats.assertions.failed );
                e.writeAttribute( "expectedFailures", sectionStats.assertions.failedButOk );

                if ( m_config->showDurations() == ShowDurations::Always )
                    e.writeAttribute( "durationInSeconds", sectionStats.durationInSeconds );

                m_xml.endElement();
            }
        }

        void testCaseEnded( TestCaseStats const& testCaseStats ) override {
            StreamingReporterBase::testCaseEnded( testCaseStats );
            XmlWriter::ScopedElement e = m_xml.scopedElement( "OverallResult" );
            e.writeAttribute( "success", testCaseStats.totals.assertions.allOk() );

            if ( m_config->showDurations() == ShowDurations::Always )
                e.writeAttribute( "durationInSeconds", m_testCaseTimer.getElapsedSeconds() );

            if( !testCaseStats.stdOut.empty() )
                m_xml.scopedElement( "StdOut" ).writeText( trim( testCaseStats.stdOut ), false );
            if( !testCaseStats.stdErr.empty() )
                m_xml.scopedElement( "StdErr" ).writeText( trim( testCaseStats.stdErr ), false );

            m_xml.endElement();
        }

        void testGroupEnded( TestGroupStats const& testGroupStats ) override {
            StreamingReporterBase::testGroupEnded( testGroupStats );
            // TODO: Check testGroupStats.aborting and act accordingly.
            m_xml.scopedElement( "OverallResults" )
                .writeAttribute( "successes", testGroupStats.totals.assertions.passed )
                .writeAttribute( "failures", testGroupStats.totals.assertions.failed )
                .writeAttribute( "expectedFailures", testGroupStats.totals.assertions.failedButOk );
            m_xml.endElement();
        }

        void testRunEnded( TestRunStats const& testRunStats ) override {
            StreamingReporterBase::testRunEnded( testRunStats );
            m_xml.scopedElement( "OverallResults" )
                .writeAttribute( "successes", testRunStats.totals.assertions.passed )
                .writeAttribute( "failures", testRunStats.totals.assertions.failed )
                .writeAttribute( "expectedFailures", testRunStats.totals.assertions.failedButOk );
            m_xml.endElement();
        }

    private:
        Timer m_testCaseTimer;
        XmlWriter m_xml;
        int m_sectionDepth = 0;
    };

    XmlReporter::~XmlReporter() {}
    INTERNAL_CATCH_REGISTER_REPORTER( "xml", XmlReporter )

} // end namespace Catch
// end catch_reporter_xml.cpp
// ~*~* CATCH_CPP_STITCH_PLACE *~*~

namespace Catch {
    LeakDetector leakDetector;

    // These are all here to avoid warnings about not having any out of line
    // virtual methods
    NonCopyable::~NonCopyable() {}
    IStream::~IStream() noexcept {}
    FileStream::~FileStream() noexcept {}
    CoutStream::~CoutStream() noexcept {}
    DebugOutStream::~DebugOutStream() noexcept {}
    StreamBufBase::~StreamBufBase() noexcept {}
    IContext::~IContext() {}
    IResultCapture::~IResultCapture() {}
    ITestInvoker::~ITestInvoker() {}
    ITestCaseRegistry::~ITestCaseRegistry() {}
    IRegistryHub::~IRegistryHub() {}
    IMutableRegistryHub::~IMutableRegistryHub() {}
    IExceptionTranslator::~IExceptionTranslator() {}
    IExceptionTranslatorRegistry::~IExceptionTranslatorRegistry() {}
    IRunner::~IRunner() {}
    IMutableContext::~IMutableContext() {}
    IConfig::~IConfig() {}

    void Config::dummy() {}
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

// end catch_impl.hpp
#endif

#ifdef CATCH_CONFIG_MAIN
// start catch_default_main.hpp

#ifndef __OBJC__

#if defined(WIN32) && defined(_UNICODE) && !defined(DO_NOT_USE_WMAIN)
// Standard C/C++ Win32 Unicode wmain entry point
extern "C" int wmain (int argc, wchar_t * argv[], wchar_t * []) {
#else
// Standard C/C++ main entry point
int main (int argc, char * argv[]) {
#endif

    return Catch::Session().run( argc, argv );
}

#else // __OBJC__

// Objective-C entry point
int main (int argc, char * const argv[]) {
#if !CATCH_ARC_ENABLED
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
#endif

    Catch::registerTestMethods();
    int result = Catch::Session().run( argc, (char* const*)argv );

#if !CATCH_ARC_ENABLED
    [pool drain];
#endif

    return result;
}

#endif // __OBJC__

// end catch_default_main.hpp
#endif

#ifdef CLARA_CONFIG_MAIN_NOT_DEFINED
#  undef CLARA_CONFIG_MAIN
#endif

//////
// If this config identifier is defined then all CATCH macros are prefixed with CATCH_
#ifdef CATCH_CONFIG_PREFIX_ALL

#if defined(CATCH_CONFIG_FAST_COMPILE)
#define CATCH_REQUIRE( ... ) INTERNAL_CATCH_TEST_NO_TRY( "CATCH_REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST_NO_TRY( "CATCH_REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#else
#define CATCH_REQUIRE( ... ) INTERNAL_CATCH_TEST( "CATCH_REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST( "CATCH_REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#endif

#define CATCH_REQUIRE_THROWS( ... ) INTERNAL_CATCH_THROWS( "CATCH_REQUIRE_THROWS", Catch::ResultDisposition::Normal, "", __VA_ARGS__ )
#define CATCH_REQUIRE_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CATCH_REQUIRE_THROWS_AS", exceptionType, Catch::ResultDisposition::Normal, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_REQUIRE_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CATCH_REQUIRE_THROWS_WITH", Catch::ResultDisposition::Normal, matcher, expr )
#define CATCH_REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CATCH_REQUIRE_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::Normal, matcher, expr )
#endif// CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_REQUIRE_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CATCH_REQUIRE_NOTHROW", Catch::ResultDisposition::Normal, __VA_ARGS__ )

#define CATCH_CHECK( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECK_FALSE( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK_FALSE", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#define CATCH_CHECKED_IF( ... ) INTERNAL_CATCH_IF( "CATCH_CHECKED_IF", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECKED_ELSE( ... ) INTERNAL_CATCH_ELSE( "CATCH_CHECKED_ELSE", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_CHECK_NOFAIL( ... ) INTERNAL_CATCH_TEST( "CATCH_CHECK_NOFAIL", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail, __VA_ARGS__ )

#define CATCH_CHECK_THROWS( ... )  INTERNAL_CATCH_THROWS( "CATCH_CHECK_THROWS", Catch::ResultDisposition::ContinueOnFailure, "", __VA_ARGS__ )
#define CATCH_CHECK_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CATCH_CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CATCH_CHECK_THROWS_WITH", Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#define CATCH_CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CATCH_CHECK_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CATCH_CHECK_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CATCH_CHECK_NOTHROW", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CATCH_CHECK_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CATCH_CHECK_THAT", matcher, Catch::ResultDisposition::ContinueOnFailure, arg )

#if defined(CATCH_CONFIG_FAST_COMPILE)
#define CATCH_REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT_NO_TRY( "CATCH_REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#else
#define CATCH_REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CATCH_REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#endif
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define CATCH_INFO( msg ) INTERNAL_CATCH_INFO( "CATCH_INFO", msg )
#define CATCH_WARN( msg ) INTERNAL_CATCH_MSG( "CATCH_WARN", Catch::ResultWas::Warning, Catch::ResultDisposition::ContinueOnFailure, msg )
#define CATCH_SCOPED_INFO( msg ) INTERNAL_CATCH_INFO( "CATCH_INFO", msg )
#define CATCH_CAPTURE( msg ) INTERNAL_CATCH_INFO( "CATCH_CAPTURE", #msg " := " << ::Catch::Detail::stringify(msg) )
#define CATCH_SCOPED_CAPTURE( msg ) INTERNAL_CATCH_INFO( "CATCH_CAPTURE", #msg " := " << ::Catch::Detail::stringify(msg) )

#define CATCH_TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE( __VA_ARGS__ )
#define CATCH_TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define CATCH_METHOD_AS_TEST_CASE( method, ... ) INTERNAL_CATCH_METHOD_AS_TEST_CASE( method, __VA_ARGS__ )
#define CATCH_REGISTER_TEST_CASE( Function, ... ) INTERNAL_CATCH_REGISTER_TESTCASE( Function, __VA_ARGS__ )
#define CATCH_SECTION( ... ) INTERNAL_CATCH_SECTION( __VA_ARGS__ )
#define CATCH_FAIL( ... ) INTERNAL_CATCH_MSG( "CATCH_FAIL", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define CATCH_FAIL_CHECK( ... ) INTERNAL_CATCH_MSG( "CATCH_FAIL_CHECK", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CATCH_SUCCEED( ... ) INTERNAL_CATCH_MSG( "CATCH_SUCCEED", Catch::ResultWas::Ok, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#define CATCH_ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE()

#define CATCH_REGISTER_REPORTER( name, reporterType ) INTERNAL_CATCH_REGISTER_REPORTER( name, reporterType )

// "BDD-style" convenience wrappers
#define CATCH_SCENARIO( ... ) CATCH_TEST_CASE( "Scenario: " __VA_ARGS__ )
#define CATCH_SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Scenario: " __VA_ARGS__ )
#define CATCH_GIVEN( desc )    CATCH_SECTION( std::string( "Given: ") + desc )
#define CATCH_WHEN( desc )     CATCH_SECTION( std::string( " When: ") + desc )
#define CATCH_AND_WHEN( desc ) CATCH_SECTION( std::string( "  And: ") + desc )
#define CATCH_THEN( desc )     CATCH_SECTION( std::string( " Then: ") + desc )
#define CATCH_AND_THEN( desc ) CATCH_SECTION( std::string( "  And: ") + desc )

// If CATCH_CONFIG_PREFIX_ALL is not defined then the CATCH_ prefix is not required
#else

#if defined(CATCH_CONFIG_FAST_COMPILE)
#define REQUIRE( ... ) INTERNAL_CATCH_TEST_NO_TRY( "REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST_NO_TRY( "REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )

#else
#define REQUIRE( ... ) INTERNAL_CATCH_TEST( "REQUIRE", Catch::ResultDisposition::Normal, __VA_ARGS__  )
#define REQUIRE_FALSE( ... ) INTERNAL_CATCH_TEST( "REQUIRE_FALSE", Catch::ResultDisposition::Normal | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#endif

#define REQUIRE_THROWS( ... ) INTERNAL_CATCH_THROWS( "REQUIRE_THROWS", Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define REQUIRE_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "REQUIRE_THROWS_AS", exceptionType, Catch::ResultDisposition::Normal, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define REQUIRE_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "REQUIRE_THROWS_WITH", Catch::ResultDisposition::Normal, matcher, expr )
#define REQUIRE_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "REQUIRE_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::Normal, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define REQUIRE_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "REQUIRE_NOTHROW", Catch::ResultDisposition::Normal, __VA_ARGS__ )

#define CHECK( ... ) INTERNAL_CATCH_TEST( "CHECK", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_FALSE( ... ) INTERNAL_CATCH_TEST( "CHECK_FALSE", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::FalseTest, __VA_ARGS__ )
#define CHECKED_IF( ... ) INTERNAL_CATCH_IF( "CHECKED_IF", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECKED_ELSE( ... ) INTERNAL_CATCH_ELSE( "CHECKED_ELSE", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_NOFAIL( ... ) INTERNAL_CATCH_TEST( "CHECK_NOFAIL", Catch::ResultDisposition::ContinueOnFailure | Catch::ResultDisposition::SuppressFail, __VA_ARGS__ )

#define CHECK_THROWS( ... )  INTERNAL_CATCH_THROWS( "CHECK_THROWS", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define CHECK_THROWS_AS( expr, exceptionType ) INTERNAL_CATCH_THROWS_AS( "CHECK_THROWS_AS", exceptionType, Catch::ResultDisposition::ContinueOnFailure, expr )
#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THROWS_WITH( expr, matcher ) INTERNAL_CATCH_THROWS_STR_MATCHES( "CHECK_THROWS_WITH", Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#define CHECK_THROWS_MATCHES( expr, exceptionType, matcher ) INTERNAL_CATCH_THROWS_MATCHES( "CHECK_THROWS_MATCHES", exceptionType, Catch::ResultDisposition::ContinueOnFailure, matcher, expr )
#endif // CATCH_CONFIG_DISABLE_MATCHERS
#define CHECK_NOTHROW( ... ) INTERNAL_CATCH_NO_THROW( "CHECK_NOTHROW", Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )

#if !defined(CATCH_CONFIG_DISABLE_MATCHERS)
#define CHECK_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "CHECK_THAT", matcher, Catch::ResultDisposition::ContinueOnFailure, arg )

#if defined(CATCH_CONFIG_FAST_COMPILE)
#define REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT_NO_TRY( "REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#else
#define REQUIRE_THAT( arg, matcher ) INTERNAL_CHECK_THAT( "REQUIRE_THAT", matcher, Catch::ResultDisposition::Normal, arg )
#endif // CATCH_CONFIG_FAST_COMPILE
#endif // CATCH_CONFIG_DISABLE_MATCHERS

#define INFO( msg ) INTERNAL_CATCH_INFO( "INFO", msg )
#define WARN( msg ) INTERNAL_CATCH_MSG( "WARN", Catch::ResultWas::Warning, Catch::ResultDisposition::ContinueOnFailure, msg )
#define SCOPED_INFO( msg ) INTERNAL_CATCH_INFO( "INFO", msg )
#define CAPTURE( msg ) INTERNAL_CATCH_INFO( "CAPTURE", #msg " := " << ::Catch::Detail::stringify(msg) )
#define SCOPED_CAPTURE( msg ) INTERNAL_CATCH_INFO( "CAPTURE", #msg " := " << ::Catch::Detail::stringify(msg) )

#define TEST_CASE( ... ) INTERNAL_CATCH_TESTCASE( __VA_ARGS__ )
#define TEST_CASE_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, __VA_ARGS__ )
#define METHOD_AS_TEST_CASE( method, ... ) INTERNAL_CATCH_METHOD_AS_TEST_CASE( method, __VA_ARGS__ )
#define REGISTER_TEST_CASE( Function, ... ) INTERNAL_CATCH_REGISTER_TESTCASE( Function, __VA_ARGS__ )
#define SECTION( ... ) INTERNAL_CATCH_SECTION( __VA_ARGS__ )
#define FAIL( ... ) INTERNAL_CATCH_MSG( "FAIL", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::Normal, __VA_ARGS__ )
#define FAIL_CHECK( ... ) INTERNAL_CATCH_MSG( "FAIL_CHECK", Catch::ResultWas::ExplicitFailure, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define SUCCEED( ... ) INTERNAL_CATCH_MSG( "SUCCEED", Catch::ResultWas::Ok, Catch::ResultDisposition::ContinueOnFailure, __VA_ARGS__ )
#define ANON_TEST_CASE() INTERNAL_CATCH_TESTCASE()

#define REGISTER_REPORTER( name, reporterType ) INTERNAL_CATCH_REGISTER_REPORTER( name, reporterType )

#endif

#define CATCH_TRANSLATE_EXCEPTION( signature ) INTERNAL_CATCH_TRANSLATE_EXCEPTION( signature )

// "BDD-style" convenience wrappers
#define SCENARIO( ... ) TEST_CASE( "Scenario: " __VA_ARGS__ )
#define SCENARIO_METHOD( className, ... ) INTERNAL_CATCH_TEST_CASE_METHOD( className, "Scenario: " __VA_ARGS__ )

#define GIVEN( desc )    SECTION( std::string("   Given: ") + desc )
#define WHEN( desc )     SECTION( std::string("    When: ") + desc )
#define AND_WHEN( desc ) SECTION( std::string("And when: ") + desc )
#define THEN( desc )     SECTION( std::string("    Then: ") + desc )
#define AND_THEN( desc ) SECTION( std::string("     And: ") + desc )

using Catch::Detail::Approx;

// start catch_reenable_warnings.h


#ifdef __clang__
#    ifdef __ICC // icpc defines the __clang__ macro
#        pragma warning(pop)
#    else
#        pragma clang diagnostic pop
#    endif
#elif defined __GNUC__
#    pragma GCC diagnostic pop
#endif

// end catch_reenable_warnings.h
// end catch.hpp
#endif // TWOBLUECUBES_SINGLE_INCLUDE_CATCH_HPP_INCLUDED

