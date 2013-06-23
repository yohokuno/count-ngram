def options(opt):
    opt.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx') 
    conf.env.CXXFLAGS = ['-O3', '-Wall', '-std=c++0x']

def build(bld):
    bld.program(source='countNgram.cpp', target='count-ngram')
    bld.program(source=bld.path.ant_glob('*Test.cpp'),
        target='test', install_path=None,
        lib=['gtest','gtest_main','pthread'])

