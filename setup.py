import os
import shutil
from setuptools import setup
from Cython.Build import cythonize

module_list = [
    'src/utils/narrationclassifier.pyx',
    'src/utils/getBankName.pyx',
    'src/utils/substringmatch.pyx'
]


def remove_compiled_c(paths):
    for path in paths:
        c_path = path.replace('.pyx', '.c')
        new_path = os.path.join('build', c_path)
        dir_ = os.path.dirname(new_path)
        if not os.path.exists(dir_):
            os.makedirs(dir_)
        try:
            shutil.move(c_path, new_path)
            print(f'\tRemoving file: {c_path}')
        except FileNotFoundError:
            print(f"\tFile: {c_path} doesn't exists.")
            continue


setup(
    ext_modules=cythonize(module_list=module_list, language_level="3")
)
print("Removing compiled C files...")
remove_compiled_c(module_list)
print('\nDone Setup...')
