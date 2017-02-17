from distutils.core import setup, Extension
import subprocess


krakenprivatemodule = Extension('kr_private',
        extra_link_args=['-fPIC', '-D_GNU_SOURCE', '-D_POSIX_C_SOURCE=200112L' ],
        include_dirs = ['.', '/usr/local/lib', '/usr/lib', '/usr/lib/x86_64-linux-gnu'],
        libraries = [ 'kraken', 'crypto', 'm'],
        library_dirs = ['.', '/usr/local/lib', '/usr/lib', '/usr/lib/x86_64-linux-gnu'],
        sources = ['krakenprivatemodule.c']
        )


setup (name="kr_private", version="1.0",
      ext_modules=[krakenprivatemodule])

