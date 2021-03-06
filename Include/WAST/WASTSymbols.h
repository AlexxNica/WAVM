#pragma once

#include "Core/SExpressions.h"
#include "WAST.h"

namespace WAST
{
	#define ENUM_WAST_DECL_SYMBOLS() \
		WAST_SYMBOL(module) \
		WAST_SYMBOL(func) \
		WAST_SYMBOL(type) \
		WAST_SYMBOL(table) \
		WAST_SYMBOL(export) \
		WAST_SYMBOL(import) \
		WAST_SYMBOL(memory) \
		WAST_SYMBOL(data) \
		WAST_SYMBOL(elem) \
		WAST_SYMBOL(start) \
		WAST_SYMBOL(param) \
		WAST_SYMBOL(result) \
		WAST_SYMBOL(local) \
		WAST_SYMBOL(global) \
		WAST_SYMBOL(case) \
		WAST_SYMBOL(fallthrough) \
		WAST_SYMBOL(assert_return) \
		WAST_SYMBOL(assert_return_canonical_nan) \
		WAST_SYMBOL(assert_return_arithmetic_nan) \
		WAST_SYMBOL(assert_trap) \
		WAST_SYMBOL(assert_invalid) \
		WAST_SYMBOL(assert_unlinkable) \
		WAST_SYMBOL(assert_malformed) \
		WAST_SYMBOL(assert_exhaustion) \
		WAST_SYMBOL(invoke) \
		WAST_SYMBOL(get) \
		WAST_SYMBOL(align) \
		WAST_SYMBOL(offset) \
		WAST_SYMBOL(then) \
		WAST_SYMBOL(else) \
		WAST_SYMBOL(register)

	#define ENUM_WAST_UNIVERSAL_OPCODE_SYMBOLS() \
		WAST_SYMBOL(nop) \
		WAST_SYMBOL(br_if) \
		WAST_SYMBOL(br_table) \
		WAST_SYMBOL(select) \
		WAST_SYMBOL(call) \
		WAST_SYMBOL(call_indirect) \
		WAST_SYMBOL(if) \
		WAST_SYMBOL(loop) \
		WAST_SYMBOL(br) \
		WAST_SYMBOL(unreachable) \
		WAST_SYMBOL(return) \
		WAST_SYMBOL(block) \
		WAST_SYMBOL(get_local) \
		WAST_SYMBOL(set_local) \
		WAST_SYMBOL(tee_local) \
		WAST_SYMBOL(set_global) \
		WAST_SYMBOL(get_global) \
		WAST_SYMBOL(drop) \
		WAST_NUM_OPCODE_SYMBOL(load) \
		WAST_NUM_OPCODE_SYMBOL(store) \
		WAST_NUM_OPCODE_SYMBOL(const) \
		WAST_NUM_OPCODE_SYMBOL(sub) \
		WAST_NUM_OPCODE_SYMBOL(add) \
		WAST_NUM_OPCODE_SYMBOL(mul)

	#define ENUM_WAST_INT_OPCODE_SYMBOLS() \
		WAST_INT_OPCODE_SYMBOL(load8_s) \
		WAST_INT_OPCODE_SYMBOL(load8_u) \
		WAST_INT_OPCODE_SYMBOL(load16_s) \
		WAST_INT_OPCODE_SYMBOL(load16_u) \
		WAST_INT_OPCODE_SYMBOL(load32_s) \
		WAST_INT_OPCODE_SYMBOL(load32_u) \
		WAST_INT_OPCODE_SYMBOL(store8) \
		WAST_INT_OPCODE_SYMBOL(store16) \
		WAST_INT_OPCODE_SYMBOL(store32) \
		WAST_INT_OPCODE_SYMBOL(clz) \
		WAST_INT_OPCODE_SYMBOL(ctz) \
		WAST_INT_OPCODE_SYMBOL(popcnt) \
		WAST_INT_OPCODE_SYMBOL(div_s) \
		WAST_INT_OPCODE_SYMBOL(div_u) \
		WAST_INT_OPCODE_SYMBOL(rem_s) \
		WAST_INT_OPCODE_SYMBOL(rem_u) \
		WAST_INT_OPCODE_SYMBOL(and) \
		WAST_INT_OPCODE_SYMBOL(or) \
		WAST_INT_OPCODE_SYMBOL(xor) \
		WAST_INT_OPCODE_SYMBOL(shl) \
		WAST_INT_OPCODE_SYMBOL(shr_s) \
		WAST_INT_OPCODE_SYMBOL(shr_u) \
		WAST_INT_OPCODE_SYMBOL(rotl) \
		WAST_INT_OPCODE_SYMBOL(rotr) \
		WAST_INT_OPCODE_SYMBOL(eqz) \
		WAST_SYMBOL(current_memory) \
		WAST_SYMBOL(grow_memory)

	#define ENUM_WAST_FLOAT_OPCODE_SYMBOLS() \
		WAST_FLOAT_OPCODE_SYMBOL(neg) \
		WAST_FLOAT_OPCODE_SYMBOL(abs) \
		WAST_FLOAT_OPCODE_SYMBOL(ceil) \
		WAST_FLOAT_OPCODE_SYMBOL(floor) \
		WAST_FLOAT_OPCODE_SYMBOL(trunc) \
		WAST_FLOAT_OPCODE_SYMBOL(nearest) \
		WAST_FLOAT_OPCODE_SYMBOL(div) \
		WAST_FLOAT_OPCODE_SYMBOL(rem) \
		WAST_FLOAT_OPCODE_SYMBOL(copysign) \
		WAST_FLOAT_OPCODE_SYMBOL(min) \
		WAST_FLOAT_OPCODE_SYMBOL(max) \
		WAST_FLOAT_OPCODE_SYMBOL(sqrt)

	#define ENUM_WAST_CONVERSION_OPCODE_SYMBOLS() \
		WAST_CONVERSION_OPCODE_SYMBOL(i32,wrap,i64) \
		WAST_CONVERSION_OPCODE_SYMBOL(i64,extend_s,i32) \
		WAST_CONVERSION_OPCODE_SYMBOL(i64,extend_u,i32) \
		WAST_CONVERSION_OPCODE_SYMBOL(i32,trunc_s,f32) WAST_CONVERSION_OPCODE_SYMBOL(i32,trunc_u,f32) \
		WAST_CONVERSION_OPCODE_SYMBOL(i32,trunc_s,f64) WAST_CONVERSION_OPCODE_SYMBOL(i32,trunc_u,f64) \
		WAST_CONVERSION_OPCODE_SYMBOL(i64,trunc_s,f32) WAST_CONVERSION_OPCODE_SYMBOL(i64,trunc_u,f32) \
		WAST_CONVERSION_OPCODE_SYMBOL(i64,trunc_s,f64) WAST_CONVERSION_OPCODE_SYMBOL(i64,trunc_u,f64) \
		WAST_CONVERSION_OPCODE_SYMBOL(i32,reinterpret,f32) \
		WAST_CONVERSION_OPCODE_SYMBOL(f32,reinterpret,i32) \
		WAST_CONVERSION_OPCODE_SYMBOL(i64,reinterpret,f64) \
		WAST_CONVERSION_OPCODE_SYMBOL(f64,reinterpret,i64) \
		WAST_CONVERSION_OPCODE_SYMBOL(f64,promote,f32) \
		WAST_CONVERSION_OPCODE_SYMBOL(f32,demote,f64) \
		WAST_CONVERSION_OPCODE_SYMBOL(f32,convert_s,i32) WAST_CONVERSION_OPCODE_SYMBOL(f32,convert_u,i32) \
		WAST_CONVERSION_OPCODE_SYMBOL(f32,convert_s,i64) WAST_CONVERSION_OPCODE_SYMBOL(f32,convert_u,i64) \
		WAST_CONVERSION_OPCODE_SYMBOL(f64,convert_s,i32) WAST_CONVERSION_OPCODE_SYMBOL(f64,convert_u,i32) \
		WAST_CONVERSION_OPCODE_SYMBOL(f64,convert_s,i64) WAST_CONVERSION_OPCODE_SYMBOL(f64,convert_u,i64) \

	#define ENUM_WAST_COMPARISON_OPCODE_SYMBOLS() \
		WAST_NUM_OPCODE_SYMBOL(eq) \
		WAST_NUM_OPCODE_SYMBOL(ne) \
		WAST_INT_OPCODE_SYMBOL(lt_s) \
		WAST_INT_OPCODE_SYMBOL(lt_u) \
		WAST_INT_OPCODE_SYMBOL(le_s) \
		WAST_INT_OPCODE_SYMBOL(le_u) \
		WAST_INT_OPCODE_SYMBOL(gt_s) \
		WAST_INT_OPCODE_SYMBOL(gt_u) \
		WAST_INT_OPCODE_SYMBOL(ge_s) \
		WAST_INT_OPCODE_SYMBOL(ge_u) \
		WAST_FLOAT_OPCODE_SYMBOL(lt) \
		WAST_FLOAT_OPCODE_SYMBOL(le) \
		WAST_FLOAT_OPCODE_SYMBOL(gt) \
		WAST_FLOAT_OPCODE_SYMBOL(ge)

	#define ENUM_WAST_TYPE_SYMBOLS() \
		WAST_SYMBOL(i32) \
		WAST_SYMBOL(i64) \
		WAST_SYMBOL(f32) \
		WAST_SYMBOL(f64) \
		WAST_SYMBOL(anyfunc) \
		WAST_SYMBOL(mut)

	#define ENUM_WAST_SYMBOLS() \
		ENUM_WAST_DECL_SYMBOLS() \
		ENUM_WAST_UNIVERSAL_OPCODE_SYMBOLS() \
		ENUM_WAST_INT_OPCODE_SYMBOLS() \
		ENUM_WAST_FLOAT_OPCODE_SYMBOLS() \
		ENUM_WAST_CONVERSION_OPCODE_SYMBOLS() \
		ENUM_WAST_COMPARISON_OPCODE_SYMBOLS() \
		ENUM_WAST_TYPE_SYMBOLS()

	// Declare an enum with all the symbols used by WAST.
	enum class Symbol : uintp
	{
		#define WAST_SYMBOL(symbol) _##symbol,
		#define WAST_INT_OPCODE_SYMBOL(opcode) _i32_##opcode, _i64_##opcode,
		#define WAST_FLOAT_OPCODE_SYMBOL(opcode) _f32_##opcode, _f64_##opcode,
		#define WAST_NUM_OPCODE_SYMBOL(opcode) WAST_INT_OPCODE_SYMBOL(opcode) WAST_FLOAT_OPCODE_SYMBOL(opcode)
		#define WAST_CONVERSION_OPCODE_SYMBOL(destType,opcode,sourceType) _##destType##_##opcode##_##sourceType,
		ENUM_WAST_SYMBOLS()
		#undef WAST_SYMBOL
		#undef WAST_INT_OPCODE_SYMBOL
		#undef WAST_FLOAT_OPCODE_SYMBOL
		#undef WAST_NUM_OPCODE_SYMBOL
		#undef WAST_CONVERSION_OPCODE_SYMBOL
		num
	};

	// Declare an array, indexed by the symbol enum, containing the symbol string.
	extern WAST_API const char* wastSymbols[(size_t)Symbol::num];
	
	// Encapsulates static initialization of the WAST symbol index map.
	WAST_API const SExp::SymbolIndexMap& getWASTSymbolIndexMap();
}
