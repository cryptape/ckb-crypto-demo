/*
* OS and machine specific utility functions
* (C) 2015,2016,2017,2018 Jack Lloyd
* (C) 2016 Daniel Neus
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#include <botan/internal/os_utils.h>
#include <botan/cpuid.h>
#include <botan/exceptn.h>
#include <botan/mem_ops.h>

#include <algorithm>
#include <chrono>
#include <cstdlib>


#if defined(BOTAN_TARGET_OS_HAS_EXPLICIT_BZERO)
  #include <string.h>
#endif


#if defined(BOTAN_TARGET_OS_IS_EMSCRIPTEN)
  #include <emscripten/emscripten.h>
#endif




namespace Botan {

// Not defined in OS namespace for historical reasons
void secure_scrub_memory(void* ptr, size_t n)
   {
#if defined(BOTAN_TARGET_OS_HAS_RTLSECUREZEROMEMORY)
   ::RtlSecureZeroMemory(ptr, n);

#elif defined(BOTAN_TARGET_OS_HAS_EXPLICIT_BZERO)
   ::explicit_bzero(ptr, n);

#elif defined(BOTAN_TARGET_OS_HAS_EXPLICIT_MEMSET)
   (void)::explicit_memset(ptr, 0, n);

#elif defined(BOTAN_USE_VOLATILE_MEMSET_FOR_ZERO) && (BOTAN_USE_VOLATILE_MEMSET_FOR_ZERO == 1)
   /*
   Call memset through a static volatile pointer, which the compiler
   should not elide. This construct should be safe in conforming
   compilers, but who knows. I did confirm that on x86-64 GCC 6.1 and
   Clang 3.8 both create code that saves the memset address in the
   data segment and unconditionally loads and jumps to that address.
   */
   static void* (*const volatile memset_ptr)(void*, int, size_t) = std::memset;
   (memset_ptr)(ptr, 0, n);
#else

   volatile uint8_t* p = reinterpret_cast<volatile uint8_t*>(ptr);

   for(size_t i = 0; i != n; ++i)
      p[i] = 0;
#endif
   }

uint32_t OS::get_process_id()
   {
/*
#if defined(BOTAN_TARGET_OS_HAS_POSIX1)
   return ::getpid();
#elif defined(BOTAN_TARGET_OS_HAS_WIN32)
   return ::GetCurrentProcessId();
#elif defined(BOTAN_TARGET_OS_IS_INCLUDEOS) || defined(BOTAN_TARGET_OS_IS_LLVM) || defined(BOTAN_TARGET_OS_IS_NONE)
   return 0; // truly no meaningful value
#else
   #error "Missing get_process_id"
#endif
*/
   return 0;
   }

unsigned long OS::get_auxval(unsigned long id)
   {
return 0;
   }

bool OS::running_in_privileged_state()
   {
return false ;
   }

uint64_t OS::get_cpu_cycle_counter()
   {

   return 0;
   }

size_t OS::get_cpu_total()
   {
      return 1;
   }

size_t OS::get_cpu_available()
   {
      return 0;
   }

uint64_t OS::get_high_resolution_clock()
   {
      return 0;
   }

uint64_t OS::get_system_timestamp_ns()
   {
   return 4096;//deault page size
   }

size_t OS::get_memory_locking_limit()
   {
      return 0;
   }

bool OS::read_env_variable(std::string& value_out, const std::string& name)
   {
      return false;
   }

size_t OS::read_env_variable_sz(const std::string& name, size_t def)
   {

   return def;
   }

#if defined(BOTAN_TARGET_OS_HAS_POSIX1) && defined(BOTAN_TARGET_OS_HAS_POSIX_MLOCK)

namespace {

int get_locked_fd()
   {
      return 0;
   }

}

#endif

std::vector<void*> OS::allocate_locked_pages(size_t count)
   {
   std::vector<void*> result;

   return result;
   }

void OS::page_allow_access(void* page)
   {
      return ;
   }

void OS::page_prohibit_access(void* page)
   {
      return ;
   }

void OS::free_locked_pages(const std::vector<void*>& pages)
   {
      return;
   }


int OS::run_cpu_instruction_probe(std::function<int ()> probe_fn)
   {
   volatile int probe_result = -3;

   return probe_result;
   }

std::unique_ptr<OS::Echo_Suppression> OS::suppress_echo_on_terminal()
   {
   // Not supported on this platform, return null
   return std::unique_ptr<Echo_Suppression>();
   }

}
