import sys
import os
import shutil

def help():
	print "USAGE: python <Program> no param"

if __name__ == "__main__":
	if 1 != len(sys.argv):
		help()
		sys.exit(-1)
	http_path = 'http://127.0.0.1:8000/swf_fuzz/'
	swf_files_dir = 'C:\\Python27\\Lib\\swf_fuzz\\'
	cmd = '"C:\Program Files\Internet Explorer\iexplore.exe" '
	for root,dirs,files in os.walk(swf_files_dir):
		for filename in files:
			the_path = http_path + filename
			cmd_line = cmd + the_path
			os.system(cmd_line)
