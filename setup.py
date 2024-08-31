from distutils.core import setup, Extension
from numpy import get_include


setup(
    ext_modules=[
        Extension(name="gentrig", sources=[
                  "gentrig.c"], include_dirs=[get_include()])
    ]
)
