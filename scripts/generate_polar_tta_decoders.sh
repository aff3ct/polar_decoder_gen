#/bin/bash

mkdir ../src_generated          > /dev/null 2>&1
mkdir ../src_generated/SC/      > /dev/null 2>&1
mkdir ../src_generated/SCL/     > /dev/null 2>&1
mkdir ../src_generated/SCL/CRC/ > /dev/null 2>&1

echo "Generates SC decoders (rate 1/2)..."
../build/bin/polar_decoder_gen -D SC -N 1024 -K 512 --fbg-gen-method FILE --fbg-awgn-path ../lib/aff3ct/conf/cde/awgn_polar_codes/TV/10/N1024_awgn_s0.750.pc --dec-polar-nodes "{R0_8+,R1_8+,R0L_8+}"  --fbg-snr 1.0 -a TTA
# ../build/bin/polar_decoder_gen -D SC -N 512  -K 256 --fbg-gen-method FILE --fbg-awgn-path ../lib/aff3ct/conf/cde/awgn_polar_codes/TV/9/N512_awgn_s0.750.pc   --dec-polar-nodes "{R0_8+,R1_8+}"  --fbg-snr 1.0 -a TTA
# ../build/bin/polar_decoder_gen -D SC -N 256  -K 128 --fbg-gen-method FILE --fbg-awgn-path ../lib/aff3ct/conf/cde/awgn_polar_codes/TV/8/N256_awgn_s0.750.pc   --dec-polar-nodes "{R0_8+,R1_8+}"  --fbg-snr 1.0 -a TTA
# ../build/bin/polar_decoder_gen -D SC -N 128  -K 64  --fbg-gen-method FILE --fbg-awgn-path ../lib/aff3ct/conf/cde/awgn_polar_codes/TV/7/N128_awgn_s0.750.pc   --dec-polar-nodes "{R0_8+,R1_8+}"  --fbg-snr 1.0 -a TTA



echo "Generates SCAN decoders (rate 1/2)..."
# ../build/bin/polar_decoder_gen -D SCAN -N 1024 -K 512 --fbg-gen-method FILE --fbg-awgn-path ../lib/aff3ct/conf/cde/awgn_polar_codes/TV/10/N1024_awgn_s0.750.pc --dec-polar-nodes "{}"  --fbg-snr 1.0 -a TTA
