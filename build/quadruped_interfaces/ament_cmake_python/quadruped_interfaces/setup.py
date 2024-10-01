from setuptools import find_packages
from setuptools import setup

setup(
    name='quadruped_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('quadruped_interfaces', 'quadruped_interfaces.*')),
)
