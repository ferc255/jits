import ctypes
import unittest
from hypothesis import given, settings
import hypothesis.strategies as st


mod = ctypes.cdll.LoadLibrary('libhyposmoke.so')
#mod.tess(b'sdfsdlfkewo', 4)
count = 0

class A(unittest.TestCase):
    def test1(self):
        pass

    @settings(max_examples=10)
    @given(st.text())
    def test2(self, s):
        global count
        print(count, str(s))
        count += 1

        if len(s) > 4 and '8' in s:
            trash += 1


if __name__ == '__main__':
    unittest.main()

