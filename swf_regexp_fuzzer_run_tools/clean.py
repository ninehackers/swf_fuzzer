import sys
import os
import shutil

def help():
	print "USAGE: python <Program> no param"

if __name__ == "__main__":
	if 1 != len(sys.argv):
		help()
		sys.exit(-1)
	as3_files_output_dir = 'as3_files_output'
	swf_files_ouput_dir = 'swf_files_ouput'
	for root,dirs,files in os.walk(as3_files_output_dir):
		for filename in files:
			file_path = os.path.join(as3_files_output_dir, filename)
			os.remove(file_path)
	for root,dirs,files in os.walk(swf_files_ouput_dir):
		for filename in files:
			file_path = os.path.join(swf_files_ouput_dir, filename)
			os.remove(file_path)	