#pragma once

#include "Core/Core.h"
#include "Core/Platform.h"
#include "TaggedValue.h"
#include "WebAssembly/Types.h"

#ifndef RUNTIME_API
	#define RUNTIME_API DLL_IMPORT
#endif

// Declare WebAssembly::Module to avoid including the definition.
namespace WebAssembly { struct Module; }

namespace Runtime
{
	// Information about a runtime exception.
	struct Exception
	{
		enum class Cause : uint8
		{
			unknown,
			accessViolation,
			stackOverflow,
			integerDivideByZeroOrIntegerOverflow,
			invalidFloatOperation,
			invokeSignatureMismatch,
			reachedUnreachable,
			indirectCallSignatureMismatch,
			undefinedTableElement,
			calledAbort,
			calledUnimplementedIntrinsic
		};

		Cause cause;
		std::vector<std::string> callStack;		
	};
	
	// Returns a string that describes the given exception cause.
	inline const char* describeExceptionCause(Exception::Cause cause)
	{
		switch(cause)
		{
		case Exception::Cause::accessViolation: return "access violation";
		case Exception::Cause::stackOverflow: return "stack overflow";
		case Exception::Cause::integerDivideByZeroOrIntegerOverflow: return "integer divide by zero or signed integer overflow";
		case Exception::Cause::invalidFloatOperation: return "invalid floating point operation";
		case Exception::Cause::invokeSignatureMismatch: return "invoke signature mismatch";
		case Exception::Cause::reachedUnreachable: return "reached unreachable code";
		case Exception::Cause::indirectCallSignatureMismatch: return "call_indirect to function with wrong signature";
		case Exception::Cause::undefinedTableElement: return "undefined function table element";
		case Exception::Cause::calledAbort: return "called abort";
		case Exception::Cause::calledUnimplementedIntrinsic: return "called unimplemented intrinsic";
		default: return "unknown";
		}
	}

	struct InstantiationException
	{
		enum Cause
		{
			importCountMismatch,
			importTypeMismatch,
			invalidInitializerGlobalRef,
			invalidDataSegmentBase,
			codeGenFailed,
			startFunctionException,
			outOfMemory
		};

		const Cause cause;

		InstantiationException(Cause inCause): cause(inCause) {}
	};

	struct FunctionInstance;
	struct Table;
	struct Memory;
	struct GlobalInstance;
	struct ModuleInstance;

	struct Object
	{
		const WebAssembly::ObjectKind kind;

		Object(WebAssembly::ObjectKind inKind): kind(inKind) {}
		virtual ~Object() {}
	};
	
	RUNTIME_API bool isA(Object* object,const WebAssembly::ObjectType& type);

	inline FunctionInstance* asFunction(Object* object)	{ assert(object && object->kind == WebAssembly::ObjectKind::function); return (FunctionInstance*)object; }
	inline Table* asTable(Object* object)				{ assert(object && object->kind == WebAssembly::ObjectKind::table); return (Table*)object; }
	inline Memory* asMemory(Object* object)			{ assert(object && object->kind == WebAssembly::ObjectKind::memory); return (Memory*)object; }
	inline GlobalInstance* asGlobal(Object* object)		{ assert(object && object->kind == WebAssembly::ObjectKind::global); return (GlobalInstance*)object; }
	inline ModuleInstance* asModule(Object* object)		{ assert(object && object->kind == WebAssembly::ObjectKind::module); return (ModuleInstance*)object; }

	inline FunctionInstance* asFunctionNullable(Object* object)	{ return object && object->kind == WebAssembly::ObjectKind::function ? (FunctionInstance*)object : nullptr; }
	inline Table* asTableNullable(Object* object)			{ return object && object->kind == WebAssembly::ObjectKind::table ? (Table*)object : nullptr; }
	inline Memory* asMemoryNullable(Object* object)		{ return object && object->kind == WebAssembly::ObjectKind::memory ? (Memory*)object : nullptr; }
	inline GlobalInstance* asGlobalNullable(Object* object)		{ return object && object->kind == WebAssembly::ObjectKind::global ? (GlobalInstance*)object : nullptr; }
	inline ModuleInstance* asModuleNullable(Object* object)	{ return object && object->kind == WebAssembly::ObjectKind::module ? (ModuleInstance*)object : nullptr; }

	inline Object* asObject(FunctionInstance* function) { return (Object*)function; }
	inline Object* asObject(Table* table) { return (Object*)table; }
	inline Object* asObject(Memory* memory) { return (Object*)memory; }
	inline Object* asObject(GlobalInstance* global) { return (Object*)global; }
	inline Object* asObject(ModuleInstance* module) { return (Object*)module; }

	// Function API
	RUNTIME_API Value invokeFunction(FunctionInstance* function,const std::vector<Value>& parameters);
	RUNTIME_API const WebAssembly::FunctionType* getFunctionType(FunctionInstance* function);

	// Table API
	RUNTIME_API Table* createTable(WebAssembly::TableType type);
	RUNTIME_API Object* getTableElement(Table* table,uintptr index);
	RUNTIME_API Object* setTableElement(Table* table,uintptr index,Object* newValue);
	RUNTIME_API size_t getTableNumElements(Table* table);
	RUNTIME_API size_t getTableMaxElements(Table* table);
	RUNTIME_API intptr_t growTable(Table* table,size_t numElements);
	RUNTIME_API intptr_t shrinkTable(Table* table,size_t numElements);

	// Memory API
	RUNTIME_API Memory* createMemory(WebAssembly::MemoryType type);
	RUNTIME_API uint8* getMemoryBaseAddress(Memory* memory);
	RUNTIME_API size_t getMemoryNumPages(Memory* memory);
	RUNTIME_API size_t getMemoryMaxPages(Memory* memory);
	RUNTIME_API intptr_t growMemory(Memory* memory,size_t numPages);
	RUNTIME_API intptr_t shrinkMemory(Memory* memory,size_t numPages);

	// Validates that an offset range is wholly inside a Memory's virtual address range.
	RUNTIME_API uint8* getValidatedMemoryOffsetRange(Memory* memory,uintptr offset,size_t numBytes);
	
	// Validates an access to a single element of memory at the given offset, and returns a reference to it.
	template<typename Value> Value& memoryRef(Memory* memory,uint32 offset)
	{ return *(Value*)getValidatedMemoryOffsetRange(memory,offset,sizeof(Value)); }

	// Validates an access to multiple elements of memory at the given offset, and returns a pointer to it.
	template<typename Value> Value* memoryArrayPtr(Memory* memory,uint32 offset,uint32 numElements)
	{ return (Value*)getValidatedMemoryOffsetRange(memory,offset,numElements * sizeof(Value)); }

	// Global API
	RUNTIME_API GlobalInstance* createGlobal(WebAssembly::GlobalType type,Value initialValue);
	RUNTIME_API Value getGlobalValue(GlobalInstance* global);
	RUNTIME_API Value setGlobalValue(GlobalInstance* global,Value newValue);

	// Module API
	RUNTIME_API ModuleInstance* instantiateModule(const WebAssembly::Module& module,std::vector<Object*>&& imports);
	RUNTIME_API Memory* getDefaultMemory(ModuleInstance* moduleInstance);
	RUNTIME_API Table* getDefaultTable(ModuleInstance* moduleInstance);
	RUNTIME_API Object* getInstanceExport(ModuleInstance* moduleInstance,const char* exportName);

	// Initializes the runtime. Should only be called once.
	RUNTIME_API void init();

	// Causes an exception.
	[[noreturn]] RUNTIME_API void causeException(Exception::Cause cause);

	// Frees unreferenced Objects, using the provided array of Objects as the root set.
	RUNTIME_API void freeUnreferencedObjects(const std::vector<Object*>& rootObjectReferences);
}
