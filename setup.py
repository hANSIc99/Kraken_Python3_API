from distutils.core import setup, Extension
import subprocess

long_description = 'This module enables to execute API calls from inside Python. 
For an overview of the diffrent API functions see https://www.kraken.com/help/api 
The result of all api calls are retrievable with the \"result\" function.'

kr_module = Extension('kr_module',
        extra_link_args=['-fPIC', '-D_GNU_SOURCE', '-D_POSIX_C_SOURCE=200112L' ],
        include_dirs = ['.', '/usr/local/lib', '/usr/lib', '/usr/lib/x86_64-linux-gnu'],
        libraries = [ 'kraken', 'crypto', 'm'],
        library_dirs = ['.', '/usr/local/lib', '/usr/lib', '/usr/lib/x86_64-linux-gnu'],
        sources = ['kr_module.c']
        )


classifiers = [
        classifiers=[
    # How mature is this project? Common values are
    #   3 - Alpha
    #   4 - Beta
    #   5 - Production/Stable
    'Development Status :: 4 - Beta',

    # Indicate who your project is intended for
    'Intended Audience :: Financial and Insurance Industry',
    'Topic :: Software Development :: Build Tools',

    # Pick your license as you wish (should match "license" above)
     'License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)',

    # Specify the Python versions you support here. In particular, ensure
    # that you indicate whether you support Python 2, Python 3 or both.
    'Programming Language :: Python :: 3',
    'Programming Language :: Python :: 3.2',
    'Programming Language :: Python :: 3.3',
    'Programming Language :: Python :: 3.4',
],


setup (name="kr_module",
        version="0.9",
        description='API for Kraken.com in Python3',
        long_description=long_description,
        url='https://github.com/hANSIc99/Kraken_Python3_API',
        author = 'Stephan Avenwedde',
        author_email = 's.avenwedde@gmail.com',
        license='GPLv3',
        keywords='API REST Kraken ecoin e-coin bitcoin bank financial',
        ext_modules=[kr_module])

