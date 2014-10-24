import sys
import os
import shutil

def help():
	print "USAGE: python <Program> <lenbias> <template_file_name>  <number>"

if __name__ == "__main__":
	if 4 != len(sys.argv):
		help()
		sys.exit(-1)
	lenbias = sys.argv[1]
	template_file_name = sys.argv[2]
	file_number = sys.argv[3]
	param = r'"swf_regexp_fuzzer.exe" ' + lenbias
	param += ' '
	param += template_file_name
	param += ' '
	param += file_number
	#print param
	os.system(param)
	as3_file_output_dir = 'as3_files_output'
	as3_compiler_path = r'swf_generator\\bin\\mxmlc.exe '
	for root,dirs,files in os.walk(as3_file_output_dir):
		for filename in files:
			print filename
			file_path = os.path.join(as3_file_output_dir, filename)
			portion = os.path.splitext(filename)
			if portion[1] == '.swf':
				continue
			swf_name = portion[0] + '.swf'
			#print swf_name
			new_swf_path = 'swf_files_ouput\\'
			new_swf_path += swf_name 
			old_swf_path = os.path.join(as3_file_output_dir, swf_name);
			
			as3_compile_cmd = as3_compiler_path + file_path
			try:
				os.system(as3_compile_cmd)
				shutil.copy(old_swf_path, new_swf_path)
				os.remove(old_swf_path)
			except:
				pass
			