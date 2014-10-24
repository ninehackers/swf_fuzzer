import sys
import os
import shutil

def help():
	print "USAGE: python <Program> <dest>"

if __name__ == "__main__":
	if 2 != len(sys.argv):
		help()
		sys.exit(-1)
	dest_dir = sys.argv[1]
	src_dir = 'swf_files_ouput\\'
	for root,dirs,files in os.walk(src_dir):
		for filename in files:
			file_path = os.path.join(src_dir, filename)
			new_file_path = os.path.join(dest_dir, filename)
			shutil.copy(file_path, new_file_path)
