from distutils.core import setup, Extension
from numpy import get_include


setup(
    name="gentrig",
    version="0.1.0",
    description="Trigonometric functions generalized for parabolas and polygons",
    author="Katherine Rose",
    author_email="kiarc@kiarc.win",
    ext_modules=[
        Extension(name="gentrig", sources=["gentrig.c"], include_dirs=[get_include()])
    ]
)
