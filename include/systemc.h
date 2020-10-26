// 2006-03-24, Thorsten Schubert, OFFIS

#ifndef QUINY_SYSTEMC_H_INCLUDED
#define QUINY_SYSTEMC_H_INCLUDED

#include "systemc"

using sc_core::sc_module;
using sc_core::sc_port;
using sc_core::sc_in;
using sc_core::sc_out;
using sc_core::sc_signal;
using sc_core::sc_module_name;
using sc_core::sc_event;
using sc_core::sc_time;

using sc_core::SC_FS; 
using sc_core::SC_PS; 
using sc_core::SC_NS; 
using sc_core::SC_US; 
using sc_core::SC_MS; 
using sc_core::SC_SEC;

using sc_core::sc_trace_file;
using sc_core::sc_create_vcd_trace_file;
using sc_core::sc_close_vcd_trace_file;
using sc_core::sc_write_comment;

using sc_core::sc_start;

using sc_dt::sc_int;
using sc_dt::sc_uint;
using sc_dt::sc_signed;
using sc_dt::sc_bigint;
using sc_dt::sc_unsigned;
using sc_dt::sc_biguint;
using sc_dt::sc_logic;
using sc_dt::sc_bv_base;
using sc_dt::sc_bv;
using sc_dt::sc_lv_base;
using sc_dt::sc_lv;
using sc_dt::sc_fxnum;
using sc_dt::sc_fix;
using sc_dt::sc_fixed;
using sc_dt::sc_ufix;
using sc_dt::sc_ufixed;


#include <iostream>
#include <fstream>
#include <cstring>

// Taken from the standard
using std::ios;
using std::streambuf;
using std::streampos;
using std::streamsize;
using std::iostream;
using std::istream;
using std::ostream;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::dec;
using std::hex;
using std::oct;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::size_t;
using std::memchr;
using std::memcmp;
using std::memcpy;
using std::memmove;
using std::memset;
using std::strcat;
using std::strncat;
using std::strchr;
using std::strrchr;
using std::strcmp;
using std::strncmp;
using std::strcpy;
using std::strncpy;
using std::strcspn;
using std::strspn;
using std::strlen;
using std::strpbrk;
using std::strstr;
using std::strtok;

#define while(cond) for(::quiny_sc::cpp_stmt::BlockHelper b(::quiny_sc::cpp_stmt::BlockHelper::BLOCK_WHILE, cond); \
                        b.m_runOnce == false;\
                        b.m_runOnce = true)

#define if(cond) for(::quiny_sc::cpp_stmt::BlockHelper b(::quiny_sc::cpp_stmt::BlockHelper::BLOCK_IF, cond,\
                                                         ::quiny::collector::SourcePos(__LINE__, __FILE__)); \
                        b.m_runOnce == false;\
                        b.m_runOnce = true)
                        
#define else for(::quiny_sc::cpp_stmt::BlockHelper b(::quiny_sc::cpp_stmt::BlockHelper::BLOCK_ELSE); \
                 b.m_runOnce == false;\
                 b.m_runOnce = true)


#define bool ::quiny_sc::cpp_dt::Bool
                                                                 
#endif
