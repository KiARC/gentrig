from distutils.core import setup, Extension
import numpy

setup(
      ext_modules = [
          Extension(
              name="gentrig",
              sources=["gentrig.c"],
              include_dirs=[numpy.get_include()]
            )
          ]
);