from setuptools import setup, Extension
from numpy import get_include

gentrig_ext = Extension(name="gentrig", sources=["gentrig.c"], include_dirs=[get_include()])

setup(ext_modules=[gentrig_ext], long_description=open('README.md').read(), long_description_content_type='text/markdown')
