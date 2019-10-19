import hypothesis.strategies as st
from hypothesis import given, settings

expr = st.deferred(
    lambda: st.one_of(
        st.floats(
            allow_nan=False,
            allow_infinity=False,
            min_value=1,
            max_value=10e9),
        st.tuples(st.just('('), expr, st.just(')')),
        st.tuples(expr, st.sampled_from('+-*/'), expr),
    )
)

def to_str(expr, result):
    if isinstance(expr, (float, int)):
        result.append(str(expr))
        return

    if expr[0] == '(':
        result.append(expr[0])
        to_str(expr[1], result)
        result.append(expr[2])
        return

    to_str(expr[0], result)
    result.append(expr[1])
    to_str(expr[2], result)


@settings(max_examples=2)
@given(expr)
def test(expr):
    #expr = (6292, '+', (('(', 44, ')'), '*', 82))
    result = []
    #expr = (54, '+', )
    to_str(expr, result)
    print(''.join(result))

test()

