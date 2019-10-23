#include <stdio.h>
#include <jit/jit.h>


int main(int argc, char **argv)
{
	jit_context_t context;
	jit_type_t params[1];
	jit_type_t signature;
	jit_function_t function;
	jit_value_t x;
	//jit_value_t res[10];
	jit_int arg1;
	void *args[1];
	jit_int result;

	/* Create a context to hold the JIT's primary state */
	context = jit_context_create();

	/* Lock the context while we build and compile the function */
	jit_context_build_start(context);

	/* Build the function signature */
	params[0] = jit_type_int;
	signature = jit_type_create_signature
		(jit_abi_cdecl, jit_type_int, params, 1, 1);

	/* Create the function object */
	function = jit_function_create(context, signature);

	/* Construct the function body */
	x = jit_value_get_param(function, 0);
    jit_value_t size = jit_value_create_nint_constant(function, jit_type_int, 100);
    jit_value_t res = jit_insn_alloca(function, size);
    jit_value_t i = jit_value_create(function, jit_type_int);
    jit_insn_store_elem(function, res, i, x);
    
    jit_insn_return(function, i);

	/* Compile the function */
	jit_function_compile(function);

	/* Unlock the context */
	jit_context_build_end(context);

	/* Execute the function and print the result */
	arg1 = 3;
	args[0] = &arg1;
	jit_function_apply(function, args, &result);
	printf("mul_add(3, 5, 2) = %d\n", (int)result);

	/* Clean up */
	jit_context_destroy(context);

	/* Finished */
	return 0;
}
