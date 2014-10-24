swf_fuzzer
==========
It is a simple swf regexp fuzzer.
1. C code will generate as files to as3_files_output
2. generate_swf_files.py will call swf compiler to generate swf files to swf_files_output
3. copy_sample_to_vm.py will copy all the swf files to one dest path you want to run swfs with IE
4. run.py will call IE to run the swfs in the dest path
5. kill_ie.py will check dump files and close windbg and IE
