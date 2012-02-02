VERSION = '0.1.0'
APPNAME = 'algorithm_library'

def options(opt):
    opt.load('compiler_cxx')
    opt.load('unittest_gtest')

def configure(conf):
    conf.load('compiler_cxx')
    conf.load('unittest_gtest')
    conf.check_cxx(lib = 'pthread')
#    conf.check_cfg(package = 'pficommon', args = '--cflags --libs', uselib_store = 'PFICOMMON')
    
    conf.env.CXXFLAGS += ['-W', '-Wall', '-Wextra', '-O2', '-g', '-pg']

def build(bld):
    bld.recurse('src')
    
