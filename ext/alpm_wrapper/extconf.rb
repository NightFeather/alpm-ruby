require 'mkmf'

have_library("alpm") or raise

create_makefile 'alpm_wrapper/alpm_wrapper'
