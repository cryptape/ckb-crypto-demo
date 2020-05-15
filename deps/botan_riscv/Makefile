
# This makefile was generated using 'configure.py --prefix=/code/build --cpu=riscv64 --ar-command=/riscv/bin/riscv64-unknown-elf-gcc-ar --cc-bin=/riscv/bin/riscv64-unknown-elf-g++ --cc-abi-flags= -Wl,-static -fdata-sections -ffunction-sections -Wl,--gc-sections --build-targets=static --without-os-feature=threads,thread_local,posix1,filesystem,getauxval --minimized-build --disable-shared-library --link-method=copy --enable-modules=sm2,sm3,ecdsa'

# Paths to relevant programs

CXX            = /riscv/bin/riscv64-unknown-elf-g++
LINKER         = $(CXX)
AR             = /riscv/bin/riscv64-unknown-elf-gcc-ar
AR_OPTIONS     = crs
PYTHON_EXE     = python

# Compiler Flags

ABI_FLAGS      =  -fstack-protector  -Wl,-static -fdata-sections -ffunction-sections -Wl,--gc-sections
LANG_FLAGS     = -std=c++11 -D_REENTRANT 
CXXFLAGS       = -O3 -DBOTAN_IS_BEING_BUILT
WARN_FLAGS     = -Wall -Wextra -Wpedantic -Wstrict-aliasing -Wcast-align -Wmissing-declarations -Wpointer-arith -Wcast-qual -Wzero-as-null-pointer-constant -Wnon-virtual-dtor
LIB_FLAGS      = 
LDFLAGS        = 

EXE_LINK_CMD   = $(LINKER) 

LIB_LINKS_TO   = 
EXE_LINKS_TO   = -L. -lbotan-2 $(LIB_LINKS_TO)

BUILD_FLAGS    = $(ABI_FLAGS) $(LANG_FLAGS) $(CXXFLAGS) $(WARN_FLAGS)

SCRIPTS_DIR    = src/scripts
INSTALLED_LIB_DIR = /code/build/lib

# The primary target
all: libs docs

# Executable targets

LIBRARIES     = ./libbotan-2.a


libs: $(LIBRARIES)
docs: build/doc.stamp

# Misc targets

.PHONY: all libs check docs clean distclean install

build/doc.stamp: ./doc/*.rst ./doc/api_ref/*.rst ./doc/dev_ref/*.rst
	$(PYTHON_EXE) $(SCRIPTS_DIR)/build_docs.py --build-dir="build"

clean:
	$(PYTHON_EXE) $(SCRIPTS_DIR)/cleanup.py --build-dir="build"

distclean:
	$(PYTHON_EXE) $(SCRIPTS_DIR)/cleanup.py --build-dir="build" --distclean

install: libs docs
	$(PYTHON_EXE) $(SCRIPTS_DIR)/install.py --prefix="/code/build" --build-dir="build" --bindir=/code/build/bin --libdir=/code/build/lib --docdir=share/doc --includedir=include

check: tests
	$(PYTHON_EXE) $(SCRIPTS_DIR)/check.py --build-dir="build"

# Object Files
LIBOBJS = build/obj/lib/asn1_alg_id.o build/obj/lib/asn1_attribute.o build/obj/lib/asn1_obj.o build/obj/lib/asn1_oid.o build/obj/lib/asn1_print.o build/obj/lib/asn1_str.o build/obj/lib/asn1_time.o build/obj/lib/asn1_ber_dec.o build/obj/lib/asn1_der_enc.o build/obj/lib/asn1_oid_maps.o build/obj/lib/asn1_oids.o build/obj/lib/base_buf_comp.o build/obj/lib/base_scan_name.o build/obj/lib/base_sym_algo.o build/obj/lib/base_symkey.o build/obj/lib/codec_base64.o build/obj/lib/codec_hex.o build/obj/lib/entropy_srcs.o build/obj/lib/hash.o build/obj/lib/hash_mdx_hash.o build/obj/lib/hash_sha2_32.o build/obj/lib/hash_sm3.o build/obj/lib/kdf.o build/obj/lib/kdf_kdf2.o build/obj/lib/mac.o build/obj/lib/math_bigint_big_code.o build/obj/lib/math_bigint_big_io.o build/obj/lib/math_bigint_big_ops2.o build/obj/lib/math_bigint_big_ops3.o build/obj/lib/math_bigint_big_rand.o build/obj/lib/math_bigint.o build/obj/lib/math_bigint_divide.o build/obj/lib/math_mp_comba.o build/obj/lib/math_mp_karat.o build/obj/lib/math_mp_monty.o build/obj/lib/math_mp_monty_n.o build/obj/lib/math_numbertheory_dsa_gen.o build/obj/lib/math_numbertheory_jacobi.o build/obj/lib/math_numbertheory_make_prm.o build/obj/lib/math_numbertheory_mod_inv.o build/obj/lib/math_numbertheory_monty.o build/obj/lib/math_numbertheory_monty_exp.o build/obj/lib/math_numbertheory_mp_numth.o build/obj/lib/math_numbertheory_nistp_redc.o build/obj/lib/math_numbertheory_numthry.o build/obj/lib/math_numbertheory_pow_mod.o build/obj/lib/math_numbertheory_primality.o build/obj/lib/math_numbertheory_primes.o build/obj/lib/math_numbertheory_reducer.o build/obj/lib/math_numbertheory_ressol.o build/obj/lib/pk_pad_eme.o build/obj/lib/pk_pad_emsa.o build/obj/lib/pk_pad_emsa1.o build/obj/lib/pk_pad_padding.o build/obj/lib/pubkey_blinding.o build/obj/lib/pubkey_ec_group_curve_gfp.o build/obj/lib/pubkey_ec_group.o build/obj/lib/pubkey_ec_group_ec_named.o build/obj/lib/pubkey_ec_group_point_gfp.o build/obj/lib/pubkey_ec_group_point_mul.o build/obj/lib/pubkey_ecc_key.o build/obj/lib/pubkey_ecdsa.o build/obj/lib/pubkey_keypair.o build/obj/lib/pubkey_pem.o build/obj/lib/pubkey_pk_algs.o build/obj/lib/pubkey_pk_keys.o build/obj/lib/pubkey_pk_ops.o build/obj/lib/pubkey_pkcs8.o build/obj/lib/pubkey.o build/obj/lib/pubkey_sm2.o build/obj/lib/pubkey_sm2_enc.o build/obj/lib/pubkey_workfactor.o build/obj/lib/pubkey_x509_key.o build/obj/lib/rng.o build/obj/lib/utils_assert.o build/obj/lib/utils_calendar.o build/obj/lib/utils_charset.o build/obj/lib/utils_cpuid.o build/obj/lib/utils_cpuid_arm.o build/obj/lib/utils_cpuid_ppc.o build/obj/lib/utils_cpuid_x86.o build/obj/lib/utils_ct_utils.o build/obj/lib/utils_data_src.o build/obj/lib/utils_exceptn.o build/obj/lib/utils_filesystem.o build/obj/lib/utils_mem_ops.o build/obj/lib/utils_os_utils.o build/obj/lib/utils_parsing.o build/obj/lib/utils_read_cfg.o build/obj/lib/utils_read_kv.o build/obj/lib/utils_timer.o build/obj/lib/utils_version.o


# Executable targets




# Library targets


./libbotan-2.a: $(LIBOBJS)
	$(AR) $(AR_OPTIONS) $@ $(LIBOBJS)



# Build Commands

build/obj/lib/asn1_alg_id.o: src/lib/asn1/alg_id.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/alg_id.cpp -o $@

build/obj/lib/asn1_attribute.o: src/lib/asn1/asn1_attribute.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/asn1_attribute.cpp -o $@

build/obj/lib/asn1_obj.o: src/lib/asn1/asn1_obj.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/asn1_obj.cpp -o $@

build/obj/lib/asn1_oid.o: src/lib/asn1/asn1_oid.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/asn1_oid.cpp -o $@

build/obj/lib/asn1_print.o: src/lib/asn1/asn1_print.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/asn1_print.cpp -o $@

build/obj/lib/asn1_str.o: src/lib/asn1/asn1_str.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/asn1_str.cpp -o $@

build/obj/lib/asn1_time.o: src/lib/asn1/asn1_time.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/asn1_time.cpp -o $@

build/obj/lib/asn1_ber_dec.o: src/lib/asn1/ber_dec.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/ber_dec.cpp -o $@

build/obj/lib/asn1_der_enc.o: src/lib/asn1/der_enc.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/der_enc.cpp -o $@

build/obj/lib/asn1_oid_maps.o: src/lib/asn1/oid_maps.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/oid_maps.cpp -o $@

build/obj/lib/asn1_oids.o: src/lib/asn1/oids.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/asn1/oids.cpp -o $@

build/obj/lib/base_buf_comp.o: src/lib/base/buf_comp.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/base/buf_comp.cpp -o $@

build/obj/lib/base_scan_name.o: src/lib/base/scan_name.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/base/scan_name.cpp -o $@

build/obj/lib/base_sym_algo.o: src/lib/base/sym_algo.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/base/sym_algo.cpp -o $@

build/obj/lib/base_symkey.o: src/lib/base/symkey.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/base/symkey.cpp -o $@

build/obj/lib/codec_base64.o: src/lib/codec/base64/base64.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/codec/base64/base64.cpp -o $@

build/obj/lib/codec_hex.o: src/lib/codec/hex/hex.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/codec/hex/hex.cpp -o $@

build/obj/lib/entropy_srcs.o: src/lib/entropy/entropy_srcs.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/entropy/entropy_srcs.cpp -o $@

build/obj/lib/hash.o: src/lib/hash/hash.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/hash/hash.cpp -o $@

build/obj/lib/hash_mdx_hash.o: src/lib/hash/mdx_hash/mdx_hash.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/hash/mdx_hash/mdx_hash.cpp -o $@

build/obj/lib/hash_sha2_32.o: src/lib/hash/sha2_32/sha2_32.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/hash/sha2_32/sha2_32.cpp -o $@

build/obj/lib/hash_sm3.o: src/lib/hash/sm3/sm3.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/hash/sm3/sm3.cpp -o $@

build/obj/lib/kdf.o: src/lib/kdf/kdf.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/kdf/kdf.cpp -o $@

build/obj/lib/kdf_kdf2.o: src/lib/kdf/kdf2/kdf2.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/kdf/kdf2/kdf2.cpp -o $@

build/obj/lib/mac.o: src/lib/mac/mac.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/mac/mac.cpp -o $@

build/obj/lib/math_bigint_big_code.o: src/lib/math/bigint/big_code.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/bigint/big_code.cpp -o $@

build/obj/lib/math_bigint_big_io.o: src/lib/math/bigint/big_io.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/bigint/big_io.cpp -o $@

build/obj/lib/math_bigint_big_ops2.o: src/lib/math/bigint/big_ops2.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/bigint/big_ops2.cpp -o $@

build/obj/lib/math_bigint_big_ops3.o: src/lib/math/bigint/big_ops3.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/bigint/big_ops3.cpp -o $@

build/obj/lib/math_bigint_big_rand.o: src/lib/math/bigint/big_rand.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/bigint/big_rand.cpp -o $@

build/obj/lib/math_bigint.o: src/lib/math/bigint/bigint.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/bigint/bigint.cpp -o $@

build/obj/lib/math_bigint_divide.o: src/lib/math/bigint/divide.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/bigint/divide.cpp -o $@

build/obj/lib/math_mp_comba.o: src/lib/math/mp/mp_comba.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/mp/mp_comba.cpp -o $@

build/obj/lib/math_mp_karat.o: src/lib/math/mp/mp_karat.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/mp/mp_karat.cpp -o $@

build/obj/lib/math_mp_monty.o: src/lib/math/mp/mp_monty.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/mp/mp_monty.cpp -o $@

build/obj/lib/math_mp_monty_n.o: src/lib/math/mp/mp_monty_n.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/mp/mp_monty_n.cpp -o $@

build/obj/lib/math_numbertheory_dsa_gen.o: src/lib/math/numbertheory/dsa_gen.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/dsa_gen.cpp -o $@

build/obj/lib/math_numbertheory_jacobi.o: src/lib/math/numbertheory/jacobi.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/jacobi.cpp -o $@

build/obj/lib/math_numbertheory_make_prm.o: src/lib/math/numbertheory/make_prm.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/make_prm.cpp -o $@

build/obj/lib/math_numbertheory_mod_inv.o: src/lib/math/numbertheory/mod_inv.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/mod_inv.cpp -o $@

build/obj/lib/math_numbertheory_monty.o: src/lib/math/numbertheory/monty.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/monty.cpp -o $@

build/obj/lib/math_numbertheory_monty_exp.o: src/lib/math/numbertheory/monty_exp.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/monty_exp.cpp -o $@

build/obj/lib/math_numbertheory_mp_numth.o: src/lib/math/numbertheory/mp_numth.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/mp_numth.cpp -o $@

build/obj/lib/math_numbertheory_nistp_redc.o: src/lib/math/numbertheory/nistp_redc.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/nistp_redc.cpp -o $@

build/obj/lib/math_numbertheory_numthry.o: src/lib/math/numbertheory/numthry.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/numthry.cpp -o $@

build/obj/lib/math_numbertheory_pow_mod.o: src/lib/math/numbertheory/pow_mod.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/pow_mod.cpp -o $@

build/obj/lib/math_numbertheory_primality.o: src/lib/math/numbertheory/primality.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/primality.cpp -o $@

build/obj/lib/math_numbertheory_primes.o: src/lib/math/numbertheory/primes.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/primes.cpp -o $@

build/obj/lib/math_numbertheory_reducer.o: src/lib/math/numbertheory/reducer.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/reducer.cpp -o $@

build/obj/lib/math_numbertheory_ressol.o: src/lib/math/numbertheory/ressol.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/math/numbertheory/ressol.cpp -o $@

build/obj/lib/pk_pad_eme.o: src/lib/pk_pad/eme.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pk_pad/eme.cpp -o $@

build/obj/lib/pk_pad_emsa.o: src/lib/pk_pad/emsa.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pk_pad/emsa.cpp -o $@

build/obj/lib/pk_pad_emsa1.o: src/lib/pk_pad/emsa1/emsa1.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pk_pad/emsa1/emsa1.cpp -o $@

build/obj/lib/pk_pad_padding.o: src/lib/pk_pad/padding.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pk_pad/padding.cpp -o $@

build/obj/lib/pubkey_blinding.o: src/lib/pubkey/blinding.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/blinding.cpp -o $@

build/obj/lib/pubkey_ec_group_curve_gfp.o: src/lib/pubkey/ec_group/curve_gfp.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/ec_group/curve_gfp.cpp -o $@

build/obj/lib/pubkey_ec_group.o: src/lib/pubkey/ec_group/ec_group.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/ec_group/ec_group.cpp -o $@

build/obj/lib/pubkey_ec_group_ec_named.o: src/lib/pubkey/ec_group/ec_named.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/ec_group/ec_named.cpp -o $@

build/obj/lib/pubkey_ec_group_point_gfp.o: src/lib/pubkey/ec_group/point_gfp.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/ec_group/point_gfp.cpp -o $@

build/obj/lib/pubkey_ec_group_point_mul.o: src/lib/pubkey/ec_group/point_mul.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/ec_group/point_mul.cpp -o $@

build/obj/lib/pubkey_ecc_key.o: src/lib/pubkey/ecc_key/ecc_key.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/ecc_key/ecc_key.cpp -o $@

build/obj/lib/pubkey_ecdsa.o: src/lib/pubkey/ecdsa/ecdsa.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/ecdsa/ecdsa.cpp -o $@

build/obj/lib/pubkey_keypair.o: src/lib/pubkey/keypair/keypair.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/keypair/keypair.cpp -o $@

build/obj/lib/pubkey_pem.o: src/lib/pubkey/pem/pem.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/pem/pem.cpp -o $@

build/obj/lib/pubkey_pk_algs.o: src/lib/pubkey/pk_algs.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/pk_algs.cpp -o $@

build/obj/lib/pubkey_pk_keys.o: src/lib/pubkey/pk_keys.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/pk_keys.cpp -o $@

build/obj/lib/pubkey_pk_ops.o: src/lib/pubkey/pk_ops.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/pk_ops.cpp -o $@

build/obj/lib/pubkey_pkcs8.o: src/lib/pubkey/pkcs8.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/pkcs8.cpp -o $@

build/obj/lib/pubkey.o: src/lib/pubkey/pubkey.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/pubkey.cpp -o $@

build/obj/lib/pubkey_sm2.o: src/lib/pubkey/sm2/sm2.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/sm2/sm2.cpp -o $@

build/obj/lib/pubkey_sm2_enc.o: src/lib/pubkey/sm2/sm2_enc.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/sm2/sm2_enc.cpp -o $@

build/obj/lib/pubkey_workfactor.o: src/lib/pubkey/workfactor.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/workfactor.cpp -o $@

build/obj/lib/pubkey_x509_key.o: src/lib/pubkey/x509_key.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/pubkey/x509_key.cpp -o $@

build/obj/lib/rng.o: src/lib/rng/rng.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/rng/rng.cpp -o $@

build/obj/lib/utils_assert.o: src/lib/utils/assert.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/assert.cpp -o $@

build/obj/lib/utils_calendar.o: src/lib/utils/calendar.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/calendar.cpp -o $@

build/obj/lib/utils_charset.o: src/lib/utils/charset.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/charset.cpp -o $@

build/obj/lib/utils_cpuid.o: src/lib/utils/cpuid/cpuid.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/cpuid/cpuid.cpp -o $@

build/obj/lib/utils_cpuid_arm.o: src/lib/utils/cpuid/cpuid_arm.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/cpuid/cpuid_arm.cpp -o $@

build/obj/lib/utils_cpuid_ppc.o: src/lib/utils/cpuid/cpuid_ppc.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/cpuid/cpuid_ppc.cpp -o $@

build/obj/lib/utils_cpuid_x86.o: src/lib/utils/cpuid/cpuid_x86.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/cpuid/cpuid_x86.cpp -o $@

build/obj/lib/utils_ct_utils.o: src/lib/utils/ct_utils.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/ct_utils.cpp -o $@

build/obj/lib/utils_data_src.o: src/lib/utils/data_src.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/data_src.cpp -o $@

build/obj/lib/utils_exceptn.o: src/lib/utils/exceptn.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/exceptn.cpp -o $@

build/obj/lib/utils_filesystem.o: src/lib/utils/filesystem.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/filesystem.cpp -o $@

build/obj/lib/utils_mem_ops.o: src/lib/utils/mem_ops.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/mem_ops.cpp -o $@

build/obj/lib/utils_os_utils.o: src/lib/utils/os_utils.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/os_utils.cpp -o $@

build/obj/lib/utils_parsing.o: src/lib/utils/parsing.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/parsing.cpp -o $@

build/obj/lib/utils_read_cfg.o: src/lib/utils/read_cfg.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/read_cfg.cpp -o $@

build/obj/lib/utils_read_kv.o: src/lib/utils/read_kv.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/read_kv.cpp -o $@

build/obj/lib/utils_timer.o: src/lib/utils/timer.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/timer.cpp -o $@

build/obj/lib/utils_version.o: src/lib/utils/version.cpp
	$(CXX) $(LIB_FLAGS) $(BUILD_FLAGS)  -Ibuild/include -c src/lib/utils/version.cpp -o $@






