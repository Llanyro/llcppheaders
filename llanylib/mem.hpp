//////////////////////////////////////////////
//	mem.hpp									//
//											//
//	Author: Francisco Julio Ruiz Fernandez	//
//	Author: llanyro							//
//											//
//	Version: 9.0							//
//////////////////////////////////////////////

#if defined(LLANYLIB_MEM_HPP_) // Guard && version protector
	#if LLANYLIB_MEM_MAYOR_ != 9 || LLANYLIB_MEM_MINOR_ < 0
		#if defined(LL_REAL_CXX23)
			#warning "mem.hpp version error!"
		#else
			#error "mem.hpp version error!"
		#endif // LL_REAL_CXX23
	#endif // LLANYLIB_MEM_MAYOR_ || LLANYLIB_MEM_MINOR_

#else !defined(LLANYLIB_MEM_HPP_)
#define LLANYLIB_MEM_HPP_
#define LLANYLIB_MEM_MAYOR_ 9
#define LLANYLIB_MEM_MINOR_ 0

#include "BaseNodeList.hpp"
#include "Container.hpp"

namespace llcpp {
namespace meta {
namespace mem {

namespace __mem__ {

constexpr len_t HOLDER_BUFFER_SZIE = 256;

template<class T>
struct SearchData {
	// Item to find
	T* search = LL_NULLPTR;
	// Position in node array if found
	len_t position = 0;
};

} // namespace __mem__

template<class _T, len_t _N = mem::__mem__::HOLDER_BUFFER_SZIE>
class NodeData : public meta::containers::Container<_T[_N]> {
	#pragma region Types
	public:
		// Class related
		using _MyType		= NodeData;
		using Container		= meta::containers::Container<_T[_N]>;
		using Node			= linked::FunctionalNode<NodeData>;

		// Types
		using T				= Container::T;
		using SearchData	= mem::__mem__::SearchData<_T>;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr len_t N = Container::N;

	#pragma endregion
	#pragma region Assets
	public:
		static_assert(N > 0, "Size cannot be 0!");

	#pragma endregion
	#pragma region Attirbutes
	protected:
		SearchData* searchData;

	#pragma endregion
	#pragma region Functions
		#pragma region Contructors
	public:
		constexpr NodeData() noexcept
			: Container()
			, searchData(LL_NULLPTR)
		{}
		constexpr NodeData(const T& object) noexcept
			: Container(std::forward<const T&>(object))
			, searchData(LL_NULLPTR) 
		{}
		constexpr NodeData(T&& object) noexcept
			: Container(std::forward<T&&>(object))
			, searchData(LL_NULLPTR)
		{}
		constexpr ~NodeData() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr NodeData(const NodeData& other) noexcept
			: Container(std::forward<const Container&>(other))
			, searchData(LL_NULLPTR)
		{}
		constexpr NodeData& operator=(const NodeData& other) noexcept {
			Container::operator=(std::forward<const Container&>(other));
			this->searchData = other.searchData;
			return *this;
		}
		constexpr NodeData(NodeData&& other) noexcept
			: Container(std::forward<Container&&>(other))
			, searchData(LL_NULLPTR)
		{}
		constexpr NodeData& operator=(NodeData&& other) noexcept {
			Container::operator=(std::forward<Container&&>(other));
			this->searchData = other.searchData;
			other.searchData = LL_NULLPTR;
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const NodeData*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator NodeData*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr ll_bool_t nodeChecker(const Node* a) noexcept {
			this->searchData->position = algorithm::FindersCluster<T, T, llcpp::TRUE>().find(
				a->getContainerArrayPair(), *this->searchData->search
			);
			return this->searchData->position != meta::algorithm::npos;
		}
		__LL_NODISCARD__ constexpr cmp_t compareNode(const Node* a, const Node* b) const noexcept {
			auto a_arr = a->getContainerArrayPair();
			auto b_arr = b->getContainerArrayPair();
			return algorithm::CompareCluster<_T>().compare(
				a_arr.begin(), b_arr.begin(), a_arr.lenght()
			);
		}

		__LL_NODISCARD__ constexpr void set_search(SearchData* search) noexcept {
			this->searchData = search;
		}
		__LL_NODISCARD__ constexpr SearchData* get_search(SearchData* search) const noexcept {
			return this->searchData;
		}

		constexpr void die() noexcept {}

		#pragma endregion

	#pragma endregion
};

/*template<class T, len_t N, len_t POSITION>
constexpr T get_value_base() noexcept {
	mem::__mem__::SearchData<T> searchData;
	meta::linked::Node<mem::NodeData<T, N>, llcpp::TRUE> node{};
	node.set_search(&searchData);
	auto container_array = node.getContainerArray();
	T val = 59;
	for (T& i : container_array) {
		i = val;
		val = (val + ((val > 0) ? 2 : -2)) * -1;
	}

	return node[POSITION];
}

constexpr auto _value_0 = get_value_base<int, 10, 0>();
constexpr auto _value_1 = get_value_base<int, 10, 1>();
constexpr auto _value_2 = get_value_base<int, 10, 2>();
constexpr auto _value_3 = get_value_base<int, 10, 3>();
constexpr auto _value_4 = get_value_base<int, 10, 4>();
constexpr auto _value_5 = get_value_base<int, 10, 5>();
constexpr auto _value_6 = get_value_base<int, 10, 6>();*/

template<class T, len_t N>
class StackAllocator;

template<class _T, len_t _N>
class Pool;

template<class T, len_t N = mem::__mem__::HOLDER_BUFFER_SZIE>
struct FunctionData {
	using StackAllocator = StackAllocator<T, N>;
	using Pool = Pool<T, N>;

	StackAllocator* allocator;
	Pool* pool;
	ui64 continuation_point;
	len_t position;
	T result;

	constexpr FunctionData(StackAllocator* allocator, const len_t position, const T& result) noexcept
		: allocator(allocator), continuation_point(llcpp::ZERO_UI64)
		, pool(LL_NULLPTR), position(position), result(result)
	{}
	constexpr FunctionData(StackAllocator* allocator, const len_t position, T&& result) noexcept
		: allocator(allocator), continuation_point(llcpp::ZERO_UI64)
		, pool(LL_NULLPTR), position(position), result(std::forward<T&&>(result))
	{}
	constexpr ~FunctionData() {}
};

template<class _T, len_t _N = mem::__mem__::HOLDER_BUFFER_SZIE>
class Pool : protected meta::linked::BaseNodeList<NodeData<_T, _N>, llcpp::TRUE> {
	#pragma region Types
	public:
		// Class related
		using _MyType		= Pool;
		using BaseNodeList	= meta::linked::BaseNodeList<NodeData<_T, _N>, llcpp::TRUE>;

		// Types
		using NodeType		= BaseNodeList::NodeType;
		using T				= NodeType::T;
		using SearchData	= NodeType::SearchData;

	#pragma endregion
	#pragma region Expresions
	public:
		static constexpr len_t N = NodeType::N;

	#pragma endregion
	#pragma region Assets
	public:
		static_assert(N > 0, "Size cannot be 0!");

	#pragma endregion
	#pragma region Friends
	protected:
		friend class StackAllocator<T, N>;

	#pragma endregion
	#pragma region Attirbutes
	protected:
		SearchData searchData;

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept {
			this->searchData = {};
		}

		#pragma endregion
		#pragma region Contructors
	public:
		constexpr Pool() noexcept : BaseNodeList() {}
		constexpr ~Pool() noexcept {}

		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr Pool(const Pool& other) noexcept = delete;
		constexpr Pool& operator=(const Pool& other) noexcept = delete;
		constexpr Pool(Pool&& other) noexcept
			: BaseNodeList(std::forward<BaseNodeList&&>(other))
			, searchData(other.searchData)
		{ other.simpleClear(); }
		constexpr Pool& operator=(Pool&& other) noexcept {
			BaseNodeList::operator=(std::forward<BaseNodeList&&>(other));
			this->searchData = other.searchData;
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const Pool*() const noexcept = delete;
		__LL_NODISCARD__ constexpr operator Pool*() noexcept = delete;

		#pragma endregion
		#pragma region ClassFunctions
	public:
		__LL_NODISCARD__ constexpr T* get(const len_t position) noexcept {
#if defined(_DEBUG)
			if (this->inRange(position)) __debug_error_out_of_range(position, this->length());
#endif // _DEBUG

			len_t node_pos = position / N;
			len_t array_pos = position % N;
			return &this->getNode(node_pos)->operator[](array_pos);
		}
		__LL_NODISCARD__ constexpr T* get_s(const len_t position) noexcept {
			len_t node_pos = position / N;
			len_t array_pos = position % N;
			if (!this->inRange(node_pos)) return LL_NULLPTR;
			if (array_pos > N) return LL_NULLPTR;
			return &this->getNode(node_pos)->operator[](array_pos);
		}
		__LL_NODISCARD__ constexpr ui64 numObjects() const noexcept {
			return this->lenght() * N;
		}

		constexpr void push_back(NodeType* node) noexcept {
#if defined(_DEBUG)
			if (!node) __debug_error_nullptr_str(node, "node");
#endif // _DEBUG

			this->push_back_impl(node);
		}
		__LL_NODISCARD__ constexpr ll_bool_t push_back_s(NodeType* node) noexcept {
			if (!node) return llcpp::FALSE;
			this->push_back_impl(node);
			return llcpp::TRUE;
		}


		#pragma endregion

	#pragma endregion
};

template<class T, len_t N = mem::__mem__::HOLDER_BUFFER_SZIE>
class StackAllocator {
	#pragma region Types
	public:
		// Class related
		using _MyType			= StackAllocator;
		using FunctionData		= mem::FunctionData<T, N>;

		// Types
		using CotinueSignature = void(*)(FunctionData* args) noexcept;
		using PoolType = mem::Pool<T, N>;

	#pragma endregion
	#pragma region Expresions
	public:


	#pragma endregion
	#pragma region Asserts
	public:


	#pragma endregion
	#pragma region Attributes
	protected:
		len_t bytesGenerated;
		CotinueSignature continuation;
		FunctionData* args;

	#pragma endregion
	#pragma region Functions
		#pragma region Private
	private:
		constexpr void simpleClear() noexcept {
			this->bytesGenerated = llcpp::ZERO_UI64;
			this->continuation = LL_NULLPTR;
			this->args = LL_NULLPTR;
		}

		#pragma endregion
		#pragma region Contructors
	public:
		constexpr StackAllocator() noexcept
			: bytesGenerated(llcpp::ZERO_UI64)
			, continuation(LL_NULLPTR), args(LL_NULLPTR)
		{}
		constexpr ~StackAllocator() noexcept {}
		
		#pragma endregion
		#pragma region CopyMove
	public:
		constexpr StackAllocator(const StackAllocator& other) noexcept = delete;
		constexpr StackAllocator& operator=(const StackAllocator& other) noexcept = delete;
		constexpr StackAllocator(StackAllocator&& other) noexcept
			: bytesGenerated(other.bytesGenerated)
			, continuation(other.continuation), args(other.args)
		{ other.simpleClear(); }
		constexpr StackAllocator& operator=(StackAllocator&& other) noexcept {
			this->bytesGenerated = other.bytesGenerated;
			this->continuation = other.continuation;
			this->args = other.args;
			other.simpleClear();
			return *this;
		}

		#pragma endregion
		#pragma region ClassReferenceOperators
	public:
		__LL_NODISCARD__ constexpr operator const StackAllocator*() const noexcept { return this; }
		__LL_NODISCARD__ constexpr operator StackAllocator*() noexcept { return this; }

		#pragma endregion
		#pragma region ClassFunctions
	private:
		constexpr void malloc_priv(PoolType& pool, const len_t objects) noexcept {
			typename PoolType::NodeType node{};
			pool.push_back(&node);

			if (objects > N)
				this->malloc_priv(pool, objects - N);
			else this->continuation(this->args);
		}
		constexpr void prepare_malloc(CotinueSignature continuation, FunctionData* args) noexcept {
			this->continuation = continuation;
			this->args = args;
		}

	public:
		constexpr void malloc(CotinueSignature continuation, FunctionData* args, const len_t objects) noexcept {
			PoolType pool{};
			args->pool = &pool;
			this->prepare_malloc(continuation, args);
			this->malloc_priv(pool, objects);
		}

		#pragma endregion

	#pragma endregion
};

template<class T>
constexpr void test(FunctionData<T>* args) noexcept {	
	if (args->continuation_point == 0) {
		++args->continuation_point;
		args->allocator->malloc(test<T>, args, args->position);
	}

	if (args->continuation_point == 1) {
		++args->continuation_point;
		T value = 2;
		//for (ui64 i{}; i < 2; ++i) {
		for (ui64 i{}; i < args->pool->numObjects(); ++i) {
			T* tmp = args->pool->get_s(i);
			//T* tmp = LL_NULLPTR; //args->pool->get_s(i);
			if (tmp) {
				*tmp = value;
				value = (value + ((value > 0) ? 2 : -2)) * -1;
			}
			//else {
			//	throw "Err";
			//}
		}
	}
	
	if (args->continuation_point == 2) {
		auto* tmp = args->pool->get_s(args->position);
		if(tmp) args->result = *tmp;
		else args->result = meta::algorithm::npos;
		args->continuation_point = meta::algorithm::npos;
	}
}

template<class T>
constexpr T test_prep(const len_t position) {
	StackAllocator<T> allocator;
	FunctionData<T> data(&allocator, position, llcpp::ZERO_I32);
	test<T>(&data);
	return data.result;
}

constexpr auto asdasdasda = test_prep<int>(998);
//constexpr auto asdasdasda = test_prep<int>(999);


/*template<class T>
class Holder : public linked::NodeNext<Holder<T>> {
		#pragma region Types
	public:
		using NodeNext = linked::NodeNext<Holder<T>>;
		using type = T;

	#pragma endregion
	#pragma region Asserts
	public:
		static_assert(!std::is_reference_v<T>, "Reference type is forbidden!");
		static_assert(!std::is_const_v<T>, "Const type is forbidden!");

	#pragma endregion

	protected:
		T buffer[HOLDER_BUFFER_SZIE];
	public:

};

template<class T>
class MemoryStack {
	public:
	protected:
		len_t size;
		len_t filled;
		linked::NodeNext<T>* first;
	public:
		constexpr MemoryStack(const len_t size) noexcept
			: size(size), filled(ZERO_UI64), first(LL_NULLPTR) {}
		constexpr ~MemoryStack() noexcept {}


		constexpr void setSize(const len_t size) noexcept { this->size = size; }
		constexpr void incrementSize(const len_t size) noexcept { this->size += size; }

		constexpr void setSize(const len_t size) noexcept { this->size = size; }
		constexpr void incrementSize(const len_t size) noexcept { this->size += size; }




};

template<class T, class U>
using UserDefinedFunction = std::conditional_t<
	std::is_same_v<U, void>,
	void(*)(MemoryStack<T>&) noexcept,
	void(*)(MemoryStack<T>& , U&) noexcept
>;


template<class T>
constexpr void generate_stack_memory(MemoryStack<T>& stack) noexcept {
	
}
template<class T, class U>
constexpr void generate_stack_memory(const len_t size, UserDefinedFunction<T, U> user_function, U& extra_data) noexcept {
	MemoryStack<T> stack(size);
	generate_stack_memory<T>(stack);
}
template<class T>
constexpr void generate_stack_memory<T, void>(const len_t size, UserDefinedFunction<T, void> user_function) noexcept {
	MemoryStack<T> stack(size);
	generate_stack_memory<T>(stack);
}
*/

} // namespace mem
} // namespace meta
} // namespace llcpp

#endif // LLANYLIB_MEM_HPP_
