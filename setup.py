from setuptools import setup, Extension
import numpy as np


setup(
    ext_modules=[
        Extension(
            name="gentrig",
            sources=["gentrig.c"],
            include_dirs=[np.get_include()],
        )
    ],
)
