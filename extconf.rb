require 'pkg-config'

PACKAGE_NAME = "loudmouth"
PACKAGE_ID = "loudmouth"

# SRCDIR = File.expand_path(File.dirname(__FILE__) + '/src')

require 'mkmf'

srcdir = File.join(File.expand_path(File.dirname(__FILE__)), 'src')

PKGConfig.have_package("loudmouth-1.0", 1, 3, 4) or exit 1
PKGConfig.have_package("glib-2.0", 2, 4, 0) or exit 1

create_makefile("loudmouth", srcdir)
