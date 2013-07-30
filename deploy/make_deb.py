#!/usr/bin/python

import string, os, stat, shutil, subprocess, mmap, re, glob

# Package options
pkg_options = {
	'pkg_name': 'libnovile',
	'architecture': "amd64",
	'build_system': 'debian7'}

# Extract package version
def read_version(src_w_version, version_prefix):
	with open(src_w_version) as version_f:
		# 0 - whole file
		data = mmap.mmap(version_f.fileno(), 0, access = mmap.ACCESS_READ)
		m = re.search(re.escape(version_prefix) + '(\d+\.\d+\.\d+)(\+|\-)?', data)
		version = m.group(1)
		beta_sign = m.group(2)
		data.close()
		
		# construct package version from 'beta' sign
		if beta_sign == '+':
			package_version = '1'
		elif beta_sign == '-':
			package_version = '2'
		else:
			package_version = '0'
		
		return version + '-' + package_version


src_w_version = '../pro/novile.pro'
version_prefix = 'VERSION = '
pkg_options['version'] = read_version(src_w_version, version_prefix)

# Package control
deb_control = string.Template("""
Package: libnovile
Version: $version
Maintainer: Yury Kapoyko <yury.kapoyko@gmail.com>
Architecture: $architecture
Section: misc
Description: Library files for Novile (https://github.com/tucnak/novile)
Depends: libqt4-core, libqt4-gui, libqt4-webkit
""").substitute(pkg_options)

def collect_files(pkg_root):
	# Library files
	os.makedirs(os.path.join(pkg_root, 'usr/lib'))
	for f in glob.glob('../lib/*.so*'):
		shutil.copy(f, os.path.join(pkg_root, 'usr/lib'))
	
	# Package files
	os.makedirs(os.path.join(pkg_root, 'DEBIAN'))
	with open(os.path.join(pkg_root, 'DEBIAN', 'control'), 'w') as f:
		f.write(deb_control)

# Build packet
def build_packet(pkg_root):
	pkg_name = pkg_options['pkg_name'] + '.' + pkg_options['build_system'] + '_' + pkg_options['version'] + \
		'_' + pkg_options['architecture'] + '.deb'
	subprocess.check_call(['fakeroot', 'dpkg-deb', '--build', pkg_root, pkg_name])

# MAIN program

# Create package root
pkg_root = 'pkg_root'
if os.path.exists(pkg_root):
	raise Exception('Package root directory "' + pkg_root + '" already exists')

# Build packet
try:
	collect_files(pkg_root)
	build_packet(pkg_root)
finally:
	# Clean-up package root
	shutil.rmtree(pkg_root)
