cmake_minimum_required(VERSION 3.1)
project(unicorn)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

if(MSVC)
  include_directories(SYSTEM
    ${CMAKE_CURRENT_SOURCE_DIR}/win
  )
else()
  # GCC or Clang
  include_directories(SYSTEM
    ${CMAKE_CURRENT_SOURCE_DIR}/nix
  )
endif()
include_directories(SYSTEM
  ${UNICORN_DIR}/qemu
  ${UNICORN_DIR}/qemu/include
  ${UNICORN_DIR}/qemu/tcg
  ${UNICORN_DIR}/qemu/tcg/i386
  ${UNICORN_DIR}/qemu/target-i386
  ${UNICORN_DIR}/include
)

set(SOFTMMU_HEADERS
  ${UNICORN_DIR}/qemu/fpu/softfloat-macros.h
  ${UNICORN_DIR}/qemu/fpu/softfloat-specialize.h
  ${UNICORN_DIR}/qemu/target-i386/cc_helper_template.h
  ${UNICORN_DIR}/qemu/target-i386/cpu-qom.h
  ${UNICORN_DIR}/qemu/target-i386/cpu.h
  ${UNICORN_DIR}/qemu/target-i386/helper.h
  ${UNICORN_DIR}/qemu/target-i386/ops_sse.h
  ${UNICORN_DIR}/qemu/target-i386/ops_sse_header.h
  ${UNICORN_DIR}/qemu/target-i386/shift_helper_template.h
  ${UNICORN_DIR}/qemu/target-i386/svm.h
  ${UNICORN_DIR}/qemu/target-i386/topology.h
  ${UNICORN_DIR}/qemu/target-i386/unicorn.h
  ${UNICORN_DIR}/qemu/tcg/i386/tcg-target.h
  ${UNICORN_DIR}/qemu/tcg/tcg-be-ldst.h
  ${UNICORN_DIR}/qemu/tcg/tcg-be-null.h
  ${UNICORN_DIR}/qemu/tcg/tcg-op.h
  ${UNICORN_DIR}/qemu/tcg/tcg-opc.h
  ${UNICORN_DIR}/qemu/tcg/tcg-runtime.h
  ${UNICORN_DIR}/qemu/tcg/tcg.h
  ${UNICORN_DIR}/qemu/x86_64.h
  ${CMAKE_CURRENT_SOURCE_DIR}/x86_64-softmmu/config-target.h
)

set(SOFTMMU_SRCS
  ${UNICORN_DIR}/qemu/cpu-exec.c
  ${UNICORN_DIR}/qemu/cpus.c
  ${UNICORN_DIR}/qemu/cputlb.c
  ${UNICORN_DIR}/qemu/exec.c
  ${UNICORN_DIR}/qemu/fpu/softfloat.c
  ${UNICORN_DIR}/qemu/hw/i386/pc.c
  ${UNICORN_DIR}/qemu/hw/i386/pc_piix.c
  ${UNICORN_DIR}/qemu/hw/intc/apic.c
  ${UNICORN_DIR}/qemu/hw/intc/apic_common.c
  ${UNICORN_DIR}/qemu/ioport.c
  ${UNICORN_DIR}/qemu/memory.c
  ${UNICORN_DIR}/qemu/memory_mapping.c
  ${UNICORN_DIR}/qemu/target-i386/arch_memory_mapping.c
  ${UNICORN_DIR}/qemu/target-i386/cc_helper.c
  ${UNICORN_DIR}/qemu/target-i386/cpu.c
  ${UNICORN_DIR}/qemu/target-i386/excp_helper.c
  ${UNICORN_DIR}/qemu/target-i386/fpu_helper.c
  ${UNICORN_DIR}/qemu/target-i386/helper.c
  ${UNICORN_DIR}/qemu/target-i386/int_helper.c
  ${UNICORN_DIR}/qemu/target-i386/mem_helper.c
  ${UNICORN_DIR}/qemu/target-i386/misc_helper.c
  ${UNICORN_DIR}/qemu/target-i386/seg_helper.c
  ${UNICORN_DIR}/qemu/target-i386/smm_helper.c
  ${UNICORN_DIR}/qemu/target-i386/svm_helper.c
  ${UNICORN_DIR}/qemu/target-i386/translate.c
  ${UNICORN_DIR}/qemu/target-i386/unicorn.c
#  ${UNICORN_DIR}/qemu/tcg/i386/tcg-target.c
  ${UNICORN_DIR}/qemu/tcg/optimize.c
  ${UNICORN_DIR}/qemu/tcg/tcg.c
  ${UNICORN_DIR}/qemu/translate-all.c
)

add_library(x86_64softmmu
    ${SOFTMMU_HEADERS}
    ${SOFTMMU_SRCS}
)

if(MSVC)
  target_compile_options(x86_64softmmu PRIVATE /FI"x86_64.h"
    /I"${CMAKE_CURRENT_SOURCE_DIR}/x86_64-softmmu"
    "/MT$<$<CONFIG:Debug>:d>"
    /wd4018 /wd4244 /wd4267
  )

  target_compile_definitions(x86_64softmmu PRIVATE
    -D_CRT_SECURE_NO_WARNINGS
    -D_LIB
    -D__i386__
    -Dinline=__inline
    -D__func__=__FUNCTION__
    -DNEED_CPU_H
    -DWIN32_LEAN_AND_MEAN
  )
else()
  # GCC or Clang
  target_compile_options(x86_64softmmu PRIVATE
    "-includex86_64.h"
    "-I${CMAKE_CURRENT_SOURCE_DIR}/x86_64-softmmu"
  )
  target_compile_definitions(x86_64softmmu PRIVATE
    -D_LIB
    -DNEED_CPU_H
  )
endif()

set(UNICORN_HEADERS
  ${UNICORN_DIR}/include/list.h
  ${UNICORN_DIR}/include/qemu.h
  ${UNICORN_DIR}/include/uc_priv.h
  ${UNICORN_DIR}/include/unicorn/arm.h
  ${UNICORN_DIR}/include/unicorn/arm64.h
  ${UNICORN_DIR}/include/unicorn/m68k.h
  ${UNICORN_DIR}/include/unicorn/mips.h
  ${UNICORN_DIR}/include/unicorn/platform.h
  ${UNICORN_DIR}/include/unicorn/sparc.h
  ${UNICORN_DIR}/include/unicorn/unicorn.h
  ${UNICORN_DIR}/include/unicorn/x86.h
  ${UNICORN_DIR}/qemu/include/config.h
  ${UNICORN_DIR}/qemu/include/elf.h
  ${UNICORN_DIR}/qemu/include/exec/address-spaces.h
  ${UNICORN_DIR}/qemu/include/exec/cpu-all.h
  ${UNICORN_DIR}/qemu/include/exec/cpu-common.h
  ${UNICORN_DIR}/qemu/include/exec/cpu-defs.h
  ${UNICORN_DIR}/qemu/include/exec/cputlb.h
  ${UNICORN_DIR}/qemu/include/exec/cpu_ldst.h
  ${UNICORN_DIR}/qemu/include/exec/cpu_ldst_template.h
  ${UNICORN_DIR}/qemu/include/exec/exec-all.h
  ${UNICORN_DIR}/qemu/include/exec/gen-icount.h
  ${UNICORN_DIR}/qemu/include/exec/helper-gen.h
  ${UNICORN_DIR}/qemu/include/exec/helper-head.h
  ${UNICORN_DIR}/qemu/include/exec/helper-proto.h
  ${UNICORN_DIR}/qemu/include/exec/helper-tcg.h
  ${UNICORN_DIR}/qemu/include/exec/hwaddr.h
  ${UNICORN_DIR}/qemu/include/exec/ioport.h
  ${UNICORN_DIR}/qemu/include/exec/memory-internal.h
  ${UNICORN_DIR}/qemu/include/exec/memory.h
  ${UNICORN_DIR}/qemu/include/exec/ram_addr.h
  ${UNICORN_DIR}/qemu/include/fpu/softfloat.h
  ${UNICORN_DIR}/qemu/include/glib_compat.h
  ${UNICORN_DIR}/qemu/include/hw/arm/arm.h
  ${UNICORN_DIR}/qemu/include/hw/boards.h
  ${UNICORN_DIR}/qemu/include/hw/cpu/icc_bus.h
  ${UNICORN_DIR}/qemu/include/hw/hw.h
  ${UNICORN_DIR}/qemu/include/hw/i386/apic.h
  ${UNICORN_DIR}/qemu/include/hw/i386/apic_internal.h
  ${UNICORN_DIR}/qemu/include/hw/i386/pc.h
  ${UNICORN_DIR}/qemu/include/hw/m68k/m68k.h
  ${UNICORN_DIR}/qemu/include/hw/mips/cpudevs.h
  ${UNICORN_DIR}/qemu/include/hw/mips/mips.h
  ${UNICORN_DIR}/qemu/include/hw/qdev-core.h
  ${UNICORN_DIR}/qemu/include/hw/qdev.h
  ${UNICORN_DIR}/qemu/include/hw/sparc/sparc.h
  ${UNICORN_DIR}/qemu/include/qapi/dealloc-visitor.h
  ${UNICORN_DIR}/qemu/include/qapi/error.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp-input-visitor.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp-output-visitor.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qbool.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qdict.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qerror.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qfloat.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qint.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qjson.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qlist.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qobject.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/qstring.h
  ${UNICORN_DIR}/qemu/include/qapi/qmp/types.h
  ${UNICORN_DIR}/qemu/include/qapi/string-input-visitor.h
  ${UNICORN_DIR}/qemu/include/qapi/visitor-impl.h
  ${UNICORN_DIR}/qemu/include/qapi/visitor.h
  ${UNICORN_DIR}/qemu/include/qemu-common.h
  ${UNICORN_DIR}/qemu/include/qemu/aes.h
  ${UNICORN_DIR}/qemu/include/qemu/atomic.h
  ${UNICORN_DIR}/qemu/include/qemu/bitmap.h
  ${UNICORN_DIR}/qemu/include/qemu/bitops.h
  ${UNICORN_DIR}/qemu/include/qemu/bswap.h
  ${UNICORN_DIR}/qemu/include/qemu/compiler.h
  ${UNICORN_DIR}/qemu/include/qemu/crc32c.h
  ${UNICORN_DIR}/qemu/include/qemu/host-utils.h
  ${UNICORN_DIR}/qemu/include/qemu/int128.h
  ${UNICORN_DIR}/qemu/include/qemu/log.h
  ${UNICORN_DIR}/qemu/include/qemu/module.h
  ${UNICORN_DIR}/qemu/include/qemu/osdep.h
  ${UNICORN_DIR}/qemu/include/qemu/queue.h
  ${UNICORN_DIR}/qemu/include/qemu/range.h
  ${UNICORN_DIR}/qemu/include/qemu/thread-posix.h
  ${UNICORN_DIR}/qemu/include/qemu/thread-win32.h
  ${UNICORN_DIR}/qemu/include/qemu/thread.h
  ${UNICORN_DIR}/qemu/include/qemu/timer.h
  ${UNICORN_DIR}/qemu/include/qemu/typedefs.h
  ${UNICORN_DIR}/qemu/include/qom/cpu.h
  ${UNICORN_DIR}/qemu/include/qom/object.h
  ${UNICORN_DIR}/qemu/include/qom/qom-qobject.h
  ${UNICORN_DIR}/qemu/include/sysemu/accel.h
  ${UNICORN_DIR}/qemu/include/sysemu/cpus.h
  ${UNICORN_DIR}/qemu/include/sysemu/memory_mapping.h
  ${UNICORN_DIR}/qemu/include/sysemu/os-win32.h
  ${UNICORN_DIR}/qemu/include/sysemu/sysemu.h
  ${UNICORN_DIR}/qemu/vl.h
)

set(UNICORN_SRCS
  ${UNICORN_DIR}/list.c
  ${UNICORN_DIR}/qemu/accel.c
  ${UNICORN_DIR}/qemu/glib_compat.c
  ${UNICORN_DIR}/qemu/hw/core/machine.c
  ${UNICORN_DIR}/qemu/hw/core/qdev.c
  ${UNICORN_DIR}/qemu/qapi/qapi-dealloc-visitor.c
  ${UNICORN_DIR}/qemu/qapi/qapi-visit-core.c
  ${UNICORN_DIR}/qemu/qapi/qmp-input-visitor.c
  ${UNICORN_DIR}/qemu/qapi/qmp-output-visitor.c
  ${UNICORN_DIR}/qemu/qapi/string-input-visitor.c
  ${UNICORN_DIR}/qemu/qemu-log.c
  ${UNICORN_DIR}/qemu/qemu-timer.c
  ${UNICORN_DIR}/qemu/qobject/qbool.c
  ${UNICORN_DIR}/qemu/qobject/qdict.c
  ${UNICORN_DIR}/qemu/qobject/qerror.c
  ${UNICORN_DIR}/qemu/qobject/qfloat.c
  ${UNICORN_DIR}/qemu/qobject/qint.c
  ${UNICORN_DIR}/qemu/qobject/qlist.c
  ${UNICORN_DIR}/qemu/qobject/qstring.c
  ${UNICORN_DIR}/qemu/qom/container.c
  ${UNICORN_DIR}/qemu/qom/cpu.c
  ${UNICORN_DIR}/qemu/qom/object.c
  ${UNICORN_DIR}/qemu/qom/qom-qobject.c
  ${UNICORN_DIR}/qemu/tcg-runtime.c
  ${UNICORN_DIR}/qemu/util/aes.c
  ${UNICORN_DIR}/qemu/util/bitmap.c
  ${UNICORN_DIR}/qemu/util/bitops.c
  ${UNICORN_DIR}/qemu/util/crc32c.c
  ${UNICORN_DIR}/qemu/util/cutils.c
  ${UNICORN_DIR}/qemu/util/error.c
  ${UNICORN_DIR}/qemu/util/getauxval.c
  ${UNICORN_DIR}/qemu/util/host-utils.c
  ${UNICORN_DIR}/qemu/util/module.c
  ${UNICORN_DIR}/qemu/util/qemu-timer-common.c
  ${UNICORN_DIR}/qemu/vl.c
  ${UNICORN_DIR}/uc.c
)

if (MSVC)
  set(UNICORN_SRCS ${UNICORN_SRCS}
    ${UNICORN_DIR}/qemu/util/oslib-win32.c
    ${UNICORN_DIR}/qemu/util/qemu-thread-win32.c
    ${UNICORN_DIR}/qemu/util/qemu-error.c

    ${CMAKE_CURRENT_SOURCE_DIR}/win/qapi-types.c
    ${CMAKE_CURRENT_SOURCE_DIR}/win/qapi-visit.c

    ${CMAKE_CURRENT_SOURCE_DIR}/win/config-host.h
    ${CMAKE_CURRENT_SOURCE_DIR}/win/qapi-types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/win/qapi-visit.h
  )
else()
  # GCC or Clang
  set(UNICORN_SRCS ${UNICORN_SRCS}
    ${UNICORN_DIR}/qemu/util/oslib-posix.c
    ${UNICORN_DIR}/qemu/util/qemu-thread-posix.c

    ${CMAKE_CURRENT_SOURCE_DIR}/nix/qapi-types.c
    ${CMAKE_CURRENT_SOURCE_DIR}/nix/qapi-visit.c

    ${CMAKE_CURRENT_SOURCE_DIR}/nix/config-host.h
    ${CMAKE_CURRENT_SOURCE_DIR}/nix/qapi-types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/nix/qapi-visit.h
  )
endif()

add_library(unicorn-static
  ${UNICORN_HEADERS}
  ${UNICORN_SRCS}
)

if(MSVC)
  # MBCS?
  target_compile_options(unicorn-static PRIVATE
    "/MT$<$<CONFIG:Debug>:d>"
    /wd4018 /wd4244 /wd4267
  )
  target_compile_definitions(unicorn-static PRIVATE
    -D_LIB
    -D_CRT_SECURE_NO_WARNINGS
    -Dinline=__inline
    -D__func__=__FUNCTION__
    -D__i386__
#   -DUNICORN_HAS_ARM
#   -DUNICORN_HAS_ARM64
#   -DUNICORN_HAS_M68K
#   -DUNICORN_HAS_MIPS
#   -DUNICORN_HAS_MIPS64
#   -DUNICORN_HAS_MIPSEL
#   -DUNICORN_HAS_MIPS64EL
#   -DUNICORN_HAS_SPARC
    -DUNICORN_HAS_X86
    -DWIN32_LEAN_AND_MEAN
    -D_MBCS
  )
else()
  # GCC or Clang
  target_compile_options(unicorn-static PRIVATE
    "-includex86_64.h"
    "-I${CMAKE_CURRENT_SOURCE_DIR}/nix"
  )
  target_compile_definitions(unicorn-static PRIVATE
    -D_LIB
    -DUNICORN_HAS_X86
  )
endif()

target_link_libraries(unicorn-static
  x86_64softmmu
)